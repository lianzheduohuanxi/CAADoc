---
```vbscript
title: "How to Use Geometric Operators"
category: "technical article"
module: "CAACgmModel"
tags: ["CATICGMProjectionCrvSur", "CATICGMProjectionPtSur", "CATICGMConfusionPtOnSurPtOnSur", "CATICGMDistanceMinPtSur", "CATICGMIntersectionSurSur", "CATICGMDistanceMinPtCrv", "CATICGMProjectionPtCrv", "CATICGMIntersectionCrvCrv", "CATICGMContainer", "CATICGMInclusionPtCrv", "CATICGMMassProperties1D", "CATICGMDistanceMinCrvCrv", "CATICGMLocalAnalysis1D", "CATIA", "CATICGMConfusionPtOnCrvPtOnCrv", "CATICGMInclusionPtSur", "CATICGMIntersectionCrvSur", "CATICGMReflectCurve", "CATICGMLocalAnalysis2D", "CATICGMEdgeCurveComputation"]
source_file: "Doc/online/CAACgmModel/CAACgmUcGMModelOpeOverw.htm"
converted: "2026-05-11T17:33:48.309647"
```

---
# How to Use Geometric Operators  

---  
Technical Article  
## Abstract

Geometric operators are transient objects that allow you to create new objects from existing ones or to analyze them. These operators all follow the same scheme which is described in this article.
    * Introduction
    * How to Create and Use a Geometric Operator
      * The BASIC Mode
      * The ADVANCED Mode
    * How to Delete a Geometric Operator
    * In Short
    * References  
---  
## Introduction

Using geometric operators is an easy way to create or analyze geometric objects. While the geometric objects provide basic services, that are easily computed by the objects themselves, the geometric operators do more complex operations using advanced mathematics tools. As an example, evaluations from parameters to Cartesian coordinates is offered by the geometric curve or surface, whereas the torsion or curvature are computed by a geometric operator.

Using geometric operators is an easy way to create or analyze geometric objects. While the geometric objects provide basic services, that are easily computed by the objects themselves, the geometric operators do more complex operations using advanced mathematics tools. As an example, evaluations from parameters to Cartesian coordinates is offered by the geometric curve or surface, whereas the torsion or curvature are computed by a geometric operator.
All these operators never modify the input objects, they create new ones.

The geometric operators work inside one geometric container: the input and output objects must belong to the same geometric container.

Here are some examples of operators creating geometric objects:

    * Intersection between: 
      * Two curves (`CATICGMIntersectionCrvCrv`).
      * Two surfaces (`CATICGMIntersectionSurSur`).
      * A curve and a surface (`CATICGMIntersectionCrvSur`).
    * Projection of: 
      * A curve on a surface (`CATICGMProjectionCrvSur`).
      * A point on a curve (`CATICGMProjectionPtCrv`) or a surface (`CATICGMProjectionPtSur`).
    * Creation of reflect lines (`CATICGMReflectCurve`).
    * Creation of edge curves (`CATICGMEdgeCurveComputation`).

Here are some examples of operators dedicated to geometric analysis:

    * Confusion of: 
      * Two points of a curve (`CATICGMConfusionPtOnCrvPtOnCrv`).
      * Two points of a surface (`CATICGMConfusionPtOnSurPtOnSur`).
    * Inclusion of: 
      * A point on a curve (`CATICGMInclusionPtCrv`).
      * A point on a surface (`CATICGMInclusionPtSur`).
    * Minimum distance between: 
      * Two curves (`CATICGMDistanceMinCrvCrv`).
      * A point and a curve (`CATICGMDistanceMinPtCrv`).
      * A point and a surface (`CATICGMDistanceMinPtSur`).
    * Local analysis of a point on a curve (`CATICGMLocalAnalysis1D`), or a surface (`CATICGMLocalAnalysis2D`).
    * Global analysis of a point a a curve (`CATICGMMassProperties1D`).

The geometric operators are generic: the `CATICGMIntersectionCrvSur` operator, for example, computes the intersection of any type of curves with any type of surfaces.
## How to Create and Use a Geometric Operator

The geometric operators are generic: the `CATICGMIntersectionCrvSur` operator, for example, computes the intersection of any type of curves with any type of surfaces.
All the geometric operators are based on the same scheme. The geometric operator instances, created by a global function (CATCGMCreate...), are transient (that is to say, they are not streamed when streaming the geometric factory). They are used to declare an operation, to run it, and to retrieve the resulting objects.

The geometric operators can be used in two modes, BASIC (the default mode) or ADVANCED.

    * In the BASIC mode, data given when creating the operator is sufficient to execute it, and the operation is automatically run.
    * In the ADVANCED mode, the operator can be tuned after its creation with advanced options. You have then to explicitly ask for its execution. In any cases, the resulting objects are not created during the execution step. They are created when you ask for them, by calling the `GetXxx` methods. These methods are often presented as iterators and the following methods are provided: 
      * A method to retrieve the number of solutions.
      * An initialization of the iterator.
      * A method to increment the iterator.
      * A method to retrieve (and, hence create) the geometric result.
### The BASIC Mode

To operate in this mode, you must:

