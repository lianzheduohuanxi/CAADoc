// COPYRIGHT DASSAULT SYSTEMES 2012
//=================================================================================================
//
// CAAEV5V6ExtMmrDataExtensionContInit.cpp
// Provide implementation to interface CATIInit : Initialization of Applicative Container
//
// Note : CAAEV5V6ExtMmrDataExtensionContInit is the same use case as CAAEMmrDataExtensionContInit. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//=================================================================================================

// Local CAAV5V6MechanicalModeler.edu Framework
#include "CAAEV5V6ExtMmrDataExtensionContInit.h"
#include "CAAV5V6ExtMmrUpdateProvForExtCont.h"
#include "CAAV5V6ExtMmrNavigateProvForExtCont.h"
#include "CAAV5V6ExtMmrParmProvForExtCont.h"
#include "CAAV5V6ExtMmrVisuProvForExtCont.h"

// ObjectSpecsModeler Framework for V5
// DataCommonProtocolUse Framework for V6
#include "CATIUpdateProvider.h"

// ObjectModelerNavigator Framework for V5
// DataCommonProtocolUse Framework for V6
#include "CATINavigateProvider.h"

// ObjectModelerBase Framework for V5
// DataCommonProtocolUse Framework for V6
#include "CATIParmProvider.h"
#include "CATI3DVisuProvider.h"

// System Framework
#include "CATInstantiateComponent.h"
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

// FeatureModelerExt Framework 
#include "CATFmCredentials.h"
#include "CATFmFeatureFacade.h"
#include "CATFmContainerFacade.h"
#include "CATFmContainerServices.h"
#include "CATFmAttributeValue.h"
#include "CATFmFeatureIterator.h"
#include "CATFmFeatureModelerID.h"

// Visualization Framework for V5
// VisualizationInterfaces Framework for V6
#include "CATIModelEvents.h"

// C++ Standard library
#include "iostream.h"

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

//DataCommonProtocolExt Framework
#include "CATIProviderManager.h"

#else
//============================================== 
// V5 only
//============================================== 

// ObjectModelerBase Framework
#include "CATIContainer.h"
#include "CATILinkableObject.h"
#include "CATDocument.h"

// ObjectSpecsModeler Framework
#include "CATIProviders.h"

#endif


//===============================================================================================
CATImplementClass(CAAEV5V6ExtMmrDataExtensionContInit,DataExtension,CATInit,CAAV5V6ExtMmrDataExtensionCont);
CATImplementBOA(CATInit,CAAEV5V6ExtMmrDataExtensionContInit);
//===============================================================================================

