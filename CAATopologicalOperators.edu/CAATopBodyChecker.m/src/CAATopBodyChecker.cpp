/**
* @quickReview CRE 04:05:18
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2004
//                 
// Sample code for : TopologicalOperators
// Mission         : Use of Body Checker to detect small curvature radii.
//                   
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Coding steps    : 1 - Preliminary declarations
//                   2 - Get the body to be checked
//                   3 - Create and use the body checker
//                   4 - Close the application
//
// How to run it   : CAATopBodyChecker  inputFile.ncgm  
//                   inputfile to be used is bodyChecker1.ncgm which is delivered in
//                   CAATopologicalOperators.edu/FunctionsTests/InputData
//
//=============================================================================
#include <iostream.h>
#include "fstream.h"

// Mathematics
#include "CATSoftwareConfiguration.h"  // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory 
#include "CATCGMContainerMngt.h"       // Geometry factory management
                
// TopologicalObjects
#include "CATBody.h"                   // body

#include "CATTopData.h"                // TopData of an operator
#include "CATBodyChecker.h"
//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (3) 
         char** iArgv)   
{
    int rc=0;
    if(2<iArgc) return (1);
    
    
    char *pFileName = NULL;
    if( 2 != iArgc ) 
    {
        cout << "one .ncgm file is missing" << endl;
        return (1);
    }
    else
    {
        pFileName = iArgv[1];
    }
    
    
#ifdef _WINDOWS_SOURCE
    ifstream filetoread(pFileName, ios::binary ) ;
#else
    ifstream filetoread(pFileName) ;
#endif
    //
    // -----------------------------------------------------------
    // 1 - Preliminary declarations
    // -----------------------------------------------------------
    //
    // (a) Loads the container 
    //
    CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
    if (NULL==piGeomFactory) return (1);
    //
    // (b) Configuration management
    //
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
	//
    // (c) - Create the default journal

    CATTopData topdata(pConfig, NULL);
   
	//
    // -----------------------------------------------------------
    // 2 - Retrieve the body to be checked
    // -----------------------------------------------------------
    //
    CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(2353356); 
    if (piCGMObj1 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATBody * piBodyToBeChecked= (CATBody *) piCGMObj1;


    // -----------------------------------------------------------
    // 3 - Create and use the body checker object
    // -----------------------------------------------------------
    //
    // a - Create the checker
	CATBodyChecker *  pBodyChecker = CATBodyChecker::Create(piGeomFactory, &topdata, piBodyToBeChecked);
	//
	// b - Specify the Full Mode
	if (NULL != pBodyChecker)
	{
		CATBodyChecker::CheckMode eChkMode = CATBodyChecker::BodyChkModeFull;
		pBodyChecker->SetCheckMode(eChkMode);
		//
		// c - Run the operator
		CATBoolean bRet = FALSE;
		bRet = pBodyChecker->Run();
		//
		// d - Display the diagnosis
		CATLONG32 nNbDiagnosis = -1;
		nNbDiagnosis = pBodyChecker->GetNbDiagnoses();
		
		pBodyChecker->BeginningDiagnosis();
		while( pBodyChecker->NextDiagnosis() )
		{
			CATUnicodeString strDiagnosis;
			pBodyChecker->GetDiagnosis(strDiagnosis);
			
			cout << strDiagnosis.ConvertToChar() << endl;
		}
		
		CATBodyChecker::Remove(pBodyChecker);
	}

    // ----------------------------------------------------------
    // 4 - Close the application
    // ----------------------------------------------------------
    //
	pConfig->Release();
	pConfig = NULL;
	
    filetoread.close();
    CATCloseCGMContainer(piGeomFactory);
    return rc;
    }
