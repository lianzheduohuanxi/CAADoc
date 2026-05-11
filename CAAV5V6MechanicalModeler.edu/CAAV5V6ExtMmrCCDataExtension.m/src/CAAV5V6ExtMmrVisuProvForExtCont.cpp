// COPYRIGHT DASSAULT SYSTEMES 2012
//=================================================================================================
//  Abstract of the class:
//  ----------------------
//
//   : 
//  implmements CATI3DVisuProvider interface.
//  Extends CATI3DGeoVisu Mechanism to Extension Features contained in the 
//    applicative container V5V6ExtMmrDataExtensionCont (type = CAAV5V6ExtMmrNavigateProvForExtCont)
//
// Note : CAAV5V6ExtMmrVisuProvForExtCont is the same use case as CAAMmrVisuProvForExtCont. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//==================================================================================================

#include "CATIAV5Level.h"

// Local CAAV5V6MechanicalModeler.edu Framework
#include "CAAV5V6ExtMmrVisuProvForExtCont.h"

// ObjectModelerNavigator Framework in V5
// DataCommonProtocolUse Framework in V6
#include "CATI3DVisuProvider.h"

// Visualization Framework in V5
// VisualizationInterfaces Framework in V6
#include "CATI3DGeoVisu.h"

// System Framework 
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

// FeatureModelerExt 
#include "CATFmCredentials.h"
#include "CATFmFeatureFacade.h"
#include "CATFmFeatureModelerID.h"
#include "CATFmFeatureIterator.h"
#include "CATFmContainerFacade.h"

// C++ Standard library
#include "iostream.h"

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

// System Framework
#include "CATLISTP_CATBaseUnknown.h"

// CATPLMIdentificationAccess Framework
#include "CATIPLMComponent.h"

// CATPLMComponentInterfaces Framework
#include "CATPLMComponentInterfacesServices.h"
#include "CATIPLMNavRepReference.h"

#else
//============================================== 
// V5 only
//==============================================

// ObjectModelerSystem Framework
#include "sequence_CATBaseUnknown_ptr.h"

// ObjectModelerBase Framework
#include "CATILinkableObject.h"
#include "CATDocument.h"
#include "CATIContainer.h"
#include "CATAppliContServices.h"

#endif

//==================================================================================

CATImplementClass(CAAV5V6ExtMmrVisuProvForExtCont,
                  Implementation,
                  CATI3DVisuProvider,
                  CATNULL);

CATImplementBOA(CATI3DVisuProvider, CAAV5V6ExtMmrVisuProvForExtCont);

CAAV5V6ExtMmrVisuProvForExtCont::CAAV5V6ExtMmrVisuProvForExtCont()
{}

CAAV5V6ExtMmrVisuProvForExtCont::~CAAV5V6ExtMmrVisuProvForExtCont()
{}

HRESULT CAAV5V6ExtMmrVisuProvForExtCont::GetChildren(CATBaseUnknown * iObj, CATLISTP(CATBaseUnknown) ** oListChildren)
{
  cout <<" CAAV5V6ExtMmrVisuProvForExtCont::GetChildren" << endl;

  HRESULT rc = E_FAIL;

  if ( NULL == iObj)
    return rc;

  ///======================================
  // 1) Retrieves the applicative container
  //=======================================
  
  //Keep in Mind The MechanicalPart context: iObj represents the Mechanical Part.
  CATBaseUnknown* piMmrDataCont = NULL; 

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

  CATIPLMComponent_var spPLMComponentOnPart;
  rc = CATPLMComponentInterfacesServices::GetPLMComponentOf(iObj,spPLMComponentOnPart);
  if (SUCCEEDED(rc) && (NULL_var!=spPLMComponentOnPart)) 
  {
    CATIPLMNavRepReference_var spRepRef = spPLMComponentOnPart;
    if (spRepRef != NULL_var)
    {
      const CATUnicodeString AppContTypeLate("V5V6ExtMmrDataExtensionCont");
      rc = spRepRef->RetrieveApplicativeContainer(AppContTypeLate,IID_CATBaseUnknown,(void **)&piMmrDataCont);
    }
  }
#else
//============================================== 
// V5 only
//==============================================
  CATILinkableObject *piLinkableOnObj = NULL;

  rc = iObj->QueryInterface (IID_CATILinkableObject, (void**) &piLinkableOnObj);
  if (SUCCEEDED(rc) && piLinkableOnObj != NULL)
  {
    CATDocument* pDoc = piLinkableOnObj -> GetDocument();

    piLinkableOnObj -> Release();
    piLinkableOnObj = NULL;

    const CATUnicodeString AppContTypeLate ("V5V6ExtMmrDataExtensionCont");
  
    rc = ::CATGetApplicativeContainer(&piMmrDataCont,
                                      pDoc,
                                      IID_CATIContainer,
									  AppContTypeLate);
  }
#endif


  if(SUCCEEDED(rc) && piMmrDataCont!= NULL)
  {
    CATFmCredentials CredentialForCCExtend;
    CATUnicodeString ClientId("CAAMmrUseCase");
    CATUnicodeString PartnerId = "CAAMmrExtMechanicalModeler";
    CATUnicodeString CatalogName("CAAV5V6ExtMmrCCDataExtensionCatalog");
    CredentialForCCExtend.RegisterAsApplicationBasedOn(CATFmFeatureModelerID, PartnerId); 
    CredentialForCCExtend.RegisterAsCatalogOwner(CatalogName,ClientId);
    
    CATFmContainerFacade MmrDataContFacade(CredentialForCCExtend, piMmrDataCont);
  
    piMmrDataCont->Release();
    piMmrDataCont = NULL;

    //===============================================================
    // 2) Retrieves the list of features in the applicative container
    //===============================================================

    CATFmFeatureIterator IteratorOnAllFeats;
    rc = MmrDataContFacade.ScanFeatures(IteratorOnAllFeats);
    if (SUCCEEDED(rc))
    {
  	  CATFmFeatureFacade FeatFacadeOnCurrentElt(CredentialForCCExtend);
      HRESULT rc_loop = IteratorOnAllFeats.Next(FeatFacadeOnCurrentElt);
   	  while(SUCCEEDED(rc_loop))
      {
        CATI3DGeoVisu * piFeatVisu = NULL;
        rc = FeatFacadeOnCurrentElt.QueryInterfaceOnFeature(IID_CATI3DGeoVisu, (void**) &piFeatVisu);
        if (SUCCEEDED(rc) && piFeatVisu)
        {
          if (*oListChildren == NULL)
             *oListChildren = new CATListPtrCATBaseUnknown;
          if (*oListChildren)
          {
            // Cast to CATBaseUnknwon before adding to output list
            CATBaseUnknown* piFeat = NULL;
            rc = piFeatVisu->QueryInterface(IID_CATBaseUnknown, (void**) & piFeat);
            if(SUCCEEDED(rc) && piFeat != NULL)
              (*oListChildren)->Append(piFeat);
          }
          piFeatVisu->Release();
          piFeatVisu = NULL;
        }
        rc_loop =  IteratorOnAllFeats.Next(FeatFacadeOnCurrentElt);
      }
    }
  }
  return rc;
}

