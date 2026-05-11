// COPYRIGHT DASSAULT SYSTEMES 2012
#ifndef CAAIV5V6ExtMmrCombinedCurve_H
#define CAAIV5V6ExtMmrCombinedCurve_H

// Local Framework
#include "CAAV5V6ExtMmrCombinedCurve.h"

// System Framework
#include "CATBaseUnknown.h"

extern ExportedByCAAV5V6ExtMmrCombinedCurve IID IID_CAAIV5V6ExtMmrCombinedCurve ;

/**
 * Interface to manage Combined Curves.
 *  
 *  Role : use this interface to get / set the input of a Combined Curve. 
 *         A Combined Curve is the intersection of two extruded surfaces.
 *         Each of the two surfaces is buildt using a curve (profile) and a direction (of extrusion).
 *         Consequently, a Combined Curve has two input curves and two input directions.
 */

class ExportedByCAAV5V6ExtMmrCombinedCurve CAAIV5V6ExtMmrCombinedCurve: public CATBaseUnknown
{
  CATDeclareInterface;

  public:

   /**
   * Sets one of the input curves of the Combined Curve.
   *
   * param iNum    : the index of the input curve.
   *                 Legal values : 1 for the first curve.
   *                                2 for the second curve.
   * param ipCurve : the input curve
   *
   * returns       : S_OK  the call succeeded.
   *               : E_FAIL  the call failed.
   */
   virtual HRESULT SetCurve(int iNum , CATBaseUnknown *ipCurve) = 0 ;


  /**
   * Gets one of the input Curves of the Combined Curve.
   *
   * param iNum    : the index of the input curve.
   *                 Legal values : 1 for the first curve.
   *                                2 for the second curve.
   * param opCurve : the intput curve
   *
   * returns       : S_OK  the call succeeded.
   *               : E_FAIL  the call failed.
   */
   virtual HRESULT GetCurve(int iNum, CATBaseUnknown *&opCurve) = 0 ;

  /**
   * Sets one of the input directions of the Combined Curve.
   *
   * param iNum        : the index of the input curve.
   *                     Legal values : 1 for the first curve.
   *                                    2 for the second curve.
   * param ipDirection : the input direction
   *
   * returns           : S_OK  the call succeeded.
   *                   : E_FAIL  the call failed.
   */
  virtual HRESULT SetDirection (int iNum, CATBaseUnknown *ipDirection) = 0 ;
  

   /**
   * Gets one of the input directions of the Combined Curve.
   *
   * param iNum        : the index of the input curve.
   *                     Legal values : 1 for the first curve.
   *                                    2 for the second curve.
   * param opDirection : the input direction
   *
   * returns           : S_OK  the call succeeded.
   *                   : E_FAIL  the call failed.
   */
  virtual HRESULT GetDirection (int iNum , CATBaseUnknown *&opDirection) = 0 ;


};

CATDeclareHandler(CAAIV5V6ExtMmrCombinedCurve , CATBaseUnknown);

#endif
