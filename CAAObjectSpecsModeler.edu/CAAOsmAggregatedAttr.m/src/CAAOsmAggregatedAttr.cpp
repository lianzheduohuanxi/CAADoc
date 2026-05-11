// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
// Abstract of Use Case "CAAOsmAggregatedAttr":
// -------------------------------------------
//
// This sample illustrates working with aggregated features and with lists of
// attributes.  It loads an existing catalog containing StartUps which are
// retrieved and new instances of them created.  A list of aggregated features
// is created and assigned to a unique "father" feature.
//   
// Following is a list of the StartUps and their attributes that were created in a
// new catalog in a previous Use Case (see CAAOsmCatalogSU.m) whose execution is,
// therefore, a pre-requisite to this Use Case.
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
//=============================================================================
//  Main Methods:
//  ------------
//
//  Create_Session:  Creates a new session, necessary in a batch program
//  New:             Creates a new document in which to store the new features
//  GetRootContainer:Gets the root container of the new document
//  CATOsmSUHandler :To get a handler for the particular StartUp from the Catalog
//  RetrieveSU:      Retrieves StartUps from the catalog using the CATOsmSUHandler
//  Instantiate:     Creates a new feature from an existing one or from a StartUp
//  GetAttrKey:      Retrieves the attribute key for a given attribute name on
//                      a given features
//  SetString:       Valuates a string-type attribute
//  SetInteger:      Valuates an integer-type attribute
//  SetSpecObject:   Valuates an attribute with a feature object
//  GetFather:       Retrieves the father of the aggregated feature attribute
//  SaveAs:          Saves the document
//  Remove:          Removes the document from the session
//  Delete_Session:  Deletes the session
//
//=============================================================================
//  Return Errors:
//  -------------
//  1 - ERROR in creating the session
//  2 - ERROR in creating a new document
//  3 - ERROR in QueryInterface
//  4 - ERROR in GetRootContainer
//  5 - ERROR in RetrieveSU
//  6 - ERROR in Instanciate
//  7 - ERROR in GetAttrKey
//  8 - ERROR in saving the document
//  9 - ERROR in removing the document from the session
// 10 - ERROR in deleting the session 
// 11 - ERROR in GetSpecObject
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAOsmAggregatedAttr CatalogName DocumentStorageName" 
//  where the "CatalogName" is the name and .CATfct extension (without the path) of the
//     catalog created by the CAAOsmCatalogSU use case and found under the
//     "Ws" + "Os" + resources + graphic directory, and
//  where the "DocumentStorageName" is the entire pathname, name and .CATPart extension
//    under which the new document is to be stored. 
//
//=============================================================================

// System Framework
#include "CATUnicodeString.h"

// ObjectModelerBase Framework
#include "CATSessionServices.h"             // Create_Session and Delete_Session
#include "CATDocumentServices.h"            // New, SaveAs and Remove document
#include "CATInit.h"                        // GetRootContainer
#include "CATDocument.h"                    // Document
#include "CATSession.h"
#include "CATIContainer.h"
#include "CATBaseUnknown.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"                 // Instanciate, GetFather, GetName
#include "CATISpecAttrAccess.h"             // GetAttrKey, SetString, SetInteger,
											//    SetSpecObject, GetString,
											//    GetSpecObject, 
#include "CATISpecAttrKey.h"                // Result of GetAttrKey
#include "CATOsmSUHandler.h"

// Other
#include <iostream.h>


