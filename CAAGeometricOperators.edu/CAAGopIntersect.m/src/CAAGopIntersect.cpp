/**
* @quickReview CRE 04:03:19
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2000
//
// Sample code for : Geometric Modeler
// Mission         : Use of the geometric operator of intersection between a curve and 
//                    a surface: CATIntersectionCrvSur
//
// Type            : Batch program
// Inputs          : None
// Outputs         : 1- following cout
//                   Basic case: Number of intersection points: 2
//                   X= -7.07107 Y= -7.07107 Z= 0
//                   X= 7.07107 Y= 7.07107 Z= 0
//                   Advanced mode: Number of intersection points: 1
//                   X= 7.07107 Y= 7.07107 Z= 0
//                   Advanced mode with another run: Number of intersection points: 0
//                   Advanced mode with another run: Number of intersection curves: 1
//                   2- NCGM file if asked for
//                   3- Return codes (if not null, the model is not saved)
//                       0- OK 
//                       1- Null pointer
// Illustrates     : 1- Creates the geometric factory
//                   2- Creates the line and cylinder to intersect
//                   3- Uses of the geometric operator in BASIC mode
//                    - a- creates it 
//                    - b- gets the results- uses an iterator
//                    - c- deletes 
//                   4-Uses the geometric operator in ADVANCED mode
//                    - a- creates
//                    - b - runs 
//                    - gets the result
//                    - modifies th inputs
//                    - runs again
//                    - deletes
//                   5- Closes the factory. 
//
// How to run it   : CAAGopIntersect           // to run whithout storing the NCGM file
//                   CAAGopIntersect file.NCGM // to run and store the result in file.NCGM                     
//=============================================================================
// output
#include <iostream.h>
#include <iomanip.h> 
#include "fstream.h"

// mathematics
#include "CATMathPoint.h"            // mathematical point
#include "CATMathVector.h"           // mathematical vector
#include "CATMathAxis.h"             // axis system

// geometric objects
#include "CATCartesianPoint.h"       // geometric cartesian point
#include "CATLine.h"                 // geometric line
#include "CATCylinder.h"             // geometric cylinder
#include "CATCrvParam.h"             // curve parameter
#include "CATCrvLimits.h"            // curve limits
#include "CATSoftwareConfiguration.h"  // software configuration

// geometric objects management
#include "CATGeoFactory.h"           // geometry factory
#include "CATCGMContainerMngt.h"     // geometry factory management

// geometric operators
#include "CATIntersectionCrvSur.h"   // curve - surface intersection operator 
#include "CATCreateIntersection.h"      // the global function to create the intersection operator
//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (0) or (1) 
         char** iArgv)   // Path to the *.NCGM document that will contain the result of the main.
{
	int rc=0;
	if(2<iArgc) return (1);

  char *pfileName = 0;
	int  toStore = 0;
	if (2==iArgc) 
	{
		toStore = 1; 
	  pfileName = iArgv[1];
	}
	//--------------------------------------------------------------------------
	// 1- Initializes the factory and create the software configuration
	//--------------------------------------------------------------------------
	
    CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer() ;
	if (NULL==piGeomFactory) return (1);
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
	//--------------------------------------------------------------------------
	// 2- Creates the geometry 
	//--------------------------------------------------------------------------

	// ------------ line passing thru (0,0,0), of direction (1.,1.,0)
	CATLine * piLine = piGeomFactory->CreateLine(CATMathO, CATMathVector(1.,1.,0.) );
	if (NULL==piLine) 
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }
	//
	// ------------ cylinder 
	double radius = 10.;
	double axisStart = -50.;
	double axisEnd = 50.;
	double angleStart = 0.;
	double angleEnd = CAT2PI;
	CATCylinder* piCylinder = piGeomFactory->CreateCylinder(CATMathOIJK,
                                                            radius,
                                                            axisStart,
                                                            axisEnd,
                                                            angleStart,
                                                            angleEnd);
	if (NULL==piCylinder) 
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }

	//--------------------------------------------------------------------------
	//  3- Uses the BASIC mode
    //--------------------------------------------------------------------------
	// ----------- Creates and runs

    CATIntersectionCrvSur* pIntOp = ::CATCreateIntersection(piGeomFactory,
        pConfig,
        piLine,
        piCylinder,
        BASIC);
	if (NULL==pIntOp) 
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }
	//
	// ----------- Gets the results
    //
	CATLONG32 nbPoints = pIntOp->GetNumberOfPoints();

	cout << "Basic case: Number of intersection points: "<< nbPoints << endl;
	if (0 != nbPoints) 
	{
	 pIntOp->BeginningPoint();										// iterator one the points
	 while(TRUE == (pIntOp->NextPoint()) )						    // loops on the resulting points
	 {
		 CATCartesianPoint* piPoint=pIntOp->GetCartesianPoint();    // creates the geometric point
		 double x,y,z;
		 if (NULL != piPoint)
		 {
			piPoint->GetCoord(x,y,z);
		  cout << " X= "<< x << " Y= "<< y << " Z= "<< z <<endl;
		  piGeomFactory->Remove(piPoint);                          // because you do not want to keep it
		 }
	  }
	}
	// ----------- Deletes
    delete pIntOp; 
	pIntOp=NULL;

    //--------------------------------------------------------------------------
	//  4- Uses the ADVANCED mode
    //--------------------------------------------------------------------------

	// ------------ Creates the operator
    pIntOp = ::CATCreateIntersection(piGeomFactory, 
         pConfig,
                                piLine,
                                piCylinder,
                                ADVANCED);
	if (NULL==pIntOp)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }
	// ------------ Sets limits on the line to be tken into account
	CATCrvParam  startParam, endParam;
	piLine->GetParam(CATMathO,startParam);
	piLine->GetParam(CATMathPoint(35.,35.,0.),endParam);
	CATCrvLimits crvLimits(startParam,endParam);

	pIntOp->SetLimits(crvLimits);

    // ------------- Runs
	pIntOp->Run();

	// ------------- Gets the results
	// the way to get the result is the same as in the basic mode
	// but now, there is only one curve solution, between the curve limits are more restrictive
	nbPoints = pIntOp->GetNumberOfPoints();
	cout << "Advanced mode: Number of intersection points: "<< nbPoints << endl;
	if (0 != nbPoints) 
	{
	  pIntOp->BeginningPoint();                                 // iterator one the points
	  while(TRUE== (pIntOp->NextPoint()) )                      // loop on the resulting points
		{
		  CATCartesianPoint* piPoint=pIntOp->GetCartesianPoint(); // create the geometric point
          if (NULL!=piPoint)
          {
		    double x,y,z;
		    piPoint->GetCoord(x,y,z);
		    cout << " X= "<< x << " Y= "<< y << " Z= "<< z <<endl;
          }
		}
	}

	//
	// ----------- Runs again the operator with other inputs
    // ----------- First defines new inputs
	//
	CATMathPoint  MP(0.,radius,0.);
	CATMathVector k(0.,0.,1.);
	CATLine * piNewLine = piGeomFactory->CreateLine(MP, k );
	if (NULL==piNewLine) 
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }
	pIntOp->SetCurve(piNewLine);
	piLine->GetParam(MP,startParam);
	piLine->GetParam(MP+k,endParam);
    crvLimits.SetLow(startParam);
	crvLimits.SetHigh(endParam);

	// ------------ Runs
	pIntOp->Run();

    // ------------ Gets the results
    nbPoints = pIntOp->GetNumberOfPoints();
    cout << "Advanced mode with another run: Number of intersection points: "<< nbPoints << endl;
	CATLONG32 nbCurves= pIntOp->GetNumberOfCurves();
	cout << "Advanced mode with another run: Number of intersection curves: "<< nbCurves << endl;

	// here as no GetPCurve is called, the resulting curve will not be created
	//

	// ------------- Deletes
    delete pIntOp;  
	pIntOp=NULL;

	if (pConfig)
	{
		pConfig->Release();
		pConfig = NULL;
	}

	//--------------------------------------------------------------------------
	// 5- Writes the model
	//--------------------------------------------------------------------------
	 
    if(1==toStore)
    {
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
	return (0);
}


