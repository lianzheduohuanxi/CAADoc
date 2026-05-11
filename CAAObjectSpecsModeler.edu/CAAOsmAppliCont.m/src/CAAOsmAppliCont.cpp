// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
// Abstract of Use Case "CAAOsmAppliCont":
// -------------------------------------
//
// This sample illustrates how to create an applicative container in a new document,
// how to create features in this container, how to retrieve a specific applicative
// container and how to retrieve the objects created within it.
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
//  CATOsmSUHandler :              To get a handler for the particular StartUp from the Catalog
//  RetrieveSU:                    Retrieves StartUps from the catalog using the CATOsmSUHandler
//  Instantiate:                   Creates a new feature from an existing StartUp
//  SaveAs
//  Remove
//  Open
//  CATGetApplicativeContainer:    Retrieves an applicative container of a given type
//  ListMembers:                   Lists the objects found in a given container
//  Delete_Session:                Deletes the session
//
//=============================================================================
//  Return Errors:
//  -------------
//  1 - ERROR in Create_Session
//  2 - ERROR in New
//  3 - ERROR in CATCreateApplicativeContainer
//  4 - ERROR in QueryInterface
//  5 - ERROR in GetRootContainer
//  6 - ERROR in CATOsmSUHandler 
//  7 - ERROR in RetrieveSU
//  8 - ERROR in Instanciate
//  9 - ERROR in SaveAs
// 10 - ERROR in Remove
// 11 - ERROR in Open
// 12 - ERROR in CATGetApplicativeContainer
// 13 - ERROR in ListMembers
// 14 - ERROR in Delete_Session 
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAOsmAppliCont CatalogName DocumentStorageName" 
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
#include "CATDocumentServices.h"         // New (creating a new document)
                                         //    SaveAs, Remove document
#include "CATAppliContServices.h"        // CATCreateApplicativeContainer, 
                                         //    CATGetApplicativeContainer
#include "CATSession.h"
#include "CATBaseUnknown.h"
#include "CATIContainer.h"
#include  "sequence_CATBaseUnknown_ptr.h" 


//ObjectSpecsModeler Framework
#include "CATISpecObject.h"              // Instanciate
#include "CATIClientContainer.h"         // ListMembers
#include "CATOsmSUHandler.h"			 // RetrieveSU, Instanciate

//Note : If you want to instanciate a feature from a feature, then as of now you will have to use Instanciate() method of
//       CATISpecObject

#include "iostream.h"


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

//--------------------------------------------------------
// Create a new applicative container within the document 
//--------------------------------------------------------

	CATIdent idAppliCont = "CATFeatCont";
	CATUnicodeString appliContIdentifier("CAAOsmAppliCont");
	CATBaseUnknown *pApplicativeContainer = NULL;
	rc = ::CATCreateApplicativeContainer(&pApplicativeContainer,   // appli cont created
                                         pDoc,                     // document  
									     idAppliCont,              // type of appli cont
									     IID_CATIContainer,        // interface type of appli cont
									     "",                       // supertype of appli cont 
									     appliContIdentifier);     // name of appli cont
	if (SUCCEEDED(rc)) cout << "Applicative container created OK" << endl << flush;
	else
	{
		cout << "ERROR in creating applicative container" << endl << flush;
		return 3;
	}

    // Gets a CATIContainer handle on the applicative container
	CATIContainer *piApplicativeContainer = (CATIContainer*) pApplicativeContainer;

    /*
    // Declares the container to the Undo/redo mechanism
    // only in interactive code otherwise the method return E_FAIL 
    // because, there is no undo/redo management
    
    rc = ::CATOmbPerformAfterContainerCreation( piApplicativeContainer );
    if ( FAILED(rc) )
    {
       cout <<" Error in declaring the container to the Undo/redo mechanism" << endl;
       return 1 ;
    }
    */

/*--------------------------------------------------------*/
/* Get a CATOsmSUHandler on the StartUp ("CAAOsmAdd").    */
/*--------------------------------------------------------*/

	CATUnicodeString CatalogName = argv[1];
	CATUnicodeString clientId("CAAOsmClientId");
	CATUnicodeString addOpSUType("CAAOsmAdd");

	CATOsmSUHandler addOpSUHandler(addOpSUType, clientId, CatalogName);

