// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Abstract of Use Case "CAAV5V6OsmReferencedAttr":
// -------------------------------------------
//
// This Use Case fundamentally illustrates the salient features of a "referenced" feature.
//
// The current UC refers to the following list of the StartUps defined in the catalog 
// CAAOsmCatalogSU.CATfct, which thus is its prerequisite
// This catalog is provided in the CAAFeatureModelerExt.edu/CNext/resources/graphic folder,
// which on mkrtv is copied to the Workspace run time view
// Alternatively, user can execute the CAAOsmCatalogSU Use Case, to generate this CATfct
//
//		StartUp									Attribute
//		-------									---------
//		CAAOsmPublisher							PublisherName
//												PublisherAddress
//
//
//		CAAOsmBook								Title
//												BookPublisher  (specobject)
//
//		CAAOsmNovel (a kind of CAAOsmBook)		Title
//												BookPublisher   (specobject )
//												Author
//												NovelChapter    (list of component)
//
//		CAAOsmChapter                   		ChapterTitle
//												FirstPage    
//												LastPage
//												 
//=============================================================================
//  Steps :

//	The Session creation and Save Services code is different for V5 and V6 environment.
//	The crux of this use case is to study how the V5 FeatureModeler scenario is done using
//	V6 APIs

//   1- Retrieve Keys to Attributes associated with the features to be instantiated
//		1-1- Retrieve a key to the "PublisherName" attribute (string)
//		1-2- Retrieve a key to the "PublisherAddress" attribute (string)
//		1-3- Retrieve a key to the "BookPublisher" attribute (specobject)
//		1-4- Retrieve a key to the "NovelChapter" attribute (component)
//   2- Illustrate a single "reference" feature could be referred to by several referencing features
//		2-1- Instantiate CAAOsmPublisher (Publisher)
//		2-2- Valuate the Name and Adress attributes of Publisher
//		2-3- Instantiate CAAOsmNovel (Novel1)
//		2-4- Set Publisher as a reference to Novel1 
//		2-5- Instantiate CAAOsmNovel (Novel2)
//		2-6- Set Publisher as a reference to Novel2. 
//	  3- Illustrate the notion of "father" of a referenced feature does not exist
//    4- Illustrate that a referenced feature is not dead after the last dereferencing
//		4-1- Delink the reference to Publisher by Novel2
//		4-2- Delete Novel1 (Referencing feature)
//		4-3- Build a reference to Publisher from Novel2 
//
//=============================================================================
// How to execute :
//
//	For V6
//   mkrun -c "CAAV5V6OsmReferencedAttr <Repository> <Server> <User> <Password> <SecurityCtx> <Environment> "  
//
//	 where    Repository	      : The name of the repository (or provider) 
//			  Server		      : The name and port of the server as name:port_number
//			  User		          : The user identifier
//            Password		      : The user password  
//			  SecurityCtx		  : A string representing the security context (Role.Organization.Project)
//						    		  Choose Role as Designer ( as the use case modifies the PLM Data)
//			  Environment	      : A PLM Environment containing a PRODUCT modeler customization
//
// Return code :
//   0 successful execution
//   1 execution failed

//	For V5
//	Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAV5V6OsmReferencedAttr DocumentStorageName" 
//  where the "DocumentStorageName" is the entire pathname, name and .CATPart extension
//    under which the new document is to be stored. 
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

//CAT3DPhysicalRepInterfaces Framework 
#include "CATIPsiRepresentationReference.h"  // interface on rep ref

//ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

// CATPLMIntegrationUse
#include "CATAdpSaver.h"

// CAAPLMClientAdapter.edu Framework
#include "CAAAdpCreatePartRepresentation.h"     // to create the Rep ref
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

