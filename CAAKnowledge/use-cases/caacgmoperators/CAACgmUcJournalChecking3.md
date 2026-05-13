---
```vbscript
title: "Topological Journal: Writing a Validation Tool "
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMCheckForPart", "CAAGMOperatorsInterfaces", "CAAGMOperatorsCheckGnOK", "CAAGMOperatorsJournalThreadOpMain", "CAAGMTopCheckForPart", "CAATopCheckNoCopy", "CAAAddInputBody", "CAAGMOperatorsCheckGnKO", "CAAGMOperatorsCheckForPart", "CAACheck"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcJournalChecking3.htmmd"
converted: "2026-05-11T17:33:48.983062"
```

---
tags: ["CAAGMCheckForPart", "CAAGMOperatorsInterfaces", "CAAGMOperatorsCheckGnOK", "CAAGMOperatorsJournalThreadOpMain", "CAAGMTopCheckForPart", "CAATopCheckNoCopy", "CAAAddInputBody", "CAAGMOperatorsCheckGnKO", "CAAGMOperatorsCheckForPart", "CAACheck"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcJournalChecking3.htmmd"
converted: "2026-05-11T17:33:48.983062"
Topological Journal: Writing a Validation Tool

---
converted: "2026-05-11T17:33:48.983062"
Topological Journal: Writing a Validation Tool
Use Case
Abstract A valid journal should at least follow one rule: _" all the cells belonging to the resulting body must be backtracked"_. In other words, the history of each cell in the resulting body must be traceable. There are other rules but they are not mandatory.  As a reminder, here are the rules to be fulfilled when you create a journal:
    1. all the cells belonging to the resulting body must be backtracked
    2. all reported cells must be of CATFace/CATEdge/CATVertex type
    3. all reported cells must bording cells
    4. cells with same parents & infos must not be of different type.
The CAAGMOperatorsCheckForPart.m use case provides you with a way to write your own tool to validate a journal. It is a fully open tool which can be adjusted, modified or enhanced according to your need.

    * Operator to be Used
    * References
---
4. cells with same parents & infos must not be of different type.
The CAAGMOperatorsCheckForPart.m use case provides you with a way to write your own tool to validate a journal. It is a fully open tool which can be adjusted, modified or enhanced according to your need.
Operator to be Used The CAAGMCheckForPart operator is created in CAAGMOperatorsInterfaces.edu/PublicInterfaces. It is being used in the some use cases such as CAAGMOperatorsCheckGnKO.m, CAAGMOperatorsCheckGnOK.m or CAAGMOperatorsJournalThreadOpMain.m. Its implementation is delivered in the CAAGMTopCheckForPart.cpp file of the CAAGMOperatorsCheckForPart.m module.  Refer to: [ Topological Journal: Creation and Validation (1) ](CAACgmUcJournalChecking1.md), [Topological Journal: Creation and Validation (2)](CAACgmUcJournalChecking2.md), [Threading a Rod](CAACgmUcAdtThreadOperator.md) for examples. The CAAGMCheckForPart operator is to be used like this:

    // Creates the operator
Operator to be Used The CAAGMCheckForPart operator is created in CAAGMOperatorsInterfaces.edu/PublicInterfaces. It is being used in the some use cases such as CAAGMOperatorsCheckGnKO.m, CAAGMOperatorsCheckGnOK.m or CAAGMOperatorsJournalThreadOpMain.m. Its implementation is delivered in the CAAGMTopCheckForPart.cpp file of the CAAGMOperatorsCheckForPart.m module.  Refer to: [ Topological Journal: Creation and Validation (1) ](CAACgmUcJournalChecking1.md), [Topological Journal: Creation and Validation (2)](CAACgmUcJournalChecking2.md), [Threading a Rod](CAACgmUcAdtThreadOperator.md) for examples. The CAAGMCheckForPart operator is to be used like this:
    CAAGMCheckForPart * reportCheck = new CAAGMCheckForPart(JournalToBeChecked,  // The journal to be checked
            pResultBody,

            &FeatureName;,        // mainly dedicated to Part Design applications
            &VerdictFile;,        // summary of checking operations
            &WarningFile;,        // detailed list of errors and warnings
CAAGMCheckForPart * reportCheck = new CAAGMCheckForPart(JournalToBeChecked,  // The journal to be checked
pResultBody,
            TRUE);               // activates a verbose mode

    // Adds the input body(ies) and specifies the Copy/NoCopy mode
TRUE);               // activates a verbose mode
    reportCheck->CAAAddInputBody(pInputBody1, CAATopCheckNoCopy);
    reportCheck->CAAAddInputBody(pInputBody2, CAATopCheckNoCopy);

    ...
    // Checks the journal - 0 is returned if valid
reportCheck->CAAAddInputBody(pInputBody1, CAATopCheckNoCopy);
reportCheck->CAAAddInputBody(pInputBody2, CAATopCheckNoCopy);
    int checkReturn = reportCheck->CAACheck(#);

---
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)
[6] |  [Topological Journal: Principles](CAACgmTaTopJournal.md)
[7] |  [Topological Journal: Methodology](CAACgmTaTopJournalMethodology.md)
[8] |  [Using the Topological Journal](CAACgmUcTopJournal.md)
History Version: **1** [Sept 2011] | Document created
---|---
