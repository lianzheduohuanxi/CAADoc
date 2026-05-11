#ifndef CAAAmtForeignFctXY_H
#define CAAAmtForeignFctXY_H
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
#include "CAAAmtForeignFct.h"               // For Windows - ExportedBy 
#include "CATMathFunctionXY.h"              // Base class for foreign function

//-----------------------------------------------------------------
/**
 * Function representing one of the coordinate  of a
 * CAAForeignSurfaceData equation (the eggs box).
 *  <pre> F: R^2   -> R
 *        (u,v) -> F(u,v)=_a*u + _b*v + _c * cos(u)*cos(v) + _Origin
 * </pre>
 */ 
class ExportedByCAAAmtForeignFct CAAAmtForeignFctXY : public CATMathFunctionXY
{

 public:
  //-----------------------------------------------------------------
  // Constructors
  //-----------------------------------------------------------------
/**
 * Constructs a CAAAmtForeignFctXY.
 * <br>The input parameters define the following function:
 *  <pre> F: R^2   -> R
 *        (u,v) -> F(u,v)= iA*u + iB*v + iC * cos(u)*cos(v) + iOrigin
 * </pre>
 */
  
  CAAAmtForeignFctXY(const double iA,
                     const double iB,
                     const double iC,
                     const double iOrigin);
                                      
  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------
/**
 * Returns "CAAAmtForeignFctXY".
 */
  CATMathClassId IsA() const;


/**
 * Returns <tt>TRUE</tt> if <tt>this</tt> CAAAmtForeignFctXY is a kind of <tt>iClassId</tt>,
 * <tt>FALSE</tt> otherwise.
 */
  CATBoolean IsAKindOf(const CATMathClassId iClassId) const;


/**
 * Returns <tt>TRUE</tt> if the option is available for <tt>this</tt> CAAAmtForeignFctXY,
 * <tt>FALSE</tt> otherwise..
 * @param iOption
 * The type of evalution you want.
 * <dl> <dt>OptionEval   </dt>  <dd>  evaluation of the function
 * <dt>OptionEvalFirstDeriv   </dt>  <dd>  evaluation of the first derivatives of the function
 * <dt>OptionEvalSecondDeriv</dt>  <dd>  evaluation of the second derivatives of the function
 * <dt>OptionEvalThirdDeriv</dt>  <dd>  evaluation of the third derivatives of the function
 * </dl>
 */
  CATBoolean IsOption(const CATMathOption iOption) const;
   
  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------
   
/** 
 * Evaluates <tt>this</tt> CATMathFunctionXY.
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @return
 * The result of the evaluation.
 */
  double Eval(const double & iX, const double & iY) const;

 /** 
 * Evaluates the first partial derivative wrt the first variable of <tt>this</tt> CATMathFunctionXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @return
 * The value of the first partial derivative wrt the first variable.
 */
  double EvalFirstDerivX(const double & iX, const double & iY) const;

 /** 
 * Evaluates the first partial derivative wrt the second variable of <tt>this</tt> CATMathFunctionXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @return
 * The value of the first partial derivative wrt the second variable.
 */
  double EvalFirstDerivY(const double & iX, const double & iY) const;
 
 /** 
 * Evaluates the second partial derivative of <tt>this</tt> CATMathFunctionXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @return
 * The value of the second partial derivative.
 */
  double EvalSecondDerivX2(const double & iX, const double & iY) const;

  /** 
 * Evaluates the second partial derivative of <tt>this</tt> CATMathFunctionXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @return
 * The value of the second partial derivative.
 */
  double EvalSecondDerivXY(const double & iX, const double & iY) const;

