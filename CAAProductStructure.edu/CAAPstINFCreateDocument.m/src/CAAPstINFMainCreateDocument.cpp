// COPYRIGHT DASSAULT SYSTEMES 2002

//=============================================================================
// Abstract of Use Case "CAAPstINFMainCreateDocument":
// --------------------------------------------------
//
// This program illustrates creating a Product document containing features in an
// applicative container. Using the provider mechanism, these features will be
// able to be integrated in the navigation, visualization and update processes of
// the Product document in order to be able to perform other basic operations such
// as editing, cut/copy/paste or delete.
//
//=============================================================================
//  Main Methods:
//  ------------
//  Create_Session:                Creates a new session, necessary in a batch program
//  New:                           Creates a new document in which to store the new
//                                    features
//  CATCreateApplicativeContainer: Creates an applicative container within the new
//                                    document
//  AccessCatalog:                 Loads an existing catalog containing StartUps 
//  RetrieveSU:                    Retrieves a StartUp from the catalog
//  Instanciate:                   Creates a new feature from an existing StartUp
//  SetX, SetY, SetZ:              Valuates the coordinates of a CAAPstINFPoint feature
//  SetPoint:                      Valuates the points defining a CAAPstINFLine feature
//  SetPoints:                     Valuates the points defining a CAAPstINFWire feature
//  AddChild:                      Aggregates a new feature to the CAAPstINFRoot feature
//  SaveAs:                        Saves the document
//  Remove:                        Removes the document from the session
//  Delete_Session:                Deletes the session
//
//=============================================================================
//  Return Errors:
//  -------------
//  1 - ERROR in Create_Session
//  2 - ERROR in New
//  3 - ERROR in CATCreateApplicativeContainer
//  4 - ERROR in AccessCatalog
//  5 - ERROR in RetrieveSU
//  6 - ERROR in Instanciate
//  7 - ERROR in QueryInterface
//  8 - ERROR in SetX, SetY, SetZ
//  9 - ERROR in SetPoint
// 10 - ERROR in SetPoints
// 11 - ERROR in AddChild
// 12 - ERROR in SaveAs
// 13 - ERROR in Remove
// 14 - ERROR in Delete_Session 
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAPstINFCreateDocument CatalogName DocumentStorageName" 
//  where the "CatalogName" is the name of the catalog and 
//  where the "DocumentStorageName" is the entire pathname, name and .CATProduct extension
//  under which the new document is to be stored.
//
//=============================================================================

//System Framework
#include "CATUnicodeString.h"

//ObjectModelerBase Framework
#include "CATSessionServices.h"          // Create_Session and Delete_Session
#include "CATDocument.h"
#include "CATDocumentServices.h"         // New (creating a new document), SaveAs, Remove
#include "CATAppliContServices.h"        // CATCreateApplicativeContainer
#include "CATInit.h"

//ObjectSpecsModeler Framework
#include "CATISpecObject.h"              // Instanciate
#include "CATListPtrCATISpecObject.h"    // List of CATISpecObject

// Local Framework
#include "CAAIPstINFPoint.h"             // SetX, SetY, SetZ             
#include "CAAIPstINFLine.h"              // SetPoint
#include "CAAIPstINFWire.h"              // SetPoints
#include "CAAIPstINFRoot.h"              // AddChild 

#include "CATOsmSUHandler.h"

// Others
#include "iostream.h"


