// COPYRIGHT DASSAULT SYSTEMES 2007
//=================================================================================================
//
// CAAEMmrDataExtensionContInit.cpp
// Provide implementation to interface
//    CAAEMmrDataExtensionContInit - i.e. CATIInit .... Initialization of Applicative Container
//
//=================================================================================================
// Local Framework
#include "CAAEMmrDataExtensionContInit.h"
#include "CAAMmrUpdateProvForExtCont.h"
#include "CAAMmrNavigateProvForExtCont.h"
#include "CAAMmrParmProvForExtCont.h"
#include "CAAMmrVisuProvForExtCont.h"

// ObjectSpecsModeler Framework
#include "CATIProviders.h"
#include "CATOsmExtensionServices.h"
#include "CATIClientContainer.h"
#include "CATISpecObject.h"
#include "CATIOsmExtension.h"

#include "CATIUpdateProvider.h"
#include "CATINavigateProvider.h"
#include "CATIParmProvider.h"

// ObjectModelerBase Framework
#include "CATIContainer.h"
#include "CATILinkableObject.h"
#include "CATDocument.h"

//MecModInterface Framework
#include "CATIContainerOfDocument.h"

//Visu Framework
#include "CATIModelEvents.h"


CATImplementClass(CAAEMmrDataExtensionContInit,DataExtension,CATInit,CAAMmrDataExtensionCont);
CATImplementBOA(CATInit,CAAEMmrDataExtensionContInit);

CAAEMmrDataExtensionContInit::CAAEMmrDataExtensionContInit()
{
}
CAAEMmrDataExtensionContInit::~CAAEMmrDataExtensionContInit()
{
}
// CATInit interface methods
void CAAEMmrDataExtensionContInit::Init (CATBoolean  iDestroyExistingData )
{
  //===============================================================================================
  // -1-a- Retrieves a CATIContainer interface pointer on this (CATPrtCont)
  //===============================================================================================
  CATIContainer *pContainerOnThis = NULL;
  HRESULT rc = QueryInterface( IID_CATIContainer , ( void**) &pContainerOnThis );
  if ( FAILED(rc) || ( NULL==pContainerOnThis) )
  {
    return;
  }
  //===============================================================================================
  // -1-b- Retrieves a pointer to the CATDocument to which the container belongs
  //===============================================================================================
  CATILinkableObject* pIlink = NULL;
  rc = pContainerOnThis -> QueryInterface( IID_CATILinkableObject, ( void**) &pIlink );

  if(SUCCEEDED(rc) && pIlink != NULL)
  {
    CATDocument * pDoc = pIlink -> GetDocument();
    if (pDoc != NULL)
    {
      // Retrieves a CATIProviders pointer on the current document
      CATIProviders *piProvidersManager = NULL;
      rc = pDoc -> QueryInterface(IID_CATIProviders,
                                      (void**) &piProvidersManager);
      if (SUCCEEDED(rc))
      {
        //Adds all providers we need to extend Update, f(x), NavigateObject, Visu Mecanism to Applicative Container.

        //Adds CAAMmrUpdateProvForExtCont
        CAAMmrUpdateProvForExtCont* pUpdateProvider = new CAAMmrUpdateProvForExtCont();
        piProvidersManager->AddProvider(CATIUpdateProvider::ClassId(), pUpdateProvider);
        pUpdateProvider -> Release();
        pUpdateProvider = NULL;
        
        //Adds CAAMmrParmProvForExtCont
        CAAMmrParmProvForExtCont* pParmProvider = new CAAMmrParmProvForExtCont();
        piProvidersManager->AddProvider(CATIParmProvider::ClassId(), pParmProvider);
        pParmProvider -> Release();
        pParmProvider = NULL;
      
        //Adds CAAMmrNavigateProvForExtCont
        CAAMmrNavigateProvForExtCont* pNavigateProvider = new CAAMmrNavigateProvForExtCont();
        piProvidersManager->AddProvider(CATINavigateProvider::ClassId(), pNavigateProvider);
        pNavigateProvider -> Release();
        pNavigateProvider = NULL;

        //Adds CAAMmrVisuProvForExtCont
        CAAMmrVisuProvForExtCont* pVisuProvider = new CAAMmrVisuProvForExtCont();
        piProvidersManager->AddProvider(CATI3DVisuProvider::ClassId(), pVisuProvider);
        pVisuProvider -> Release();
        pVisuProvider = NULL;

        piProvidersManager->Release();
        piProvidersManager = NULL;
      }
    }

    pIlink -> Release();
    pIlink = NULL;
  }

  pContainerOnThis -> Release();
  pContainerOnThis = NULL;

  CATIClientContainer *piClientOnAppliCont = NULL;
  if ( SUCCEEDED(rc) )
  {
	 rc = QueryInterface(IID_CATIClientContainer, (void **) &piClientOnAppliCont);
  }
  CATListPtrCATBaseUnknown *pMemberList = new CATListPtrCATBaseUnknown();
  if ( SUCCEEDED(rc) )
  {
	 CATUnicodeString clientId("CAAMmrUseCase"); 
	 rc = piClientOnAppliCont->ListMembers(IID_CATISpecObject, clientId,  &pMemberList);
  }
  if (NULL != piClientOnAppliCont )
  {
	 piClientOnAppliCont->Release();
	 piClientOnAppliCont = NULL;
  }
  if (SUCCEEDED(rc)  )
  {
	  for ( int i = 1 ; i <= pMemberList->Size();  i++ )
	  {
	     CATBaseUnknown *pMemberInsideCont = (*pMemberList)[i];
		 if ( NULL != pMemberInsideCont)
		 {
             // Search its base feature
             CATIOsmExtension_var spExtensionOnExtendedFeature = pMemberInsideCont ;
             CATBaseUnknown *pBaseFeature = NULL ; 
			 if ( NULL_var != spExtensionOnExtendedFeature )
			 {
                spExtensionOnExtendedFeature -> QueryBaseObject( IID_CATBaseUnknown, (void**)& pBaseFeature);
			 }

			 // connect the extended feature to its base feature
			 CATIModelEvents_var spModelEventOnBaseFeature = pBaseFeature ;
			 if ( NULL_var != spModelEventOnBaseFeature )
			 {
                spModelEventOnBaseFeature->ConnectTo(pMemberInsideCont);
			 }
       if(NULL != pBaseFeature )
       {
                pBaseFeature -> Release();
                pBaseFeature = NULL;
       }
			 pMemberInsideCont->Release();
			 pMemberInsideCont = NULL ;
		 }
	  }
  }
  delete pMemberList ;
  pMemberList = NULL ;


  return;
}

CATBaseUnknown* CAAEMmrDataExtensionContInit::GetRootContainer (const CATIdent  iInterfaceID )
{
    return NULL;
}
