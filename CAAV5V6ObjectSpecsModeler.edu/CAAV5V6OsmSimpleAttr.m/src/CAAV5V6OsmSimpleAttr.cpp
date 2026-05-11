// COPYRIGHT DASSAULT SYSTEMES 2012
//=============================================================================
// Abstract of Use Case "CAAV5V6OsmSimpleAttr":
// ---------------------------------------
//
// This sample illustrates fundamentally to retrieve a StartUp from an existing catalog,
// Instantiate it , valuate some attributes and retrieve the new values.
//
//
// The current UC refers to the following list of the StartUps defined in the catalog 
// CAAOsmCatalogSU.CATfct, which thus is its prerequisite
// This catalog is provided in the CAAV5V6ObjectSpecsModeler/CNext/resources/graphic folder,
// which on mkrtv is copied to the Workspace run time view
// Alternatively, user can execute the CAAOsmCatalogSU Use Case, to generate this CATfct
//
// Only these two StartUps will be referenced in this use case:
//
//		StartUp									Attribute
//		-------									---------
//
//		CAAOsmBook								Title
//												BookPublisher
//
//		CAAOsmNovel (a kind of CAAOsmBook)		Title
//												BookPublisher
//												Author
//												(list of) NovelChapter
//													
//
//
//=============================================================================
//  Steps
//

//  1- Creates a Product Representation Reference as Techno Rep in which to store the new features
//  2- Creates "Title" & "Author" Attributes  
//  3- Instantiates "CAAOsmNovel" , the instance is named Novel
//  4- Retrieves its "Author" attribute  ((own attribute)
//  5- Retrieves its "Author" attribute value  
// 6- Valuates its "Title" attribute (inherited attribute)
// 7- Retrieves its "Title" attribute value  
//
//=============================================================================
// How to execute :
//
//	For V6 environment
//   mkrun -c "CAAV5V6OsmSimpleAttr <Repository> <Server> <User> <Password> <SecurityCtx> <Environment>"  
//
//	 where    Repository	      : The name of the repository (or provider) 
//			  Server		      : The name and port of the server as name:port_number
//			  User		          : The user identifier
//            Password		      : The user password  
//			  SecurityCtx		  : A string representing the security context (Role.Organization.Project)
//						    		  Choose Role as Designer ( as the use case modifies the PLM Data)
//			  Environment	      : A PLM Environment containing a PRODUCT modeler customization
//
//	For V5 environment
//	  To run this program, you can use the command:
//        mkrun -c "CAAOsmSimpleAttr DocumentStorageName" 
//  where the "DocumentStorageName" is the entire pathname, name and .CATPart extension
//    under which the new document is to be stored. 

// Return code :
//   0 successful execution
//   1 execution failed
// 
//=============================================================================
//	Note: The Session creation and Save Services code is different for V5 and V6 environment.
//			The crux of this use case is to study how the V5 FeatureModeler scenario is done using
//			V6 APIs


// System Framework
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATString.h"

//FeatureModelerExt Framework
#include "CATFmFeatureFacade.h"
#include "CATFmContainerFacade.h"
#include "CATFmStartUpFacade.h"
#include "CATFmCredentials.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATFmFeatureModelerID.h"
#include "CATFmFeatureIterator.h"
#include "CATFmPointingFeatureIterator.h"

#include "CATIAV5Level.h"

// Other
#include <iostream.h>

//-------------------------------------------------------------------------
//	Include guards when the Framework is in V6 Environment
//-------------------------------------------------------------------------
#ifdef CATIAR214

//local Framework
#include "CAAV5V6FmExtCreateRepRef.h"     // to create the Rep ref

// ObjectModelerBase
#include "CATOmbLifeCycleRootsBag.h"

//CAT3DPhysicalRepInterfaces Framework
#include "CATIPsiRepresentationReference.h"  // interface on rep ref

// CATPLMIntegrationUse
#include "CATAdpSaver.h"

// CAAPLMClientAdapter.edu Framework
#include "CAAAdpCreateCloseSession.h"

#endif
/*--------------------------*/

//-------------------------------------------------------------------------
//	Include guards when the Framework is in V5 Environment
//-------------------------------------------------------------------------
#ifdef CATIAV5R23

// ObjectModelerBase Framework
#include "CATSessionServices.h"             // Create_Session and Delete_Session
#include "CATDocumentServices.h"            // New, SaveAs and Remove document
#include "CATInit.h"                        // GetRootContainer
#include "CATDocument.h"                    // Document
#include "CATSession.h"
#include "CATIContainer.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"                 // Instanciate, GetFather, GetName
#include "CATISpecAttrAccess.h"             // GetAttrKey, SetString, SetInteger,
//    SetSpecObject, GetString,
//    GetSpecObject, 
#include "CATISpecAttrKey.h"                // Result of GetAttrKey
#include "CATOsmSUHandler.h"

#endif
//------------------

//=======================================================================================

