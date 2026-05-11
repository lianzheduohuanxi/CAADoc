// COPYRIGHT DASSAULT SYSTEMES 2009
//===============================================
// Abstract of Use Case "CAAV5V6FmExtInstantiation"
// ----------------------------------------------
//	The Use Case illustrates instantiating a Novel (feature) from its StartUp (CAAOsmNovel)
//	The new Novel instance, is then further instantiated to create another new Novel instance
//	Then, it instantiates a Chapter and aggregates it under the Novel instance
//  Lastly you learn how to use the same StartUp facade to create 2 kinds of features.
//
//=============================================================================
//  Steps :
//
//   1- Instantiate "Novel" from its "CAAOsmNovel" StartUp
//		1-1- Create a Facade to the Novel StartUp
//		1-2- Instantiate "Novel" from its StartUp
//	 2- Instantiate "Novel" from the new Novel instance, created in the previous step
//   3- Instantiate a "Chapter" and aggregate it under a "Novel" instance
//			3-1- Create a Facade on the Chapter StartUp
//			3-2- Create a key to a Novel attribute, of type "tk_Component" 
//			3-3- Instantiate the Chapter. 
//               The new Instance is appended to the list of Components under the Novel
//   4- Binding a StartUp facade to another StartUp's latetype
//   Saves the Session
//   Closes the Session
//
//=============================================================================
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAV5V6FmExtInstantiation DocumentStorageName" 
//  where the "DocumentStorageName" is the entire pathname, name and .CATPart extension
//    under which the new document is to be stored. 
//
// Return code :
//   0 successful execution
//   1 execution failed
// 
//=============================================================================
//  Note: This Use-Case is compatible in V5 as well as V6 environment. Thus the code in #ifdef
//		  represents the difference in the respective functionality of V5 and V6 for E.g. Session
//		  creation, Applicative Containers concept, Save Services etc.
//		  The code outside the #ifdef is the common code for V5 and V6 and represents the backported
//		  functionalities of V6 to V5.

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

//ObjectModelerBase Framework
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

//=================================================================
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
//-------------------------------------------------------------------------------
// 3- Build Client Credentials 
//-------------------------------------------------------------------------------
	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
    rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials" << endl;
		
	//Create container facade to work with
	CATFmContainerFacade MyContFacade(MyCredential,piRootContainer);


#endif

#ifdef CATIAR214

//---------------------
// 1- Checks arguments
//---------------------
	if ( 7 != iArgc )
	{
		cout << endl;
		cout << "Usage: CAAV5V6FmExtInstantiation <Repository> <Server> <User> <Password> <SecurityCtx> <Environment> " ;
		cout <<endl;
		return 1;
	}
	cout << "The CAAV5V6FmExtInstantiation main program begins in V6 env...."<< endl << endl;
  
//------------------------------------------------------------------
// 2 - Initializes the PLM session 
//------------------------------------------------------------------
	HRESULT rc = ::CAAAdpCreateSession(iArgv[1], iArgv[2], iArgv[3], iArgv[4],iArgv[5]);
	if (FAILED(rc))	 return 1;   
		
	cout << "   PLM session initialized with the following connection parameters" << endl;
	cout << "      Repository=" << iArgv[1] << endl;
	cout << "      Server="     << iArgv[2] << endl;
	cout << "      UserID="     << iArgv[3] << endl;
	cout << "      UserPasswd=" << iArgv[4] << endl;
	cout << "      SecurityCtx="<< iArgv[5] << endl;

//-------------------------------------------------------------------------------
// 3- Build Client Credentials 
//-------------------------------------------------------------------------------
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
	CATFmContainerFacade MyContFacade(MyCredential,pContainer);

    pPsiCreatedRepRef->Release();
	pPsiCreatedRepRef = NULL;

#endif
  
