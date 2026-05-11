// COPYRIGHT DASSAULT SYSTEMES 2010
// =========================================================
// Abstract of Use Case "CAAV5V6FmExtWorkingWithCredentials"
//  
//	The Use Case illustrates working with a Credentials object.
//  As an owner of a catalog, user has the privilige to instantiate its features, 
//  retrieve them by scanning the Applicative Containers and introspect them
//
//  Steps:
// 
//   1- Instantiate & valuates features to create the data model
//      1-1- Instantiate a "CAAFmExtLibrary" `feature (Library) 
//      1-2- Instantiate a "CAAFmExtLibBook" feature (Book). Aggregate it under the Library feature
//      1-3- Instantiate a "CAAFmExtLibBookPublisher" feature (Publisher) 
//      1-4- Create a Referencing link from the Book to the Publisher feature
//      1-5- Instantiate a "CAAFmExtLibBookReader" feature (Reader)
//      1-6- Create a Referencing link from the Reader to the Book feature
//      1-7- Add the "CAAFmExtHistoricalNovel" feature(HistoricalNovel), as extension to the Book
//
//   2- Working as on Owner of the Base catalog
//      2-0- Success for some information like display name
//      2-1- Success in introspecting the Book feature
//           2-1-1- Retrieve the value of the attribute "Title" of Book
//           2-1-2- Success in retrieving the feature aggregating the Book. (Library feature)
//           2-1-3- Success in retrieving the feature "pointed to" (referenced) by Book (Publisher)
//           2-1-4- Success in retrieving the feature "extended by" the Book (HistoricalNovel)
//           2-1-5- Success in retrieving the feature "referencing " the Book (Reader/Library)
//      2-2- Confirm failure in introspecting the features related to the Book feature (Inadequate ownership credentials)
//           2-2-1- Confirm failure to introspect the referenced feature (Publisher)
//           2-2-2- Confirm failure to introspect the feature extension (HistoricNovel)
//           2-2-2- Confirm failure to introspect the pointing feature (Reader)
//      2-3- Confirm success in limited introspection of a retrieved feature through services exposed by its implementing Interfaces
//           2-3-1 Retrieve the feature extension (as an Interface type) from its façade (refer 7-1-4)
//           2-3-2 Invoke services exposed by this interface which allow introspecting the feat extension
//
//   3- Introspecting features retrieved from the Book feature using a feat facade with appropriate credentials
//      3-1- Introspecting the referenced feature (Publisher) retrieved from the Book
//           3-1-1- Create feature facade associated with the credentials of the referenced catalog + Publisher feature
//           3-1-2- Success in introspecting Publisher
//           3-1-3- Failure in introspecting the Publisher parent feature (the Company feature)
//      3-2- Introspecting the extension feature (HistoricNovel) of the Book feature
//           3-2-1- Create feature facade associated with the credentials of the extension catalog (defining HistoricalNovel)
//           3-2-2- Link this feature facade to HistoricalNovel 
//           3-2-3- Success in introspecting HistoricalNovel 
//
//   4- Working with Book feature without actually owning the base catalog
//      4-0- Failure for some information like display name
//      4-1- Success in retrieving the feature extension, by owning only the extension feature catalog
//           4-1-1- Create feature facade associated with the credentials of the extension catalog + Book feature
//           4-1-2- Retrieve its HistoricalNovel extension
//      4-2- Success in retrieving the features referencing the Book, by owning only the referencing feature
//           4-2-1- Create feature facade associated with the credentials of the referencing catalog (defining Reader) + Book feature
//           4-2-2- Retrieve the feature referencing the Book feature (Reader)
//
//   5- Working as a Client of an Applicative Container
//       5-1- Instantiate a Container Facade associated with the credentials of the base catalog (defining Book, Library)
//       5-2- Bind this Container Facade with the Applicative Container, created in the Init step
//       5-3- Scan through the Container. Confirm it returns only the Book & Library features
//       5-4- Instantiate Container Facade, associated with the credentials of both the base (defining Book) and extension catalog (defining HistoricalNovel)
//       5-5- Bind this Container Facade with the Applicative Container, created in the Init step
//       5-6- Scan through the Container. Confirm it returns now the Book , Library, and HistoricalNovel features
//
//   - Saves the Session
//   - Closes the Session
//
// ============================================================================
/* Catalogs and the features defined

CATALOG                                 FEATURES DEFINED
-----------------------------------------------------------------------
CAAFmExtBaseCatalogForCredential        CAAFmExtLibrary
CAAFmExtLibBook
CAAFmExtRefCatalogForCredential         CAAFmExtLibBookPublisher
CAAFmExtLibBookReader
CAAFmExtExtnCatalogForCredential        CAAFmExtHistoricalNovel
*/
//=============================================================================
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAV5V6FmExtWorkingWithCredentials DocumentStorageName" 
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

