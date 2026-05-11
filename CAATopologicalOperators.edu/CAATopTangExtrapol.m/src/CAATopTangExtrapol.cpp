/**
* @quickReview CRE 03:11:18
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2002
//
// Sample code for : Geometric Modeler
// Mission         : Use of the topological operators: 
//                   Extrapolates a wire.
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Illustrates     : 1- Creates the geometric factory
//                   2- Creates the wire to be extrapolated
//                   3- Performs the tangency extrapolation
//                   4- Performs the curvature extrapolation 
//                   5- Releases the configuration
//                   6- Writes the model
//                   7- Closes the container. 
//
// How to run it   : CAATopTangExtrapol           // to run whithout storing the NCGM file
//                   CAATopTangExtrapol file.NCGM // to run and store the result in file.NCGM                       
//=============================================================================

#include <iostream.h>
#include <iomanip.h>
#include "fstream.h"

#include "CATSoftwareConfiguration.h"  // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory 
#include "CATCGMContainerMngt.h"       // Geometry factory management

// TopologicalObjects
#include "CATBody.h"                   // body
#include "CATDomain.h"                 // domain (boundary of a cell) 
#include "CATCell.h"                   // cell 
#include "CATEdge.h"                   // edge

// NewTopologicalObjects
#include "CATTopData.h"                // TopData of an operator
#include "CATWire.h" 

// BasicTopologicalOpe 
#include "CATTopPointOperator.h"
#include "CATTopSplineOperator.h"

// TopologicalOperators
#include "CATExtrapolateBody.h"       // Tangency extrapolation 
#include "CATWireExtrapolationOp.h"   // Curvature extrapolation

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
    
    //---------------------------------------------------------------------------
    // 2- Creates the wire to be extrapolated
    //---------------------------------------------------------------------------
    //
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig);
    
    const int nbpts = 4;
    CATBody ** aPoints = new CATBody * [nbpts];
    
    aPoints[0] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,10., 0., 0.);
    aPoints[1] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,20., 0., 0.0);
    aPoints[2] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,30., 18., 0.);
    aPoints[3] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,35., 10., 0.5);
    
    CATBody * piSplineBody = ::CATCreateTopSpline(piGeomFactory,
        &topdata,
        nbpts,
        aPoints);
    if (NULL==piSplineBody)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    // Retrieve the wire
    //
    CATDomain * piDomain = NULL;
    piDomain = piSplineBody->GetDomain(1);
    if (NULL==piDomain)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);	
    }	
    
    // Retrieve the cell to be extrapolated
    //
    short dimWire = piDomain->GetLowDimension();
    cout << dimWire << endl;
    if ( 1 != dimWire )
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }

    CATVertex * V1 = NULL;
    CATVertex * V2 = NULL;
    if (piDomain->IsATypeOf(CATWireType)) 
    {
        ((CATWire *)piDomain)->GetExtremities(&V1, &V2);
    }
    else return (1);

    CATCell * cellToExtrapolate = (CATCell *) V2;

    //---------------------------------------------------------------------------
    // 3 - Tangency extrapolation
    //---------------------------------------------------------------------------
    //
    CATExtrapolateBody * extrapolOpe0 =::CATCreateExtrapolateBody(piGeomFactory,
        &topdata,
        piSplineBody,NULL,0);
     if (NULL==extrapolOpe0)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    extrapolOpe0->SetLimitToExtrapolate(cellToExtrapolate, 20.0);
    extrapolOpe0->Run();
    CATBody * pBody0 = extrapolOpe0->GetResult();
    delete extrapolOpe0;
    extrapolOpe0 = NULL;
    
    //---------------------------------------------------------------------------
    // 4 - Curvature extrapolation
    //---------------------------------------------------------------------------
    //
    CATWireExtrapolationOp * extrapolOpe1 =::CATCreateWireExtrapolationOp( piGeomFactory,
        &topdata,piSplineBody);
    if (NULL==extrapolOpe1)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    extrapolOpe1->SetExtrapolation(V2, 20.0);
    extrapolOpe1->Run();
    CATBody * pBody1 = extrapolOpe1->GetResult();
    delete extrapolOpe1;
    extrapolOpe1 = NULL;
    delete [] aPoints;     
    aPoints = 0;
    //---------------------------------------------------------------------------
    // 5 - Releases the configuration
    //---------------------------------------------------------------------------
    //
    pConfig->Release();

    //---------------------------------------------------------------------------
    // 6- Writes the model
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

    // --------------------------------------------------------------------------
    // 7 - Closes the container
    // --------------------------------------------------------------------------
    //
    ::CATCloseCGMContainer(piGeomFactory);
    return (rc);
}

