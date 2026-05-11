// COPYRIGHT DASSAULT SYSTEMES 2012

#ifndef CAAIV5V6ExtMmrMultiMeasure_H
#define CAAIV5V6ExtMmrMultiMeasure_H

// Local Framework
#include "CAAV5V6ExtMmrMultiMeasure.h"

// System Framework
#include "CATBaseUnknown.h"

class CATICkeParm_var;

extern ExportedByCAAV5V6ExtMmrMultiMeasure IID IID_CAAIV5V6ExtMmrMultiMeasure ;

/**
* Interface to manage CAAV5V6ExtMmrMultiMeasure.
*  
*  Role : use this interface to get / set the input of the CAAV5V6ExtMmrMultiMeasure. 
*         A CAAV5V6ExtMmrMultiMeasure is an non geometrical feature derivated from MechanicalElement.
*         It computes the wet area of pointed feature.
*         Consequently, a CAAV5V6ExtMmrMultiMeasure has only one input: The "Geometrical Feature" pointed.
*/

class ExportedByCAAV5V6ExtMmrMultiMeasure CAAIV5V6ExtMmrMultiMeasure: public CATBaseUnknown
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
  virtual HRESULT GetGeomFeature (CATBaseUnknown *& oGeomFeature ) = 0;

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

CATDeclareHandler(CAAIV5V6ExtMmrMultiMeasure , CATBaseUnknown);

#endif
