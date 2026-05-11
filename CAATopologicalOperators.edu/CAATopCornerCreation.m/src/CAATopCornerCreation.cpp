/**
* @quickReview CRE 04:03:18
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2003
//
// Sample code for : Geometric Modeler
// Mission         : Creation and use of CATTopCorner
//                    
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (in this case, the file is not saved)
//                   0- OK
//                   1- Null pointer detection 
//                      or bad number of arguments when running the command
//                            
// Coding steps    : 
//                   1- Load the .ncgm file to be read (this use case is explanatory if you read 
//                      the ToBeCornered.ncgm input file
//                   and scans the geometry to retrieve the data to be passed as the arguments 
//                      of the CATTopCorner operator
//                   2- Create the CATTopCorner operator
//                   3- Set the parameters and run the operator
//                   4- Scan the resulting corners and display the centers.
//                   5- Close the application
//
// How to run it   : CAATopCorner fileToBeRead.NCGM outputFile.NCGM  
//                   Both arguments are to be specified in the command   
//                   The first argument should be ToBeCornered.NCGM 
//                                                 
//=============================================================================

#include <iostream.h>
#include "fstream.h"

// Mathematics
#include "CATMathPoint.h"
#include "CATSoftwareConfiguration.h"  // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory 
#include "CATCGMContainerMngt.h"       // Geometry factory management

// NewTopologicalObjects
#include "CATBody.h"                   

// TopologicalOperators
#include "CATTopCorner.h"             // The operator to create a corner between
// two wires

//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (3) 
         char** iArgv)   
{
    int rc=0;
    if(3<iArgc) return (1);
    
    char *pFileName1 = 0;
    int  toStore = 0;
    
    
    char *pFileName = NULL;
    if( 3 != iArgc ) 
    {
        cout << "one .ncgm file is missing" << endl;
        return (1);
    }
    else
    {
        toStore = 1; 
        pFileName = iArgv[1];
        pFileName1 = iArgv[2];
    }
    
    
#ifdef _WINDOWS_SOURCE
    ifstream filetoread(pFileName, ios::binary ) ;
#else
    ifstream filetoread(pFileName) ;
#endif
    
    // ------------------------------------------------------
    // 1 - Load the ncgm input file (ToBeCornered.ncgm)
    //     and retrieve the input data 
    // ------------------------------------------------------
    //
    CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
    if (NULL==piGeomFactory) return (1);
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig, NULL);
    
    //
    // (a) The first curve (inner curve)
    //
    CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(252);
    if (piCGMObj1 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATBody * piCurve1 = (CATBody *) piCGMObj1;
    //
    // (b) The second curve (bording edge)
    // 
    CATICGMObject * piCGMObj2 = piGeomFactory->FindObjectFromTag(2855);
    if (piCGMObj2 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    
    CATCell * piEdge = (CATCell *) piCGMObj2;
    CATBody * piCurve2 =  piGeomFactory->CreateBody();
    CATDomain *pWireDomain = piCurve2->CreateDomain(1); 
    pWireDomain->AddCell(piEdge);
    piCurve2->AddDomain(pWireDomain);
    //
    // (c) The support
    //
    CATICGMObject * piCGMObj3 = piGeomFactory->FindObjectFromTag(2836);
    if (piCGMObj3 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATBody * piSupport = (CATBody *) piCGMObj3;
    
    // ----------------------------------------------------------
    // 2 - Creation of the CATTopCorner operator 
    // ----------------------------------------------------------
    //
    CATTopCorner* pCornerOpe = ::CATCreateTopCorner(piGeomFactory, 
        &topdata, 
        piCurve1,  // inner wire
        piCurve2,  // bording wire
        piSupport, // supporting shell 
        11.0) ;	  
    
    if (NULL==pCornerOpe) return 1;
    
    // ----------------------------------------------------------
    // 3 - Set the parameters & run the operator
    // ----------------------------------------------------------
    // 
    // a) All corners are created (i.e. two corners)
    //
    pCornerOpe -> SetOffsetOrientation(0,0); 
    //
    // b) No corner created with this option
    //
    //    pCornerOpe -> SetOffsetOrientation(1,1);  
    //
    // c) No corner created with this option
    //
    //    pCornerOpe -> SetOffsetOrientation(-1,1);
    //
    // d) One corner created with this option
    //
    //    pCornerOpe -> SetOffsetOrientation(-1,-1); 
    //
    // e) One corner created with this option
    //
    //    pCornerOpe -> SetOffsetOrientation(1,-1);
    
    int ResultTrimmingMode1 = pCornerOpe -> SetCircleMode(Direct); // shortest portion kept
    int ResultTrimmingMode2 = pCornerOpe -> SetSupportTrimmingSideAndMode(0,0); // no merge
    
    pCornerOpe->Run();
    
    // ----------------------------------------------------------
    // 4 - Scan the corners
    // ----------------------------------------------------------
    //
    CATBody *piCornerBody = pCornerOpe->GetResult();     
    CATLONG32 nbOfCorners = pCornerOpe->GetNumberOfCorners( ) ;
    cout << "Number of corners: " << nbOfCorners << endl;
    pCornerOpe -> BeginningCorner();
    // 
    // Create a cartesian point at each corner center
    // and display the radius
    //
    while (pCornerOpe -> NextCorner())
    {
        CATBody * pCurrentBody = pCornerOpe ->GetCorner(NULL);
        CATMathPoint oCornerCenter;
        double oRadius = 0;
        pCornerOpe->GetCenterRadius(oCornerCenter, oRadius);
        CATCartesianPoint * pCartPoint = 
            piGeomFactory->CreateCartesianPoint(oCornerCenter.GetX(),
            oCornerCenter.GetY(),
            oCornerCenter.GetZ() );
        cout << "Radius " << oRadius << endl;
        
    }
    
    delete pCornerOpe;
    pCornerOpe = NULL;
    
    // ----------------------------------------------------------
    // 5 - Close the application
    // ----------------------------------------------------------
    //
	pConfig->Release();
    if(1==toStore)
    {
        cout << "Writing the model" << endl;
#ifdef _WINDOWS_SOURCE
        ofstream filetowrite(pFileName1, ios::binary ) ;
#else
        ofstream filetowrite(pFileName1,ios::out,filebuf::openprot) ;
#endif
        
        ::CATSaveCGMContainer(piGeomFactory,filetowrite);
        filetowrite.close();
    }	
    filetoread.close();
    CATCloseCGMContainer(piGeomFactory);
    return rc;
    }
