// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
// Abstract of Use Case "CAAOsmReferencedAttr":
// -------------------------------------------
//
// This sample illustrates working with "referenced" features.  It loads an
// existing catalog containing StartUps, some of which are retrieved and new 
// instances of them are created.  Then, certain features are assigned values and
// then used as "referenced" feature attributes.
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
//  SetSpecObject:   Valuates an attribute with a feature object
//  GetFather:       Retrieves the father of an aggregated feature attribute
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
//  5 - ERROR in CATOsmSUHandler
//  6 - ERROR in RetrieveSU
//  7 - ERROR in Instanciate
//  8 - ERROR in GetAttrKey
//  9 - ERROR in saving the document
// 10 - ERROR in removing the document from the session
// 11 - ERROR in deleting the session 
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAOsmReferencedAttr CatalogName DocumentStorageName" 
//  where the "CatalogName" is the name and .CATfct extension (without the path) of the
//     catalog created by the CAAOsmCatalogSU use case and found under the
//     "Ws" + "Os" + resources + graphic directory, and
//  where the "DocumentStorageName" is the entire pathname, name and .CATPart extension
//    under which the new document is to be stored. 
//
//=============================================================================

//System Framework
#include "CATUnicodeString.h"

//ObjectModelerBase Framework
#include "CATSessionServices.h"               // Create_Session and Delete_Session
#include "CATInit.h"                          // GetRootContainer
#include "LifeCycleObject.h"                  // Delete a feature (remove)
#include "CATDocumentServices.h"              // New (creating a new document),
                                              //    SaveAs, Remove document
#include "CATDocument.h"                      // Document 

//ObjectSpecsModeler Framework                
#include "CATISpecObject.h"                   // Instanciate, GetFather
#include "CATISpecAttrAccess.h"               // GetAttrKey, SetString, SetSpecObject
#include "CATISpecAttrKey.h"                  // Result of GetAttrKey    
#include "CATOsmSUHandler.h"				  // RetrieveSU, Instanciate
#include "CATSession.h"
#include "CATBaseUnknown.h"				  // For CATIdent interface inclusion
#include "CATIContainer.h"

//Note : If you want to instanciate feature from a feature, then as of now you will have to use Instanciate() method of
//       CATISpecObject

//Other
#include <iostream.h>

int main (int argc, char * argv[] )
{ 

/*--------------------------------------------------------------*/
/* Open a Session:  this is a necessary step in a batch program */
/*--------------------------------------------------------------*/
	
	char* pSessionName = "CAA2_Sample_Session";
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
/* Get a CATOsmSUHandler on the StartUp "CAAOsmPublisher".    */
/*--------------------------------------------------------*/

    CATUnicodeString CatalogName = argv[1];
	CATUnicodeString clientId("CAAOsmClientId");
	CATUnicodeString publisherSUType("CAAOsmPublisher");

	CATOsmSUHandler publisherSUHandler(publisherSUType, clientId, CatalogName);

	CATISpecObject_var spPublisherSU = NULL_var;

	rc = publisherSUHandler.RetrieveSU(spPublisherSU);
	if (NULL_var != spPublisherSU && SUCCEEDED(rc))
		cout << "CAAOsmPublisher StartUp retrieved OK" << endl << flush;
    else
	{
		cout << "ERROR in retrieving CAAOsmPublisher StartUp" << endl << flush;
		return 6;
	}

// Get a CATISpecObject handle on the CAAOsmPublisher StartUp

// Retrieve the attribute keys to the "CAAOsmPublisher" attributes:  "PublisherName" and 
// "PublisherAddress"

	CATISpecAttrAccess *piSpecAttrAccessOnPubSU = NULL;
	rc = spPublisherSU -> QueryInterface(IID_CATISpecAttrAccess,
                                        (void**) &piSpecAttrAccessOnPubSU);
	if (FAILED(rc)) 
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for CAAOsmPublisher SU" << endl << flush;
        piRootContainer -> Release();
		return 3;
	}

	CATISpecAttrKey *piKeyPublisherName = piSpecAttrAccessOnPubSU -> GetAttrKey("PublisherName");
	if (NULL == piKeyPublisherName)
	{
		cout << "ERROR in retrieving PublisherName key" << endl << flush;
		piRootContainer -> Release();
		return 8;
	}

	CATISpecAttrKey *piKeyPublisherAddress = piSpecAttrAccessOnPubSU -> GetAttrKey("PublisherAddress");
	if (NULL == piKeyPublisherAddress)
	{
		cout << "ERROR in retrieving PublisherAddress key" << endl << flush;
		piRootContainer -> Release();
		return 8;
	}
	piSpecAttrAccessOnPubSU -> Release();

