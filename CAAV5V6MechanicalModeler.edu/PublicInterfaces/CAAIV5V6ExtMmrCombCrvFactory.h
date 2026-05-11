// COPYRIGHT DASSAULT SYSTEMES 2012

#ifndef CAAIV5V6ExtMmrCombCrvFactory_H
#define CAAIV5V6ExtMmrCombCrvFactory_H

// Local Framework
#include "CAAV5V6ExtMmrCombinedCurve.h"

// System Framework
#include "CATBaseUnknown.h"

class CAAIV5V6ExtMmrCombinedCurve;

extern ExportedByCAAV5V6ExtMmrCombinedCurve IID IID_CAAIV5V6ExtMmrCombCrvFactory ;

/**
 * Interface to create a Combined Curve.
 * 
 * Role : use this interface to create a Combined Curve.
 *        A Combined Curve is the intersection of two extruded surfaces.
 *        Each of the two surfaces is buildt using a curve (profile) and a direction (of extrusion).
 *        Consequently, a Combined Curve has two input curves and two input directions.
 */

class ExportedByCAAV5V6ExtMmrCombinedCurve CAAIV5V6ExtMmrCombCrvFactory: public CATBaseUnknown
{
  CATDeclareInterface;

  public:

   /**
   * Creates a Combined Curve.
   * param ipCurve1       : the first input curve.
   * param ipDirection1   : the first input direction.
   * param ipCurve2       : the second input curve.
   * param ipDirection2   : the second input direction.
   * param opCombinedCurve : the resulting Combined Curve.
   *
   * returns the result of the creation.
   *     Legal values : S_OK   the creation of the Combined Curve succeeded.
   *                    E_FAIL the creation of the Combined Curve failed.
   */
      virtual HRESULT CreateCombinedCurve(CATBaseUnknown  *ipCurve1,
                                          CATBaseUnknown  *ipDirection1,
                                          CATBaseUnknown  *ipCurve2,
                                          CATBaseUnknown  *ipDirection2,
                                          CAAIV5V6ExtMmrCombinedCurve *& opCombinedCurve) = 0;

};

CATDeclareHandler(CAAIV5V6ExtMmrCombCrvFactory, CATBaseUnknown);

#endif
