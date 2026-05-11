/**
 * @quickreview nd1 12:05:28 IR0601911V5-6R2013:Code modif since CATICatalog and CATCatalogFactoryServices
                             APIs are deprecated. CATOsmSUHandler APIs used instead.
 * @quickreview vso jsk 08:02:07
 */
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
//  Utilities to be shared among all modules in CAASchPlatformModeler.edu
//  Specifically in the area of user defined "start-up" features' handling.
//
//=============================================================================
#include <iostream.h>
#include "CAASchAppFeatureSUServices.h"
#include "CAASchAppClassNames.h"

// System
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

// ObjectModelerBase
#include "CATIContainer.h"

// ObjectSpecsModeler
// Deprecated APIs in CXR23: CATCatalogFactoryServices.h and CATICatalog.h
#include "CATOsmSUHandler.h" // replacement for CATCatalogFactoryServices.h and CATICatalog.h
#include "CATISpecObject.h"
#include "CATISpecAttribute.h"

//=============================================================================
//  Constructor
//=============================================================================
CAASchAppFeatureSUServices::CAASchAppFeatureSUServices ()
{
}

//=============================================================================
//  Destructor
//=============================================================================
CAASchAppFeatureSUServices::~CAASchAppFeatureSUServices ()
{
}

//=============================================================================
//   FindStartUpClass
//=============================================================================
HRESULT CAASchAppFeatureSUServices::FindStartUpClass (
  CATUnicodeString iuParentType, CATIContainer *iCont, 
  CATISpecObject **oFeatureSU)
{	
  HRESULT RC = E_FAIL;

  // Code using CATICatalog and CATCatalogFactoryServices.h APIs is removed since
  // APIs are deprecated with effect from CXR23. 
  // Suggested code for AccessCatalog / RetreiveSU pattern -> Use of CATOsmSUHandler.
  // code add start.
   CATUnicodeString  uStorageCatalogName(SCHEDUAppFeat_Name);
   CATUnicodeString  uClientId(SCHEDUAppClientID);
   CATUnicodeString  uFeatureStartupType(iuParentType); // feature name
   CATOsmSUHandler   SCHE_SUHandler(uFeatureStartupType, uClientId, uStorageCatalogName);
   if (SUCCEEDED(SCHE_SUHandler.IsValid()))
   {
     CATISpecObject_var spSchSU = NULL_var;
     RC = SCHE_SUHandler.RetrieveSU(spSchSU);     
     if (SUCCEEDED(RC))
     {
       RC = spSchSU->QueryInterface(IID_CATISpecObject,(void**)oFeatureSU);
     } 
   }// code add end

  if (NULL != *oFeatureSU)
  {
     cout << iuParentType.ConvertToChar() << " Found" << endl;
	   RC = S_OK;
  }
  return RC;
}





