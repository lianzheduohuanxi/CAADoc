// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of Use Case "CAAOmbNewDoc":
//  -----------------------------------
//
//  This Use Case illustrates how to create a new document of a standard type.
//  
//=============================================================================
//  Main Methods:
//  ------------
//
//  Create_Session:  Creates a new session, necessary in a batch program
//  New:  Creates a new document of a standard type ("Part")
//  SaveAs:  Saves the document under a new name 
//  Remove:  Removes the document from the session
//  Delete_Session:  Deletes the session
//
//  Return Errors:
//  -------------
//  1 - ERROR in creating the session
//  2 - ERROR in creating a new document
//  3 - ERROR in Query Interface
//  4 - ERROR in retrieving the root container
//  5 - ERROR in saving the document
//  6 - ERROR in removing the document
//  7 - ERROR in deleting the session 
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAOmbNewDoc output.CATPart" where the prefix "output" is the 
//  entire pathname of the directory in which the document is to be stored and the
//  name of the of the document itself.
//=============================================================================

//ObjectModelerBase Framework
#include "CATSessionServices.h"          // Create_Session and Delete_Session
#include "CATDocumentServices.h"         // New, SaveAs and Remove
#include "CATInit.h"                     // GetRootContainer
#include "CATDocument.h"                 // QueryInterface - CATInit

//Other includes
#include <iostream.h>                    // Print to the screen during execution

int main (int argc, char * argv[] )
{ 

    //------------------------------------------------------------------
    //Create Session:  A session must always be created in a batch
    //environment.  Deleting the session at the end of the program is
    //also necessary.
    //------------------------------------------------------------------

	char *sessionName = "CAA2_Sample_Session";
	CATSession *pSession = NULL;
	HRESULT rc = ::Create_Session(sessionName,
		                          pSession);
	if ((FAILED(rc)) || (NULL == pSession))
	{
		return 1;
	}

    //-------------------------------------------------------------------------
    //Create a document of a standard type:  "Part" is the string that appears
    //under File/New during an interactive session.  "CATPart" is the actual
    //suffix of the document.
    //-------------------------------------------------------------------------

	CATDocument* pDoc = NULL;
	rc = CATDocumentServices::New("Part",
		                           pDoc);
	if (NULL != pDoc) cout << "New document created OK" << endl << flush;
	else
	{
		return 2;
	}

	//----------------------------------------------------------------------------
	//Retrieve the root container of the new document
	//----------------------------------------------------------------------------

	CATInit *piInitOnDoc = NULL;
	rc = pDoc -> QueryInterface (IID_CATInit,
		                         (void**) &piInitOnDoc);
	if (FAILED(rc))
	{
		return 3;
	}

	CATIContainer *piRootContainer = NULL;
	piRootContainer = (CATIContainer*)
		piInitOnDoc -> GetRootContainer("CATIPrtContainer");

    piInitOnDoc->Release();
    piInitOnDoc= NULL ;

	if (NULL == piRootContainer)
	{
		return 4;
	}

    //----------------------------------------------------------------------------
    //Now that the document is created, you can work within the document by adding
    //new objects using specific API external to the ObjectModelerBase framework. 
    //----------------------------------------------------------------------------

    piRootContainer->Release();
    piRootContainer = NULL ;

    //--------------------------------------------------------------------------
    //Save and remove the document and end the session.  The document is saved
	//under the name passed to the program as an argument: the entire path name
	//is necessary as there is no default directory under which to save the
	//document.
    //--------------------------------------------------------------------------

	rc = CATDocumentServices::SaveAs (*pDoc, 
		                              argv[1]);
	if (SUCCEEDED(rc)) cout << "Document saved OK" << endl << flush;
	else
	{
		return 5;
	}

	//----------------------------------------------------------------------
    //Remove the document from the session.  This step is a good habit to
	//acquire:  it prevents problems from occurring in the case where the
	//same document is re-loaded during the same session.
	//----------------------------------------------------------------------

	rc = CATDocumentServices::Remove (*pDoc);
	if (SUCCEEDED(rc)) cout << "Document removed OK" << endl << flush;
	else
	{
		return 6;
	}
	pDoc = NULL ;

	//----------------
    // Delete session
	//----------------

	rc = ::Delete_Session(sessionName);
	if (SUCCEEDED(rc)) cout << "Session deleted OK" << endl << flush;
	else
	{
		return 7;
	}
		
	return 0;
}
