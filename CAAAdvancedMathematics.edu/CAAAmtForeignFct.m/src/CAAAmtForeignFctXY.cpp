//
// COPYRIGHT DASSAULT SYSTEMES 2000
//

#include "CAAAmtForeignFctXY.h"

//#include <math.h>

// AdvancedMathematics       
#include "CATMathIntervalND.h"

//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
  
CAAAmtForeignFctXY::CAAAmtForeignFctXY( const double ia,
                                        const double ib,
                                        const double ic,
                                        const double iOrigin)
{
  _a = ia;
  _b = ib;
  _c = ic;
  _Origin = iOrigin;
}
                                      
//-----------------------------------------------------------------
// Information methods
//-----------------------------------------------------------------

CATMathClassId CAAAmtForeignFctXY::IsA() const
{
  return "CAAAmtForeignFctXY";
}

CATBoolean CAAAmtForeignFctXY::IsAKindOf(const CATMathClassId iClassId) const
{
  if (strcmp(iClassId,"CAAAmtForeignFctXY")==0) return (TRUE);
  return CATMathFunctionXY::IsAKindOf(iClassId);
}

CATBoolean CAAAmtForeignFctXY::IsOption(const CATMathOption iOption) const
{
  CATMathOption myOptions = 
    OptionEval + OptionEvalFirstDeriv + OptionEvalSecondDeriv ;

   if ((myOptions & iOption) == iOption) return (TRUE);   
   return (FALSE); 
}
   
//-----------------------------------------------------------------
// CAAAmtForeignFctXY::Evaluators on doubles
//-----------------------------------------------------------------
   
double CAAAmtForeignFctXY::Eval(const double & iX, 
								const double & iY) const
{
  // Directly evaluates
  return (_a*iX+_b*iY+_c*cos(iX)*cos(iY)+_Origin);
}

//-----------------------------------------------------------------
double CAAAmtForeignFctXY::EvalFirstDerivX(const double & iX, 
                                           const double & iY) const
{
  // Directly evaluates
  return (_a-_c*sin(iX)*cos(iY));
}

//-----------------------------------------------------------------
double CAAAmtForeignFctXY::EvalFirstDerivY(const double & iX, 
                                           const double & iY) const
{
  // Directly evaluates
  return (_b-_c*cos(iX)*sin(iY));
}

//-----------------------------------------------------------------   
double CAAAmtForeignFctXY::EvalSecondDerivX2(const double & iX, 
                                             const double & iY) const
{
  // Directly evaluates
  return (-_c*cos(iX)*cos(iY));
}

//-----------------------------------------------------------------
double CAAAmtForeignFctXY::EvalSecondDerivXY(const double & iX, 
                                             const double & iY) const
{
  // Directly evaluates  
  return (_c*sin(iX)*sin(iY));
}

//-----------------------------------------------------------------
double CAAAmtForeignFctXY::EvalSecondDerivY2(const double & iX, 
                                             const double & iY) const
{
  // Directly evaluates  
  return (-_c*cos(iX)*cos(iY));
}

//-----------------------------------------------------------------   
// Evaluates the function and derivatives at the same time
//   ---> to enhance the performances : 
//              cos and sin are computed only if necessary,
//              and bufferized, to be used again later.
// As multi evaluators are used in the geometric operators, it is important 
// to enhance their performances.
void CAAAmtForeignFctXY::Eval(const double iX, const double iY, 
                              const CATMathOption iOptions,
                              double * f,
                              double * fx , 
                              double * fy,
                              double * fx2, 
                              double * fxy, 
                              double * fy2) const
{
  double cosu = cos(iX), cosv = cos(iY);
  if (iOptions & OptionEval) 
  {
    *f = _a*iX+_b*iY+_c*cosu*cosv+_Origin;
    if (iOptions == OptionEval) return; // to avoid computing sin(iX) and sin(iY) in this case
  }

  double sinu=sin(iX), sinv=sin(iY);    // to compute sin(iX) and sin(iY) only once
  if (iOptions & OptionEvalFirstDeriv)  // first derivatives
  {
    *fx = _a-_c*sinu*cosv;
    *fy = _b-_c*cosu*sinv;
  }
  if (iOptions & OptionEvalSecondDeriv) // second derivatives
  {
    *fx2 = *fy2 = -_c*cosu*cosv;
    *fxy = _c*sinu*sinv;
  }
}

