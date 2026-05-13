---
```vbscript
title: "Chamfer"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CATICGMDynAdvancedChamfer", "CAAGMOperatorsChamfer"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopChamfer.htmmd"
converted: "2026-05-11T17:33:49.109308"
```

---
tags: ["CAAGMOperatorsInterfaces", "CATICGMDynAdvancedChamfer", "CAAGMOperatorsChamfer"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopChamfer.htmmd"
converted: "2026-05-11T17:33:49.109308"
Chamfer

---
converted: "2026-05-11T17:33:49.109308"
Chamfer
Use Case
Abstract Chamfering consists in removing or adding a flat section from a selected edge to create a beveled surface between the two original faces common to that edge. A chamfer can be propagated along one or several edges.

    * Operator to be Used
    * Use Case Description
    * References
---
Abstract Chamfering consists in removing or adding a flat section from a selected edge to create a beveled surface between the two original faces common to that edge. A chamfer can be propagated along one or several edges.
Operator to be Used To create a chamfer, use the CATICGMDynAdvancedChamfer operator in GMOperatorsInterfaces. This operator has to be created by the CATCGMCreateDynAdvancedChamfer global function. Use Case Description The CAAGMOperatorsChamfer.m module in CAAGMOperatorsInterfaces.edu illustrates how to create chamfers. This use case is to be run with the ChamferInputs.NCGM input file which is delivered in CAAGMOperatorsInterfaces.edu/FunctionTests/InputData. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).  With the input data below in which there are six edges to be chamfered (five top edges, plus one lateral edge in pink on figures): Fig.1 Chamfer Operation: Input Data ![Chamfer0](images/CGM_chamfer_0.png)

Operator to be Used To create a chamfer, use the CATICGMDynAdvancedChamfer operator in GMOperatorsInterfaces. This operator has to be created by the CATCGMCreateDynAdvancedChamfer global function. Use Case Description The CAAGMOperatorsChamfer.m module in CAAGMOperatorsInterfaces.edu illustrates how to create chamfers. This use case is to be run with the ChamferInputs.NCGM input file which is delivered in CAAGMOperatorsInterfaces.edu/FunctionTests/InputData. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).  With the input data below in which there are six edges to be chamfered (five top edges, plus one lateral edge in pink on figures): Fig.1 Chamfer Operation: Input Data ![Chamfer0](images/CGM_chamfer_0.png)
Front view | Rear view
and the code below:

    CATListPtrCATFace listFaces;
    CATDynChamferRibbon* pRibbon =  new CATDynChamferRibbon(iEdges,
                       listFaces,
                       CATDynd1a1,
                       50,  // distance from edge to be chamfered to face
                       45); // angle 45 deg

    ...
listFaces,
CATDynd1a1,
50,  // distance from edge to be chamfered to face
45); // angle 45 deg
    CATICGMDynAdvancedChamfer *pChamferOp = CATCGMCreateDynAdvancedChamfer(iFactory, iTopData, iBody);

    ...
50,  // distance from edge to be chamfered to face
45); // angle 45 deg
CATICGMDynAdvancedChamfer *pChamferOp = CATCGMCreateDynAdvancedChamfer(iFactory, iTopData, iBody);
    pChamferOp->Append(pRibbon);

    pChamferOp->SetCornerCap(#);
    pChamferOp->Run(#);
    CATBody * pChamferBody = NULL;
```vbscript
    pChamferBody = pChamferOp->GetResult(#);

```

    ...
pChamferOp->SetCornerCap(#);
pChamferOp->Run(#);
CATBody * pChamferBody = NULL;
pChamferBody = pChamferOp->GetResult(#);
    pChamferOp->Release(#);
    pChamferOp = NULL;
```vbscript
    if (NULL != pRibbon)

```

    {
pChamferOp->Release(#);
pChamferOp = NULL;
if (NULL != pRibbon)
      delete pRibbon;
      pRibbon = NULL;

    }

---
pRibbon = NULL;
you get this result: Fig.2 Result of Chamfer Operation  ![Chamfer Result Cap Corner Front View ](images/CGM_chamfer_1.png)

you get this result: Fig.2 Result of Chamfer Operation  ![Chamfer Result Cap Corner Front View ](images/CGM_chamfer_1.png)
Front view: Chamfer result | Rear view: No corner cap setting | Rear view: SetCornerCap
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)

[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)
History Version: **1** [Sept 2011] | Document created
---|---
