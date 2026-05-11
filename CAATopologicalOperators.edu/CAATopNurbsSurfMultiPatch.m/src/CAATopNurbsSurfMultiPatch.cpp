/**
* @quickReview CRE 04:03:18
*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2002
//
// Sample code for : Geometric Modeler
// Mission         : Explain how to "dress" one patch of a multipatch NURBS with a skin 
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Illustrates     : 1- Create the geometric factory
//   how to          2- Create the knot vectors
//                   3- Create the control points and display them 
//                   4- Create the NURBS surface
//                   5- Dress one patch of the NURBS with a skin
//                   6- Write the model and close the container  
//
// How to run it   : CAATopNurbsSurfMultiPatch  // to run whithout storing the NCGM file
//                   CAATopNurbsSurfMultiPatch file.NCGM // to run and store the result 
//                   in file.NCGM     
//==================================================================
#include <iostream.h>
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
#include "CATBody.h"
#include "CATFace.h"
#include "CATSurface.h"
#include "CATCrvLimits.h"
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
    // 1- Initialize the factory
    //-----------------------------------------------------------------------------
    
    CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer() ;
    if (NULL==piGeomFactory) return (1);	
    
    //-----------------------------------------------------------------------------
    // 2 - Create the knot vectors
    //-----------------------------------------------------------------------------
    //
    CATLONG32 IsPeriodic= 0;
    CATLONG32 DegreeU= 3;
	CATLONG32 DegreeV= 3;
    CATLONG32 IndexOffset= 1;
    
    // a - Create the knot vector along U
    //
    CATLONG32 KnotsCount1= 5;                    // 5 knots -> 4 arcs/patches along U
    double Knots1[]= {0., 2., 3., 4., 5.};
    CATLONG32 Multiplicities1[]= {4, 1, 1, 1, 4};
    
    CATKnotVector NonUniformU(DegreeU,IsPeriodic,KnotsCount1,Knots1, Multiplicities1);
    
    // b - Create the knot vector along V
    //
    CATLONG32 KnotsCount2= 5;                    // 5 knots -> 4 arcs/patches along V
    double Knots2[]= {0.,10.,11.,12.,13.};
    
    CATLONG32 Multiplicities2[]= {4, 1, 1, 1, 4};
    
    CATKnotVector NonUniformV(DegreeV,IsPeriodic,KnotsCount2,Knots2, Multiplicities2 );
    
    //-----------------------------------------------------------------------------
    // 3 - Create the control points (poles)
    //     Reminder: Given a knot vector, the number of control points for a NURBS is 
    //     the sum of the multiplicities minus the last multiplicity
    //     OR: Number control points = sum of multiplicities - (degree + 1)
    //     Number of control points along U = nbPoleU = 7
    //     Number of control points along V = nbPoleV = 7
    //     Total number of control points = nbPoleU*nbPoleV = 49
    //-----------------------------------------------------------------------------
    //
    int nbPoleU = 7;
    int nbPoleV = 7;
    
    CATMathGridOfPoints gridOfPoints(nbPoleU,nbPoleV);
    
    // Row 0
    //
    gridOfPoints.SetPoint(CATMathPoint( 0., 0., 0.),0,0);
    gridOfPoints.SetPoint(CATMathPoint(10., 0., 0.),0,1);
    gridOfPoints.SetPoint(CATMathPoint(20., 0., 0.),0,2);
    gridOfPoints.SetPoint(CATMathPoint(30., 0., 0.),0,3);
    gridOfPoints.SetPoint(CATMathPoint(40., 0., 0.),0,4);
    gridOfPoints.SetPoint(CATMathPoint(50., 0., 0.),0,5);
	gridOfPoints.SetPoint(CATMathPoint(60., 0., 0.),0,6);
    
    // Row 1
    //
    gridOfPoints.SetPoint(CATMathPoint( 0.,10., 0.),1,0);
    gridOfPoints.SetPoint(CATMathPoint(10.,10., 10.),1,1);
    gridOfPoints.SetPoint(CATMathPoint(20.,10., 10.),1,2);
    gridOfPoints.SetPoint(CATMathPoint(30.,10., 10.),1,3);
    gridOfPoints.SetPoint(CATMathPoint(40.,10., 10.),1,4);
    gridOfPoints.SetPoint(CATMathPoint(50.,10., 0.),1,5);
	gridOfPoints.SetPoint(CATMathPoint(60.,10., 0.),1,6);
    
    // Row 2
    //
    gridOfPoints.SetPoint(CATMathPoint( 0.,20., 0.),2,0);
    gridOfPoints.SetPoint(CATMathPoint(10.,20., 10.),2,1);
    gridOfPoints.SetPoint(CATMathPoint(20.,20.,-80.),2,2);
    gridOfPoints.SetPoint(CATMathPoint(30.,20., 10.),2,3);
    gridOfPoints.SetPoint(CATMathPoint(40.,20., 10.),2,4);
    gridOfPoints.SetPoint(CATMathPoint(50.,20., 0.),2,5);
    gridOfPoints.SetPoint(CATMathPoint(60.,20., 0.),2,6);

    // Row 3
    //
    gridOfPoints.SetPoint(CATMathPoint( 0.,30., 0.),3,0);
    gridOfPoints.SetPoint(CATMathPoint(10.,30., 10.),3,1);
    gridOfPoints.SetPoint(CATMathPoint(20.,30., 10.),3,2);
    gridOfPoints.SetPoint(CATMathPoint(30.,30., 10.),3,3);
    gridOfPoints.SetPoint(CATMathPoint(40.,30., 10.),3,4);
    gridOfPoints.SetPoint(CATMathPoint(50.,30., 0.),3,5);
     gridOfPoints.SetPoint(CATMathPoint(60.,30., 0.),3,6);

    // Row 4
    //
    gridOfPoints.SetPoint(CATMathPoint( 0.,40., 0. ),4,0);
    gridOfPoints.SetPoint(CATMathPoint(10.,40., 10.),4,1);
    gridOfPoints.SetPoint(CATMathPoint(20.,40., -80.),4,2);
    gridOfPoints.SetPoint(CATMathPoint(30.,40., 10.),4,3);
    gridOfPoints.SetPoint(CATMathPoint(40.,40., 10.),4,4);
    gridOfPoints.SetPoint(CATMathPoint(50.,40., 0. ),4,5);
	gridOfPoints.SetPoint(CATMathPoint(60.,40., 0. ),4,6);
    
    // Row 5
    //
    gridOfPoints.SetPoint(CATMathPoint( 0.,50., 0.),5,0);
    gridOfPoints.SetPoint(CATMathPoint(10.,50., 10.),5,1);
    gridOfPoints.SetPoint(CATMathPoint(20.,50., 10.),5,2);
    gridOfPoints.SetPoint(CATMathPoint(30.,50., 10.),5,3);
    gridOfPoints.SetPoint(CATMathPoint(40.,50., 10.),5,4);
    gridOfPoints.SetPoint(CATMathPoint(50.,50., 0.),5,5);
	gridOfPoints.SetPoint(CATMathPoint(60.,50., 0.),5,6);
    
    // Row 6
    //
    gridOfPoints.SetPoint(CATMathPoint( 0.,60., 0.),6,0);
    gridOfPoints.SetPoint(CATMathPoint(10.,60., 0.),6,1);
    gridOfPoints.SetPoint(CATMathPoint(20.,60., 0.),6,2);
    gridOfPoints.SetPoint(CATMathPoint(30.,60., 0.),6,3);
    gridOfPoints.SetPoint(CATMathPoint(40.,60., 0.),6,4);
    gridOfPoints.SetPoint(CATMathPoint(50.,60., 0.),6,5);
	gridOfPoints.SetPoint(CATMathPoint(60.,60., 0.),6,6);

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
    // 4 - Create the NURBS surface
    //-----------------------------------------------------------------------------
    //   
    // a - Initialize the weights
    //
    CATLONG32 isRational=1;
    double * aWeights=new double[nbPoleU*nbPoleV];
    for (i = 0; i < nbPoleU*nbPoleV; i++)
    {
        aWeights[i] = 1.;
    }
    
    // For a non rational Nurbs surface
    /*
    CATLONG32 isRational=0;
    double * aWeights=NULL;
    */
    
    // b - Create the Nurbs surface
    //
    CATNurbsSurface * piSurf1 = piGeomFactory->
        CATCreateNurbsSurface(NonUniformU, NonUniformV,isRational,gridOfPoints,aWeights);
    if (NULL==piSurf1)
    {
        cout << "NURBS surface could not be created" << endl;
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }

    // c - Assign a weight value (150) to the (5, 5) and (3,5) poles 
    //
    piSurf1->SetOneWeight(1,1,150);
    piSurf1->SetOneWeight(2,2,150);
    
    delete [] aWeights;
    aWeights = NULL;
 
    //-----------------------------------------------------------------------------
    // 5 - Create a skin from one patch of the multi-patch NURBS
    //-----------------------------------------------------------------------------
	// Authorized values from 1,1 to 5,5
    CATSurLimits surMaxLimits ;
    piSurf1->GetInternalMaxLimits(4,4,surMaxLimits) ;
    
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
    
    // Get the resulting body
    CATBody * piSkinBody = pSkinOpe->GetResult();
    
    if (NULL==piSkinBody)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    // Delete the operator
    delete pSkinOpe;
    pSkinOpe=NULL;

    // ----------------------------------------------------------------------------
    // 6- Retrieve the NurbsCurve corresponding to the face borders
    //    The code below applies when the borders are PLines - otherwise you must 
    //    use the CATCrvFittingToNurbsCrv operator.
    // ----------------------------------------------------------------------------
    
    CATLISTP(CATCell)  faceList;      
    piSkinBody->GetAllCells( faceList,2);
    cout << "number of faces " <<  faceList.Size() << endl;
    CATFace * myFace = (CATFace *) faceList[1];
	if (myFace != NULL)
	{
       CATSurface * mySurface = myFace->GetSurface();
    
       CATIsoParameter IsoPar;
       CATSurParam SurfPar[4];
       CATSurLimits SurfLim, *FaceLim; 
       FaceLim = (CATSurLimits *)myFace->Get2DBoundingBox();
       FaceLim->GetLow(SurfPar[0]);
       FaceLim->GetHigh(SurfPar[2]);
       SurfPar[1] = SurfPar[0];
       SurfPar[1].SetParamU( SurfPar[2].GetParamU() );
       SurfPar[3] = SurfPar[2];      
       SurfPar[3].SetParamU( SurfPar[0].GetParamU() );

       CATLONG32 index = 0;
for (; index < 4; index++)
	   {
          cout << SurfPar[index].GetParamU() << endl;
          cout << SurfPar[index].GetParamV() << endl;
	   }
    
       for (index = 0; index < 4; index++)
	   {
          if ( index == 0 || index == 2 )
             IsoPar = CATIsoParamV;
          else
             IsoPar = CATIsoParamU;  
             CATCurve * Boundary = mySurface->ExtractIsoParametricCurve(IsoPar,SurfPar[index], piGeomFactory); 
             // Reset the boundaries to the limits of the face
		     if (Boundary)
			 {
                CATCrvLimits CurveLimits, IsoParLimit;
                CATSurLimits Surlim = *FaceLim;
                Boundary->GetLimits(CurveLimits);
                IsoParLimit = CurveLimits;
				CATSurLimits surfLim;
                mySurface->GetLimits(surfLim);
                IsoParLimit.GetEquivalentLimits(surfLim,Surlim,IsoPar,CurveLimits);
                Boundary->SetLimits(CurveLimits);
			 }
	   }  
	}
    //-----------------------------------------------------------------------------
    // 7- Write the model and close the container
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
