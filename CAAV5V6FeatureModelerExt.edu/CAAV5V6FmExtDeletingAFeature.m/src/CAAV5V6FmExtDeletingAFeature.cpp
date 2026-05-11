// COPYRIGHT DASSAULT SYSTEMES 2010
//=============================================================================
// Abstract of Use Case "CAAV5V6FmExtDeletingAFeature":
// ----------------------------------------------
// The objective of the current UC illustrates the impact of a feature delete 
// on the its aggregated features, referenced features and feature extensions
// All features aggregated by the deleted feature are recursively deleted
// The feature extensions to the deleted feature and its aggregations are also deleted
// The features referenced by the deleted features however remain unaffected
// 
// The UC refers to features defined in the Catalog "CAAOsmCatalogSU.CATfct".
// It also refers to the feature extensions defined in the Catalog "CAAOsmExt2Catalog"
// These feature definition as they occur in the catalogs Osms follow:

/*
document `CAAOSMCatalogSU.CATfct` {
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
feature CAAOsmBarCode #startup {
string CAAOsmValue
}
}

document `CAAOsmExt2Catalog.CATfct` {
container RootCont #root {
feature CAAOsmChildrensNovel #startup #extension {
int AgeGroup
AgeGroup=12
}
}
}
*/

//=============================================================================
//  Steps
//
// 1- Create the Data Model
//          1-1- Create the Novel1 feature (Novel1)
//          1-2- Refer to a Publisher1 feature from the Novel1 feature
//          1-3- Aggregate Chapter1 under the Novel1 feature
//          1-4- Create an extension to the Novel1 feature (ChildrenExt1)
//          1-5- Aggregate another Novel2 feature under Novel1
//          1-6- Refer to a Publisher2 from the Novel2 feature
//          1-7- Create an extension to the Novel2 feature (ChildrenExt2)
//          1-8- Aggregate Chapter2 under the Novel2 feature
//          1-9- Aggregated Novel2 under Novel1
// 2- Output the features before deletion
//          2-1- Retrieve the base features
//          2-2- Retrieve the feature extensions
//                  2-2-1- Retrieve the Applicative Container for Feature Extensions
//                  2-2-2- Create a Facade over the Extension Container
//                  2-2-3- Scan through the Extension Container. Output the feature extensions
// 3-  Confirm when base feature (Novel) is deleted, features aggregated under it (Chapter.1 and Novel.1) 
//     are deleted recursively
//     Referenced Features (Publisher) however are not deleted 
//          3-1- Delete the base feature (Novel)
//          3-2- Confirm base feature (Novel) with its aggregated features (Novel.1, Chapter.1, BarCode.1) are
//               deleted recursively
//          3-3- Confirm Referenced Feature (Publisher) not deleted
// -  Save the session
// - Closes the session
//
//=============================================================================
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAV5V6FmExtDeletingAFeature DocumentStorageName" 
//  where the "DocumentStorageName" is the entire pathname, name and .CATPart extension
//    under which the new document is to be stored. 
//
// Return code :
//   0 successful execution
//   1 execution failed
// 
//=============================================================================


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

// CATPLMComponentInterfaces Framework
#include "CATIPLMNavRepReference.h"

// CAT3DPhysicalRepInterfaces Framework
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
	//------------------------------------------------------------
	// 3- Creating a Credential Object with client authorization
	// -----------------------------------------------------------

	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner("CAAOsmExt2Catalog","CAAOsmClientId2");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the first credentials" << endl;

	CATFmCredentials MyCredentialForBaseCatalog;
	rc = MyCredentialForBaseCatalog.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = MyCredentialForBaseCatalog.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the second credentials" << endl;

	//Create container facade to work with
	CATFmContainerFacade MyContainerFacade1(MyCredential,piRootContainer);

#endif

#ifdef CATIAR214

	//---------------------
	// 1- Checks arguments
	//---------------------
	if ( 7 != iArgc )
	{
		cout << endl;
		cout << "   Usage: CAAV5V6FmExtDeleteFeature <Repository> <Server> <User> <Password> <SecurityCtx> <Environment> " ;
		cout <<endl;
		return 1;
	}

	cout << "   The CAAV5V6FmExtDeleteFeature main program begins ...."<< endl << endl;

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

	//------------------------------------------------------------
	// 3- Creating a Credential Object with client authorization
	// -----------------------------------------------------------

	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner("CAAOsmExt2Catalog","CAAOsmClientId2");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the first credentials" << endl;

	CATFmCredentials MyCredentialForBaseCatalog;
	rc = MyCredentialForBaseCatalog.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = MyCredentialForBaseCatalog.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the second credentials" << endl;

	//------------------------------------------------------------------
	// 4- Creates a Product Representation Reference (Techno Rep)
	//------------------------------------------------------------------
	CATString EnvToUse = iArgv[6];
	CATString Repository = iArgv[1];
	CATUnicodeString NameAndTypeofContainer = "CAAFmExtAppliCont1" ;
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
	CATFmContainerFacade MyContainerFacade1(MyCredential,pContainer);

