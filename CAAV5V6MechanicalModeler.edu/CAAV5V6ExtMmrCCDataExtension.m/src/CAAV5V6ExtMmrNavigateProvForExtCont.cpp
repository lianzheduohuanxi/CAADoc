// COPYRIGHT DASSAULT SYSTEMES 2012
//=================================================================================================
//  Abstract of the class:
//  ----------------------
//
//  CAAV5V6ExtMmrNavigateProvForExtCont: 
//  Implements CATINavigateProvider interface.
//  Extends CATINavigateObject Mechanism to Extension Features contained in the 
//    applicative container V5V6ExtMmrDataExtensionCont (type = CAAV5V6ExtMmrNavigateProvForExtCont)
//
// Note : CAAV5V6ExtMmrNavigateProvForExtCont is the same use case as CAAMmrNavigateProvForExtCont. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//=================================================================================================

#include "CATIAV5Level.h"

// Local CAAV5V6MechanicalModeler.edu Framework
#include "CAAV5V6ExtMmrNavigateProvForExtCont.h"
#include "CAAIV5V6ExtMmrCCDataExtension.h"

// ObjectModelerNavigator Framework in V5
// DataCommonProtocolUse Framework in V6 
#include "CATINavigateProvider.h"

// System Framework
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

// KnowledgeInterfaces Framework
#include "CATICkeParm.h"

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
#include "CATIPLMNavRepReference.h"
#include "CATPLMComponentInterfacesServices.h"

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

CATImplementClass(CAAV5V6ExtMmrNavigateProvForExtCont,
                  Implementation,
                  CATINavigateProvider,
                  CATNULL);

CATImplementBOA(CATINavigateProvider, CAAV5V6ExtMmrNavigateProvForExtCont);

CAAV5V6ExtMmrNavigateProvForExtCont::CAAV5V6ExtMmrNavigateProvForExtCont()
{}

CAAV5V6ExtMmrNavigateProvForExtCont::~CAAV5V6ExtMmrNavigateProvForExtCont()
{}

HRESULT CAAV5V6ExtMmrNavigateProvForExtCont::GetChildren(CATBaseUnknown* iObj, CATListPtrCATBaseUnknown** ioProvidedChildren)
{
  cout <<" CAAV5V6ExtMmrNavigateProvForExtCont::GetChildren" << endl;

  HRESULT rc = E_FAIL;

  //Keep in Mind The MechanicalPart context: iObj represents the Mechanical Part.
  if ( NULL == iObj)
    return rc;

  //=======================================
  // 1) Retrieves the applicative container
  //=======================================
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
  
  if (SUCCEEDED(rc) && piLinkableOnObj!= NULL)
  {
    CATDocument* pDoc = piLinkableOnObj->GetDocument();
    piLinkableOnObj->Release();
    piLinkableOnObj = NULL;

    const CATUnicodeString AppContTypeLate ("V5V6ExtMmrDataExtensionCont");
 
    rc = ::CATGetApplicativeContainer(&piMmrDataCont,
                                      pDoc,
                                      IID_CATIContainer,
									  AppContTypeLate);
  }

#endif

  if (SUCCEEDED(rc) && piMmrDataCont!= NULL)
  {
    CATFmCredentials CredentialForCCExtend;
    CATUnicodeString ClientId("CAAMmrUseCase");
    CATUnicodeString PartnerId = "CAAMmrExtMechanicalModeler";
    CATUnicodeString CatalogName("CAAV5V6ExtMmrCCDataExtensionCatalog");
    CredentialForCCExtend.RegisterAsApplicationBasedOn(CATFmFeatureModelerID, ClientId);
    CredentialForCCExtend.RegisterAsCatalogOwner(CatalogName,ClientId); 

    CATFmContainerFacade MmrDataContFacade(CredentialForCCExtend, piMmrDataCont);
  
    piMmrDataCont->Release();
    piMmrDataCont = NULL;


    //===============================================================
    // 2) Retrieves the list of features in the applicative container
    //===============================================================

    CATListPtrCATBaseUnknown *pMemberList = new CATListPtrCATBaseUnknown();
    if (pMemberList == NULL)
      return E_FAIL;

    CATFmFeatureIterator IteratorOnAllFeats;
    rc = MmrDataContFacade.ScanFeatures(IteratorOnAllFeats);
    if (SUCCEEDED(rc))
    {
  	  CATFmFeatureFacade FeatFacadeOnCurrentElt(CredentialForCCExtend);
      HRESULT rc_loop = IteratorOnAllFeats.Next(FeatFacadeOnCurrentElt);
   	  while(SUCCEEDED(rc_loop))
      {
        CAAIV5V6ExtMmrCCDataExtension * piFeat = NULL;
        rc = FeatFacadeOnCurrentElt.QueryInterfaceOnFeature(IID_CAAIV5V6ExtMmrCCDataExtension, (void**) &piFeat);
        if (SUCCEEDED(rc) && piFeat)
          pMemberList->Append(piFeat);
   		  rc_loop =  IteratorOnAllFeats.Next(FeatFacadeOnCurrentElt);
   	  }
    }
 
	int Nbelt = pMemberList->Size();
    for(int i=1; i<=Nbelt; i++)
    {
	    CATBaseUnknown *piMemberListCurr = (*pMemberList)[i] ;
	    if ( NULL != piMemberListCurr )
	    {
        CAAIV5V6ExtMmrCCDataExtension_var spMmrCCDataExtension = piMemberListCurr;
        if(spMmrCCDataExtension != NULL_var)
        {
          //====================================================
          // 3) We Show only Built Extension
          //====================================================
          CATICkeParm_var spValuatedParm;
          rc = spMmrCCDataExtension->GetValuatedParam(spValuatedParm);
          if (SUCCEEDED(rc) && spValuatedParm != NULL_var)
          {
            //Add feature to output list
            if (*ioProvidedChildren == NULL)
             *ioProvidedChildren = new CATListPtrCATBaseUnknown;
            if (*ioProvidedChildren)
             (*ioProvidedChildren)->Append(piMemberListCurr);
		      }
          else 
          {
            piMemberListCurr->Release();
            piMemberListCurr = NULL;
          }
        }
      }
	    delete pMemberList;
	    pMemberList = NULL;
    }
  }
  return rc;
}



