// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
//  Utilities to be shared among all modules in CAASchPlatformModeler.edu
//  Specifically in the area of user defined "start-up" features' handling.
//  
//=============================================================================

#ifndef CAASchAppFeatureSUServices_h
#define CAASchAppFeatureSUServices_h

#include "CAASchAppUtilities.h"
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

class CATIContainer;
class CATISpecObject;

class ExportedByCAASchAppUtilities CAASchAppFeatureSUServices :  public CATBaseUnknown
{

  public:
	CAASchAppFeatureSUServices();
	virtual ~CAASchAppFeatureSUServices();

	//-------------------------------------------------------------------------
	// iUFeatDocName - name of .feat file to be loaded
	// iCont - pointer to container into which the file should be loaded
	//-------------------------------------------------------------------------
    HRESULT FindStartUpClass (
      CATUnicodeString iUFeatDocName, CATIContainer *iCont, 
      CATISpecObject **oFeatureSU);
    
};

#endif

