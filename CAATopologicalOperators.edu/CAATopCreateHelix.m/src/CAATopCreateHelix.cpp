//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2005 
//
// Sample code for : Geometric Modeler
// Mission         : Explain how to create a geometric helix
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Illustrates     : 1- Create the geometric factory
//   how to          2- Create the helices' input data
//                   3- Create an helix with constant pitch and constant radius
//                   4- Create an helix with variable pitch and variable radius
//                   5- Write the model and close the container  
//
// How to run it   : CAATopCreateHelix  // to run whithout storing the NCGM file
//                   CAATopCreateHelix file.NCGM // to run and store the result 
//                   in file.NCGM     
//==================================================================
#include "fstream.h"
// System
#include "IUnknown.h"
// Mathematics
#include "CATMathPoint.h"              // Mathematical point
#include "CATMathLine.h" 
#include "CATSoftwareConfiguration.h"  // Configuration of the operator
#include "CATMathVector.h"
#include "CATMathDef.h"
// AdvancedMathematics
#include "CATMathPolynomX.h"
#include "CATMathFunctionX.h"
#include "CATDataType.h"
// NewTopologicalObjects
#include "CATBody.h"
#include "CATTopDefine.h"
#include "CATTopData.h" 
// GeometricObjects
#include "CATCurve.h"
#include "CATLaw.h"
#include "CATHelix.h"
#include "CATGeoFactory.h"             // Geometry factory
#include "CATCGMContainerMngt.h"       // Management of the geometry factory
#include "CATCartesianPoint.h"         // Geometric Cartesian point
#include "CATNurbsSurface.h"           // NURBS curve
#include "CATKnotVector.h"             // Knot vector
#include "CATCrvLimits.h" 
//GeometricOperators
#include "CATDynMassProperties1D.h"
// TopologicalOperators
#include "CATTopSkin.h"                // Skin creation
#include "CATTopWire.h"                // Create the bodies in order to display the helices
//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (0) or (1) 
         char** iArgv)   // Path to the *.NCGM document that will contain the result of the main.
{
    int ret =0;
    if(2<iArgc) return (1);
    
    char *pfileName = 0;
    int  toStore = 0;
    if (2==iArgc) 
    {
        toStore = 1; 
        pfileName = iArgv[1];
    }
    
    //-----------------------------------------------------------------------------
    // 1- Initializes the factory - create CATSoftwareConfiguration 
	//                              and CATTopData
    //-----------------------------------------------------------------------------
    
    CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer() ;
    if (NULL==piGeomFactory) return (1);	
	CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig);

    //-----------------------------------------------------------------------------
    // 2- Creation of input data 
    //    Axis and origin
    //-----------------------------------------------------------------------------
    //
    CATMathPoint  O(0. , 0. , 0.) , A ( 0., 0., 50.), B(20. ,0. ,0.) ;
	CATMathLine helixAxis;
	HRESULT rc = helixAxis.Set(O, A);
    if (!SUCCEEDED(rc))
    {
		// BMB - Erreur de build sur le cout en 64 bits !!
        //cout << "ERROR in creating the Helix Axis" << endl;
        return 1;
    }

    //-----------------------------------------------------------------------------
    // 3- Creation of an helix with a constant pitch and constant radius
    //-----------------------------------------------------------------------------
    
	// (a) - Create the CATHelix
    CATHelix * pHelix0 = piGeomFactory->CreateHelix(helixAxis, /* the axis oz */
		B,                    /* the origin */
		90*CATDegreeToRadian, /* the start angle in radians */
		7*CAT2PI,             /* the end angle in radians */ 
		20,                   /* the pitch */ 
		1,                    /* the orientation with respect to the axis */
		0);                   /* the radius evolution = number of mm/turn*/
	if ( 0 == pHelix0 )
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }

	// (b) - Create the wire
	CATCurve * pCurve0 = (CATCurve*)pHelix0;
    CATCrvLimits curLim0[1];
    CATOrientation orient0[1]={1};
    pCurve0->GetLimits( curLim0[0] );
    CATLONG32 nbCurve = 1;
    CATCurve ** listOfCurves0 = new CATCurve * [nbCurve];
    listOfCurves0[0] = pCurve0;
    CATTopWire * pWireOp0 = CATCreateTopWire(piGeomFactory, 
                                            &topdata,
                                            1,
                                            listOfCurves0,
                                            curLim0,
                                            orient0);
    delete [] listOfCurves0 ;
    listOfCurves0 = 0;
    if ( 0 == pWireOp0 )
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    pWireOp0->Run();
    CATBody * piHelix0 = pWireOp0->GetResult();
    delete pWireOp0; pWireOp0 = NULL;

    //-----------------------------------------------------------------------------
    // 4- Creation of an helix with a variable pitch and a variable radius
    //-----------------------------------------------------------------------------
	//
	// (a) - Initialize the data 
	CATHelix * pHelix1 = piGeomFactory->CreateHelix(helixAxis, /* the axis */
		B,          /* the origin */
		0.,         /* the start angle */ 
        CAT2PI,     /* the end angle */
        1.,         /* the pitch */
        1,          /* the orientation */ 
        0.);        /* no law evolution */ 
    if ( 0 == pHelix1 )
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
		             
    // (b) - Retrieve the length of the basic helix
	//
    CATDynMassProperties1D * pDynOpe1 =:: CATDynCreateMassProperties1D(pHelix1, pConfig);
	if ( 0 == pDynOpe1 )
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
	CATPositiveLength theLength1= pDynOpe1->GetLength();
    delete pDynOpe1;
	//
	// (c) - create the radius linear law: radius is 100
	CATLaw * radiusLaw = ((CATLaw*)(piGeomFactory -> CreateLinearLaw(0.0, 100.0, theLength1, 100)));

	//
    // (d) - create the law which defines how the 
	//       helix is developed along the helix axis
	//       at the beginning of the curve, the z coordinate is 0.
	//       at the end of the curve, the Z coordinate is 0 + 0 + 0.02*(CATCrvParam)**2

	double LimitParameters1 [2];                 // Intervals
    LimitParameters1[0] = 0;                     // lower bound of first interval
    LimitParameters1[1] = theLength1;   
	const CATMathFunctionX **  Functions1 = new const CATMathFunctionX * [1];
	double array1[3] = {0.0,0,0.02};                      
    Functions1[0] = new CATMathPolynomX(2,array1); 
    CATLaw * ZLaw = (CATLaw*)piGeomFactory->CreateCompositeLaw (1,LimitParameters1,Functions1);

    // (e) - create the linear law for the angle (number of turns = 9)
	//       at the beginning of the curve, the number of turns is 0
	//       at the end it is 9.
	CATLaw * thetaLaw = ((CATLaw*)(piGeomFactory -> CreateLinearLaw(0.0, 0.0, theLength1, 9*CAT2PI)));
    
	// (f) - Set the helix parameters
	//
	// The vector which defines the helix axis (Oz)
	CATMathVector iUnitZ (0.,0.,1.); 
	// The vector to be used as reference for angles and turns (Ox)
    CATMathVector iUnitu (1.,0.,0.); 

    pHelix1->Set(O, iUnitZ, iUnitu, 
		1, 1, 1,        // no ratio applied to the helix coordinates
		radiusLaw,      // the radius law
		ZLaw,           // the law along z
		thetaLaw,       // the theta las
		90*CATDegreeToRadian,    // the start angle
		1);                      // the orientation

	// Retrieve the minimum and the maximum coordinates along z
    CATCurve * pCurve1 = (CATCurve*)pHelix1;
	CATCrvLimits maxLimits;
    pCurve1->GetMaxLimits(maxLimits);
	CATCrvParam startParam, endParam;
    maxLimits.GetExtremities(startParam, endParam);
	double zMin;
    pHelix1->GetZFromParameter(startParam, zMin);
	//cout << "zMin " << zMin << endl;
	double zMax;
    pHelix1->GetZFromParameter(endParam, zMax);
	//cout << "zMax " << zMax << endl;

	// (g) - Create the wire
	//
    CATCrvLimits curLim1[1];
    CATOrientation orient1[1]={1};
    pCurve1->GetLimits( curLim1[0] );

    CATCurve ** listOfCurves1 = new CATCurve * [nbCurve];
    listOfCurves1[0] = pCurve1;
    CATTopWire * pWireOp1 = CATCreateTopWire(piGeomFactory, 
                                            &topdata,
                                            1,
                                            listOfCurves1,
                                            curLim1,
                                            orient1);
    delete [] listOfCurves1 ;
    listOfCurves1 = 0;
    if ( 0 == pWireOp1 )
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    pWireOp1->Run();
    CATBody * piHelix1 = pWireOp1->GetResult();
    delete pWireOp1; pWireOp1 = NULL;

    //-----------------------------------------------------------------------------
    // 5- Write the model and close the container
    //-----------------------------------------------------------------------------
    //
	if (Functions1) 
	{
		delete Functions1[0] ;
		delete [] Functions1; 
		Functions1 = NULL;
	}
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
    
    return (ret);
}
