---
title: "Fillet: Untwist"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CATICGMDynAdvancedFillet", "CATICGMDynFillet", "CAATopAdvancedFillets", "CAAGMOperatorsAllFillets"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcFilletUntwist.htm"
converted: "2026-05-11T17:33:48.922069"
---

Fillet: Untwist  
---  
Use Case  
Abstract To create fillets, you must specify a list of radii as well as a list of edges to be filleted.   
```vbscript
For a constant radius, the list of radii contains a single item that you can apply to one or more edges.  
```

The fillet operation illustrated in this use case involves a twist scenario, which is automatically resolved by the CATICGMDynAdvancedFillet operator.
    * Operator to be Used
    * Use Case Description
    * References  
---  
Operator to be Used To create a fillet, use the CATICGMDynAdvancedFillet operator in GMOperatorsInterfaces. This operator has to be created using the CATCGMCreateDynAdvancedFillet global function. This operator offers more capabilities than CATICGMDynFillet, especially when the resulting body can be potentially twisted. Use Case Description The CAAGMOperatorsAllFillets.m module in CAAGMOperatorsInterfaces.edu framework illustrates how to create a fillet. This use case can be executed without arguments. The CAATopAdvancedFillets.cpp file of the CAAGMOperatorsAllFillets.m module contains the code which is specifically dedicated to this untwist scenario. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). In this example, a cube is created with one of its vertical edges filleted with a relatively small radius. Three of the edges on the cube's top face that are connected to the vertical fillet are then subsequently filleted with a relatively larger radius. This combination of an initial fillet with a small radius followed by a fillet with a larger radius causes a twist scenario, which is automatically resolved by the fillet operator. The figure below shows the input body for the fillet operation with the twist scenario.  Fig.1 Fillet (Untwist) Input  ![Fillet Untwist Inputs](images/CGM_fillet_untwist_0.png)   
---  
With the code below:
    
    CATLISTP(CATEdge) listEdges;
    listEdges.Append(pEdge1);
    listEdges.Append(pEdge2);
    listEdges.Append(pEdge3);
            
    double * ratio= NULL;
    CATDynFilletRadius * pRadius = new CATDynFilletRadius(3.5,    // radius value
                NULL,  
                ratio,  
                NULL);  
    ...
    CATLISTP(CATDynFilletRadius) listRadius;		
    listRadius.Append(pRadius);		
    CATDynEdgeFilletRibbon * pRibbon = new 	CATDynEdgeFilletRibbon(listEdges, listRadius);
    ...
    CATICGMDynAdvancedFillet * pFilletOp1 = CATCGMCreateDynAdvancedFillet(iFactory,iTopData,pBody2);
    pFilletOp1 ->Append(pRibbon);
    pFilletOp1->Run(); 
    CATBody * pResultBody = NULL;
    pResultBody = pFilletOp1->GetResult();
    pFilletOp1->Release();
    pFilletOp1 = NULL;
    ...
      
  
---  
you get this result: Fig.2 Fillet Untwist Result  ![Fillet Untwist Result](images/CGM_fillet_untwist_1.png)  
---  
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)  
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)  
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)  
History Version: **1** [Sept 2011] | Document created  
---|---
