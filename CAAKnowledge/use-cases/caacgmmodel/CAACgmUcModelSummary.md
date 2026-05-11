---
title: "GMOperators List of Use Cases"
category: "general"
module: "CAACgmModel"
tags: ["CAAGMModelPositionOpe", "CAAGMModelConvertSurfaceToC2", "CAAGMModelScanEdgeCurve", "CAAGMModelAnalysisOpe", "CAAGMModelTesMProcMain", "CAAGMModelEdgeCurveComputation", "CAAGMModelAttributeRead", "CAAGMModelConeCreation", "CAAGMModelConfusionOpe", "CAAGMModelNurbs", "CAAGMModelConvertCurveToC2", "CAAGMModelCreation", "CAAGMModelAttribute", "CAAGMModelDistanceMinOpe", "CAAGMModelGemBrowser", "CAAGMModelIntersectionOpe", "CAAGMModelTetra", "CAAGMModelGeometryCreation", "CAAGMModelIntersect", "CAAGMModelSmartDuplicator"]
source_file: "Doc\online\CAACgmModel\CAACgmUcModelSummary.htm"
converted: "2026-05-11T17:33:48.471605"
---

# GMModel List of Use Cases  
  
---  
  
The use cases illustrating the GMModelInterfaces capabilities are delivered in CAAGMModelInterfaces.edu 