/*-------------------------------------------------------------------------------*/
/* Create an instance of "CAAOsmPublisher" in the root container of the document */
/*-------------------------------------------------------------------------------*/

	CATUnicodeString publisher1("CAAOsmPublisher1");

	CATISpecObject_var spPublisherInst1 = NULL_var;
	rc = publisherSUHandler.Instanciate(spPublisherInst1, piRootContainer, publisher1);
    if (SUCCEEDED(rc))
		cout << "Publisher SU instance 1 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 1 of CAAOsmPublisher SU" << endl << flush;
	    piRootContainer -> Release();
		return 3;
	}

/*-----------------------------------------------------------------------------------*/
/* Valuate the attributes of the new "CAAOsmPublisher" instance ("CAAOsmPublisher1") */
/*-----------------------------------------------------------------------------------*/

	CATISpecAttrAccess *piSpecAttrAccessOnPub1 = NULL;
	rc = spPublisherInst1 -> QueryInterface(IID_CATISpecAttrAccess, 
		                              (void**) &piSpecAttrAccessOnPub1);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for Publisher Instance 1" << endl << flush;
        piRootContainer -> Release();
		return 3;
	}

	piSpecAttrAccessOnPub1 -> SetString(piKeyPublisherName,
		                                "Collins Press");
	piSpecAttrAccessOnPub1 -> SetString(piKeyPublisherAddress,
		                                "London");
	piSpecAttrAccessOnPub1 -> Release();
	
/*-------------------------------------------------------------------------*/
/* Assign the same "reference" feature (piPubInst1) to several features: */ 
/* illustrate that the same "referenced" features can be assigned to       */
/* several different features at the same time.                            */
/*-------------------------------------------------------------------------*/


/* Get a CATOsmSUHandler on the StartUp "CAAOsmNovel".    */

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

// Get the attribute key of CAAOsmNovel's attribute "BookPublisher"

	CATISpecAttrAccess *piSpecAttrAccessOnNovel = NULL;
	rc = spNovelSU -> QueryInterface(IID_CATISpecAttrAccess,
		                             (void**) &piSpecAttrAccessOnNovel);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for CAAOsmNovel SU" << endl << flush;
        piRootContainer -> Release();
		return 3;
	}	
	
	CATISpecAttrKey *piKeyNovelPublisher = piSpecAttrAccessOnNovel -> GetAttrKey("BookPublisher");
	if (NULL == piKeyNovelPublisher)
	{
		cout << "ERROR in retrieving NovelPublisher key" << endl << flush;
		piRootContainer -> Release();
		return 8;
	}
	
	piSpecAttrAccessOnNovel -> Release();

	// Get a new instance of CAAOsmNovel

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

	// Valuate attribute "BookPublisher" for "CAAOsmNovel1" with the new instance of
	// "CAAOsmPublisher" ("CAAOsmPublisher1")

	CATISpecAttrAccess *piSpecAttrAccessOnNov1 = NULL;
	rc = spNovelInst1 -> QueryInterface(IID_CATISpecAttrAccess,
										(void**) &piSpecAttrAccessOnNov1);

	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for NovelInst1" << endl << flush;
		piRootContainer -> Release();
		return 3;
	}	
	
	piSpecAttrAccessOnNov1 -> SetSpecObject(piKeyNovelPublisher,
		                                    spPublisherInst1);

	piSpecAttrAccessOnNov1 -> Release();

