---
title: "Topological Journal: Creation and Validation (1)"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMCheckForPart", "CAAGMOperatorsInterfaces", "CAAGMTopDumpJournal", "CAATopCheckNoCopy", "CAAAddInputBody", "CAAGMOperatorsCheckGnKO", "CAACheck"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcJournalChecking1.md"
converted: "2026-05-11T17:33:48.964948"
---

Topological Journal: Creation and Validation (1)  
---  
Use Case  
Abstract If you create your own operator, you have generally to create also the associated topological journal. The journal plays a prominent role in the naming mechanism which is used by applications to differentiate cells.  Any user journal is to be checked by the appropriate tool. This use case creates and validates a journal. The created journal is basically valid and most applications can successfully use it. However a warning is issued concerning a naming rule (it is recommended to fix it).
    * Operator to be Used
    * Use Case Description
    * References  
---  
Operator to be Used To check the validity of a topological journal, you can use the CAAGMCheckForPart operator in CAAGMOperatorsInterfaces.edu/PublicInterfaces. There is no creation function, the operator has to be created by using the provided constructor. Use Case Description The CAAGMOperatorsCheckGnKO.m module in CAAGMOperatorsInterfaces.edu creates a new journal which is valid but contains some defects. This use case creates its input topological data, a prism. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). Note: Unlike most Geometric Modeler use cases, CAAGMOperatorsCheckGnKO is to be launched with three arguments:  `       CAAGMOperatorsCheckGnKO outputfile.NCGM verdictFile.NCGM DetailedErrorFile.NCGM` With the input and output cells below: Fig.1 Journal Checking: Extrusion of a Wire ![Journal Checking: Input Wire](images/CGM_journal_checking_0.png) 
---|---  
Input Wire |  Output Surface  
and the code below:
    
    CATCGMJournalList* pJournalNew = new CATCGMJournalList(pConfig,NULL);
    ...
    // Prism creation
    ...
    // Creation of a new journal
    pJournalNew->ReportCreation( edgeOperand, faceList[1], new CATCGMJournalInfo(1));
    pJournalNew->ReportCreation( edgeOperand, edgeList[4], new CATCGMJournalInfo(1));
    pJournalNew->ReportCreation( edgeOperand, edgeList[2], new CATCGMJournalInfo(2));
    pJournalNew->ReportCreation( vertexOperand1, edgeList[1], new CATCGMJournalInfo(4));
    pJournalNew->ReportCreation( vertexOperand2, edgeList[3], new CATCGMJournalInfo(3));
    ...
    // Tass and Dump the New journal
    pJournalNew->Tass();
    CAAGMTopDumpJournal(pJournalNew);
      
  
---  
you get this result on the standard output: ****************************************  
[Edge_26]->Creation[Face_43] Info = 1  
[Edge_26]->Creation[Edge_52] Info = 1  
[Edge_26]->Creation[Edge_51] Info = 2  
[Vertex_24]->Creation[Edge_45] Info = 4  
[Vertex_25]->Creation[Edge_48] Info = 3  
****************************************  
The code below:
    
    ofstream verdictFile(pFileName1, ios::binary ) ;
    ofstream warningFile(pFileName2, ios::binary ) ;
    CATUnicodeString mafeat("MyFeature");
    CAAGMCheckForPart * reportCheck = new CAAGMCheckForPart(pJournalNew,
            piPrismBody,
            &mafeat;,
            &verdictFile;, &warningFile;, TRUE);
    reportCheck->CAAAddInputBody(piCurve, CAATopCheckNoCopy);
    int checkReturn = reportCheck->CAACheck();  
  
---  
checks the created journal and generates two output .md files containing information on the journal.  **Step 1 -** Open the first file, you can read something like this. The journal is valid: 
    
    (1) - Mandatory Checking that all cells in result body can be traced back OK 
    (2) - Checking that all reported cells are of CATFace/CATEdge/CATVertex type OK
    (3) - Checking that all reported cells are bording cells OK 
    (4) - Checking that cells with same parents & infos are not of different type (rule not fulfilled)
    TOPOLOGICAL JOURNAL FOR FEATURE MyFeature OK 
    

The journal is basically valid. However, rule (4) is not fulfilled. If some applications were to use this journal for standard naming, the cell differentiation would not be necessarily guaranteed.  **Step 2 -** Open the second .md file for more information. You can read something like this:
    
    * 
    
    ...
    In
    [Edge_26]->Creation[Face_43] Info=1
    and
    [Edge_26]->Creation[Edge_52] Info=1
    Cells with same parents and "info" must not be of different type
    *
    

Note: the correct journal is: 
    
    [Edge_26]->Creation[Edge_51] Info = 1
    [Edge_26]->Creation[Edge_52] Info = 2
    [Vertex_24]->Creation[Edge_45] Info = 0
    [Vertex_25]->Creation[Edge_48] Info = 0
    [Edge_26]->Creation[Face_43] Info = 0
    

References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [ About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)  
[3] |  [ How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)  
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)  
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)  
[6] |  [Topological Journal: Principles](CAACgmTaTopJournal.md)  
[7] |  [Topological Journal: Methodology](CAACgmTaTopJournalMethodology.md)  
[8] |  [Using the Topological Journal](CAACgmUcTopJournal.md)  
History Version: **1** [Sept 2011] | Document created  
---|---
