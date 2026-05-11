// COPYRIGHT DASSAULT SYSTEMES 2012

#ifndef CAAIV5V6ExtMmrMultiMeasureFactory_H
#define CAAIV5V6ExtMmrMultiMeasureFactory_H

// Local Framework
#include "CAAV5V6ExtMmrMultiMeasure.h"

// System Framework
#include "CATBaseUnknown.h"


extern ExportedByCAAV5V6ExtMmrMultiMeasure IID IID_CAAIV5V6ExtMmrMultiMeasureFactory ;

/**
 * Interface to create CAAV5V6ExtMmrMultiMeasure and  CAAV5V6ExtMmrMeasureSet.
 * 
 * Role : use this interface to instantiate and create a CAAV5V6ExtMmrMultiMeasure or a CAAV5V6ExtMmrMeasureSet.
 *        A CAAV5V6ExtMmrMultiMeasure is a non geometrical feature which compute length, area and volume of the pointed object, if available.
 *        This example feature is to illustrate MechanicalElement StartUp.
 *        As MmrMultiMeasure is a non geometricalElement deriving from MechanicalElement, it has to be aggregated under a specific set.
 *        This set, deriving from MechanicalSet and dedicated to aggregated MechanicalElements subtypes is named MmrMeasureSet.
 */

class ExportedByCAAV5V6ExtMmrMultiMeasure CAAIV5V6ExtMmrMultiMeasureFactory: public CATBaseUnknown
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
                                         CATBaseUnknown *&opMultiMeasureInstance ) = 0 ;
   /**
   * Creates a MmrMeasureSet to aggregate cleanly MmrMultiMeasure instances.
   * param opMeasureSetInstance       : the resulting MmrMeasureSet created.
   *
   * returns the result of the creation.
   *     Legal values : S_OK   the creation of the MmrMeasureSet succeeded.
   *                    E_FAIL the creation of the MmrMeasureSet failed.
   */
   virtual HRESULT CreateMmrMeasureSet(CATBaseUnknown *&opMeasureSetInstance) = 0 ;
};

CATDeclareHandler(CAAIV5V6ExtMmrMultiMeasureFactory , CATBaseUnknown);

#endif
