/**
* @quickReview CRE 03:11:18
*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2003
//
// Sample code for : Geometric Modeler - Topological Journal
// Mission         : Illustrates the checking of the naming rules
//                   One journal order is ignored but the journal is OK
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Main steps        1- Preliminary operations
//                   2- Create the input cubes
//                   3- Apply the boolean operation
//                   4- Create the new journal
//                   5- Dump the new journal and check it
//                   6- Write the model and close the container  
//
// How to run it   : CAATopCheckGnOK  file.ncgm file1.html file2.html  
//=======================================================================================

#include <iostream.h>
#include <iomanip.h>
#include "fstream.h"

// Mathematics
#include "CATMathPoint.h"                // Math axis creation
#include "CATSoftwareConfiguration.h"

// GeometricObjects
#include "CATGeoFactory.h"               // Geometry factory
#include "CATCGMContainerMngt.h"         // Management of the geometry factory
#include "CATCGMJournalList.h"           // Journal
#include "CATCGMJournalInfo.h"           // Journal info

// NewTopologicalObjects
#include "CATBody.h"
#include "CATCell.h"
#include "CATFace.h"

// TopologicalOperators
#include "CATDynBoolean.h"             // To intersect the cubes
#include "CATSolidCuboid.h"

#include "CAACheckForPart.h"           // Journal checker
#include "CAADumpJournal.h"            // To dump the jourmal

// ---------------------------------------------------------------------------
int main(int    iArgc,   // Number of arguments (3) 
         char** iArgv)   // Path to the *.NCGM document that will contain the result of the main.
{
    int rc=0;
    if(4<iArgc) return (1);
    
    char *pFileName = 0;   // Path to the *.NCGM document that will contain the result of the main.
    char *pFileName1 = 0;  // Verdict file
    char *pFileName2 = 0;  // Detail file
    int  toStore = 0;
    
    if( 4 != iArgc ) 
    {
        cout << "One or more output files are missing" << endl;
        return (1);
    }
    else
    {
        toStore = 1; 
        pFileName = iArgv[1];
        pFileName1 = iArgv[2];
        pFileName2 = iArgv[3];
    }
    
    //----------------------------------------------------------------------------
    // 1 - Preliminary operations
    //----------------------------------------------------------------------------
    //
    // (a) - Create the geometry factory
    CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer() ;
    if (NULL==piGeomFactory) return (1);
    // (b) - Create the software configuration
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    // (c) - Create the default journal
    CATCGMJournalList* pJournal = new CATCGMJournalList(pConfig,NULL);
    CATTopData topdata(pConfig, pJournal);
    // (d) - Create the new journal journal to validate naming/dimension rule
    CATCGMJournalList* pJournalNew = new CATCGMJournalList(pConfig,NULL);
    
    //----------------------------------------------------------------------------
    // 2 - Create the cubes
    //     First cube 200mm each side
    //     Second cube 100mm each side
    //----------------------------------------------------------------------------
    //
    // Creating the math points
    //
    CATMathPoint *P = new CATMathPoint[8];
    // for cube 1
    P[0].SetCoord( 0.,0.,0.);
    P[1].SetCoord( 200.,0.,0.);
    P[2].SetCoord(  0.,200.,0.);
    P[3].SetCoord(  0.,0.,200.);
    P[4].SetCoord( 50.,50.,199);
    P[5].SetCoord( 150.,50.,199);
    P[6].SetCoord(  50.,150.,199);
    P[7].SetCoord(  50.,50.,299.5);
    
    // First cube
    //
    CATSolidCuboid * pSolidCubl = CATCreateSolidCuboid(piGeomFactory, 
        &topdata,
        P[0],
        P[1],
        P[2],
        P[3]);
    
    if (NULL==pSolidCubl)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    pSolidCubl->Run();
    
    CATBody * pBody1 = pSolidCubl->GetResult();
    if (NULL==pBody1)
    {
        cout << "Problem when creating pBody1 " << endl;
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    // Second cube 
    //
    CATSolidCuboid * pSolidCub2 = CATCreateSolidCuboid(piGeomFactory, 
        &topdata,
        P[4],
        P[5],
        P[6],
        P[7]);
    
    if (NULL==pSolidCub2)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    pSolidCub2->Run();
    
    CATBody * pBody2 = pSolidCub2->GetResult();
    if (NULL==pBody2)
    {
        cout << "Probleme when creating pBody2 " << endl;
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    // -------------------------------------------------------------------
    // 3 - Creating pBody3 as a boolean intersection of pBody1 and pBody2
    // -------------------------------------------------------------------
    //
    CATDynBoolean * pIntersectOpe = NULL;
    pIntersectOpe = CATCreateDynBoolean(piGeomFactory, &topdata, CATBoolIntersection,
        pBody1, pBody2);
    if (NULL==pIntersectOpe)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    pIntersectOpe ->Run(); 
    CATBody * pBody3 = pIntersectOpe ->GetResult(); 
    
    if (NULL==pBody3)
    {
        cout << "Probleme when creating pBody3 " << endl;
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    CATLISTP(CATCell)  edgeList; 
    pBody3->GetAllCells( edgeList,1);
    CATLISTP(CATCell)  faceList; 
    pBody3->GetAllCells( faceList,2);
    
    // -------------------------------------------------------------------
    // 4 - Create the new journal and check it
    // -------------------------------------------------------------------
    //
    // (a) - Display the default journal - just for information
    //
    cout << "Default journal" << endl;
    pJournal->Tass();
    CAATopDumpJournal(pJournal);
    cout << "---------------" << endl;
    //
    // (b) - Create the new journal
    //
    // 
    // NOTE: edgeList[1] is not backtracked
    // the order below will be ignored by the checker
    pJournalNew->ReportCreation( NULL, edgeList[1],
        new CATCGMJournalInfo(1));
    pJournalNew->ReportCreation( NULL, faceList[1],
        new CATCGMJournalInfo(1));
    pJournalNew->ReportCreation( NULL, faceList[2],
        new CATCGMJournalInfo(1));
    pJournalNew->ReportCreation( NULL, faceList[3],
        new CATCGMJournalInfo(2));
    pJournalNew->ReportCreation( NULL, faceList[4],
        new CATCGMJournalInfo(3));
    pJournalNew->ReportCreation( NULL, faceList[5],
        new CATCGMJournalInfo(4));
    pJournalNew->ReportCreation( NULL, faceList[6],
        new CATCGMJournalInfo(5));
    //
    // (c) - Check the new journal
    //
    cout << "NEW JOURNAL expected OK - ONLY 1 WARNING (order ignored)" << endl; 
    pJournalNew->Tass();
    CAATopDumpJournal(pJournalNew);
    /*
    [ ]->Creation[Edge_275] Info = 1
    [ ]->Creation[Face_302] Info = 1
    [ ]->Creation[Face_115] Info = 1
    [ ]->Creation[Face_320] Info = 2
    [ ]->Creation[Face_314] Info = 3
    [ ]->Creation[Face_318] Info = 4
    [ ]->Creation[Face_324] Info = 5

    // You get this warning in the file specified in arg 3:
    WARNING
    [ ]->Creation[Edge_275] Info=1
    275 is not a bording cell - The order is ignored
    */