int main (int argc, char * argv[])
{ 
//---------------------------------------------------------------
// Open a Session:  this is a necessary step in a batch program 
//---------------------------------------------------------------

	char *sessionName = "CAA_Sample_Session";
	CATSession *pSession = NULL;
	HRESULT rc = ::Create_Session(sessionName, pSession);
	if ((FAILED(rc)) || (NULL == pSession))
	{
		cout << "ERROR in creating session" << endl << flush;
		return 1;
	}
	
//-------------------------------------
// Create a new CATProduct document 
//-------------------------------------
	
// We will work with a "CATProduct" document. 

	CATDocument *pDoc = NULL;
	rc = CATDocumentServices::New("Product",
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

	CATIdent idAppliCont = "CAAPstINFCont";
	CATUnicodeString appliContIdentifier = "PstINFContainer";
	CATBaseUnknown *pINFAppliCont = NULL;
	rc = ::CATCreateApplicativeContainer(&pINFAppliCont,            // appli cont created
					     pDoc,                     // document  
					     idAppliCont,              // type of appli cont
					     IID_CATIContainer,        // interface type of appli cont
					     "CATFeatCont",            // supertype of appli cont 
					     appliContIdentifier);     // name of appli cont
	if (SUCCEEDED(rc))
	{
		cout << "Applicative container created OK" << endl << flush;
	}
	else
	{
		cout << "ERROR in creating applicative container" << endl << flush;
		return 3;
	}

	// Get a CATIContainer handle on the applicative container

	CATIContainer *piINFAppliCont = (CATIContainer*) pINFAppliCont;

#ifdef INTERACTIVE_APPLICATION
	// Initialize the applicative container
	// For a product structure, the call to CATInit is only mandatory
	// in interactive
	  CATInit * pInit = NULL ;
	  rc = piINFAppliCont->QueryInterface(IID_CATInit, (void**) &pInit);
	  if (FAILED(rc))
	  {
		  cout << "ERROR in querying CATInit interface" << endl;
		  return 3;
	  }
	  pInit->Init(FALSE);
	  pInit->Release();
	  pInit = NULL ;

	  // Declare the container to the Undo/redo mechanism
	  // only in interactive otherwise the method returns E_FAIL
	  // (as there is no undo/redo management in batch mode)
   
	  rc = ::CATOmbPerformAfterContainerCreation( piINFAppliCont );
	  if (FAILED(rc))
	  {
		  cout <<" Error in declaring the container to the Undo/redo mechanism" << endl;
		  return 3 ;
	  }
#endif

//------------------------------------
// Open a catalog containing StartUps
//------------------------------------

	CATUnicodeString CatalogName = argv[1];
	CATUnicodeString clientId("CAAPstINFClientId");
	CATUnicodeString rootSUType("CAAPstINFRoot");

	CATOsmSUHandler rootSUHandler(rootSUType, clientId, CatalogName);

// Get a CATISpecObject handle on the CAAPstINFRoot StartUp

	CATISpecObject_var spRootSU = NULL_var;

	rc = rootSUHandler.RetrieveSU(spRootSU);
	if (NULL_var != spRootSU && SUCCEEDED(rc))
		cout << "CAAPstINFRoot StartUp retrieved OK" << endl << flush;
    else
	{
		cout << "ERROR in retrieving CAAPstINFRoot StartUp" << endl << flush;
		return 6;
	}

//-----------------------------------------------------------------
// Instantiate two new Root features from the CAAPstINFRoot StartUp 
//-----------------------------------------------------------------
	CATUnicodeString Root1("CAAPstINFRoot1");

	CATISpecObject_var spRootInst1 = NULL_var;
	rc = rootSUHandler.Instanciate(spRootInst1, piINFAppliCont, Root1);
    if (NULL_var != spRootInst1 && SUCCEEDED(rc))
		cout << "CAAPstINFRoot SU instance 1 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 1 of CAAPstINFRoot SU" << endl << flush;
	    pINFAppliCont -> Release();
		return 3;
	}

	CATUnicodeString Root2("CAAPstINFRoot2");

	CATISpecObject_var spRootInst2 = NULL_var;
	rc = rootSUHandler.Instanciate(spRootInst2, piINFAppliCont, Root2);
    if (NULL_var != spRootInst2 && SUCCEEDED(rc))
		cout << "CAAPstINFRoot SU instance 2 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 2 of CAAPstINFRoot SU" << endl << flush;
	    pINFAppliCont -> Release();
		return 3;
	}
	
//---------------------------------------------
// Retrieve a Point StartUp from the catalog
//---------------------------------------------

	CATUnicodeString pointSUType("CAAPstINFPoint");

	CATOsmSUHandler pointSUHandler(pointSUType, clientId, CatalogName);

