/**
* @quickReview CRE 04:03:18
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2003
//
// Sample code for : Geometric Modeler
// Mission         : Creation and use of CATHybBoundary
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
//                      the boundary.ncgm input file
//                   and scans the geometry to retrieve the data to be passed as the arguments 
//                      of the creation function.
//                   2- Create the CATHybBoundary operator - run it and get the result
//                   3- Display the journal (optional - to illustrate the keep order)
//                   4- Close the application
//
// How to run it   : CAATopBoundaryCreation fileToBeRead.NCGM outputFile.NCGM  
//                   Both arguments are to be specified in the command   
//                   The first argument should be boundary.NCGM 
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

// TopologicalOperators
#include "CATHybBoundary.h"             // The operator to create a boundary 
#include "CATCreateTopBoundary.h"

#include "CATCGMJournalList.h"  

// TopologicalObjects
#include "CATBody.h"                   // body
#include "CATFace.h" 
#include "CATTopData.h"                // TopData of an operator

// CAATopologicalOperators.edu
//#include "CAACheckForPart.h"
#include "CAADumpJournal.h"

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
    // 1 - Load the ncgm input file (boundary.ncgm)
    //     and retrieve the input data 
    // ------------------------------------------------------
    //
    CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
    if (NULL==piGeomFactory) return (1);
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATCGMJournalList* pJournal = new CATCGMJournalList(pConfig,NULL);
    CATTopData topdata(pConfig, pJournal);

    // Retrieve the body
    //
    CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(9048);
    if (piCGMObj1 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATBody * piInputBody = (CATBody *) piCGMObj1;

    // Retrieve an initial cell
    //
    CATICGMObject * piCGMObj2 = piGeomFactory->FindObjectFromTag(3595);
    if (piCGMObj2 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    
    CATCell * piEdge = (CATCell *) piCGMObj2;

    // Retrieve a domain
    //
    CATICGMObject * piCGMObj3 = piGeomFactory->FindObjectFromTag(9069);
    if (piCGMObj3 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATDomain * piDomain = (CATDomain *) piCGMObj3;

    // -------------------------------------------------------------
    // 2 - Create the CATHybBoundary operator
    // -------------------------------------------------------------
    //
    
    /*  
    // Case 1
    // ------
    // Outer loop is generated.
    // On the domain of CATShell type which is specified, 
    // the loop which contains the specified edge makes up
    // the boundary. 
    // The other loop (i.e. the internal loop) is not part 
    // of the boundary because the point continuity has been
    // specified.
    CATHybBoundary * pBoundOpe =::CATCreateTopBoundary(piGeomFactory,
    &topdata, 
    piInputBody,
    piDomain, // the domain
    piEdge, // the initial cell
    POINT_CONTINUITY);
    */

    /* 
    // Case 2
    // ------
    // The two loops of the CATShell are generated as boundaries
    // because there are no restrictions on continuity.
    //
    CATHybBoundary * pBoundOpe =::CATCreateTopBoundary(piGeomFactory,
    &topdata, 
    piInputBody,
    piDomain, // the domain
    piEdge, // the initial cell
    NO_CONTINUITY);
    */

     
    // Case 3
    // ------
    // The generated boundary is made up of a single edge
    // because the continuity in tangent has been specified
    //
    CATHybBoundary * pBoundOpe =::CATCreateTopBoundary(piGeomFactory,
        &topdata, 
        piInputBody,
        piDomain, // the domain
        piEdge, // the initial cell
        TANGENT_CONTINUITY);
    if (NULL==pBoundOpe)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }

    pBoundOpe->Run();
    CATBody * piBoundaryBody = pBoundOpe->GetResult();
    pJournal->Tass();
    CAATopDumpJournal(pJournal);
    

    // -------------------------------------------------------------
    // 3 - Optional - display the journal
    // -------------------------------------------------------------

    /*
    char *pFileName3 = "verdict.html";
    char *pFileName4 = "moreinformation.html";
    
#ifdef _WINDOWS_SOURCE
    ofstream verdictFile(pFileName3, ios::binary ) ;
    ofstream warningFile(pFileName4, ios::binary ) ;
#else
    ofstream verdictFile(pFileName3,ios::out,filebuf::openprot) ;
    ofstream warningFile(pFileName4,ios::out,filebuf::openprot) ;
#endif
    CATUnicodeString mafeat("MyFeature");
 
    cout << "Start CAACheckForPart" << endl;
    CAACheckForPart * reportCheck = new CAACheckForPart(pJournal,
        piBoundaryBody,
        &mafeat,
        &verdictFile, &warningFile, TRUE);
    reportCheck->CAAAddInputBody(piInputBody, CAATopCheckNoCopy);
    
    reportCheck->CAACheck();
    delete reportCheck;
    reportCheck = NULL;
    cout << "End CAACheckForPart" << endl;
    */
    delete pBoundOpe; 
    pBoundOpe = NULL;
    delete pJournal; pJournal=NULL;
    // ----------------------------------------------------------
    // 4 - Close the application
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
