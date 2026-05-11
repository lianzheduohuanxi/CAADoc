---
title: "Creating a Silhouette"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsSilhouette", "CATICGMTopSilhouette", "CAAGMOperatorsInterfaces"]
source_file: "Doc\online\CAACgmOperators\CAACgmUcTopSilhouette.htm"
converted: "2026-05-11T17:33:49.314941"
---

Creating a Silhouette  
---  
Use Case  
Abstract A silhouette is a two-dimensional representation of the shape of body as projected orthographically upon a planar screen. Portions of the projection that miss the screen are trimmed at its boundary.
    * Operator to be Used
    * Use Case Description
    * References  
---  
Operator to be Used To create a silhouette, use the CATICGMTopSilhouette operator found in GMOperatorsInterfaces. This operator has to be created by the CATCGMCreateTopSilhouette global function. Use Case Description The CAAGMOperatorsSilhouette.m module in CAAGMOperatorsInterfaces.edu illustrates how to create a silhouette. This use case is to be run with the Silhouette.NCGM input file which is delivered in CAAGMOperatorsInterfaces.edu/FunctionTests/InputData. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.htm).  
  
With the input data below: Fig.1 Silhouette Operation: Input Data ![Silhouette Operation: Input data](images/CGM_silhouette_0.png)  
---  
and the code below:
    
    CATICGMTopSilhouette* pSilhouetteOp = CATCGMCreateTopSilhouette(pGeomFactory, &topdata;, pSolidBody);
    ...
    CATBoolean lightSourceInFront = TRUE;
    pSilhouetteOp->SetProjectionScreenForShadows(pProjectionScreen, lightSourceInFront);
    pSilhouetteOp->Run();
    CATBody * pShadowBody = pSilhouetteOp->GetResult();
    pSilhouetteOp->Release();
    pSilhouetteOp = NULL;
    ...  
  
---  
you get this result: Fig.2 Result of Silhouette Operation ![Silhouette Operation: Output data](images/CGM_silhouette_1.png)  
---  
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.htm)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.htm)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.htm)  
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.htm)  
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.htm)  
History Version: **1** [May 2012] | Document created  
---|---