// Get a CATISpecObject handle on the CAAPstINFPoint StartUp

	CATISpecObject_var spPointSU = NULL_var;

	rc = pointSUHandler.RetrieveSU(spPointSU);
	if (NULL_var != spPointSU && SUCCEEDED(rc))
		cout << "CAAPstINFPoint StartUp retrieved OK" << endl << flush;
    else
	{
		cout << "ERROR in retrieving CAAPstINFPoint StartUp" << endl << flush;
		return 6;
	}

//-------------------------------------------------------------
// Instantiate five new Points from the CAAPstINFPoint StartUp 
//-------------------------------------------------------------

	CATUnicodeString Point1("CAAPstINFRoot1");

	CATISpecObject_var spPointInst1 = NULL_var;
	rc = pointSUHandler.Instanciate(spPointInst1, piINFAppliCont, Point1);
    if (NULL_var != spPointInst1 && SUCCEEDED(rc))
		cout << "CAAPstINFPoint SU instance 1 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 1 of CAAPstINFPoint SU" << endl << flush;
	    pINFAppliCont -> Release();
		return 3;
	}

	CATUnicodeString Point2("CAAPstINFRoot2");

	CATISpecObject_var spPointInst2 = NULL_var;
	rc = pointSUHandler.Instanciate(spPointInst2, piINFAppliCont, Point2);
    if (NULL_var != spPointInst2 && SUCCEEDED(rc))
		cout << "CAAPstINFPoint SU instance 2 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 2 of CAAPstINFPoint SU" << endl << flush;
	    pINFAppliCont -> Release();
		return 3;
	}

		CATUnicodeString Point3("CAAPstINFRoot3");

	CATISpecObject_var spPointInst3 = NULL_var;
	rc = pointSUHandler.Instanciate(spPointInst3, piINFAppliCont, Point3);
    if (NULL_var != spPointInst3 && SUCCEEDED(rc))
		cout << "CAAPstINFPoint SU instance 3 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 3 of CAAPstINFPoint SU" << endl << flush;
	    pINFAppliCont -> Release();
		return 3;
	}

		CATUnicodeString Point4("CAAPstINFRoot4");

	CATISpecObject_var spPointInst4 = NULL_var;
	rc = pointSUHandler.Instanciate(spPointInst4, piINFAppliCont, Point4);
    if (NULL_var != spPointInst4 && SUCCEEDED(rc))
		cout << "CAAPstINFPoint SU instance 4 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 4 of CAAPstINFPoint SU" << endl << flush;
	    pINFAppliCont -> Release();
		return 3;
	}

		CATUnicodeString Point5("CAAPstINFRoot5");

	CATISpecObject_var spPointInst5 = NULL_var;
	rc = pointSUHandler.Instanciate(spPointInst5, piINFAppliCont, Point5);
    if (NULL_var != spPointInst5 && SUCCEEDED(rc))
		cout << "CAAPstINFPoint SU instance 5 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 5 of CAAPstINFPoint SU" << endl << flush;
	    pINFAppliCont -> Release();
		return 3;
	}

