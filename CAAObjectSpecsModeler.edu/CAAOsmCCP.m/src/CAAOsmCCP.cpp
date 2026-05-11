// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
// Abstract of Use Case "CAAOsmCCP":
// -------------------------------------
//
// This sample illustrates how to perform CCP (cut, copy and paste) operations on spec objects.
// Two cases are exemplified:  one for batch conditions where the notion of extracting objects
// onto the clipboard is ignored, the other for interactive conditions, where objects must first
// be extracted onto the clipboard before they can be pasted or removed. 
//
//=============================================================================
//  Main Methods:
//  ------------
//
//  Create_Session:                Creates a new session, necessary in a batch program
//  New:                           Creates a new document in which to store the new
//                                    features
//  CATCreateApplicativeContainer: Creates an applicative container within the new
//                                    document
//  CATOsmSUHandler :To get a handler for the particular StartUp from the Catalog
//  RetrieveSU:      Retrieves StartUps from the catalog using the CATOsmSUHandler
//  Instanciate:                   Creates a new feature from an existing StartUp
//  BoundaryExtract:               Creates a list of objects to be extracted
//  Extract:                       Creates a structure to receive the boundary objects
//  Remove(CATICutAndPastable):    Removes objects  
//  Paste:                         Creates new objects from a given list of objects                   
//  SaveAs:                        Saves the document 
//  Remove(CATDocumentServices):   Removes the document from the session
//  Delete_Session:                Deletes the session
//
//=============================================================================
//  Return Errors:
//  -------------
//  1 - ERROR in Create_Session
//  2 - ERROR in New
//  3 - ERROR in QueryInterface
//  4 - ERROR in CATCreateApplicativeContainer
//  5 - ERROR in CATOsmSUHandler
//  6 - ERROR in RetrieveSU
//  7 - ERROR in Instanciate
//  8 - ERROR in Paste
//  9 - ERROR in Remove
// 10 - ERROR in BoundaryExtract
// 11 - ERROR in SaveAs
// 12 - ERROR in Remove(CATDocumentServices)
// 13 - ERROR in Delete_Session
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAOsmCCP CatalogName DocumentStorageName" 
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
#include "CATSessionServices.h"          // Create_Session and Delete_Session
#include "CATDocument.h"                 // 
#include "CATDocumentServices.h"         // New (creating a new document),
                                         //    SaveAs, Remove document
#include "CATAppliContServices.h"        // CATCreateApplicativeContainer, 
#include "CATICutAndPastable.h"          // BoundaryExtract, Paste, Remove

//ObjectSpecsModeler Framework
#include "CATISpecObject.h"              // Instanciate

#include "SpecBindNativeFormat.h"        // Initialization of default formats

#include "CATOsmSUHandler.h"			 // RetrieveSU, Instanciate
#include "CATSession.h"			  
#include "CATBaseUnknowns.h"			
#include "CATBaseUnknown.h"				// For CATIdent interface inclusion
#include "CATIContainer.h"
#include "CATFormat.h"


#include <iostream.h>

