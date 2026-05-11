/**
* @quickReview CRE 04:03:18
*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2002
//
// Sample code for : Geometric Modeler
// Mission         : Explain how to "dress" a single patch NURBS with a skin 
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Illustrates     : 1- Create the geometric factory
//   how to          2- Create the grid of points to be used as the poles
//                   3- Create the knot vector
//                   4- Create a rational NURBS surface
//                   5- Dress the NURBS with a skin
//                   6- Write the model and close the container  
//
// How to run it   : CAATopNurbsSurfSinglePatch  // to run whithout storing the NCGM file
//                   CAATopNurbsSurfSinglePatch file.NCGM // to run and store the result 
//                   in file.NCGM     
//==================================================================
#include <iostream.h>
#include <iomanip.h>
#include "fstream.h"

// Mathematics
#include "CATMathPoint.h"              // Mathematical point
#include "CATSoftwareConfiguration.h"  // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory
#include "CATCGMContainerMngt.h"       // Management of the geometry factory
#include "CATCartesianPoint.h"         // Geometric Cartesian point
#include "CATNurbsSurface.h"           // NURBS curve
#include "CATKnotVector.h"             // Knot vector

// TopologicalOperators
#include "CATTopSkin.h"                // Skin creation
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
    
    //-----------------------------------------------------------------------------
    // 1- Initializes the factory
    //-----------------------------------------------------------------------------
    
    CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer() ;
    if (NULL==piGeomFactory) return (1);	
    
    //-----------------------------------------------------------------------------
    // 2- Creation of the grid of points to be passed as the
    //    Knot vector argument
    //-----------------------------------------------------------------------------
    //
    int nbPoleU = 5;
    int nbPoleV = 5;
    CATMathGridOfPoints gridOfPoints(nbPoleU,nbPoleV);
    
    // Row 0
    gridOfPoints.SetPoint(CATMathPoint( 0., 0., 0.),0,0);
    gridOfPoints.SetPoint(CATMathPoint(10., 0., 0.),0,1);
    gridOfPoints.SetPoint(CATMathPoint(20., 0., 0.),0,2);
    gridOfPoints.SetPoint(CATMathPoint(30., 0., 0.),0,3);
    gridOfPoints.SetPoint(CATMathPoint(40., 0., 0.),0,4);
    
    // Row 1
    gridOfPoints.SetPoint(CATMathPoint( 0.,10., 0.),1,0);
    gridOfPoints.SetPoint(CATMathPoint(10.,10.,-10.),1,1);
    gridOfPoints.SetPoint(CATMathPoint(20.,10.,-10.),1,2);
    gridOfPoints.SetPoint(CATMathPoint(30.,10.,-10.),1,3);
    gridOfPoints.SetPoint(CATMathPoint(40.,10., 0.),1,4);
    
    // Row 2
    gridOfPoints.SetPoint(CATMathPoint( 0.,20., 0.),2,0);
    gridOfPoints.SetPoint(CATMathPoint(10.,20.,-40.),2,1);
    gridOfPoints.SetPoint(CATMathPoint(20.,20.,-40.),2,2);
    gridOfPoints.SetPoint(CATMathPoint(30.,20., -40.),2,3);
    gridOfPoints.SetPoint(CATMathPoint(40.,20., 0.),2,4);
    
    // Row 4
    gridOfPoints.SetPoint(CATMathPoint( 0.,30., 0.),3,0);
    gridOfPoints.SetPoint(CATMathPoint(10.,30., -10.),3,1);
    gridOfPoints.SetPoint(CATMathPoint(20.,30., -10.),3,2);
    gridOfPoints.SetPoint(CATMathPoint(30.,30., -10.),3,3);
    gridOfPoints.SetPoint(CATMathPoint(40.,30., 0.),3,4);
    
    // Row 5
    gridOfPoints.SetPoint(CATMathPoint( 0.,40., 0.),4,0);
    gridOfPoints.SetPoint(CATMathPoint(10.,40., 0.),4,1);
    gridOfPoints.SetPoint(CATMathPoint(20.,40., 0.),4,2);
    gridOfPoints.SetPoint(CATMathPoint(30.,40., 0.),4,3);
    gridOfPoints.SetPoint(CATMathPoint(40.,40., 0.),4,4);
    
    // Display the control points
    //
    int i = 0;
for (; i < nbPoleU; i++)
    {
        for (int j = 0; j < nbPoleV; j++)
        {
            CATMathPoint ptToBeDisplayed = gridOfPoints.GetPoint(i,j);
            CATCartesianPoint* piCartPt = piGeomFactory->CreateCartesianPoint(ptToBeDisplayed);
        }
    }
    //-----------------------------------------------------------------------------
    // 3 - Creation of the knot vectors
    //-----------------------------------------------------------------------------
    //
    
    CATLONG32 IsPeriodic= 0;
    CATLONG32 Degree= 4;
    CATLONG32 KnotsCount= 2;
    double Knots[]= {0.,10.};
    CATLONG32 Multiplicities[]= {5,5};
    CATLONG32 IndexOffset= 1;
    
    CATKnotVector NonUniformU(Degree,IsPeriodic,KnotsCount,Knots,
        Multiplicities,IndexOffset);
    CATKnotVector NonUniformV(Degree,IsPeriodic,KnotsCount,Knots,
        Multiplicities,IndexOffset);
    
    //-----------------------------------------------------------------------------
    // 4 - Creation of a rational NURBS surface
    //-----------------------------------------------------------------------------
    
    CATLONG32 isRational=1;
    double * aWeights=new double[nbPoleU*nbPoleV];
    for (i = 0; i < nbPoleU*nbPoleV; i++)
    {
        aWeights[i] = 1.;
    }
    
    // NURBS Surface creation
    //
    CATNurbsSurface * piSurf1 = piGeomFactory->
        CATCreateNurbsSurface(NonUniformU, NonUniformV,isRational,gridOfPoints,aWeights);
    if (NULL==piSurf1)
    {
        cout << "NURBS surface could not be created" << endl;
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    // Assign a weight value (80) to the (3,3) poles 
    //
    piSurf1->SetOneWeight(3,3,80);
    
    delete [] aWeights;
    aWeights = NULL;
    
    //-----------------------------------------------------------------------------
    // 5 - Creation of the skin
    //-----------------------------------------------------------------------------
    
    CATSurLimits surMaxLimits ;
    piSurf1->GetMaxLimits(surMaxLimits) ;
    
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig);
    
    CATTopSkin * pSkinOpe =::CATCreateTopSkin(piGeomFactory,
        &topdata,
        piSurf1,
        &surMaxLimits);
    
    if (NULL==pSkinOpe)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    pSkinOpe->Run();
    
    // Gets the resulting body
    CATBody * piSkinBody = pSkinOpe->GetResult();
    
    if (NULL==piSkinBody)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    // Deletes the operator
    delete pSkinOpe;
    pSkinOpe=NULL;
    
    //-----------------------------------------------------------------------------
    // 6- Write the model and close the container
    //-----------------------------------------------------------------------------
    //
	 pConfig->Release();
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
    
    ::CATCloseCGMContainer(piGeomFactory);
    
    return (rc);
}
