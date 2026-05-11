---
```vbscript
title: "Topology"
category: "use cases"
module: "CAACgmBase"
tags: ["CAAGMOperatorsInterfaces", "CATIA"]
source_file: "Doc/online/CAACgmBase/CAACgmTopologyHome.htm"
converted: "2026-05-11T17:33:47.855751"
```

---
tags: ["CAAGMOperatorsInterfaces", "CATIA"]
source_file: "Doc/online/CAACgmBase/CAACgmTopologyHome.htm"
converted: "2026-05-11T17:33:47.855751"
Geometric Modeler New V6 operators have been coexisting with V5 operators from V5R20 so that CAA developers can start migrating their V5 applications to V6 while remaining in V5. CAA developers are encouraged to migrate to these new interfaces. The use cases related to topology are delivered in the CAAGMOperatorsInterfaces.edu framework. Turn to [GM Operators](CAACgmGMOperatorsHome.md) to access the documentation associated with the use cases. |  Topology  

converted: "2026-05-11T17:33:47.855751"
Geometric Modeler New V6 operators have been coexisting with V5 operators from V5R20 so that CAA developers can start migrating their V5 applications to V6 while remaining in V5. CAA developers are encouraged to migrate to these new interfaces. The use cases related to topology are delivered in the CAAGMOperatorsInterfaces.edu framework. Turn to [GM Operators](CAACgmGMOperatorsHome.md) to access the documentation associated with the use cases. |  Topology
Technical Articles  

---  
[CGM Overview](../CAACgmTechArticles/CAACgmOverview.md) | A first glance at CATIA Geometric Modeler  
[ Topology Concepts](../CAATobTechArticles/TopoConcepts.md) | What is topology?  
[ The CGM Topological Model](../CAATobTechArticles/TopoModel.md) | How the topological concepts are implemented  
[ How to Associate Topology with Geometry](../CAATobTechArticles/TopoCreate.md) | Rules between topological and geometric objects  
[ The Boolean Operators](../CAATopTechArticles/TopoBoolean.md) | Best practices  
[ The CGM Journal](../CAATopTechArticles/TopoJournal.md) | The record of the topological modifications  
[ Journal methodology](../CAATopTechArticles/JournalMethodology.md) | Tips and tricks on how to create a journal.  
[The CGM Data Checker](../CAACgmTechArticles/CAACgmDataChecker.md)](../CAAAmtUseCases/CAAAmtPolynomAndFunction.md) | How to check CGM data consistency  
[ The Versioning of the Topological Operators](../CAATopTechArticles/TopoVersioning.md) | Migration principles  
[Top]  
Use Cases  
**Topological Objects** |    

  * [Using Topological Objects](../CAATobUseCases/CAATobTetra.md)

| A tetrahedron is created by using low level services. No operator is used.  

  * [ How to Revert the Orientation of an Edge](../CAATobUseCases/CAATopReverseEdgeOrientation.md)

| Explains how to modify some parameters in topological objects  

  * [ How to Scan an Edge Curve ](../CAATobUseCases/CAATopEdgeCurve.md)

| The geometry making up an edge curve is scanned by using a dedicated iterator.   
**Operators: Overview** |    

  * [Basic Topological Operators](../CAATopUseCases/CAATopSpline.md)

| Points, lines and splines are created by using basic operators.  

  * [Overview of the Topological Operators](../CAATopUseCases/CAATopOverview.md)

| A solid is created by chaining several operations such as solid primitive creation, extrusion, Boolean operations, filleting and shelling.  

  * [How to Use the Topological Journal](../CAATopUseCases/CAATopJournal.md)

| Reading the data and creating the journal of a sequence of topological operations  
**Operation List** |    

  * [How to Create a Point on a Wire](../CAABtoUseCases/CAABtoPointOnWire.md)

