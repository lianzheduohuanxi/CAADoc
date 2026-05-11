// COPYRIGHT DASSAULT SYSTEMES 2010
//===================================================================
// Abstract of Use Case "CAAV5V6FmExtFeatModelerAPIIntroUse" 
//===================================================================
//
// Mission: The UC is an introduction to the Feature Modeler Facade, Credentials and Attribute classes, their
//          most commonly invoked APIs and their inter-relationship.
//          The facade and the attributes classes are key to realizing a secured access to the	feature model. 
//          The UC primarily involves creating the Credentials, Instantiating a Feature and subsequently 
//          setting and retrieving its Attribute values
//
//  Steps
//
// 1- Instantiate the StartUp "CAAOsmNovel"
//      1-1- Instantiate the "CAAOsmNovel" StartUp Facade 
//      1-2- Instantiate "CAAOsmNovel" feature 
// 2- Set an Author to the Novel
//      2-1- Define the "Author" Attribute Key
//      2-2- Create a CATFmAttributeValue equivalent of the Author attirbute value
//      2-3- Set a value for the attribute "Author" of the feature Novel
// 3- Retrieve the Author of the Novel
//      3-1- Retrieve the Author of a Novel, as a CATFmAttributeValue equivalent
//      3-2- Retrieve the Author as a string from its CATFmAttributeValue equivalent
// 6- Saves in repository
// 7- Closes the Session
//
//==================================================================================================
//
// The current UC refers to the following list of the StartUps 
//
//		CAAOsmCatalogSU.CATfct
//
//		StartUp									Attribute
//		-------									---------
//		CAAOsmBook								Title (string)
//												BookPublisher (specObject)
//
//		CAAOsmNovel (derived from CAAOsmBook)   Author (string)
//												NovelChapter (Component)
//
// These catalogs exist in the CAAV5V6FeatureModelerExt.edu/CNext/resources/graphic folder
// which on mkrtv is copied to the Workspace run time view
// 
//==================================================================================================
//  Note: This Use-Case is compatible in V5 as well as V6 environment. Thus the code in #ifdef
//		  represents the difference in the respective functionality of V5 and V6 for E.g. Session
//		  creation, Applicative Containers concept, Save Services etc.
//		  The code outside the #ifdef is the common code for V5 and V6 and represents the backported
//		  functionalities of V6 to V5.
//=============================================================================
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAV5V6FmExtFeatModelerAPIIntroUse DocumentStorageName" 
//  where the "DocumentStorageName" is the entire pathname, name and .CATPart extension
//    under which the new document is to be stored. 
//
//=============================================================================



// System Framework
#include "CATUnicodeString.h"
#include "CATFmFeatureFacade.h"
#include "CATFmContainerFacade.h"
#include "CATFmStartUpFacade.h"
#include "CATFmCredentials.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATFmFeatureModelerID.h"
#include "CATBaseUnknown.h"
#include "CATIAV5Level.h"

// Other
#include <iostream.h>


//-------------------------------------------------------------------------
//	Include guards when the Framework is in V6 Environment
//-------------------------------------------------------------------------
#ifdef CATIAR214

//local Framework
#include "CAAV5V6FmExtCreateRepRef.h"     // to create the Rep ref

//PLMSessionInterfaces Framework
#include "CATIPsiRepresentationReference.h"  // interface on rep ref

// CAAPLMClientAdapter.edu Framework
#include "CAAAdpCreateCloseSession.h"

// CATPLMIntegrationUse
#include "CATAdpSaver.h"

//ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

//System Framework
#include "CATString.h"

#include "iostream.h"     

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
	if ((SUCCEEDED(rc)) && (NULL != pSession))
		cout << "Session created OK" << endl << flush;
	else return 1;

	/*-------------------------------------*/
	/* Create a new document for features. */
	/*-------------------------------------*/

	// We will work with a "CATPart" document. 

	CATDocument *pDoc = NULL;
	rc = CATDocumentServices::New("Part",
		pDoc);
	if (NULL != pDoc) cout << "New document created OK" << endl << flush;
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
//------------------------------------------------------------------
//3- Build Credentials to access the catalog "CAAOsmCatalogSU"
//------------------------------------------------------------------
    
	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
    rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials" << endl;

//Create container facade to work with
	CATFmContainerFacade ContFacade(MyCredential,piRootContainer);

#endif

#ifdef CATIAR214

