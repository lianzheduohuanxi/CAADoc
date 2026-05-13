---
title: "Draft: Untwist"
category: "use case"
module: "CAACgmOperators"
tags: "["CAAGMOperatorsInterfaces", "CAAGMOperatorsDraftCreation", "CATICGMDynDraft", "CAATopDraftmain", "CAATopAdvancedDraft", "CATICGMDynAdvancedDraft"]"
source_file: "Doc/online/CAACgmOperators/CAACgmUcDraft2.htm"
converted: "2026-05-11T17:33:48.904800"
---
tags: ["CAAGMOperatorsInterfaces", "CAAGMOperatorsDraftCreation", "CATICGMDynDraft", "CAATopDraftmain", "CAATopAdvancedDraft", "CATICGMDynAdvancedDraft"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcDraft2.htmmd"
converted: "2026-05-11T17:33:48.904800"
Draft: Untwist

---
converted: "2026-05-11T17:33:48.904800"
Draft: Untwist
Use Case
Abstract CATICGMDynDraft is the base operator to create a draft. However drafting a set of adjacent faces may not be possible when the drafting angle is too big or when the face arrangement is such that the generated drafted faces self-intersect or are twisted. In this case, CATICGMDynAdvancedDraft is the operator to be used. All the operation parameters are gathered in a CATDynDraftDomain which is added to the CATICGMDynAdvancedDraft operator prior to running it.

    * Operator to be Used
    * Use Case Description
    * References
---
Operator to be Used To create a draft with "untwist" mode, use the CATICGMDynAdvancedDraft operator in GMOperatorsInterfaces. This operator has to be created using the CATCGMCreateDynAdvancedDraft global function.  Use Case Description The CAAGMOperatorsDraftCreation.m module in CAAGMOperatorsInterfaces.edu framework illustrates how to create drafts. This use case must be executed with two arguments, the input file DraftTest.NCGM which is delivered in the FunctionTests/InputData folder of the CAAGMOperatorsInterfaces.edu framework and the NCGM file to store the result. This use case is divided into three parts:
    1. CAATopDraftmain.cpp, the main program which calls the two other parts
    2. CreateDraft.cpp which explains how to create a basic draft
    3. CAATopAdvancedDraft.cpp which illustrates how to use the "untwist mode".
```vbscript
If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). Fig.1 Advanced Draft: Input data  ![Advanced Draft: Input Data](images/CGM_advanced_draft_0.png)

```

---
1. CAATopDraftmain.cpp, the main program which calls the two other parts
2. CreateDraft.cpp which explains how to create a basic draft
3. CAATopAdvancedDraft.cpp which illustrates how to use the "untwist mode".
If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). Fig.1 Advanced Draft: Input data  ![Advanced Draft: Input Data](images/CGM_advanced_draft_0.png)
With the code below:

    // (a) - Create a draft angle from the specified list of faces and an angle
```cpp
If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). Fig.1 Advanced Draft: Input data  ![Advanced Draft: Input Data](images/CGM_advanced_draft_0.png)
With the code below:
    CATDynDraftAngle *pDraftAngle = new CATDynDraftAngle(iFaces, iDraftAngle);
    CATListPtrCATDynDraftAngle listDraftAngles;
    listDraftAngles.Append(pDraftAngle);

```

    // (b) - Create a draft ribbon from the specified list of angles
CATDynDraftAngle *pDraftAngle = new CATDynDraftAngle(iFaces, iDraftAngle);
CATListPtrCATDynDraftAngle listDraftAngles;
listDraftAngles.Append(pDraftAngle);
    CATDynDraftRibbon *pDraftRibbon = new CATDynDraftRibbon(listDraftAngles);

    // (c) - Create a draft domain from the specified list of ribbons, draft direction and neutral face.
CATDynDraftRibbon *pDraftRibbon = new CATDynDraftRibbon(listDraftAngles);
    CATListPtrCATDynDraftRibbon listRibbons;
    listRibbons.Append(pDraftRibbon);
    CATDynDraftDomain *pDraftDomain = new CATDynDraftDomain(iDraftDir, CATDynDraftDomainNeutral, iNeutralFace, listRibbons);

    // (d) - Create the advanced draft operator, append the draft domain and enable untwisting
CATListPtrCATDynDraftRibbon listRibbons;
listRibbons.Append(pDraftRibbon);
CATDynDraftDomain *pDraftDomain = new CATDynDraftDomain(iDraftDir, CATDynDraftDomainNeutral, iNeutralFace, listRibbons);
    CATICGMDynAdvancedDraft *pDraftOp = CATCGMCreateDynAdvancedDraft(iFactory, iTopData, iBody, CATDynBasic);

    ...
CATDynDraftDomain *pDraftDomain = new CATDynDraftDomain(iDraftDir, CATDynDraftDomainNeutral, iNeutralFace, listRibbons);
CATICGMDynAdvancedDraft *pDraftOp = CATCGMCreateDynAdvancedDraft(iFactory, iTopData, iBody, CATDynBasic);
    pDraftOp->Add(pDraftDomain);
    pDraftOp->SetAutomaticUntwistMode(TRUE);

    ...
CATICGMDynAdvancedDraft *pDraftOp = CATCGMCreateDynAdvancedDraft(iFactory, iTopData, iBody, CATDynBasic);
pDraftOp->Add(pDraftDomain);
pDraftOp->SetAutomaticUntwistMode(TRUE);
    pDraftOp->Run(#);
    CATBody * pDraftBody = NULL;
```vbscript
    pDraftBody = pDraftOp->GetResult(#);

```

---
CATBody * pDraftBody = NULL;
pDraftBody = pDraftOp->GetResult(#);
you get this result: Fig.2 Advanced Draft: No Untwist Mode and Untwist Mode  ![ Advanced Draft: No Untwist](images/CGM_advanced_draft_1.png)

References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)
History Version: **1** [Sept 2011] | Document created
---|---
