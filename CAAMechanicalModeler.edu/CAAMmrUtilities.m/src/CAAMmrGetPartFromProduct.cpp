// COPYRIGHT DASSAULT SYSTEMES 2001
//==========================================================================
// This file contains the method to extract from the original CATPart the
// geometrie to create the new user feature
// This method is called in the CAAMcaUdfCreation.cpp 
//==========================================================================

//MecModInterfaces Framework
#include "CATIContainerOfDocument.h"
#include "CATIPrtContainer.h"

//ObjectSpecsModeler Framework
#include "CATISpecObject.h"

//ObjectModelerBase
#include "CATILinkableObject.h"
#include "CATIContainer.h"
#include "CATDocument.h"

//ProductStructure Framework
#include "CATIProduct.h"

// 
#include "CATLISTV_CATBaseUnknown.h" 

// Local Framework
#include "CAAMmrGetPartFromProduct.h"      // to retrieve a specific element

// others
#include "iostream.h"


HRESULT CAAMmrGetPartFromProduct(CATIProduct_var       ispProduct,                                
				                 CATISpecObject_var  & ospPartFromProduct)
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
                 CATIPrtContainer * piPrtCont = NULL ;
                 rc = pIContainerOnSpecContainer->QueryInterface( IID_CATIPrtContainer , 
                                                                    (void**) &piPrtCont );

                 if ( SUCCEEDED(rc) )
                 {
                    ospPartFromProduct = piPrtCont->GetPart();

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

