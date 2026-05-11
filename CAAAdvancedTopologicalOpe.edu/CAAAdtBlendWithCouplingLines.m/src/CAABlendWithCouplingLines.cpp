/**
* @quickReview CRE 04:03:02
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2003
//
// Sample code for : Geometric Modeler
// Mission         : Explains how to create a a blend by specifying coupling lines
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
// How to run it   : CAAAdtBlendWithCouplingLines   // to run whithout storing the NCGM file
//                   CAAAdtBlendWithCouplingLines file.NCGM // to run and store the result 
//                   in file.NCGM     
//=============================================================================
#include <iostream.h>
#include "fstream.h"

// BasicTopologicalOpe
#include "CATTopPointOperator.h" 
#include "CATTopLineOperator.h"
#include "CATTopSplineOperator.h"

// AdvancedTopologicalOpe
#include "CATCreateTopBlend.h"               // Blend creation
#include "CATTopBlend.h"

// Mathematics
#include "CATSoftwareConfiguration.h"        // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"                   // Geometry factory
#include "CATCGMContainerMngt.h"             // Geometry factory management
#include "CATLine.h"                         // Geometrical line
#include "CATCrvLimits.h"                    // Curve limits definition

// TopologicalOperators
#include "CATTopWire.h"                      // Topological wire
#include "CATTopPrism.h"                     // Extruded surface
#include "CATHybOperator.h"
#include "CATCreateTopProject.h"             // Projection operators
               
// NewTopologicalObjects
#include "CATBody.h"  
#include "CATTopData.h"                      // Topdata of an operator


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
    //
    // ---------------------------------------------------------------------------
    // 2 -  Create the input data
    // ---------------------------------------------------------------------------
    //
    //   ----
    //   A - Create the coupling lines 
    //   ----
    //     
    const int nbpts = 3;
    CATBody * aPoints1[3];
    
    aPoints1[0] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,0,-20,0);
    aPoints1[1] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,0.0, 0.,20.0);
    aPoints1[2] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,0.0,30,20.0);

    const int nbpts1 = 3;
    CATBody * aPoints2[3];
    //
    aPoints2[0] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,40,-40,30);
    aPoints2[1] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,40.0, -18.,50.0);
    aPoints2[2] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,40.0,40,30.0);
   
    // 
    CATBody * piGuide1 = ::CATCreateTopLineFromPoints(piGeomFactory,
        &topdata,
        aPoints1[0],
        aPoints2[0] );
    
    CATBody * piGuide2 = ::CATCreateTopLineFromPoints(piGeomFactory,
        &topdata,
        aPoints1[0],
        aPoints2[1] );
    
    CATBody * piGuide3 = ::CATCreateTopLineFromPoints(piGeomFactory,
        &topdata,
        aPoints1[2],
        aPoints2[2] );
    
    CATLISTP(CATGeometry) guides;
    CATGeometry * piGuideGeom1 = (CATGeometry*)piGuide1;
    CATGeometry * piGuideGeom2 = (CATGeometry*)piGuide2;
    CATGeometry * piGuideGeom3 = (CATGeometry*)piGuide3;
    guides.Append(piGuideGeom1);
    guides.Append(piGuideGeom2);
    guides.Append(piGuideGeom3);
    
    //   ----
    //   B - Create the first wire and support 
    //   ----
    CATBody * piInitialWire0 = ::CATCreateTopSpline(piGeomFactory,
        &topdata,
        nbpts,
        aPoints1);
    if (NULL==piInitialWire0)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    } 
    
    CATMathDirection   zDir1(1., 0.,  0.);
    double startOffset = -20.;
    double endOffset   = 0.;
    CATTopPrism       *pPrismOpe = ::CATCreateTopPrism (piGeomFactory,
        &topdata,
        piInitialWire0,
        &zDir1,
        startOffset,
        endOffset);
    if (NULL==pPrismOpe)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    } 
    pPrismOpe->Run();
    
    CATBody * piMainBody0=NULL;
    piMainBody0 = pPrismOpe->GetResult();

    delete pPrismOpe;
    pPrismOpe=NULL;
    
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
    pProjectOpe=NULL;
    
    //   ----
    //   C - Create the second wire and support 
    //   ----
    CATMathPoint P1(40,-40,30);
    CATMathPoint P2(40.0, -18.,50.0);
    CATMathPoint P3(40.0,40,30.0);
    CATLine * piLine1 = piGeomFactory->CreateLine(P1,P2);
    CATLine * piLine2 = piGeomFactory->CreateLine(P2,P3);
    
    CATLONG32 nbcurve1 = 2;
    
    CATCurve ** ListOfCurves1 = new CATCurve * [nbcurve1];
    CATCrvLimits * curLimits1 = new CATCrvLimits[nbcurve1];
    short * wireOrientations1 = new short[nbcurve1];
    
    ListOfCurves1[0] = (CATCurve *)piLine1;
    ListOfCurves1[1] = (CATCurve *)piLine2;
    int i = 0;
for (; i < nbcurve1 ; i++)
    {
		CATCurve * pLocalCurve = ListOfCurves1[i];
		if (pLocalCurve != NULL)
            pLocalCurve->GetLimits(curLimits1[i]);
        wireOrientations1[i]=short(1);
    } 
    
    CATTopWire * pWire1 = ::CATCreateTopWire(piGeomFactory, 
        &topdata,
        nbcurve1,
        ListOfCurves1,
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
    //
    // Clean data
    //
    delete[] wireOrientations1; wireOrientations1=NULL;
    delete[] curLimits1; curLimits1=NULL;
    
    for (i=0; i < nbcurve1; i++)
        piGeomFactory -> Remove (ListOfCurves1[i]);
    delete [] ListOfCurves1;
    
    delete pWire1; pWire1=NULL;
    
    CATTopPrism       *pPrismOpe1 = ::CATCreateTopPrism (piGeomFactory,
        &topdata,
        piInitialWire1,
        &zDir1,
        20.0,
        0.0);
    if (NULL==pPrismOpe1)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    pPrismOpe1->Run();
    
    CATBody * piMainBody1=NULL;
    piMainBody1 = pPrismOpe1->GetResult();

    delete pPrismOpe1;
    pPrismOpe1 = NULL;
    
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
    // ---------------------------------------------------------------------------
    // 2 -  Create the CATTopBlend operator
    // --------------------------------------------------------------------------
    
    CATTopBlend * pBlendOpe =::CATCreateTopBlend(piGeomFactory,
							 &topdata, piWireLyingOn1, piWireLyingOn0,
                             piMainBody1,
                             piMainBody0); 
    if (NULL==pBlendOpe)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    // Case 1 - SetCouplingMode
    // pBlendOpe->SetCouplingMode(CATTopBlend::CATTopBlendCouplingMode_DomainG1);
    
    // Case 2 - SetCouplingLines
    pBlendOpe->SetCouplingLines(&guides);
    pBlendOpe->SetTransitionContinuity(1,2);  // curvature continuity 
    pBlendOpe->SetTransitionContinuity(2,1);  // tangency continuity
    
    pBlendOpe->Run();
    CATBody * pBodyBlend = pBlendOpe->GetResult();
    delete pBlendOpe;
    pBlendOpe=NULL;
    // ---------------------------------------------------------------------------
    // 3 -  Close the application 
    // --------------------------------------------------------------------------
    
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