   /** 
 * Evaluates the second partial derivative of <tt>this</tt> CATMathFunctionXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @return
 * The value of the second partial derivative.
 */
  double EvalSecondDerivY2(const double & iX, const double & iY) const;

/**
 * Simultaneously evaluates <tt>this</tt> CATMathFunctionXY or/and its partial derivatives.
 * <br><b>Precondition</b>:The output arrays
 * must have been previously allocated if you asked for the corresponding evaluation.
 * @param iOptions
 * The type of evalution.
 * <br><b>Legal values</b>:
 * <dl> <dt>OptionEval   </dt>  <dd>  evaluation of the function
 * <dt>OptionEvalFirstDeriv   </dt>  <dd>  evaluation of the first derivatives of the function
 * <dt>OptionEvalSecondDeriv</dt>  <dd>  evaluation of the second derivatives of the function
 * </dl>
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param ioF
 * A pointer to the value of <tt>this</tt> CATMathFunctionXY.
 * @param ioFx
 * A pointer to the first partial derivative of <tt>this</tt> CATMathFunctionXY. 
 * @param ioFy
 * A pointer to the first partial derivative of <tt>this</tt> CATMathFunctionXY. 
 * @param ioFx2
 * A pointer to the second partial derivative of <tt>this</tt> CATMathFunctionXY.
 * @param ioFxy
 * A pointer to the second partial derivative of <tt>this</tt> CATMathFunctionXY.
 * @param ioFy2
 * A pointer to the second partial derivative of <tt>this</tt> CATMathFunctionXY.
 */
  void Eval(const double iX, const double iY, 
		    const CATMathOption iOptions,
		    double * ioF,
		    double * ioFx =NULL, double * ioFy=NULL,
		    double * ioFx2=NULL, double * ioFxy=NULL, double *ioFy2=NULL) const;
   
 /**
 * Simultaneously evaluates <tt>this</tt> CATMathFunctionXY or/and its partial derivatives 
 * on a regular grid of points.
 * <br><b>Precondition</b>: The output arrays
 * must have been previously allocated if you asked for the corresponding evaluation.
 * <tt>oF[Ny*i+j]</tt> contains the evaluation of <tt>this</tt> at <tt>(x_i,y_j)</tt>.
 * @param iDomain
 * The 2D-interval of definition of the grid <tt>[xStart,xEnd] x [yStart,yEnd]</tt>. 
 * @param iNbPoints
 * The array of 2 longs, stating the number of points of the grid in each direction <tt>x</tt>
 * and <tt>y</tt>. If <tt>iNbPoints[0]=1</tt> and <tt>iNbPoints[1]=1</tt>, there is only one
 * evaluation made at the parameter <tt>(xStart,xStart)</tt>
 * @param iOptions
 * The type of evalution.
 * <br><b>Legal values</b>:
 * <dl> <dt>OptionEval   </dt>  <dd>  evaluation of the function
 * <dt>OptionEvalFirstDeriv   </dt>  <dd>  evaluation of the first derivatives of the function
 * <dt>OptionEvalSecondDeriv</dt>  <dd>  evaluation of the second derivatives of the function
 * </dl>
 * @param ioF
 * The array of the evaluations of <tt>this</tt> CATMathFunctionXY.
 * @param ioFx
 * The array of the first partial derivative of <tt>this</tt> CATMathFunctionXY at the grid points. 
 * @param ioFy
 * The array of the first partial derivative of <tt>this</tt> CATMathFunctionXY at the grid points. 
 * @param ioFx2
 * The array of the second partial derivative of <tt>this</tt> CATMathFunctionXY at the grid points.
 * @param ioFxy
 * The array of the second partial derivative of <tt>this</tt> CATMathFunctionXY at the grid points.
 * @param ioFy2
 * The array of the second partial derivative of <tt>this</tt> CATMathFunctionXY at the grid points.
 */ 
  void Eval(const CATMathIntervalND & iDomain, const CATLONG32 * iNbPoints,
		    const CATMathOption iOptions,
		    double * ioF,
		    double * ioFx =NULL, double * ioFy=NULL,
		    double * ioFx2=NULL, double * ioFxy=NULL, double *ioFy2=NULL) const;

   

private:
  double _a, _b, _c, _Origin;
};

#endif


