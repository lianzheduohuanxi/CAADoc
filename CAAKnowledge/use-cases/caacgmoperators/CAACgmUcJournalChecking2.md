---
title: "Topological Journal: Creation and Validation (2)"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMCheckForPart", "CAAGMOperatorsInterfaces", "CAAGMOperatorsCheckGnOK", "CAAGMTopDumpJournal", "CAATopCheckNoCopy", "CAAAddInputBody", "CAACheck"]
source_file: "Doc\online\CAACgmOperators\CAACgmUcJournalChecking2.htm"
converted: "2026-05-11T17:33:48.974055"
---

Topological Journal: Creation and Validation (2)  
---  
Use Case  
Abstract If you create your own operator, you have generally to create also the associated topological journal. The journal plays a prominent role in the naming mechanism which is used by applications to differentiate cells.  Any user journal is to be checked by the appropriate tool.  This use case creates and validates a journal. The created journal is valid and applications in need for journal data will successfully use it. However the journal contains an order which is ignored. In other words, it is not clean. It is recommended to discard such order from your journals.
    * Operator to be Used
    * Use Case Description
    * References  
---  
Operator to be Used To check the validity of a topological journal, you can use the CAAGMCheckForPart operator in CAAGMOperatorsInterfaces.edu/PublicInterfaces. There is no creation function, the operator has to be created by using the provided constructor. Use Case Description The CAAGMOperatorsCheckGnOK.m module in CAAGMOperatorsInterfaces.edu creates a new journal which is valid. This use case creates its input topological data. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.htm). Note: Unlike most Geometric Modeler use cases, CAAGMOperatorsCheckGnOK is to be launched with three arguments:  `CAAGMOperatorsCheckGnOK outputfile.NCGM verdictFile.NCGM DetailedErrorFile.NCGM` With the input and output cells below: Fig.1 Journal Checking: Boolean Intersection ![Journal Checking: Boolean Operation](images/CGM_journal_checking_2.png) |  ![Journal Checking: Boolean Result](images/CGM_journal_checking_3.png)  
---|---  
Input Bodies |  Output Solid  
and the code below:
    
    CATCGMJournalList* pJournalNew = new CATCGMJournalList(pConfig,NULL);
    ...
    // Prism creation
    ...
    // Creation of a new journal
    // NOTE: edgeList[1] is not backtracked
    // the order below will be ignored by the checker
    pJournalNew->ReportCreation( NULL, edgeList[1], new CATCGMJournalInfo(1));
    pJournalNew->ReportCreation( NULL, faceList[1], new CATCGMJournalInfo(6));
    pJournalNew->ReportCreation( NULL, faceList[2], new CATCGMJournalInfo(1));
    pJournalNew->ReportCreation( NULL, faceList[3], new CATCGMJournalInfo(2));
    pJournalNew->ReportCreation( NULL, faceList[4], new CATCGMJournalInfo(3));
    pJournalNew->ReportCreation( NULL, faceList[5], new CATCGMJournalInfo(4));
    pJournalNew->ReportCreation( NULL, faceList[6], new CATCGMJournalInfo(5));
    ...
    // Tass and Dump the New journal
    pJournalNew->Tass();
    CAAGMTopDumpJournal(pJournalNew);
      
  
---  
you get this result on the standard output:
    
    [ ]->Creation[Edge_257] Info = 1
    [ ]->Creation[Face_301] Info = 6
    [ ]->Creation[Face_115] Info = 1
    [ ]->Creation[Face_323] Info = 2
    [ ]->Creation[Face_319] Info = 3
    [ ]->Creation[Face_317] Info = 4
    [ ]->Creation[Face_313] Info = 5
    

The code below:
    
    ofstream verdictFile(pFileName1, ios::binary ) ;
    ofstream warningFile(pFileName2, ios::binary ) ;
    CATUnicodeString mafeat("MyFeature");
    CAAGMCheckForPart * reportCheck = new CAAGMCheckForPart(pJournalNew,
            piPrismBody,
            &mafeat;,
            &verdictFile;, &warningFile;, TRUE);
    reportCheck->CAAAddInputBody(pBody1, CAATopCheckNoCopy);
    reportCheck->CAAAddInputBody(pBody2, CAATopCheckNoCopy);
    int checkReturn = reportCheck->CAACheck();
      
  
---  
checks the created journal and generates two output .htm files containing information on the journal.  **Step 1 -** Open the first file, you can read something like this. The journal is valid: 
    
    (1) - Mandatory Checking that all cells in result body can be traced back OK 
    (2) - Checking that all reported cells are of CATFace/CATEdge/CATVertex type OK
    (3) - Checking that all reported cells are bording cells (rule not fulfilled) 
    (4) - Checking that cells with same parents & infos are not of different type OK
    TOPOLOGICAL JOURNAL FOR FEATURE MyFeature OK 
    

The journal is valid. However, rule (3) is not fulfilled because Edge_257 is not to be reported (it is not a bording cell).  **Step 2 -** Open the second .htm file for more information. You can read something like this:
    
    * 
    
    ...
    * 
    WARNING
    [ ]->Creation[Edge_257] Info=1
    257 is not a bording cell - The order is ignored
    * 
    
    WARNING
    The following cells are not bording cells:
    257 
    
    

References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.htm)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.htm)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.htm)  
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.htm)  
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.htm)  
[6] |  [Topological Journal: Principles](CAACgmTaTopJournal.htm)  
[7] |  [Topological Journal: Methodology](CAACgmTaTopJournalMethodology.htm)  
[8] |  [Using the Topological Journal](CAACgmUcTopJournal.htm)  
History Version: **1** [Sept 2011] | Document created  
---|---
