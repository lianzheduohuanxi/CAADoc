// COPYRIGHT DASSAULT SYSTEMES 2007
//=================================================================================================
//
// CAAEMmrCCDataExtensionFactory.cpp
// Provide implementation to interface
//    CAAIMmrCCDataExtensionFactory
//
//=================================================================================================

// Local Framework
#include "CAAEMmrCCDataExtensionFactory.h"

// CAAMechanicalModeler.edu Framework
#include "CAAIMmrCCDataExtension.h" // needed by the factory to return a pointer on this interface
#include "CAAMmrAddCCExtension.h"

// ObjectModelerBase Framework
#include "CATIContainer.h"       
#include "CATAppliContServices.h"
#include "CATILinkableObject.h"
#include "CATDocument.h"
#include "CATInit.h"

//For BRepAccess Management
#include "CATIBRepAccess.h"

// Include System
#include "CATUnicodeString.h"

CATImplementClass ( CAAEMmrCCDataExtensionFactory ,
                    DataExtension         ,
                    CATBaseUnknown        ,
                    CATPrtCont            );

//---------------------------------------------------------------------------------------------------
// CAAEMmrCCDataExtensionFactory : constructor
//---------------------------------------------------------------------------------------------------
CAAEMmrCCDataExtensionFactory::CAAEMmrCCDataExtensionFactory():
CATBaseUnknown()
{
    
}

