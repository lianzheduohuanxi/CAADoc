/**
* @quickReview CRE 04:03:02
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2003
//
// Sample code for : Geometric Modeler
// Mission         : Explains how to create a a blend by specifying coupling modes
//           
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Main steps        1- Create the geometry factory and other preliminary operations
//                   2- Create the input data
//                   3- Create the CATTopBlend operator
//                   4- Write the model and close the container  
//
// How to run it   : CAAAdtBlendWithCouplingModes   // to run whithout storing the NCGM file
//                   CAAAdtBlendWithCouplingModes file.NCGM // to run and store the result 
//                   in file.NCGM     
//=============================================================================
#include <iostream.h>
#include "fstream.h"

// AdvancedTopologicalOpe 
#include "CATCreateTopBlend.h"               // Blend operator
#include "CATTopBlend.h"

// Mathematics
#include "CATSoftwareConfiguration.h"        // Configuration of the operator
#include "CATMathDirection.h" 
#include "CATMathPlane.h"

// GeometricObjects
#include "CATGeoFactory.h"                   // Geometry factory
#include "CATCGMContainerMngt.h"             // Geometry factory management
#include "CATLine.h"                         // Geometrical line
#include "CATCrvLimits.h"                    // Curve limits definition

// TopologicalOperators
#include "CATTopWire.h"                      // Topological wire
#include "CATTopPrism.h"                     // Surface extrusion
#include "CATHybOperator.h"
#include "CATCreateTopProject.h"             // Projection operator
                  
// NewTopologicalObjects
#include "CATTopData.h"                      // Topdata of an operator
#include "CATBody.h"                         // Body
 
// 

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
    
    // --------------------------------------------------------------------------
    // 1 - Initialize the factory 
    // --------------------------------------------------------------------------
    //
    CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer() ;
    if (NULL == piGeomFactory)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig);

    // ---------------------------------------------------------------------------
    // 2 -  Create the input data
    // ---------------------------------------------------------------------------
    //   ----
    //   A - Data for the first surface
    //   ----
    // 
    //   (a) - Create a wire from a circle and a line (G2 continuity)
    //
    CATMathPoint Absolute;
    CATMathDirection yDir(0.,1.,0.);
    CATMathDirection zDir(0.,0.,1.);
    CATMathPlane MathPlane(Absolute,yDir,zDir);
    
    double radius = 20.;
    double angleStart1 = 0;
    double angleEnd1 = CATPI;
    
    // Create the circle
    CATCircle * piCircle0 = piGeomFactory->CreateCircle(radius, MathPlane,
        angleStart1, angleEnd1);
    if (NULL==piCircle0)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }  
    
    CATMathPoint P0(0,20,0);
    CATMathPoint P1(-0.0, 20.,-20.0);
    
    // Create the line
    CATLine * piLine0 = piGeomFactory->CreateLine(P1,P0);
    
    if (NULL==piLine0 )
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    } 
    
    // Create the CATTopWire operator - run it - get the resulting body
    //
    CATLONG32 nbcurve0 = 2;
    
    CATCurve ** aListOfCurves0 = new CATCurve * [nbcurve0];
    CATCrvLimits * curLimits0 = new CATCrvLimits[nbcurve0];
    short * wireOrientations0 = new short[nbcurve0];
    
    aListOfCurves0[0] = (CATCurve *)piLine0;
    aListOfCurves0[1] = (CATCurve *)piCircle0;
    int i = 0;
for (; i < nbcurve0 ; i++)
    {
		CATCurve * pLocalCurve = aListOfCurves0[i];
		if ( pLocalCurve != NULL )
            pLocalCurve->GetLimits(curLimits0[i]);
        wireOrientations0[i]=short(1);
    } 
    
    CATTopWire * pWire0 = ::CATCreateTopWire(piGeomFactory, 
        &topdata,
        nbcurve0,
        aListOfCurves0,
        curLimits0,
        wireOrientations0);
    if (NULL==pWire0)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    pWire0->Run();
    CATBody * piInitialWire0 = pWire0->GetResult();
    if (NULL==piInitialWire0)
    {
        cout << "piInitialWire0 NULL" << endl;
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    } 
    //
    // Clean useless data
    delete[] wireOrientations0; wireOrientations0=NULL;
    delete[] curLimits0; curLimits0=NULL;
    
    for (i=0; i < nbcurve0; i++)
        piGeomFactory -> Remove (aListOfCurves0[i]);
    delete [] aListOfCurves0;
    
    delete pWire0; pWire0=NULL;
    
    //   (b) Extrude the created wire to obtain the first surface
    //
    CATMathDirection   zDir1(1., 0.,  0.);
    double startOffset = -20.;
    double endOffset   = 0.;
    CATTopPrism       *pPrismOp = ::CATCreateTopPrism (piGeomFactory,
        &topdata,
        piInitialWire0,
        &zDir1,
        startOffset,
        endOffset);
    
    if (NULL==pPrismOp)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    pPrismOp->Run();
    
    CATBody * piMainBody0=NULL;
    piMainBody0 = pPrismOp->GetResult();
    
    delete pPrismOp;
    pPrismOp = NULL;

    //  (c) - Project the initial wire on the initial surface
    //       (this has to be done because the initial wire must have a "lying on" 
    //       link with the initial surface 
    
    CATHybOperator * pProjectOpe = (CATHybOperator *)CATCreateTopProject(piGeomFactory, &topdata,
        piInitialWire0,piMainBody0);
    if (NULL==pProjectOpe)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    pProjectOpe->Run();
    CATBody * piWireLyingOn0 = pProjectOpe->GetResult();
    delete pProjectOpe;
    pProjectOpe = NULL;
    
    //    ----
    //    B - Data for the second surface
    //    ----
    
    CATMathPoint PtPlane (40,0, 30);;
    CATMathPlane MathPlane1(PtPlane,yDir,zDir);
    
    //    (a) - Create a wire from a circle and a line (G2 continuity)
    //
    CATCircle * piCircle1 = piGeomFactory->CreateCircle(40.0, MathPlane1,
        angleStart1, angleEnd1);
    if (NULL==piCircle1)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }  
    CATMathPoint P2(40,40,-50);
    CATMathPoint P3(40.0, 40.,30.0);
    
    CATLine * piLine1 = piGeomFactory->CreateLine(P2,P3);
    
    if (NULL==piLine0 )
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    } 
    
    CATLONG32 nbcurve1 = 2;
    
    CATCurve ** aListOfCurves1 = new CATCurve * [nbcurve1];
    CATCrvLimits * curLimits1 = new CATCrvLimits[nbcurve1];
    short * wireOrientations1 = new short[nbcurve0];
    
    aListOfCurves1[0] = (CATCurve *)piLine1;
    aListOfCurves1[1] = (CATCurve *)piCircle1;
    for (i = 0; i < nbcurve1 ; i++)
    {
		CATCurve * pLocalCurve = aListOfCurves1[i];
		if ( pLocalCurve != NULL)
            pLocalCurve->GetLimits(curLimits1[i]);
        wireOrientations1[i]=short(1);
    } 
    
    CATTopWire * pWire1 = ::CATCreateTopWire(piGeomFactory, 
        &topdata,
        nbcurve1,
        aListOfCurves1,
        curLimits1,
        wireOrientations1);
    if (NULL==pWire1)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    pWire1->Run();
    CATBody * piInitialWire1 = pWire1->GetResult();
    if (NULL==piInitialWire1)
    {
        cout << "piInitialWire1 NULL" << endl;
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    } 
    
    // Clean useless data
    delete[] wireOrientations1; wireOrientations1=NULL;
    delete[] curLimits1; curLimits1=NULL;
    
    for (i=0; i < nbcurve1; i++)
        piGeomFactory -> Remove (aListOfCurves1[i]);
    delete [] aListOfCurves1;
    
    delete pWire1; pWire1=NULL;
    //
    //   (b) - Create the second support
    //
    CATTopPrism       *pPrismOp1 = ::CATCreateTopPrism (piGeomFactory,
        &topdata,
        piInitialWire1,
        &zDir1,
        20.0,
        0.0);
    
    if (NULL==pPrismOp1)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    pPrismOp1->Run();
    
    CATBody * piMainBody1=NULL;
    piMainBody1 = pPrismOp1->GetResult();
    
    delete pPrismOp1;
    pPrismOp1 = NULL;
    //   (c) - Project the initial wire on the initial surface
    //       (this has to be done because the initial wire must have a "lying on" 
    //       link with the initial surface 
    pProjectOpe = (CATHybOperator *)CATCreateTopProject(piGeomFactory, &topdata,
        piInitialWire1,piMainBody1);
    if (NULL==pProjectOpe)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    pProjectOpe->Run();
    CATBody * piWireLyingOn1 = pProjectOpe->GetResult();
    delete pProjectOpe;
    pProjectOpe = NULL;
    
    // ----------------------------------------------------------
    // 3 - Blend creation
    // ----------------------------------------------------------
    // 
    // (a) Operator creation
    //
    CATTopBlend * pBlendOpe =::CATCreateTopBlend(
                             piGeomFactory,   // geometry factory
							 &topdata,        // topdata - configuration management
                             piWireLyingOn1,    // the first wire to be connected 
                             piWireLyingOn0,    // the second wire to be connected
                             piMainBody1,     // the supporting surface of the first wire
                             piMainBody0);    // the supporting surface of the second wire
        
   if (NULL==pBlendOpe)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    // (b) Set the coupling mode 
    //
    //pBlendOpe->SetCouplingMode(CATTopBlend::CATTopBlendCouplingMode_DomainG0);
    //pBlendOpe->SetCouplingMode(CATTopBlend::CATTopBlendCouplingMode_DomainG1);
    //pBlendOpe->SetCouplingMode(CATTopBlend::CATTopBlendCouplingMode_DomainG2);
    pBlendOpe->SetCouplingMode(CATTopBlend::CATTopBlendCouplingMode_Edge);

    // (c) Set a transition continuity 
    //
    pBlendOpe->SetTransitionContinuity(1,2);  // curvature continuity for the first wire
    pBlendOpe->SetTransitionContinuity(2,1);  // tangency continuity for the second wire
    
    pBlendOpe->Run();
    CATBody * pBodyBlend = pBlendOpe->GetResult();
    
    delete pBlendOpe;
    pBlendOpe = NULL;
    //
    // ----------------------------------------------------------
    // 4 - Close the application
    // ----------------------------------------------------------
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
