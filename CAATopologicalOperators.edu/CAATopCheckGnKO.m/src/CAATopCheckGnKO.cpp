/**
* @quickReview GDR 03:06:30
*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2002
//
// Sample code for : Geometric Modeler - Topological journal
// Mission         : Illustrates the checking of the namimg rules
//                   Journal OK but Naming Rules KO
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
// How to run it   : CAATopCheckGnKO file.ncgm file1.html file2.html  
//=======================================================================================

#include <iostream.h>
#include <iomanip.h>
#include "fstream.h"

// Mathematics
#include "CATSoftwareConfiguration.h"
#include "CATMathDirection.h" 

// BasicTopologicalOpe
#include "CATTopPointOperator.h"

// GeometricObjects
#include "CATGeoFactory.h"               // Geometry factory
#include "CATCGMContainerMngt.h"         // Management of the geometry factory
#include "CATCGMJournalList.h"           // Journal
#include "CATCGMJournalInfo.h"

// NewTopologicalObjects
#include "CATBody.h"
#include "CATCell.h"
#include "CATFace.h"

// TopologicalOperators
#include "CATTopPrism.h"
#include "CATTopSplineOperator.h"
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
    // 2 - Create spline and prism
    //----------------------------------------------------------------------------
   
     // Create a wire 

    const int nbpts = 3;
    CATBody ** aPoints1 = new CATBody * [nbpts];
    
    aPoints1[0] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,0,0,0);
    aPoints1[1] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,20.0, 10.,0.0);
    aPoints1[2] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,30.0, 5.,0.0);

     CATBody * piCurve = ::CATCreateTopSpline(piGeomFactory,
        &topdata,
        nbpts,
        aPoints1);
    if (NULL==piCurve)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    } 
    // Create a prism
    // 
    CATMathDirection   zDir1(0., 0.,  1.);
    double startOffset = 20.;
    double endOffset   = 0.;
    CATTopPrism       *pPrismOpe = ::CATCreateTopPrism (piGeomFactory,
        &topdata,
        piCurve,
        &zDir1,
        startOffset,
        endOffset);
    if (NULL==pPrismOpe)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    } 
    pPrismOpe->Run();
    
    CATBody * piPrismBody=NULL;
    piPrismBody = pPrismOpe->GetResult();
    if (NULL==piPrismBody)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    } 
  
    CATLISTP(CATCell)  edgeListWire; 
    piCurve->GetAllCells( edgeListWire,1);
    CATLISTP(CATCell)  vertexListWire; 
    piCurve->GetAllCells( vertexListWire,0);
    CATLISTP(CATCell)  edgeList; 
    piPrismBody->GetAllCells( edgeList,1);
    CATLISTP(CATCell)  faceList; 
    piPrismBody->GetAllCells( faceList,2);
    CATLISTP(CATGeometry) edgeOperand;
    edgeOperand.Append(edgeListWire[1]);
    CATLISTP(CATGeometry) vertexOperand1;
    vertexOperand1.Append(vertexListWire[1]);
    CATLISTP(CATGeometry) vertexOperand2;
    vertexOperand2.Append(vertexListWire[2]);
    //
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
    pJournalNew->ReportCreation( edgeOperand, faceList[1],
        new CATCGMJournalInfo(1));
    pJournalNew->ReportCreation( edgeOperand, edgeList[4],
        new CATCGMJournalInfo(1));
    pJournalNew->ReportCreation( edgeOperand, edgeList[2],
        new CATCGMJournalInfo(2));
    pJournalNew->ReportCreation( vertexOperand1, edgeList[1],
        new CATCGMJournalInfo(4));
    pJournalNew->ReportCreation( vertexOperand2, edgeList[3],
        new CATCGMJournalInfo(3));
       
    //
    // (c) - Check the new journal
    //
    cout << "NEW JOURNAL EXPECTED OK WITH ONE NAMING ERROR/WARNING " << endl; 
    pJournalNew->Tass();
    CAATopDumpJournal(pJournalNew);
/*
Journal is OK but NAMING RULE CHECK IS KO

[Edge_27]->Creation[Face_44] Info = 1
[Edge_27]->Creation[Edge_53] Info = 1
[Edge_27]->Creation[Edge_52] Info = 2
[Vertex_25]->Creation[Edge_46] Info = 4
[Vertex_26]->Creation[Edge_49] Info = 3

ERROR
In
[Edge_27]->Creation[Face_44] Info=1
and
[Edge_27]->Creation[Edge_53] Info=1
Cells with same parents and infos must not be of different type
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
        piPrismBody,
        &mafeat,
        &verdictFile, &warningFile, TRUE);
    reportCheck->CAAAddInputBody(piCurve, CAATopCheckNoCopy);
    
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
    
    delete pPrismOpe ;
    pPrismOpe  = NULL;
    delete [] aPoints1;
    if (reportCheck)
    {
      delete reportCheck;
      reportCheck = NULL;
    }
    if (pJournalNew)
    {
      delete pJournalNew;
      pJournalNew = NULL;
    }
    if (pJournal)
    {
      delete pJournal;
      pJournal = NULL;
    }

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


