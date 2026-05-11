// COPYRIGHT DASSAULT SYSTEMES 2000

#ifndef CAAIMmrCombCrvFactory_H
#define CAAIMmrCombCrvFactory_H

// Local Framework
#include "CAAMmrCombinedCurve.h"

// System Framework
#include "CATBaseUnknown.h"

class CATISpecObject;

extern ExportedByCAAMmrCombinedCurve IID IID_CAAIMmrCombCrvFactory ;

/**
 * Interface to create a Combined Curve.
 * 
 * Role : use this interface to create a Combined Curve.
 *        A Combined Curve is the intersection of two extruded surfaces.
 *        Each of the two surfaces is buildt using a curve (profile) and a direction (of extrusion).
 *        Consequently, a Combined Curve has two input curves and two input directions.
 */

class ExportedByCAAMmrCombinedCurve CAAIMmrCombCrvFactory: public CATBaseUnknown
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
      virtual HRESULT CreateCombinedCurve (  CATISpecObject *ipCurve1 ,
                                            CATISpecObject *ipDirection1 ,
                                            CATISpecObject *ipCurve2 ,
                                            CATISpecObject *ipDirection2 ,
                                            CATISpecObject **opCombinedCurve ) = 0 ;

};

#endif