//---------------------------------------------
// Valuate the coordinates of all of the points 
//---------------------------------------------

	CAAIPstINFPoint *piPstINFPoint = NULL;
	rc = spPointInst1 -> QueryInterface (IID_CAAIPstINFPoint,
					     (void**) &piPstINFPoint);
	if (FAILED(rc)) 
	{
		cout << "QueryInterface failed on CAAIPstINFPoint" << endl;
		return 7;
	}
	else cout << "QueryInterface OK on CAAIPstINFPoint" << endl;

	rc = piPstINFPoint -> SetX (0.0);
	if (FAILED(rc))
	{
		cout << "SetX failed." << endl;
		return 8;
	}
	else cout << "SetX succeeded." << endl;

	rc = piPstINFPoint -> SetY (0.0);
	if (FAILED(rc))
	{
		cout << "SetY failed." << endl;
		return 8;
	}
	else cout << "SetY succeeded." << endl;
	
	rc = piPstINFPoint -> SetZ (0.0);
	if (FAILED(rc))
	{
		cout << "SetZ failed." << endl;
		return 8;
	}
	else cout << "SetZ succeeded." << endl;

	piPstINFPoint -> Release();
	piPstINFPoint = NULL;

	rc = spPointInst2 -> QueryInterface (IID_CAAIPstINFPoint,
					     (void**) &piPstINFPoint);

	if (FAILED(rc))  
	{
		cout << "QueryInterface failed on CAAIPstINFPoint" << endl;
		return 7;
	}
	else
		cout << "QueryInterface OK on CAAIPstINFPoint" << endl;


	rc = piPstINFPoint -> SetX (10.0);
	if (FAILED(rc))
	{
		cout << "SetX failed." << endl;
		return 8;
	}
	else cout << "SetX succeeded." << endl;

	rc = piPstINFPoint -> SetY (20.0);
	if (FAILED(rc))
	{
		cout << "SetY failed." << endl;
		return 8;
	}
	else cout << "SetY succeeded." << endl;

	rc = piPstINFPoint -> SetZ (30.0);
	if (FAILED(rc))
	{
		cout << "SetZ failed." << endl;
		return 8;
	}
	else cout << "SetZ succeeded." << endl;

	piPstINFPoint -> Release();
	piPstINFPoint = NULL;
    
	rc = spPointInst3 -> QueryInterface (IID_CAAIPstINFPoint,
					     (void**) &piPstINFPoint);
	if (FAILED(rc)) 
	{
		cout << "QueryInterface failed on CAAIPstINFPoint" << endl;
		return 7;
	}
	else cout << "QueryInterface OK on CAAIPstINFPoint" << endl;

	rc = piPstINFPoint -> SetX (10.0);
	if (FAILED(rc))
	{
		cout << "SetX failed." << endl;
		return 8;
	}
	else cout << "SetX succeeded." << endl;

	rc = piPstINFPoint -> SetY (10.0);
	if (FAILED(rc))
	{
		cout << "SetY failed." << endl;
		return 8;
	}
	else cout << "SetY succeeded." << endl;
	
	rc = piPstINFPoint -> SetZ (-10.0);
	if (FAILED(rc))
	{
		cout << "SetZ failed." << endl;
		return 8;
	}
	else cout << "SetZ succeeded." << endl;

	piPstINFPoint -> Release();
	piPstINFPoint = NULL;

	rc = spPointInst4 -> QueryInterface (IID_CAAIPstINFPoint,
					     (void**) &piPstINFPoint);

	if (FAILED(rc))  
	{
		cout << "QueryInterface failed on CAAIPstINFPoint" << endl;
		return 7;
	}
	else
		cout << "QueryInterface OK on CAAIPstINFPoint" << endl;


	rc = piPstINFPoint -> SetX (120.0);
	if (FAILED(rc))
	{
		cout << "SetX failed." << endl;
		return 8;
	}
	else cout << "SetX succeeded." << endl;

	rc = piPstINFPoint -> SetY (20.0);
	if (FAILED(rc))
	{
		cout << "SetY failed." << endl;
		return 8;
	}
	else cout << "SetY succeeded." << endl;

	rc = piPstINFPoint -> SetZ (30.0);
	if (FAILED(rc))
	{
		cout << "SetZ failed." << endl;
		return 8;
	}
	else cout << "SetZ succeeded." << endl;

	piPstINFPoint -> Release();
	piPstINFPoint = NULL;

	rc = spPointInst5 -> QueryInterface (IID_CAAIPstINFPoint,
					     (void**) &piPstINFPoint);

	if (FAILED(rc))  
	{
		cout << "QueryInterface failed on CAAIPstINFPoint" << endl;
		return 7;
	}
	else
		cout << "QueryInterface OK on CAAIPstINFPoint" << endl;


	rc = piPstINFPoint -> SetX (20.0);
	if (FAILED(rc))
	{
		cout << "SetX failed." << endl;
		return 8;
	}
	else cout << "SetX succeeded." << endl;

	rc = piPstINFPoint -> SetY (-20.0);
	if (FAILED(rc))
	{
		cout << "SetY failed." << endl;
		return 8;
	}
	else cout << "SetY succeeded." << endl;

	rc = piPstINFPoint -> SetZ (-50.0);
	if (FAILED(rc))
	{
		cout << "SetZ failed." << endl;
		return 8;
	}
	else cout << "SetZ succeeded." << endl;

	piPstINFPoint -> Release();
	piPstINFPoint = NULL;

