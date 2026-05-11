/**
* @quickReview CRE 03:10:17
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2000
//
// Sample code for : Geometric Modeler
// Mission         : Use of the basic topological operators
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return Codes (if not null, the model is not saved)
//                   1- Null pointer
//
// Illustrates     : 1- Creation of the geometric factory
//                   2- Direct creation of point bodies
//                   3- Direct creation of spline body
//                   4- Use of a topological operator to create a spline
//                    - a - create
//                    - b - run 
//                    - c - get results
//                    - c - delete
//                   5- Length computation 
//                   6- Unused point bodies deletion
//                   7- Factory close. 
//
// How to run it   : CAATopSpline            // to run whithout storing the NCGM file
//                   CAATopSpline  file.NCGM // to run and store the result in file.NCGM                       
//=============================================================================

#include <iostream.h>
#include <iomanip.h>
#include "fstream.h"

// Mathematics
#include "CATMathVector.h"               // Mathematical vector
#include "CATSoftwareConfiguration.h"  // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"               // Geometry factory
#include "CATCGMContainerMngt.h"         // Management of the geometry factory

// TopologicalObjects
#include "CATBody.h"                     // Body
#include "CATTopData.h"                // TopData of an operator

// BasicTopologicalOpe
#include "CATTopPointOperator.h"         // To create point bodies
#include "CATTopLineOperator.h"          // To create line bodies   
#include "CATTopSplineOperator.h"        // To create spline bodies
#include "CATLengthFromBodyOnWire.h"     // To compute length

//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (0) or (1) 
         char** iArgv)   // Path to the *.NCGM document that will contain the result of the main.
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
    // 1-Initializes the factory 
    //----------------------------------------------------------------------------
    
    CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer() ;
    if (NULL==piGeomFactory) return (1);
    
    //----------------------------------------------------------------------------
    // 2-Directly creates of point bodies 
    //----------------------------------------------------------------------------
    const int nbpts = 4;
    CATBody ** aPoints = new CATBody * [nbpts];
    
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig);
    
    aPoints[0] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,10., 15., 0.);
    aPoints[1] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,20., 20., 0.5);
    aPoints[2] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,30., 18., 0.);
    aPoints[3] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,40., 15., 0.5);
    
    //----------------------------------------------------------------------------
    // 3-Directly creates a spline body without any tangent or curvature imposition.
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
    //----------------------------------------------------------------------------
    // 4-Uses now a CATTopSplineBody Operator.
    //----------------------------------------------------------------------------
    
    CATMathVector aTangent[nbpts];
    CATLONG32          aImposition[nbpts];
    
    // Imposes the direction of the tangent at the start point.
    aImposition[0]=1;
    aTangent[0].SetCoord(1.,0.,0.);
    
    // no imposition for the intermediate points:
    // the corresponding aTangent values need not to be given
    aImposition[1]=0;
    aImposition[2]=0;
    
    // imposition of the tangent at the ending point.
    aImposition[3]=2;
    aTangent[3].SetCoord(5.,5.,0.);
    //
    // a --------- Creates the operator
    //
    CATTopSplineOperator * pSplineOp = ::CATCreateTopSplineOperator(piGeomFactory,
        &topdata,
        nbpts,
        aPoints,
        aTangent,
        NULL, // no curvature imposition
        aImposition);
    if (NULL==pSplineOp)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    //
    // b---------  Runs the operator
    //
    pSplineOp->Run();
    
    //
    // c --------- Gets the result
    //
    CATBody * piSplineBody2 = pSplineOp->GetResult();
    if (NULL==piSplineBody2)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    // Also gets the computed tangents .
    const CATMathVector *  pComputedTangents=NULL; 
    pSplineOp->GetComputedTangents(pComputedTangents);
    if (NULL==pComputedTangents)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    // Creates topological lines representing the tangents
    CATBody * aTgtBody[nbpts];
    int i = 0;
for (;i <nbpts; i++)
    {
        double length = pComputedTangents[i].Norm();
        aTgtBody[i] = ::CATCreateTopLineFromDirection(piGeomFactory,
            &topdata,
            aPoints[i],
            pComputedTangents[i],
            length);
        if (NULL==aTgtBody[i])
        {
            ::CATCloseCGMContainer(piGeomFactory);
            return (1);
        }
    }
    
    // d ---------  deletes the operator
    //
    delete pSplineOp;
    pSplineOp=NULL;
    
    // Releases the configuration
    pConfig->Release();
    
    //----------------------------------------------------------------------------
    // 5- Computes the length
    //----------------------------------------------------------------------------
    // between two points on the first spline
    CATLengthFromBodyOnWire* pLengthOp= 
        new CATLengthFromBodyOnWire(piGeomFactory,
        &topdata,
        aPoints[1], 
        aPoints[2],
        piSplineBody );
    double l1=0.;
    if (NULL != pLengthOp)
    {
        l1=pLengthOp->GetDistance();
        
        delete pLengthOp;
        pLengthOp = NULL;
    }
    
    // between the same points on the second spline
    pLengthOp =new CATLengthFromBodyOnWire(piGeomFactory,
        &topdata,
        aPoints[1], 
        aPoints[2],
        piSplineBody2 );	
    
    // P2 will contain the 3D mathematical coordinates of the second point 
    CATMathPoint P2;
    double l2=0.;
    if (NULL != pLengthOp)
    {
        l2=pLengthOp->GetDistance(NULL, // the coordinates of the first point are not asked
            &P2); // the coordinates of the second point
        delete pLengthOp;
        pLengthOp = NULL;
    }
    cout << "length 1 = " << l1 <<" , length2  "<< l2 << endl;
    
    //----------------------------------------------------------------------------
    // 6- Delete the unused point bodies and the array
    //----------------------------------------------------------------------------
    
    for (i=0;i <nbpts; i++)
    {
        piGeomFactory->Remove(aPoints[i],CATICGMContainer::RemoveDependancies);
    }
    
    delete [] aPoints;
    aPoints = NULL;
    
    //----------------------------------------------------------------------------
    // 7-Writes the model
    //----------------------------------------------------------------------------
    if(1==toStore)
    {
#ifdef _WINDOWS_SOURCE
        ofstream filetowrite(pFileName, ios::binary ) ;
#else
        ofstream filetowrite(pFileName,ios::out,filebuf::openprot) ;
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


