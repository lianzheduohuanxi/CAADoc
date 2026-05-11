// COPYRIGHT DASSAULT SYSTEMES 2000
#ifndef CAAIMmrCombinedCurve_H
#define CAAIMmrCombinedCurve_H

// Local Framework
#include "CAAMmrCombinedCurve.h"

// System Framework
#include "CATBaseUnknown.h"

class CATISpecObject;

extern ExportedByCAAMmrCombinedCurve IID IID_CAAIMmrCombinedCurve ;

/**
 * Interface to manage Combined Curves.
 *  
 *  Role : use this interface to get / set the input of a Combined Curve. 
 *         A Combined Curve is the intersection of two extruded surfaces.
 *         Each of the two surfaces is buildt using a curve (profile) and a direction (of extrusion).
 *         Consequently, a Combined Curve has two input curves and two input directions.
 */

class ExportedByCAAMmrCombinedCurve CAAIMmrCombinedCurve: public CATBaseUnknown
{
  CATDeclareInterface;

  public:

   /**
   * Sets one of the input curve of the Combined Curve.
   *
   * param iNum    : the index of the input curve.
   *                 Legal values : 1 for the first curve.
   *                                2 for the second curve.
   * param ipCurve : the input curve
   *
   * returns       : S_OK  the call succeeded.
   *               : E_FAIL  the call failed.
   */
   virtual HRESULT SetCurve ( int iNum ,
                              CATISpecObject *ipCurve ) = 0 ;


  /**
   * Gets one of the input curve of the Combined Curve.
   *
   * param iNum    : the index of the input curve.
   *                 Legal values : 1 for the first curve.
   *                                2 for the second curve.
   * param ipCurve : the input curve
   *
   * returns       : S_OK  the call succeeded.
   *               : E_FAIL  the call failed.
   */
   virtual HRESULT GetCurve ( int iNum ,
                              CATISpecObject **opCurve ) = 0 ;

  /**
   * Sets one of the input direction of the Combined Curve.
   *
   * param iNum        : the index of the input curve.
   *                     Legal values : 1 for the first curve.
   *                                2 for the second curve.
   * param ipDirection : the input direction
   *
   * returns           : S_OK  the call succeeded.
   *                   : E_FAIL  the call failed.
   */
  virtual HRESULT SetDirection ( int iNum , 
                                 CATISpecObject *ipDirection ) = 0 ;
  

   /**
   * Gets one of the input direction of the Combined Curve.
   *
   * param iNum        : the index of the input curve.
   *                     Legal values : 1 for the first curve.
   *                                2 for the second curve.
   * param opDirection : the input direction
   *
   * returns           : S_OK  the call succeeded.
   *                   : E_FAIL  the call failed.
   */
  virtual HRESULT GetDirection ( int iNum ,
                                 CATISpecObject **opDirection ) = 0 ;


};

#endif