//====================================================================

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
//-------------------------------------------------------------------------------------------------
//  Creating a Credential Object which authorizes client to handle the "CAAFmExtPoint2D" feature
// ------------------------------------------------------------------------------------------------
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
// 1- Checks arguments
//---------------------
 	if ( 7 != iArgc )
	{
		cout << endl;
		cout << "Usage: CAAV5V6OsmReferencedAttr <Repository> <Server> <User> <Password> <SecurityCtx> <Environment> " ;
		cout <<endl;
		return 1;
	}
	cout << "The CAAV5V6OsmReferencedAttr main program begins ...."<< endl << endl;
  
//------------------------------------------------------------------
// 2 - Initializes the PLM session 
//------------------------------------------------------------------
	HRESULT rc = ::CAAAdpCreateSession(iArgv[1], iArgv[2], iArgv[3], iArgv[4],iArgv[5]);
	if (FAILED(rc))	return 1;
	cout << "   PLM session initialized with the following connection parameters" << endl;
	cout << "      Repository=" << iArgv[1] << endl;
	cout << "      Server="     << iArgv[2] << endl;
	cout << "      UserID="     << iArgv[3] << endl;
	cout << "      UserPasswd=" << iArgv[4] << endl;
	cout << "      SecurityCtx=" << iArgv[5] << endl;

//------------------------------------------------------------------
// 3- Build Credentials to access the catalog "CAAOsmCatalogSU"
//------------------------------------------------------------------
    CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
    rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials" << endl;
	
//------------------------------------------------------------------
// 4- Creates a Product Representation Reference (Techno Rep)
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
//1- Retrieve Keys to Attributes associated with the features to be instantiated
//--------------------------------------------------------------------------------
	// 1-1- Retrieve a key to the "PublisherName" attribute (string)
	CATFmAttributeName PublshrNameAttrKey("PublisherName");

	// 1-2- Retrieve a key to the "PublisherAddress" attribute (string)
	CATFmAttributeName PublshrAddrAttrKey("PublisherAddress");

	// 1-3- Retrieve a key to the "BookPublisher" attribute (tk_specObject)
	CATFmAttributeName BookPublshrAttrKey("BookPublisher");

	// 1-4- Retrieve a key to the "NovelChapter" attribute (tk_component)
	CATFmAttributeName ChptrAttrKey("NovelChapter");

