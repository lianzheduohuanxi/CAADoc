//// COPYRIGHT DASSAULT SYSTEMES 2002
//
////=============================================================================
//// Abstract of module "CAAPstINFCatalog":
//// --------------------------------------
////
//// This program creates a new feature catalog containing the StartUps to be used
//// in the CAAPstIntegrateNewFeatures use case. These StartUps describe the data
//// structures of the feature "CAAPstINFRoot" which will aggregate the other features,
//// the feature "CAAPstINFPoint", the feature "CAAPstINFLine" and the feature "CAAPstINFWire".
//// The "CAAPstINFPoint" feature contains attributes referencing its coordinate values; the 
//// "CAAPstINFLine" feature contains attributes referencing two "CAAPstINFPoint" features; the 
//// "CAAPstINFWire" feature contains an attribute pointing to a list of "CAAPstINFPoint"
//// features. 
//// 
////  Main Methods:
////  ------------
////  Create_Session:    Creates a new session, necessary in a batch program
////  CreateCatalog:     Creates a new catalog for storing StartUps
////  SetClientId:       Sets a client identification name for the catalog
////  CreateSUInCatalog: Creates a new StartUp in the catalog
////  AddAttribute:      Adds an attribute to a StartUp
////  SaveCatalog:       Saves the catalog document
////  Delete_Session:    Deletes the session
////
////=============================================================================
////  Return Errors:
////  -------------
////  1 - ERROR in creating the session
////  2 - ERROR in creating catalog
////  3 - ERROR in creating a StartUp
////  4 - ERROR in adding a new attribute
////  5 - ERROR in saving the catalog document
////  6 - ERROR in deleting the session 
////
////  Running the program:
////  -------------------
////  To run this program, you can use the command:
////        mkrun -c "CAAPstINFCatalog CatalogStorageName" 
////  where the "CatalogStorageName" is the name of the entire path where the catalog is
////  to be stored. The extension .CATfct is not mandatory: it is added on by default during
////  the save operation. Remember that when accessing the catalog, it must be found under
////  the run-time directory: current workspace + os_directory + resources + graphic +
////  CatalogName.  For example, under WindowsNT, the "CatalogStorageName" would be:
////        currentWS\intel_a\resources\graphic\CAAPstINFCatalog.CATfct
////  or under AIX:
////        currentWS/aix_a/resources/graphic/CAAPstINFCatalog.CATfct
////  In order for the catalog to be accessible from the run-time directory, it should be 
////  stored under the currentWS + currentFW + CNext + resources + graphic directory. Then,
////  when updating the run-time view (mkrtcv), the catalog will be automatically transferred to the
////  run-time directory.
////         
////=============================================================================
//
//// System Framework
//#include "CATUnicodeString.h"
//
////ObjectModelerBase Framework
//#include "CATSessionServices.h"          // Create_Session and Delete_Session
//
////ObjectSpecsModeler Framework
//#include "CATCatalogFactoryServices.h"   // CreateCatalog and SaveCatalog global functions
//#include "CATICatalog.h"                 // CreateSUInCatalog, SetClientId
//#include "CATISpecObject.h"              // AddAttribute
//#include "CATISpecAttribute.h"           // Result of AddAttribute
//
////Other includes
//#include <iostream.h>
//
//
int main (int argc, char * argv[] )
{
/*
// YRC: Deprecated from V5R23
//------------------------------------------------------------------
// Create Session:  CreateCatalog will create a session in case     
// it has not already been created.  You need to delete it at the   
// end regardless of who has created it.                            
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

//-----------------------------------------------
// Create the Catalog that will contain StartUps 
//-----------------------------------------------

	CATICatalog *piCatalog = NULL;
	CATUnicodeString storageName = argv[1];
	rc = ::CreateCatalog(&storageName, 
		                 &piCatalog);
	if (NULL == piCatalog) 
       {
		cout << "ERROR in creating Catalog" << endl << flush;
		return 2;
	   }
	else cout << "Catalog created OK" << endl << flush;	

// Add a client identification to the catalog.  This is a mandatory step. 
	CATUnicodeString clientId("CAAPstINFClientId");
	rc = piCatalog -> SetClientId(&clientId);
	if (NULL == rc) cout << "ClientID setOK" << endl << flush;
	else cout << "ERROR in setting ClientID" << endl << flush;

//----------------------------------------------------------------------------
// Create StartUps within the Catalog.  Do not forget to release the pointers
// when they are no longer needed. 
//----------------------------------------------------------------------------

// Create StartUp "CAAPstINFRoot"

	CATBaseUnknown *pRootSU = NULL;
	CATUnicodeString rootSUName("CAAPstINFRoot");
	CATUnicodeString rootSUType("CAAPstINFRoot");
	rc = piCatalog -> CreateSUInCatalog (&pRootSU,
		                                 &rootSUName,
						                 &rootSUType,
									     "CATISpecObject");
    if (NULL == pRootSU) 
    {
	    cout << "ERROR in creating CAAPstINFRoot StartUp" << endl << flush;
		piCatalog -> Release();
	    piCatalog = NULL;
		return 3;
	}
	else cout << "CAAPstINFRoot StartUp created OK" << endl << flush;

// Get a CATISpecObject handle on the CAAPstINFRoot StartUp

	CATISpecObject *piRootSU = (CATISpecObject*) pRootSU;
		
// Add "CAAPstINFRoot" attributes

	CATUnicodeString listComp("ListOfComponents");
	CATISpecAttribute *piListComp = piRootSU -> AddAttribute(listComp,
		                                                    tk_list(tk_component),
															sp_IN);
	pRootSU -> Release();
	pRootSU = NULL;

	if (NULL == piListComp)
	{
		cout << "ERROR in adding ListOfComponents attribute" << endl << flush;
		piCatalog -> Release();
		piCatalog = NULL;
		return 4;
	}
	else
	{
		cout << "ListOfComponents attribute added OK" << endl << flush;
		piListComp -> Release();
		piListComp = NULL;
	}
	
// Create StartUp "CAAPstINFPoint"

	CATBaseUnknown *pPointSU = NULL;
	CATUnicodeString pointSUName("CAAPstINFPoint");
	CATUnicodeString pointSUType("CAAPstINFPoint");
	rc = piCatalog -> CreateSUInCatalog (&pPointSU,
		                                 &pointSUName,
						                 &pointSUType,
									     "CATISpecObject");
    if (NULL == pPointSU) 
    {
	    cout << "ERROR in creating CAAPstINFPoint StartUp" << endl << flush;
		piCatalog -> Release();
		piCatalog = NULL;
		return 3;
	}
	else cout << "CAAPstINFPoint StartUp created OK" << endl << flush;

// Get a CATISpecObject handle on the CAAPstINFPoint StartUp

	CATISpecObject *piPointSU = (CATISpecObject*) pPointSU;
		
// Add "CAAPstINFPoint" attributes

	CATUnicodeString xCoord("X");
	CATISpecAttribute *piXCoord = piPointSU -> AddAttribute(xCoord,
		                                                    tk_double,
														    sp_IN);
	if (NULL == piXCoord)
	{
		cout << "ERROR in adding xCoord attribute" << endl << flush;
		piCatalog -> Release();
		piCatalog = NULL;
		pPointSU -> Release();
		pPointSU = NULL;
		return 4;
	}
	else
	{
		cout << "xCoord attribute added OK" << endl << flush;
		piXCoord -> Release();
		piXCoord = NULL;
	}

	CATUnicodeString yCoord("Y");
	CATISpecAttribute *piYCoord = piPointSU -> AddAttribute(yCoord,
		                                                    tk_double,
															sp_IN);
	if (NULL == piYCoord)
    {
		cout << "ERROR in adding yCoord attribute" << endl << flush;
	    piCatalog -> Release();
		piCatalog = NULL;
		pPointSU -> Release();
		pPointSU = NULL;
		return 4;
	}
	else
	{
		cout << "yCoord attribute added OK" << endl << flush;
		piYCoord -> Release();
		piYCoord = NULL;
	}
	
	CATUnicodeString zCoord("Z");
	CATISpecAttribute *piZCoord = piPointSU -> AddAttribute(zCoord,
		                                                    tk_double,
															sp_IN);
	if (NULL == piZCoord)
	{
		cout << "ERROR in adding zCoord attribute" << endl << flush;
		piCatalog -> Release();
		piCatalog = NULL;
		pPointSU -> Release();
		pPointSU = NULL;
		return 4;
	}
	else
	{
		cout << "zCoord attribute added OK" << endl << flush;
		piZCoord -> Release();
		piZCoord = NULL;
	}
	
	pPointSU -> Release();
	pPointSU = NULL;
	
// Create StartUp "CAAPstINFLine"

	CATBaseUnknown *pLineSU = NULL;
	CATUnicodeString lineSUName("CAAPstINFLine");
	CATUnicodeString lineSUType("CAAPstINFLine");
	rc = piCatalog -> CreateSUInCatalog (&pLineSU,
		                                 &lineSUName,
						                 &lineSUType,
									     "CATISpecObject");
    if (NULL == pLineSU) 
    {
	    cout << "ERROR in creating CAAPstINFLine StartUp" << endl << flush;
		piCatalog -> Release();
		piCatalog = NULL;
		return 3;
	}
	else cout << "CAAPstINFLine StartUp created OK" << endl << flush;

// Get a CATISpecObject handle on the CAAPstINFLine StartUp

	CATISpecObject *piLineSU = (CATISpecObject*) pLineSU;
		
	// Add "CAAPstINFLine" attributes

	CATUnicodeString point1("Point1");
	CATISpecAttribute *piPoint1 = piLineSU -> AddAttribute(point1,
		                                                   tk_specobject,
														   sp_IN);
	if (NULL == piPoint1)
	{
		cout << "ERROR in adding Point1 attribute" << endl << flush;
		piCatalog -> Release();
		piCatalog = NULL;
		pLineSU -> Release();
		pLineSU = NULL;
		return 4;
	}
	else
	{
		cout << "Point1 attribute added OK" << endl << flush;
		piPoint1 -> Release();
		piPoint1 = NULL;
	}

	CATUnicodeString point2("Point2");
	CATISpecAttribute *piPoint2 = piLineSU -> AddAttribute(point2,
		                                                   tk_specobject,
														   sp_IN);
	if (NULL == piPoint2)
	{
		cout << "ERROR in adding Point2 attribute" << endl << flush;
		piCatalog -> Release();
		piCatalog = NULL;
		pLineSU -> Release();
		pLineSU = NULL;
		return 4;
	}
	else
	{
		cout << "Point2 attribute added OK" << endl << flush;
		piPoint2 -> Release();
		piPoint2 = NULL;
	}

	pLineSU -> Release();
	pLineSU = NULL;

// Create StartUp "CAAPstINFWire"

	CATBaseUnknown *pWireSU = NULL;
	CATUnicodeString wireSUName("CAAPstINFWire");
	CATUnicodeString wireSUType("CAAPstINFWire");
	rc = piCatalog -> CreateSUInCatalog (&pWireSU,
		                                 &wireSUName,
						                 &wireSUType,
									     "CATISpecObject");
    if (NULL == pWireSU) 
    {
	    cout << "ERROR in creating CAAPstINFWire StartUp" << endl << flush;
		piCatalog -> Release();
		piCatalog = NULL;
		return 3;
	}
	else cout << "CAAPstINFWire StartUp created OK" << endl << flush;

// Get a CATISpecObject handle on the CAAPstINFWire StartUp

	CATISpecObject *piWireSU = (CATISpecObject*) pWireSU;
		
	// Add "CAAPstINFWire" attributes

	CATUnicodeString points ("Points"); 
	CATISpecAttribute *piWirePoints = piWireSU -> AddAttribute(points,
		                                                       tk_list,
															   tk_specobject,
													    	   sp_IN);
	if (NULL == piWirePoints)
	{
		cout << "ERROR in adding Points attribute" << endl << flush;
		piCatalog -> Release();
		piCatalog = NULL;
		pWireSU -> Release();
		pWireSU = NULL;
		return 4;
	}
	else
	{
		cout << "Points attribute added OK" << endl << flush;
		piWirePoints -> Release();
		piWirePoints = NULL;
	}

	pWireSU -> Release();
	pWireSU = NULL;
	
//------------------
// Save the catalog 
//------------------

	rc = ::SaveCatalog(&piCatalog,
		               &storageName);
	if (NULL != piCatalog)
	{
	    piCatalog -> Release();
	    piCatalog = NULL;
	}
    if (FAILED(rc))
	{
		cout << "ERROR in saving catalog document" << endl << flush;
		return 5;
	}	

//----------------
// Delete session
//----------------

	rc = ::Delete_Session(sessionName);
	if (FAILED(rc))
	{
		cout << "ERROR in deleting session" << endl << flush;
		return 6;
	}
*/
	return 0;
}