CAAEV5V6ExtMmrDataExtensionContInit::CAAEV5V6ExtMmrDataExtensionContInit()
{
}
CAAEV5V6ExtMmrDataExtensionContInit::~CAAEV5V6ExtMmrDataExtensionContInit()
{
}
// CATInit interface methods
void CAAEV5V6ExtMmrDataExtensionContInit::Init (CATBoolean  iDestroyExistingData )
{ 
  cout <<" CAAEV5V6ExtMmrDataExtensionContInit::Init" << endl;

  //
	// Two steps
	//   1- declare the providers to the manager
	//   2- connect the extended features to their base feature 
	//

  //===============================================================================================
  // -1- Declare the providers to the manager
  //===============================================================================================

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

  // Retrieve the Provider's manager
  CATIProviderManager *piProvidersMgr = NULL;
  HRESULT rc = ::CATInstantiateComponent("CAAMmrServices",
					       IID_CATIProviderManager,
					       (void **) &piProvidersMgr);
	
#else
//============================================== 
// V5 only
//==============================================

  CATIProviders *piProvidersMgr = NULL;
  CATDocument * pDoc = NULL;

  CATIContainer *pContainerOnThis = NULL;
  HRESULT rc = QueryInterface( IID_CATIContainer , ( void**) &pContainerOnThis );
  if ( FAILED(rc) || ( NULL==pContainerOnThis) )
    return;

  CATILinkableObject* pIlink = NULL;
  rc = pContainerOnThis -> QueryInterface( IID_CATILinkableObject, ( void**) &pIlink );

  pContainerOnThis -> Release();
  pContainerOnThis = NULL;

  if (SUCCEEDED(rc) && pIlink != NULL)
  {
    pDoc = pIlink->GetDocument();
    if (pDoc != NULL)
    {
      // Retrieves a CATIProviders pointer on the current document
      rc = pDoc->QueryInterface(IID_CATIProviders,(void**) &piProvidersMgr);  
	}

	pIlink -> Release();
    pIlink = NULL;
  }
#endif

  if (SUCCEEDED(rc) && piProvidersMgr)
  {
    //Adds all providers we need to extend Update, f(x) (Parameter) , NavigateObject, Visu Mecanism to Applicative Container.

    //Adds CAAV5V6ExtMmrUpdateProvForExtCont
    CAAV5V6ExtMmrUpdateProvForExtCont* pUpdateProvider = new CAAV5V6ExtMmrUpdateProvForExtCont();
    if (pUpdateProvider)
    {
      rc = piProvidersMgr->AddProvider(CATIUpdateProvider::ClassId(), pUpdateProvider);
   
	  if (SUCCEEDED(rc))
		cout <<"   Update Provider added" << endl;
    
      pUpdateProvider->Release();
      pUpdateProvider = NULL;
    }

    //Adds CAAV5V6ExtMmrParmProvForExtCont
    CAAV5V6ExtMmrParmProvForExtCont* pParmProvider = new CAAV5V6ExtMmrParmProvForExtCont();
    if (pParmProvider)
    {
      rc = piProvidersMgr->AddProvider(CATIParmProvider::ClassId(), pParmProvider);

	  if (SUCCEEDED(rc))
		cout <<"   Parm Provider added" << endl ;

      pParmProvider->Release();
      pParmProvider = NULL;
    }

    //Adds CAAV5V6ExtMmrNavigateProvForExtCont
    CAAV5V6ExtMmrNavigateProvForExtCont* pNavigateProvider = new CAAV5V6ExtMmrNavigateProvForExtCont();
    if (pNavigateProvider)
    {
      rc = piProvidersMgr->AddProvider(CATINavigateProvider::ClassId(), pNavigateProvider);
    
	  if (SUCCEEDED(rc))
		cout <<"   Navigate Provider added" << endl ;
	
      pNavigateProvider->Release();
      pNavigateProvider = NULL;
    }

    //Adds CAAV5V6ExtMmrVisuProvForExtCont
    CAAV5V6ExtMmrVisuProvForExtCont* pVisuProvider = new CAAV5V6ExtMmrVisuProvForExtCont();
    if (pVisuProvider)
    {
      rc = piProvidersMgr->AddProvider(CATI3DVisuProvider::ClassId(), pVisuProvider);

      if (SUCCEEDED(rc))
	    cout <<"   Add Visu  Provider" << endl;

      pVisuProvider->Release();
      pVisuProvider = NULL;
    }

    //At the end of operation, don't forget to release the Provider Manager
    piProvidersMgr->Release();
    piProvidersMgr = NULL;    
  }


  //===============================================================================================
  // -2-  Connect the extended feature to their base feature
  //===============================================================================================

  // Declare credentials
  CATFmCredentials CredentialForDataExt;
  CATUnicodeString ClientId("CAAMmrUseCase");
  CATUnicodeString PartnerId = "CAAMmrExtMechanicalModeler";
  CATUnicodeString CatalogName("CAAV5V6ExtMmrCCDataExtensionCatalog");
  rc=CredentialForDataExt.RegisterAsApplicationBasedOn(CATFmFeatureModelerID, PartnerId); 
  rc=CredentialForDataExt.RegisterAsCatalogOwner(CatalogName,ClientId);

  CATFmContainerFacade ContainerFacade(CredentialForDataExt, this);
  if (ContainerFacade.IsValid())
	  cout << "container ok"<< endl;
  else
	  cout << "conatiner ko" << endl;

  CATFmFeatureIterator Iterator;
  rc = ContainerFacade.ScanFeatures(Iterator);
    
  if (SUCCEEDED(rc))
  {
    CATFmFeatureFacade FeatFacadeOnCurrentElement(CredentialForDataExt);
  	HRESULT rc_loop =  Iterator.Next(FeatFacadeOnCurrentElement);
    while (SUCCEEDED(rc_loop)) 
    {
	  // Get data extension
	  CATBaseUnknown * piExtFeat = NULL;
      rc = FeatFacadeOnCurrentElement.QueryInterfaceOnFeature(IID_CATBaseUnknown, (void**)&piExtFeat);

	  if (SUCCEEDED(rc) && piExtFeat)
	  {
		// Get base feature
		CATFmAttributeValue BaseFeat;
        rc = FeatFacadeOnCurrentElement.GetBaseFeature(BaseFeat);

		CATFmFeatureFacade FeatFacadeOnBaseFeat ;
   	    FeatFacadeOnBaseFeat = BaseFeat;
  
   	    CATBaseUnknown_var spBaseFeat = FeatFacadeOnBaseFeat.GetFeature();

		if (spBaseFeat != NULL_var)
		{
          // connect the extended feature to its base feature
		  CATIModelEvents_var spModelEventOnBaseFeature = spBaseFeat;
		  if (spModelEventOnBaseFeature != NULL_var)
            spModelEventOnBaseFeature->ConnectTo(piExtFeat);
		}
		piExtFeat->Release();
		piExtFeat = NULL;
	  }	
	  rc_loop = Iterator.Next(FeatFacadeOnCurrentElement);
	}
  }

#ifdef CATIAV5R23
//============================================== 
// V5 only
//==============================================
  
  rc = CATFmContainerServices::LoadAllFeatureContainers(CredentialForDataExt, pDoc);
       
#endif
  return;

}

CATBaseUnknown* CAAEV5V6ExtMmrDataExtensionContInit::GetRootContainer (const CATIdent  iInterfaceID )
{
  return NULL;
}
