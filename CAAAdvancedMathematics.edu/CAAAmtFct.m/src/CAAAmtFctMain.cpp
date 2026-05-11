//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2000
//
// Sample code for : Geometric Modeler
// Mission         : Derivation of a new mathematical function: the egg box.
//                   The CAAAmtForeignFctXY is defined in CAAAmtForeignFctXY.h 
//                   The code is in CAAAmtForeignFctXY.cpp
//
// Type            : Batch program
// Inputs          : None
// Outputs         : cout
// Returns         : 0      if all is OK
//                 : 1 or 2 if the function type is wrong
//                 : 3      if the evaluation is wrong
//                 : 4      if the derative evaluation is wrong
//                 : 5      if the second derivative evaluation is wrong
//                 : 6      if the derivative evaluation is wrong
// Illustrates     : 1- How to create a new type of mathematical function, that 
//                    can be later used in foreign surfaces
//                   2- How to use mathematical functions CATMathFunctionXY: the evaluations
//                   
//
// How to run it   : CAAAmtFct                              
//=============================================================================

#include <iostream.h>
#include <math.h>

// Mathematics
#include "CATMath.h"                  // for CATAbs         
#include "CATMathConstant.h"          // CATPI definition

// AdvancedMathematics
#include "CATMathIntervalND.h"        // N dimensional interval

// Foreign definition
#include "CAAAmtForeignFctXY.h"       // the created class 


//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main()   
{
 int rc=0;
 
  // -----------------------------------------------------------------------------
  // 1-Creates a CAAAmtForeignFctXY instance 
  // -----------------------------------------------------------------------------
  double a = 1.;
  double b = 2.;
  double c = 3.;
  double d = 10.;

  //(u,v) -> F(u,v) = a*u + b*v + c * cos(u)*cos(v) + d
  CAAAmtForeignFctXY f(a,b,c,d);

  // Checks the type
  if (FALSE== f.IsAKindOf("CAAAmtForeignFctXY") )   return (1);
  if (FALSE== f.IsAKindOf("CATMathFunctionXY") )    return (2);

  // -----------------------------------------------------------------------------
  // 2-Uses the evaluators
  // -----------------------------------------------------------------------------

  double u=0., v=0.;
  double val = f.Eval (u,v);
  if (val != (c+d))                                 return (3);


  // ------------ Computes the first derivative in u
  u = 0.; 
  v = CATPIBY4;
  val = f.EvalFirstDerivX(u,v);
  if (val != (a-c*sin(u)*cos(v)) )                  return (4);

  // ------------ Computes the first derivative in v
  double val1 = f.EvalFirstDerivY(u,v);
  if (val1 != (b-c*cos(u)*sin(v)) )                 return (4);

  // ------------ Computes the second derivatives 
  double val2 = f.EvalSecondDerivX2(u,v);
  if (val2 != (-c*cos(u)*cos(v)) )                 return (4);

  double val3 = f.EvalSecondDerivXY(u,v);
  if (val3 != (-c*sin(u)*sin(v)) )                 return (4);

  double val4 = f.EvalSecondDerivY2(u,v);
  if (val4 != (-c*cos(u)*cos(v)) )                 return (4);

  // ------------ Simultaneously evaluates at a point
  double fu=0, fv=0, fu2=0 , fuv=0 , fv2=0;
  f.Eval( u,  v, OptionEvalSecondDeriv, &val, &fu, &fv, &fu2, &fuv, &fv2 );

  if (fv2 != (-c*cos(u)*cos(v)) )                   return (5);


  // ------------ Simultaneously evaluates the tangents at grid of points
  // 
  double umin       = 0.;
  double umax       = CATPIBY4;
  double vmin       = 0.;
  double vmax       = CATPIBY2;
  double aMinMax[4] = {umin, umax, vmin, vmax}; 
  CATMathIntervalND domain(2,aMinMax);

  CATLONG32 nb[2]    = {10,20};         // number of point in each direction of the grid
  CATLONG32 tot      = nb[0]*nb[1];
  double * aVal = new double [tot];
  double * aFu  = new double [tot];
  double * aFv  = new double [tot];
  // The NULL arguments corresponds to the arrays of the second derivatives:
  // we do not want to recover them in this sample. 
  f.Eval(domain, nb, OptionEval+OptionEvalFirstDeriv , aVal, aFu, aFv , NULL, NULL , NULL);

  // ------------ Checks the evaluation of uij, vij, 0 <= i <= nb[0],  0 <= j <= nb[1]
  //              the corresponding value is aVal[nb[1]*i+j]

  int i=2, j=14;
  double uij = umin + (umax-umin)*(i)/(nb[0]-1);
  double vij = vmin + (vmax-vmin)*(j)/(nb[1]-1);
  cout << aVal[nb[1]*i+j] << ", "<< a*uij + b*vij + c*cos(uij)*cos(vij) +d << endl;
  if ( CATFabs(aVal[nb[1]*i+j] - (a*uij + b*vij + c*cos(uij)*cos(vij) +d)) > 1.e-12 ) return (6);

  delete [] aVal;
  aVal = NULL;
  delete [] aFu;
  aFu = NULL;
  delete [] aFv;
  aFv = NULL;

  return (rc);
}


