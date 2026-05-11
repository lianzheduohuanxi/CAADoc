---
```vbscript
title: "Creating a Non-Manifold Wire "
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsTopWireAssembly", "CAAGMOperatorsInterfaces", "CATICGMHybAssemble", "CATICGMHybProject"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopNonManifoldWire.htm"
converted: "2026-05-11T17:33:49.211399"
```

---
tags: ["CAAGMOperatorsTopWireAssembly", "CAAGMOperatorsInterfaces", "CATICGMHybAssemble", "CATICGMHybProject"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopNonManifoldWire.htm"
converted: "2026-05-11T17:33:49.211399"
Creating a Non-Manifold Wire

---
converted: "2026-05-11T17:33:49.211399"
Creating a Non-Manifold Wire
Use Case
Abstract Most operations can be performed on non-manifold bodies, but not all.  When creating an interactive command, it is recommended to allow the user to check whether he accepts to generate a non-manifold result. Here are examples of operations you cannot perform on non-manifold bodies:

    * extruding or filling a profile which has a closed portion as well as a free edge
    * joining a non-manifold body to another body.
Use Case
Abstract Most operations can be performed on non-manifold bodies, but not all.  When creating an interactive command, it is recommended to allow the user to check whether he accepts to generate a non-manifold result. Here are examples of operations you cannot perform on non-manifold bodies:
```vbscript
If the command cannot complete due to the non-manifold nature of the input bodies, it is necessary to remove some sub-elements in order to obtain appropriate manifold bodies. But the operation which consists in removing sub-elements can only be applied to manifold domains. If your body is not made up of correct manifold domains, you won't be able to clean or transform your initial body. Note that CGM services allow you to create non-manifold bodies while usually the interactive commands break the created bodies into appropriate domains. That way, the resulting bodies are non-manifold-like but contain sub-elements easy to be manipulated.  This use case illustrates how to create a non-manifold wire and project it onto a plane.

```

    * Operator to be Used
    * Use Case Description
    * References
---
```vbscript
If the command cannot complete due to the non-manifold nature of the input bodies, it is necessary to remove some sub-elements in order to obtain appropriate manifold bodies. But the operation which consists in removing sub-elements can only be applied to manifold domains. If your body is not made up of correct manifold domains, you won't be able to clean or transform your initial body. Note that CGM services allow you to create non-manifold bodies while usually the interactive commands break the created bodies into appropriate domains. That way, the resulting bodies are non-manifold-like but contain sub-elements easy to be manipulated.  This use case illustrates how to create a non-manifold wire and project it onto a plane.
Operator to be Used You can create a non-manifold wire by assembling lines using the CATICGMHybAssemble operator. This wire can be projected onto a surface by using the CATICGMHybProject operator. Use Case Description The CAAGMOperatorsTopWireAssembly.m module in CAAGMOperatorsInterfaces.edu illustrates how to create a non-manifold wire and project it onto a plane.If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). The code below creates a multi-domain wire from three lines:

    CATICGMHybAssemble* pHybOp = ::CATCGMCreateTopAssemble(piGeomFactory, &topdata;,&bodies;);
    if (NULL!=pHybOp)
```

      {
Operator to be Used You can create a non-manifold wire by assembling lines using the CATICGMHybAssemble operator. This wire can be projected onto a surface by using the CATICGMHybProject operator. Use Case Description The CAAGMOperatorsTopWireAssembly.m module in CAAGMOperatorsInterfaces.edu illustrates how to create a non-manifold wire and project it onto a plane.If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). The code below creates a multi-domain wire from three lines:
CATICGMHybAssemble* pHybOp = ::CATCGMCreateTopAssemble(piGeomFactory, &topdata;,&bodies;);
if (NULL!=pHybOp)
    pHybOp->Run();
    piAssembledBody = pHybOp->GetResult();
    pHybOp->Release();
    pHybOp = NULL;

      }

---
pHybOp = NULL;
you get this result: Fig.1 The non-manifold wire ![non manifold wire](images/CGM_nonManifold_0.png)

---
The created non-manifold wire can be projected onto the plane. References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)
History Version: **1** [Feb 2014] | Document created
---|---
