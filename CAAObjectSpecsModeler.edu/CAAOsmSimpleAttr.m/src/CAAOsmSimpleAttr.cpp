// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
// Abstract of Use Case "CAAOsmSimpleAttr":
// ---------------------------------------
//
// This sample illustrates how to load an existing Catalog containing StartUps,    
// how to retrieve the StartUps, how to instantiate them, assign values to their
// attributes and how to add new attributes to feature instances.
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
//  GetRootContainer:Retrieves the root container of the new document
//  CATOsmSUHandler :To get a handler for the particular StartUp from the Catalog
//  RetrieveSU:      Retrieves StartUps from the catalog using the CATOsmSUHandler
//  Instantiate:     Creates a new feature from an existing one or from a StartUp
//  GetAttrKey:      Retrieves the attribute key for a given attribute name on
//                      a given features
//  SetString:       Valuates a string-type attribute
//  AddAttribute:    Adds a new attribute to a feature
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
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAOsmSimpleAttr CatalogName DocumentStorageName" 
//  where the "CatalogName" is the name and .CATfct extension (without the path) of the
//     catalog created by the CAAOsmCatalogSU use case and found under the
//     "Ws" + "Os" + resources + graphic directory, and
//  where the "DocumentStorageName" is the entire pathname, name and .CATPart extension
//    under which the new document is to be stored. 
//=============================================================================

//System Framework
#include "CATUnicodeString.h"

//ObjectModelerBase Framework
#include "CATSessionServices.h"          // Create_Session and Delete_Session
#include "CATDocument.h"                 // 
#include "CATDocumentServices.h"         // New (creating a new document)
                                         //    SaveAs, Remove document
#include "CATInit.h"                     // GetRootContainer

//ObjectSpecsModeler Framework

#include "CATISpecObject.h"              // Instanciate, AddAttribute
#include "CATISpecAttribute.h"           // Result from AddAttribute
#include "CATISpecAttrAccess.h"          // GetAttrKey, SetString, SetInteger
#include "CATISpecAttrKey.h"             // Used in: SetString, SetInteger
#include "CATOsmSUHandler.h"			 // RetrieveSU, Instanciate
#include "CATSession.h"
#include "CATBaseUnknown.h"				  // For CATIdent interface inclusion
#include "CATIContainer.h"

#include <iostream.h>
//Note : If you want to instanciate feature from a feature, then as of now you will have to use Instanciate() method of
//       CATISpecObject

int main (int argc, char * argv[])
{ 
/*--------------------------------------------------------------*/
/* Open a Session:  this is a necessary step in a batch program */
/*--------------------------------------------------------------*/

	char *sessionName = "CAA2_Sample_Session";
	CATSession *pSession = NULL;
	HRESULT rc = ::Create_Session(sessionName, pSession);
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
/* Get a CATOsmSUHandler on the StartUp "CAAOsmNovel".    */
/*--------------------------------------------------------*/

	CATUnicodeString CatalogName = argv[1];
	CATUnicodeString clientId("CAAOsmClientId");
	CATUnicodeString novelSUType("CAAOsmNovel");

	CATOsmSUHandler novelSUHandler(novelSUType, clientId, CatalogName);

// Get a CATISpecObject handle on the CAAOsmNovel StartUp

	CATISpecObject_var spNovelSU = NULL_var;
	rc = novelSUHandler.RetrieveSU(spNovelSU);
	if (NULL_var != spNovelSU && SUCCEEDED(rc)) cout << "CAAOsmNovel StartUp retrieved OK" << endl << flush;
    else
	{
		cout << "ERROR in retrieving CAAOsmNovel StartUp" << endl << flush;
		return 6;
	}

// Retrieve the attribute key to some ofthe CAAOsmNovel StartUp's attributes

	CATISpecAttrAccess *piSpecAttrAccessOnNovelSU = NULL;
	rc = spNovelSU -> QueryInterface(IID_CATISpecAttrAccess,
		                             (void**) &piSpecAttrAccessOnNovelSU);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for NovelSU" << endl << flush;
		piRootContainer -> Release();
		return 3;
	}

	CATISpecAttrKey *piKeyTitle = piSpecAttrAccessOnNovelSU -> GetAttrKey("Title");
	if (NULL == piKeyTitle)
	{
		cout << "ERROR in retrieving Title key" << endl << flush;
		piRootContainer -> Release();
		return 8;
	}

    CATISpecAttrKey *piKeyAuthor = piSpecAttrAccessOnNovelSU -> GetAttrKey("Author");
	if (NULL == piKeyAuthor)
	{
		cout << "ERROR in retrieving Author key" << endl << flush;
		piRootContainer -> Release();
		return 8;
	}

	piSpecAttrAccessOnNovelSU -> Release();
	
