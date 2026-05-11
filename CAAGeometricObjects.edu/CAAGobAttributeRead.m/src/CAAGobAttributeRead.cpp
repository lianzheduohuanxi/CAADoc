/**
* @quickReview CRE 04:12:02
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2001
//
// Sample code for : Geometric Modeler
// Mission         : Creation and use of attributes (CATCGMAttribute)
//                    
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (in this case, the file is not saved)
//                   0- OK
//                   1- Null pointer detection 
//                      or bad number of arguments when running the command
//                  
//                   
// Coding steps    : 
//                   1- Load the .ncgm file to be read 
//                   2- Scans the geometry to retrieve the value of 
//                      the CAAGobAttributeManagement attribute 
//                      on a given type of objects
//                   3- Closing operations
//
//
// How to run it   : CAAGobAttributeRead file.NCGM (file .NCGM is required)   
//                                                 
//=============================================================================

#include <fstream.h>                     // C++ file streaming
#include "CAAGobAttributeManagement.h"   // the class defining the attribute

// GeometricObjects
#include "CATCGMContainerMngt.h"         // Management of the geometry factory
#include "CATGeoFactory.h"               // Geometry factory      
#include "CATGeometry.h"                 // Base class for geometric objects

/** @c++ansi mcf 2004-10-08.12:03:56 [include iostream.h for cout declaration] **/
#include "iostream.h"

//------------------------------------------------------------------------------
int main(int    iArgc,   // Number of arguments (1) 
         char** iArgv)   // Path to the *.NCGM document to be read.
{
	int rc=0;
	char *pFileName = NULL;
	if( 2 != iArgc ) 
	{
		cout << "You must specify the .ncgm file to be read" << endl;
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
	
		
    //-----------------------------------------------------------------------------
	// 1 - Load the file specified in the command argument
	//-----------------------------------------------------------------------------
	//
	CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
	
	//-----------------------------------------------------------------------------
	// 2 - Scan the geometry and retrieve the CAAGobAttributeManagement 
	//     attribute value for each PLine object
	//-----------------------------------------------------------------------------
	//
	// (a) --- Initialize variables
	//
	cout << "-----------------------------------" << endl;
	cout << "Reading the attribute on Plines ..." << endl;
	cout << "Scanning the geometry...  " << endl; 
	CATGeometry * piCurG = NULL;

	CATULONG32  curtag;

	// (b) --- Loop through the geometry
	//
    if (NULL==piGeomFactory) 
	{
		return (1);
	}
	else
	{
	for (piCurG = piGeomFactory->Next(NULL,CATPLineType);
	piCurG != NULL;
	piCurG = piGeomFactory->Next(piCurG)) 
	{
		// Find the PLine from its persistent tag
		//
		curtag = piCurG->GetPersistentTag();
        CATICGMObject * piCGMObj = piGeomFactory->FindObjectFromTag(curtag);
		
		if (piCGMObj == NULL)
		{
			cout << "No object with the specified tag" <<endl;
			return 1;
		}
		
		// Retrieve the CATCGMAttribute from its identifier
		//
		CATCGMAttribute * piActAttr = piCGMObj->
			GetAttribute(UAIDPtr(CAAGobAttributeManagement));

		// No searched attribute found on the PLine 
		//
		if (NULL == piActAttr)
		{
			cout << "------------------------------------------------- " << endl;
			cout << "PLine with no CAAGobAttributeManagement attribute " << endl;
		}

		// The searched attribute found on the Pline
		//
		else
		{
			cout << "------------------------------------------------- " << endl;
			cout << "PLine with CAAGobAttributeManagement attribute    " << endl; 
		
			CAAGobAttributeManagement * iPersAttr = NULL;
			iPersAttr = (CAAGobAttributeManagement *) piActAttr;

			    // Retrieve the attribute value 
			    // See the CAAAttributeManagement module
			    // 
				if (iPersAttr)
				{
					CATLONG32 oPersval;
					iPersAttr->GetValue(oPersval);

				}
				else return 1;
				cout << "------------------------------------------------- " << endl;		
		}
	}
	}
	
	//-----------------------------------------------------------------------------
	// 3 - Close the input file and the CGM container
	//-----------------------------------------------------------------------------
	//
	filetoread.close();
	CATCloseCGMContainer(piGeomFactory);
	
	return 0;
}


//automate:26/09/01:suppression include de CATPLine.h
//automate:26/09/01:suppression include de CATICGMContainer.h
