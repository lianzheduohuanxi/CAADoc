// COPYRIGHT DASSAULT SYSTEMES 2010
//=============================================================================
// Abstract of Use Case "CAAV5V6FmExtFeatNamingIndexMgt":
// ----------------------------------------------
// The objective of the current UC is for an end-user to gain a better understanding
// of a Feature display name index management
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
feature CAAOsmLibrary #startup #isa(CAAOsmPublicLibrary) {
}
feature CAAOsmBarCode #startup {
string CAAOsmValue
}
*/

//=============================================================================
//  Steps
//
// 1- Build the Feature Model
//    1-1- Creating a Library feature
//    1-2- Creating 2 Publishers
//    1-3- Creating 3 BarCode features 
//    1-4- Creating 3 Book features
//    1-5- Refer Publisher from Book
//    1-6- Aggregate a BarCode under each Book
//    1-7- Create a Novel feature with 2 Chapters aggregated and 1 standalone
// 2- Output Display Names of features before AutoNumbering (Only the Chapter Name has an index associated with it)
// 3- Check that no feature as autonumber provider  when invoked on stand-alone  feature without a Reference
// 4- Check that no feature as autonumber provider  when invoked on aggregated feature(and without an explicit Reference)
// 5- Use Library as a Reference Feature for Numbering for all features, except the Chapters
// 6- Output Display Names of features after AutoNumbering 1 
// 7- Check that library is the feature as autonumber provider   
// 8- SetAutoNumberingProvider() Call impact is same, invoked on an aggregated feature or on standalone feature followed by aggregation
//    8-1- The autonumbering is done after  the aggregation 
//    8-2- The autonumbering is done before the aggregation 
// - Save the session
// - Closes the session
//=============================================================================
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAV5V6FmExtFeatNamingIndexMgt DocumentStorageName" 
//  where the "DocumentStorageName" is the entire pathname, name and .CATPart extension
//    under which the new document is to be stored. 

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

// FeatureModelerExt 
#include "CATFmFeatureFacade.h"
#include "CATFmContainerFacade.h"
#include "CATFmStartUpFacade.h"
#include "CATFmCredentials.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATFmFeatureModelerID.h"

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

// =================================================================================
// Outputs the display names of features input
HRESULT OutputDisplayNamesOfFeats(CATFmFeatureFacade & FeatFacadeOnNovel,
								  CATFmFeatureFacade & FeatFacadeOnChapter1,
								  CATFmFeatureFacade & FeatFacadeOnChapter2,
								  CATFmFeatureFacade & FeatFacadeOnChapter3,
								  CATFmFeatureFacade & FeatFacadeOnBook1,
								  CATFmFeatureFacade & FeatFacadeOnBook2,
								  CATFmFeatureFacade & FeatFacadeOnBook3,
								  CATFmFeatureFacade & FeatFacadeOnBarCode1, 
								  CATFmFeatureFacade & FeatFacadeOnBarCode2,
								  CATFmFeatureFacade & FeatFacadeOnBarCode3,
								  CATFmFeatureFacade & FeatFacadeOnPublisher1,
								  CATFmFeatureFacade & FeatFacadeOnPublisher2);
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
	CATFmContainerFacade MyContainerFacade(MyCredential,piRootContainer);


#endif