//-----------------------------------------------------------------    
// Multi-evaluates the function and its derivatives on a regular 
// grid of Nu x Nv points delimited by the [uStart,uEnd] x [vStart,vEnd] domain.
// The value f[Nv*i+j] contains Eval(x_i,y_j)  
//
// To speed up this multi evaluation, a precomputation computes
// fast cosinus and sinus evaluations on a regular grid thanks to the formula:
//    cos(v+delta) = cos(v)*cos(delta)-sin(v)*sin(delta)
//    sin(v+delta) = cos(v)*sin(delta)-sin(v)*cos(delta)
//
// As multi evaluators are used in the geometric operators, it is important 
// to enhance their performances.
void CAAAmtForeignFctXY::Eval(const CATMathIntervalND & iDomain, 
                              const CATLONG32 * NbPoints,
                              const CATMathOption iOptions,
                              double * f,
                              double * fx , 
                              double * fy,
                              double * fx2, 
                              double * fxy, 
                              double * fy2) const
{
  // Retrieves the number of points on each direction of the grid
  CATLONG32 nu = NbPoints[0], nv = NbPoints[1];

  // Retrieves the limits of the domain
  const double * coords = iDomain.GetCoords();

  // Computes the first coordinate of the first value 
  double uStart = coords[0], uDelta=0.;  
 
  // Computes the step in the first u direction
  if (nu>1) uDelta = (coords[1]-coords[0])/double(nu-1);

  // Computes the second coordinate of the first value 
  double vStart = coords[2], vDelta=0.;

  // Computes the step in the second v direction
  if (nv>1) vDelta = (coords[3]-coords[2])/double(nv-1);
  
  // Computes cos(vStart+j*vDelta) and sin(vStart+j*vDelta) in aSinTab and aCosTab
  double * aCosTab = new double[2*nv];
  double * aSinTab = aCosTab + nv;

  // Computes dcos and dsin to be used in the formula
  //    cos(v+delta) = cos(v)*dcos-sin(v)*dsin
  //    sin(v+delta) = cos(v)*dsin-sin(v)*dcos
  double dcos = cos(vDelta), dsin = sin(vDelta);

  // Fills the arrays
  aCosTab[0] = cos(vStart);
  aSinTab[0] = sin(vStart);

  for (CATLONG32 j=1; j<nv; j++) 
  {
    aCosTab[j] = aCosTab[j-1]*dcos-aSinTab[j-1]*dsin;
    aSinTab[j] = aCosTab[j-1]*dsin+aSinTab[j-1]*dcos;
  }
  //
  // ------------------  Main double loop to fill the returned arrays
  // 
  double cosu = cos(uStart);
  double sinu = sin(uStart);
  dcos = cos(uDelta);
  dsin = sin(uDelta);
  double u = uStart;
  for (CATLONG32 i=0; i<nu; i++) {
    if (i>0) {
      double tmp = cosu;            // to avoid to recompute it
      cosu = cosu*dcos-sinu*dsin;   // c = cos(uStart+i*uDelta)
      sinu = tmp*dsin+sinu*dcos;    // s = sin(uStart+i*uDelta)
    }
    double v = vStart;
    for (CATLONG32 j=0; j<nv; j++) {
      if (iOptions & OptionEval)
        *(f++) = _a*u+_b*v+_c*cosu*aCosTab[j]+_Origin;
      if (iOptions & OptionEvalFirstDeriv) 
      {
        *(fx++) = _a-_c*sinu*aCosTab[j];
        *(fy++) = _b-_c*cosu*aSinTab[j];
      }
      if (iOptions & OptionEvalSecondDeriv) 
      {
        *(fx2++) = *(fy2++) = -_c*cosu*aCosTab[j];
        *(fxy++) = _c*sinu*aSinTab[j];
      }
      v += vDelta;
    }
    u += uDelta;
  }
  delete [] aCosTab;
  aCosTab = NULL;
}
  
   
