// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
// Abstract of Use Case "CAAV5V6FmExtAggregatedAttr":
// -------------------------------------------
//
// This sample illustrates working with aggregated features and with lists of
// attributes.  It loads an existing catalog containing StartUps which are
// retrieved and new instances of them created.  A list of aggregated features
// is created and assigned to a unique "father" feature.
//   
// Following is a list of the StartUps and their attributes from CAAOsmCatalogSU catalog
// that were created using CATfctEditorAssistant tool
//
//
//		StartUp									Attribute
//		-------									---------
//		CAAOsmPublisher							PublisherName
//												PublisherAddress
//
//		CAAOsmChapter							ChapterTitle
//												FirstPage
//												LastPage
//
//		CAAOsmBook								Title
//												BookPublisher
//
//		CAAOsmNovel (a kind of CAAOsmBook)		Title
//												BookPublisher
//												Author
//												(list of) NovelChapter
//													
//		CAAOsmDictionary (a kind of CAAOsmBook)	Title
//												BookPublisher
//												Language
//
//  Note: This Use-Case is compatible in V5 as well as V6 environment. Thus the code in #ifdef
//		  represents the difference in the respective functionality of V5 and V6 for E.g. Session
//		  creation, Applicative Containers concept, Save Services etc.
//		  The code outside the #ifdef is the common code for V5 and V6 and represents the backported
//		  functionalities of V6 to V5.
//
//=============================================================================
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAV5V6FmExtAggregatedAttr DocumentStorageName" 
//  where the "DocumentStorageName" is the entire pathname, name and .CATPart extension
//    under which the new document is to be stored. 
//
//=============================================================================


// System Framework
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATIAV5Level.h"
#include <iostream.h>

//FeatureModelerExt FW
#include "CATFmFeatureFacade.h"
#include "CATFmContainerFacade.h"
#include "CATFmStartUpFacade.h"
#include "CATFmCredentials.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATFmFeatureModelerID.h"

//-------------------------------------------------------------------------
//	Include guards when the Framework is in V6 Environment
//-------------------------------------------------------------------------
#ifdef CATIAR214
// CATPLMIntegrationUse
#include "CATAdpSaver.h"

// CAAPLMClientAdapter.edu Framework
#include "CAAAdpCreateCloseSession.h"

//CAT3DPhysicalRepInterfaces  Framework
#include "CATIPsiRepresentationReference.h"  // interface on rep ref

//local Framework
#include "CAAV5V6FmExtCreateRepRef.h"     // to create the Rep ref

//System Framework
#include "CATSysBoolean.h"

// ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

#endif
/*--------------------------*/

//-------------------------------------------------------------------------
//	Include guards when the Framework is in V5 Environment
//-------------------------------------------------------------------------

#ifdef CATIAV5R23

// ObjectModelerBase Framework
#include "CATDocument.h"                    // Document
#include "CATSession.h"
#include "CATDocumentServices.h"            // New, SaveAs and Remove document
#include "CATSessionServices.h"             // Create_Session and Delete_Session

#include "CATInit.h"                        // GetRootContainer


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

