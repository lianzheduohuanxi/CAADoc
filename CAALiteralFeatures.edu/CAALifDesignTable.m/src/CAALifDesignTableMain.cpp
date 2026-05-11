// COPYRIGHT DASSAULT SYSTEMES  2000

//============================================================================
//  Abstract:
//  ---------
//
//  Batch program which creates a design table (CAALifDesignTableCreate.cpp)
//    and accesses the design table values (CAALifDesignTableAccess.cpp)
//  Illustrates:
//     1 (CAALifDesignTableCreate.cpp)
//     Creating a design table from an external file in txt forma 
//     Adding automatically associations 
//     Adding one-by-one associations
//     Retrieving the list of associations
//     Displaying the current configuration
//     Setting the current configuration
//     2 (CAALifDesignTableAccess.cpp)
//     Creating a design table from an external file in txt format 
//     Adding associations 
//     Displaying the names of the columns
//     Getting the column where a parameter is
//     Retrieving the parameter in a gievn column
//     Retrieving the value in a given cell
//    
//============================================================================
//  Usage:
//  ------
//
//  The design table is an input data of program 
//  Its is delivered in the CAALifDesignTable00.txt file
//  You should use an environment variable (for example ADL_ODT_IN)
//  and assign the path where you have unloaded this txt file to the environment
//  variable.  
//
//============================================================================

#include <CAALifDesignTableAccess.h>
#include <CAALifDesignTableCreate.h>
#include <iostream.h>

// ObjectModelerBase
#include "CATIContainer.h"

// LiteralFeatures  
#include "CATICkeParmFactory.h"
#include "CATCke.h"

#include "CAALifServices.h"
#include "CAALifReturnCodes.h"

int main (int argc, char** argv)
{
    if( argc != 2 )
	return -1;

	//path contains the graphic directory of the runtimeview ...\intel_a(solaris_a)\resources\graphic
	char* path = argv[1];

    
    CAALifServices CAAliteralFeaturesServices;
    
    // Initialize the session
    HRESULT hr = 0;
    int rc = 0;
    CAAliteralFeaturesServices.CAALifInitSession();
    
    
    // Retrieve the parameter factory 
    CATIContainer* piContainer = NULL;		
    hr = CAAliteralFeaturesServices.CAALifCreateInstanceContainer( &piContainer );
    if( FAILED(hr) )                          
        return CAALifKO;
    
    CATICkeParmFactory* piFact = NULL;
    CATCke::Boolean result2 = CATCke::False;   
    CATCke::Boolean result1 = CATCke::False;
    
    if(!!piContainer )
    {
        hr = piContainer -> QueryInterface(IID_CATICkeParmFactory,
            (void**) &piFact);
        piContainer->Release();
        piContainer = NULL;
        
        if (SUCCEEDED(hr)) 
        {
            cout << "QueryInterface for Parameter Factory: OK" << endl << flush;
            
            
            CATICkeParmFactory_var spFact = piFact;
            piFact->Release();
            // Create a design table
            result1 = CAALifDesignTableCreate(spFact, path);
            
            // Access the design table cells
           result2 = CAALifDesignTableAccess(spFact, path);
        }
        else
        {
            rc = CAALifContainerInitFailed;        
        }
    }
    
    CAAliteralFeaturesServices.CAALifCloseSession();
    
    if( result1 == CATCke::False || result2 == CATCke::False)
      return E_FAIL;
    
    return rc;
}