#ifdef _WINDOWS_SOURCE
    ofstream verdictFile(pFileName1, ios::binary ) ;
    ofstream warningFile(pFileName2, ios::binary ) ;
#else
    ofstream verdictFile(pFileName1,ios::out,filebuf::openprot) ;
    ofstream warningFile(pFileName2,ios::out,filebuf::openprot) ;
#endif
    CATUnicodeString mafeat("MyFeature");
    
    cout << "Start CAACheckForPart" << endl;
    CAACheckForPart * reportCheck = new CAACheckForPart(pJournalNew,
        pBody3,
        &mafeat,
        &verdictFile, &warningFile, TRUE);
    reportCheck->CAAAddInputBody(pBody1, CAATopCheckNoCopy);
    reportCheck->CAAAddInputBody(pBody2, CAATopCheckNoCopy);
    
    int checkReturn = reportCheck->CAACheck();
    if (checkReturn == 0 ) 
    {   
        cout << "Journal OK" << endl;
        rc = 0;
    }
    
    else
    {
        cout << "Journal KO" << endl;
        rc =1;
    }


    //----------------------------------------------------------------------------
    // 5 - Clean operators
    //----------------------------------------------------------------------------
    delete pSolidCubl ;
    pSolidCubl  = NULL;
    delete pSolidCub2 ;
    pSolidCub2  = NULL;
    delete pIntersectOpe ;
    pIntersectOpe  = NULL;
    delete [] P;
    if (reportCheck)
    {
      delete reportCheck;
      reportCheck = NULL;
    } 
    delete pJournal;  pJournal=NULL;
    delete pJournalNew; pJournalNew = NULL;
    //----------------------------------------------------------------------------
    // 6 - Release the configuration and save the result
    //----------------------------------------------------------------------------
    pConfig->Release();    
    if(1==toStore)
    {
        cout << "Writing the model" << endl;
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


