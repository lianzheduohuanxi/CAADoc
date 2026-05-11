// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
// Abstract of Use Case "CAAOsmBuildUpdate":
// -------------------------------------------
//
// This sample program illustrates the Build/Update mechanism of the feature
// modeler.  It is accompanied by two implementations of the CATIBuild interface
// whose execution is triggered whenever an "Update" operation is requested. 
// In this way, the values of the attributes of the two features defined here, 
// "CAAOsmAdd" and "CAAOsmSquare" are updated according to the current values of 
// the attributes. Note that a dictionary entry for these implementations would be 
// necessary if the CATIBuild implementations were included in a separate shared library. 
//
// The "CAAOsmAdd" and "CAAOsmSquare" StartUps are created in the CAAOsmCatalogSU
// Use Case whose execution is, therefore, a pre-requisite to this Use Case. Here is the
// definition of the StartUps:
//
//
//		StartUp						Attribute
//		-------						---------
//      CAAOsmAdd                   First
//                                  Second
//                                  Sum
//
//      CAAOsmSquare                Num
//                                  Square
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
//  SetSpecAttribute:Valuates an attribute with the value of another attribute
//  Beginning:       Initialize list of chapters before looping
//  Next:            Get the next item in the list of chapters
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
//        mkrun -c "CAAOsmBuildUpdate CatalogName DocumentStorageName" 
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
#include "CATSessionServices.h"           // Create_Session and Delete_Session
#include "CATInit.h"                      // GetRootContainer
#include "CATDocument.h"                  // Document
#include "CATDocumentServices.h"          // New (creating a new document),
                                          //    SaveAs, Remove document
// ObjectSpecsModeler Framework
#include "CATISpecObject.h"               // Instanciate, Update
#include "CATISpecAttrAccess.h"           // GetAttrKey, SetSpecAttribute,
                                          //    SetInteger, GetInteger
#include "CATISpecAttrKey.h"              // Result of GetAttrKey
#include "CATOsmSUHandler.h"			  // RetrieveSU, Instanciate

#include "CATSession.h"
#include "CATBaseUnknown.h"				  // For CATIdent interface inclusion
#include "CATIContainer.h"

// Other
#include "iostream.h"

 
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

/*---------------------------------------*/
/* Open the catalog containing StartUps. */
/*---------------------------------------*/

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

/*--------------------------------------------------------*/
/* Get a CATOsmSUHandler on the StartUp "CAAOsmAdd".    */
/*--------------------------------------------------------*/

// Get the attribute keys for the CAAOsmAdd StartUp

	CATISpecAttrAccess *piSpecAttrAccessOnAdd = NULL;
	rc = spaddOpSU -> QueryInterface(IID_CATISpecAttrAccess, 
		                           (void**) &piSpecAttrAccessOnAdd);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for CAAOsmAdd SU" << endl << flush;
        return 3;
	}
 
	CATISpecAttrKey *piKeyFirst = piSpecAttrAccessOnAdd -> GetAttrKey("First");
	if (NULL == piKeyFirst)
	{
		cout << "ERROR in retrieving First key" << endl << flush;
		return 8;
	}

	CATISpecAttrKey *piKeySecond = piSpecAttrAccessOnAdd -> GetAttrKey("Second");
	if (NULL == piKeySecond)
	{
		cout << "ERROR in retrieving Second key" << endl << flush;
		return 8;
	}

	CATISpecAttrKey *piKeySum = piSpecAttrAccessOnAdd -> GetAttrKey("Sum");
	if (NULL == piKeySum)
	{
		cout << "ERROR in retrieving Sum key" << endl << flush;
		return 8;
	}
	
	piSpecAttrAccessOnAdd -> Release();

/*-------------------------------------------------------------------*/
/* Create an instance of the CAAOsmAdd StartUp in the root container */
/*-------------------------------------------------------------------*/

	CATUnicodeString Add1("CAAOsmAdd1");

	CATISpecObject_var spAddOpInst1 = NULL_var;
	rc = addOpSUHandler.Instanciate(spAddOpInst1, piRootContainer, Add1);
    if (NULL_var != spAddOpInst1 && SUCCEEDED(rc))
		cout << "CAAOsmAdd SU instance 1 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 1 of CAAOsmAdd SU" << endl << flush;
	    piRootContainer -> Release();
		return 3;
	}

/*-----------------------------------------*/
/* Valuate the attributes of this instance */
/*-----------------------------------------*/

	CATISpecAttrAccess *piSpecAttrAccessOnAdd1 = NULL;
	rc = spAddOpInst1 -> QueryInterface(IID_CATISpecAttrAccess,
		                            (void**) &piSpecAttrAccessOnAdd1);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for AddInst1" << endl << flush;
		return 3;
	}

    piSpecAttrAccessOnAdd1 -> SetInteger(piKeyFirst, 1);
    piSpecAttrAccessOnAdd1 -> SetInteger(piKeySecond, 2);
	piKeySecond -> Release();
   