//---------------------------------------------------------------------------------------------------
// 2- Illustrate a single "reference" feature could be referred to by several "referencing" features
//---------------------------------------------------------------------------------------------------
	// 2-1- Instantiate Publisher (PublisherInst)
	CATUnicodeString PublisherStartUpType("`CAAOsmPublisher`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade PublisherStartUpFacade(MyCredential, PublisherStartUpType);

	CATFmFeatureFacade oFeatFacadeOnPublisher(MyCredential);
	rc = PublisherStartUpFacade.InstantiateIn(MyContainerFacade,oFeatFacadeOnPublisher);
	if (FAILED(rc)) return 1;
		
	cout << "   CAAOsmPublisher SU Instance created OK" << endl;

	// 2-2- Valuate Name & Adress attributes of the new Publisher
	CATUnicodeString strPublishrName("Collins Press");
	CATFmAttributeValue AttrAsFmValue(strPublishrName);
	rc =  oFeatFacadeOnPublisher.SetValue(PublshrNameAttrKey,AttrAsFmValue);
	
	CATUnicodeString strPublishrAddr("London");
	AttrAsFmValue.SetString(strPublishrAddr);
	rc =  oFeatFacadeOnPublisher.SetValue(PublshrAddrAttrKey,AttrAsFmValue);
	if (FAILED(rc)) return 1;
	cout << "   Success in setting the Name & Adress of CAAOsmPublisher1 " << endl;

	// 2-3- Instantiate Novel1
	CATUnicodeString MyNovelStartUpType("`CAAOsmNovel`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade NovelStartUpFacade(MyCredential, MyNovelStartUpType);
	CATFmFeatureFacade oFeatFacadeOnNovel1(MyCredential);
	rc = NovelStartUpFacade.InstantiateIn(MyContainerFacade,oFeatFacadeOnNovel1);
	if (FAILED(rc))	return 1;
	cout << "   CAAOsmNovel1 SU Instance created OK" << endl;
	
	// 2-4- Set Publisher as a reference from Novel1
	AttrAsFmValue.SetFeature(oFeatFacadeOnPublisher);
	rc = oFeatFacadeOnNovel1.SetValue(BookPublshrAttrKey,AttrAsFmValue);

	// 2-5- Instantiate the Novel2 
	CATFmFeatureFacade oFeatFacadeOnNovel2(MyCredential);
	rc = NovelStartUpFacade.InstantiateIn(MyContainerFacade,oFeatFacadeOnNovel2);
	if (FAILED(rc))	return 1;
	cout << "   CAAOsmNovel2 SU Instance created OK" << endl;
	
	// 2-6- Set Publisher as a reference from Novel2
	AttrAsFmValue.SetFeature(oFeatFacadeOnPublisher);
	rc = oFeatFacadeOnNovel2.SetValue(BookPublshrAttrKey,AttrAsFmValue);
	if (FAILED(rc))	return 1;
	cout << "   Success in setting CAAOsmPublisher as a referenced feature to more than one referencing features" << endl;

//-----------------------------------------------------------------------------------------------------------
// 3- Illustrate the notion of "father" of a referenced feature does not exist
//-----------------------------------------------------------------------------------------------------------
	rc = oFeatFacadeOnPublisher.GetParentFeature(AttrAsFmValue);
	if (SUCCEEDED(rc))
	{
		CATFmFeatureFacade FeatFacadeOnParent;
        AttrAsFmValue.GetFeature(FeatFacadeOnParent);
 
	    CATBaseUnknown_var Parent = FeatFacadeOnParent.GetFeature();
		if ( NULL_var !=  Parent ) rc= E_FAIL ; else rc= S_OK ;
	}

	if FAILED(rc) return 1 ;
    cout << "   Published is without parent" << endl;

//-----------------------------------------------------------------------------------------------------------
// 4- Illustrate that a referenced feature is not dead after the last dereferencing  
//-----------------------------------------------------------------------------------------------------------
	// 4-1- Delink the reference to Publisher by Novel2
    AttrAsFmValue.SetFeature(NULL);
	rc =  oFeatFacadeOnNovel2.SetValue(BookPublshrAttrKey,AttrAsFmValue);
	if (FAILED(rc))	return 1;
	cout << "   Success in dereferencing Publisher by Novel2" << endl;
	
	// 4-2- Delete Novel1 (Referencing feature)
	rc = oFeatFacadeOnNovel1.DeleteSelf();
	if (FAILED(rc))	return 1;

	// 4-3- Build a reference to Publisher from Novel2
	AttrAsFmValue.SetFeature(oFeatFacadeOnPublisher);
	rc = oFeatFacadeOnNovel2.SetValue(BookPublshrAttrKey,AttrAsFmValue);
	if (FAILED(rc))	return 1; 
	cout << "   Referenced feature PublisherInst exists though referencing feature Novel1 deleted." << endl;
	cout << "   Success in setting a reference to Publisher from Novel2" << endl;
    
#ifdef CATIAR214
//---------------------------------------------------------------------
// - Saves the session
//---------------------------------------------------------------------

	CATAdpSaver saver;
    rc = saver.Save();
    if (FAILED(rc))	return 1;
	cout <<"   Save is successful " << endl;

	// Unload components from session
	Bag.RemoveAll();

	pContainer->Release();
	pContainer = NULL;
//------------------------------------------------------------------
// - Closes the session
//------------------------------------------------------------------
	rc = ::CAAAdpCloseSession();
	if (FAILED(rc) ) return 1;
	cout <<"   PLM session closed" << endl;
	cout << endl << "The CAAV5V6OsmReferencedAttr main program ends ...."<< endl << endl;
	return 0;

#endif

#ifdef CATIAV5R23
/*--------------------------------------------------------------------------*/
/*  Save and remove the document and end the session when in V5 environment */
/*--------------------------------------------------------------------------*/

		piRootContainer->Release();
		piRootContainer = NULL;

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