// Other
#include <iostream.h>
#include "CATIAV5Level.h"
//-------------------------------------------------------------------------
//	Include guards when the Framework is in V6 Environment
//-------------------------------------------------------------------------
#ifdef CATIAR214

//local Framework
#include "CAAV5V6FmExtCreateRepRef.h"     // to create the Rep ref

//System Framework
#include "CATUnicodeString.h"
#include "CATString.h"
#include "CATBaseUnknown.h"
#include "CATSysBoolean.h"

//ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

//CAT3DPhysicalRepInterfaces Framework
#include "CATIPsiRepresentationReference.h"

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
	// =====================================================================================
	// - Initialization Credentials and illustrating the MultiKey concept for Credentials
	// =====================================================================================
	CATUnicodeString clientId("CAAFmExtCatalogForCredential");
	CATUnicodeString iBaseCatalogName("CAAFmExtBaseCatalogForCredential"),
		iExtnCatalogName("CAAFmExtExtnCatalogForCredential"),
		iRefCatalogName("CAAFmExtRefCatalogForCredential");

	// - Build distinct Credentials object for each catalog (Base, Referenced/Referencing, Extension)
	CATFmCredentials CredentialForBaseCatalog, CredentialForExtnCatalog, CredentialForRefCatalog;
	rc = CredentialForBaseCatalog.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = CredentialForBaseCatalog.RegisterAsCatalogOwner(iBaseCatalogName,clientId);
	if (FAILED(rc)) return 1;

	rc = CredentialForExtnCatalog.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = CredentialForExtnCatalog.RegisterAsCatalogOwner(iExtnCatalogName,clientId);
	if (FAILED(rc)) return 1;

	rc = CredentialForRefCatalog.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = CredentialForRefCatalog.RegisterAsCatalogOwner(iRefCatalogName,clientId);
	if (FAILED(rc)) return 1;
	cout << "   Success in creating distinct Credentials object for the Base, Referenced/Referencing and Extension Catalog" << endl;

	// - Build an all-inclusive Credential Object
	CATFmCredentials CredentialsForAll;
	CredentialsForAll += CredentialForBaseCatalog;
	CredentialsForAll.RegisterAsCatalogOwner(iExtnCatalogName,clientId);
	CredentialsForAll.RegisterAsCatalogOwner(iRefCatalogName,clientId);
	cout << "   Appended the Credentials object with the Base, Referenced/Referencing and Extension Catalog Credentials" << endl;

	//Create container facade to work with
	CATFmContainerFacade MyContFacade(CredentialsForAll,piRootContainer);


#endif