int main (int iArgc, char * iArgv[])
{ 
#ifdef CATIAV5R23

	/*--------------------------------------------------------------*/
	/* Open a Session:  this is a necessary step in a batch program */
	/*--------------------------------------------------------------*/

	char *pSessionName = "CAA2_Sample_Session";
	CATSession *pSession = NULL;
	HRESULT rc = ::Create_Session(pSessionName,
		pSession);
	if ((FAILED(rc)) || (NULL == pSession))
	{
		cout << "ERROR in creating session" << endl << flush;
		return 1;
	}

	/*-------------------------------------*/
	/* Create a new document for features. */
	/*-------------------------------------*/

	// We will work with a "CATPart" document. 

	CATDocument *pDoc = NULL;
	rc = CATDocumentServices::New("Part",
		pDoc);
	if (NULL != pDoc) cout << "New document created OK in V5 env" << endl << flush;
	else
	{
		cout << "ERROR in creating New document" << endl << flush;
		return 2;
	} 	

	/*----------------------------------------------*/
	/* Retrieve the root container of the document. */
	/*----------------------------------------------*/

	CATInit *piInitOnDoc = NULL;
	rc = pDoc -> QueryInterface(IID_CATInit,
		(void**) &piInitOnDoc);
	if (FAILED(rc)) 
	{
		cout << "ERROR in QueryInterface on CATInit for doc" << endl << flush;
		return 3;
	}

	const CATIdent idCATIContainer = "CATIContainer";
	CATIContainer *piRootContainer = NULL;
	piRootContainer = (CATIContainer*) piInitOnDoc -> GetRootContainer(idCATIContainer);
	piInitOnDoc -> Release();
	if (NULL == piRootContainer)
	{
		cout << "ERROR in GetRootContainer" << endl << flush;
		return 4;
	}
	//-------------------------------------------------------------------------------
	// - Build Client Credentials 
	//-------------------------------------------------------------------------------
	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials in V5 env" << endl;

	//Create container facade to work with
	CATFmContainerFacade MyContainerFacade(MyCredential,piRootContainer);

#endif

#ifdef CATIAR214

	//---------------------
	// - Checks arguments
	//---------------------

	if ( 7 != iArgc )
	{
		cout << endl;
		cout << "Usage: CAAV5V6OsmSimpleAttr <Repository> <Server> <User> <Password> <SecurityCtx> <Environment> " ;
		cout <<endl;
		return 1;
	}

	cout << "The CAAV5V6OsmSimpleAttr main program begins ...."<< endl << endl;

	//------------------------------------------------------------------
	// - Initializes the PLM session 
	//------------------------------------------------------------------
	HRESULT rc = ::CAAAdpCreateSession(iArgv[1], iArgv[2], iArgv[3], iArgv[4],iArgv[5]);
	if (FAILED(rc))	 return 1;   

	cout << "   PLM session initialized with the following connection parameters" << endl;
	cout << "      Repository=" << iArgv[1] << endl;
	cout << "      Server="     << iArgv[2] << endl;
	cout << "      UserID="     << iArgv[3] << endl;
	cout << "      UserPasswd=" << iArgv[4] << endl;
	cout << "      SecurityCtx=" << iArgv[5] << endl;

	//--------------------------------------------------------------------
	// - Creates a Credential Object
	// -------------------------------------------------------------------
	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAV5V6FmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials" << endl;

	//------------------------------------------------------------------
	// - Creates a Product Representation Reference
	//------------------------------------------------------------------
	CATString EnvToUse = iArgv[6];
	CATString Repository = iArgv[1];
	CATUnicodeString NameAndTypeofContainer = "CAAFmExtAppliCont" ;
	CATIPsiRepresentationReference * pPsiCreatedRepRef= NULL;
	CATBaseUnknown * pContainer = NULL ;
	rc = ::CAAV5V6FmExtCreateRepRef(MyCredential, EnvToUse,Repository,NameAndTypeofContainer,NameAndTypeofContainer,
		IID_CATIPsiRepresentationReference,(void**) &pPsiCreatedRepRef, &pContainer);
	if (FAILED(rc) || (NULL==pPsiCreatedRepRef) || (NULL==pContainer) ) return 1;
	cout <<"   The Product Representation Reference is created" << endl;

	// Insert component that is loaded in session, in BAG
	CATOmbLifeCycleRootsBag Bag;
	Bag.InsertRoot(pPsiCreatedRepRef);

	//Create container facade to work with
	CATFmContainerFacade MyContainerFacade(MyCredential,pContainer);

	pPsiCreatedRepRef->Release();
	pPsiCreatedRepRef = NULL;

#endif

	//--------------------------------------------------------------------------------
	// 1- Creates Attribute Names
	//--------------------------------------------------------------------------------
	CATFmAttributeName TitleAttrName("Title");
	cout << "   Retrieved the Name to the attribute Title" << endl;

	CATFmAttributeName AuthorAttrName("Author");
	cout << "   Retrieved the Name to the attribute Author" << endl;
	//------------------------------------------------------------------
	// 2- Instantiates "CAAOsmNovel" , the instance is named Novel
	//------------------------------------------------------------------
	CATUnicodeString MyNovelStartUpType("`CAAOsmNovel`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade NovelStartUpFacade(MyCredential, MyNovelStartUpType);
	cout << "CAAOsmNovel StartUp Facade retrieved OK" << endl << flush;

	CATFmFeatureFacade oFeatFacadeOnNovel(MyCredential);
	rc = NovelStartUpFacade.InstantiateIn(MyContainerFacade,oFeatFacadeOnNovel);
	if (FAILED(rc)) return 1;

	cout << "   The Novel feature is created" << endl;

	//------------------------------------------------------------------
	// 3- Valuates the "Author" attribute of the Novel feature
	//------------------------------------------------------------------
	CATUnicodeString AuthorOfBook = "Dumas";
	CATFmAttributeValue AuthorAsFmValue(AuthorOfBook);
	rc =  oFeatFacadeOnNovel.SetValue(AuthorAttrName,AuthorAsFmValue);
	if (FAILED(rc)) return 1;

	cout << "   Valuated the Author attribute of the Novel" << endl;

	//-------------------------------------------------------------------------------------
	// 4- Retrieves "Author" attribute value of the Novel feature
	//-------------------------------------------------------------------------------------
	CATFmAttributeValue RetrievedValueAsFmValue;
	rc = oFeatFacadeOnNovel.GetValue(AuthorAttrName,RetrievedValueAsFmValue); 
	if (SUCCEEDED(rc))
	{
		CATUnicodeString oStrAuthor ;
		AuthorAsFmValue.GetString(oStrAuthor);

		if ( RetrievedValueAsFmValue==AuthorAsFmValue )
		{
			cout << "   Confirmation on the Valuation is OK" << endl;
		} else rc = E_FAIL ; 

	}
	if (FAILED(rc)) return 1;

	//------------------------------------------------------------------
	// 5- Valuates the "Title" attribute of the Novel feature
	//------------------------------------------------------------------
	CATUnicodeString TheThreeMusketeers = "The Three Musketeers";
	CATFmAttributeValue TitleAsFmValue(TheThreeMusketeers);
	rc =  oFeatFacadeOnNovel.SetValue(TitleAttrName,TitleAsFmValue);
	if (FAILED(rc)) return 1;

	cout << "   Valuated the Title attribute of the Novel" << endl;

	//-------------------------------------------------------------------------------------
	// 6- Retrieves "Title" attribute value of the Novel feature
	//-------------------------------------------------------------------------------------
	rc = oFeatFacadeOnNovel.GetValue(TitleAttrName,RetrievedValueAsFmValue); 
	if (SUCCEEDED(rc))
	{
		CATUnicodeString oStrTitle ;
		TitleAsFmValue.GetString(oStrTitle);

		if ( RetrievedValueAsFmValue==TitleAsFmValue )
		{
			cout << "   Confirmation on the Valuation is OK" << endl;
		} else rc = E_FAIL ; 

	}
	if (FAILED(rc)) return 1;


#ifdef CATIAR214
	//-------------------------------------------------------------------------------------
	// - Saves the session
	//-------------------------------------------------------------------------------------
	CATAdpSaver saver;
	rc = saver.Save();
	if ( FAILED(rc)  ) return 1;
	cout <<"   Save is successful " << endl;

	// Unload components from session
	Bag.RemoveAll();

	pContainer->Release();
	pContainer = NULL ;
	//--------------------------------------------------------------------------------------
	// - Closes the session
	//--------------------------------------------------------------------------------------
	rc = ::CAAAdpCloseSession();
	if (FAILED(rc) ) return 1;

	cout <<"   PLM session closed" << endl;
	cout << endl << "The CAAV5V6OsmSimpleAttr main program ends ...."<< endl << endl;

	return 0;
#endif

#ifdef CATIAV5R23

	// release the pointer on the container
	piRootContainer -> Release();
	piRootContainer = NULL;
	/*--------------------------------------------------------------------------*/
	/*  Save and remove the document and end the session when in V5 environment */
	/*--------------------------------------------------------------------------*/

	// @CSC-Filter UNER 
	rc = CATDocumentServices::SaveAs(*pDoc,
		iArgv[2]);
	if (FAILED(rc))
	{
		cout << "ERROR in saving document" << endl << flush;
		return 9;
	}

	rc = CATDocumentServices::Remove (*pDoc);
	if (FAILED(rc)) 
	{
		cout << "ERROR in removing document" << endl << flush;
		return 10;
	}

	// Delete session

	rc = ::Delete_Session(pSessionName);
	if (FAILED(rc))
	{
		cout << "ERROR in deleting session" << endl << flush;
		return 11;
	}

	return 0;
#endif
}