/*---------------------------------------------------------------------*/
/* Create an instance of "CAAOsmNovel" in the root container of the document */
/*---------------------------------------------------------------------*/

	CATISpecObject_var spNovelInst = NULL_var;
	rc = novelSUHandler.Instanciate(spNovelInst, piRootContainer, CATUnicodeString("CAAOsmNovel1"));

	if (NULL_var != spNovelInst && SUCCEEDED(rc))
		cout << "CAAOsmNovel SU instance 1 created OK" << endl << flush;
	else 
	{
		cout << "ERROR in creating instance 1 of CAAOsmNovel SU" << endl << flush;
		piRootContainer -> Release();
		return 7;
	}
	
/*-----------------------------------------------------------------------------------*/
/* Valuate some of the attributes of the new "CAAOsmNovel" instance ("CAAOsmNovel1") */
/*-----------------------------------------------------------------------------------*/

	CATISpecAttrAccess *piSpecAttrAccessOnNovelInst = NULL;
	rc = spNovelInst -> QueryInterface(IID_CATISpecAttrAccess,
		                                (void**) &piSpecAttrAccessOnNovelInst);
	if (FAILED(rc)) 
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for NovelInst1" << endl << flush;
		piRootContainer -> Release();
		return 3;
	}
	
	piSpecAttrAccessOnNovelInst -> SetString(piKeyTitle,
		                                     "The Three Musketeers");
	piSpecAttrAccessOnNovelInst -> SetString(piKeyAuthor, 
		                                     "Alexandre Dumas");
		
	piKeyTitle -> Release();
	piKeyAuthor -> Release();

/*-------------------------------------------------------------------------------*/
/* Add and valuate new attributes to the "CAAOsmNovel" instance ("CAAOsmNovel1") */
/*-------------------------------------------------------------------------------*/

	CATISpecAttribute *piVolumeNumber = spNovelInst -> AddAttribute(CATUnicodeString("Volume"),
		                                                             tk_integer);
    if (NULL != piVolumeNumber)
        piVolumeNumber -> Release();

	CATISpecAttrKey *piKeyVolume = piSpecAttrAccessOnNovelInst -> GetAttrKey("Volume");
	if (NULL == piKeyVolume)
	{
		cout << "ERROR in retrieving Volume key" << endl << flush;
		return 8;
	}

	piSpecAttrAccessOnNovelInst -> SetInteger(piKeyVolume,
		                                      1);
	piKeyVolume -> Release();

	CATISpecAttribute *piTranslator = spNovelInst -> AddAttribute(CATUnicodeString("Translator"),
		                                                           tk_string);
    if (NULL != piTranslator)
	    piTranslator -> Release();

	CATISpecAttrKey *piKeyTrans = piSpecAttrAccessOnNovelInst -> GetAttrKey("Translator");
	if (NULL == piKeyTrans)
	{
		cout << "ERROR in retrieving Trans key" << endl << flush;
		return 8;
	}

	piSpecAttrAccessOnNovelInst -> SetString(piKeyTrans,
		                                     "John D. Smith");
	piKeyTrans -> Release();

	piSpecAttrAccessOnNovelInst -> Release();
	piSpecAttrAccessOnNovelInst = NULL;
	
/*--------------------------------------------------------------------------------------- */
/* Create an instance of "CAAOsmNovel1":  the new instance inherits all of the attributes */
/* and their values of "CAAOsmNovel1"                                                     */
/*----------------------------------------------------------------------------------------*/

	CATISpecObject_var spNovelInst2 = spNovelInst -> Instanciate(CATUnicodeString("CAAOsmNovel2"),
		                                                       piRootContainer);

	if (NULL_var != spNovelInst2) cout << "New instance of NovelInst2 created OK" << endl << flush;
	else 
	{
		cout << "ERROR in creating new instance of NovelInst1" << endl << flush;
		piRootContainer -> Release();
		return 7;
	}

//*------------------------------------------------*/
//* Valuate the "CAAOsmNovel2" attribute "Volume". */
//*------------------------------------------------*/

