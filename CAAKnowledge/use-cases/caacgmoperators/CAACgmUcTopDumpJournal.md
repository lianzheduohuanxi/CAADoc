---
```vbscript
title: "Dumping the Topological Journal"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMDumpJournal", "CAAGMOperatorsInterfaces", "CAAGMOperatorsCheckGnOK", "CAAGMTopDumpJournal", "CAAGMOperatorsClashIntersect", "CAAGMOperatorsBoundaryCreation", "CAAGMOperatorsCheckGnKO", "CAAGMOperatorsDumpJournal"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopDumpJournal.htmmd"
converted: "2026-05-11T17:33:49.148870"
```

---
tags: ["CAAGMDumpJournal", "CAAGMOperatorsInterfaces", "CAAGMOperatorsCheckGnOK", "CAAGMTopDumpJournal", "CAAGMOperatorsClashIntersect", "CAAGMOperatorsBoundaryCreation", "CAAGMOperatorsCheckGnKO", "CAAGMOperatorsDumpJournal"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopDumpJournal.htmmd"
converted: "2026-05-11T17:33:49.148870"
Dumping the Topological Journal

---
converted: "2026-05-11T17:33:49.148870"
Dumping the Topological Journal
Use Case
Abstract The journal describes the topological modifications brought to the input bodies to get the resulting body during a topological operation. The journal is filled under request by the topological operators. To display a journal on the standard output, you can use the CAAGMOperatorsDumpJournal use case. This use case can be customized by those of you who want to modify or re-arrange the format of the orders.

    * What You Will Learn With This Use Case
    * The CAAGMOperatorsDumpJournal Use Case
      * What Does CAAGMOperatorsDumpJournal Do
      * How to Call It
      * Where to Find Examples
    * Step-by-Step
    * References
---
What You Will Learn With This Use Case The primary goal of the use case is to help you dump the journal orders. It is also an illustration of :
    * how to scan a journal by using the `CATCGMJournalList::Next method`
    * how to determine the type of an event (creation, modification...) by using `CATCGMJournalListItem::GetType`
    * how to retrieve the parent objects for a given statement by using `CATCGMJournalListItem::GetFirstObjs`
    * or how to retrieve the children object by using `CATCGMJournalListItem::GetLastObjs.`
See "Topological Journal Principles" [1]  "Topological Journal Methodology" [2] for more information about this subject. The CAAGMOperatorsDumpJournal Use Case CAAGMOperatorsDumpJournal is a use case to be used as a **shared library**. It is delivered in the CAAGMOperatorsInterfaces.edu framework that illustrates the GMOperatorsInterfaces framework capabilities. What Does CAAGMOperatorsDumpJournal Do It dumps the topological journal on the standard output. How to Call It CAAGMOperatorsDumpJournal is a **shared library** which has to be included in the Imakefile.mk file of your application, then you call the global function CAAGMTopDumpJournal to dump the journal:
    #include CAAGMDumpJournal.h
    ...
See "Topological Journal Principles" [1]  "Topological Journal Methodology" [2] for more information about this subject. The CAAGMOperatorsDumpJournal Use Case CAAGMOperatorsDumpJournal is a use case to be used as a **shared library**. It is delivered in the CAAGMOperatorsInterfaces.edu framework that illustrates the GMOperatorsInterfaces framework capabilities. What Does CAAGMOperatorsDumpJournal Do It dumps the topological journal on the standard output. How to Call It CAAGMOperatorsDumpJournal is a **shared library** which has to be included in the Imakefile.mk file of your application, then you call the global function CAAGMTopDumpJournal to dump the journal:
    CATCGMJournalList* pJournalToDump = ...;
    CAAGMTopDumpJournal(pJournalToDump);

Where to Find Examples The topological journal is dumped in the use cases below:

    * CAAGMOperatorsCheckGnOK.m
    * CAAGMOperatorsCheckGnKO.m
    * CAAGMOperatorsClashIntersect.m
    * CAAGMOperatorsBoundaryCreation.m
Where to Find Examples The topological journal is dumped in the use cases below:
which are all in the CAAGMOperatorsInterfaces.edu framework. Step-by-Step
    1. Scan the journal:

           CATCGMJournalItem* pJournalItem = Next->CastToReportItem(#);

    2. For each journal statement:
       1. get the input cells ("parent cells"):

              CATLISTP(CATGeometry) parentList;
              pJournalItem->GetFirstObjs(parentList);

       2. get the event type:

              CATCGMJournal::Type CGMEventType = pJournalItem->GetType(#);
              switch (CGMEventType)

                 {
2. get the event type:
CATCGMJournal::Type CGMEventType = pJournalItem->GetType(#);
switch (CGMEventType)
```vbscript
                   case CATCGMJournal::Creation:

```

                     {
CATCGMJournal::Type CGMEventType = pJournalItem->GetType(#);
switch (CGMEventType)
case CATCGMJournal::Creation:
                       cout >> "->Creation";

                       ...

cout >> "->Creation";
       3. get the output cells ("children cells"):

              CATLISTP(CATGeometry) childrenList;
              pJournalItem->GetLastObjs(childrenList);

       4. get the associated "info data":

              const CATCGMJournalInfo * journalInfo = pJournalItem->GetAssociatedInfo(#);

References [1] | [Topological Journal Principles](CAACgmTaTopJournal.md)

[2] |  [ Topological Journal Methodology](CAACgmTaTopJournalMethodology.md)
History Version: **1** [May 2014] | Document created
---|---
