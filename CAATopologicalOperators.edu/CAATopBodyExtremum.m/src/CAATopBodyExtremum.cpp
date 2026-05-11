/**
* @quickReview CRE 03:08:11
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2003
//
// Sample code for : Geometric Modeler
// Mission         : Use of the topological operators: 
//                   Retrieve the extremums of a body.
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Illustrates     : 1- Creates the geometric factory and software configuration
//                   2- Creates a body (solid cuboid)
//                   3- Creates the CATTopBodyExtremum operator - runs it and gets the result.
//                   4- Release the configuration, writes the model and closes the factory 
//
// How to run it   : CAATopBodyExtremum           // to run whithout storing the NCGM file
//                   CAATopBodyExtremum file.NCGM // to run and store the result in file.NCGM                       
//=============================================================================

#include <iostream.h>
#include <iomanip.h>
#include "fstream.h"


// Mathematics
#include "CATMathPoint.h"              // mathematical point
#include "CATMathDirection.h"          // mathematical unitary vector
#include "CATMathPlane.h"              // mathematical plane
#include "CATMathVector.h"  
#include "CATSoftwareConfiguration.h"  // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory 
#include "CATCGMContainerMngt.h"       // Geometry factory management
#include "CATICGMObject.h" 

#include "CATTopData.h"                // TopData of an operator

// TopologicalOperators
#include "CATTopBodyExtremum.h"        // Prism operator
#include "CATSolidCuboid.h"            // Box primitive

// BasicTopologicalOpe
#include "CATTopLineOperator.h"
#include "CATTopPointOperator.h"

#include "CATBody.h"
//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (0) or (1) 
         char** iArgv)   // Path to the *.NCGM document that will contain the result of the main.
{
    int rc=0;
    if(2<iArgc) return (1);
	
    char *pfileName = NULL;
    int  toStore = 0;
    if (2==iArgc) 
    {
		toStore = 1; 
		pfileName = iArgv[1];
    }
	
	//---------------------------------------------------------------------------
	// 1-Initializes the factory 
	//---------------------------------------------------------------------------
	
	CATGeoFactory* piGeomFactory = CATCreateCGMContainer() ;
    if (NULL == piGeomFactory) return (1);
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig);	
	
	//---------------------------------------------------------------------------
	// 2-Create a solid cuboid
	//---------------------------------------------------------------------------
	// 
    CATMathPoint vO( 0., 0., 28.),  vOI(0., 15., 28.), vOJ(-15., 0., 28.),  vOK(0., 0., 35.);

	CATPoint *Point1 = (CATPoint *) piGeomFactory->CreateCartesianPoint(vO);

    CATSolidCuboid *pCuboidOp = ::CATCreateSolidCuboid( piGeomFactory, 
		&topdata, 
		vO, 
		vOI, 
		vOJ, 
		vOK);
    if (NULL==pCuboidOp)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
    // Gets the result (the operator is run at is creation)
	CATBody *piCuboidBody=NULL;
	piCuboidBody = pCuboidOp->GetResult();
    if (NULL==piCuboidBody)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
    // Deletes the operator
	delete pCuboidOp;
	pCuboidOp = NULL;	
	
    //---------------------------------------------------------------------------
	// 3 - Create the CATTopBodyExtremum operator,
    //     runs the operator,
    //     and retrieves the result
	//---------------------------------------------------------------------------   

    CATMathVector VecteurDirectionExtremum(1,1,1);
    CATMathPoint pointOrigin(0,0,28);
    //CATLine * pLine = piGeomFactory->CreateLine(PointOrigine, VecteurDirectionExtremum);

    CATBody * pOriginBody =::CATCreateTopPointXYZ(piGeomFactory,
        &topdata, 0,0,28);
    CATBody * pLineBody =::CATCreateTopLineFromDirection(piGeomFactory,
        &topdata, pOriginBody,VecteurDirectionExtremum, 100.0);

    
    CATTopBodyExtremum * pOpeExtremum =:: CATCreateDirBodyExtremum(piGeomFactory,
        &topdata, 
        piCuboidBody, 
        CATMaximum, 
        VecteurDirectionExtremum,
        pointOrigin);
    if (NULL==pOpeExtremum)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
    pOpeExtremum->Run();

    CATBody * pBodyExtremum = pOpeExtremum->GetResult();
    if (NULL==pBodyExtremum)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
    double extremum = pOpeExtremum->GetExtremum();
    cout << "Distance extremum - direction" << extremum << endl;
	
    delete pOpeExtremum;
    pOpeExtremum=NULL;
    //
	//---------------------------------------------------------------------------
	// 3 - Writes the model
	//---------------------------------------------------------------------------
    //
   
    piGeomFactory->Remove(pOriginBody);
    // Releases the configuration
    pConfig->Release();

	// Stores the model
    if(1==toStore)
    {
		cout << "Writing the model" << endl;
#ifdef _WINDOWS_SOURCE
		ofstream filetowrite(pfileName, ios::binary ) ;
#else
		ofstream filetowrite(pfileName,ios::out,filebuf::openprot) ;
#endif
		
		::CATSaveCGMContainer(piGeomFactory,filetowrite);
		filetowrite.close();
    }	
	//
	// Closes the container
	//
    ::CATCloseCGMContainer(piGeomFactory);
	return (rc);
}

