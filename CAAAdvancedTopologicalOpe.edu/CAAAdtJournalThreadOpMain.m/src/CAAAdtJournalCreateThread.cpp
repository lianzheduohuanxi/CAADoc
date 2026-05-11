/**
* @quickReview CRE 03:01:23
*/

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2002
//
// Sample code for : Geometric Modeler
// Mission         : Explain how to thread a rod. The threading is done
//                   by using the CAAAdtJournalThread operator which is defined in the
//                   CAAAdtJournalThreadUtility.m module 
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Main steps        1- Create the geometry factory 
//                   2- Create the rod to be threaded 
//                   3- Scan the topology and retrieve the surface to be threaded
//                   4- Create the thread by using the CAAAdtThread operator
//                   5- Dump the journal
//                   6- Write the model and close the container  
//
// How to run it   : CAAAdtJournalThreadOpMain  // to run whithout storing the NCGM file
//                   CAAAdtJournalThreadOpMain file.NCGM // to run and store the result 
//                   in file.NCGM     
//=============================================================================

#include <iostream.h>
#include "fstream.h"
// Mathematics
#include "CATMathPoint.h"              // mathematical point
#include "CATMathDirection.h"          // mathematical unitary vector
#include "CATSoftwareConfiguration.h"  // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory 
#include "CATCGMContainerMngt.h"       // Geometry factory management
#include "CATSolidCylinder.h"               // Geometric cylinder
#include "CATCylinder.h"
#include "CATCGMJournalList.h"  

// TopologicalObjects
#include "CATBody.h"                   // body
#include "CATFace.h" 
#include "CATTopData.h"                // TopData of an operator

// CAATopologicalOperators.edu
#include "CAAAdtJournalThreadUtility.h"  
#include "CAAAdtJournalThread.h" 
 
#include "CAACheckForPart.h"

//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (0) or (1) 
         char** iArgv)   // Path to the *.NCGM document that will contain the result of the main.
{
    int rc=0;
    if(4<iArgc) return (1);
    
    char *pFileName = 0;
    char *pFileName1 = 0;
    char *pFileName2 = 0;
    int  toStore = 0;
        
    if( 4 != iArgc ) 
    {
        cout << "one or more output files are missing" << endl;
        return (1);
    }
    else
    {
        toStore = 1; 
        pFileName = iArgv[1];
        pFileName1 = iArgv[2];
        pFileName2 = iArgv[3];
    }
    
    //---------------------------------------------------------------------------
    // 1 - Initialize the factory 
    //---------------------------------------------------------------------------
    
    CATGeoFactory* piGeomFactory = CATCreateCGMContainer() ;
    if (NULL == piGeomFactory)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    //---------------------------------------------------------------------------
    // 2 - Create the rod
    //---------------------------------------------------------------------------
    //
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATCGMJournalList* pJournal = new CATCGMJournalList(pConfig,NULL);
    CATTopData topdata(pConfig, pJournal);
    
    // a - Specify the rod parameters
    //
    double scwBodyRadius = 6.;
    double scwBodyLength = 45.;
    CATMathDirection scwAxis(0.,0.,1.);
    CATMathPoint scwOrigin(0.,0.,0.);
    
    // b - Create the solid cylinder
    // 
    CATSolidCylinder * pCylOperator = ::CATCreateSolidCylinder( 
        piGeomFactory,
        &topdata,
        scwOrigin,                        // first point
        scwOrigin+scwAxis*scwBodyLength,  // second point
        scwBodyRadius);                   // radius
    
    if (NULL==pCylOperator)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    CATBody *piRodBody = pCylOperator->GetResult();
    
    if (NULL==piRodBody)
    {
        cout << "piRodBody NULL " << endl;
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    delete pCylOperator;
    pCylOperator = NULL ;
   
    // ------------------------------------------------------------------------
    // 3 - Scan the topology
    // ------------------------------------------------------------------------
    //
    CATLISTP(CATCell) faceList;
    piRodBody->GetAllCells(faceList, 2);
    
    CATCylinder *piRodCylinder = NULL;
    
    for (int k = 1; k < faceList.Size()+1; k++)
    {
        CATFace *piFace = (CATFace*) (faceList[k]);
        if (NULL == piFace) return (1);
        CATSurface *piSurface = piFace->GetSurface();
        if (piSurface->IsAKindOf(CATCylinder::ClassName()))
            piRodCylinder = (CATCylinder*) piSurface;
    }
 
     // ------------------------------------------------------------------------
    // 4 - Create the journal
    // ------------------------------------------------------------------------
    //
    CATCGMJournalList *pJournal1 = new CATCGMJournalList(pConfig,NULL);
    CATTopData topdata1 (pConfig, pJournal1);
    
    // ------------------------------------------------------------------------
    // 4 - Create the thread by using the CAAAdtThread operator
    // ------------------------------------------------------------------------
    //
    // The distance where the threading is to be started
    // i.e. the non-threaded length
    double scwThreadedLength = 15.;  
                                    
    CAAAdtJournalThread *pThreadOpe = NULL;
    cout << "ope creation" << endl;
    pThreadOpe = new CAAAdtJournalThread (piGeomFactory,  &topdata1,
    piRodBody, piRodCylinder, scwThreadedLength);
    
    if (NULL==pThreadOpe)
    {
        cout << "pThreadOpe NULL" << endl;
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    pThreadOpe->Run();
    CATBody *piThreadedBody = pThreadOpe->GetResult();
    
    if (NULL==piThreadedBody)
    {
        cout << "piThreadedBody NULL" << endl;
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    delete pThreadOpe;
    pThreadOpe = NULL;

    // ------------------------------------------------------------------------
    // 5 - Dump & check the journal
    // ------------------------------------------------------------------------
    //char *pfileName1 = "verdict.html";
    //char *pfileName2 = "moreinformation.html";
    
#ifdef _WINDOWS_SOURCE
    ofstream verdictFile(pFileName1, ios::binary ) ;
    ofstream warningFile(pFileName2, ios::binary ) ;
#else
    ofstream verdictFile(pFileName1,ios::out,filebuf::openprot) ;
    ofstream warningFile(pFileName2,ios::out,filebuf::openprot) ;
#endif
    CATUnicodeString mafeat("MyFeature");
 
    cout << "Start CAACheckForPart" << endl;
    CAACheckForPart * reportCheck = new CAACheckForPart(pJournal1,
        piThreadedBody,
        &mafeat,
        &verdictFile, &warningFile, TRUE);
    reportCheck->CAAAddInputBody(piRodBody, CAATopCheckCopy);
    
    reportCheck->CAACheck();
    delete reportCheck;
    reportCheck = NULL;
    cout << "End CAACheckForPart" << endl;
    
    piGeomFactory->Remove(piRodBody);
    //---------------------------------------------------------------------------
    // 6- Write the model and close the container 
    //---------------------------------------------------------------------------
    if (pJournal!=NULL) delete pJournal;pJournal=NULL;
    if (pJournal1!=NULL) delete pJournal1;pJournal1=NULL;
    pConfig->Release();   // Release the configuration
    if(1==toStore)
    {
#ifdef _WINDOWS_SOURCE
        ofstream filetowrite(pFileName, ios::binary ) ;
#else
        ofstream filetowrite(pFileName,ios::out,filebuf::openprot) ;
#endif
        
        ::CATSaveCGMContainer(piGeomFactory,filetowrite);
        filetowrite.close();
    }	
    
    ::CATCloseCGMContainer(piGeomFactory);
    return (rc);
}

