---
title: "Corner"
category: "use case"
module: "CAACgmOperators"
tags: "["CAAGMOperatorsCornerCreation", "CATICGMTopCorner", "CAAGMOperatorsInterfaces"]"
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopCorner.htm"
converted: "2026-05-11T17:33:49.126240"
---
Corner

    ---

    		Use Case

    		Abstract
    		Corners are circle arcs tangent to two wires. A corner must
    		be created on a support. The two input wires must lie on the support.

            * Operator to be Used

            * Use Case Description

            * References

    ---

    Operator to be Used
    To create a corner, use the CATICGMTopCorner operator in GMOperatorsInterfaces.
    This operator has to
    be created by the CATCGMCreateTopCorner global function.
    Use Case Description
    The CAAGMOperatorsCornerCreation.m module in CAAGMOperatorsInterfaces.edu
    illustrates how to create a corner on support. This use case is to be run with
    the CornerInputs.NCGM input file which is delivered in
    CAAGMOperatorsInterfaces.edu/FunctionTests/InputData. If you are not already
    familiar with geometric modeler use cases, go to

    [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).
illustrates how to create a corner on support. This use case is to be run with
the CornerInputs.NCGM input file which is delivered in
CAAGMOperatorsInterfaces.edu/FunctionTests/InputData. If you are not already
familiar with geometric modeler use cases, go to
    With the input data below:

      Fig.1 Corner Operation: Input Data

        ![Corner on support](images/CGM_corner_0.png)

    ---

    and the code below:

    CATICGMTopCorner* pCornerOpe = ::CATCGMCreateTopCorner(piGeomFactory,
            &topdata;,
CATICGMTopCorner* pCornerOpe = ::CATCGMCreateTopCorner(piGeomFactory,
            pBodyWire1,    // inner wire
            pBodyWire2,    // bounding wire
            pBodySupport,  // supporting shell
            11.0) ;        // corner radius

    ...
pBodyWire1,    // inner wire
pBodyWire2,    // bounding wire
pBodySupport,  // supporting shell
11.0) ;        // corner radius
    pCornerOpe -> SetOffsetOrientation(-1,-1);
    int ResultTrimmingMode1 = pCornerOpe -> SetCircleMode(Direct); // shortest portion kept
    int ResultTrimmingMode2 = pCornerOpe -> SetSupportTrimmingSideAndMode(0,0); // no merge
    pCornerOpe->Run(#);
    CATBody *piCornerBody = pCornerOpe->GetResult(#);
    pCornerOpe->Release(#);
    pCornerOpe = NULL;

---
pCornerOpe->Release(#);
pCornerOpe = NULL;
you get this result: Fig.2 Result of Corner Operation  ![Corner-SetOffsetOrientation/(-1,-1/)](images/CGM_corner_minus1_minus1.png)

SetOffsetOrientation(-1,-1) | SetOffsetOrientation(1,-1)  | SetOffsetOrientation(1,-1)
```vbscript
SetCircleMode(Direct) | SetCircleMode(Direct) | SetCircleMode(Complementary)

```

**Merging the created corner with input wires** The created corner can be assembled or not with one input body or both input bodies. The input bodies are trimmed for this operation.  Fig.3 Merging the corner with the input wires
you get this result: Fig.2 Result of Corner Operation  ![Corner-SetOffsetOrientation/(-1,-1/)](images/CGM_corner_minus1_minus1.png)
SetOffsetOrientation(-1,-1) | SetOffsetOrientation(1,-1)  | SetOffsetOrientation(1,-1)
```vbscript
SetCircleMode(Direct) | SetCircleMode(Direct) | SetCircleMode(Complementary)
SetOffsetOrientation(1,-1)  and SetCircleMode(Direct) ![Corner-SetOffsetOrientation/(-1,-1/)](images/CGM_corner_minus1_minus1.png)

```

```vbscript
SetOffsetOrientation(-1,-1) | SetOffsetOrientation(1,-1)  | SetOffsetOrientation(1,-1)
```vbscript
SetCircleMode(Direct) | SetCircleMode(Direct) | SetCircleMode(Complementary)
SetOffsetOrientation(1,-1)  and SetCircleMode(Direct) ![Corner-SetOffsetOrientation/(-1,-1/)](images/CGM_corner_minus1_minus1.png)
SetOffsetOrientation(-1,-1) |  SetSupportTrimmingSideAndMode(0,1)
Result = Created corner + input wires  | SetOffsetOrientation(1,-1)
```

References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
```

[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)
History Version: **1** [Sept 2011] | Document created
---|---
