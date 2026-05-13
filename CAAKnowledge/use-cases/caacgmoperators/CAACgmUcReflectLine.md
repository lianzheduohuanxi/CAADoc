---
title: "Extract a Face from a Solid"
category: "use case"
module: "CAACgmOperators"
tags: "["CATICGMTopReflectLine", "CAAGMOperatorsInterfaces", "CAAGMOperatorsReflectLine"]"
source_file: "Doc/online/CAACgmOperators/CAACgmUcReflectLine.htm"
converted: "2026-05-11T17:33:49.029685"
---
tags: ["CATICGMTopReflectLine", "CAAGMOperatorsInterfaces", "CAAGMOperatorsReflectLine"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcReflectLine.htmmd"
converted: "2026-05-11T17:33:49.029685"
Reflect Line

---
converted: "2026-05-11T17:33:49.029685"
Reflect Line
Use Case
Abstract There are two kinds of reflect lines:
    1. The conical reflect lines:
given a point O, conical reflect lines are the set of points P for which the tangent to the surface in each point P presents the same angle with OP.

    2. The cylindrical reflect lines:
given a direction D, cylindrical reflect lines are the set of points P for which the tangent to the surface in each point P presents the same angle with D.

    * Operator to be Used
    * Use Case Description
    * References
---
given a direction D, cylindrical reflect lines are the set of points P for which the tangent to the surface in each point P presents the same angle with D.
Operator to be Used To generate reflect lines on a surface, use the CATICGMTopReflectLine operator in GMOperatorsInterfaces. This operator has to be created using the CATCGMCreateTopReflectLine global function.  Use Case Description The CAAGMOperatorsReflectLine.m module in CAAGMOperatorsInterfaces.edu framework illustrates how create reflect lines on a surface. This use case creates its own input data. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). Case 1: Conical Reflect Line with 140 Degree Angle With the input data below Fig.1 Reflect Line Inputs: surface, point  ![Reflect line: Input Data](images/CGM_reflect_line_0.png)

---
Operator to be Used To generate reflect lines on a surface, use the CATICGMTopReflectLine operator in GMOperatorsInterfaces. This operator has to be created using the CATCGMCreateTopReflectLine global function.  Use Case Description The CAAGMOperatorsReflectLine.m module in CAAGMOperatorsInterfaces.edu framework illustrates how create reflect lines on a surface. This use case creates its own input data. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). Case 1: Conical Reflect Line with 140 Degree Angle With the input data below Fig.1 Reflect Line Inputs: surface, point  ![Reflect line: Input Data](images/CGM_reflect_line_0.png)
and the code below:

    CATICGMTopReflectLine *pConicalReflectLineOp = CATCGMCreateTopReflectLine( pGeomFactory, &topdata;,
                      pSkin, pOriginBody, 140*CATDegreeToRadian);

    ...
and the code below:
CATICGMTopReflectLine *pConicalReflectLineOp = CATCGMCreateTopReflectLine( pGeomFactory, &topdata;,
pSkin, pOriginBody, 140*CATDegreeToRadian);
    pConicalReflectLineOp->Run(#);
    CATBody * pConicalReflectLineBody = pConicalReflectLineOp->GetResult(#);
    pConicalReflectLineOp->Release(#);
    pConicalReflectLineOp = 0;

---
pConicalReflectLineOp->Release(#);
pConicalReflectLineOp = 0;
you get this result: Fig.2 Conical Reflect Line Result  ![Conical Reflect Line Result](images/CGM_reflect_line_1.png)

---
you get this result: Fig.2 Conical Reflect Line Result  ![Conical Reflect Line Result](images/CGM_reflect_line_1.png)
```vbscript
Case 2: Cylindrical Reflect Line with 40 Degree Angle with x Axis With the same input data and the code below:

```

    CATMathDirection ReflectDir( 1, 0, 0);
    CATICGMTopReflectLine *pCylReflectLineOp = CATCGMCreateTopReflectLine( pGeomFactory, pSkin,
                          ReflectDir, 40*CATDegreeToRadian, &topdata;);

    ...
CATMathDirection ReflectDir( 1, 0, 0);
CATICGMTopReflectLine *pCylReflectLineOp = CATCGMCreateTopReflectLine( pGeomFactory, pSkin,
ReflectDir, 40*CATDegreeToRadian, &topdata;);
    pCylReflectLineOp->Run(#);
    CATBody * pCylReflectLineBody = pCylReflectLineOp->GetResult(#);
    pCylReflectLineOp->Release(#);
    pCylReflectLineOp = 0;

---
pCylReflectLineOp->Release(#);
pCylReflectLineOp = 0;
you get this result: Fig.3 Cylindrical Reflect Line Result  ![Conical Reflect Line Result](images/CGM_reflect_line_2.png)

---
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)
History Version: **1** [Nov 2011] | Document created
---|---