#ifdef CATIAR214

	//---------------------
	// 1- Checks arguments
	//---------------------
	if ( 7 != iArgc )
	{
		cout << endl;
		cout << "   Usage: CAAV5V6FmExtFeatNamingIndexMgt <Repository> <Server> <User> <Password> <SecurityCtx> <Environment> " ;
		cout <<endl;
		return 1;
	}

	cout << "   The CAAV5V6FmExtFeatNamingIndexMgt main program begins ...."<< endl << endl;

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

	// -----------------------------------------------------------------------
	//  1- Build the Feature Model
	// -----------------------------------------------------------------------
	// 1-1- Creating a Library feature
	CATUnicodeString LibraryStartUpType("CAAOsmPublicLibrary");
	CATFmStartUpFacade SUFacadeOnLibrary(MyCredential,LibraryStartUpType);
	cout << "   CAAOsmLibrary StartUp Facade retrieved OK" << endl << flush;

	CATFmFeatureFacade FeatFacadeOnLibrary(MyCredential);
	rc = SUFacadeOnLibrary.InstantiateIn(MyContainerFacade,FeatFacadeOnLibrary);
	if (FAILED(rc)) return 1;
	cout << "   Library Feature created OK" << endl;

	// 1-2- Creating 2 Publishers
	// 1-2-1- Creating the 1st Publisher feature
	CATUnicodeString PublisherStartUpType("`CAAOsmPublisher`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade SUFacadeOnPublisher(MyCredential,PublisherStartUpType);
	cout << "   CAAOsmPublisher StartUp Facade retrieved OK" << endl << flush;

	CATFmFeatureFacade FeatFacadeOnPublisher1(MyCredential);
	rc = SUFacadeOnPublisher.InstantiateIn(MyContainerFacade,FeatFacadeOnPublisher1);
	if (FAILED(rc)) return 1;
	cout << "   Publisher Feature 1 created OK" << endl;

	// 1-2-2- Creating the 2nd Publisher feature
	CATFmFeatureFacade FeatFacadeOnPublisher2(MyCredential);
	rc = SUFacadeOnPublisher.InstantiateIn(MyContainerFacade,FeatFacadeOnPublisher2);
	if (FAILED(rc)) return 1;
	cout << "   Publisher Feature 2 created OK" << endl;

	// 1-3- Creating 3 BarCode features 
	// 1-3-1- Creating the 1st BarCode feature
	CATUnicodeString BarCodeStartUpType("`CAAOsmBarCode`#10@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade SUFacadeOnBarCode(MyCredential,BarCodeStartUpType);
	cout << "   CAAOsmBarCode StartUp Facade retrieved OK" << endl << flush;

	CATFmFeatureFacade FeatFacadeOnBarCode1(MyCredential);
	rc = SUFacadeOnBarCode.InstantiateIn(MyContainerFacade,FeatFacadeOnBarCode1);
	if (FAILED(rc)) return 1;
	cout << "   BarCode Feature 1 created OK" << endl;

	// 1-3-2- Creating the 2nd BarCode feature
	CATFmFeatureFacade FeatFacadeOnBarCode2(MyCredential);
	rc = SUFacadeOnBarCode.InstantiateIn(MyContainerFacade,FeatFacadeOnBarCode2);
	if (FAILED(rc)) return 1;
	cout << "   BarCode Feature 2 created OK" << endl;

	// 1-3-3- Creating the 3rd BarCode feature
	CATFmFeatureFacade FeatFacadeOnBarCode3(MyCredential);
	rc = SUFacadeOnBarCode.InstantiateIn(MyContainerFacade,FeatFacadeOnBarCode3);
	if (FAILED(rc)) return 1;
	cout << "   BarCode Feature 3 created OK" << endl;

	// 1-4- Creating 3 Book features
	// 1-4-1- Creating the 1st Book feature
	CATUnicodeString BookStartUpType("`CAAOsmBook`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade SUFacadeOnBook(MyCredential,BookStartUpType);
	cout << "   CAAOsmBook StartUp Facade retrieved OK" << endl << flush;

	CATFmFeatureFacade FeatFacadeOnBook1(MyCredential);
	rc = SUFacadeOnBook.InstantiateIn(MyContainerFacade,FeatFacadeOnBook1);
	if (FAILED(rc)) return 1;
	cout << "   Book Feature 1 created OK" << endl;

	// 1-4-2- Creating the 2nd Book feature
	CATFmFeatureFacade FeatFacadeOnBook2(MyCredential);
	rc = SUFacadeOnBook.InstantiateIn(MyContainerFacade,FeatFacadeOnBook2);
	if (FAILED(rc)) return 1;
	cout << "   Book Feature 2 created OK" << endl;

	// 1-4-3- Creating the 3rd Book feature
	CATFmFeatureFacade FeatFacadeOnBook3(MyCredential);
	rc = SUFacadeOnBook.InstantiateIn(MyContainerFacade,FeatFacadeOnBook3);
	if (FAILED(rc)) return 1;
	cout << "   Book Feature 3 created OK" << endl;

	// 1-5- Refer Publisher from Book
	// 1-5-1- Refer the 1st Publisher from the 1st Book
	CATFmAttributeName AttrNameBookPublisher("BookPublisher");

	CATFmAttributeValue AttrValue;
	AttrValue.SetFeature(FeatFacadeOnPublisher1);

	rc = FeatFacadeOnBook1.SetValue(AttrNameBookPublisher,AttrValue);
	if (FAILED(rc)) return 1;
	cout << "   1st Book feature refers to the 1st Publisher" << endl;

	// 1-5-2- Refer the 2nd Publisher from the 2nd and 3rd Book
	AttrValue.SetFeature(FeatFacadeOnPublisher2);

	rc = FeatFacadeOnBook2.SetValue(AttrNameBookPublisher,AttrValue);
	if (FAILED(rc)) return 1;
	cout << "   2nd Book feature refers to the 2nd Publisher" << endl;

	rc = FeatFacadeOnBook3.SetValue(AttrNameBookPublisher,AttrValue);
	if (FAILED(rc)) return 1;
	cout << "   3rd Book feature refers to the 2nd Publisher" << endl;

	//// 1-6- Aggregate a BarCode under each Book
	//// 1-6-1- Aggregate the 1st BarCode to 1st Book
	CATFmAttributeName AttrNameBarCode("CAAOsmBarCode");
	AttrValue.SetFeature(FeatFacadeOnBarCode1);
	rc = FeatFacadeOnBook1.SetValue(AttrNameBarCode,AttrValue);
	if (FAILED(rc)) return 1;

	// 1-6-2- Aggregate the 2nd BarCode to the 2nd Book
	AttrValue.SetFeature(FeatFacadeOnBarCode2);
	rc = FeatFacadeOnBook2.SetValue(AttrNameBarCode,AttrValue);
	if (FAILED(rc)) return 1;

	// 1-6-3- Aggregate the 3rd BarCode to the 3rd Book
	AttrValue.SetFeature(FeatFacadeOnBarCode3);
	rc = FeatFacadeOnBook3.SetValue(AttrNameBarCode,AttrValue);
	if (FAILED(rc)) return 1;

	// 1-7- Create a Novel feature with 2 Chapters aggregated and 1 standalone
	// 1-7-1- Instantiate a Novel feature
	CATUnicodeString NovelStartUpType("`CAAOsmNovel`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade SUFacadeOnNovel(MyCredential,NovelStartUpType);
	cout << "   CAAOsmNovel StartUp Facade retrieved OK" << endl << flush;

	CATFmFeatureFacade FeatFacadeOnNovel(MyCredential);
	rc = SUFacadeOnNovel.InstantiateIn(MyContainerFacade,FeatFacadeOnNovel);
	if (FAILED(rc)) return 1;
	cout << "   Novel Feature created OK" << endl;

	// 1-7-2- Instantiate 1st Chapter feature
	CATUnicodeString ChapterStartUpType("`CAAOsmChapter`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade SUFacadeOnChapter(MyCredential,ChapterStartUpType);
	cout << "   CAAOsmChapter StartUp Facade retrieved OK" << endl << flush;

	CATFmFeatureFacade FeatFacadeOnChapter1(MyCredential);
	rc = SUFacadeOnChapter.InstantiateIn(MyContainerFacade,FeatFacadeOnChapter1);
	if (FAILED(rc)) return 1;
	cout << "   Chapter Feature 1 created OK" << endl;

	// 1-7-3- Instantiate 2nd Chapter feature
	CATFmFeatureFacade FeatFacadeOnChapter2(MyCredential);
	rc = SUFacadeOnChapter.InstantiateIn(MyContainerFacade,FeatFacadeOnChapter2);
	if (FAILED(rc)) return 1;
	cout << "   Chapter Feature 2 created OK" << endl;

	// 1-7-4- Instantiate 3rd Chapter feature
	CATFmFeatureFacade FeatFacadeOnChapter3(MyCredential);
	rc = SUFacadeOnChapter.InstantiateIn(MyContainerFacade,FeatFacadeOnChapter3);
	if (FAILED(rc)) return 1;
	cout << "   Chapter Feature 3 created OK" << endl;

	// 1-7-5- Aggregate the 2nd and 3rd Chapter under Novel
	CATFmAttributeName AttrNameNovelChapter("NovelChapter");
	AttrValue.SetFeature(FeatFacadeOnChapter2);
	rc = FeatFacadeOnNovel.AppendValue(AttrNameNovelChapter,AttrValue);
	if (FAILED(rc)) return 1;

	AttrValue.SetFeature(FeatFacadeOnChapter3);
	rc = FeatFacadeOnNovel.AppendValue(AttrNameNovelChapter,AttrValue);
	if (FAILED(rc)) return 1;

	// -----------------------------------------------------------------------------------------------------------------
	// 2- Output Display Names of features before AutoNumbering (Only the Chapter Name has an index associated with it)
	// -----------------------------------------------------------------------------------------------------------------
	rc = OutputDisplayNamesOfFeats( FeatFacadeOnNovel,FeatFacadeOnChapter1,FeatFacadeOnChapter2,FeatFacadeOnChapter3,
		FeatFacadeOnBook1,FeatFacadeOnBook2,FeatFacadeOnBook3,
		FeatFacadeOnBarCode1,FeatFacadeOnBarCode2,FeatFacadeOnBarCode3,
		FeatFacadeOnPublisher1,FeatFacadeOnPublisher2);

	if (FAILED(rc)) return 1;

	//-------------------------------------------------------------------------------------------------------------------------------
	// 3- Call to CATFmFeatureFacade::GetAutoNumberingProvider() returns S_FALSE when invoked on Book (since Book has no Reference)
	//-------------------------------------------------------------------------------------------------------------------------------
	CATFmAttributeValue oValueOnRef;
	rc = FeatFacadeOnBook1.GetAutoNumberingProvider(oValueOnRef);
	if (FAILED(rc) ) return 1;
	CATFmFeatureFacade TheReference; 
	rc = oValueOnRef.GetFeature(TheReference) ;
	if ( S_FALSE !=  rc) return 1 ;
	cout << "   Call to CATFmFeatureFacade::GetAutoNumberingProvider() returns a null value for the Book" << endl;

	//-------------------------------------------------------------------------------------------------------------------------------
	// 4- Call to CATFmFeatureFacade::GetAutoNumberingProvider() returns S_FALSE when invoked on Chapter (since the aggregating Novel is not an explicit Reference)
	//-------------------------------------------------------------------------------------------------------------------------------
	rc = FeatFacadeOnChapter2.GetAutoNumberingProvider(oValueOnRef);
	if (FAILED(rc)) return 1;
	rc = oValueOnRef.GetFeature(TheReference) ;
	if ( S_FALSE !=  rc) return 1 ;
	cout << "   Call to CATFmFeatureFacade::GetAutoNumberingProvider() returns a null value when invoked on Chapter2(since the aggregating Novel is not an explicit Reference)" << endl;

	// ---------------------------------------------------------------------------------------------
	// 5- Use Library as a Reference Feature for Numbering for all features, except the Chapters
	// ---------------------------------------------------------------------------------------------
	CATFmAttributeValue FeatureAsValueForIndexRef = FeatFacadeOnLibrary.GetFeatureAsValue();
	rc = FeatFacadeOnNovel.SetAutoNumberingProvider(FeatureAsValueForIndexRef);
	if (FAILED(rc)) return 1;

	rc = FeatFacadeOnBook1.SetAutoNumberingProvider(FeatureAsValueForIndexRef);
	if (FAILED(rc)) return 1;

	rc = FeatFacadeOnBook2.SetAutoNumberingProvider(FeatureAsValueForIndexRef);
	if (FAILED(rc)) return 1;

	rc = FeatFacadeOnBook3.SetAutoNumberingProvider(FeatureAsValueForIndexRef);
	if (FAILED(rc)) return 1;

	rc = FeatFacadeOnBarCode1.SetAutoNumberingProvider(FeatureAsValueForIndexRef);
	if (FAILED(rc)) return 1;

	rc = FeatFacadeOnBarCode2.SetAutoNumberingProvider(FeatureAsValueForIndexRef);
	if (FAILED(rc)) return 1;

	rc = FeatFacadeOnBarCode3.SetAutoNumberingProvider(FeatureAsValueForIndexRef);
	if (FAILED(rc)) return 1;

	rc = FeatFacadeOnPublisher1.SetAutoNumberingProvider(FeatureAsValueForIndexRef);
	if (FAILED(rc)) return 1;

	rc = FeatFacadeOnPublisher2.SetAutoNumberingProvider(FeatureAsValueForIndexRef);
	if (FAILED(rc)) return 1;

	cout << "   Used Library as a Reference Feature for Numbering for all features, except the Chapters" << endl;

	// -------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// 6- Output Display Names of features after AutoNumbering (All except Library, have an Index. The BarCodes are now indexed 1,2,3, while previously it was 1 for all)
	// -------------------------------------------------------------------------------------------------------------------------------------------------------------------
	rc = OutputDisplayNamesOfFeats( FeatFacadeOnNovel,FeatFacadeOnChapter1,FeatFacadeOnChapter2,FeatFacadeOnChapter3,
		FeatFacadeOnBook1,FeatFacadeOnBook2,FeatFacadeOnBook3,
		FeatFacadeOnBarCode1,FeatFacadeOnBarCode2,FeatFacadeOnBarCode3,
		FeatFacadeOnPublisher1,FeatFacadeOnPublisher2);
	if (FAILED(rc)) return 1;
	cout << "   Output Display Names of features after AutoNumbering (All except Library, have an Index. The BarCodes are now indexed 1,2,3, while previously it was 1 for all)" << endl;

	//----------------------------------------------------------------------------------------------------------------------------------
	// 7- Call to CATFmFeatureFacade::GetAutoNumberingProvider() returns S_OK when invoked on BarCode (since Library is its Reference)
	//----------------------------------------------------------------------------------------------------------------------------------

	rc = FeatFacadeOnBarCode3.GetAutoNumberingProvider(oValueOnRef);
	if (FAILED(rc) || (oValueOnRef != FeatureAsValueForIndexRef)) return 1;
	cout << "   The Library feature is the reference to the Bar Code 3 feature" << endl;

	//---------------------------------------------------------------------------------------------------------------------------------------
	// 8- SetAutoNumberingProvider() Call impact is same, invoked on an aggregated feature or on standalone feature followed by aggregation
	//---------------------------------------------------------------------------------------------------------------------------------------
	cout << "   Case1: Impact analysis of SetAutoNumberingProvider() call on an aggregated feature" << endl;
	// 8-1- Case 1: Impact analysis of SetAutoNumberingProvider() call on an aggregated feature
	// 8-1-1- Instantiate Book, BarCode
	CATFmFeatureFacade FeatFacadeOnBook4(MyCredential);
	rc = SUFacadeOnBook.InstantiateIn(MyContainerFacade,FeatFacadeOnBook4);
	if (FAILED(rc)) return 1;
	cout << "   Book Feature 4 created OK" << endl;

	CATFmFeatureFacade FeatFacadeOnBarCode4(MyCredential);
	rc = SUFacadeOnBarCode.InstantiateIn(MyContainerFacade,FeatFacadeOnBarCode4);
	if (FAILED(rc)) return 1;
	cout << "   BarCode Feature 4 created OK" << endl;

	// 8-1-2- Aggregate BarCode under Book
	AttrValue.SetFeature(FeatFacadeOnBarCode4);
	rc = FeatFacadeOnBook4.SetValue(AttrNameBarCode,AttrValue);
	if (FAILED(rc)) return 1;

	// 8-1-3- Output display name of aggregated BarCode
	CATUnicodeString strDisplayName;
	rc = FeatFacadeOnBarCode4.GetDisplayName(strDisplayName);
	if (FAILED(rc)) return 1;
	cout << "   The display name of the aggregated BarCode feature is " << strDisplayName.ConvertToChar() << endl;

	// 8-1-4- SetAutoNumberingProvider() call on the aggregated BarCode
	rc = FeatFacadeOnBarCode4.SetAutoNumberingProvider(FeatureAsValueForIndexRef);
	if (FAILED(rc)) return 1;

	// 8-1-5- Output display name of aggregated BarCode after SetNumberingProvider() call. Index is 4
	rc = FeatFacadeOnBarCode4.GetDisplayName(strDisplayName);
	if (FAILED(rc)) return 1;
	cout << "   Output display name of aggregated BarCode after SetNumberingProvider() call. Index is 4 " << strDisplayName.ConvertToChar() << endl;

	// 8-2- Case 2: Impact analysis of SetAutoNumberingProvider() call on a standalone feature aggregated after the call
	cout << "   Case2: Impact analysis of SetAutoNumberingProvider() call on a standalone feature aggregated after the call" << endl;
	// 8-2-1- Instantiate Book, BarCode
	CATFmFeatureFacade FeatFacadeOnBook5(MyCredential);
	rc = SUFacadeOnBook.InstantiateIn(MyContainerFacade,FeatFacadeOnBook5);
	if (FAILED(rc)) return 1;
	cout << "   Book Feature 5 created OK" << endl;

	CATFmFeatureFacade FeatFacadeOnBarCode5(MyCredential);
	rc = SUFacadeOnBarCode.InstantiateIn(MyContainerFacade,FeatFacadeOnBarCode5);
	if (FAILED(rc)) return 1;
	cout << "   BarCode Feature 5 created OK" << endl;

	// 8-2-2- SetAutoNumberingProvider() call on the standalone BarCode
	rc = FeatFacadeOnBarCode5.SetAutoNumberingProvider(FeatureAsValueForIndexRef);
	if (FAILED(rc)) return 1;

	rc = FeatFacadeOnBarCode5.GetDisplayName(strDisplayName);
	if (FAILED(rc)) return 1;
	cout << "   The display name of the stand alone BarCode feature is " << strDisplayName.ConvertToChar() << endl;

	// 8-2-3- Aggregate the BarCode under Book
	AttrValue.SetFeature(FeatFacadeOnBarCode5);
	rc = FeatFacadeOnBook5.SetValue(AttrNameBarCode,AttrValue);
	if (FAILED(rc)) return 1;

	// 8-2-4- Output display name of aggregated BarCode after the SetNumberingProvider() call. it is still 5.
	rc = FeatFacadeOnBarCode5.GetDisplayName(strDisplayName);
	if (FAILED(rc)) return 1;
	cout << "   The display name of aggregated BarCode after the SetNumberingProvider() call. it is still 5 " << strDisplayName.ConvertToChar() << endl;

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
	cout << endl << "The CAAV5V6FmExtFeatNamingAndBasicSkill main program ends ...."<< endl << endl;

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

//--------------------------------------------------------------------------------------
// Outputs the display names of the features input
//--------------------------------------------------------------------------------------
HRESULT OutputDisplayNamesOfFeats(CATFmFeatureFacade & FeatFacadeOnNovel,
								  CATFmFeatureFacade & FeatFacadeOnChapter1,
								  CATFmFeatureFacade & FeatFacadeOnChapter2,
								  CATFmFeatureFacade & FeatFacadeOnChapter3,
								  CATFmFeatureFacade & FeatFacadeOnBook1,
								  CATFmFeatureFacade & FeatFacadeOnBook2,
								  CATFmFeatureFacade & FeatFacadeOnBook3,
								  CATFmFeatureFacade & FeatFacadeOnBarCode1, 
								  CATFmFeatureFacade & FeatFacadeOnBarCode2,
								  CATFmFeatureFacade & FeatFacadeOnBarCode3,
								  CATFmFeatureFacade & FeatFacadeOnPublisher1,
								  CATFmFeatureFacade & FeatFacadeOnPublisher2)
{
	CATUnicodeString strDisplayName;
	HRESULT rc = FeatFacadeOnBarCode1.GetDisplayName(strDisplayName);
	if (SUCCEEDED(rc))
	{
		cout << "   The display name of the 1st BarCode is " << strDisplayName.ConvertToChar() << endl;
		rc = FeatFacadeOnBarCode2.GetDisplayName(strDisplayName);
	}

	if (SUCCEEDED(rc))
	{
		cout << "   The display name of the 2nd BarCode is " << strDisplayName.ConvertToChar() << endl;
		rc = FeatFacadeOnBarCode3.GetDisplayName(strDisplayName);
	}

	if (SUCCEEDED(rc))
	{
		cout << "   The display name of the 3rd BarCode is " << strDisplayName.ConvertToChar() << endl;
		rc = FeatFacadeOnChapter1.GetDisplayName(strDisplayName);
	}

	if (SUCCEEDED(rc))
	{
		cout << "   The display name of the 1st Chapter feature is " << strDisplayName.ConvertToChar() << endl;
		rc = FeatFacadeOnChapter2.GetDisplayName(strDisplayName);
	}

	if (SUCCEEDED(rc))
	{
		cout << "   The display name of the 2nd Chapter feature is " << strDisplayName.ConvertToChar() << endl;
		rc = FeatFacadeOnChapter3.GetDisplayName(strDisplayName);
	}

	if (SUCCEEDED(rc))
	{
		cout << "   The display name of the 3rd Chapter feature is " << strDisplayName.ConvertToChar() << endl;
		rc = FeatFacadeOnNovel.GetDisplayName(strDisplayName);
	}

	if (SUCCEEDED(rc))
	{
		cout << "   The display name of the Novel feature is " << strDisplayName.ConvertToChar() << endl;
		rc = FeatFacadeOnBook1.GetDisplayName(strDisplayName);
	}

	if (SUCCEEDED(rc))
	{
		cout << "   The display name of the 1st Book feature is " << strDisplayName.ConvertToChar() << endl;
		rc = FeatFacadeOnBook2.GetDisplayName(strDisplayName);
	}

	if (SUCCEEDED(rc))
	{
		cout << "   The display name of the 2nd Book feature is " << strDisplayName.ConvertToChar() << endl;
		rc = FeatFacadeOnBook3.GetDisplayName(strDisplayName);
	}

	if (SUCCEEDED(rc))
	{
		cout << "   The display name of the 3rd Book feature is " << strDisplayName.ConvertToChar() << endl;
		rc = FeatFacadeOnPublisher1.GetDisplayName(strDisplayName);
	}

	if (SUCCEEDED(rc))
	{
		cout << "   The display name of the 1st Publisher feature is " << strDisplayName.ConvertToChar() << endl;
		rc = FeatFacadeOnPublisher2.GetDisplayName(strDisplayName);
	}

	if (SUCCEEDED(rc))
		cout << "   The display name of the 2nd Publisher feature is " << strDisplayName.ConvertToChar() << endl;

	return rc;
}