int main (int argc, char * argv[])
{ 
//---------------------------------------------------------------
// Open a Session:  this is a necessary step in a batch program 
//---------------------------------------------------------------

	char *sessionName = "CAA2_Sample_Session";
	CATSession *pSession = NULL;
	HRESULT rc = ::Create_Session(sessionName, pSession);
	if ((FAILED(rc)) || (NULL == pSession))
	{
		cout << "ERROR in creating session" << endl << flush;
		return 1;
	}
	
//-------------------------------------
// Create a new CATPart document 
//-------------------------------------
	
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

// Lock the document to avoid link problems during CCP operations
	CATLockDocument(*pDoc);

//----------------------------------------------------------------
// FORMATS:  Define a format type by declaring a format supported
//           by the CCP system.  This step is necessary even
//           if no formats are to be actually used.
//----------------------------------------------------------------

    IdFormat FEATURE_FORMAT = "CATFeatCont";
    const CATFormat *featFormat = SpecBindNativeFormat(FEATURE_FORMAT);

//---------------------------------------------------------------
// Create the "source" applicative container within the document 
//---------------------------------------------------------------

	CATIdent idAppliCont = "CATFeatCont";
	CATUnicodeString sourceAppliContId ("CAAOsmSourceContainer");
	CATBaseUnknown *pSourceContainer = NULL;
    rc = ::CATCreateApplicativeContainer(&pSourceContainer,        // appli cont created
                                         pDoc,                     // document  
									     idAppliCont,              // type of appli cont
									     IID_CATIContainer,        // interface type of appli cont
									     "",                       // supertype of appli cont 
									     sourceAppliContId);       // name of appli cont
	if (SUCCEEDED(rc)) cout << "Source applicative container created OK" << endl << flush;
	else
	{
		cout << "ERROR in creating source applicative container" << endl << flush;
	    return 4;
    }

    // Gets a CATIContainer handle on the applicative container
	CATIContainer *piSourceContainer = (CATIContainer*) pSourceContainer;

    // Declares the container to the Undo/redo mechanism
    // only in interactive code otherwise the method return E_FAIL 
    // because, there is no undo/redo management
    /*
    rc = ::CATOmbPerformAfterContainerCreation( piSourceContainer );
    if ( FAILED(rc) )
    {
       cout <<" Error in declaring the container to the Undo/redo mechanism" << endl;
       return 1 ;
    }
    */
//---------------------------------------------------------------
// Create the "target" applicative container within the document 
//---------------------------------------------------------------

	CATUnicodeString targetAppliContId ("CAAOsmTargetContainer");
	CATBaseUnknown *pTargetContainer = NULL;
	rc = ::CATCreateApplicativeContainer(&pTargetContainer,        // appli cont created
                                         pDoc,                     // document  
									     idAppliCont,              // type of appli cont
									     IID_CATIContainer,        // interface type of appli cont
									     "",                       // supertype of appli cont 
									     targetAppliContId);       // name of appli cont
	if (SUCCEEDED(rc)) cout << "Target applicative container created OK" << endl << flush;
	else
	{
		cout << "ERROR in creating target applicative container" << endl << flush;
        pSourceContainer -> Release();
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

	if (SUCCEEDED(rc))
		cout << "CAAOsmNovel SU retrieved OK" << endl << flush;
    else
	{
		cout <<"ERROR in retrieveing CAAOsmNovel SU" << endl << flush;
	    piSourceContainer -> Release();
		return 3;
	}
//---------------------------------------------------
// Instantiate CAAOsmNovel StartUp to create a new feature
//---------------------------------------------------

	CATUnicodeString novel1("CAAOsmNovel1");

	CATISpecObject_var spNovelInst1 = NULL_var;
	rc = novelSUHandler.Instanciate(spNovelInst1, piSourceContainer, novel1);
    if (SUCCEEDED(rc))
		cout << "CAAOsmNovel SU instance 1 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 1 of CAAOsmNovel SU" << endl << flush;
	    piSourceContainer -> Release();
		return 3;
	}

/*--------------------------------------------------------*/
/* Get a CATOsmSUHandler on the StartUp "CAAOsmChapter".    */
/*--------------------------------------------------------*/

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
	    piSourceContainer -> Release();
		return 3;
	}

//----------------------------------------------------------------
// Instantiate CAAOsmChapter StartUp to create three new features
//----------------------------------------------------------------

	CATUnicodeString chapter1("CAAOsmChapter1");
	CATISpecObject_var spChapterInst1 = NULL_var;
	rc = chapterSUHandler.Instanciate(spChapterInst1, piSourceContainer, chapter1);
    if (SUCCEEDED(rc))
		cout << "CAAOsmChapter SU instance 1 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 1 of CAAOsmChapter SU" << endl << flush;
	    piSourceContainer -> Release();
		return 3;
	}

	CATUnicodeString chapter2("CAAOsmChapter2");

	CATISpecObject_var spChapterInst2 = NULL_var;
	rc = chapterSUHandler.Instanciate(spChapterInst2, piSourceContainer, chapter2);
    if (SUCCEEDED(rc))
		cout << "CAAOsmChapter SU instance 2 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 2 of CAAOsmChapter SU" << endl << flush;
	    piSourceContainer -> Release();
		return 3;
	}

	CATUnicodeString chapter3("CAAOsmChapter3");

	CATISpecObject_var spChapterInst3 = NULL_var;
	rc = chapterSUHandler.Instanciate(spChapterInst3, piSourceContainer, chapter2);
    if (SUCCEEDED(rc))
		cout << "CAAOsmChapter SU instance 3 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 3 of CAAOsmChapter SU" << endl << flush;
	    piSourceContainer -> Release();
		return 3;
	}

