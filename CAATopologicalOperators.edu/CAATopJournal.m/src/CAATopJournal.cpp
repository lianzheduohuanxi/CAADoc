//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2000
//
// Sample code for : Geometric Modeler
// Mission         : Use of the topological operators: the journal
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//                   2- CAATopStiffener problem 
//
// Illustrates     : 1- Creates the geometric factory
//                   2- Creates the limiting bodies
//                   3- Creates the skin body to extrude
//                   4- Runs the new topological operator
//                   5- Closes the factory. 
//
// How to run it   : CAATopJournal           // to run whithout storing the NCGM file
//                   CAATopJournal file.NCGM // to run and store the result in file.NCGM                       
//=============================================================================

#include <iostream.h>
#include "fstream.h"
#include "CATErrorMacros.h"                  // error management

// Mathematics
#include "CATMathPoint.h"              // mathematical point
#include "CATMathVector.h"             // vector
#include "CATMathDirection.h"          // mathematical unitary vector
#include "CATMathPlane.h"              // mathematical plane
#include "CATSoftwareConfiguration.h"  // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory 
#include "CATCGMContainerMngt.h"       // Geometry factory management

#include "CATSurParam.h"               // Surface parameter
#include "CATSurLimits.h"              // Surface limits
#include "CATCrvLimits.h"              // Curve limits
#include "CATPlane.h"                  // Geometric plane
#include "CATPCurve.h"                 // Curve on a surface 
#include "CATPLine.h"                  // Line on a surface
#include "CATCylinder.h"               // Geometric cylinder


// TopologicalObjects
#include "CATBody.h"                   // body
#include "CATTopData.h"                // TopData of an operator

// TopologicalOperators
#include "CATTopSkin.h"                // Skin body creation
#include "CATTopPrism.h"               // Prism creation