To operate in this mode, you must:
    1. Create the operator with the appropriate global function (`for example CATCGMCreateIntersection`), and specify the BASIC mode (or without specifying any mode: by default, the operator is created with the BASIC mode). The global function executes the requested operation and returns the corresponding operator instance.
    2. Get the result(s)
    3. Delete the operator instance (see How to Delete a Geometric Operator).

    **//  creation and run**
1. Create the operator with the appropriate global function (`for example CATCGMCreateIntersection`), and specify the BASIC mode (or without specifying any mode: by default, the operator is created with the BASIC mode). The global function executes the requested operation and returns the corresponding operator instance.
2. Get the result(s)
3. Delete the operator instance (see How to Delete a Geometric Operator).
    CATICGMIntersectionCrvSur* pIntOp = **::CATCGMCreateIntersection**(
                           piGeomFactory,   // geometric factory 
                           piLine,          // geometric line
                           piCylinder,      // geometric cylinder

                           **BASIC**);          // the mode (default value)
    ...
piGeomFactory,   // geometric factory
piLine,          // geometric line
piCylinder,      // geometric cylinder
    CATLONG32 nbPoints = pIntOp->GetNumberOfPoints();

    ...

The `CATICGMContainer::Remove` method removes geometric objects from the geometry factory. Any object which is not removed is streamed when the factory is streamed. When using geometric operators, you will usually have to remove unnecessary objects by using the `CATICGMContainer::Remove` method.

**Note** : Although geometric objects are handled by the mean of interfaces, such as `CATCartesianPoint`, `CATLine`, or `CATBody`, the pointers on these objects must not be released. In fact, they are released at the closure of the factory (the `CATCloseCGMContainer` global function).
### The ADVANCED Mode

The `CATICGMContainer::Remove` method removes geometric objects from the geometry factory. Any object which is not removed is streamed when the factory is streamed. When using geometric operators, you will usually have to remove unnecessary objects by using the `CATICGMContainer::Remove` method.
This mode can be used when you want to set parameters (for example limits on the geometry), or run again an operator with different input data.

To operate in this mode, you have to:

    1. Create the operator with the appropriate global function (`for example CATCGMCreateIntersection`), and specify the ADVANCED mode. The global function returns the corresponding operator instance, but does not run the operation.
    2. Specify additional information or advanced options to the operator by calling one of its `SetXxx` methods.
    3. Execute the operation: `Run` method.
    4. Get the result with the desired iterator.
    5. Optionally, set new options, run again the operator, and retrieve the new results.
    6. Remove the operator instance from the memory (see How to Delete a Geometric Operator).

    CATICGMIntersectionCrvSur* pIntOp = **::CATCGMCreateIntersection**(
                                    piGeomFactory,    // geometric factory
                                    piLine,           // geometric line
                                    piCylinder,       // geometric cylinder

                                    **ADVANCED**);        // MODE

    // set  limits. These limits were previously defined or computed
piLine,           // geometric line
piCylinder,       // geometric cylinder
    pIntOp->**SetLimits**(crvLimits);

    // run
    pIntOp->**Run**();

    // set another line and new limits

pIntOp->**Run**();
    pIntOp->**SetCurve**(piNewLine);    // piNewLine was previously created
    pIntOp->SetLimits(newCrvLimits); // newCrvLimits was previously defined

    // run again 
pIntOp->**SetCurve**(piNewLine);    // piNewLine was previously created
pIntOp->SetLimits(newCrvLimits); // newCrvLimits was previously defined
    pIntOp->**Run**();

    // get the results
pIntOp->**Run**();
    nbPoints = pIntOp->GetNumberOfPoints();
    cout << " Number of intersection points: "<< nbPoints << endl;
    long nbCurves= pIntOp->GetNumberOfCurves();
    cout << "Number of intersection curves: "<< nbCurves << endl;

## How to Delete a Geometric Operator

cout << " Number of intersection points: "<< nbPoints << endl;
long nbCurves= pIntOp->GetNumberOfCurves();
cout << "Number of intersection curves: "<< nbCurves << endl;
Geometric operators should be deleted by using the **Release** method.

    CATICGMIntersectionCrvSur* pIntOp = **::CATCGMCreateIntersection**(
                                    piGeomFactory,    // geometric factory
                                    piLine,           // geometric line
                                    piCylinder,       // geometric cylinder

                                    **ADVANCED**);        // MODE
    ...
    **// delete the operator**
    **pIntOp- >Release();
    pIntOp=NULL;**
## In Short

    * The geometric operators are transient objects used to create or analyze geometric objects. They do not modify the input operands.
    * All the geometric operators are based on the same scheme: creation, optionally set of advanced options, run, read of the results, deletion. They work inside one container.
## References

[1] |  [The Objects of CATIA Geometric Modeler](CAACgmTaGobGeoObjects.md)  
---|---  
[2] |  [The Curves of CATIA Geometric Modeler](CAACgmTaGobCurves.md)  
[3] |  [The Surfaces of CATIA Geometric Modeler](CAACgmTaGobSurfaces.md)  
[4] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
## History

Version: **1** [Jan 2007] | Document created  
---|---
