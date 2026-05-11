---
title: "Boolean Union"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CATICGMTopCompatible", "CAAGMOperatorsCompatible", "CATICGMDynBoolean"]
source_file: "Doc\online\CAACgmOperators\CAACgmUcBooleanUnion.htm"
converted: "2026-05-11T17:33:48.886943"
---

Boolean Union  
---  
Use Case  
Abstract A Boolean union results in a solid in which the unshared portions are unified and the shared portions cut away. The volumes making up the input bodies can be unified or not, depending on the operator. The CAAGMOperatorsCompatible use case illustrates how to perform a Boolean union with the CATICGMTopCompatible operator.
    * Operator to be Used
    * Use Case Description
    * References  
---  
Operator to be Used To perform a Boolean union between two solids, you can use: 
    1. either the CATICGMDynBoolean operator which is created by the CATCGMCreateDynBoolean global function. The third argument of the function must be set to CATBoolUnion. This operator unifies the input volumes.
    2. or the CATICGMTopCompatible operator which is created by the CATCGMCreateCompatibleForCGM global function. This operator does not unify the input volumes.
Use Case Description The CAAGMOperatorsCompatible.m module in CAAGMOperatorsInterfaces.edu performs a Boolean union of two solid cuboids. This use case creates the operator input data.  If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.htm). With the input bodies below: Fig.1 Boolean Union Between Two Solid Cuboids (CATICGMTopCompatible) ![Boolean Compatible: Inputs](images/CGM_boolean_union_comp_0.png)  
---  
and the code below:
    
    CATICGMTopCompatible * pBoolOpe =::CATCGMCreateCompatibleForCGM(piGeomFactory, &topdata;,
            piCuboidBody1,
            piCuboidBody2);
        ...
    pBoolOpe->Run();
    CATBody *piBoolBody=NULL;
    piBoolBody = pBoolOpe->GetResult(NULL);
    ...
    int nbVertices = 0;
    int nbEdges = 0;
    int nbFaces = 0;
    int nbVolumes = 0;
    // Check the number of volumes
    piBoolBody->GetCellNumbers( &nbVertices;, &nbEdges;, &nbFaces;, &nbVolumes; );
    if ( nbVolumes != 2 )
     {
            ::CATCloseCGMContainer(piGeomFactory);
            return (1);
     }
    ...
      
  
---  
you get this result: Fig.2 Boolean Union: Result (CATICGMTopCompatible) ![Boolean Union: Result](images/CGM_boolean_union_comp_1.png)  
---  
The result is a single body made up of 2 volumes, 12 faces, 24 edges and 16 vertices. This can be checked by using the `CATTopology::GetCellNumbers` method. References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.htm)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.htm)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.htm)  
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.htm)  
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.htm)  
History Version: **1** [Sept 2011] | Document created  
---|---