// Get a CATISpecObject handle on the CAAOsmAdd StartUp

	CATISpecObject_var spaddOpSU = NULL_var;

	rc = addOpSUHandler.RetrieveSU(spaddOpSU);
	if (NULL_var != spaddOpSU && SUCCEEDED(rc))
		cout << "CAAOsmAdd StartUp retrieved OK" << endl << flush;
    else
	{
		cout << "ERROR in retrieving CAAOsmAdd StartUp" << endl << flush;
		return 6;
	}

//-------------------------------------------------
// Instantiate the StartUp to create a new feature
//-------------------------------------------------

	CATUnicodeString Add1("CAAOsmAdd1");

	CATISpecObject_var spAddOpInst1 = NULL_var;
	rc = addOpSUHandler.Instanciate(spAddOpInst1, piApplicativeContainer, Add1);
    if (NULL_var != spAddOpInst1 && SUCCEEDED(rc))
		cout << "CAAOsmAdd SU instance 1 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 1 of CAAOsmAdd SU" << endl << flush;
	    piApplicativeContainer -> Release();
		return 3;
	}

//-----------------------
// Save the new document
//-----------------------
	// @CSC-Filter UNER 
	rc = CATDocumentServices::SaveAs (*pDoc, argv[2]);
	if (FAILED(rc))
	{
		cout << "ERROR in saving document" << endl << flush;
		return 9;
	}
		
//--------------------------------------
// Remove the document from the session
//--------------------------------------
    rc = CATDocumentServices::Remove (*pDoc);
	if (FAILED(rc)) 
	{
		cout << "ERROR in removing document" << endl << flush;
		return 10;
	}

//-------------------
// Open the document
//-------------------
	rc = CATDocumentServices::OpenDocument(argv[2], 
		                           pDoc);
	if (SUCCEEDED(rc) && (NULL != pDoc)) cout << "Document opened OK" << endl << flush;
	else
	{
		cout << "ERROR in opening an existing document" << endl << flush;
		return 11;
	}

//------------------------------------
// Retrieve the applicative container
//------------------------------------
	rc = ::CATGetApplicativeContainer (&pApplicativeContainer,   // appli cont retrieved
		                               pDoc,                     // document
									   IID_CATIContainer,        // interface type of appli cont
	                                   appliContIdentifier);     // name of appli cont to retrieve
    if (SUCCEEDED(rc)) cout << "Applicative container retrieved OK" << endl << flush;
	else
	{
		cout << "ERROR in retrieving applicative container" << endl << flush;
		return 12;
	}

//--------------------------------------------------------------
// Get a list of the objects found in the applicative container
//--------------------------------------------------------------
    CATIClientContainer *piClientOnAppliCont = NULL;
	rc = pApplicativeContainer -> QueryInterface(IID_CATIClientContainer,
		                                         (void**) &piClientOnAppliCont);

	pApplicativeContainer -> Release();
	pApplicativeContainer = NULL;

	if (NULL == piClientOnAppliCont)
	{
		cout << "ERROR in retrieving catalog pointer" << endl << flush;
		return 4;
	}
	
	CATListPtrCATBaseUnknown *pMemberList = new CATListPtrCATBaseUnknown();
	rc = piClientOnAppliCont -> ListMembers(IID_CATISpecObject,   // filter on object type
		                                    clientId,             // filter on client id of object
					                        &pMemberList);        // list of objects retrieved
	piClientOnAppliCont -> Release();
	piClientOnAppliCont = NULL;

	if (SUCCEEDED(rc)) cout << "Member list retrieved OK" << endl << flush;
	else
	{
		cout << "ERROR in retrieving member list" << endl << flush;
		return 13;
	}

	cout << "Number of members in applicative container: " << pMemberList->Size() << endl << flush;
	
	delete pMemberList;
	pMemberList = NULL;

//--------------------------------------
// Remove the document from the session
//--------------------------------------
    rc = CATDocumentServices::Remove (*pDoc);
	if (FAILED(rc)) 
	{
		cout << "ERROR in removing document" << endl << flush;
		return 10;
	}

//----------------	
// Delete session
//----------------
	rc = ::Delete_Session(sessionName);
	if (FAILED(rc))
	{
			cout << "ERROR in deleting session" << endl << flush;
			return 14;
	}
		
	return 0;
}