//---------------------------------------------------------------------------------------------------
// CAAEMmrCCDataExtensionFactory : destructor
//---------------------------------------------------------------------------------------------------
CAAEMmrCCDataExtensionFactory::~CAAEMmrCCDataExtensionFactory()
{
    
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CAAIMmrCCDataExtensionFactory.h" // needed to tie the implementation to its interface
TIE_CAAIMmrCCDataExtensionFactory( CAAEMmrCCDataExtensionFactory);

// 
// To declare that GSMTool implements CAAIMmrCCDataExtensionFactory, insert 
// the following line in the interface dictionary:
//
// CATPrtCont  CAAIMmrCCDataExtensionFactory    libCAAMmrCCDataExtension



//---------------------------------------------------------------------------------------------------
// Implements CAAIMmrCCDataExtensionFactory::CreateDataExtension
//---------------------------------------------------------------------------------------------------

HRESULT CAAEMmrCCDataExtensionFactory::CreateMmrCCDataExtension ( const CATBaseUnknown *iBaseFeature,
                                                                  CAAIMmrCCDataExtension **ioMmrCCDataExtension)  
{
  // A Feature Extension needs to be instanciate in a specific CATFeatCont applicative container.
  // Let's name this specific container "MmrDataExtensionCont".
  // This name will be its LateType to define it...in particular during initialization process.
  //
  // Feature Extension are design to extend Base Features defined in a specific ressource file (CAAMmrCCDataExtension.CATRsc)
  //
  // As Features Extensions are specific features, instantiated in applicative container, their factories are quite particular... 
  //
  
  //===============================================================================================
  //
  //  What does the factory do ?
  //
  //     o -1- Generates the extension container if it doesn't exist
  //     o -1-a- Retrieves a CATIContainer interface pointer on this (CATPrtCont)
  //     o -1-b- Retrieves a pointer to the CATDocument to which the container belongs
  //     o -1-c- Check if Applicative Container "MmrDataExtensionCont" exists
  //     o -1-c-1- Applicative Container doesn't exist -  Creates It !
  //     o -1-c-1-1- Initializes Created Applicative Container
  //     o -1-c-1-2- Initializes Undo/Redo Mechanism on  Applicative Container - For UI Creation
  //     o -2- Extends iBaseFeature with MmrCCDataExtension using CAAMmrAddCCExtension method
  //
  //===============================================================================================

  //===============================================================================================
  //
  // -1- Generates the extension container if it doesn't exist
  //
  //===============================================================================================

  HRESULT Status = E_FAIL;
  const CATUnicodeString AppContTypeLate ("MmrDataExtensionCont");

  //===============================================================================================
  // -1-a- Retrieves a CATIContainer interface pointer on this (CATPrtCont)
  //===============================================================================================

  CATIContainer *piContainerOnThis = NULL;
  HRESULT rc = QueryInterface( IID_CATIContainer , ( void**) &piContainerOnThis );
  if ( FAILED(rc) )
  {
    return E_FAIL;
  }
  if (iBaseFeature == NULL)
    return E_FAIL;

  //===============================================================================================
  // -1-b- Retrieves a pointer to the CATDocument to which the container belongs
  //===============================================================================================

  CATILinkableObject* pIlink = NULL;
  rc = QueryInterface( IID_CATILinkableObject, ( void**) &pIlink );

  if(SUCCEEDED(rc) && pIlink != NULL)
  {
    CATDocument * pDoc = pIlink -> GetDocument();
    if (pDoc != NULL)
    {
      //===============================================================================================
      // -1-c- Check if Applicative Container "MmrDataExtensionCont" exists
      //===============================================================================================
      
			CATBaseUnknown *pApplicativeCont = NULL;	
      rc = ::CATGetApplicativeContainer(&pApplicativeCont,
                                        pDoc,
                                        IID_CATIContainer,
                                        AppContTypeLate);

      if (FAILED(rc) || pApplicativeCont == NULL)
      {
        //===============================================================================================
        // -1-c-1- Applicative Container doesn't exist -  Creates It !
        //===============================================================================================

        CATIdent idAppliCont = "CAAMmrDataExtensionCont";
        CATIdent idSuperType = "CATFeatCont";


        rc = ::CATCreateApplicativeContainer(&pApplicativeCont,  // applicative cont created
                                             pDoc,               // document 
                                             idAppliCont,        // type of applicative cont
                                             IID_CATIContainer,  // interface type of applicative cont
                                             idSuperType,        // supertype of applicative cont 
                                             AppContTypeLate );  // name of appli cont

        if (SUCCEEDED(rc) && pApplicativeCont!= NULL)
        {
          CATIContainer *pApplicativeContainer = NULL;
          rc = pApplicativeCont -> QueryInterface( IID_CATIContainer , ( void**) &pApplicativeContainer);
          
          if (SUCCEEDED(rc) && pApplicativeContainer!= NULL)
          {
            //===============================================================================================
            // -1-c-1-1- Initializes Created Applicative Container
            //===============================================================================================
            CATInit *pMyContInit = NULL;
            rc = pApplicativeContainer -> QueryInterface( IID_CATInit, ( void**) &pMyContInit);
          
            if (SUCCEEDED(rc) && pMyContInit != NULL)
            {
              //Initialise Applicative Container
              pMyContInit -> Init(FALSE);
							pMyContInit -> Release();
              pMyContInit = NULL;

              //===============================================================================================
              // -1-c-1-2- Initializes Undo/Redo Mechanism on  Applicative Container - For UI Creation
              //===============================================================================================
              
							rc = ::CATOmbPerformAfterContainerCreation( pApplicativeContainer );
						}
            pApplicativeContainer -> Release();
						pApplicativeContainer = NULL;
					}
				}
			}

			if (SUCCEEDED(rc) && pApplicativeCont!= NULL)
			{
				//===============================================================================================
        //
        // -2- Extends iBaseFeature with MmrCCDataExtension
        //
        //===============================================================================================

				rc = ::CAAMmrAddCCExtension(iBaseFeature, ioMmrCCDataExtension);

				pApplicativeCont->Release();
				pApplicativeCont = NULL;
			}
			else
				rc = E_FAIL;      
    }
    else
      rc = E_FAIL;
  }
	else
		rc = E_FAIL;
 
  if(piContainerOnThis != NULL)
  {
    piContainerOnThis -> Release();
    piContainerOnThis = NULL;
  }

  if(pIlink != NULL)
  {
    pIlink -> Release();
    pIlink = NULL;
  }

  return rc; 
}