//---------------------------------------------
// Retrieve a Line StartUp from the catalog
//---------------------------------------------

	CATUnicodeString lineSUType("CAAPstINFLine");

	CATOsmSUHandler lineSUHandler(lineSUType, clientId, CatalogName);

// Get a CATISpecObject handle on the CAAPstINFLine StartUp

	CATISpecObject_var spLineSU = NULL_var;

	rc = lineSUHandler.RetrieveSU(spLineSU);
	if (NULL_var != spLineSU && SUCCEEDED(rc))
		cout << "CAAPstINFLine StartUp retrieved OK" << endl << flush;
    else
	{
		cout << "ERROR in retrieving CAAPstINFLine StartUp" << endl << flush;
		return 6;
	}

//-------------------------------------------------------
// Instantiate a new line from the CAAPstINFLine StartUp 
//-------------------------------------------------------

	CATUnicodeString Line1("CAAPstINFLine1");

	CATISpecObject_var spLineInst1 = NULL_var;
	rc = lineSUHandler.Instanciate(spLineInst1, piINFAppliCont, Line1);
    if (NULL_var != spLineInst1 && SUCCEEDED(rc))
		cout << "CAAPstINFLine SU instance 1 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 1 of CAAPstINFLine SU" << endl << flush;
	    pINFAppliCont -> Release();
		return 3;
	}
	
//---------------------------------------------------------------------------------
// Valuate the two point attributes defining the line with the two point instances
// created just before 
//---------------------------------------------------------------------------------

	CAAIPstINFLine *piPstINFLine = NULL;
	rc = spLineInst1 -> QueryInterface (IID_CAAIPstINFLine,
					    (void**) &piPstINFLine);
	if (SUCCEEDED(rc)) cout << "QueryInterface on CAAIPstINFLine succeeded." << endl;
	else
	{
		cout << "QueryInterface on CAAIPstINFLine failed." << endl;
		return 7;
	}

	rc = piPstINFLine -> SetPoint (1, spPointInst1);
	if (SUCCEEDED(rc)) cout << "First point set OK." << endl;
	else
	{
		cout << "SetPoint for first point failed." << endl;
		return 9;
	}

	rc = piPstINFLine -> SetPoint (2, spPointInst2);
	if (SUCCEEDED(rc)) cout << "Second point set OK." << endl;
	else
	{
		cout << "SetPoint for second point failed." << endl;
		return 9;
	}

	piPstINFLine -> Release();
	piPstINFLine = NULL;

//---------------------------------------------
// Retrieve a Wire StartUp from the catalog
//---------------------------------------------

	CATUnicodeString wireSUType("CAAPstINFWire");

	CATOsmSUHandler wireSUHandler(wireSUType, clientId, CatalogName);

// Get a CATISpecObject handle on the CAAPstINFWire StartUp

	CATISpecObject_var spWireSU = NULL_var;

	rc = wireSUHandler.RetrieveSU(spWireSU);
	if (NULL_var != spWireSU && SUCCEEDED(rc))
		cout << "CAAPstINFWire StartUp retrieved OK" << endl << flush;
    else
	{
		cout << "ERROR in retrieving CAAPstINFWire StartUp" << endl << flush;
		return 6;
	}

//-------------------------------------------------------
// Instantiate a new wire from the CAAPstINFWire StartUp 
//-------------------------------------------------------

	CATUnicodeString Wire1("CAAPstINFWire1");

	CATISpecObject_var spWireInst1 = NULL_var;
	rc = wireSUHandler.Instanciate(spWireInst1, piINFAppliCont, Wire1);
    if (NULL_var != spWireInst1 && SUCCEEDED(rc))
		cout << "CAAPstINFWire SU instance 1 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 1 of CAAPstINFWire SU" << endl << flush;
	    pINFAppliCont -> Release();
		return 3;
	}
	