// Create a new instance of "CAAOsmNovel" in the root container of the document

	CATUnicodeString novel2("CAAOsmNovel2");
	CATISpecObject_var spNovelInst2 = NULL_var;

	rc = novelSUHandler.Instanciate(spNovelInst2, piRootContainer, novel2);
    if (FAILED(rc))
	{
		cout << "ERROR in creating instance 2 of CAAOsmNovel SU" << endl << flush;
        piRootContainer -> Release();
		return 7;
	}	
    else cout <<"CAAOsmNovel SU instance 2 created OK" << endl << flush;


// Valuate attribute "BookPublisher" for "CAAOsmNovel2" with the new instance of
// "CAAOsmPublisher" ("CAAOsmPublisher1")

	CATISpecAttrAccess *piSpecAttrAccessOnNov2 = NULL;
	rc = spNovelInst2 -> QueryInterface(IID_CATISpecAttrAccess,
		                                (void**) &piSpecAttrAccessOnNov2);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for NovelInst2" << endl << flush;
        piRootContainer -> Release();
		return 3;
	}	
	
	piSpecAttrAccessOnNov2 -> SetSpecObject(piKeyNovelPublisher,
		                                    spPublisherInst1);

	piKeyNovelPublisher -> Release();
	piSpecAttrAccessOnNov2 -> Release();

/*--------------------------------------------*/
/* Create a new instance of "CAAOsmPublisher" */
/*--------------------------------------------*/

	CATUnicodeString publisher2("CAAOsmPublisher2");
	CATISpecObject_var spPubInst2 = NULL_var;

	rc = publisherSUHandler.Instanciate(spPubInst2, piRootContainer, publisher2);
    if (SUCCEEDED(rc))
		cout << "CAAOsmPublisher SU instance 2 created OK" << endl << flush;
	else 
	{
		cout <<"ERROR in creating CAAOsmPublisher SU instance 2" << endl << flush;
        piRootContainer -> Release();
		return 7;
	}

/*-----------------------------------------------------------------------------------*/
/* Valuate the attributes of the new "CAAOsmPublisher" instance ("CAAOsmPublisher2") */
/*-----------------------------------------------------------------------------------*/
	CATISpecAttrAccess *piSpecAttrAccessOnPub2 = NULL;
	rc = spPubInst2 -> QueryInterface(IID_CATISpecAttrAccess,
		                              (void**) &piSpecAttrAccessOnPub2);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for PubInst2" << endl << flush;
        piRootContainer -> Release();
		return 3;
	}	
	
	piSpecAttrAccessOnPub2 -> SetString(piKeyPublisherName,
		                                "Larousse");
	piSpecAttrAccessOnPub2 -> SetString(piKeyPublisherAddress, 
		                                "Paris");

	piKeyPublisherName -> Release();
	piKeyPublisherAddress -> Release();
	piSpecAttrAccessOnPub2 -> Release();

/*-----------------------------------------------------------------------------------------*/
/* Assign the new "CAAOsmPublisher" reference attribute to the feature "CAAOsmDictionary1" */
/*-----------------------------------------------------------------------------------------*/


/* Get a CATOsmSUHandler on the StartUp "CAAOsmDictionary".    */

	CATUnicodeString dictionarySUType("CAAOsmDictionary");

	CATOsmSUHandler dictionarySUHandler(dictionarySUType, clientId, CatalogName);

	// Get a CATISpecObject handle on the CAAOsmDictionary StartUp

	CATISpecObject_var spDictionarySU = NULL_var;
	rc = dictionarySUHandler.RetrieveSU(spDictionarySU);
	if (SUCCEEDED(rc)) cout << "CAAOsmDictionary StartUp retrieved OK" << endl << flush;
    else
	{
		cout << "ERROR in retrieving CAAOsmDictionary StartUp" << endl << flush;
        piRootContainer -> Release();
		return 7;
	}
	
// Get the dictionary's attribute key "BookPublisher"

	CATISpecAttrAccess *piSpecAttrAccessOnDict = NULL;
	rc = spDictionarySU -> QueryInterface(IID_CATISpecAttrAccess, 
		                                  (void**) &piSpecAttrAccessOnDict);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for CAAOsmDictionary SU" << endl << flush;
        piRootContainer -> Release();
		return 3;
	}	
	
	CATISpecAttrKey *piKeyDictPublisher = piSpecAttrAccessOnDict -> GetAttrKey("BookPublisher");
	if (NULL == piKeyDictPublisher)
	{
		cout << "ERROR in retrieving DictPublisher key" << endl << flush;
		piRootContainer -> Release();
		return 8;
	}
	piSpecAttrAccessOnDict -> Release();

