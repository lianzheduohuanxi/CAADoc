// COPYRIGHT DASSAULT SYSTEMES 2012

#ifndef CAAIV5V6ExtMmrCCDataExtension_H
#define CAAIV5V6EXtMmrCCDataExtension_H

// Local Framework
#include "CAAV5V6ExtMmrCCDataExtension.h"

// System Framework
#include "CATBaseUnknown.h"

class CATICkeParm_var;

extern ExportedByCAAV5V6ExtMmrCCDataExtension IID IID_CAAIV5V6ExtMmrCCDataExtension ;

/**
* Interface to manage CAAV5V6ExtMmrCCDataExtension, data extension of a CombinedCurve.
*  
*  Role : use this interface to get / set the input of the CAAV5V6ExtMmrCCDataExtension. 
*         A CAAV5V6ExtMmrCCDataExtension is an Extension which computes the length of a geometrical element.
*         Consequently, it has only one input: a geomerical element.
*/

class ExportedByCAAV5V6ExtMmrCCDataExtension CAAIV5V6ExtMmrCCDataExtension: public CATBaseUnknown
{
  CATDeclareInterface;

public:

  /**
  * Sets the base feature to extend.
  *
  * INPUT param iGeomFeature  : The Feature to Extend.
  *
  * returns       : S_OK  the call succeeded.
  *               : E_FAIL  the call failed.
  */
  virtual HRESULT SetGeomFeature (CATBaseUnknown * ipGeomFeature ) = 0;

  /**
  * Gets the base feature extended
  *
  * OUTPUT param ioGeomFeature : The Feature Extended.
  *
  * returns       : S_OK  the call succeeded.
  *               : E_FAIL  the call failed.
  */
  virtual HRESULT GetGeomFeature (CATBaseUnknown*& opGeomFeature ) = 0;

  /**
  * Aggregegate the Parameter defining the result of Computing Length
  *
  * INPUT param iParmToAggregate : The Parm to aggregate.
  *
  * returns       : S_OK  the call succeeded.
  *               : E_FAIL  the call failed.
  */
  virtual HRESULT AggregateParam (CATICkeParm_var ispParmToAggregate) = 0;
    
  /**
  * Retrieves the valuated parameter
  *
  * OUTPUT param ioValuatedParm: the valuated parameter.
  *
  * returns       : S_OK  the call succeeded.
  *               : E_FAIL  the call failed.
  */
  virtual HRESULT GetValuatedParam(CATICkeParm_var& iospValuatedParm) = 0;

};

CATDeclareHandler(CAAIV5V6ExtMmrCCDataExtension , CATBaseUnknown);

#endif
