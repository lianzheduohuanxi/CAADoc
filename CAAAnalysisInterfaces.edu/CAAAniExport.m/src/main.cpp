// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the Use Case:
//  ------------------------
//
//  This Use Case illustrates how create or to load (open) an existing Analysis 
//  document which can be found in the file specified by the first input argument.
//  The second argument define the complete path for the exported file
//  You must enter the entire path and document name since there is no default 
//  associated to it.
//=============================================================================
//  Main Methods:
//  ------------
//   
//  Return Errors:
//  -------------
//  1 - ERROR in managing the session
//  2 - ERROR in managing the document
//  3 - ERROR in task of export
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAAniExport input.CATAnalysis Outputfile.txt" 
//        where the prefix "input and ouput " are entire pathnames where to find
//        and write the files.
//=============================================================================

//ObjectModelerBase Framework
#include "CATSessionServices.h"          // Create_Session and Delete_Session
#include "CATDocumentServices.h"         // New, Open, Save and Remove Document

// Relative to this sample
#include "CAAAniExport.h"               // To get the CATSamExport cpp
#include "CATSamTransitionSetup.h"      // To get the Analysis Transition Check
//
//Other includes
#include <iostream.h>                    // Print to the screen during execution

//=============================================================================
int main (int argc, char * argv[] )
{ 
	//------------------------------------------------------------------
	//Create Session:  A session must always be created in a batch
	//environment.  Deleting the session at the end of the program is
	//also necessary.
	//------------------------------------------------------------------

    char        *sessionName = "CAA2_Sample_Session";
	CATSession  *pSession    = NULL;
	CATDocument *pDoc        = NULL;

	HRESULT rc = Create_Session(sessionName, pSession);
	if ((rc != S_OK) || (!pSession))
	{
		cout << "ERROR in creating session" << endl << flush;
		return 1;
	}

	//-----------------------------------------------------------------------
    //Open an existing document:  the input parameter to this sample program 
    //must contain the entire path and name of the document that is to be    
    //opened.  
    //-----------------------------------------------------------------------
	rc = CATDocumentServices::OpenDocument(argv[1], pDoc);
	if (SUCCEEDED(rc) && pDoc) cout << "Document opened OK" << endl << flush;
	else
	{
		cout << "ERROR in opening an existing document" << endl << flush;
		return 2;
	}

    //---------------------------------------------------
    //Let's Work: 
    //---------------------------------------------------
	rc = CAAAniExport(pDoc,argv[2]); 
	if (! SUCCEEDED(rc))
	{
		cout << "Error: MainExport failure" << endl << flush;
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
		cout << "ERROR in removing document" << endl << flush;
		return 2;
	}
	
	//-------------------
    // Delete session
	//-------------------

	rc = Delete_Session(sessionName);
	if (SUCCEEDED(rc)) cout << "Session deleted OK" << endl << flush;
	else
	{
		cout << "ERROR in deleting session" << endl << flush;
		return 1;
	}
		
	return 0;
}
