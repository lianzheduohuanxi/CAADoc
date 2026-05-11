/**
* @quickReview CRE 04:03:11
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2006
//                 
// Sample code for : TopologicalOperators
// Mission         : Use of CATHybIntersect
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Coding steps    : 1- Load the container - create the topdata - retrieve the input bodies
//                   2- Creates the intersection operator - retrieve the result
//                   3- Close the application.
//
// How to run it   : CAATopIntersectShellShell inputFile.ncgm outputFile.ncgm     
//                   The tag specified in this piece of code 
//                   corresponds to the intersectShellShell.ncgm file which is delivered in 
//                   the InputData file.
//=============================================================================

#include <iostream.h>
#include "fstream.h"

// Mathematics
#include "CATSoftwareConfiguration.h"  // Configuration of the operator
#include "CATMathDirection.h"

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory 
#include "CATCGMContainerMngt.h"       // Geometry factory management                

// TopologicalObjects
#include "CATBody.h"                   // body
#include "CATFace.h"

// TopologicalOperator
#include "CATHybIntersect.h"
#include "CATCreateTopIntersect.h"
#include "CATTopData.h"
#include "CATCGMJournalList.h"
#include "CATSoftwareConfiguration.h"
#include "CATICGMObject.h"

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
    // ---------------------------------------------------------------
    // (1) - Preliminary operations
    //           (a) - load the container (FaceOrientation.ncgm in InputData)
    //           (b) - create the topdata
	//           (c) - retrieve the two input shells
    // ---------------------------------------------------------------
    //
    CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
    if (NULL==piGeomFactory) return (1);
    cout << "piGeomFactory "<< endl;  
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig, NULL);
	
	//first shell
	CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(667827); //first shell
    if (piCGMObj1 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATBody * pBody1= (CATBody *) piCGMObj1;

    //second shell
	CATICGMObject * piCGMObj2 = piGeomFactory->FindObjectFromTag(668637); // curve
    if (piCGMObj2 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATBody * pBody2= (CATBody *) piCGMObj2;

    // ---------------------------------------------------------------
    // (2) - Create the CATHybIntersect
    // ---------------------------------------------------------------
    //
    CATHybIntersect *pIntersectOpe = NULL;
	CATBody *CurrentBody = NULL;
	
	pIntersectOpe = CATCreateTopIntersect(piGeomFactory, &topdata, pBody1, pBody2);
	if(pIntersectOpe )
	{
		pIntersectOpe -> Run();
		CurrentBody = pIntersectOpe -> GetResult ();	
		delete pIntersectOpe; pIntersectOpe=NULL;
	}
    // ----------------------------------------------------------
    // (3) - Close the application
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
