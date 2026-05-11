//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2002
//
// Sample code for : Geometric Modeler
// Mission         : Use of the topological operators:
//                   CREATE CHAMFERS 
//                  
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Illustrates     : 1- Preliminary declarations
//                   2- Create chamfers of different types
//                   3- Release  the configuration
//                   4- Write the model 
//
// How to run it   : CAAGMOperatorsChamfer          // to run whithout storing the NCGM file
//                   CAAGMOperatorsChamfer file.NCGM // to run and store the result in file.NCGM                       
//=============================================================================

#include <iostream.h>
#include "fstream.h"

// Mathematics
#include "CATSoftwareConfiguration.h"  // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory 
#include "CATCGMContainerMngt.h"       // Geometry factory management
#include "CATCGMJournalList.h"

// GMModelInterfaces
#include "CATBody.h"                   // body
#include "CATEdge.h"
#include "CATCell.h"

// GMOperatorsInterfaces
#include "CATICGMDynAdvancedChamfer.h"
#include "CATDynChamferRibbon.h"


int CAAAdvancedChamfer(CATGeoFactory *iFactory, CATTopData *iTopData, CATBody *iBody, CATLISTP(CATEdge) &iEdges, CATBoolean iCreateCornerCaps)
{
    int rc = 0;

    if (NULL==iFactory || NULL==iTopData || NULL==iBody)
    { 
        cout << "Null pointer in CAAAdvancedChamfer" << endl;
        return (1);
    } 
 
	// ----------------------------------------------------------------------------
	// 1 -  Create the chamfer
	// -----------------------------------------------------------------------------
	//
	// (a) - Create a ribbon from the specified list of edges, a distance, and an angle
	//
	CATListPtrCATFace listFaces;
	CATDynChamferRibbon* pRibbon =  new CATDynChamferRibbon(iEdges, listFaces, CATDynd1a1, 50, 45);

	if (NULL==pRibbon)
	{
		return (1);
	}

	//
	// (b) - Create the operator
	//
	CATICGMDynAdvancedChamfer *pChamferOp = CATCGMCreateDynAdvancedChamfer(iFactory, iTopData, iBody);
	if (NULL==pChamferOp)
	{
		cout << "Create chamfer oper error." << endl;
		return (1);
	}
	//
	// (c) - Append the ribbon
	pChamferOp->Append(pRibbon);

	//
	// (d) - Specify corner caps, if requested
	if (iCreateCornerCaps)
		pChamferOp->SetCornerCap();

	cout << "Run the operator ..." << endl;
	// (e) - Run the operator
	pChamferOp->Run(); 

	// (f) - Get the resulting body
	CATBody * pChamferBody = NULL;
	pChamferBody = pChamferOp->GetResult();

	if (NULL==pChamferBody)
	{
		return (1);
	}

	// (g) - Delete the operator
	pChamferOp->Release();
	pChamferOp = NULL;

	if (NULL != pRibbon) 
	{
		delete pRibbon;
		pRibbon = NULL;
	}

	return rc;
}

CATBody *GetInputs(CATGeoFactory *iFactory, CATLISTP(CATEdge) &oEdges)
{
    // -----------------------------------------------------------
    // 1 - Identify the body and the edges to be chamfered
    // -----------------------------------------------------------
	CATBody *pRetBody = NULL;
	if (NULL != iFactory)
	{
		pRetBody = (CATBody *) iFactory->FindObjectFromTag(529);
		CATEdge* pRetEdge = (CATEdge *) iFactory->FindObjectFromTag(632);
		oEdges.Append(pRetEdge);
		pRetEdge = (CATEdge *) iFactory->FindObjectFromTag(610);
		oEdges.Append(pRetEdge);
		pRetEdge = (CATEdge *) iFactory->FindObjectFromTag(638);
		oEdges.Append(pRetEdge);
		pRetEdge = (CATEdge *) iFactory->FindObjectFromTag(428);
		oEdges.Append(pRetEdge);
		pRetEdge = (CATEdge *) iFactory->FindObjectFromTag(420);
		oEdges.Append(pRetEdge);
		pRetEdge = (CATEdge *) iFactory->FindObjectFromTag(416);
		oEdges.Append(pRetEdge);
	}

	return pRetBody;
}

//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (0) or (1) 
         char** iArgv)   // Path to the *.NCGM document that will contain the result of the main.
{
    int rc=0;
	if(iArgc < 2) return (1);
    
	CATBody *piInputBody=NULL;
	char *pInputFileName = iArgv[1];
    char *pOutputFileName = NULL;
    int  toStore = 0;
	if(3 == iArgc)
	{
		toStore = 1; 
		pOutputFileName = iArgv[2];
	}

#ifdef _WINDOWS_SOURCE
    ifstream filetoread(pInputFileName, ios::binary ) ;
#else
    ifstream filetoread(pInputFileName) ;
#endif
    //
    // -----------------------------------------------------------
    // 1 - Preliminary declarations
    // -----------------------------------------------------------
    //
    // (a) Loads the container 
    //
    CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
    if (NULL==piGeomFactory) return (1);
    //
    // (b) Configuration management
    //
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
	//
    // (c) - Create the default journal
	//
    CATCGMJournalList* pJournal = new CATCGMJournalList(pConfig,NULL);
    CATTopData topdata(pConfig, pJournal);

    // -----------------------------------------------------------
    // Input Body and Edges to be Chamfered
    // -----------------------------------------------------------
	CATLISTP(CATEdge) listOfEdges;
	piInputBody = GetInputs(piGeomFactory, listOfEdges);
	if (NULL == piInputBody)
	{
        cout << "No object with the specified tag" <<endl;
		return 1;
	}

	// -------------------------------------------------------------------------
    // 2 - Create chamfers of different types
    // -------------------------------------------------------------------------
    //
    // (a) - Create a chamfer without corner caps
    //
	CATBoolean createCornerCaps = FALSE;
	rc = CAAAdvancedChamfer(piGeomFactory, &topdata, piInputBody, listOfEdges, createCornerCaps);

    // (b) - Create a chamfer with corner caps
    //
	createCornerCaps = TRUE;
	rc = CAAAdvancedChamfer(piGeomFactory, &topdata, piInputBody, listOfEdges, createCornerCaps);

	piGeomFactory->Remove(piInputBody, CATICGMContainer::RemoveDependancies);

    // --------------------------------------------------------------------------
    // 3 - Release  the configuration
    // --------------------------------------------------------------------------
    pConfig->Release();
    
    //---------------------------------------------------------------------------
    // 4 - Write the model
    //---------------------------------------------------------------------------
    if(1==toStore)
    {
        cout << "Writing the model" << endl;
#ifdef _WINDOWS_SOURCE
        ofstream filetowrite(pOutputFileName, ios::binary ) ;
#else
        ofstream filetowrite(pOutputFileName,ios::out,filebuf::openprot) ;
#endif
        
        ::CATSaveCGMContainer(piGeomFactory,filetowrite);
        filetowrite.close();
    }	

	//
    // Close the container
    //
    ::CATCloseCGMContainer(piGeomFactory);
    return (rc);
}

