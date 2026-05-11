/**
* @quickReview CRE 04:06:17
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2004
//                 
// Sample code for : AdvancedTopologicalOpe
// Mission         : TOLERANT MODELING
//                   Use of the smoothing options of the CATFrFTopologicalSweep operator
//                   Code to be used to create a segment sweep with one guide and 
//                   one reference surface.
//                   Explains how to use the smooth options.
//                   The effects of smooth options are explained in the
//                   CAAAdtSweepSmoothing.htm article of the CAAAdvancedTopoOpeDoc.edu
//                   framework.
//                   
//                   
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Coding steps    : 1- Load the container 
//                   2- Create the CATFrFTopologicalSweep operator
//                     (a) - Specify the guide
//                     (b) - Create the operator
//                     (c) - Create the length laws
//                     (d) - Create the angle law
//                     (e) - Specify the length and angle laws
//                     (f) - Specify the reference surface
//                     (g) - Specify the smoothing options (four set of data)
//                     (h) - Run the operator and get the result
//                   3- Close the application
//
// How to run it   : CAATopSweepSmoothing inputFile.ncgm outputFile.ncgm     
//                   The tags specified in this piece of code 
//                   correspond to the TolerantSweepInit.ncgm file which is delivered in 
//                   the InputData file. 
// ======================================================================================== 
#include <iostream.h>
#include "fstream.h"

// Mathematics
#include "CATSoftwareConfiguration.h"  // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory 
#include "CATCGMContainerMngt.h"       // Geometry factory management                
#include "CATConstantLaw.h"
#include "CATCompositeLaw.h" 

// NewTopologicalObjects
#include "CATTopData.h"                // TopData of an operator
#include "CATBody.h" 

// AdvancedTopologicalOpe
#include "CreateFrFTopologicalSweep.h"
#include "CATFrFTopologicalSweep.h"

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
    // 1 - Load the ncgm input file (TolerantSweepInit.ncgm)
    //     and retrieve the input data 
    // ------------------------------------------------------
    //
    CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
    if (NULL==piGeomFactory) return (1);
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig, NULL);
    
    /* the guide */
    //
    CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(25126); 
    
    if (piCGMObj1 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATBody * piInputBody = (CATBody *) piCGMObj1;
    
    
    /*  the reference surface  */
    // 
    CATICGMObject * piCGMObj2 = piGeomFactory->FindObjectFromTag(24934); 
    if (piCGMObj2 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    //
    CATGeometry * piReferenceSurface = (CATGeometry *)  piCGMObj2;
    
    // ------------------------------------------------------
    // 2 - Create the CATFrFTopologicalSweep operator,
    //     run it and get the result
    // ------------------------------------------------------
    
    // (a) - Define the list of guides (a single guide list in this case)
    //
    CATLISTP(CATGeometry) guides;
    guides.Append(piInputBody);
    
    // (b) - Create the sweep operator
    //
    CATFrFTopologicalSweep * sweepOpe =::CATCreateFrFTopologicalSegmentSweep(piGeomFactory, 
        &topdata, &guides);
    if (NULL==sweepOpe)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    // (c) - Create the length laws
    //
    CATLaw * lengthLaws[2] = {NULL, NULL};
    CATConstantLaw * LengthLaw1 = piGeomFactory -> CreateConstantLaw(0, 1, 40.0);
    CATConstantLaw * LengthLaw2 = piGeomFactory -> CreateConstantLaw(0, 1, 5.0);
    lengthLaws[0] = LengthLaw1;
    lengthLaws[1] = LengthLaw2;
    
    // (d) - Create the angle law
    //
    CATConstantLaw * AngleLaw1  = piGeomFactory -> CreateConstantLaw(0, 1, 45);
    
    // (e) - Specify the length and angle laws
    //
    sweepOpe -> SetLengthLaws( lengthLaws, 2);
    sweepOpe -> SetAngularLaw( AngleLaw1);
    
    // (f) - Specify the reference surface
    //
    sweepOpe-> SetReferenceElement(piReferenceSurface);
    
    // (g) - Specify the Smooth Options
    // 
    // ---------------------------------
    // Specification 1:
    // Angular correction not activated
    // Deviation from guide 0.03mm
    // ---------------------------------
    /*
    sweepOpe -> SetSmoothOption (0);   // no angular correction
    double iCleanMaxDeformation=0.03;
    sweepOpe -> SetCleanGuidesOption(1, &iCleanMaxDeformation, NULL, NULL);
    */
    
    // ---------------------------------
    // Specification 2
    // Angular correction 0.5deg
    // Deviation from guide 0.03mm
    // ---------------------------------
    sweepOpe -> SetSmoothOption (1);   // angular correction
    double AngleTol = 0.5 ;// in degrees
    double RadianAngleTol = AngleTol*CATDegreeToRadian; 
    sweepOpe -> SetSmoothAngleThreshold(RadianAngleTol);
    double iCleanMaxDeformation=0.03;
    sweepOpe -> SetCleanGuidesOption(1, &iCleanMaxDeformation, NULL, NULL);
    
    // ---------------------------------
    // Specification 3
    // Angular correction 2deg
    // Deviation from guide 1mm
    // ---------------------------------
    /*
    sweepOpe -> SetSmoothOption (1);   // angular correction
    double AngleTol = 2 ;// in degrees
    double RadianAngleTol = AngleTol*CATDegreeToRadian; 
    sweepOpe -> SetSmoothAngleThreshold(RadianAngleTol);
    double iCleanMaxDeformation=1;
    sweepOpe -> SetCleanGuidesOption(1, &iCleanMaxDeformation, NULL, NULL);
    */
    
    // ---------------------------------
    // Specification 4
    // Angular correction not activated
    // Deviation from guide not activated
    // ---------------------------------
    /*
    // THROW IS GENERATED
    */
    // (h) - Run the operator and get the result
    //
    sweepOpe -> Run();
    CATBody * pBodySweepCircle  = sweepOpe->GetResult();  
    
    delete sweepOpe; 
    sweepOpe = NULL;
    
    // ----------------------------------------------------------
    // 3 - Close the application
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