int main (int argc, char * argv[] )
{ 

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

/*--------------------------------------------------------*/
/* Get a CATOsmSUHandler on the StartUp "CAAOsmChapter".    */
/*--------------------------------------------------------*/

	CATUnicodeString CatalogName = argv[1];
	CATUnicodeString clientId("CAAOsmClientId");
	CATUnicodeString chapterSUType("CAAOsmChapter");

	CATOsmSUHandler chapterSUHandler(chapterSUType, clientId, CatalogName);

	// Get a CATISpecObject handle on the CAAOsmChapter StartUp

	CATISpecObject_var spChapterSU = NULL_var;
	rc = chapterSUHandler.RetrieveSU(spChapterSU);

	if (SUCCEEDED(rc))
		cout << "CAAOsmChapter SU retrieved OK" << endl << flush;
	else
	{
		cout <<"ERROR in retrieveing CAAOsmChapter SU" << endl << flush;
		piRootContainer -> Release();
		return 3;
	}

	// Retrieve the attribute keys to the "CAAOsmChapter" attributes:  "ChapterTitle" 
	// "FirstPage" and "LastPage"

	CATISpecAttrAccess *piSpecAttrAccessOnChapt = NULL;
	rc = spChapterSU -> QueryInterface(IID_CATISpecAttrAccess,
		(void**) &piSpecAttrAccessOnChapt);
	if (FAILED(rc)) 
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for CAAOsmChapter SU" << endl << flush;
		return 3;
	}

	CATISpecAttrKey *piKeyChapterTitle = piSpecAttrAccessOnChapt -> GetAttrKey("ChapterTitle");
	if (NULL == piKeyChapterTitle) 
	{
		cout << "ERROR in retrieving ChapterTitle key" << endl << flush;
		return 8;
	}

	CATISpecAttrKey *piKeyFirstPage = piSpecAttrAccessOnChapt -> GetAttrKey("FirstPage");
	if (NULL == piKeyFirstPage) 
	{
		cout << "ERROR in retrieving FirstPage key" << endl << flush;
		return 8;
	}

	CATISpecAttrKey *piKeyLastPage = piSpecAttrAccessOnChapt -> GetAttrKey("LastPage");
	if (NULL == piKeyLastPage) 
	{
		cout << "ERROR in retrieving LastPage key" << endl << flush;
		return 8;
	}

	piSpecAttrAccessOnChapt -> Release();

	/*-----------------------------------------------------------------------------*/
	/* Create an instance of "CAAOsmChapter" in the root container of the document */
	/*-----------------------------------------------------------------------------*/

	CATUnicodeString chapter1("CAAOsmChapter1");

	CATISpecObject_var spChapterInst1 = NULL_var;
	rc = chapterSUHandler.Instanciate(spChapterInst1, piRootContainer, chapter1);
	if (SUCCEEDED(rc))
		cout << "CAAOsmChapter SU instance 1 created OK" << endl << flush;
	else
	{
		cout <<"ERROR in creating instance 1 of CAAOsmChapter SU" << endl << flush;
		piRootContainer -> Release();
		return 7;
	}

		/*--------------------------------------*/
		/* Valuate the new Chapter's attributes */
		/*--------------------------------------*/

		CATISpecAttrAccess *piSpecAttrAccessOnChapt1 = NULL;
		rc = spChapterInst1 -> QueryInterface(IID_CATISpecAttrAccess,
			(void**) &piSpecAttrAccessOnChapt1);
		if (FAILED(rc)) 
		{
			cout << "ERROR in QueryInterface on CATISpecAttrAccess for ChaptInst1" << endl << flush;
			return 3;
		}

		piSpecAttrAccessOnChapt1 -> SetString(piKeyChapterTitle,
			"The Three Presents of M.D Artagnan, the Father");
		piSpecAttrAccessOnChapt1 -> SetInteger(piKeyFirstPage,
			11);
		piSpecAttrAccessOnChapt1 -> SetInteger(piKeyLastPage,
			27);
		piSpecAttrAccessOnChapt1 -> Release();

		/*-----------------------------------------------------------------------*/
		/* Create a second new instance of "CAAOsmChapter" in the root container */
		/*-----------------------------------------------------------------------*/

		CATUnicodeString chapter2("CAAOsmChapter2");

		CATISpecObject_var spChapterInst2 = NULL_var;
		rc = chapterSUHandler.Instanciate(spChapterInst2, piRootContainer, chapter2);
		if (SUCCEEDED(rc))
			cout << "CAAOsmChapter SU instance 2 created OK" << endl << flush;
		else
		{
			cout <<"ERROR in creating instance 2 of CAAOsmChapter SU" << endl << flush;
			piRootContainer -> Release();
			return 3;
		}

		/*---------------------------------------------*/
		/* Valuate the second new Chapter's attributes */
		/*---------------------------------------------*/

		CATISpecAttrAccess *piSpecAttrAcessOnChapt2 = NULL;
		rc = spChapterInst2 -> QueryInterface(IID_CATISpecAttrAccess,
			(void**) &piSpecAttrAcessOnChapt2);
		if (FAILED(rc)) 
		{
			cout << "ERROR in QueryInterface on CATISpecAttrAccess for ChaptInst2" << endl << flush;
			return 3;
		}

		piSpecAttrAcessOnChapt2 -> SetString(piKeyChapterTitle,
			"The Antechambre of M. de Treville");
		piSpecAttrAcessOnChapt2 -> SetInteger(piKeyFirstPage,
			28);
		piSpecAttrAcessOnChapt2 -> SetInteger(piKeyLastPage,
			37);
		piSpecAttrAcessOnChapt2->Release();
		piSpecAttrAcessOnChapt2 = NULL;

		/*----------------------------------------------------------------------*/
		/* Create a third new instance of "CAAOsmChapter" in the root container */
		/*----------------------------------------------------------------------*/

		CATUnicodeString chapter3("CAAOsmChapter3");

		CATISpecObject_var spChapterInst3 = NULL_var;
		rc = chapterSUHandler.Instanciate(spChapterInst3, piRootContainer, chapter2);
		if (SUCCEEDED(rc))
			cout << "CAAOsmChapter SU instance 3 created OK" << endl << flush;
		else
		{
			cout <<"ERROR in creating instance 3 of CAAOsmChapter SU" << endl << flush;
			piRootContainer -> Release();
			return 3;
		}

		/*--------------------------------------------*/
		/* Valuate the third new Chapter's attributes */
		/*--------------------------------------------*/

		CATISpecAttrAccess *piSpecAttrAccessOnChapt3 = NULL;
		rc = spChapterInst3 -> QueryInterface(IID_CATISpecAttrAccess,
			(void**) &piSpecAttrAccessOnChapt3);
		if (FAILED(rc)) 
		{
			cout << "ERROR in QueryInterface on CATISpecAttrAccess for ChaptInst3" << endl << flush;
			return 3;
		}

		piSpecAttrAccessOnChapt3 -> SetString(piKeyChapterTitle,
			"The Audience");
		piSpecAttrAccessOnChapt3 -> SetInteger(piKeyFirstPage,
			38);
		piSpecAttrAccessOnChapt3 -> SetInteger(piKeyLastPage, 
			50);
		piSpecAttrAccessOnChapt3 -> Release();
		piKeyFirstPage -> Release();
		piKeyLastPage -> Release();

		/*---------------------------------------------------------------------------------*/
		/* Assign the list of chapters to an instance of "CAAOsmNovel".  Note that         */
		/* these same chapters cannot be assigned to another feature.  Once set to         */
		/* "CAAOsmNovel1", this feature will be their exclusive "father".                  */
		/*---------------------------------------------------------------------------------*/

		// Get a handler of CATOsmSUHandler on StartUp "CAAOsmNovel"

		CATBaseUnknown *pNovelSU = NULL;
		CATUnicodeString novelSUType("CAAOsmNovel");

		CATOsmSUHandler novelSUHandler(novelSUType, clientId, CatalogName);

		// Get a CATISpecObject handle on the CAAOsmNovel StartUp

		CATISpecObject_var spNovelSU = NULL_var;
		rc = novelSUHandler.RetrieveSU(spNovelSU);

		if (SUCCEEDED(rc))
			cout << "CAAOsmNovel SU retrieved OK" << endl << flush;
		else
		{
			cout <<"ERROR in retrieveing CAAOsmNovel SU" << endl << flush;
			piRootContainer -> Release();
			return 3;
		}

		// Retrieve the Novel's attribute key "NovelChapter"

		CATISpecAttrAccess *piSpecAttrAccessOnNovel = NULL;
		rc = spNovelSU -> QueryInterface(IID_CATISpecAttrAccess, 
			(void**) &piSpecAttrAccessOnNovel);
		if (FAILED(rc)) 
		{
			cout << "ERROR in QueryInterface on CATISpecAttrAccess for Novel SU" << endl << flush;
			return 3;
		}

		CATISpecAttrKey *piKeyNovelChapter = piSpecAttrAccessOnNovel -> GetAttrKey("NovelChapter");
		if (NULL == piKeyNovelChapter) 
		{
			cout << "ERROR in retrieving NovelChapter key" << endl << flush;
			return 8;
		}

		piSpecAttrAccessOnNovel -> Release();

		// Get an instance of the CAAOsmNovel StartUp

		CATUnicodeString novel1("CAAOsmNovel1");

		CATISpecObject_var spNovelInst1 = NULL_var;
		rc = novelSUHandler.Instanciate(spNovelInst1, piRootContainer, novel1);
		if (SUCCEEDED(rc))
			cout << "CAAOsmNovel SU instance 1 created OK" << endl << flush;
		else
		{
			cout <<"ERROR in creating instance 1 of CAAOsmNovel SU" << endl << flush;
			piRootContainer -> Release();
			return 3;
		}

		// Valuate the list of attributes "NovelChapter" for "CAAOsmNovel1" with the instances of
		// "CAAOsmChapter" ("CAAOsmChapter1", "CAAOsmChapter2" and "CAAOsmChapter3") just defined.

		CATISpecAttrAccess *piSpecAttrAccessOnNov1 = NULL;
		rc = spNovelInst1 -> QueryInterface(IID_CATISpecAttrAccess, 
			(void**) &piSpecAttrAccessOnNov1);

		if (SUCCEEDED(rc) && piSpecAttrAccessOnNov1 != NULL) 
		{
			piSpecAttrAccessOnNov1 -> SetSpecObject(piKeyNovelChapter,
				spChapterInst1);
			piSpecAttrAccessOnNov1 -> SetSpecObject(piKeyNovelChapter,
				spChapterInst2);
			piSpecAttrAccessOnNov1 -> SetSpecObject(piKeyNovelChapter,
				spChapterInst3);
		}

		else
		{
			cout << "ERROR in QueryInterface on CATISpecAttrAccess for NovelInst1" << endl << flush;
			return 3;
		}

		/* Attributes of tk_list(tk_specobject) and tk_list(tk_component) types are assigned
		an iterator.  By using such an iterator, you can scan right through a list.  
		Functions are provided for moving in either direction. */

		/*-------------------------------------------------*/
		/* Scan through the "CAAOsmNovel1" Chapter titles. */
		/*-------------------------------------------------*/

		int ListSize = piSpecAttrAccessOnNov1 -> GetListSize(piKeyNovelChapter);
		cout << "The Novel chapter titles (" << ListSize <<") are: " << endl;
		for ( int i=1 ; i <= ListSize ; i++ )
		{
			CATISpecObject *piNovelChapter = piSpecAttrAccessOnNov1 -> GetSpecObject(piKeyNovelChapter,i);
			if (NULL == piNovelChapter)
			{
				cout << "ERROR in GetSpecObject on piNovelChapter" << endl << flush;         
				return 12;
			}

			CATISpecAttrAccess *piSpecAttrAccessOnNovChapt = NULL;
			rc = piNovelChapter -> QueryInterface(IID_CATISpecAttrAccess, 
				(void**) &piSpecAttrAccessOnNovChapt);
			piNovelChapter -> Release(); 
			piNovelChapter = NULL ;

			if (FAILED(rc)) 
			{
				cout << "ERROR in QueryInterface on CATISpecAttrAccess for CAAOsmNovel SU" << endl << flush;          
				return 3;
			}
			cout << piSpecAttrAccessOnNovChapt -> GetString(piKeyChapterTitle).CastToCharPtr() << endl;

			piSpecAttrAccessOnNovChapt -> Release(); piSpecAttrAccessOnNovChapt  = NULL ;
		}

		piSpecAttrAccessOnNov1 -> Release(); piSpecAttrAccessOnNov1 = NULL ;
		piKeyChapterTitle -> Release(); piKeyChapterTitle = NULL ;
		piKeyNovelChapter -> Release(); piKeyNovelChapter = NULL ;

		/*------------------------------------------------*/
		/* Illustrate the behavior of aggregated features */
		/*------------------------------------------------*/

		// ChaptInst1 is aggregated to NovelInst1:  it belongs to NovelInst1 who
		// is its "parent" and it cannot be assigned to another feature.  If the "parent"
		// feature is deleted, so is the feature aggregated to it.

		// Show that the father of ChaptInst1 is NovelInst1 

		CATISpecObject *piChaptInst1Father = spChapterInst1 -> GetFather();
		if (NULL != piChaptInst1Father)
		{
			cout << "The 'ChapterInst1' parent feature is " << endl;
			cout << piChaptInst1Father -> GetName().ConvertToChar() << endl;
			piChaptInst1Father -> Release();
			piChaptInst1Father = NULL;
		}

		/*---------------------------------------------------*/
		/*  Save and remove the document and end the session */
		/*---------------------------------------------------*/

		// @CSC-Filter UNER 
		rc = CATDocumentServices::SaveAs(*pDoc,
			argv[2]);
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
	
}

