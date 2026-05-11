// COPYRIGHT DASSAULT SYSTEMES 2012
//==================================================================================================
//  Abstract of the class:
//  ----------------------
//
//  CAAV5V6ExtMmrUpdateProvForExtCont : 
//  Implements CATIUpdateProvider interface.
//  Extends Update Mechanism to Extension Features contained in the 
//    applicative container V5V6ExtMmrDataExtensionCont (type = CAAV5V6ExtMmrNavigateProvForExtCont)
//
// Note : CAAV5V6ExtMmrUpdateProvForExtCont is the same use case as CAAMmrUpdateProvForExtCont. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//==================================================================================================

#include "CATIAV5Level.h"

// CAAV5V6MechanicalModeler.edu Framework
#include "CAAV5V6ExtMmrUpdateProvForExtCont.h"

// ObjectSpecsModeler Framework in V5
// DataCommonProtocolUse Framework in V6
#include "CATIUpdateProvider.h"

// VisualizationInterfaces
#include "CATIModelEvents.h"
#include "CATModify.h"

// System Framework
#include "CATBoolean.h"
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATErrorMacros.h"

// FeatureModelerExt Framework
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

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

#endif

CATImplementClass(CAAV5V6ExtMmrUpdateProvForExtCont,
                  Implementation,
                  CATIUpdateProvider,
                  CATNULL);


CATImplementBOA(CATIUpdateProvider, CAAV5V6ExtMmrUpdateProvForExtCont);

CAAV5V6ExtMmrUpdateProvForExtCont::CAAV5V6ExtMmrUpdateProvForExtCont()
{}

CAAV5V6ExtMmrUpdateProvForExtCont::~CAAV5V6ExtMmrUpdateProvForExtCont()
{}

int CAAV5V6ExtMmrUpdateProvForExtCont::Update(CATBaseUnknown* iWorkingObj, CATBaseUnknown_var iDomain)
{
  int retnum = 1; 
  HRESULT rc = E_FAIL;

  cout <<" CAAV5V6ExtMmrCCDataExtension.m::Update" << endl;

  //Keep in Mind The MechanicalPart context: iWorkingObj represents the Mechanical Part.
  if (NULL == iWorkingObj)
    return retnum;

  //
  //1)Retrieves the V5V6ExtMmrDataExtensionCont container
  // 
  CATBaseUnknown* piMmrDataCont = NULL; 
  
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
  CATIPLMComponent_var spPLMComponentOnPart;
  rc = CATPLMComponentInterfacesServices::GetPLMComponentOf(iWorkingObj,spPLMComponentOnPart);
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

  rc = iWorkingObj->QueryInterface(IID_CATILinkableObject, (void**) &piLinkableOnObj);
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


    // 2) Retrieves the list of features in the applicative container
    CATFmFeatureIterator IteratorOnAllFeats;
    rc = MmrDataContFacade.ScanFeatures(IteratorOnAllFeats);
    if (SUCCEEDED(rc))
    {
  	  CATFmFeatureFacade FeatFacadeOnCurrentElt(CredentialForCCExtend);
      HRESULT rc_loop = IteratorOnAllFeats.Next(FeatFacadeOnCurrentElt);
   	  while(SUCCEEDED(rc_loop))
      {
        // 3) Update each feature
        rc = FeatFacadeOnCurrentElt.IsUpToDate();
        if (rc == S_FALSE)
          rc = FeatFacadeOnCurrentElt.Update();
        
        if (SUCCEEDED(rc))
        {
          retnum = 0;

          // 5) After Update, Send an Event for Visu in order to advice VisuManager for a modification in Model
          CATBaseUnknown_var spFeat = FeatFacadeOnCurrentElt.GetFeature();
          if (spFeat != NULL_var)
          {
            CATIModelEvents_var spModelEventOnFeat = spFeat;
            if(spModelEventOnFeat != NULL_var)
				    {
              CATModify BuiltInfo(spFeat);     
              spModelEventOnFeat->Dispatch(BuiltInfo);
            }
          }
        }

        rc_loop =  IteratorOnAllFeats.Next(FeatFacadeOnCurrentElt);
      }
    }    
  }

  return retnum;
}