#ifdef CATIAR214

	// =====================================
	// - Checks arguments
	// =====================================
	if ( 7!= iArgc )
	{
		cout << endl;
		cout << "Usage: CAAV5V6FmExtWorkingWithCredentials <Repository> <Server> <User> <Password> <SecurityCtx> <Environment> " ;
		cout <<endl;
		return 1;
	}
	cout << "The CAAV5V6FmExtWorkingWithCredentials main program begins in V6 env...."<< endl << endl;

	// =====================================
	//  - Initializes the PLM session 
	// =====================================
	HRESULT rc = ::CAAAdpCreateSession(iArgv[1], iArgv[2], iArgv[3], iArgv[4],iArgv[5]);
	if (FAILED(rc))	
		return 1;   
	cout << "   PLM session initialized with the following connection parameters" << endl;
	cout << "      Repository=" << iArgv[1] << endl;
	cout << "      Server="     << iArgv[2] << endl;
	cout << "      UserID="     << iArgv[3] << endl;
	cout << "      UserPasswd=" << iArgv[4] << endl;
	cout << "      SecurityCtx="<< iArgv[5] << endl;

	// =====================================================================================
	// - Initialization Credentials and illustrating the MultiKey concept for Credentials
	// =====================================================================================
	CATUnicodeString clientId("CAAFmExtCatalogForCredential");
	CATUnicodeString iBaseCatalogName("CAAFmExtBaseCatalogForCredential"),
		iExtnCatalogName("CAAFmExtExtnCatalogForCredential"),
		iRefCatalogName("CAAFmExtRefCatalogForCredential");

	// - Build distinct Credentials object for each catalog (Base, Referenced/Referencing, Extension)
	CATFmCredentials CredentialForBaseCatalog, CredentialForExtnCatalog, CredentialForRefCatalog;
	rc = CredentialForBaseCatalog.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = CredentialForBaseCatalog.RegisterAsCatalogOwner(iBaseCatalogName,clientId);
	if (FAILED(rc)) return 1;

	rc = CredentialForExtnCatalog.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = CredentialForExtnCatalog.RegisterAsCatalogOwner(iExtnCatalogName,clientId);
	if (FAILED(rc)) return 1;

	rc = CredentialForRefCatalog.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = CredentialForRefCatalog.RegisterAsCatalogOwner(iRefCatalogName,clientId);
	if (FAILED(rc)) return 1;
	cout << "   Success in creating distinct Credentials object for the Base, Referenced/Referencing and Extension Catalog" << endl;

	// - Build an all-inclusive Credential Object
	CATFmCredentials CredentialsForAll;
	CredentialsForAll += CredentialForBaseCatalog;
	CredentialsForAll.RegisterAsCatalogOwner(iExtnCatalogName,clientId);
	CredentialsForAll.RegisterAsCatalogOwner(iRefCatalogName,clientId);
	cout << "   Appended the Credentials object with the Base, Referenced/Referencing and Extension Catalog Credentials" << endl;

	// =========================================================
	// - Creates a Product Representation Reference (Techno Rep)
	// =========================================================
	CATString EnvToUse = iArgv[6];
	CATString Repository = iArgv[1];
	CATUnicodeString NameAndTypeofContainer = "CAAFmExtAppliCont" ;
	CATIPsiRepresentationReference * pPsiCreatedRepRef= NULL;
	CATBaseUnknown * pContainer = NULL ;
	rc = ::CAAV5V6FmExtCreateRepRef(CredentialsForAll, EnvToUse,Repository,NameAndTypeofContainer,NameAndTypeofContainer,
		IID_CATIPsiRepresentationReference,(void**) &pPsiCreatedRepRef, &pContainer);
	if (FAILED(rc) || (NULL==pPsiCreatedRepRef) || (NULL==pContainer) ) return 1;
	cout <<"   The Product Representation Reference is created" << endl;

	// Insert component that is loaded in session, in BAG
	CATOmbLifeCycleRootsBag Bag;
	Bag.InsertRoot(pPsiCreatedRepRef);

	//Create container facade to work with
	CATFmContainerFacade MyContFacade(CredentialsForAll,pContainer);

	pPsiCreatedRepRef->Release();
	pPsiCreatedRepRef = NULL; 

