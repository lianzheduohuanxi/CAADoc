/**
* @quickReview CRE 04:05:12
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2004
//                 
// Sample code for : TopologicalObjects
// Mission         : Use of CATSmartBodyDuplicator
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Coding steps    : 1 - Preliminary declarations
//                   2 - Retrieve the body from which the hole is to be removed 
//                   3 - Retrieve the holed face and the inner loop of that face
//                   4 - Specify the cell to be modified in the smart
//                       duplication operation
//                   5 - Create a smart duplicator in order to modify  
//                       the topology
//                   6 - Retrieve the duplicated face associated with the holed face
//                   7 - Scan the domains within the duplicated face    
//                       and remove the internal loop
//                   8 - Close the application
//
// How to run it   : CAATopSmartDuplicator  inputFile.ncgm  outputFile.ncgm 
//                   inputfile to be used is partwithhole.ncgm 
//                   partwithhole.ncgm is provided in the 
//                   FunctionTests/InputData folder
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
#include "CATDomain.h"
#include "CATCell.h" 
#include "CATTopData.h"                // TopData of an operator
#include "CATLoop.h"

// NewTopologicalObjects
#include "CATSmartBodyDuplicator.h"

// Error management
#include "CATError.h"              // errors
#include "CATErrorMacros.h"        // to catch errors 
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
    CATTopData topdata(pConfig, NULL);
    //
    // -----------------------------------------------------------
    // 2 - Retrieve the body the hole is to be removed from
    // -----------------------------------------------------------
    //
    CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(10990); 
    if (piCGMObj1 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATBody * piBody= (CATBody *) piCGMObj1;
    //
    // -----------------------------------------------------------
    // 3 - Retrieve the holed face and the inner loop of that face
    // -----------------------------------------------------------
    //
    CATLISTP(CATCell) faceList;
    piBody->GetAllCells(faceList,2);
    CATDomain* pInnerLoop=NULL;
    CATFace * holedFace = NULL;
    for (int k = 1; k < faceList.Size()+1; k++)
    {
		CATCell * pLocalCell = faceList[k];
        if (pLocalCell && pLocalCell->GetNbInternalDomains() > 0)
        {       
            int NbDomains=pLocalCell->GetNbDomains();
            for(int j=1;j<=NbDomains;j++)
            {
                CATDomain *pDomain=pLocalCell->GetDomain(j);
                CATLocation Location=pDomain->GetLocation();
                if(Location==CATLocationInner)
                {
                    pInnerLoop=pDomain;                    // the inner loop 
                    holedFace = (CATFace *) faceList[k] ;  // the holed face
                    break; 
                }
            }
        }
    } 
    //  Just for checking
    if ((pInnerLoop == NULL) || (holedFace == NULL)) return (1); 
        
    cout << "the  holed face " << holedFace->GetPersistentTag() << endl;
    cout << "the inner loop " << pInnerLoop->GetPersistentTag() << endl;
   
    // -----------------------------------------------------------
    // 4 - Specify the cell to be modified in the smart
    //     duplication operation
    // -----------------------------------------------------------
    //
    holedFace->Touch(piBody);
    // 
    // ------------------------------------------------------------
    // 5 - Create a smart duplicator in order to modify  
    //     the topology
    // ------------------------------------------------------------
    //
    int NbLoops = holedFace->GetNbDomains();
    cout << "Create the smart duplicator" << endl;
    CATBody * copBody = piGeomFactory->CreateBody();
    CATSmartBodyDuplicator * smartDuplicator = 
        copBody->CreateSmartDuplicator(piBody, topdata);
    if (smartDuplicator == NULL) return (1); 
    smartDuplicator->Run();

    cout << " Smart duplicated body " << copBody->GetPersistentTag() << endl;

    // ------------------------------------------------------------
    // 6 - Retrieve the duplicated face associated with the holed face
    // ------------------------------------------------------------
    //
    CATFace * duplicatedFace = (CATFace *)smartDuplicator->GetDuplicatedCell(holedFace);
    if (duplicatedFace == NULL) return (1); 
    //
    // ------------------------------------------------------------
    // 7 - Scan the domains within the duplicated face    
    //     and remove the internal loop
    // ------------------------------------------------------------
    int NbD=duplicatedFace->GetNbDomains();
    for(int j=1;j<=NbD;j++)
    {
        CATDomain *pDom=duplicatedFace->GetDomain(j);
        CATLocation Loc=pDom->GetLocation();
        if(Loc==CATLocationInner)
        {
           duplicatedFace->RemoveDomain(pDom);
        }
    }
	
    CATTry   
    {
        copBody->Completed(TRUE);
    }
    CATCatch(CATError,error)
    { 
        cout << (error->GetNLSMessage()).ConvertToChar()<<endl;
        rc=1;
    }
    CATEndTry;
	
	if (smartDuplicator)
		delete smartDuplicator;
	smartDuplicator = NULL;

 
    // ----------------------------------------------------------
    // 8 - Close the application
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
