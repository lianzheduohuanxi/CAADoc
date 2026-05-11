---
title: "Fill"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CATICGMPowerFill", "CAAGMOperatorsPowerFill"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopPowerFill.htm"
converted: "2026-05-11T17:33:49.275425"
---

Fill  
---  
Use Case  
Abstract A fill is a two-dimensional region whose boundaries are defined by a set of closed wire bodies. By default, the fill satisfies G0 continuity with the wires, but if a corresponding set of support bodies is specified, G1 continuity with these bodies may be requested. 
    * Operator to be Used
    * Use Case Description
    * References  
---  
Operator to be Used To create a fill, use the CATICGMPowerFill operator found in GMOperatorsInterfaces. This operator has to be created by the CATCGMCreatePowerFill global function. Use Case Description The CAAGMOperatorsPowerFill.m module in CAAGMOperatorsInterfaces.edu illustrates how to create a fill. This use case is to be run with the PowerFill.NCGM input file which is delivered in CAAGMOperatorsInterfaces.edu/FunctionTests/InputData. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). With the input data below: Fig.1 Fill Operation: Input Data ![Fill inputs](images/CGM_fill_0.png)  
---  
and the code below:
    
    CATICGMPowerFill* pPowerFillOp =
    	CATCGMCreatePowerFill(piGeomFactory, &topdata;, wires, supports);
    ...
    double layDownTolerance = 0.001;
    pPowerFillOp->SetLayDownRequest(layDownTolerance);
    CATLONG32 whichWire = 1; 
    CATLONG32 transitionContinuity = 1;
    pPowerFillOp->SetTransitionContinuity(whichWire, transitionContinuity);
    pPowerFillOp->Run();
    CATBody* pResultBody = pPowerFillOp->GetResult();
    pPowerFillOp->Release(); 
    pPowerFillOp = NULL;
      
  
---  
you get this result: Fig.2 Fill Operation: Output Data ![Fill output](images/CGM_fill_1.png)  
---  
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)  
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)  
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)  
History Version: **1** [Feb 2013] | Document created  
---|---