//--------------------------------------------------------------
// 1- Instantiate a Novel feature from its "CAAOsmNovel" StartUp
//--------------------------------------------------------------
	// 1-1- Create a Novel StartUp Facade
	CATUnicodeString MyStartUpType("`CAAOsmNovel`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade MyStartUpNovelFacade(MyCredential,MyStartUpType);

	// 1-2- Instantiate a Novel Feature from its "CAAOsmNovel" StartUp
	CATFmFeatureFacade oInstanceNovelFromStartUp(MyCredential);
	rc = MyStartUpNovelFacade.InstantiateIn(MyContFacade,oInstanceNovelFromStartUp);
	if (FAILED(rc)) return 1;

	CATUnicodeString NovelInstFromSUName;
	rc = oInstanceNovelFromStartUp.GetDisplayName(NovelInstFromSUName);
	if (FAILED(rc)) return 1;
	cout << "   Success in instantiating a Novel " << NovelInstFromSUName.ConvertToChar() << " from its CAAOsmNovel StartUp" << endl;

//-----------------------------------------------------------------------------------------
// 2- Instantiate a Novel feature, with the Novel feature created above, held as reference
//-----------------------------------------------------------------------------------------
	CATFmAttributeValue AttrValue;
	rc = oInstanceNovelFromStartUp.InstantiateIn(MyContFacade,AttrValue);
	if (FAILED(rc)) return 1;
    CATFmFeatureFacade oInstanceNovelFromFeature(MyCredential,AttrValue);

	CATUnicodeString NovelInstFromFeatName;
	rc = oInstanceNovelFromFeature.GetDisplayName(NovelInstFromFeatName);
	if (FAILED(rc)) return 1;
	cout << "   Success in instantiating a Novel feature " << NovelInstFromFeatName.ConvertToChar() << " from an existing Novel feature" << endl;

//---------------------------------------------------------
// 3- Instantiate a Chapter as an aggregate under the Novel
//---------------------------------------------------------
	// 3-1- Create a Chapter StartUp Facade
	CATUnicodeString MyChapterStartUpType("`CAAOsmChapter`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade MyStartUpChapterFacade(MyCredential,MyChapterStartUpType);

	// 3-2- Create a key to the Novel attribute of type "tk_Component"
	CATFmAttributeName MyKeyNovelChapter("NovelChapter");

	// 3-3- Instantiate a Chapter. The new Instance is appended to the list of Components under the Novel
	CATFmFeatureFacade oFeatFacadeOnChapter(MyCredential);		
	rc = MyStartUpChapterFacade.InstantiateUnder (MyContFacade,oInstanceNovelFromStartUp,MyKeyNovelChapter,oFeatFacadeOnChapter); 
	if (FAILED(rc)) return 1;

	CATUnicodeString ChptInstName;
	rc = oFeatFacadeOnChapter.GetDisplayName(ChptInstName);
    if (FAILED(rc)) return 1;
    cout << "   Success in instantiating a Chapter " << ChptInstName.ConvertToChar()  << " aggregated under a Novel " 
		 << NovelInstFromSUName.ConvertToChar()   << endl;

//---------------------------------------------------------
// 4- Binding a StartUp facade to another StartUp's latetype
//---------------------------------------------------------
    rc = MyStartUpChapterFacade.BindTo("`CAAOsmPublisher`@`CAAOsmCatalogSU.CATfct`");
	if (FAILED(rc)) return 1;
	cout << "   Success in changing the StartUp latetype" <<endl;

    CATFmFeatureFacade oFeatFacadeOnPublisher(MyCredential);
	rc = MyStartUpChapterFacade.InstantiateIn(MyContFacade,oFeatFacadeOnPublisher);
	if (FAILED(rc)) return 1;

	rc = oFeatFacadeOnPublisher.GetDisplayName(ChptInstName);
	if (FAILED(rc)) return 1;
    cout << "   Success in instantiating a Publisher " << ChptInstName.ConvertToChar()  << endl;

#ifdef CATIAR214
//---------------------------------------------------------------------
// - Saves the Session
//---------------------------------------------------------------------
	CATAdpSaver saver;
    rc = saver.Save();
	if ( FAILED(rc)  ) return 1;
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
		
	cout <<"   Close is successful " << endl;
	cout << endl << "The CAAV5V6FmExtInstantiation main program ends ...."<< endl << endl;
	
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
