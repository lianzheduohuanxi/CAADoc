// COPYRIGHT DASSAULT SYSTEMES 2007

#ifndef CAAIMmrMultiMeasureAndMeasureSetFactory_H
#define CAAIMmrMultiMeasureAndMeasureSetFactory_H

// Local Framework
#include "CAAMmrMultiMeasureAndMeasureSet.h"

// System Framework
#include "CATBaseUnknown.h"

class CATISpecObject;

extern ExportedByCAAMmrMultiMeasureAndMeasureSet IID IID_CAAIMmrMultiMeasureAndMeasureSetFactory ;

/**
 * Interface to create MmrMultiMeasure and  MmrMeasureSet.
 * 
 * Role : use this interface to instantiate and create a MmrMultiMeasure or a MmrMeasureSet.
 *        A MmrMultiMeasure is a non geometrical feature which compute length, area and volume of the pointed object, if available.
 *        This example feature is to promote MechanicalElement StartUp.
 *        As MmrMultiMeasure is a non geometricalElement deriving from MechanicalElement, it has to be aggregated under a specific set.
 *        This set, deriving from MechanicalSet and dedicated to aggregated MechanicalElements subtypes is named MmrMeasureSet.
 */

class ExportedByCAAMmrMultiMeasureAndMeasureSet CAAIMmrMultiMeasureAndMeasureSetFactory: public CATBaseUnknown
{
  CATDeclareInterface;

  public:

   /**
   * Creates a MmrMultiMeasure.
   * param ipGeometricalElementToMesure : the input of MmrMultiMeasure - A geometrical Element to measure.
   * param opMultiMeasureInstance       : the resulting MmrMultiMeasure created.
   *
   * returns the result of the creation.
   *     Legal values : S_OK   the creation of the MmrMultiMeasure succeeded.
   *                    E_FAIL the creation of the MmrMultiMeasure failed.
   */
      virtual HRESULT CreateMmrMultiMeasure(CATBaseUnknown *ipGeometricalElementToMesure ,
                                            CATISpecObject **opMultiMeasureInstance ) = 0 ;
   /**
   * Creates a MmrMeasureSet to aggregate cleanly MmrMultiMeasure instances.
   * param opMeasureSetInstance       : the resulting MmrMeasureSet created.
   *
   * returns the result of the creation.
   *     Legal values : S_OK   the creation of the MmrMeasureSet succeeded.
   *                    E_FAIL the creation of the MmrMeasureSet failed.
   */
      virtual HRESULT CreateMmrMeasureSet(CATISpecObject **opMeasureSetInstance) = 0 ;
};

#endif