// Get an instance of the CAAOsmDictionary StartUp

	CATUnicodeString dictionary1("CAAOsmDictionary1");

   CATISpecObject_var spDictionaryInst = NULL_var;
   rc = dictionarySUHandler.Instanciate(spDictionaryInst, piRootContainer, dictionary1);
   if (SUCCEEDED(rc))
		cout << "Dictionary SU instance 1 created OK" << endl << flush;
   else 
   {
	   cout <<"ERROR in creating instance 1 of CAAOsmDictionary SU" << endl << flush;
	   piRootContainer -> Release();
	   return 3;
   }

// Valuate attribute "BookPublisher" for "CAAOsmDictionary1" with the new instance of
// "CAAOsmPublisher" (CAAOsmPublisher2")

	CATISpecAttrAccess *piSpecAttrAccessOnDict1 = NULL;
	rc = spDictionaryInst -> QueryInterface(IID_CATISpecAttrAccess,
		                               (void**) &piSpecAttrAccessOnDict1);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for DictInst1" << endl << flush;
        piRootContainer -> Release();
		return 3;
	}	
	
	piSpecAttrAccessOnDict1 -> SetSpecObject(piKeyDictPublisher,
		                                     spPubInst2);
	piSpecAttrAccessOnDict1 -> Release();

/*---------------------------------------------------------------------------*/
/* Illustrate that the notion of "father" for a referenced attribute has no  */
/* meaning and that deleting the feature does not delete the referenced      */
/* attribute which can continue to be attached to other attributes.          */
/*---------------------------------------------------------------------------*/

	CATISpecObject *piPubInst2Father = spPubInst2 -> GetFather();
	if (NULL == piPubInst2Father) cout << "OK:  Feature Publisher2 does not have a father!" << endl << flush;
	else 
	{
		cout << "ERROR:  Feature Publisher2 should not have a father and it does!" << endl << flush;
	    piPubInst2Father -> Release();
	}
	
// Delete feature "CAAOsmDictionary1" (DictInst1)

	LifeCycleObject *pDict = NULL;
	rc = spDictionaryInst -> QueryInterface(IID_LifeCycleObject,
		                               (void**) &pDict);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on LifeCycleObject for Dictionary1" << endl << flush;
        piRootContainer -> Release();
		return 3;
	}
	else pDict -> remove();

	pDict -> Release();

// To show that "CAAOsmPublisher2" is not also deleted, assign it to a new instance of
// "CAAOsmDictionary"

// Create a new instance of "Dictionary"
	CATUnicodeString dictionary2("CAAOsmDictionary2");
   CATISpecObject_var spDictionaryInst2 = NULL_var;

   rc = dictionarySUHandler.Instanciate(spDictionaryInst2, piRootContainer, dictionary2);
   if (SUCCEEDED(rc))
		cout << "Dictionary SU instance 2 created OK" << endl << flush;
   else 
   {
	   cout <<"ERROR in creating instance 2 of CAAOsmDictionary SU" << endl << flush;
        piRootContainer -> Release();
		return 3;
   }
	piRootContainer -> Release();

// Assign "CAAOsmPublisher2" to "CAAOsmDictionary2"
	CATISpecAttrAccess *piSpecAttrAccessOnDict2 = NULL;
	rc = spDictionaryInst2 -> QueryInterface(IID_CATISpecAttrAccess, 
		                               (void**) &piSpecAttrAccessOnDict2);

	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for DictInst2" << endl << flush;
		return 3;
	}	
	
	piSpecAttrAccessOnDict2 -> SetSpecObject(piKeyDictPublisher,
		                                      spPubInst2);
	
	piKeyDictPublisher -> Release();
	piSpecAttrAccessOnDict2 -> Release();

/*---------------------------------------------------*/
/* Save and remove the document  and end the session */
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