#endif
	//-----------------

	// ------------------------------------
	// 1- Creating the Data Model
	// ------------------------------------
	// 1-1- Create the Novel1 feature (Novel1)
	CATUnicodeString NovelStartUpType("`CAAOsmNovel`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade SUFacadeOnNovel(MyCredential,NovelStartUpType);

	CATFmFeatureFacade FeatFacadeOnNovel1(MyCredential);
	rc = SUFacadeOnNovel.InstantiateIn(MyContainerFacade1,FeatFacadeOnNovel1);
	if (FAILED(rc)) return 1;
	cout << "   Novel1 Feature created" << endl;

	// 1-2- Refer to a Publisher1 feature from the Novel1 feature
	CATFmAttributeName BookPublisherAttrName("BookPublisher");

	CATUnicodeString PublisherStartUpType("`CAAOsmPublisher`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade SUFacadeOnPublisher(MyCredential,PublisherStartUpType);

	CATFmFeatureFacade FeatFacadeOnPublisher1(MyCredential);
	rc = SUFacadeOnPublisher.InstantiateIn(MyContainerFacade1,FeatFacadeOnPublisher1);
	if (SUCCEEDED(rc)) cout << "   Publisher SU instantiated.." << endl;
	else return 1;

	CATFmAttributeValue AttrValue;
	AttrValue.SetFeature(FeatFacadeOnPublisher1);
	rc = FeatFacadeOnNovel1.SetValue(BookPublisherAttrName,AttrValue);
	if (SUCCEEDED(rc)) cout << "   Referred to a Publisher1 feature from the Novel1 feature" << endl;
	else return 1;

	// 1-3- Aggregate a BarCode to the Novel1 feature
	CATUnicodeString BarCodeStartUpType("`CAAOsmBarCode`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade SUFacadeOnBarCode(MyCredential,BarCodeStartUpType);

	// 1-4- Aggregate Chapter1 under the Novel1 feature
	CATUnicodeString ChapterStartUpType("`CAAOsmChapter`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade SUFacadeOnChapter(MyCredential,ChapterStartUpType);

	CATFmFeatureFacade FeatFacadeOnChapter1(MyCredential);
	rc = SUFacadeOnChapter.InstantiateIn(MyContainerFacade1,FeatFacadeOnChapter1);
	if (FAILED(rc)) return 1;

	CATFmAttributeName NovelChapterAttrName("NovelChapter");
	AttrValue.SetFeature(FeatFacadeOnChapter1);
	FeatFacadeOnNovel1.SetValue(NovelChapterAttrName,AttrValue);
	cout << "   Agggregated Chapter1 under the Novel1 feature" << endl;

	// 1-5- Create an extension to the Novel1 feature (ChildrenExt1)
	CATString strChildrensExtNovel("`CAAOsmChildrensNovel`#2@`CAAOsmExt2Catalog.CATfct`");
	CATFmAttributeValue attrValue;
	rc =  FeatFacadeOnNovel1.AddExtension(strChildrensExtNovel,attrValue);
	if (FAILED(rc)) return 1;
	cout << "   ChildrenExt1, an extension to Novel1 created" << endl;
	CATFmFeatureFacade FeatFacadeOnChildNovelExtn1(MyCredential,attrValue);

	// 1-6- Aggregate another Novel2 feature under Novel1
	CATFmFeatureFacade FeatFacadeOnNovel2(MyCredential);
	rc = SUFacadeOnNovel.InstantiateIn(MyContainerFacade1,FeatFacadeOnNovel2);
	if (FAILED(rc)) return 1;
	cout << "   Feature Novel2 created" << endl;

	// 1-7- Refer to a Publisher2 from the Novel2 feature
	CATFmFeatureFacade FeatFacadeOnPublisher2(MyCredential);
	rc = SUFacadeOnPublisher.InstantiateIn(MyContainerFacade1,FeatFacadeOnPublisher2);
	if (SUCCEEDED(rc)) cout << "   Publisher SU instantiated 2nd time.." << endl;
	else return 1;

	AttrValue.SetFeature(FeatFacadeOnPublisher2);
	rc = FeatFacadeOnNovel2.SetValue(BookPublisherAttrName,AttrValue);
	if (SUCCEEDED(rc)) cout << "   Referred to a Publisher2 feature from the Novel2 feature" << endl;
	else return 1;

	// 1-8- Create an extension to the Novel2 feature (ChildrenExt2)
	rc =  FeatFacadeOnNovel2.AddExtension(strChildrensExtNovel,AttrValue);
	if (FAILED(rc)) return 1;
	cout << "   ChildrenExt2, an extension to Novel2 created" << endl;
	CATFmFeatureFacade FeatFacadeOnChildNovelExtn2(MyCredential,AttrValue);

	// 1-9- Aggregate Chapter2 under the Novel2 feature
	CATFmFeatureFacade FeatFacadeOnChapter2(MyCredential);
	rc = SUFacadeOnChapter.InstantiateIn(MyContainerFacade1,FeatFacadeOnChapter2);
	if (FAILED(rc)) return 1;

	AttrValue.SetFeature(FeatFacadeOnChapter2);
	rc = FeatFacadeOnNovel2.SetValue(NovelChapterAttrName,AttrValue);
	if (FAILED(rc)) return 1;
	cout << "   Aggregated Chapter2 under the Novel2 feature" << endl;

	// 1-10- Aggregated Novel2 under Novel1
	AttrValue.SetFeature(FeatFacadeOnNovel2);
	rc = FeatFacadeOnNovel1.SetValue(NovelChapterAttrName,AttrValue);
	if (FAILED(rc)) return 1;
	cout << "   Aggregated Novel2 feature under Novel1" << endl;

	// -------------------------------------------------------------
	// 2- Output the features before deletion
	// -------------------------------------------------------------
	// 2-1- Retrieve the base features
	CATFmFeatureFacade FeatFacade(MyCredential);
	CATUnicodeString strFeatDisplayName;
	CATFmFeatureIterator oFeatIterator;
	rc =  MyContainerFacade1.ScanFeatures(oFeatIterator);
	if (FAILED(rc)) return 1;

	while ((SUCCEEDED(oFeatIterator.Next(FeatFacade))))
	{
		rc = FeatFacade.GetDisplayName(strFeatDisplayName);
		if (SUCCEEDED(rc))
			cout << "   The feature that exists before call to delete is " << strFeatDisplayName.ConvertToChar() << endl;
	}

	// -------------------------------------------------------------------------------------------------------------------
	// 3-  Confirm when base feature (Novel) is deleted, features aggregated under it (Chapter.1 and Novel.1) 
	//     are deleted recursively
	//     Referenced Features (Publisher) however are not deleted 
	// -------------------------------------------------------------------------------------------------------------------
	// Delete the base feature (Novel)
	CATFmFeatureFacade FeatFacadeOnNovelWithBaseFeatCred(MyCredentialForBaseCatalog);
	FeatFacadeOnNovelWithBaseFeatCred = FeatFacadeOnNovel1;
	rc = FeatFacadeOnNovelWithBaseFeatCred.DeleteSelf();
	if (FAILED(rc)) return 1;
	cout << "   Feature Novel deleted" << endl;

	// Confirm base feature (Novel) with its aggregated features (Novel.1, Chapter.1, BarCode.1) are
	// deleted recursively
	// Confirm Referenced Feature not deleted
	CATFmFeatureIterator oFeatIterator1;
	rc =  MyContainerFacade1.ScanFeatures(oFeatIterator1);
	if (FAILED(rc)) return 1;

	CATUnicodeString strPublisherType("CAAOsmPublisher");
	CATBoolean bFeatDeleted = TRUE; // Valuated to true, assuming all features expected to be deleted are deleted
	CATUnicodeString strFeatType;
	int iFeatCount = 0;
	while ( (SUCCEEDED(oFeatIterator1.Next(FeatFacade))))
	{
		iFeatCount++;
		rc = FeatFacade.GetType(strFeatType);
		if (SUCCEEDED(rc))
			if (strFeatType != strPublisherType) bFeatDeleted = FALSE; 
	}

	if ((FALSE == bFeatDeleted) || (2 != iFeatCount)) return 1;
	cout << "   Confirmed Novel1 is deleted with its aggregated features Chapter,BarCode and Novel.1 recursively";
	cout << "   Also confirmed referenced feature Publisher not deleted";

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
	cout << endl << "   The CAAV5V6FmExtDeletingAFeature main program ends ...."<< endl << endl;
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
