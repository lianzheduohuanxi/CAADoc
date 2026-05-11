/**
* @quickReview CRE 03:10:17
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2000
//
// Sample code for : Geometric Modeler
// Mission         : Use of the TopologicalOperators framework
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return Codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Illustrates     : 1- Creation of the geometric factory
//                   2- Direct creation of point bodies
//                   3- Direct creation of spline body
//                   4- Scan the domain and check the list of cells
//                   5- Use of a topological operator 
//                      to create a CATCreateTopCrvToNurbsCrvOperator
//                    - a - create
//                    - b - run 
//                    - c - tune the parameters
//                    - d - get the result
//                    - e - delete
//               
//                   6- Unused point bodies deletion
//                   7- Write the model and close the factory
//                   
//
// How to run it   : CAATopCrvToNurbs             // to run without storing the NCGM file
//                   CAATopCrvToNurbs   file.NCGM // to run and store the result in file.NCGM                       
//=============================================================================

#include <iostream.h>
#include <iomanip.h>
#include "fstream.h"

// Mathematics
#include "CATSoftwareConfiguration.h"    // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"               // Geometry factory
#include "CATCGMContainerMngt.h"         // Management of the geometry factory

// TopologicalObjects
#include "CATBody.h"                     // Body
#include "CATCell.h" 
#include "CATTopData.h"                  // TopData of an operator

// BasicTopologicalOpe
#include "CATTopPointOperator.h"         // To create point bodies
#include "CATTopSplineOperator.h"        // To create spline bodies
#include "CATTopCrvToNurbsCrvOperator.h" // To convert curves into Nurbs

//------------------------------------------------------------------------------
int main(int    iArgc,   // Number of arguments (0) or (1) 
         char** iArgv)   // Path to the *.NCGM document created by the program.
{
	int rc=0;
	if(2<iArgc) return (1);
	
	char *pFileName = 0;
	int  toStore = 0;
	if (2==iArgc) 
	{
		toStore = 1; 
		pFileName = iArgv[1];
	}
	
	//----------------------------------------------------------------------------
	// 1 - Initialize the factory 
	//----------------------------------------------------------------------------
	
    CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer() ;
	if (NULL==piGeomFactory) return (1);
	
	//----------------------------------------------------------------------------
	// 2 - Create points 
	//----------------------------------------------------------------------------
	const int nbpts = 4;
	CATBody ** aPoints = new CATBody * [nbpts];
	
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig);
	
	aPoints[0] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,-20.,0., 0.);
	aPoints[1] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,-20.,5., 0);
	aPoints[2] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,-10.,5., 0.);
	aPoints[3] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,-10.,0., 0.);
	
	//----------------------------------------------------------------------------
	// 3 - Create a spline body 
	//----------------------------------------------------------------------------
    
	CATBody * piSplineBody = ::CATCreateTopSpline(piGeomFactory,
		&topdata,
		nbpts,
		aPoints);
    if (NULL==piSplineBody)
	{
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
	}
	
	//-----------------------------------------------------------------------------
	// 4 - Scan the domain - check the list of cells
	//-----------------------------------------------------------------------------
	
	// (a) --- Retrieve the number of domains (1 is expected) 
	//
	CATLONG32 nbDomain = piSplineBody ->GetNbDomains();
	if (1!=nbDomain) 
	{
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
	}
	
	// (b) --- Retrieve the domain
	//
	CATDomain * piDomain1 = NULL;
	piDomain1 = piSplineBody->GetDomain(1);
	if (NULL==piDomain1)
	{
		::CATCloseCGMContainer(piGeomFactory);
		return (1);	
	}	
	
	// (c) --- Retrieve the number of edges
	//
	CATLISTP(CATCell) list1;
	piDomain1 ->GetAllCells(list1, 1 );
	
	// (d) --- Check the number of edges (1 is expected for the spline)
	//
	int nbCells1 = list1.Size();
	cout << "The edge number for the Spline is : " << nbCells1 << endl; 
	
	//-----------------------------------------------------------------------------
	// 5 - Create and use of the CATTopCrvToNurbsCrvOperator operator
	//-----------------------------------------------------------------------------
	
	// (a) --- Create the operator 
	//
	CATTopCrvToNurbsCrvOperator * pCrvToNurbsOp = ::CATCreateTopCrvToNurbsCrvOperator(piGeomFactory,
		&topdata,
		piSplineBody,
		list1[1]);
	if (NULL==pCrvToNurbsOp)
	{
		cout << "No operator created" << endl;
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
	}
	
	// (b) --- Tune the parameters
	// Warning: Depending on the parameter values, the result may or may 
	// not be valid. 
	//
	pCrvToNurbsOp->SetMaxDegree(2);
	pCrvToNurbsOp->SetMaxArcs(1);
	pCrvToNurbsOp->SetRationalAbility(0);
	pCrvToNurbsOp->Set3DOutputDimension(TRUE);
	
	// (c) --- Runs the operator
	//
	pCrvToNurbsOp->Run();
	
	// (d) --- Gets the result
	//         Check your parameters if the returned value is NULL
	CATBody * pBody1 = pCrvToNurbsOp->GetResult();
	if (NULL==pBody1)
	{
		cout << "No valid result - NULL" << endl;
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
	}
					
	//-----------------------------------------------------------------------------
	// 6 - Deletes the operator
	//-----------------------------------------------------------------------------
	
	delete pCrvToNurbsOp;
	pCrvToNurbsOp=NULL;
	
	//-----------------------------------------------------------------------------
	// 7 - Release the configuration
	//-----------------------------------------------------------------------------
	
	pConfig->Release();
	
	//----------------------------------------------------------------------------
	// 8 - Delete the unused point bodies and the array
	//----------------------------------------------------------------------------
	
	for (int i=0;i <nbpts; i++)
	{
		piGeomFactory->Remove(aPoints[i],CATICGMContainer::RemoveDependancies);
	}
	
	delete [] aPoints;
	aPoints = NULL;
	
	//----------------------------------------------------------------------------
	// 9 - Write the model and close the container
	//----------------------------------------------------------------------------

	if(1==toStore)
	{
		cout << "Writing the model" << endl;
#ifdef _WINDOWS_SOURCE
		ofstream filetowrite(pFileName, ios::binary ) ;
#else
		ofstream filetowrite(pFileName,ios::out,filebuf::openprot) ;
#endif
		
		::CATSaveCGMContainer(piGeomFactory,filetowrite);
		filetowrite.close();
	}	
   	
	::CATCloseCGMContainer(piGeomFactory);
	return (rc);
}


//automate:11/09/01:suppression include de CATTopLineOperator.h
//automate:11/09/01:suppression include de CATMathVector.h
//automate:11/09/01:suppression include de CATMathPoint.h
//automate:11/09/01:suppression include de CATEdge.h
//automate:11/09/01:suppression include de CATCurve.h
//automate:11/09/01:suppression include de CATCrvParam.h
//automate:11/09/01:suppression include de CATCrvLimits.h
