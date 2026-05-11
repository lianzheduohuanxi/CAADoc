// COPYRIGHT DASSAULT SYSTEMES 2007

#ifndef CAAIMmrMultiMeasure_H
#define CAAIMmrMultiMeasure_H

// Local Framework
#include "CAAMmrMultiMeasureAndMeasureSet.h"

// System Framework
#include "CATBaseUnknown.h"

class CATISpecObject;
class CATICkeParm_var;

extern ExportedByCAAMmrMultiMeasureAndMeasureSet IID IID_CAAIMmrMultiMeasure ;

/**
* Interface to manage MmrMultiMeasure.
*  
*  Role : use this interface to get / set the input of the MmrMultiMeasure. 
*         A MmrMultiMeasure is an non geometrical feature derivated from MechanicalElement.
*         It computes the wet area of pointed feature.
*         Consequently, a MmrMultiMeasure has only one input: The "Geometrical Feature" pointed.
*/

class ExportedByCAAMmrMultiMeasureAndMeasureSet CAAIMmrMultiMeasure: public CATBaseUnknown
{
  CATDeclareInterface;

public:

  /**
  * Sets the feature to measure
  *
  * INPUT param ipGeomFeature : The Feature to measure.
  *
  * returns       : S_OK  the call succeeded i.e if the input feature is set correctly.
  *               : E_FAIL  the call failed.
  */
  virtual HRESULT SetInputGeomFeature (CATBaseUnknown * ipGeomFeature ) = 0;

  /**
  * Gets the base feature to measure
  *
  * OUTPUT param ioGeomFeature : The Feature to measure.
  *
  * returns       : S_OK  the call succeeded.
  *               : E_FAIL  the call failed.
  */
  virtual HRESULT GetGeomFeature (CATISpecObject** ioGeomFeature ) = 0;

  /**
  * Gets the length parameter.
  */
  virtual HRESULT GetLengthParameter (CATICkeParm_var &oLengthParm) = 0;
   /**
  * Gets the wet aera parameter.
  */
  virtual HRESULT GetWetAreaParameter (CATICkeParm_var &oWetAreaParm) = 0;
   /**
  * Gets the volume parameter.
  */
  virtual HRESULT GetVolumeParameter (CATICkeParm_var &oVolumeParm) = 0;

};

#endif
