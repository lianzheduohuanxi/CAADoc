// COPYRIGHT DASSAULT SYSTEMES 2010
//=============================================================================
// Abstract of Use Case "CAAV5V6FmExtFeatNamingAndBasicSkill":
// ----------------------------------------------
// The objective of the current UC is for an end-user to gain a better understanding
// of a StartUp and Feature default Naming.
// 
// The UC refers to features defined in the Catalog "CAAOsmCatalogSU"
// An extract of the contents of the CAAOsmCatalogSU.osm referred by this UC follows

/*
document `CAAFmExtElementCatalog.CATfct` {
container RootCont #root {
feature CAAOsmPublisher #startup {
string PublisherAddress
string PublisherName
}
feature CAAOsmChapter #startup {
string ChapterTitle
int FirstPage
int LastPage
}
feature CAAOsmBook #startup {
specobject BookPublisher
component CAAOsmBarCode
string Title
}
feature CAAOsmNovel CAAOsmBook #startup #inheritability(caa) {
string Author
component NovelChapter #list
}
feature CAAOsmLibrary #startup #isa(CAAFmExtLibrary) {
}
*/

//=============================================================================
//  Steps
//

// 1- Retrieving the StartUp Facade Types
// 1-1- Retrieve Type of a StartUp Facade, whose associated StartUp has a #isa facet
// 1-2- Retrieve Type of a derived StartUp Facade, whose associated StartUp is without a #isa facet
// 1-3- Retrieve Type of a StartUp Facade, whose associated StartUp is ...???
// 2- Retrieving the Feature Facade Type and Display Names
// 2-1- Retrieve information of a Library Feature Facade
// 2-1-1- Instantiate a Library feature
// 2-1-2- Retrieve the display name of the library feature
// 2-1-3- Retrieve the Type of the Library feature. 
// 2-2-   Retrieve information of an aggregated Chapter Feature Facade
//  2-2-1- Instantiate a Chapter feature (referred to as Chapter1, hereafter)
//  2-2-2- Retrieve the display name of the Chapter feature
//  2-2-3- Retrieve the Type of the Chapter feature. 
//  2-2-4- Instantiate a Novel feature
//  2-2-5- Aggregate Chapter1 under Novel
//  2-2-6- Retrieve display name of the first aggregated Chapter feature
//  2-2-7- Create and aggregate a second Chapter feature under the Novel
//  2-2-8- Retrieve display name of the second aggregated Chapter feature
//  2-2-9- Detach Chapter1 from under the Novel feature
// 2-2-10- Retrieve display name of the first Chapter feature
// 2-3- Retrieve information of a Referenced (Pointed) feature
// 2-3-1- Instantiate a Publisher feature
// 2-3-2- Retrieve display name of the Publisher feature
// 2-3-3- Have Novel pointing to Publisher
// 2-3-4- Retrieve display name of the pointed Publisher feature
// 3-Save the session
// 4- Closes the session
//=============================================================================
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAV5V6FmExtFeatNamingAndBasicSkill DocumentStorageName" 
//  where the "DocumentStorageName" is the entire pathname, name and .CATPart extension
//    under which the new document is to be stored. 
// 
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

//System Framework

#include "CATSysBoolean.h"

// ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

//CAT3DPhysicalRepInterfaces Framework
#include "CATIPsiRepresentationReference.h"  // interface on rep ref