//---------------------------------------------------------------------------------------
// Valuate the list of points attribute defining the wire with the last three point
// instances created above 
//---------------------------------------------------------------------------------------

	CAAIPstINFWire *piPstINFWire = NULL;
	rc = spWireInst1 -> QueryInterface (IID_CAAIPstINFWire,
					    (void**) &piPstINFWire);
	if (SUCCEEDED(rc)) cout << "QueryInterface on CAAIPstINFWire succeeded." << endl;
	else
	{
		cout << "QueryInterface on CAAIPstINFWire failed." << endl;
		return 7;
	}

	CATListPtrCATISpecObject pointList;
	pointList.Append (spPointInst3);
	pointList.Append (spPointInst4);
	pointList.Append (spPointInst5);
	cout << "Size of pointlist = " << pointList.Size() << endl;
	rc = piPstINFWire -> SetPoints (&pointList);
	
	if (SUCCEEDED(rc)) cout << "Wire valuated OK." << endl;
	else
	{
		cout << "Wire valuation failed." << endl;
		return 10;
	}

	piPstINFWire -> Release();
	piPstINFWire = NULL;

// Append the points, line and wire to the root feature node

	CAAIPstINFRoot *piPstINFRoot = NULL;
	rc = spRootInst1 -> QueryInterface (IID_CAAIPstINFRoot,
					    (void**) &piPstINFRoot);

	if (SUCCEEDED(rc)) cout << "QueryInterface on CAAIPstINFRoot succeeded." << endl;
	else
	{
		cout << "QueryInterface on CAAIPstINFRoot failed." << endl;
		return 7;
	}
   
	rc = piPstINFRoot -> AddChild(spPointInst1);
	if (SUCCEEDED(rc)) cout << "First point aggregated OK" << endl;
	else
	{
		cout << "AddChild for first point failed." << endl;
		return 11;
	}
   
	rc = piPstINFRoot -> AddChild(spPointInst2);
	if (SUCCEEDED(rc)) cout << "Second point aggregated OK" << endl;
	else
	{
		cout << "AddChild for second point failed." << endl;
		return 11;
	}
   
	rc = piPstINFRoot -> AddChild(spPointInst3);
	if (SUCCEEDED(rc)) cout << "Third point aggregated OK" << endl;
	else
	{
		cout << "AddChild for third point failed." << endl;
		return 11;
	}

	rc = piPstINFRoot -> AddChild(spPointInst4);
	if (SUCCEEDED(rc)) cout << "Fourth point aggregated OK" << endl;
	else
	{
		cout << "AddChild for fourth point failed." << endl;
		return 11;
	}

	rc = piPstINFRoot -> AddChild(spPointInst5);
	if (SUCCEEDED(rc)) cout << "Fifth point aggregated OK" << endl;
	else
	{
		cout << "AddChild for fifth point failed." << endl;
		return 11;
	}

	rc = piPstINFRoot -> AddChild(spLineInst1);
	if (SUCCEEDED(rc)) cout << "Line aggregated OK" << endl;
	else
	{
		cout << "AddChild for line failed." << endl;
		return 11;
	}

	rc = piPstINFRoot -> AddChild(spWireInst1);
	piPstINFRoot -> Release();
	piPstINFRoot = NULL;
	if (SUCCEEDED(rc)) cout << "Wire aggregated OK" << endl;
	else
	{
		cout << "AddChild for wire failed." << endl;
		return 11;
	}

//-----------------------
// Save the new document
//-----------------------
	rc = CATDocumentServices::SaveAs (*pDoc, argv[2]);
	if (FAILED(rc))
	{
		cout << "ERROR in saving document" << endl << flush;
		return 12;
	}
		
//--------------------------------------
// Remove the document from the session
//--------------------------------------
	rc = CATDocumentServices::Remove (*pDoc);
	if (FAILED(rc)) 
	{
		cout << "ERROR in removing document" << endl << flush;
		return 13;
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
