// COPYRIGHT DASSAULT SYSTEMES 2012
//===============================================================================
// This file contains the method to initialize a session, open a part and extract
// the specification container.
//===============================================================================

#include "CAAV5V6MmrInitSession.h"  

#include "CATIAV5Level.h"

// CATMecModUseItf
#include "CATIMmiPrtContainer.h"

// System Frameworks
#include "CATBoolean.h"
#include "CATUnicodeString.h"

// C++ Standard library
#include "iostream.h"


#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 

// CAAPLMClientAdapter.edu Framework
#include "CAAAdpCreateCloseSession.h"
#include "CAAOpenPLMComponent.h"

//ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

// CAT3DPhysicalRepInterfaces


#include "CATIPsiRepresentationLoadMode.h"

// CATPLMIdentificationAccess Framework
#include "CATIPLMComponent.h" 

// CATPLMComponentInterfaces
#include "CATPLMSessionServices.h"
#include "CATIPLMNavRepReference.h"

#else
//============================================== 
// V5 only
//============================================== 

// ObjectModelerBase Framework
#include "CATDocument.h"
#include "CATSessionServices.h"    
#include "CATSession.h"
#include "CATDocumentServices.h" 
#include "CATInit.h"

#endif


#ifdef CATIAR214
//============================================== 
// V6 only
//============================================== 
HRESULT CAAV5V6MmrInitSession(const char *  iRepository, 
    				          const char *  iServer, 
    					      const char *  iUser,
    				          const char * iPassword,
    					      const char * iRole,
						      const char* iStrPLMType,
   		                      const CATUnicodeString& iPLM_ExternalIDValue,
   		                      const CATUnicodeString& iV_versionValue,
						      CATOmbLifeCycleRootsBag &iBag,
                              CATIMmiPrtContainer *&opApplicativeContainer)	
{
  HRESULT rc = E_FAIL;
  
  //
  // Create a session with : repository, server, user, password, SecurityCtx
  //
  rc = ::CAAAdpCreateSession(iRepository, iServer, iUser, iPassword, iRole);
  if ( FAILED(rc) )
  {
	cout <<"   Error creating a session" << endl;
	return 1 ;
  }
  cout <<"   Create Session is OK" << endl;


  //
  // Load the Representation with the values of the identifiant set attributes 
  //	
  CATIPLMComponent * piPLMComponentOnPart = NULL;
  rc = ::CAAOpenPLMComponent(iStrPLMType, 
		                     iPLM_ExternalIDValue,
		                     iV_versionValue,
		                     IID_CATIPLMComponent,
		                     (void**)&piPLMComponentOnPart, 
							 iBag,
							 TRUE);

	if ( FAILED(rc) || ( NULL ==piPLMComponentOnPart))
	{
		cout <<"   Error in opening the Part" << endl;
		::CAAAdpCloseSession();
		return 1 ;
	}

	// Swap to Edit Mode
	CATIPsiRepresentationLoadMode_var spLoadModeOn3DShape = piPLMComponentOnPart;
	if (spLoadModeOn3DShape != NULL_var)
    rc = spLoadModeOn3DShape->ChangeLoadingMode(CATIPsiRepresentationLoadMode::EditMode);

	cout << "   " << iPLM_ExternalIDValue.ConvertToChar() << " is opened" << endl << endl;

	CATIPLMNavRepReference_var spRepRef = piPLMComponentOnPart;
    if (spRepRef == NULL_var)
      return 1;		
	
	piPLMComponentOnPart->Release();
	piPLMComponentOnPart = NULL;

	rc = spRepRef->RetrieveApplicativeContainer("CATPrtCont",IID_CATIMmiPrtContainer,(void **)&opApplicativeContainer);

	if (FAILED(rc) || (opApplicativeContainer))
		return 1;

	cout << "   The Part container has been retrieved"<< endl;

  return rc;
}
#else
//============================================== 
// V5 only
//============================================== 
HRESULT CAAV5V6MmrInitSession(char * iSessionName, 
	                      const CATUnicodeString& iStorageName,
						  CATDocument *& oNewDoc,
    				      CATIMmiPrtContainer *&opApplicativeContainer)
{
  HRESULT rc = E_FAIL;
  
  //
  // Create a session
  //
  CATSession *pSession = NULL;
  rc = Create_Session(iSessionName, pSession) ;

  if ( FAILED(rc) )
  {
	cout <<"   Error creating a session" << endl;
	return 1 ;
  }
  cout <<"   Create Session is OK" << endl;
 
  //
  // Load the input document
  //
  rc= CATDocumentServices::OpenDocument(iStorageName, oNewDoc) ;

  if( FAILED(rc) )
  {
    cout <<"Error in opening the document: " << iStorageName.ConvertToChar() << endl ;
    return 1;
  }
  cout <<"   " << iStorageName.ConvertToChar() << " is opened" << endl;

  CATInit *pDocAsInit = NULL;
  rc= oNewDoc->QueryInterface(IID_CATInit, (void**)&pDocAsInit) ;
  if( FAILED(rc) )
  {
    cout << "Error, the document does not implement CATInit"<< endl;
    return 1;
  }

   //
  // Get root container of the document
  //
  opApplicativeContainer = (CATIMmiPrtContainer*)pDocAsInit->GetRootContainer("CATIPrtContainer");

  pDocAsInit->Release();
  pDocAsInit = NULL ;

  if( NULL == opApplicativeContainer )
  {
    cout <<"Error, the root container is NULL" << endl;
    return 1;
  }
  return rc;

}
#endif