// CATPLMIdentificationAccess Framework
#include "CATIPLMComponent.h"
#include "CATIAdpPLMIdentificator.h"

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
	if (NULL != pDoc) cout << "New document created OK in V5-V6 compatible FW" << endl << flush;
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
	// 3- Creating a Credential Object which authorizes client to handle the "CAAFmExtPoint2D" feature
	// ------------------------------------------------------------------------------------------------
	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials in V5 env..." << endl;

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
		cout << "   Usage: CAAV5V6FmExtFeatNamingAndBasicSkill <Repository> <Server> <User> <Password> <SecurityCtx> <Environment>" ;
		cout <<endl;
		return 1;
	}

	cout << "   The CAAV5V6FmExtFeatNamingAndBasicSkill main program begins in V5-V6 compatible FW...."<< endl << endl;

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
	cout << "      SecurityCtx=" << iArgv[5] << endl;

	//-------------------------------------------------------------------------------------------------
	// 3- Creating a Credential Object which authorizes client to handle the "CAAFmExtPoint2D" feature
	// ------------------------------------------------------------------------------------------------
	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials in V6 env" << endl;

	//------------------------------------------------------------------
	// 4- Creates a Product Representation Reference ( Techno Rep)
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

	// -----------------------------------------------------------------------
	//  1- Retrieving the StartUp Facade Types
	// -----------------------------------------------------------------------
	// 1-1- Retrieve Type of a StartUp Facade, whose associated StartUp has a #isa facet
	CATUnicodeString LibraryStartUpType("CAAOsmPublicLibrary");
	CATFmStartUpFacade SUFacadeOnLibrary(MyCredential,LibraryStartUpType);
	cout << "   CAAFmExtLibrary StartUp Facade retrieved OK" << endl << flush;

	CATUnicodeString strTypeName;
	rc =  SUFacadeOnLibrary.GetTypeName(strTypeName);
	if (FAILED(rc)) return 1;
	cout << "   The Type of the Library StartUp Facade is " << strTypeName.ConvertToChar() << endl;

	// 1-2- Retrieve Type of a derived StartUp Facade, whose associated StartUp is without a #isa facet
	CATUnicodeString NovelStartUpType("`CAAOsmNovel`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade SUFacadeOnNovel(MyCredential,NovelStartUpType);
	cout << "   CAAOsmNovel StartUp Facade retrieved OK" << endl << flush;

	rc =  SUFacadeOnNovel.GetTypeName(strTypeName);
	if (FAILED(rc)) return 1;
	cout << "   The Type of the Novel StartUp Facade is " << strTypeName.ConvertToChar() << endl;

	// 1-3- Retrieve Type of a StartUp Facade, whose associated StartUp is ...???
	CATUnicodeString ChapterStartUpType("`CAAOsmChapter`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade SUFacadeOnChapter(MyCredential,ChapterStartUpType);
	cout << "   CAAOsmChapter StartUp Facade retrieved OK" << endl << flush;

	rc =  SUFacadeOnChapter.GetTypeName(strTypeName);
	if (FAILED(rc)) return 1;
	cout << "   The Type of the Chapter StartUp Facade is " << strTypeName.ConvertToChar() << endl;

	// -----------------------------------------------------------------------
	//  2- Retrieving the Feature Facade Type and Display Names
	// -----------------------------------------------------------------------
	// 2-1-   Retrieve information of a Library Feature Facade (whose StartUp Latetype explicitly defined with #isa facet)
	// 2-1-1- Instantiate a Library feature
	CATFmFeatureFacade FeatFacadeOnLibrary(MyCredential);
	rc = SUFacadeOnLibrary.InstantiateIn(MyContainerFacade,FeatFacadeOnLibrary);
	if (FAILED(rc)) return 1;
	cout << "   Library Feature created OK" << endl;

	// 2-1-2- Retrieve the display name of the library feature
	CATUnicodeString strDisplayName;
	rc = FeatFacadeOnLibrary.GetDisplayName(strDisplayName);
	if (FAILED(rc)) return 1;
	cout << "   The display name of the Library feature is " << strDisplayName.ConvertToChar() << endl;

	// 2-1-3- Retrieve the Type of the Library feature. 
	rc =  FeatFacadeOnLibrary.GetType(strTypeName);
	if (FAILED(rc)) return 1;
	cout << "   The Type of the Library feature  is " << strTypeName.ConvertToChar() << endl;

	// 2-2-   Retrieve information of an aggregated Chapter Feature Facade
	// 2-2-1- Instantiate a Chapter feature (referred to as Chapter1, hereafter)
	CATFmFeatureFacade FeatFacadeOnChapter1(MyCredential);
	rc = SUFacadeOnChapter.InstantiateIn(MyContainerFacade,FeatFacadeOnChapter1);
	if (FAILED(rc)) return 1;
	cout << "   First Chapter feature created OK" << endl;

	// 2-2-2- Retrieve the display name of the Chapter feature
	rc = FeatFacadeOnChapter1.GetDisplayName(strDisplayName);
	if (FAILED(rc)) return 1;
	cout << "   The display name of the Chapter feature is " << strDisplayName.ConvertToChar() << endl;

	// 2-2-3- Retrieve the Type of the Chapter feature. 
	rc =  FeatFacadeOnChapter1.GetType(strTypeName);
	if (FAILED(rc)) return 1;
	cout << "   The Type of the Chapter feature  is " << strTypeName.ConvertToChar() << endl;

	// 2-2-4- Instantiate a Novel feature
	CATFmFeatureFacade FeatFacadeOnNovel(MyCredential);
	rc = SUFacadeOnNovel.InstantiateIn(MyContainerFacade,FeatFacadeOnNovel);
	if (FAILED(rc)) return 1;
	cout << "   Novel feature created OK" << endl;

	// 2-2-5- Aggregate Chapter1 under Novel
	CATFmAttributeValue AttrValueForChapterComp;
	AttrValueForChapterComp.SetFeature(FeatFacadeOnChapter1);

	CATFmAttributeName AttrNameChapters("NovelChapter");

	rc = FeatFacadeOnNovel.AppendValue(AttrNameChapters,AttrValueForChapterComp);
	if (FAILED(rc)) return 1;
	cout << "   Success in appending a Chapter feature to the Novel" << endl;

	// 2-2-6- Retrieve display name of the first aggregated Chapter feature
	rc = FeatFacadeOnChapter1.GetDisplayName(strDisplayName);
	if (FAILED(rc)) return 1;
	cout << "   The display name of the first aggregated Chapter feature is " << strDisplayName.ConvertToChar() << endl;

	// 2-2-7- Create and aggregate a second Chapter feature under the Novel
	CATFmFeatureFacade FeatFacadeOnChapter2(MyCredential);
	rc = SUFacadeOnChapter.InstantiateUnder(MyContainerFacade,FeatFacadeOnNovel,AttrNameChapters,FeatFacadeOnChapter2);
	if (FAILED(rc)) return 1;

	// 2-2-8- Retrieve display name of the second aggregated Chapter feature
	rc = FeatFacadeOnChapter2.GetDisplayName(strDisplayName);
	if (FAILED(rc)) return 1;
	cout << "   The display name of the second aggregated Chapter feature is " << strDisplayName.ConvertToChar() << endl;

	// 2-2-9- Detach Chapter1 from under the Novel feature
	rc = FeatFacadeOnNovel.DetachComponent(AttrNameChapters,1);
	if (FAILED(rc)) return 1;
	cout << "   Success in detaching the first Chapter feature under the Novel" << endl;

	// 2-2-10- Retrieve display name of the first Chapter feature
	rc = FeatFacadeOnChapter1.GetDisplayName(strDisplayName);
	if (FAILED(rc)) return 1;
	cout << "   The display name of the first Chapter feature after detach is " << strDisplayName.ConvertToChar() << endl;

	// 2-3- Retrieve information of a Referenced (Pointed) feature
	// 2-3-1- Instantiate a Publisher feature
	CATUnicodeString PublisherStartUpType("`CAAOsmPublisher`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade SUFacadeOnPublisher(MyCredential,PublisherStartUpType);
	cout << "   CAAOsmPublisher StartUp Facade retrieved OK" << endl << flush;

	CATFmFeatureFacade FeatFacadeOnPublisher(MyCredential);
	rc = SUFacadeOnPublisher.InstantiateIn(MyContainerFacade,FeatFacadeOnPublisher);
	if (FAILED(rc)) return 1;
	cout << "   Publisher feature created OK" << endl;

	// 2-3-2- Retrieve display name of the Publisher feature
	rc = FeatFacadeOnPublisher.GetDisplayName(strDisplayName);
	if (FAILED(rc)) return 1;
	cout << "   The display name of the standalone Publisher feature is " << strDisplayName.ConvertToChar() << endl;

	// 2-3-3- Have Novel pointing to Publisher
	CATFmAttributeValue AttrValueForPublisher;
	AttrValueForPublisher.SetFeature(FeatFacadeOnPublisher);

	CATFmAttributeName AttrNamePublisher("BookPublisher");

	rc = FeatFacadeOnNovel.SetValue(AttrNamePublisher,AttrValueForPublisher);
	if (FAILED(rc)) return 1;
	cout << "   Success in creating a reference from the Novel feature to the Publisher" << endl;

	// 2-3-4- Retrieve display name of the pointed Publisher feature
	rc = FeatFacadeOnPublisher.GetDisplayName(strDisplayName);
	if (FAILED(rc)) return 1;
	cout << "   The display name of the pointed Publisher feature is " << strDisplayName.ConvertToChar() << endl;

#ifdef CATIAR214
	//-------------------------------------------------------------------------------------
	// - Save the session
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
	cout << endl << "The CAAV5V6FmExtFeatNamingAndBasicSkill main program ends in V6 env...."<< endl << endl;

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