//---------------------
// 1- Checks arguments
//---------------------
	if ( 7 != iArgc )
	{
		cout << endl;
		cout << "Usage: CAAV5V6FmExtFeatModelerAPIIntroUse <Repository> <Server> <User> <Password> <SecurityCtx> <Environment> " ;
		cout <<endl;
		return 1;
	}
	cout << "The CAAV5V6FmExtFeatModelerAPIIntroUse main program begins in V6 env...."<< endl << endl;
  
//------------------------------------------------------------------
//2 - Initializes the PLM session 
//------------------------------------------------------------------
	HRESULT rc = ::CAAAdpCreateSession(iArgv[1], iArgv[2], iArgv[3], iArgv[4],iArgv[5]);
	if (FAILED(rc))	 return 1;   
		
	cout << "   PLM session initialized with the following connection parameters" << endl;
	cout << "      Repository=" << iArgv[1] << endl;
	cout << "      Server="     << iArgv[2] << endl;
	cout << "      UserID="     << iArgv[3] << endl;
	cout << "      UserPasswd=" << iArgv[4] << endl;
	cout << "      SecurityCtx="<< iArgv[5] << endl;

//--------------------------------------------------------------------------------------------------
// 3- Build Credentials to access features in the catalog CAAOsmCatalogSU 
//--------------------------------------------------------------------------------------------------
	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
    rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials" << endl;

//--------------------------------------------------------------
// 4- Create a new Product representation reference (Techno Rep)
//--------------------------------------------------------------
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
	CATFmContainerFacade ContFacade(MyCredential,pContainer);

    pPsiCreatedRepRef->Release();
	pPsiCreatedRepRef = NULL;

#endif


//------------------------------------------------------------
// 6- Instantiate the StartUp "CAAOsmNovel"
//------------------------------------------------------------
	// 6-1- Instantiate the "CAAOsmNovel" StartUp Facade 
	CATUnicodeString NovelStartUpType("`CAAOsmNovel`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade NovelStartUpFacade(MyCredential,NovelStartUpType);

	// 6-2- Instantiate "CAAOsmNovel" feature 
	CATFmFeatureFacade FeatFacadeOnNovelFeat(MyCredential);
	rc = NovelStartUpFacade.InstantiateIn(ContFacade,FeatFacadeOnNovelFeat);
	if (FAILED(rc)) return 1;
	cout << "   Success in instantiating the CAAOsmNovel feature"<<endl;

// ---------------------------------
// 7- Set an Author to the Novel
// ---------------------------------
    // 7-1- Define the "Author" Attribute Key
    CATFmAttributeName AuthorAttrName("Author");

    // 7-2- Create a CATFmAttributeValue equivalent of the Author attirbute value
    CATFmAttributeValue AuthorAttrValue;
    CATUnicodeString strAuthor("William Shakespeare");
    AuthorAttrValue.SetString(strAuthor);

    // 7-3- Set a value for the attribute "Author" of the feature Novel
    rc = FeatFacadeOnNovelFeat.SetValue(AuthorAttrName,AuthorAttrValue);
    if (FAILED(rc)) return 1;
    cout << "   The Novel feature is set with an Author" << endl;

// -------------------------------------
// 8- Retrieve the Author of the Novel
// -------------------------------------
    // 8-1- Retrieve the Author of a Novel, as a CATFmAttributeValue equivalent
    CATFmAttributeValue RetrievedAuthorAsAttrValue;
    rc = FeatFacadeOnNovelFeat.GetValue(AuthorAttrName,RetrievedAuthorAsAttrValue);
    if (rc != S_OK) return 1; 
 
    // 8-2- Retrieve the Author as a string from its CATFmAttributeValue equivalent
    CATUnicodeString strAuthorRetrieved;
	rc = RetrievedAuthorAsAttrValue.GetString(strAuthorRetrieved);
	if (FAILED(rc)) return 1;
    cout << "   The Novel's author retrieved is " << strAuthorRetrieved.ConvertToChar() << endl;

#ifdef CATIAR214

//---------------------------------------------------------------------
// 11- Saves in repository
//---------------------------------------------------------------------
	CATAdpSaver saver;
    rc = saver.Save();
	if ( FAILED(rc)  ) return 1;
	cout <<"   Save is successful " << endl;

	pContainer->Release();
	pContainer= NULL ;

	Bag.RemoveAll();

//------------------------------------------------------------------
// 12- Closes the session
//------------------------------------------------------------------
	rc = ::CAAAdpCloseSession();
	if (FAILED(rc) ) return 1;
	cout <<"   Close is successful " << endl;
	cout << endl << "   The CAAV5V6FmExtFeatModelerAPIIntroUse main program ends ...."<< endl << endl;
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
			iArgv[1]);
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