#endif

	// ==============================
	// 1- Instantiates & Valuates the features to create a data model
	// ==============================
	// 1-1- Instantiate a "CAAFmExtLibrary" feature (Library) 
	CATUnicodeString LibraryStartUpType("`CAAFmExtLibrary`@`CAAFmExtBaseCatalogForCredential.CATfct`");
	CATFmStartUpFacade LibraryStartUpFacade(CredentialForBaseCatalog, LibraryStartUpType);
	CATFmFeatureFacade oFeatFacadeOnLibrary(CredentialForBaseCatalog);
	rc = LibraryStartUpFacade.InstantiateIn(MyContFacade,oFeatFacadeOnLibrary);
	if (FAILED(rc)) return 1;
	cout << "   Success in instantiating a Library feature " << endl;

	// 1-2- Instantiate a "CAAFmExtLibBook" feature (Book). Aggregate it under Library
	CATUnicodeString LibBookStartUpType("`CAAFmExtLibBook`@`CAAFmExtBaseCatalogForCredential.CATfct`");
	CATFmStartUpFacade BookStartUpFacade(CredentialForBaseCatalog, LibBookStartUpType);
	CATFmFeatureFacade oFeatFacadeOnBook(CredentialForBaseCatalog);
	rc = BookStartUpFacade.InstantiateIn(MyContFacade,oFeatFacadeOnBook);
	if (FAILED(rc)) return 1;
	cout << "   Success in instantiating a Book feature " << endl;

	CATFmAttributeName LibBooksAttrName("LibraryBooks");
	CATFmAttributeValue AttrValue;
	AttrValue.SetFeature(oFeatFacadeOnBook);
	rc = oFeatFacadeOnLibrary.SetValue(LibBooksAttrName,AttrValue);
	if (FAILED(rc)) return 1;
	cout << "   Success in aggregating the Books feature under the Library feature" << endl;

	// 1-3- Instantiate a "CAAFmExtLibBookPublisher" feature (Publisher)
	CATUnicodeString LibBookPublisherStartUp("`CAAFmExtLibBookPublisher`@`CAAFmExtRefCatalogForCredential.CATfct`");
	CATFmStartUpFacade PublisherStartUpFacade(CredentialForRefCatalog, LibBookPublisherStartUp);
	CATFmFeatureFacade oFeatFacadeOnPublisher(CredentialForRefCatalog);
	rc = PublisherStartUpFacade.InstantiateIn(MyContFacade,oFeatFacadeOnPublisher);
	if (FAILED(rc)) return 1;
	cout << "   Success in instantiating a Publisher feature " << endl;

	// 1-4- Create a Referencing Link from Book to the Publisher feature
	CATFmAttributeName BookPublshrAttrName("BookPublisher");
	AttrValue.SetFeature(oFeatFacadeOnPublisher);
	rc = oFeatFacadeOnBook.SetValue(BookPublshrAttrName,AttrValue);

	// 1-5- Instantiate a "CAAFmExtLibBookReader" feature (Reader)
	CATUnicodeString LibBookReaderStartUp("`CAAFmExtLibBookReader`@`CAAFmExtRefCatalogForCredential.CATfct`");
	CATFmStartUpFacade ReaderStartUpFacade(CredentialForRefCatalog, LibBookReaderStartUp);
	CATFmFeatureFacade oFeatFacadeOnReader(CredentialForRefCatalog);
	rc = ReaderStartUpFacade.InstantiateIn(MyContFacade,oFeatFacadeOnReader);
	if (FAILED(rc)) return 1;
	cout << "   Success in instantiating a Reader feature " << endl;

	// 1-6- Create a Referencing link from the Reader to the Book feature
	CATFmAttributeName BooksReadAttrName("CAAFmExtBooksRead");
	AttrValue.SetFeature(oFeatFacadeOnBook);
	rc = oFeatFacadeOnReader.SetValue(BooksReadAttrName,AttrValue);
	if (FAILED(rc)) return 1;
	cout << "   Success in setting a reference link to the Book feature from the Reader feature" << endl;

	// 1-7- Instantiate the "CAAFmExtHistoricalNovel" feature (HistoricalNovel), an extension to Book
	// 1-7-1- Create a feature facade on the base feature with only the Extension credentials
	CATFmFeatureFacade FeatFacadeOnBookWithOnlyExtnCatalogCreds(CredentialForExtnCatalog);
	FeatFacadeOnBookWithOnlyExtnCatalogCreds = oFeatFacadeOnBook.GetFeature();
	// 1-7-2- Add an extension (HistoricalNovel) to the Book feature
	CATFmAttributeValue attrValue;
	rc =  FeatFacadeOnBookWithOnlyExtnCatalogCreds.AddExtension("`CAAFmExtHistNovel`#3@`CAAFmExtExtnCatalogForCredential.CATfct`",attrValue);
	if (FAILED(rc)) return 1;
	cout << "   Success in instantiating the Historical Novel, an extension to the Book feature " << endl;
	CATFmFeatureFacade oFeatFacadeOnHistNovelExtn(CredentialForExtnCatalog,attrValue);

	// =============================================================
	// 2- Working as on Owner of the Base catalog (defining Book & Library)
	// =============================================================
	// 2-1- Success in introspecting the Book feature

	// 2-1-0  Success for internal data
	CATUnicodeString TheFeatureBookName ; 
	rc = oFeatFacadeOnBook.GetDisplayName(TheFeatureBookName);
	if (FAILED(rc)) return 1;
	cout << "   The Book name is " << TheFeatureBookName.CastToCharPtr() << endl;

	CATBaseUnknown_var spBook = oFeatFacadeOnBook.GetFeature();
	if (NULL_var == spBook ) return 1;

	// 2-1-1- Retrieve the value of the attribute "Title" of Book
	CATFmAttributeName iAttrNameForTitle("Title");
	rc = oFeatFacadeOnBook.GetValue(iAttrNameForTitle,AttrValue);
	if (FAILED(rc)) return 1;

	CATUnicodeString strTitle;
	AttrValue.GetString(strTitle);
	cout << "   Success in introspecting the Book feature. Its title is " << strTitle.ConvertToChar() << endl;

	// 2-1-2- Success in retrieving the feature aggregating Book. It is the Library feature
	rc = oFeatFacadeOnBook.GetRootParentFeature(AttrValue);
	if (FAILED(rc)) return 1;

	CATFmFeatureFacade FeatFacadeOnParentLibraryFeat;
	rc = AttrValue.GetFeature(FeatFacadeOnParentLibraryFeat);
	if (FAILED(rc)) return 1;

	CATBaseUnknown_var spLibrary = FeatFacadeOnParentLibraryFeat.GetFeature() ;
	if ( NULL_var == spLibrary ) return 1;
	cout << "   Success in retrieving the aggregating parent of the Book feature" << endl;

	// 2-1-3- Success in retrieving the feature "pointed to" (referenced) by Book (in this case, Publisher)
	CATFmAttributeName iAttrNameForPublisher("BookPublisher");
	rc = oFeatFacadeOnBook.GetValue(iAttrNameForPublisher,AttrValue);
	if (FAILED(rc)) return 1;

	CATFmFeatureFacade FeatFacadeOnRetrievedPublisher;
	rc = AttrValue.GetFeature(FeatFacadeOnRetrievedPublisher);
	if (FAILED(rc)) return 1;

	CATBaseUnknown_var spPublisher = FeatFacadeOnRetrievedPublisher.GetFeature() ;
	if ( NULL_var == spPublisher ) return 1;
	cout << "   Success in retrieving the feature referenced (pointed to) by the Book" << endl;

	// 2-1-4- Success in retrieving the feature "extended by" Book. (in this case, HistoricalNovel)
	rc = oFeatFacadeOnBook.GetExtension("`CAAFmExtHistNovel`#3@`CAAFmExtExtnCatalogForCredential.CATfct`",attrValue);
	if (FAILED(rc)) return 1;
	cout << "   Success in retrieving the extension to the base feature" << endl;
	CATFmFeatureFacade FeatFacadeOnRetrievedHistNovelExtn;
	FeatFacadeOnRetrievedHistNovelExtn = attrValue;

	// 2-1-5- Success in retrieving the feature "referencing" Book. (in this case, Reader)
	CATFmPointingFeatureIterator oIteratorOnPointing;
	rc = oFeatFacadeOnBook.ScanPointingFeatures(oIteratorOnPointing);
	if (FAILED(rc)) return 1;  

	CATFmFeatureFacade FeatFacadeOnPointing ;
	rc = oIteratorOnPointing.Next(FeatFacadeOnPointing);
	if (FAILED(rc) ) return 1; 
	rc = oIteratorOnPointing.Next(FeatFacadeOnPointing);
	if (SUCCEEDED(rc) ) return 1;  

	cout << "   Success in retrieving the feature (Reader) pointing the book" << endl;

	// 2-2- Confirm failure in introspecting the features related to the base (Inadequate ownership credentials)

	// 2-2-1-  Confirm failure to introspect the referenced feature (Publisher)
	CATFmAttributeName iAttrNamePublisherName("PublisherName");
	rc = FeatFacadeOnRetrievedPublisher.GetValue(iAttrNamePublisherName,AttrValue);
	if (SUCCEEDED(rc)) return 1;  
	cout << "   Confirmed failure to introspect the referenced feature (Publisher)" << endl;

	// 2-2-2- Confirm failure to introspect the retrieved feature extension (HistoricalNovel)
	CATFmAttributeName iAttrNameEpoch("Epoch");
	rc = FeatFacadeOnRetrievedHistNovelExtn.GetValue(iAttrNameEpoch,AttrValue);
	if (SUCCEEDED(rc)) return 1;  
	cout << "   Confirmed failure to introspect the retrieved feature extension (HistoricalNovel)" << endl;

	// 2-3- Confirm success in limited introspection of a retrieved feat through services exposed by its implementing Interfaces
	/*
	The following part of code is based on working with attributes using the Interfaces, which is
	not the aim of this use-case.

	// 2-3-1 Retrieve the feature extension (as an Interface type) from its façade (refer 2-1-4)
	CAAIFmExtHistNovel* piHistNovel = NULL;
	rc = FeatFacadeOnRetrievedHistNovelExtn.QueryInterfaceOnFeature(IID_CAAIFmExtHistNovel,(void**)&piHistNovel);
	if (FAILED(rc) || (NULL == piHistNovel)) return 1;

	// 2-3-2 Invoke services exposed by this interface which allow introspecting the feat extension
	CATUnicodeString strAttrEpoch;
	rc = piHistNovel->GetEpoch(&strAttrEpoch);
	if (FAILED(rc)) return 1;
	cout << "   Success in retrieving the Epoch attribute value of a feature extension by invoking its Interface service" << endl;
	cout << "   The value of the attribute Epoch is " << strAttrEpoch.ConvertToChar() << endl;
	strAttrEpoch ="Renaissance" ;
	rc = piHistNovel->SetEpoch(strAttrEpoch);
	if (FAILED(rc)) return 1;
	*/

	// =============================================================================================================
	// 3- Introspecting features retrieved from the Book using a feature facade with appropriate Credentials
	// =============================================================================================================
	// 3-1- Introspecting the referenced feature (Publisher) retrieved from the Book

	// 3-1-1- Create feat facade associated with the credentials of the referenced catalog (defining Publisher) +Publisher
	CATFmFeatureFacade FeatFacadeOnPublisherWithRefCatalogCreds(CredentialForRefCatalog,spPublisher);
	// 3-1-2- Success in introspecting the Publisher feature
	rc = FeatFacadeOnPublisherWithRefCatalogCreds.GetValue(iAttrNamePublisherName,AttrValue);
	if (FAILED(rc)) return 1;
	cout << "   Confirmed success in introspecting the referenced feature (Publisher) with the right credentials" << endl;

	// 3-1-3- Confirm FAILURE in introspecting the Publisher parent (the Company feature)
	CATFmAttributeName iAttrNameCompanyKind("CAAFmExtCompanyKind");
	rc = FeatFacadeOnPublisherWithRefCatalogCreds.GetValue(iAttrNameCompanyKind,AttrValue);
	if (SUCCEEDED(rc)) return 1;
	cout << "   Confirmed FAILURE in introspecting the Publisher parent (the Company feature)" << endl;

	// 3-2- Introspecting the Extension feature (HistoricNovel) retrieved from the Book
	// 3-2-1- Create Feature Facade associated with the credentials of the Extension Catalog (defining HistoricalNovel)
	CATFmFeatureFacade FeatFacadeOnExtnWithExtnCredentials(CredentialForExtnCatalog);

	// 3-2-2- Link this feature facade to the Extension feat (HistoricalNovel)
	//FeatFacadeOnExtnWithExtnCredentials = piHistNovel ;

	// 3-2-3- Success in introspecting the feature extension (HistoricalNovel)
	//rc = FeatFacadeOnExtnWithExtnCredentials.GetValue(iAttrNameEpoch,AttrValue);
	//if (FAILED(rc)) return 1;
	//cout << "   Confirmed success in introspecting the extension feature (HistoricalNovel) with the right credentials" << endl;

	//piHistNovel->Release(); piHistNovel = NULL;

	// =========================================================================
	//4- Working with a Book feature without actually owning the base feature catalog
	// =========================================================================

	// 4-0  Failure for internal data
	CATFmFeatureFacade FeatFacadeOnBaseFeatWithNoCredential;
	FeatFacadeOnBaseFeatWithNoCredential = spBook  ;
	TheFeatureBookName = "" ; 
	rc = FeatFacadeOnBaseFeatWithNoCredential.GetDisplayName(TheFeatureBookName);
	if (SUCCEEDED(rc)) return 1;

	// 4-1- Success in retrieving the feat extension, by owning only the extension feat

	// 4-1-1- Create feature facade associated with the credentials of the extension catalog + Book
	CATFmFeatureFacade FeatFacadeOnBaseFeatWithOnlyExtnCreds(CredentialForExtnCatalog,spBook);

	// 4-1-2- Retrieve the extension (HistoricalNovel) to the Book feature
	rc = FeatFacadeOnBaseFeatWithOnlyExtnCreds.GetExtension("`CAAFmExtHistNovel`#3@`CAAFmExtExtnCatalogForCredential.CATfct`",attrValue);
	if (FAILED(rc)) return 1;
	cout << "   Success in retrieving the extension from a base feature facade which has only the extension credentials" << endl;
	CATFmFeatureFacade FeatFacadeOnHistoricalNovelExtn(CredentialForExtnCatalog,attrValue);

	// 4-2- Success in retrieving the feat referencing the base, by owning only the referencing feature catalog
	// 4-2-1- Create a feature facade associated with the credentials of the Referencing Catalog (defining Reader) + Book
	CATFmFeatureFacade FeatFacadeOnBaseFeatWithOnlyRefCreds(CredentialForRefCatalog,spBook);

	// 4-2-2- Retrieve the feature referencing the base feat (Book) (in this case, Reader)
	CATFmPointingFeatureIterator oIteratorOnReader2;
	rc = FeatFacadeOnBaseFeatWithOnlyRefCreds.ScanPointingFeatures(oIteratorOnReader2);
	if (FAILED(rc)) return 1; 

	CATFmFeatureFacade FeatFacadeOnReader2(CredentialForRefCatalog);
	int count = 0; 
	while (SUCCEEDED(oIteratorOnReader2.Next(FeatFacadeOnReader2)))
	{
		count ++ ; 
		CATUnicodeString strDisplayNameOfReader;
		FeatFacadeOnReader2.GetDisplayName(strDisplayNameOfReader);
		cout << "   The Reader feature display name is " << strDisplayNameOfReader.ConvertToChar() << endl;
	}
	if (1 != count ) return 1 ;

	cout << "   Success in retrieving the referencing feature (Reader) using a Book feat facade with only Referencing catalog credentials" << endl;

	// ========================================================
	// 5- Working as a Client of an Applicative Container
	// ========================================================
	// 5-1- Instantiate a Container Facade associated with the credentials of the Base catalog (defining Book)
	CATFmCredentials CredentialsForContainerScan(CredentialForBaseCatalog);
	CATFmContainerFacade ContFacadeForScanBaseFeats(CredentialsForContainerScan);

	// 5-2- Bind this Container Facade with the Applicative Container, created in the Init step
	ContFacadeForScanBaseFeats = MyContFacade.GetContainer();

	// 5-3- Scan through the Container. Confirm it returns only the Book & Library features
	CATFmFeatureIterator oIteratorOnContainerFeats;
	ContFacadeForScanBaseFeats.ScanFeatures(oIteratorOnContainerFeats); 

	CATFmFeatureFacade FeatReturnedByFirstContScan(CredentialForBaseCatalog);
	CATUnicodeString strContainerFeatType;
	CATUnicodeString strTypeBookFeat   ("CAAFmExtLibBook");
	CATUnicodeString strTypeLibraryFeat("CAAFmExtLibrary");
	CATBoolean bValidFeature= TRUE;
	while ( ( TRUE ==bValidFeature) && SUCCEEDED(oIteratorOnContainerFeats.Next(FeatReturnedByFirstContScan)))
	{
		strContainerFeatType = "";
		FeatReturnedByFirstContScan.GetType(strContainerFeatType);
		cout << "   The Container feature type is :" << strContainerFeatType.ConvertToChar() << endl;

		CATUnicodeString SubStr = strContainerFeatType.SubString(0,15);
		if ( (strcmp(strTypeBookFeat,SubStr)) && (strcmp(strTypeLibraryFeat,SubStr)) )  bValidFeature = FALSE;				
	}

	if (FALSE == bValidFeature) return 1;

	bValidFeature = TRUE ;
	cout << "   Success in retrieving only the Book & Library features by scanning the Container, with base credentials " << endl;

	// 5-4- Instantiate Container Facade, associated with the credentials of both the base and extension catalog
	CredentialsForContainerScan +=CredentialForExtnCatalog;
	CATFmContainerFacade ContFacadeForScanBaseAndExtnFeats(CredentialsForContainerScan);

	// 5-5- Bind this Container Facade with the Applicative Container, created in the Init step
	ContFacadeForScanBaseAndExtnFeats = MyContFacade.GetContainer();;

	// 5-6- Scan through the Container. Confirm it returns now both the Book and HistoricalNovel features
	CATFmFeatureIterator oIterOnContFeatsWithUpdatedCredentials;
	ContFacadeForScanBaseAndExtnFeats.ScanFeatures(oIterOnContFeatsWithUpdatedCredentials);
	CATFmFeatureFacade FeatReturnedBySecondContScan (CredentialsForContainerScan);
	CATUnicodeString strTypeExtnFeat("CAAFmExtHistNov");
	while (( TRUE ==bValidFeature) && SUCCEEDED(oIterOnContFeatsWithUpdatedCredentials.Next(FeatReturnedBySecondContScan)))
	{
		strContainerFeatType = "";
		FeatReturnedBySecondContScan.GetType(strContainerFeatType);
		cout << "   The Container feature type is " << strContainerFeatType.ConvertToChar() << endl;
		CATUnicodeString SubStr = strContainerFeatType.SubString(0,15);

		if ( (strcmp(strTypeBookFeat,SubStr)) &&
			(strcmp(strTypeLibraryFeat,SubStr)) &&
			(strcmp(strTypeExtnFeat,SubStr)) ) bValidFeature = FALSE;

	}

	if (FALSE == bValidFeature) return 1;   
	cout << "   Success in retrieving Book, Library and HistoricalNovel by scanning the Container, with updated credentials " << endl;

#ifdef CATIAR214
	// =========================
	// 11- Saves the Session
	// =========================
	CATAdpSaver saver;
	rc = saver.Save();
	if ( FAILED(rc)  ) return 1;

	cout <<"   Save is successful " << endl;

	// Unload components from session
	Bag.RemoveAll();

	pContainer->Release();
	pContainer = NULL ;
	// ========================
	// 12- Closes the session
	// ========================
	rc = ::CAAAdpCloseSession();
	if (FAILED(rc) ) return 1;

	cout <<"   Close is successful " << endl;
	cout << endl << "The CAAV5V6FmExtWorkingWithCredentials main program ends ...."<< endl << endl;

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
