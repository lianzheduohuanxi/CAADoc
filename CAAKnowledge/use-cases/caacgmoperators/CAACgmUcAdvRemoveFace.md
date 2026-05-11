---
title: "Remove Faces from a Body"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CATICGMAdvancedRemoveFaceOpe", "CAAAdvRemoveFace", "CAAGMOperatorsAdvancedRemoveFace", "CAAGMOperatorsDoc"]
source_file: "Doc\online\CAACgmOperators\CAACgmUcAdvRemoveFace.htm"
converted: "2026-05-11T17:33:48.878453"
---

Removing Faces from a Body  
---  
Use Case  
Abstract You can remove a set of faces from a volume or a skin, this does not change the dimension of the body. The provided set of faces must be consistent as the operator does not propagate the faces to be removed. The operation completes when the body can be closed by extrapolation of the faces which are adjacent to the ones removed.
    * Operator to be Used
    * Use Case Description
    * References  
---  
Operator to be Used To remove a set of faces from a body, you can use the CATICGMAdvancedRemoveFaceOpe operator. Use Case Description The CAAGMOperatorsAdvancedRemoveFace.m module in CAAGMOperatorsInterfaces.edu illustrates how to remove a set of faces from a body. This use case must be run with the CAAAdvRemoveFace.NCGM file which is delivered in the FunctionTests/InputData folder of the CAAGMOperatorsDoc.edu framework. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.htm). With the input data below Fig.1 Remove Face Input data  ![Remove Face Input data](images/CGM_advRemoveFace_0.png)   
---  
and the code below:
    
    CATLISTP(CATFace) iFacesToRemove;
    ...
    CATICGMAdvancedRemoveFaceOpe * pOp = ::CATCGMCreateAdvancedRemoveFaceOpe(piGeomFactory, &topdata;, piInputBody);
    ...
    pOp->Append(iFacesToRemove);
    pOp->Run();
    CATBody * piResultBody = pOp->GetResult();  
  
---  
you get this result: Fig.2 Remove Face Output Body  ![Remove Face Input data](images/CGM_advRemoveFace_1.png)   
---  
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.htm)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.htm)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.htm)  
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.htm)  
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.htm)  
History Version: **1** [Feb 2014] | Document created  
---|---
