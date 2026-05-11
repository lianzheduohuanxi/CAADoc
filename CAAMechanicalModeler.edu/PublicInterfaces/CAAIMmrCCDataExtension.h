// COPYRIGHT DASSAULT SYSTEMES 2007

#ifndef CAAIMmrCCDataExtension_H
#define CAAIMmrCCDataExtension_H

// Local Framework
#include "CAAMmrCCDataExtension.h"

// System Framework
#include "CATBaseUnknown.h"

class CATISpecObject;
class CATICkeParm_var;

extern ExportedByCAAMmrCCDataExtension IID IID_CAAIMmrCCDataExtension ;

/**
* Interface to manage MmrCCDataExtension.
*  
*  Role : use this interface to get / set the input of the MmrCCDataExtension. 
*         A MmrCCDataExtension is an Extension which compute the length of a Combined Curve
*         Consequently, a MmrCCDataExtension has only one input: The Combined Curve.
*/

class ExportedByCAAMmrCCDataExtension CAAIMmrCCDataExtension: public CATBaseUnknown
{
  CATDeclareInterface;

public:

  /**
  * Sets the base feature to extend
  *
  * INPUT param iGeomFeature  : The Feature to Extend.
  *
  * returns       : S_OK  the call succeeded.
  *               : E_FAIL  the call failed.
  */
  virtual HRESULT SetGeomFeature (const CATBaseUnknown * ipGeomFeature ) = 0;

  /**
  * Gets the base feature extended
  *
  * OUTPUT param ioGeomFeature : The Feature Extended.
  *
  * returns       : S_OK  the call succeeded.
  *               : E_FAIL  the call failed.
  */
  virtual HRESULT GetGeomFeature (CATISpecObject** ioGeomFeature ) = 0;

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

#endif
