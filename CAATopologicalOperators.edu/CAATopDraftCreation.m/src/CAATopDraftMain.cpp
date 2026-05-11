
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2008
//                 
// Mission         : Use of CATDynDraft and CATICGMDynAdvancedDraft.
//                   Create a draft on a solid block.
//                   Create an advanced draft on an input body, enabling untwisting.
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Coding steps    : 1- Preliminary declarations
//                   2- Test the CATDynDraft operator
//                   3- Test the CATDynDraft operator with limiting element
//                   4- Test the CATICGMDynAdvancedDraft operator
//                   5- Release  the configuration
//                   6- Write the model
//                   7- Close the application
//
// How to run it   : CAATopDraftCreation inputFile.ncgm outputFile.ncgm     
//=============================================================================
#include <iostream.h>
#include "fstream.h"

// Mathematics
#include "CATSoftwareConfiguration.h"        // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"                   // Geometry factory
#include "CATCGMContainerMngt.h"             // Geometric container

// NewTopologicalObjects
#include "CATTopData.h"                      // Topdata of an operator  

extern int CAATopDraft(CATGeoFactory *iFactory, CATTopData *iTopData);
extern int CAATopDraftLimitingElement(CATGeoFactory *iFactory, CATTopData *iTopData);
extern int CAATopAdvancedDraft(CATGeoFactory *iFactory, CATTopData *iTopData);


//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (2) or (3) 
		 char** iArgv)   // Path to the *.NCGM document containing the input body for advanced draft;
						 // path to the *.NCGM document that will contain the result of the main.
{
	int rc=0;
	if(3 < iArgc && 2 > iArgc) return (1);

	char *pInputFileName = iArgv[1];
	char *pOutputFileName = NULL;
    int  toStore = 0;
	if(3 == iArgc)
	{
		toStore = 1; 
		pOutputFileName = iArgv[2];
	}

    //
    // -----------------------------------------------------------
    // 1 - Preliminary declarations
    // -----------------------------------------------------------
    //
    // (a) Load the container 
    //
	CATGeoFactory* piGeomFactoryExp = NULL;
#ifdef _WINDOWS_SOURCE
    ifstream filetoread(pInputFileName, ios::binary);
#else
    ifstream filetoread(pInputFileName);
#endif
			
	piGeomFactoryExp = CATLoadCGMContainer(filetoread);
	if (NULL == piGeomFactoryExp) return (1);

	CATGeoFactory * piGeomFactory =piGeomFactoryExp->GetImplicitGeoFactory();
	if (NULL == piGeomFactory) return (1);

    //
    // (b) Create the software configuration and topdata 
    //
	CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
	CATTopData topdata(pConfig);

    // --------------------------------------------------------------------------
    // 2 - Test the CATDynDraft operator
    // -------------------------------------------------------------------------- 
    //
	rc += CAATopDraft(piGeomFactory, &topdata);

#ifdef CATIACGMV5R23
    // --------------------------------------------------------------------------
    // 3 - Test the CATDynDraft operator with limiting element
    // -------------------------------------------------------------------------- 
    //
	rc += CAATopDraftLimitingElement(piGeomFactory, &topdata);
#endif

    // --------------------------------------------------------------------------
    // 4 - Test the CATICGMDynAdvancedDraft operator
    // -------------------------------------------------------------------------- 
    //
	rc += CAATopAdvancedDraft(piGeomFactory, &topdata);

    // --------------------------------------------------------------------------
    // 5 - Release  the configuration
    // --------------------------------------------------------------------------
	pConfig->Release();
	pConfig = NULL;

    //---------------------------------------------------------------------------
    // 6 - Write the model
    //---------------------------------------------------------------------------
	if(1==toStore)
	{
#ifdef _WINDOWS_SOURCE
		cout << "file write" << endl;
		ofstream filetowrite(pOutputFileName, ios::binary ) ;
#else
		ofstream filetowrite(pOutputFileName,ios::out,filebuf::openprot) ;
#endif

		::CATSaveCGMContainer(piGeomFactory,filetowrite);
		filetowrite.close();
	}	
	
	// --------------------------------------------------------------------------
	// 7 - Close the application
	// -------------------------------------------------------------------------- 
    ::CATCloseCGMContainer(piGeomFactory);
	piGeomFactory = NULL;

	return (rc);
}
