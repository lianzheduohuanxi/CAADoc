// COPYRIGHT DASSAULT SYSTEMES 2012
//==========================================================================
// 
#include "CAAV5V6MmrGetPartFromProduct.h"      // to retrieve a specific element

#include "CATIAV5Level.h"

//CATMecModUseItf Framework
#include "CATIMmiPrtContainer.h"

//CATMecModLiveUseItf Framework
#include "CATIMmiMechanicalFeature.h"

//MecModInterfaces Framework in V5
//CATMecModLiveUseItf Framework in V6
#include "CATIPartRequest.h"

// System Framework
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

// C++ Standard library
#include "iostream.h"

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

//CATPLMIdentificationAccess Framework
#include "CATPLMCoreType.h"

// CATPLMComponentInterfaces Framework
#include "CATIPLMNavInstance.h"
#include "CATIPLMNavRepInstance.h"
#include "CATIPLMNavReference.h"
#include "CATIPLMNavRepReference.h"
#include "CATIPLMNavEntity.h"
#include "CATListPtrCATIPLMNavEntity.h"

// CAT3DPhysicalRepInterfaces Framework
#include "CATIPsiRepresentationLoadMode.h"

#else
//============================================== 
// V5 only
//============================================== 

//ObjectSpecsModeler Framework
#include "CATISpecObject.h"

//MecModInterfaces Framework
#include "CATIContainerOfDocument.h"

//ObjectModelerBase
#include "CATILinkableObject.h"
#include "CATDocument.h"

//ProductStructure Framework
#include "CATIProduct.h"

#endif

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
HRESULT CAAV5V6MmrGetPartFromProduct(CATIPLMNavInstance_var spNavInstance, CATIPartRequest_var  & ospPartFromProduct)
{
	HRESULT rc = E_FAIL ;
 
	if ( NULL_var == spNavInstance ) return E_FAIL ;

	// Retrieve the reference of the current instance
	CATIPLMNavReference *pReferenceOfInstance = NULL ;
    rc = spNavInstance->GetReferenceInstanceOf(pReferenceOfInstance);

	// Retrieve the first inst rep ref
	CATIPLMNavRepInstance * pNavRepInst = NULL ;	
	if ( NULL != pReferenceOfInstance )
	{
	   CATListPtrCATIPLMNavEntity ListNavEntity = NULL ;
       CATPLMCoreType TypeRepInstance  = PLMCoreRepInstance ;
	   pReferenceOfInstance->ListChildren(ListNavEntity,1,&TypeRepInstance) ;
	  
	   if ( ListNavEntity.Size() >=1 )
	   {
            CATIPLMNavEntity *pCurrent = ListNavEntity[1];
            rc = pCurrent->QueryInterface(IID_CATIPLMNavRepInstance, (void**)& pNavRepInst );
	   }
	   for ( int i=1 ; i<= ListNavEntity.Size() ; i++)
	   {
          CATIPLMNavEntity *pCurrent = ListNavEntity[1];
		  if ( NULL != pCurrent ) 
		  {
             pCurrent->Release(); pCurrent = NULL ;
		  }
	   }
       pReferenceOfInstance->Release(); pReferenceOfInstance = NULL ;
	}

	// Retrieve the reference of the first inst rep ref
	CATIPLMNavRepReference *pNavRepRef = NULL ;
    if ( NULL!=pNavRepInst  )
	{
       rc = pNavRepInst->GetRepReferenceInstanceOf(pNavRepRef) ;
       pNavRepInst->Release(); pNavRepInst = NULL ;
	}
    
	// change the loading mode
    if ( NULL != pNavRepRef )
	{
	   CATIPsiRepresentationLoadMode *piRepLoadMode = NULL;
	   rc = pNavRepRef->QueryInterface(IID_CATIPsiRepresentationLoadMode,(void **) &piRepLoadMode);
									     
	   if (SUCCEEDED(rc) && NULL != piRepLoadMode) 
	   {
		   rc = piRepLoadMode->ChangeLoadingMode(CATIPsiRepresentationLoadMode::EditMode);
		   piRepLoadMode->Release();
		   piRepLoadMode = NULL;
	   }
	}

	//Retrieve the applicative container
    CATIMmiPrtContainer * pContainer = NULL ;
	if ( SUCCEEDED(rc) && (NULL != pNavRepRef) )
    {
	  rc = pNavRepRef->RetrieveApplicativeContainer("CATPrtCont",IID_CATIMmiPrtContainer,(void **)&pContainer);	      
    }

	if (SUCCEEDED(rc) && (NULL != pContainer) )
	{
		CATIMmiMechanicalFeature_var spMechFeatOnPart;  
		rc = pContainer->GetMechanicalPart(spMechFeatOnPart);
	
		if (SUCCEEDED(rc) && (NULL_var != spMechFeatOnPart))
			ospPartFromProduct = spMechFeatOnPart;
	}

	if ( NULL != pContainer)
	{
       pContainer->Release();  pContainer = NULL ;
	}

    if ( NULL != pNavRepRef)
    {
		pNavRepRef->Release(); pNavRepRef = NULL ;
	}


	if ( NULL_var == ospPartFromProduct )
		return E_FAIL ;
	else return S_OK ;
   
}
#else
//============================================== 
// V5 only
//==============================================
HRESULT CAAV5V6MmrGetPartFromProduct(CATIProduct_var ispProduct, CATISpecObject_var  & ospPartFromProduct)
{
  HRESULT rc = E_FAIL ;
 
  if ( NULL_var == ispProduct ) return E_FAIL ;

  CATIProduct_var spRef = ispProduct->GetReferenceProduct();
  
  if ( NULL_var != spRef )
  {
     CATILinkableObject * piLinkableObject = NULL;
     rc = spRef->QueryInterface( IID_CATILinkableObject, (void**)& piLinkableObject );                            

     if ( SUCCEEDED(rc) )
     {
        // Do not release this pointer
        CATDocument * pDocument = NULL ;
        pDocument = piLinkableObject->GetDocument();
   
        if ( NULL != pDocument )
        {
           CATIContainerOfDocument * pIContainerOfDocument = NULL ;
           rc = pDocument->QueryInterface(IID_CATIContainerOfDocument, 
                                                   (void**)& pIContainerOfDocument );
           if ( SUCCEEDED(rc) )
           {
              CATIContainer * pIContainerOnSpecContainer = NULL ;
              rc = pIContainerOfDocument->GetSpecContainer(pIContainerOnSpecContainer);
              if ( SUCCEEDED(rc) && (NULL!=pIContainerOnSpecContainer) )
              {
                 CATIMmiPrtContainer * piPrtCont = NULL ;
                 rc = pIContainerOnSpecContainer->QueryInterface( IID_CATIMmiPrtContainer , 
                                                                    (void**) &piPrtCont );

                 if ( SUCCEEDED(rc) )
                 {
					CATIMmiMechanicalFeature_var spMechFeatOnPart;  
		            rc = piPrtCont->GetMechanicalPart(spMechFeatOnPart);

					if (SUCCEEDED(rc) && (NULL_var != spMechFeatOnPart))
			           ospPartFromProduct = spMechFeatOnPart;
                  
                    piPrtCont->Release();
                    piPrtCont =  NULL ;
                 }
                 pIContainerOnSpecContainer->Release();
                 pIContainerOnSpecContainer = NULL ;
              }
              pIContainerOfDocument->Release();
              pIContainerOfDocument = NULL ;
           }
        } else rc = E_FAIL ;

        piLinkableObject->Release();
        piLinkableObject = NULL ;
     }
  }

  return rc ;
}
#endif