// CAATopologicalOperators.edu
#include "CAATopStiffener.h"           // the CAA new operator class


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
    if (NULL == piGeomFactory)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }
    
	//---------------------------------------------------------------------------
	// 2- Creates the first limiting body
	//---------------------------------------------------------------------------
    CATMathDirection z(0.,0.,1.);
	CATMathAxis axis1(CATMathPoint(0.,0.,-120.),
                      CATMathVector(0.,1.,0.),
                      z,
                      CATMathVector(1.,0.,0.));
    double      radius = 140.;
    double      axisStart= -30.;
    double      axisEnd  = 30.;
    double      angleStart = CATPIBY2-0.3;
    double      angleEnd = CATPIBY2+0.3;
	CATCylinder * piCylinder1 = piGeomFactory->CreateCylinder
                     (axis1,radius,axisStart,axisEnd,angleStart,angleEnd);
	
    if (NULL == piCylinder1)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }

    // Creates a skin body
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig);  // an open configuration and a NULL journal

    CATSurLimits limits;
    piCylinder1->GetLimits(limits);
    CATTopSkin * pSkinOp = ::CATCreateTopSkin(piGeomFactory,&topdata,piCylinder1,&limits);
    if (NULL==pSkinOp)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }

    // Runs
	pSkinOp->Run();

    // Gets the resulting body
	CATBody * piFirstCylinderBody = pSkinOp->GetResult();
    if (NULL==piFirstCylinderBody)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }
    
    // Deletes the operator
	delete pSkinOp;
	pSkinOp = NULL;

     // --------- Creates the prism from the skin

    CATTopPrism  *pPrismOp = ::CATCreateTopPrism (piGeomFactory, 
                                                  &topdata,
                                                  piFirstCylinderBody,
                                                  &z,
                                                  0.,               // limit1
                                                  2.);              // limit2
     
    if (NULL==pPrismOp)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }

    pPrismOp->Run();
    CATBody* piFirstLimitBody = pPrismOp->GetResult();
    if (NULL==piFirstLimitBody)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }
    delete pPrismOp;
    pPrismOp=NULL;
    //---------------------------------------------------------------------------
	// Creates the second limiting body
	//---------------------------------------------------------------------------
	CATMathAxis axis2(CATMathPoint(0.,0.,120.),
                      CATMathVector(0.,1.,0.),
                      z,
                      CATMathVector(1.,0.,0.));
  
    angleStart = CAT3PIBY2-0.3;
    angleEnd = CAT3PIBY2+0.3;
	CATCylinder * piCylinder2 = piGeomFactory->CreateCylinder
                     (axis2,radius,axisStart,axisEnd,angleStart,angleEnd);
	
    if (NULL == piCylinder2)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }

    // Creates a skin body
    piCylinder2->GetLimits(limits);
    pSkinOp = ::CATCreateTopSkin (piGeomFactory, &topdata,piCylinder2,&limits);
    if (NULL==pSkinOp)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }

    // Runs
	pSkinOp->Run();

    // Gets the resulting body
	CATBody * piSecondCylinderBody = pSkinOp->GetResult();
    if (NULL==piSecondCylinderBody)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }
    
    // Deletes the operator
	delete pSkinOp;
	pSkinOp = NULL;

  // --------- Creates the prism from the skin
    CATMathDirection invz(0.,0.,-1.);
    pPrismOp = ::CATCreateTopPrism (piGeomFactory,
                                    &topdata,
                                    piSecondCylinderBody,
                                    &invz,
                                    0.,               // limit1
                                    2.);               // limit2
    
    if (NULL==pPrismOp)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }

    pPrismOp->Run();
    CATBody* piSecondLimitBody = pPrismOp->GetResult();
    if (NULL==piSecondLimitBody)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }
    delete pPrismOp;
    pPrismOp=NULL;

	//---------------------------------------------------------------------------
	// 3- Creates the skin body to extrude
	//---------------------------------------------------------------------------

    // ---------- Creates the lines of the profile	
	CATPlane * piPlane = piGeomFactory->CreatePlane(CATMathOIJ);	// Geometrical plan
    if (NULL == piPlane)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }

	CATMathPoint mathOrigin;
	CATMathDirection mathU, mathV;

	// ----------- Retrieves the mathematical definition of the geometrical plane
	piPlane->GetAxis(mathOrigin,mathU,mathV);
	
	// ----------- Defines points on the plane
    // Notice that we do not make any assumption on the plane parameterization.
    // The use of GetParam is allowed here, because the 3D points belong to the plane
    // by construction
	CATSurParam p1, p2, p3, p4;

	piPlane->GetParam(mathOrigin - 20*mathU - 5*mathV , p1);
    piPlane->GetParam(mathOrigin + 20*mathU - 5*mathV , p2);
    piPlane->GetParam(mathOrigin + 20*mathU + 5*mathV , p3);
    piPlane->GetParam(mathOrigin - 20*mathU + 5*mathV , p4);
	
	// ----------- Defines the curves of the profile
	const int nbPCurves = 4;
    CATPCurve *  aPCurves[nbPCurves];
	CATCrvLimits aLimits[nbPCurves];
	short        aOrientations[nbPCurves];
	aPCurves[0]=  piGeomFactory->CreatePLine   (p1, p2, piPlane );
	aPCurves[0] ->GetLimits(aLimits[0]);

	aPCurves[1]=  piGeomFactory->CreatePLine (p2, p3, piPlane);
	aPCurves[1] ->GetLimits(aLimits[1]);

	aPCurves[2]=  piGeomFactory->CreatePLine (p3, p4, piPlane);
	aPCurves[2] ->GetLimits(aLimits[2]);

	aPCurves[3]=  piGeomFactory->CreatePLine   (p4, p1, piPlane );
	aPCurves[3] ->GetLimits(aLimits[3]);


    for (int i=0; i<nbPCurves; i++)
    {
      if (NULL==aPCurves[i])
      {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
      }
    }

	// Defines the orientations of the curves
    // This is needed by the CATTopSkin
    // Notice that in a more general case (use of circle for example), 
    // you must test the start and end as in CAATopOverview.
	
	aOrientations[0] = 1;
	aOrientations[1] = 1;
	aOrientations[2] = 1;
	aOrientations[3] = 1;

	// ---------- Builds the skin
    // Creates the operator
    pSkinOp = ::CATCreateTopSkin  (piGeomFactory, 
                                   &topdata,
                                   piPlane,
		                           nbPCurves, 
								   aPCurves,
                                   aLimits,
                                   aOrientations);
    if (NULL==pSkinOp)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }

    // Runs
	pSkinOp->Run();

    // Gets the resulting body
	CATBody * piSkinBody = pSkinOp->GetResult();
    if (NULL==piSkinBody)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }
    
    // Deletes the operator
	delete pSkinOp;
	pSkinOp = NULL;
	
	//---------------------------------------------------------------------------
	// 4- Creates a stiffener by using the new topological operator
	//---------------------------------------------------------------------------
 
    //The journal is NULL in topdata

    CAATopStiffener *pStiffOp = new CAATopStiffener (piGeomFactory,
                                                     &topdata,
		                                             piFirstLimitBody,
                                                     piSecondLimitBody,
                                                     piSkinBody,
                                                     z);
    if (NULL==pStiffOp)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }

	// Runs
    //
    rc= pStiffOp->Run();
    if (0!=rc)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (2);
    }


    // Gets the resulting body 
    //
    CATBody * piMainBody1=NULL;
	piMainBody1 = pStiffOp->GetResult();
    if (NULL==piMainBody1)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }

    // Deletes the operator
    //
	delete pStiffOp;
	pStiffOp = NULL;

    // Releases the configuration
    pConfig->Release();
 
 
	//---------------------------------------------------------------------------
	// 5- Writes the model
	//---------------------------------------------------------------------------
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
	return (rc);
}

