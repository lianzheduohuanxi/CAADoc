/**
* @quickReview CRE 02:10:21
*/
// ========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
// Sample code for : Geometric Modeler
// Mission         : Explain how to use the CATFrFTopologicalSweep operator 
//                   along with a boolean operation to write a threading 
//                   operator.
//
// Main functions    1- Constructor, destructor 
//                   2- Global function to create the sweep profile
//                   3- Global function to create a sweep
//                   4- Run method
//                   5- GetResult  
//
// How to run it   : CAAAdtThread operator called from CAAAdtThreadOpMain
// ========================================================================

#include "CAAAdtThread.h"
#include <iostream.h>

//Mathematics
#include "CATMathPoint.h"
#include "CATMathDirection.h"
#include "CATMathAxis.h"
#include "CATMathPlane.h"
#include "CATSoftwareConfiguration.h"
#include "CATMath.h"

//GeometricObjects
#include "CATGeoFactory.h"
#include "CATSurParam.h"
#include "CATPlane.h"
#include "CATCylinder.h"
#include "CATCrvLimits.h"
#include "CATPLine.h"

//NewTopologicalObjects
#include "CATBody.h"
#include "CATCell.h"
#include "CATTopData.h"

//BasicTopologicalOpe
#include "CATTopLineOperator.h"
#include "CATTopHelixOperator.h"
#include "CATTopPointOperator.h"

//TopologicalOperators
#include "CATDynBoolean.h"
#include "CATTopSkin.h"

//AdvancedTopologicalOpe
#include "CreateFrFTopologicalSweep.h"
#include "CATFrFTopologicalSweep.h"
#include "CATCloseOperator.h"

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAAAdtThread::CAAAdtThread(CATGeoFactory *iGeoFactory, CATTopData *iTopData, 
                           CATBody *iBody, CATCylinder *iCylinder, 
                           double iLength) 
                           