//---------------------------------------------------------------------------------------------
// Case 1:  The first case means to illustrate how to Cut and Paste in a batch environment:
// In this case, no extract into a buffer is necessary.  Pasting is done directly on the list
// passed as input.  Likewise, the cut operation is performed directly on the list passed as
// input.
//---------------------------------------------------------------------------------------------

	cout << "Case 1:" << endl << flush;

//--------------------------------------------------------------------------------------------
// Paste:  create new spec objects in the target container from those in the source container
//--------------------------------------------------------------------------------------------

// Get a CATICutAndPastable handle on the target container
    CATICutAndPastable *piCutAndPastableOnTargetCont = NULL;
    rc = pTargetContainer -> QueryInterface(IID_CATICutAndPastable,
		                                    (void**) &piCutAndPastableOnTargetCont);
    pTargetContainer -> Release();
    pTargetContainer = NULL;
    if (FAILED(rc)) 
	{
		cout << "ERROR in QueryInterface on CATICutAndPastable on Target Container" << endl << flush;
        pSourceContainer -> Release();
        return 3;
	}

// Create the list of objects to be pasted
    ListOfVarBaseUnknown listToPaste;
	listToPaste.Append(spChapterInst1);
	listToPaste.Append(spChapterInst2);

// Paste the requested objects in the target container.  
    ListOfVarBaseUnknown listPastedObjects = piCutAndPastableOnTargetCont -> Paste (listToPaste,
		                                                                            NULL,
																					NULL);
	if (listPastedObjects.Size() != 2)
	{
		cout << "ERROR in Paste of objects" << endl << flush;
		pSourceContainer -> Release();
		return 8;
	}
	else cout << "Objects Pasted in Target Container from Source Container OK" << endl << flush;

//--------------------------------------------------------------------------------------------
// Cut:  delete the spec objects from the source container that have been copied to the target
//       container
//--------------------------------------------------------------------------------------------

// Get a CATICutAndPastable handle on the source container
    CATICutAndPastable *piCutAndPastableOnSourceCont = NULL;
    rc = pSourceContainer -> QueryInterface(IID_CATICutAndPastable,
                                            (void**) &piCutAndPastableOnSourceCont);
    pSourceContainer -> Release();
    pSourceContainer = NULL;
    if (FAILED(rc)) 
	{
		cout << "ERROR in QueryInterface on CATICutAndPastable on Source Container" << endl << flush;
		piCutAndPastableOnTargetCont -> Release();
	    return 3;
	}

// Create the list of objects to be removed
    ListOfVarBaseUnknown listToRemove;
	listToRemove.Append(spChapterInst1);

// Remove the requested objects from the source container
    if (piCutAndPastableOnSourceCont -> Remove (listToRemove, NULL))
        cout << "Remove of objects from Source Container succeeded" << endl << flush;
    else 
    {
        cout << "Remove failed" << endl << flush;
        piCutAndPastableOnSourceCont -> Release();
        piCutAndPastableOnTargetCont -> Release();
        return 9;
    }  
	
//---------------------------------------------------------------------------------------------
// Case 2:  The second case means to illustrate how to Copy and Paste in an interactive
// environment: In this case, it is first necessary to extract the objects to be copied in  
// order to store them in a buffer.  Then, these same objects must be extracted from the buffer
// before they can be pasted elsewhere.  This follows the interactive operations necessary to
// Copy and Paste:  A Copy operation takes the selected objects and stores them in the clipboard.
// The Paste operation (or Cut operation) takes the objects from the clipboard and pastes them
// at the location indicated.
//---------------------------------------------------------------------------------------------

	cout << "Case 2:" << endl << flush;

