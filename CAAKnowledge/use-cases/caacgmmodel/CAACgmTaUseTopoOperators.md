---
title: "How to Use the Topological Operators"
category: "technical article"
module: "CAACgmModel"
tags: ["CATICGMSolidPrimitive", "CAAGMOperatorsSpline", "CATICGMTopSkin", "CATICGMTopOperator", "CATICGMGeoToTopOperator"]
source_file: "Doc/online/CAACgmModel/CAACgmTaUseTopoOperators.md"
converted: "2026-05-11T17:33:48.060274"
---
# How to Use Topological Operators  
  
---  
Technical Article  
### Abstract

Build on a common scheme, the topological operators are transient objects used to create bodies.
    * Introduction
    * How to Create and Use a Topological Operator
    * How to Delete a Topological Operator 
    * In Short  
---  
### Introduction

Using topological operators is an easy way to create new consistent topological objects. There are two types of operators:

    1. The operators building topology from geometry. They derive from the `CATICGMGeoToTopOperator` class ( to create wire bodies or skin bodies) or from `CATICGMSolidPrimitive` (to create basic primitives such as cylinder, box, sphere).
    2. The operators only operating on topological objects. They derive from the `CATICGMTopOperator` class. Some of them allows you to create simple bodies (point, line and spline bodies), see the `CAAGMOperatorsSpline` use case.

All these operators follow the smart concept : they never modify the input bodies. They always create new topological objects, which share topological cells to reduce the model size.

The operators can log, under request, the follow-up of the faces and free edges from the input bodies to the resulting body. This data is written, under request, on a topological journal attached to each operator. Hence, the topological journal offers the developer the means to develop procedural applications, such as feature based modeling, but this point in not detailed here. See the dedicated use case in GMOperatorsInterfaces to have more information on the use of the journal.

The topological operators are transient objects used to define topological operations, and cannot be streamed.

The GMOperatorsInterfaces framework provides main topological operators. 
### How to Create and Use a Topological Operator

To use a topological operator, you must:

    1. Create it: 
       * By calling a global method.
       * During this step, the operation is not run.
    2. If needed, specify or modify additional information: 
       * During this step, the operation is not run.
    3. Run the operator: `Run`
       * The operation is run.
    4. Get the result: `GetResult`
       * The topological result is always retrieved as a `CATBody`.
    5. Delete the operator instance (see How to Delete a Topological Operator).
    
    // Create the operator
    CATICGMTopSkin * pSkinOp = ::CATCGMCreateTopSkin (piGeomFactory,
    &topdata,
    piPlane,
    nbPCurves, 
    aPCurves,
    aLimits,
    aOrientations);
    ...
    
    // Run the operator
    pSkinOp->Run();
    
    // Get the resulting body
    CATBody * piSkinBody = pSkinOp->GetResult();
    ...
### How to Delete a Topological Operator

Topological operators should be deleted by using the **Release** method.
    
    CATICGMTopSkin * pSkinOp = ::CATCGMCreateTopSkin (piGeomFactory,
    &topdata,
    piPlane, ...)
    ...
    // delete the operator
    pSkinOp **- >Release();  
    **pSkinOp **= NULL;**
### In Short

    * The topological operators are transient objects used to create on or more topological bodies. They follow the smart mechanism and do not modify the input operands.
    * All the topological operators are based on the same scheme: creation, specification od additional data if need be, run, read of the results, deletion. They work inside one container.
### History

Version: **1** [Jan 2007] | Document created  
---|---