#ifdef CATIAV5R23
CATBoolean CAAV5V6ExtMmrUpdateProvForExtCont::IsUpToDate(CATBaseUnknown* iWorkingObj, CATIDomain_var iDomain) const
{
  CATBoolean RetBool = TRUE;

  if (NULL == iWorkingObj)
    return RetBool;

  CATIContainer * piMmrDataCont = NULL; 

  //Keep in Mind The MechanicalPart context: iWorkingObj represents the Mechanical Part.
  //
  //1 ]Retrieves the MmrDataExtensionCont container
  //
  HRESULT rc = CAAV5V6ExtMmrUpdateProvForExtCont::GetMmrDataExtension(iWorkingObj, &piMmrDataCont);

  if(SUCCEEDED(rc) && piMmrDataCont!= NULL)
  {
    // 2 ] Retrieves the Extension Features contained in MmrDataExtensionCont container
    SEQUENCE(CATBaseUnknown_ptr)  pMemberList;

    // @CSC-Filter VIOI
    CATLONG32 NbObjects = piMmrDataCont -> ListMembersHere("CATIOsmExtension", pMemberList);
    //Release due to addref of GetMmrDataExtension !
    piMmrDataCont -> Release();
    piMmrDataCont = NULL;

    if(NbObjects != NULL)
    {
      CATISpecObject_var  hSpecsMember = NULL_var;
      for(int i=0;i<NbObjects;i++)
      {
        hSpecsMember = pMemberList[i];
        if (hSpecsMember != NULL_var)
        {
          // 3 ] Test "IsUpToDate" on Extension Features
          if(hSpecsMember -> IsUpToDate(iDomain) == FALSE)
            RetBool = FALSE ;
          
          //Beware Must Release pMemberList elements after use
          //(C.f. CATIContainer::ListMembersHere)
          pMemberList[i]->Release();
          pMemberList[i] = NULL;
        }
      }
    }
  }
  return RetBool;
}

void CAAV5V6ExtMmrUpdateProvForExtCont::SetUpToDate(CATBaseUnknown* iWorkingObj, boolean iFlag )
{
  return; //Not Implemented
}

int CAAV5V6ExtMmrUpdateProvForExtCont::IsInactive(CATBaseUnknown* iWorkingObj) const
{
  return 0;//Not Implemented
}

HRESULT CAAV5V6ExtMmrUpdateProvForExtCont::GetMmrDataExtension(CATBaseUnknown* iWorkingObj, CATIContainer ** ioMmrDataCont)
{
  // Retrieves a pointer to the applicative container.
  CATILinkableObject *piLinkableOnObj = NULL;

  if(iWorkingObj == NULL)
    return E_FAIL;

  HRESULT rc = iWorkingObj->QueryInterface (IID_CATILinkableObject, (void**) &piLinkableOnObj);
  if(SUCCEEDED(rc) && piLinkableOnObj != NULL)
  {
    CATDocument* pDoc = piLinkableOnObj -> GetDocument();

    piLinkableOnObj -> Release();
    piLinkableOnObj = NULL;

    const CATUnicodeString AppContTypeLate ("V5V6ExtMmrDataExtensionCont");
    CATBaseUnknown *pApplicativeCont = NULL;

    rc = ::CATGetApplicativeContainer(&pApplicativeCont,
                                      pDoc,
                                      IID_CATIContainer,
                                      AppContTypeLate);

    if(SUCCEEDED(rc) && pApplicativeCont != NULL)
    {
      rc = pApplicativeCont-> QueryInterface(IID_CATIContainer, (void**) ioMmrDataCont);
    }
  }
  return rc;
}
#endif



