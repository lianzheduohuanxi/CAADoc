---
title: "Extract a Face from a Solid"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsExtractFace", "CAAGMOperatorsInterfaces", "CATICGMTopExtractFace"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcExtractFace.htm"
converted: "2026-05-11T17:33:48.913581"
---

Extract a Face from a Solid  
---  
Use Case  
Abstract You can create a 2D body from a face belonging to a solid. This very basic operation is illustrated in the CAAGMOperatorsExtractFace use case of the CAAGMOperatorsInterfaces.edu framework.  

    * Operator to be Used
    * Use Case Description
    * References  
---  
Operator to be Used To extract a face from a solid, use the CATICGMTopExtractFace operator in GMOperatorsInterfaces. This operator has to be created using the CATCGMCreateTopExtractFace global function.  Use Case Description The CAAGMOperatorsExtractFace.m module in CAAGMOperatorsInterfaces.edu framework illustrates how to extract a face. This use case creates its own input data. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). In this example, a cube is created and the bottom face is extracted. Fig.1 Extract Face Input  ![Extract Face Input](images/CGM_extract_face_0.png)  
---  
With the code below:
    
    CATICGMTopExtractFace* pExtractFaceOp = CATCGMCreateTopExtractFace(pGeomFactory, &topData;, pFace);
    ...
    pExtractFaceOp->Run();
    CATBody* pExtractFaceBody = pExtractFaceOp->GetResult();
    pExtractFaceOp->Release();
    pExtractFaceOp = NULL;
    ...
    CATLONG32 ioMaxDim = -1;
    CATBoolean ioHomogeneity = FALSE;
    pExtractFaceBody->GetCellsHighestDimension(ioMaxDim, ioHomogeneity);
    CATLISTP(CATCell) faces;
    pExtractFaceBody->GetAllCells(faces, 2);
    // We expect to obtain a skin body with one face
    if (2 != ioMaxDim || 1 != faces.Size())
     {
        ::CATCloseCGMContainer(pGeomFactory);
        return (1);
      }
    ...
      
  
---  
you get this result: Fig.2 Extract Face Result  ![Extract Face Result](images/CGM_extract_face_1.png)   
---  
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)  
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)  
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)  
History Version: **1** [Sept 2011] | Document created  
---|---