| How to use the CATTopComputePointOnWire operator.  

  * [How to Achieve a Given Geometric Continuity along a Wire](../CAAAdtUseCases/CAAAdtCleanCurve.md)

| How to use CATTopCleanCrvOperator to achieve a given geometric continuity along a wire.  

  * [How to create a single patch NURBS and dress it with a skin](../CAATopUseCases/CAATopNurbsSurfSinglePatch.md)

| Explains how to create a single patch NURBS surface and transform it into a skin.  

  * [How to create a multi patch NURBS and dress one patch of this surface with a skin](../CAATopUseCases/CAATopNurbsSurfMultiPatch.md)

| Explains how to create a multi patch NURBS surface and transform one of its patches into a skin.  

  * [How to create a geometric helix and convert it into a wire](../CAATopUseCases/CAATopCreateHelix.md)

| Explains how to create a geometric helix and transform it into a wire.  

  * [How to thread a rod](../CAAAdtUseCases/CAAAdtThreadOperator.md)

| Explains how to combine sweep and boolean operations to create a threading operator.  

  * [How to create fillets](../CAATopUseCases/CAATopAllFillets.md)

| Explains how to create fillets with constant and variable radii.  

  * [How to create a circle sweep -1](../CAAAdtUseCases/CAAAdtCircleSwTangSurRadius.md)

| Explains how to create a circle sweep with a one guide and a tangency surface.  

  * [How to create a circle sweep - 2](../CAAAdtUseCases/CAAAdtCircleSwThreeGuides.md)

| Explains how to create a circle sweep with three guides.  

  * [How to create a circle sweep - 3](../CAAAdtUseCases/CAAAdtCircleSwTwoGuidesRadiusLaw.md)

| Explains how to create a circle sweep with two guides and a radius law.  

  * [How to create a circle sweep - 4](../CAAAdtUseCases/CAAAdtCircleSwTwoGuidesTangSur.md)

| Explains how to create a circle sweep with two guides and a tangency surface.  

  * [How to use the Smoothing options in a sweep](../CAAAdtUseCases/CAAAdtSweepSmoothing.md)

| Explains how to create a segment sweep and act on the smoothing options to improve the quality of the sweep surface  
**Analysis and Data Checking** |    

  * [How to compute the area of a CATFace](../CAATopUseCases/CAATopProperties.md)

| Explains how to use the CATDynMassProperties3D class to compute the area of a face.  

  * [How to use the CATBodyChecker](../CAATopUseCases/CAATopBodyChecker.md)

| Explains how to check that a shell is valid:  no curvature radius less than resolution - no self-intersection  
**Copying and Transforming Objects** |    

  * [How to use the Smart Duplicator](../CAATobUseCases/CAATobSmartDuplicator.md)

| Explains how to touch a topology to modify it by using the CATSmartDuplicator operator.  
[Top]  
Quick Reference  
[ Where to Find What](../CAACgmQuickRefs/CAACgmIndex.md) | The index of the resources used in the use cases  
[ Frequently Asked Questions](../CAACgmQuickRefs/CAACgmFaq.md) | To help you to answer your questions  
Quick Reference
AdvancedTopologicalOpe Framework Reference | Interface and class reference for AdvancedTopologicalOpe  
BasicTopologicalOpe Framework Reference | Interface and class reference for BasicTopologicalOpe  
GMModelInterfaces Framework Reference | Interface and class reference for GMModelInterfaces  
GMOperatorsInterfaces Framework Reference | Interface and class reference for GMOperatorsInterfaces  
NewTopologicalObjects Framework Reference | Interface and class reference for NewTopologicalObjects  
TopologicalOperators Framework Reference | Interface and class reference for TopologicalOperators  

[Top]  
### History

NewTopologicalObjects Framework Reference | Interface and class reference for NewTopologicalObjects
TopologicalOperators Framework Reference | Interface and class reference for TopologicalOperators
Version: **1** [Jan 2000] | Document created  

[Top]  

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
