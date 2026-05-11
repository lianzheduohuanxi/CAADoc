/**
* @quickReview CRE 04:08:11
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2004
//                 
// Sample code for : AdvancedTopologicalOpe
// Mission         : Use of CATTopShellOrientation.
//                   When the faces don't have the same orientation as the shell, the operator
//                   modifies the faces' orientation. The input shell orientation is not modified.
//                   The underlying surfaces orientations are modified (same as faces).
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Coding steps    : 1- Load the container 
//                   2- Retrieve the body to be processed
//                   3- Display the faces orientation with respect to the shell
//                   4- Create the CATTopShellOrientation operator      
//                   5- Display the new faces' orientation.
//                   6- Close the application.
//
// How to run it   : CAATopShellOrienttaion inputFile.ncgm outputFile.ncgm     
//                   The tag specified in this piece of code 
//                   corresponds to the FaceOrientation.ncgm file which is delivered in 
//                   the InputData file.
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
#include "CATFace.h"

// AdvancedTopologicalObjects
#include "CATTopShellOrientation.h"
#include "CATCreateTopShellOrientation.h"
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
    // ---------------------------------------------------------------
    //
    CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
    if (NULL==piGeomFactory) return (1);
    cout << "piGeomFactory "<< endl;  
    
    // ---------------------------------------------------------------
    // (2) - Retrieve the body which contains the faces to be inverted
    // ---------------------------------------------------------------
    //
	CATBody * piBody = NULL;
	CATGeometry * piGeom = NULL;
    for (piGeom = piGeomFactory->Next(NULL);
    piGeom != NULL;
    piGeom = piGeomFactory->Next(piGeom)) 
    { 
        if (piGeom->IsATypeOf(CATBodyType)) 
        {
            piBody = (CATBody *)piGeom;
		}
	}
			
			// ---------------------------------------------------------------
			// (3) - Get the faces' orientation with respect to the shell
			// ---------------------------------------------------------------
			//
			CATLISTP(CATCell) listOfFaces;
			piBody->GetAllCells(listOfFaces,2);
			// Get the Shell
			CATDomain * pShell = piBody->GetDomain(1);
			if ((pShell) && pShell->IsATypeOf(CATShellType)) 
			{
				cout << "Shell OK" << endl;
				for (int i=1; i<=listOfFaces.Size(); i++)
				{
					CATCell * pLocalCell = listOfFaces[i];
					if ( pLocalCell != NULL )
					{
						cout << "Face " << i << " tag " << pLocalCell->GetPersistentTag() << endl;
						cout << "---- " << endl;
						
						// Orientations with respect to the shell
						//
						CATOrientation oOrien =2;   // 2 for unknown
						CATLONG32 rank = pShell->GetCellRank(pLocalCell, &oOrien);
						cout << "Versus the shell (GetCellRank)" << oOrien << endl;
					}
				}       
			}
			
			// ---------------------------------------------------------------
			// (4) - Modify the body so that the faces have all the same orientation
			//       as the shell
			// ---------------------------------------------------------------
			//
			CATTopShellOrientation* ShellOrientationOpe = NULL;
            
			CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
            CATTopData topdata(pConfig, NULL);
			ShellOrientationOpe = CATCreateTopShellOrientation(piGeomFactory, &topdata,
				piBody );
			CATBody * piInvertedBody = NULL;
            if (NULL!=ShellOrientationOpe)
			{
               int result = ShellOrientationOpe->Run();		
               piInvertedBody = ShellOrientationOpe->GetResult();
			   delete ShellOrientationOpe; ShellOrientationOpe=NULL;
			}
            if (pConfig) { pConfig->Release(); pConfig = NULL; }
			if (NULL==piInvertedBody) return (1);
			// ---------------------------------------------------------------
			// (5) - Check that all faces are now oriented like the shell
			// ---------------------------------------------------------------
			//
			CATLISTP(CATCell) newListOfFaces;
			piInvertedBody->GetAllCells(newListOfFaces,2);
			// Get the Shell
			CATDomain * pNewShell = piInvertedBody->GetDomain(1);
			if ((pNewShell) && pNewShell->IsATypeOf(CATShellType)) 
			{
				cout << "new Shell OK" << endl;
				for ( int i=1; i<=newListOfFaces.Size(); i++)
				{
					CATCell * pLocalCell = newListOfFaces[i];
					if ( pLocalCell != NULL )
					{
						cout << "Face " << i << " tag " << pLocalCell->GetPersistentTag() << endl;
						cout << "---- " << endl;
						
						// Orientations with respect to the shell
						//
						CATOrientation oNewOrien =2;   // 2 for unknown
						CATLONG32 rank1 = pNewShell->GetCellRank(pLocalCell, &oNewOrien);
						//  is expected for all faces
						cout << "Versus the shell (GetCellRank)" << oNewOrien << endl;
					}
				}       
			}

    // ----------------------------------------------------------
    // (6) - Close the application
    // ----------------------------------------------------------
    //
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