/*--------------------------------------------------------*/
/* Get a CATOsmSUHandler on the StartUp "CAAOsmSquare".    */
/*--------------------------------------------------------*/

	CATUnicodeString squareSUType("CAAOsmSquare");

	CATOsmSUHandler squareSUHandler(squareSUType, clientId, CatalogName);

// Get a CATISpecObject handle on the CAAOsmSquare StartUp

	CATISpecObject_var spSquareSU = NULL_var;

	rc = squareSUHandler.RetrieveSU(spSquareSU);
	if (NULL_var != spSquareSU && SUCCEEDED(rc))
		cout << "CAAOsmSquare StartUp retrieved OK" << endl << flush;
    else
	{
		cout << "ERROR in retrieving CAAOsmSquare StartUp" << endl << flush;
		return 6;
	}

// Get the attribute keys for the CAAOsmSquare StartUp

	CATISpecAttrAccess *piSpecAttrAccessOnSq = NULL;
	rc = spSquareSU -> QueryInterface(IID_CATISpecAttrAccess, 
		                              (void**) &piSpecAttrAccessOnSq);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for CAAOsmSquare SU" << endl << flush;
		return 3;
	}
 
	CATISpecAttrKey *piKeyNum = piSpecAttrAccessOnSq -> GetAttrKey("Num");
	if (NULL == piKeyNum)
	{
		cout << "ERROR in retrieving Num key" << endl << flush;
		return 8;
	}

	CATISpecAttrKey *piKeySquare = piSpecAttrAccessOnSq -> GetAttrKey("Square");
	if (NULL == piKeySquare)
	{
		cout << "ERROR in retrieving Square key" << endl << flush;

		return 8;
	}
	  
	piSpecAttrAccessOnSq -> Release();

/*----------------------------------------------------------------------*/
/* Create an instance of the CAAOsmSquare StartUp in the root container */
/*----------------------------------------------------------------------*/

	CATUnicodeString square1("CAAOsmSquare1");

	CATISpecObject_var spSqInst1 = NULL_var;
	rc = squareSUHandler.Instanciate(spSqInst1, piRootContainer, square1);
    if (NULL_var != spSqInst1 && SUCCEEDED(rc))
		cout << "CAAOsmSquare SU instance 1 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 1 of CAAOsmSquare SU" << endl << flush;
	    piRootContainer -> Release();
		return 3;
	}

/*--------------------------------------------------------------------------*/
/* Assign to "Num" the value of "Sum" from the "CAAOsmAdd" feature instance */
/*--------------------------------------------------------------------------*/

	CATISpecAttrAccess *piSpecAttrAccessOnSq1 = NULL;
	rc = spSqInst1 -> QueryInterface(IID_CATISpecAttrAccess, 
		                             (void**) &piSpecAttrAccessOnSq1);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for CAAOsmSquare Instance 1" ;
        cout << endl ;
        return 1 ;
	}

	piSpecAttrAccessOnSq1->SetSpecAttribute(piKeyNum, spAddOpInst1, piKeySum);

	piKeySum -> Release();
	piKeyNum -> Release();
	
/*-----------------------------------------------*/
/* Update "CAAOsmSquare" and verify its validity */
/*-----------------------------------------------*/

	spSqInst1 -> Update();
	int sqVal = piSpecAttrAccessOnSq1 -> GetInteger(piKeySquare);
	cout << "First Update of CAAOsmSquare" << endl;
	cout << "9 expected: " << sqVal << endl << flush;
        if ( 9 != sqVal ) 
        {
           return 1 ;
        }

/*------------------------------*/
/* Modify the "First" attribute */
/*------------------------------*/

	piSpecAttrAccessOnAdd1 -> SetInteger(piKeyFirst, 2);
	piSpecAttrAccessOnAdd1 -> Release();
	piKeyFirst -> Release();

/*-------------------------------------------------*/
/* Reupdate "CAAOsmSquare" and verify its validity */
/*-------------------------------------------------*/

	spSqInst1 -> Update();
	sqVal = piSpecAttrAccessOnSq1 -> GetInteger(piKeySquare);
	cout << "CAAOsmSquare is updated after "
		 << "the First attribute has been modified "  << endl;
	cout << "16  expected: " << sqVal << endl << flush;
        if ( 16 != sqVal ) 
        {
           return 1 ;
        }

/*------------------*/
/* Release pointers */
/*------------------*/   

	piSpecAttrAccessOnSq1 -> Release(); piSpecAttrAccessOnSq1 = NULL ;
	
	piKeySquare -> Release(); piKeySquare = NULL ; 
	
/*----------------------------------------------------------*/
/* Save the document and the catalog and delete the session */
/*----------------------------------------------------------*/

// Save document

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