// Note that the attribute "Volume" was added to the first instance of CAAOsmNovel.  The 
// acquisition of its key is not global:  it needs to be done on each instance, unlike
// the key acquisition on a StartUp.
	
	rc = spNovelInst2 -> QueryInterface(IID_CATISpecAttrAccess,
		                                (void**) &piSpecAttrAccessOnNovelInst);
	spNovelInst2 -> Release();
	if (FAILED(rc)) 
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for NovelInst2" << endl << flush;
		piRootContainer -> Release();
		return 3;
	}
	
	CATISpecAttrKey *piKeyVolume2 = piSpecAttrAccessOnNovelInst -> GetAttrKey("Volume");
	if (NULL == piKeyVolume2)
	{
		cout << "ERROR in retrieving Volume2 key" << endl << flush;
		return 8;
	}

	piSpecAttrAccessOnNovelInst -> SetInteger(piKeyVolume2, 
		                                      2);
	if (NULL != piKeyVolume2)
		cout << "Success in setting Volume2 key" << endl << flush;
	else
	{
		cout << "Fail in setting Volume2 key" << endl << flush;
		return 6;
	}

	piKeyVolume2 -> Release();
	piSpecAttrAccessOnNovelInst -> Release();

/*-------------------------------------*/
/* Retrieve StartUp "CAAOsmDictionary" */
/*-------------------------------------*/

    CATBaseUnknown *pDictionarySU = NULL;
	CATUnicodeString DictionarySUType("CAAOsmDictionary");

	CATOsmSUHandler DictionarySUHandler(DictionarySUType, clientId, CatalogName);

	CATISpecObject_var spDictionarySU = NULL_var;
	rc = DictionarySUHandler.RetrieveSU(spDictionarySU);
	if (NULL_var != spDictionarySU) cout << "CAAOsmDictionary StartUp retrieved OK" << endl << flush;
    else
	{
		cout << "ERROR in retrieving CAAOsmDictionary StartUp" << endl << flush;
        piRootContainer -> Release();
		return 6;
	}

    	
// Retrieve the attribute key of some of the "CAAOsmDictionary" attributes:  "Title" and
// "Language"

	CATISpecAttrAccess *piSpecAttrAccessOnDictSU = NULL;
	rc = spDictionarySU -> QueryInterface(IID_CATISpecAttrAccess,
		                                  (void**) &piSpecAttrAccessOnDictSU);
	if (FAILED(rc)) 
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for CAAOsmDictionary SU" << endl << flush;
        piRootContainer -> Release();
		return 3;
	}
	
	CATISpecAttrKey *piKeyDictTitle = piSpecAttrAccessOnDictSU -> GetAttrKey("Title");
	if (NULL == piKeyDictTitle)
	{
		cout << "ERROR in retrieving DictTitle key" << endl << flush;
		piRootContainer -> Release();
		return 8;
	}

	CATISpecAttrKey *piKeyLang = piSpecAttrAccessOnDictSU -> GetAttrKey("Language");
	if (NULL == piKeyLang)
	{
		cout << "ERROR in retrieving Lang key" << endl << flush;
		piRootContainer -> Release();
		return 8;
	}

	piSpecAttrAccessOnDictSU -> Release();
	
///*--------------------------------------------------------------------------------*/
///* Create an instance of "CAAOsmDictionary" in the root container of the document */
///*--------------------------------------------------------------------------------*/


   CATISpecObject_var spDictInst = NULL_var;
   rc = DictionarySUHandler.Instanciate(spDictInst, piRootContainer, CATUnicodeString("CAAOsmDictionary1"));
   if (SUCCEEDED(rc))
		cout << "Dictionary SU instance 2 created OK" << endl << flush;
   else 
   {
	   cout <<"ERROR in creating instance 2 of CAAOsmDictionary SU" << endl << flush;
        piRootContainer -> Release();
		return 3;
   }

//*---------------------------------------------------------------------------------*/
//* Valuate some of the attributes of the new "Dictionary" instance ("Dictionary1") */
//*---------------------------------------------------------------------------------*/

	CATISpecAttrAccess *piSpecAttrAccessOnDictInst = NULL;
	rc = spDictInst -> QueryInterface(IID_CATISpecAttrAccess, 
		                              (void**) &piSpecAttrAccessOnDictInst);

	if (FAILED(rc)) 
	{
		cout << "ERROR in QueryInterface on CATISpecObject for DictInst1" << endl << flush;
        return 3;
	}
		
	piSpecAttrAccessOnDictInst -> SetString(piKeyDictTitle,
		                                    "Webster's New World Dictionary");
	piSpecAttrAccessOnDictInst -> SetString(piKeyLang, 
		                                    "English");

	piKeyDictTitle -> Release();
	piKeyLang -> Release();
	piSpecAttrAccessOnDictInst -> Release();


/*---------------------------------------------------*/
/*  Save and remove the document and end the session */
/*---------------------------------------------------*/
    // @CSC-Filter UNER
	rc = CATDocumentServices::SaveAs (*pDoc, argv[2]);
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
	rc = ::Delete_Session(sessionName);
	if (FAILED(rc))
	{
			cout << "ERROR in deleting session" << endl << flush;
			return 11;
	}
		
	return 0;
}
