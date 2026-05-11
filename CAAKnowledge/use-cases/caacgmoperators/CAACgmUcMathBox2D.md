---
title: "Retrieving the CATMathBox2D of An Edge or a Face "
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperators2DBoxComputation", "CAAGMOperatorsInterfaces", "CATICGM2DBoxComputation"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcMathBox2D.htm"
converted: "2026-05-11T17:33:48.991063"
---

Retrieving the CATMathBox2D of An Edge or a Face   
---  
Use Case  
Abstract The CATICGM2DBoxComputation operator allows you to retrieve the CATMathBox2D of a cell. 
    * Operator to be Used
    * Use Case Description
    * References  
---  
Operator to be Used To compute the CATMathBox2D of an edge or a face, use the CATICGM2DBoxComputation operator. This operator has to be created by using the CATCGMCreate2DBoxComputation global function. Use Case Description The CAAGMOperators2DBoxComputation.m module in CAAGMOperatorsInterfaces.edu  creates a CATICGM2DBoxComputation operator, runs it and retrieves the CATMathBox2D associated with an edge and a face.With the input file below: Fig.1 CATMathBox2D Input  ![CATMathBox2D input](images/CGM_mathBox2D_0.png)  
---  
and the code below: 
    
    CATFace *iFace = (CATFace *) piGeomFactory->FindObjectFromTag(9);
    CATEdge *iEdge = (CATEdge *) piGeomFactory->FindObjectFromTag(13);
    ...
    CATICGM2DBoxComputation *pComp2DBoxOp = NULL;
    pComp2DBoxOp = CATCGMCreate2DBoxComputation(piGeomFactory, &topdata;, iFace);
    ...
    pComp2DBoxOp->Run();
    
    CATSurLimits uvLimitsFace;
    pComp2DBoxOp->Get2DBox(uvLimitsFace);
    CATMathBox2D mathBox2DFace;
    uvLimitsFace.Get2DBox(mathBox2DFace);
    ...
      
  
---  
you retrieve a CATMathBox2D with the properties below: Low corner= ( 0 , 0 )  High corner= ( 9424.78 , 5000 )  The code below:
    
    CATFace *iFace = (CATFace *) piGeomFactory->FindObjectFromTag(9);
    CATEdge *iEdge = (CATEdge *) piGeomFactory->FindObjectFromTag(13);
    ...
    pComp2DBoxOp = CATCGMCreate2DBoxComputation(piGeomFactory, &topdata;, iEdge, iFace);
    pComp2DBoxOp->Run();
    
    CATSurLimits uvLimitsEdge;
    pComp2DBoxOp->Get2DBox(uvLimitsEdge);
    CATMathBox2D mathBox2DEdge;
    uvLimitsEdge.Get2DBox(mathBox2DEdge);
    ...
      
  
---  
generates the same result. References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)  
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)  
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)  
History Version: **1** [Feb 2014] | Document created  
---|---