{
    cout << "CAAAdtThread constructor " << endl;
    _bodyResult = NULL;
    _factory = iGeoFactory;
    _inputBody = iBody;
    _inputCylinder = iCylinder;
    _length = iLength;
    _topData = iTopData;
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
CAAAdtThread::~CAAAdtThread()
{
    _bodyResult = NULL;
    _factory = NULL;
    _inputBody = NULL;
    _inputCylinder = NULL;
    _length = NULL;
    _topData = NULL;
}

// ----------------------------------------------------------------------------
// Global function to create the sweep profile
// ----------------------------------------------------------------------------
CATBody * CAASweepProfile(CATGeoFactory* myFactory,
                          CATTopData * myTopdata,
                          CATPlane * iPlane, 
                          double x1, double y1,
                          double x2, double y2,
                          double x3, double y3)
{
    if ( (NULL == myFactory) 
        || (NULL == myTopdata) 
        || (NULL == iPlane) ) return NULL;
    
        const int nbOfCurves=3;
        CATSurParam thePoints[nbOfCurves+1];
        CATPCurve* theLines[nbOfCurves];
        CATCrvLimits theLimits[nbOfCurves];
        short theOrientations[nbOfCurves] = {1,1,1};
        
        iPlane->CreateParam(x1, y1, thePoints[0]);
        iPlane->CreateParam(x2, y2, thePoints[1]);
        iPlane->CreateParam(x3, y3, thePoints[2]);
        
        thePoints[3]=thePoints[0];
        
        int i = 0;
for (;i<nbOfCurves;i++) {
            theLines[i] = myFactory->CreatePLine(
                thePoints[i],
                thePoints[i+1],
                iPlane);
            theLines[i]->GetLimits( theLimits[i]);
        }
        
        // Create the skin from the profile
        // 
        CATTopSkin * pSkinOperator = CATCreateTopSkin(
            myFactory,
            myTopdata,
            iPlane,
            nbOfCurves,
            theLines,
            theLimits,
            theOrientations
            );
        
        if (NULL == pSkinOperator) return NULL;
        
        pSkinOperator->Run();

        CATBody* piSection = pSkinOperator->GetResult();
        delete pSkinOperator;
        pSkinOperator = NULL;
        for ( i=0 ;i<nbOfCurves;i++)
            myFactory->Remove(theLines[i]);
        return piSection;
}
// -------------------------------------------------------------
// Global function to create the sweep
// -------------------------------------------------------------
CATBody * CAASweepCreate( CATGeoFactory* myFactory,
                         CATTopData * myTopdata, 
                         CATBody * iHelix,
                         CATBody * iSection,
                         CATGeometry *refElem)
{
     if ( (NULL == myFactory) 
        || (NULL == myTopdata) 
        || (NULL == iHelix)
        || (NULL == iSection)
        || (NULL == refElem)) return NULL;

    // =============================================================
    // 1 - Create the sweep
    // =============================================================

    // a - Create the sweep operator
    //
    CATFrFTopologicalSweep * pSweepOperator = CATCreateFrFTopologicalSweep(
        myFactory,
        myTopdata,
        iHelix,     //  guide
        iSection);  //  profile
    
    if (NULL == pSweepOperator) return NULL;
    
    // b - Set the sweep properties and run the operator
    //
    CATMathAxis Ref; // the canonical math axis
    pSweepOperator->SetProfilePositionType(1);
    pSweepOperator->SetProfilePosition(&Ref);  // set profile axis system
    pSweepOperator->SetReferenceElement(refElem); 
    pSweepOperator->Run();

    // c - Retrieve the sweep body
    CATBody* piThreadingTool=pSweepOperator->GetResult();
    
    // d - Delete the operator
    //
    delete pSweepOperator; 
    pSweepOperator = NULL;
    
    // =============================================================
    // 2 - Create the volume
    // =============================================================
    //
    // a - Create the close operator
    //
    CATCloseOperator *  pCloseOpe = NULL;
    pCloseOpe = CATCreateCloseOperator(myFactory,
        myTopdata, piThreadingTool);
    
    if (NULL == pCloseOpe) return NULL;
    
    // b - Run the operator
    //
    pCloseOpe->Run();

    // c - Retrieve the result
    //
    CATBody * piCloseBodyResultat = pCloseOpe->GetResult();
    
    // d - Delete the operator
    //
    delete pCloseOpe;
    pCloseOpe = NULL;
    
    myFactory->Remove(piThreadingTool);
    
    return piCloseBodyResultat;
}

int CAAAdtThread::Run()
{
    int rc = 0;

    // 1 - Retrieve the software configuration
    //
    CATSoftwareConfiguration *currentConfig = _topData->GetSoftwareConfiguration();
    
    // 2 - Retrieve the solid cylinder data
    // 
    CATMathAxis  cylAxis;
    CATMathDirection  cylDirection;  // cylinder main direction
    CATMathDirection  cylOrthoDir1;  // cylinder orthogonal direction
    CATMathDirection  cylOrthoDir2;  // cylinder orthogonal direction
    CATMathPoint cylOrigin;
    double cylStartLength;
    double cylEndLength;
    double cylRadius;
    
    _inputCylinder->GetAxis(cylAxis);
    cylAxis.GetOrigin(cylOrigin);
    cylAxis.GetFirstDirection(cylOrthoDir1);
    cylAxis.GetSecondDirection(cylOrthoDir2);
    cylAxis.GetThirdDirection(cylDirection);
    cylStartLength = _inputCylinder->GetStartLength();
    cylEndLength = _inputCylinder->GetEndLength();
    cylRadius = _inputCylinder->GetRadius();
    
    // 3 - Helix creation
    // 
    
    // a - Definition of the helix parameters
    //     
    CATMathPoint P1(0.,0.,_length);   // _length is the non threaded length
    CATMathPoint P2 = P1 + cylDirection;
    
    // Helix origin
    //
    CATBody * piBPOrigin = CATCreateTopPointXYZ ( 
        _factory,
        _topData,
        P1.GetX() + (cylRadius + 0.005),
        P1.GetY() ,
        P1.GetZ());
    
    // Helix axis 
    // 
    CATBody * piBP1 = CATCreateTopPointXYZ (
        _factory,
        _topData,
        P1.GetX(),
        P1.GetY(),
        P1.GetZ());
    
    CATBody * piBP2 = CATCreateTopPointXYZ ( 
        _factory,
        _topData,
        P2.GetX(),
        P2.GetY(),
        P2.GetZ());
    
    CATBody* piHelixAxis = CATCreateTopLineFromPoints( 
        _factory,
        _topData,
        piBP1,
        piBP2);
    
    _factory->Remove(piBP1);
    _factory->Remove(piBP2);
    
    // b - Helix creation
    //
    const double pitch = 1.80;
    double helixAngleInt=(((cylStartLength+cylEndLength-_length)/pitch)+0.5)*2;
    cout << helixAngleInt << endl;
    
    cout << helixAngleInt << endl;
    CATBody* piHelix = CATCreateTopHelix(
        _factory,
        _topData,
        piHelixAxis,
        1,
        piBPOrigin,
        CATAngle (0),
        CATAngle (helixAngleInt*CATPI),
        CATLength (pitch),
        1);
    
     _factory->Remove(piBPOrigin);  
     _factory->Remove(piHelixAxis);
    
    // ------------------------------------------------------------------
    // ------------------------------------------------------------------
    // 4 - Creation of a first sweep
    // ------------------------------------------------------------------
    // ------------------------------------------------------------------
    
    //
    // a - Data required for the profile creation
    //
    
    double Angle=CATPI/3.;
    
    double DX = sin(Angle)* pitch*7./8.;
    double DY = ( pitch + 0.005)/2 ; 
    
    cout << "DX " << DX << endl;
    cout << "DY " << DY << endl;
    
    const int nbOfCurves=3;
    
    CATPlane * PlaneXOY = _factory->CreatePlane(CATMathPlane());
    
    // Profile creation
    //
    CATBody * piSwSection = ::CAASweepProfile(_factory,
        _topData, PlaneXOY,
        0,0,
        DX, DY,
        0, DY);
     if (piSwSection == NULL) return 1;
    // Sweep creation
    //
    CATBody * piCloseBodyResultat = ::CAASweepCreate(_factory,
        _topData,
        piHelix,   
        piSwSection,
        PlaneXOY); 
    if (piCloseBodyResultat == NULL) return 1;
    // Remove 
    //
    CATDynBoolean *pDynRemoveOpe = NULL;
    pDynRemoveOpe = CATCreateDynBoolean(
        _factory,
        _topData,
        CATBoolRemoval,
        _inputBody,
        piCloseBodyResultat);

    if (pDynRemoveOpe == NULL) return 1;

    pDynRemoveOpe->Run();
    
    CATBody * piBoolResultat = pDynRemoveOpe->GetResult();
    
    delete pDynRemoveOpe;
    pDynRemoveOpe = NULL;
    
    // 
    // ------------------------------------------------------------------
    // ------------------------------------------------------------------
    // 5 - Create a second sweep 
    // ------------------------------------------------------------------
    // ------------------------------------------------------------------
    CATBody * piSwSection1 = ::CAASweepProfile(_factory,
        _topData, PlaneXOY,
        0, DY,  
        DX,  DY,
        0,2*DY );
    if (NULL == piSwSection1) return 1;
    CATBody * piCloseBodyResultat1 = ::CAASweepCreate(_factory,
        _topData,
        piHelix,   
        piSwSection1,
        PlaneXOY); 
    if (NULL == piCloseBodyResultat1) return 1;

    CATDynBoolean *pDynRemoveOpe1 = NULL;
    cout << "CATBoolRemoval1 " << endl;
    pDynRemoveOpe1 = CATCreateDynBoolean(
        _factory,
        _topData,
        CATBoolRemoval,
        piBoolResultat,
        piCloseBodyResultat1);

    if (NULL == pDynRemoveOpe1) return 1;
    
    pDynRemoveOpe1->Run();
    
    CATBody * piBoolResultat1 = pDynRemoveOpe1->GetResult();
    
    delete pDynRemoveOpe1;
    pDynRemoveOpe1 = NULL;
    
    _bodyResult = piBoolResultat1;
    
    // -----------------------------------------------------
    // 6 - Remove the no longer needed bodies
    // -----------------------------------------------------
    //
    _factory->Remove(piCloseBodyResultat1);
    _factory->Remove(piSwSection1);
    _factory->Remove(piSwSection);
    _factory->Remove(piCloseBodyResultat);
    _factory->Remove(piBoolResultat);
    _factory->Remove(PlaneXOY);
    _factory->Remove(piHelix);
    
    // ----------------------------------------------------
    // 7 - Get the face list
    // ----------------------------------------------------
    
    CATLISTP(CATCell)  faceList;
    
    if (NULL == piBoolResultat1) return 1;
    piBoolResultat1->GetAllCells( faceList,2);
    cout << "number of Faces " <<  faceList.Size() << endl;
    
    if (faceList.Size() != 7)
    {
        cout << "Modify the sweep profile " << endl;
    }
    
    _factory->Remove(_inputBody);
    
    return rc;
    
}

CATBody *CAAAdtThread::GetResult()
{
    return _bodyResult;
}