//-----------------------------------------------------------------------------------------
// Extract:  create a list of the spec objects to be copied from the source container to 
//           the target container
//-----------------------------------------------------------------------------------------

// Create a list of the objects to be extracted	
    ListOfVarBaseUnknown newListToCopy;
    ListOfVarBaseUnknown listFromCopy;
    listFromCopy.Append(spChapterInst3);

    int result = NULL;
    result = piCutAndPastableOnSourceCont -> BoundaryExtract (newListToCopy, 
                                                              &listFromCopy,
                                                              NULL);
	if (NULL != result)
	{
		cout << "BoundaryExtract from Source Container succeeded" << endl << flush;
		cout << "Number of objects extracted = " << newListToCopy.Size() << endl << flush;
	}
    else
    {
        cout << "BoundaryExtract failed" << endl << flush;
        piCutAndPastableOnSourceCont -> Release();
		piCutAndPastableOnTargetCont -> Release();
        return 10;
    }


// Extract the objects from the source container and store them in the clipboard
// container which is returned from the Extract method.
	VarBaseUnknown pExtractedList;
	pExtractedList = piCutAndPastableOnSourceCont -> Extract (newListToCopy,
	                                                          NULL);
	piCutAndPastableOnSourceCont -> Release();
	piCutAndPastableOnSourceCont = NULL;

//--------------------------------------------------------------------------------------------
// Paste:  create the spec objects in the target container from the list of objects extracted
//--------------------------------------------------------------------------------------------

// Get a CATICutAndPastable handle on the clipboard container returned on the Extract
    CATICutAndPastable *piCutAndPastableOnExtractedList = NULL;
    rc = pExtractedList -> QueryInterface(IID_CATICutAndPastable,
		                                  (void**) &piCutAndPastableOnExtractedList);
    if (FAILED(rc)) 
	{
		cout << "ERROR in QueryInterface on CATICutAndPastable on Target Container" << endl << flush;
        return 3;
	}

    ListOfVarBaseUnknown extractedListToCopy;

// Extract the objects from the clipboard container.  Note that the second argument
// must be NULL in order to extract all of the objects from the clipboard.
    result = NULL;
    result = piCutAndPastableOnExtractedList -> BoundaryExtract (extractedListToCopy, 
                                                                 NULL,
                                                                 NULL);
	if (NULL != result)
	{
		cout << "BoundaryExtract from Clipboard succeeded" << endl << flush;
		cout << "Number of objects extracted = " << extractedListToCopy.Size() << endl << flush;
	}
    else
    {
        cout << "BoundaryExtract failed" << endl << flush;
        piCutAndPastableOnTargetCont -> Release();
        return 10;
    }

	piCutAndPastableOnExtractedList -> Release();
	piCutAndPastableOnExtractedList = NULL;

// Paste the objects extracted from the clipboard container to the target container
    listPastedObjects = piCutAndPastableOnTargetCont -> Paste (extractedListToCopy,
		                                                       NULL,
															   NULL);
	if (listPastedObjects.Size() != 1)
	{
		cout << "ERROR in Paste of objects" << endl << flush;
		return 8;
	}
	else cout << "Objects Pasted from Clipboard to Target Container OK" << endl << flush;
	
    piCutAndPastableOnTargetCont -> Release();
	piCutAndPastableOnTargetCont = NULL;

//-------------------
// Save the document 
//-------------------

	// @CSC-Filter UNER
    rc = CATDocumentServices::SaveAs (*pDoc, argv[2]);
    if (FAILED(rc))
    {
        cout << "ERROR in saving document" << endl << flush;
        return 11;
    }
    else cout << "SaveAs document OK" << endl << flush;

//---------------------
// Unlock the document
//---------------------

	CATUnLockDocument(*pDoc);

//--------------------------------------
// Remove the document from the session
//--------------------------------------

    rc = CATDocumentServices::Remove (*pDoc);
	if (FAILED(rc)) 
	{
		cout << "ERROR in removing document" << endl << flush;
		return 12;
	}

//-----------------	
// Delete session
//----------------
	rc = ::Delete_Session(sessionName);
	if (FAILED(rc))
	{
		cout << "ERROR in deleting session" << endl << flush;
		return 13;
	}
		
	return 0;
}