int main (int iArgc, char * iArgv[] )
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

	//------------------------------------------------------------------
	//- Build Credentials to access the catalog "CAAOsmCatalogSU"
	//------------------------------------------------------------------
	
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
	//------------------------------------------
	//  Checks arguments when in V6 environment
	//------------------------------------------
	if ( 7 != iArgc )
	{
		cout << endl;
		cout << "Usage: CAAV5V6FmExtAggregatedAttr <Repository> <Server> <User> <Password> <SecurityCtx> <Environment>" ;
		cout <<endl;
		return 1;
	}
	cout << "The CAAV5V6FmExtAggregatedAttr main program begins in V6 env...."<< endl << endl;

	//------------------------------------------------------------------
	//  Initializes the PLM session when in V6 Environment
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
	//- Build Credential s to access the catalog "CAAOsmCatalogSU"
	//------------------------------------------------------------------

	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials from V5-V6 compatible code" << endl;

	//---------------------------------------------------------------------------------------------------
	//- Creates a Product Representation Reference with an applicative container when in V6 environment
	//----------------------------------------------------------------------------------------------------
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
	//1- Retrieve Names to Attributes associated with the features to be instantiated
	//--------------------------------------------------------------------------------
	// 1-1- Retrieve the Name to the "ChapterTitle" Attribute, a string type
	CATFmAttributeName ChptrTitleAttrName("ChapterTitle");

	// 1-2- Retrieve the Name to the "FirstPage" Attribute, an int type
	CATFmAttributeName ChptrFirstPgAttrName("FirstPage");

	// 1-3- Retrieve the Name to the "LastPage" Attribute, an int type
	CATFmAttributeName ChptrLastPgAttrName("LastPage");

	// 1-4- Retrieve a Name to the "NovelChapter" attribute, a tk_component type
	CATFmAttributeName NovelChptrAttrName("NovelChapter");

	//-----------------------------------------------------------------------
	//2- Creating features instantiated from the "CAAOsmChapter" StartUp
	//-----------------------------------------------------------------------
	// 2-1- Create "CAAOsmChapter" StartUp facade
	CATUnicodeString ChapterStartUpType("`CAAOsmChapter`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade ChapterStartUpFacade( MyCredential, ChapterStartUpType );

	// 2-2- Instantiate the 1st Chapter feature
	CATFmFeatureFacade oFeatFacadeOnChptrInst1 (MyCredential);
	rc = ChapterStartUpFacade.InstantiateIn(MyContainerFacade,oFeatFacadeOnChptrInst1);
	if (FAILED(rc))	return 1;
	cout << "   CAAOsmChapter 1st SU Instance created OK" << endl;

	// 2-3- Valuate the attributes of 1st Chapter instance
	// 2-3-1- Valuate the "ChapterTitle" Attribute (string)
	CATUnicodeString strTitleName("The Three Presents of M.D Artagnan, the Father");
	CATFmAttributeValue AttrAsFmValue(strTitleName);
	rc =  oFeatFacadeOnChptrInst1.SetValue(ChptrTitleAttrName,AttrAsFmValue);
	if (FAILED(rc))	return 1;

	// 2-3-2- Valuate the "FirstPage" Attribute (int)
	int iFirstPg = 11;
	AttrAsFmValue.SetInteger(iFirstPg);
	rc =  oFeatFacadeOnChptrInst1.SetValue(ChptrFirstPgAttrName,AttrAsFmValue);
	if (FAILED(rc))	return 1;

	// 2-3-3- Valuate the "LastPage" Attribute (int)
	int iLastPg = 27;
	AttrAsFmValue.SetInteger(iLastPg);
	rc =  oFeatFacadeOnChptrInst1.SetValue(ChptrLastPgAttrName,AttrAsFmValue);
	if (FAILED(rc))	return 1;

	// 2-4- Instantiate the 2nd Chapter feature
	CATFmFeatureFacade oFeatFacadeOnChptrInst2(MyCredential);
	rc = ChapterStartUpFacade.InstantiateIn(MyContainerFacade,oFeatFacadeOnChptrInst2);
	if (FAILED(rc))	return 1;
	cout << "   CAAOsmChapter 2nd SU Instance created OK" << endl;

	// 2-5- Valuate the attributes of the 2nd Chapter instance
	CATUnicodeString strTitleName2("The Antechambre of M. de Treville");
	AttrAsFmValue.SetString(strTitleName2);
	rc =  oFeatFacadeOnChptrInst2.SetValue(ChptrTitleAttrName,AttrAsFmValue);
	if (FAILED(rc))	return 1;

	int iFirstPg2 = 28;
	AttrAsFmValue.SetInteger(iFirstPg2);
	rc =  oFeatFacadeOnChptrInst1.SetValue(ChptrFirstPgAttrName,AttrAsFmValue);
	if (FAILED(rc))	return 1;

	int iLastPg2 = 37;
	AttrAsFmValue.SetInteger(iLastPg2);
	rc =  oFeatFacadeOnChptrInst2.SetValue(ChptrLastPgAttrName,AttrAsFmValue);
	if (FAILED(rc))	return 1;

	// 2-6- Instantiate the 3rd Chapter feature
	CATFmFeatureFacade oFeatFacadeOnChptrInst3(MyCredential);
	rc = ChapterStartUpFacade.InstantiateIn(MyContainerFacade,oFeatFacadeOnChptrInst3);
	if (FAILED(rc))	return 1;
	cout << "   CAAOsmChapter 3rd SU Instance created OK" << endl;

	// 2-7- Valuate the attributes of the 3rd Chapter instance
	CATUnicodeString strTitleName3("The Audience");
	AttrAsFmValue.SetString(strTitleName3);
	rc =  oFeatFacadeOnChptrInst3.SetValue(ChptrTitleAttrName,AttrAsFmValue);
	if (FAILED(rc))	return 1;

	int iFirstPg3 = 38;
	AttrAsFmValue.SetInteger(iFirstPg3);
	rc =  oFeatFacadeOnChptrInst3.SetValue(ChptrFirstPgAttrName,AttrAsFmValue);
	if (FAILED(rc))	return 1;

	int iLastPg3 = 50;
	AttrAsFmValue.SetInteger(iLastPg3);
	rc =  oFeatFacadeOnChptrInst3.SetValue(ChptrLastPgAttrName,AttrAsFmValue);
	if (FAILED(rc))	return 1;

	//--------------------------------------------------------------------------------------------------------------------
	// 3- Confirm the Chapter Instance (aggregated) has no parent 
	//--------------------------------------------------------------------------------------------------------------------
	rc = oFeatFacadeOnChptrInst1.GetParentFeature(AttrAsFmValue);
	if (SUCCEEDED(rc))
	{
		CATFmFeatureFacade FeatFacadeOnParent(MyCredential);
		AttrAsFmValue.GetFeature(FeatFacadeOnParent);

		CATUnicodeString oDisplayName;
		rc = FeatFacadeOnParent.GetDisplayName(oDisplayName);

		if (FAILED(rc)) // because no feature bound to FeatFacadeOnParent 
		{
			//double check 
			CATBaseUnknown_var Parent = FeatFacadeOnParent.GetFeature();
			if ( NULL_var ==  Parent ) 
			{
				rc= S_OK ; 
				cout <<"   The Chapter newly created is  without parent" << endl ;
			}

		}else rc= E_FAIL ; 
	}

	if FAILED(rc) return 1 ;
	//------------------------------------------------------------------------------------------------------
	// 4- Instantiate a "CAAOsmNovel" feature and valuate its "NovelChapter" attribute (component type)                                     
	//------------------------------------------------------------------------------------------------------
	// 4-1- Instantiate a "CAAOsmNovel" feature 
	CATUnicodeString NovelStartUpType("`CAAOsmNovel`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade NovelStartUpFacade(MyCredential, NovelStartUpType);

	CATFmFeatureFacade oFeatFacadeOnNovel(MyCredential);
	rc = NovelStartUpFacade.InstantiateIn(MyContainerFacade,oFeatFacadeOnNovel);
	if (FAILED(rc))	return 1;
	cout << "   CAAOsmNovel SU Instance created OK" << endl;

	// 4-2- Valuate the "NovelChapter" attribute of the Novel Instance with the 3 Chapters
	AttrAsFmValue.SetFeature(oFeatFacadeOnChptrInst1);
	rc = oFeatFacadeOnNovel.AppendValue(NovelChptrAttrName,AttrAsFmValue);
	if (FAILED(rc))	return 1;

	AttrAsFmValue.SetFeature(oFeatFacadeOnChptrInst2);
	rc = oFeatFacadeOnNovel.AppendValue(NovelChptrAttrName,AttrAsFmValue);
	if (FAILED(rc))	return 1;

	AttrAsFmValue.SetFeature(oFeatFacadeOnChptrInst3);
	rc = oFeatFacadeOnNovel.AppendValue(NovelChptrAttrName,AttrAsFmValue);
	if (FAILED(rc))	return 1;
	cout << "   Success in setting list NovelChapter attribute of a Novel Instance" << endl;

	//--------------------------------------------------------------------------------------------------------------------
	// 5- Confirm the Chapter Instance (aggregated) has the Novel Instance as its parent (aggregating)
	//--------------------------------------------------------------------------------------------------------------------
	rc = oFeatFacadeOnChptrInst1.GetParentFeature(AttrAsFmValue);
	if (SUCCEEDED(rc))
	{
		CATFmFeatureFacade FeatFacadeOnParent(MyCredential);
		AttrAsFmValue.GetFeature(FeatFacadeOnParent);

		CATUnicodeString oDisplayName;
		rc = FeatFacadeOnParent.GetDisplayName(oDisplayName);

		if (SUCCEEDED(rc)) cout << "   The parent Novel Instance is "  << oDisplayName.ConvertToChar() << endl;

		//double check 
		CATBaseUnknown_var Parent = FeatFacadeOnParent.GetFeature();
		if ( NULL_var == Parent ) rc= E_FAIL ; 
	}

	if FAILED(rc) return 1 ;

	//-----------------------------------------------------------
	// 6- Scan through the Novel Chapters. Display their titles
	//-----------------------------------------------------------
	CATFmAttributeValue oAttrValueOnChapterTitle;
	CATFmAttributeValue oFmAttrValueOnCurrentChapter;

	rc = oFeatFacadeOnNovel.GetValue(NovelChptrAttrName,AttrAsFmValue);
	for (int i=1; i<=AttrAsFmValue.Size(); i++)
	{
		oFmAttrValueOnCurrentChapter = AttrAsFmValue[i];

		CATFmFeatureFacade FeatFacadeOnCurrentChapter(MyCredential);
		oFmAttrValueOnCurrentChapter.GetFeature(FeatFacadeOnCurrentChapter);

		oAttrValueOnChapterTitle.Clear();
		rc = FeatFacadeOnCurrentChapter.GetValue(ChptrTitleAttrName,oAttrValueOnChapterTitle);
		if (SUCCEEDED(rc))
		{
			CATUnicodeString strTitle;
			oAttrValueOnChapterTitle.GetString(strTitle);
			cout << "   The Chapter title is "  << strTitle.ConvertToChar() << endl;
		}
	}

#ifdef CATIAR214

	pContainer->Release();
	pContainer= NULL ;

	//---------------------------------------------------------------------
	//  Saves the session when in V6 environment
	//---------------------------------------------------------------------
	CATAdpSaver saver;
	rc = saver.Save();
	if (FAILED(rc))	return 1;
	cout <<"   Save is successful " << endl;

	// Unload components from session
	Bag.RemoveAll();

	// remove once no more used

	//------------------------------------------------------------------
	//  Closes the session when in V6 Environment
	//------------------------------------------------------------------
	rc = ::CAAAdpCloseSession();
	if (FAILED(rc) ) return 1;

	cout << endl << "The CAAV5V6FmExtAggregatedAttr main program ends ...."<< endl << endl;
	return 0;

#endif

#ifdef CATIAV5R23
	/*--------------------------------------------------------------------------*/
	/*  Save and remove the document and end the session when in V5 environment */
	/*--------------------------------------------------------------------------*/

	// release the pointer on the container
	piRootContainer -> Release();
	piRootContainer = NULL;

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
