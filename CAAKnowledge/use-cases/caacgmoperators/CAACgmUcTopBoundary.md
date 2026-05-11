---
title: "Boundaries"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsBoundaryCreation", "CAAGMOperatorsInterfaces", "CATICGMHybBoundary"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopBoundary.htm"
converted: "2026-05-11T17:33:49.099805"
---

Boundaries  
---  
Use Case  
Abstract You can retrieve the boundaries of a skin or of a wire. The input body must not be closed. An initial cell can be specified as well as propagation rules.
    * Operator to be Used
    * Use Case Description
    * References  
---  
Operator to be Used To retrieve the boundaries of a shell or a wire, use the CATICGMHybBoundary operator in GMOperatorsInterfaces. This operator has to be created by the CATCGMCreateTopBoundary global function. Use Case Description The CAAGMOperatorsBoundaryCreation.m module in CAAGMOperatorsInterfaces.edu illustrates how to retrieve the boundaries of a shell made up of two domains. This use case loads the boundary.NCGM file which contains the input data and is delivered in the FunctionTests/InputData. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). With the input data below: Fig.1 Boundary Operation: Input Data (Initial Cell Highlighted) ![Boundary Operation: Input Data](images/CGM_boundary_0.png)  
---  
and the code below:
    
    CATICGMHybBoundary * pBoundOpe =::CATCGMCreateTopBoundary(piGeomFactory,
            &topdata;, 
            piInputBody,
            piDomain, // the domain
            piEdge, // the initial cell
            TANGENT_CONTINUITY);
    ...
    pBoundOpe->Run();
    CATBody * piBoundaryBody = pBoundOpe->GetResult();
    ...
    pBoundOpe->Release(); 
    pBoundOpe = NULL;
      
  
---  
you get this result: Fig.2 Result of Boundary Operation  ![Boundary Result: Tangent Continuity ](images/CGM_boundary_tgcont.png) 
---|---  
TANGENT_CONTINUITY |  NO_CONTINUITY  
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)  
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)  
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)  
History Version: **1** [Sept 2011] | Document created  
---|---
