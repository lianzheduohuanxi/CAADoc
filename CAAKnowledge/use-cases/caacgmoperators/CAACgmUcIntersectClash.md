---
```vbscript
title: "Boolean Intersection"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CATICGMDynBoolean", "CAAGMTopDumpJournal", "CAAGMOperatorsClashIntersect"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcIntersectClash.htmmd"
converted: "2026-05-11T17:33:48.954937"
```

---
tags: ["CAAGMOperatorsInterfaces", "CATICGMDynBoolean", "CAAGMTopDumpJournal", "CAAGMOperatorsClashIntersect"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcIntersectClash.htmmd"
converted: "2026-05-11T17:33:48.954937"
Boolean Intersection

---
converted: "2026-05-11T17:33:48.954937"
Boolean Intersection
Use Case
Abstract A Boolean intersection results in a solid which contains only the portions which are shared between the two input bodies. If you need to determine which cells in the resulting body come from either input body, you can use the journal.  This is illustrated in the CAAGMOperatorsClashIntersect use case.

    * Operator to be Used
    * Use Case Description
    * References
---
Abstract A Boolean intersection results in a solid which contains only the portions which are shared between the two input bodies. If you need to determine which cells in the resulting body come from either input body, you can use the journal.  This is illustrated in the CAAGMOperatorsClashIntersect use case.
Operator to be Used To perform a Boolean intersection, you must use the CATICGMDynBoolean operator which is created by the CATCGMCreateDynBoolean global function. The third argument must be set to CATBoolIntersection. Use Case Description The CAAGMOperatorsClashIntersect.m module in CAAGMOperatorsInterfaces.edu intersects two cylinders. This use case loads the BodiesForClashInput.NCGM file which contains the input data and is delivered in the FunctionTests/InputData folder of the CAAGMOperatorsInterfaces.edu framework.  If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). With the input bodies below: Fig.1 Boolean Intersection Between Two Cylinders ![Boolean Intersection: Input Solids](images/CGM_clash_journal_0.png)

---
Operator to be Used To perform a Boolean intersection, you must use the CATICGMDynBoolean operator which is created by the CATCGMCreateDynBoolean global function. The third argument must be set to CATBoolIntersection. Use Case Description The CAAGMOperatorsClashIntersect.m module in CAAGMOperatorsInterfaces.edu intersects two cylinders. This use case loads the BodiesForClashInput.NCGM file which contains the input data and is delivered in the FunctionTests/InputData folder of the CAAGMOperatorsInterfaces.edu framework.  If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). With the input bodies below: Fig.1 Boolean Intersection Between Two Cylinders ![Boolean Intersection: Input Solids](images/CGM_clash_journal_0.png)
and the code below:

    CATICGMDynBoolean * pBoolOpe = NULL;
    pBoolOpe =::CATCGMCreateDynBoolean(piGeomFactory,&topdata;,
    		CATBoolIntersection, piBodyA, piBodyB);

    ...
CATICGMDynBoolean * pBoolOpe = NULL;
pBoolOpe =::CATCGMCreateDynBoolean(piGeomFactory,&topdata;,
CATBoolIntersection, piBodyA, piBodyB);
    pBoolOpe->Run(#);
    CATBody * pBodyIntersect = pBoolOpe->GetResult(#);

    ...

---
CATBody * pBodyIntersect = pBoolOpe->GetResult(#);
you get this result: Fig.2 Boolean Intersection: Result ![Boolean Intersection: Result](images/CGM_clash_journal_1.png)

---
you get this result: Fig.2 Boolean Intersection: Result ![Boolean Intersection: Result](images/CGM_clash_journal_1.png)
The code below:

    pJournal->Tass(#);
    CAAGMTopDumpJournal(pJournal);

---
pJournal->Tass(#);
CAAGMTopDumpJournal(pJournal);
dumps the journal on the standard output. You get something like this:

    [Face_2793],[Face_2782]->Absorption[Face_3350]
    [Face_2535]->Modification[Face_3298]
    [Face_2546]->Modification[Face_3296]
    [Face_2800],[Face_2553]->Absorption[Face_3286]
    [Face_2798],[Face_2551]->Absorption[Face_3290]

Each face of the resulting body results from a modification or an absorption of the input body(ies) faces.  To determine which resulting face comes from which input body, the CATCGMJournalList::FindFirst method is used.  The parent cells of the resulting cells are retrieved and looked for ("located") in the list of cells of the two input bodies.  The code below scans the faces of the resulting body and creates the list of faces coming from either input bodies.

    //
    // (b) - Scan the faces of the resulting body
    //
Each face of the resulting body results from a modification or an absorption of the input body(ies) faces.  To determine which resulting face comes from which input body, the CATCGMJournalList::FindFirst method is used.  The parent cells of the resulting cells are retrieved and looked for ("located") in the list of cells of the two input bodies.  The code below scans the faces of the resulting body and creates the list of faces coming from either input bodies.
```vbscript
    for (int k = 1; k < listOfFaces.Size(#)+1; k++)

```

      {
        CATLISTP(CATGeometry) originObjects;
        //
        // Get the parent faces if the order is creation/modification/absorption
        //
```vbscript
CATLISTP(CATGeometry) originObjects;
        CATCell * myptr =listOfFaces[k];
        pJournal->FindFirsts(myptr, originObjects, ThroughAllCreateAndModify);
       if (myptr != NULL )
```

          {
CATCell * myptr =listOfFaces[k];
pJournal->FindFirsts(myptr, originObjects, ThroughAllCreateAndModify);
if (myptr != NULL )
            cout << "Face :" << myptr->GetPersistentTag(#) << endl;

          }
     ...
```vbscript
if (myptr != NULL )
cout << "Face :" << myptr->GetPersistentTag(#) << endl;
    if ( (isInBodyA==1) && (isInBodyB == 1) )
            absorbedFaces.Append(myptr);
    if ( (isInBodyA == 1) && (isInBodyB ==0) )
            facesCommingFromA.Append(myptr);
    if ( (isInBodyA == 0) && (isInBodyB ==1) )
            facesCommingFromB.Append(myptr);
```

       }

---
facesCommingFromB.Append(myptr);
When displaying the lists of faces coming from each input body and the list of absorbed faces, you get this:

    List of faces in the resulting body
    Faces coming from BodyA and only from A
    3298
    3296
    Faces coming from BodyB and only from BodyB
    3350
    Absorbed faces
    3290
    3286

References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)

[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)
[6] |  [Topological Journal: Principles](CAACgmTaTopJournal.md)
[7] |  [Topological Journal: Methodology](CAACgmTaTopJournalMethodology.md)
[8] |  [Using the Topological Journal](CAACgmUcTopJournal.md)
History Version: **1** [Sept 2011] | Document created
---|---