Table.1  CAAGMModelInterfaces.edu: List of Use Cases Module | Purpose | Article  
---|---|---  
CAAGMModelAnalysisOpe.m | Compute the normal, curvature and torsion of point on a curve or surface.  |  [Analyzing the Parameters of a Point on a Curve ](CAACgmUcGMModelAnalysisOpe.htm) - [Analyzing the Parameters of a Point on a Surface ](CAACgmUcGMModelAnalysisOpe2.htm)  
CAAGMModelAttribute.m (V6) |  Implement an attribute.  |  [Creating an attribute](CAACgmUcGobAttCreation.htm)  
CAAGMModelAttributeCreation.m (V6) | Create an attribute. |  [Creating an attribute](CAACgmUcGobAttCreation.htm)  
CAAGMModelAttributeRead.m (V6) | Read an attribute. |  [Reading an Attribute](CAACgmUcGobAttRead.htm)  
CAAGMModelBodyFromLengthOnWire.m |  Create a topological point (CATBody) at some length along a wire (CATWire). |  [ Creating a Topological Point on a Wire at a Given Length from a Vertex](CAACgmUcTopGMModelPtOnWire.htm)  
CAAGMModelComputePointOnWire.m | Compute a mathematical point (CATMathPoint) on a wire (CATBody). Input parameter is a curvilinear ratio. |  [Compute a Point on a Wire](CAACgmUcBtoPointOnWire.htm)  
CAAGMModelConeCreation.m | Create a Frustum of a Right Circular Cone |  [Creating a Cone](CAACgmUcConeCreation.htm)  
CAAGMModelConfusionOpe.m | Check the confusion of points. |  [Checking the Confusion of Points on a Curve](CAACgmUcGMModelConfusionPtCrvOpe.htm) - [Checking the Confusion of Points on a Surface](CAACgmUcGMModelConfusionPtSurOpe.htm)  
CAAGMModelConvertCurveToC2.m | Break a C1 curve into C2 pieces. |  [Breaking a C2 Curve into C2 Pieces](CAACgmUcTopGMModelCurveC1ToC2.htm)  
CAAGMModelConvertSurfaceToC2.m | Break a C1 surface into C2 pieces. |  [Breaking a C1 Surface into C2 Pieces.](CAACgmUcTopGMModelSurfaceC1ToC2.htm)  
CAAGMModelConvertToCanonic.m | Convert a CATCurve to a CATLine. |  [ Extracting the Canonical Representation of a Curve](CAACgmUcGMModelConvertToCanonic.htm)  
CAAGMModelCreation.m (V6) | Create a Foreign Surface |  [Creating Foreign Surfaces](CAACgmUcGobForeign.htm)  
CAAGMModelCylinderCreation.m (V6) | Create a Cylinder |  [Creating a Cylinder](CAACgmUcCylinderCreation.htm)  
CAAGMModelDistanceMinOpe.m  
| Compute the minimum distance between a point and a surface, a point and a curve, two curves. |  [Computing the Minimum Distance between Two Geometries ](CAACgmUcGMModelDistanceMin.htm)  
CAAGMModelEdgeCurveComputation.m | Create an edge curve. |  [Creating or Computing an Edge Curve](CAACgmUcEdgeCurveCreation.htm)  
CAAGMModelForeign.m (V6) | Create a foreign mathematical function. |  [Foreign Mathematical Functions](CAACgmUcAmtForeign.htm)  
CAAGMModelGemBrowser.m (V6) | Browse an NCGM file. |  [Browsing the Geometry Container](CAACgmUcGemBrowser.htm)  
CAAGMModelGeometryCreation.m | Create Nurbs curves and surfaces as well as tabulated cylinder. |  SharedLib used by other modules to create basic Nurbs and tabulated cylinder  
CAAGMModelIntersect.m |  Intersect a curve with a surface. |  [Intersecting a Curve with a Surface](CAACgmUcGopIntersect.htm)  
CAAGMModelIntersectionOpe.m |  Intersect a curve with a surface, a surface with a surface, a curve with a curve. |  [IntersectIng a Curve and a Surface](CAACgmUcIntersectCrvSur.htm), [ Intersecting Surfaces](CAACgmUcIntersectSurSur.htm), [ Intersecting Curves](CAACgmUcIntersectCrvCrv.htm)  
CAAGMModelLifeCycleImplicit.m (V6) | Explain the life cycle of implicit objects. |  [Creating Implicit Objects](CAACgmUcGobLifeCycleImplicit.htm)  
CAAGMModelLifeCycleExplicit.m (V6) | Explain the life cycle of explicit objects. |  [Creating Explicit Objects](CAACgmUcGobLifeCycleExplicit.htm)  
CAAGMModelMakeLaws.m (V6) | Create composite laws. |  [Creating a Composite Law](CAACgmUcCompositeLaw.htm)  
CAAGMModelNurbs.m (V6) | Create Nurbs. |  [Using Nurbs](CAACgmUcGobNurbs.htm)  
CAAGMModelPositionOpe.m |  Determine the position of a point in a face or a volume. |  [Testing the Inclusion of a Point in a Volume or a Face.](CAACgmUcPtPosition.htm)  
CAAGMModelProjectionOpe.m | Project a point onto a surface, a curve onto a surface, a point onto a curve. |  [Projecting a Point onto a Surface](CAACgmUcProjPtSur.htm), [Projecting a Point onto a Curve](CAACgmUcProjPtCrv.htm), [Projecting a Curve onto a Surface](CAACgmUcProjCrvSur.htm)  
CAAGMModelSmartDuplicator.m (V6) | Remove a face from a skin by using the smart duplicator. |  [Using the Smart Duplicator](CAACgmUcTobSmartDuplicator.htm)  
CAAGMModelSphereCreation.m (V6) | Create a Sphere |  [Creating a Sphere](CAACgmUcSphereCreation.htm)  
CAAGMModelScanEdgeCurve.m (V6) | Scan an edge curve. |  [Scanning an Edge Curve](CAACgmUcTobEdgeCurve.htm)  
CAAGMModelTesMProcImpl.m | Implement a parallel tessellation operation. |  [How to Use MProc to Tessellate a Multi-Body Model  
CAAGMModelTesMProcMain.m |  Implement a parallel tessellation operation (main program) |  [How to Use MProc to Tessellate a Multi-Body Model  
CAAGMModelTetra.m | Use topological objects. |  [Using Topological Objects](CAACgmUcTobTetra.htm)  
CAAGMModelTorusCreation.m (V6) | Create a Torus |  [Creating a Torus](CAACgmUcTorusCreation.htm)  
CAAGMModelVolumeCreation.m | Create a volume from scratch. | Defines a function which is used in CAAGMModelPositionOpe.m to create a volume. For more information, you can refer to [Using Topological Objects](CAACgmUcTobTetra.htm) which is quite similar.  
History Version: **1** [Nov 2011] | Document created  
---|---
