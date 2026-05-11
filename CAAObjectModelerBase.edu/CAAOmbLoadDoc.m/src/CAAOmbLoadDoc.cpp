// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of Use Case "CAAOmbLoadDoc":
//  ------------------------------------
//
//  This Use Case illustrates how to load (openb) an existing document which can
//  be found in the file specified by the input argument.  You must enter the 
//  entire path and document name since there is no default associated to it.
  
//=============================================================================
//  Main Methods:
//  ------------
//
//  Create_Session:  Creates a new session, necessary in a batch program
//  Open:  Loads an existing document whose path and name are passed in the
//         argument to the program
//  Save:  Saves the document (under the same name) 
//  Remove:  Removes the document from the session
//  Delete_Session:  Deletes the session
//
//  Return Errors:
//  -------------
//  1 - ERROR in creating the session
//  2 - ERROR in loading an existing document
//  3 - ERROR in saving the document
//  4 - ERROR in removing the document
//  5 - ERROR in deleting the session 
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAOmbLoadDoc input.CATPart" where the prefix "input" is the 
//  entire pathname of the directory in which the document is to be found and the
//  name of the of the document itself.
//=============================================================================

//ObjectModelerBase Framework
#include "CATSessionServices.h"          // Create_Session and Delete_Session
#include "CATDocumentServices.h"         // Open, SaveAs and Remove

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
		cout << "ERROR in creating session" << endl << flush;
		return 1;
	}

	//-----------------------------------------------------------------------
    //Open an existing document:  the input parameter to this sample program 
    //must contain the entire path and name of the document that is to be    
    //opened.  
    //-----------------------------------------------------------------------

	CATDocument *pDoc = NULL;
	rc = CATDocumentServices::OpenDocument(argv[1], 
		                           pDoc);
	if (SUCCEEDED(rc) && (NULL != pDoc)) cout << "Document opened OK" << endl << flush;
	else
	{
		return 2;
	}

    //--------------------------------------------------------------------------
    //Now that the document exists in the session, you can work with it by
	//adding new objects or by manipulating existing objects using specific API
	//external to the ObjectModelerBase framework.
    //--------------------------------------------------------------------------

    //---------------------------------------------------
    //Save the document under the same name - 
    //Caution: The Save method does not work in batch mode
    //---------------------------------------------------

    rc = CATDocumentServices::SaveAs (*pDoc,argv[1]);
	if (SUCCEEDED(rc)) cout << "Document saved OK" << endl << flush;
	else
	{
		return 3;
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
		return 4;
	}
	pDoc = NULL ;

	//-------------------
    // Delete session
	//-------------------

	rc = ::Delete_Session(sessionName);
	if (SUCCEEDED(rc)) cout << "Session deleted OK" << endl << flush;
	else
	{
		return 5;
	}
		
	return 0;
}
