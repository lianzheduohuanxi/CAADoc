// COPYRIGHT DASSAULT SYSTEMES  2001+
//=============================================================================
//
//CAASchAppInternalError - error class for CAASchPlatformModeler.edu framework
//
#ifndef CAASchAppInternalError_H
#define CAASchAppInternalError_H

#include "CATInternalError.h"
#include "CAASchAppBase.h"

#define CAASchAppInternalErrorFile "CATSchPlatformModelerEdu"

class ExportedByCAASchAppBase CAASchAppInternalError : public CATInternalError
{
	public:

  enum 
  { 
     Internal_CannotFindCurrentDoc,
     Internal_CannotFindApplicationCont,
     Internal_FailToCreateCompRef,
     Internal_CannotFindProductRoot,
     Internal_FailToCreateCompInst,
     Internal_CannotFindAppReference,
     Internal_NotAFeature,
     Internal_FailToCreateConnector,
     Internal_FailToCreateConnection,
     Internal_NoValidConnectorType,
     Internal_NoValidConnectionType,
     Internal_InvalidConnectorType,
     Internal_InvalidConnectionType
  };

  CATDeclareErrorClass(CAASchAppInternalError, CATInternalError)
};

#endif

