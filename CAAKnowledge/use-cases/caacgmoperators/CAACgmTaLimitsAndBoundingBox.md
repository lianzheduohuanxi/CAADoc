---
```vbscript
title: "Limits and Bounding Boxes of Geometrical Objects "
category: "use-case"
module: "CAACgmOperators"
tags: ["CATICGMProjectionPtCrv", "CATICGMInclusionPtCrv", "CATICGMInclusionPtSur", "CATICGMProjectionCrvSur", "CATICGMTopExtrapolWireOpe", "CATICGMIntersectionCrvSur", "CATICGMDistanceMinPtSur", "CATICGMReflectCurve", "CATICGMIntersectionSurSur", "CATICGMEdgeCurveComputation", "CATICGMDistanceMinCrvCrv", "CATICGMTopSkin", "CATICGMDistanceMinPtCrv"]
source_file: "Doc/online/CAACgmOperators/CAACgmTaLimitsAndBoundingBox.htm"
converted: "2026-05-11T17:33:48.626586"
```

---
tags: ["CATICGMProjectionPtCrv", "CATICGMInclusionPtCrv", "CATICGMInclusionPtSur", "CATICGMProjectionCrvSur", "CATICGMTopExtrapolWireOpe", "CATICGMIntersectionCrvSur", "CATICGMDistanceMinPtSur", "CATICGMReflectCurve", "CATICGMIntersectionSurSur", "CATICGMEdgeCurveComputation", "CATICGMDistanceMinCrvCrv", "CATICGMTopSkin", "CATICGMDistanceMinPtCrv"]
source_file: "Doc/online/CAACgmOperators/CAACgmTaLimitsAndBoundingBox.htm"
converted: "2026-05-11T17:33:48.626586"
Limits and Bounding Boxes of Geometrical Objects  

---  
converted: "2026-05-11T17:33:48.626586"
Limits and Bounding Boxes of Geometrical Objects
Technical Article  
Abstract Geometrical objects such as curves and surfaces are constructed which initial limits which can be modified afterwards. Modifying limits can be a matter of troubles if the concepts behind limits are not fully understood. Bounding boxes (CATMathBox) are mathematical objects computed with respect to limits. This article explains how to deal with limits and bounding boxes.

    * Different Kinds of Limits
    * Dealing with Limits
    * Manipulating Maximum Limits
    * Bounding Boxes of Curves and Surfaces
      * External or Global Bounding Box
      * Internal Bounding Box
      * Accuracy of Bounding Box Computation
    * In Short  
---  
Different Kinds of Limits Curves and surfaces have two types of limits: 
    1. the maximum limits, outside of which no valid topology can be created. These limits are the ones computed at creation. Creating or extending a topology beyond the geometry maximum limits is not permitted. The [Data Checker](CAACgmTaTopDataChecker.md) detects such abnormalities. In order to achieve topology extension, operators dedicated to extrapolation (for example CATICGMTopExtrapolWireOpe) can modify the maximum limits of the underlying geometry. The maximum limits are described by the `CATCrvLimit` class. 
    2. the current limits which are limits which have been redefined after creation. Their purpose is to restrict the geometry to be taken into account for an operation. Current limits are also handled by the `CATCrvLimit` class and they must be created within the range of maximum limits.
Dealing with Limits When dealing with curves and surfaces, the initial or maximum limits may not suit your application needs, just because your application has to run on a restricted portion of the geometries.  Fig.1 Computing the minimum distance between two curves with maximum limits and restricted portion of the geometries ![DistanceMin before SetLimits](images/CGM_curvelimit_0.png)  

Different Kinds of Limits Curves and surfaces have two types of limits:
1. the maximum limits, outside of which no valid topology can be created. These limits are the ones computed at creation. Creating or extending a topology beyond the geometry maximum limits is not permitted. The [Data Checker](CAACgmTaTopDataChecker.md) detects such abnormalities. In order to achieve topology extension, operators dedicated to extrapolation (for example CATICGMTopExtrapolWireOpe) can modify the maximum limits of the underlying geometry. The maximum limits are described by the `CATCrvLimit` class.
2. the current limits which are limits which have been redefined after creation. Their purpose is to restrict the geometry to be taken into account for an operation. Current limits are also handled by the `CATCrvLimit` class and they must be created within the range of maximum limits.
Dealing with Limits When dealing with curves and surfaces, the initial or maximum limits may not suit your application needs, just because your application has to run on a restricted portion of the geometries.  Fig.1 Computing the minimum distance between two curves with maximum limits and restricted portion of the geometries ![DistanceMin before SetLimits](images/CGM_curvelimit_0.png)
CASE A  
Curve in yellow and curve in green  
with their initial or maximum limits:  
Minimum distance is 0 | CASE B  
Portion of the yellow curve to be taken into  
account for a new operation  
Minimum distance is > 0  
To do this, you must use the `SetLimits` method which is provided by some operators. Operators such as:

    * CATICGMDistanceMinPtCrv
    * CATICGMDistanceMinCrvCrv
    * CATICGMDistanceMinPtSur
    * CATICGMProjectionPtCrv
    * CATICGMProjectionCrvSur
    * CATICGMInclusionPtSur
    * CATICGMInclusionPtCrv
    * CATICGMIntersectionCrvSur
    * CATICGMIntersectionSurSur
    * CATICGMReflectCurve
    * CATICGMEdgeCurveComputation
    * CATICGMTopSkin
provide a `SetLimits` method. To compute the minimum distance between two curves (Fig.1), you have to use the `CATICGMDistanceMinCrvCrv::SetLimits` method. **WARNING**   
Current limits should only be used as temporary repository in applications which control completely all the calls and operations onto geometry. Note that this is not the case when a geometric modeler operator is called as no operator guarantees the stability of current limits. Any call to a geometric modeler operator can potentially modify the current limits of the input curves or surfaces.   
Manipulating Maximum Limits The maximum limits remain data attached to the geometry. However, they can be modified by extrapolation operators (CATICGMTopExtrapolWireOpe for example). If a wire (topological object) relying on a curve is to be extended beyond the curve maximum limits, the operator extrapolates the curve. The maximum limits should be used with care for geometry which is essentially infinite. For example, the maximum limits of planes and lines extend across the entire model domain (see [About Model Size and Infinite](../CAACgmModel/CAACgmTaGobModelSizeAndInfinite.md)).  Bounding Boxes of Curves and Surfaces External or Global Bounding Box This is a bounding box encompassing the global geometry with its maximum limits or its current limits, depending of the limits which are passed to the `CATCurve::GetBox` (or `CATSurface::GetBox)`.   Fig. 2 Maximum and current external bounding boxes ![curve maximum bounding box](images/CGM_curve_maxBB_0.png)  

provide a `SetLimits` method. To compute the minimum distance between two curves (Fig.1), you have to use the `CATICGMDistanceMinCrvCrv::SetLimits` method. **WARNING**
Current limits should only be used as temporary repository in applications which control completely all the calls and operations onto geometry. Note that this is not the case when a geometric modeler operator is called as no operator guarantees the stability of current limits. Any call to a geometric modeler operator can potentially modify the current limits of the input curves or surfaces.
Manipulating Maximum Limits The maximum limits remain data attached to the geometry. However, they can be modified by extrapolation operators (CATICGMTopExtrapolWireOpe for example). If a wire (topological object) relying on a curve is to be extended beyond the curve maximum limits, the operator extrapolates the curve. The maximum limits should be used with care for geometry which is essentially infinite. For example, the maximum limits of planes and lines extend across the entire model domain (see [About Model Size and Infinite](../CAACgmModel/CAACgmTaGobModelSizeAndInfinite.md)).  Bounding Boxes of Curves and Surfaces External or Global Bounding Box This is a bounding box encompassing the global geometry with its maximum limits or its current limits, depending of the limits which are passed to the `CATCurve::GetBox` (or `CATSurface::GetBox)`.   Fig. 2 Maximum and current external bounding boxes ![curve maximum bounding box](images/CGM_curve_maxBB_0.png)
Curve max bounding box,   
corresponds to the creation limits.  
CATCurve::GetBox with max limits | Curve in yellow is a relimitation of the   
white curve (CATCurve::SetLimits)  
CATCurve::GetBox with new limits  
The `CATGeometry::GetBoundingBox` method can also be used to retrieve the external bounding box. It is based on the current limits. Internal Bounding Boxes The internal bounding boxes are mathematical boxes encompassing the internal arcs of a curve or the internal patches of a surface. The internal boxes can be computed:

    * either according to the maximum limits. In this case you have to use GetInternalMaxBoundingBox
    * or according to the current limits. In this case you have to use GetInternalBoundingBox. The resulting bounding boxes are the intersection between the global bounding box with current limits and the internal maximum bounding boxes.
white curve (CATCurve::SetLimits)
CATCurve::GetBox with new limits
The `CATGeometry::GetBoundingBox` method can also be used to retrieve the external bounding box. It is based on the current limits. Internal Bounding Boxes The internal bounding boxes are mathematical boxes encompassing the internal arcs of a curve or the internal patches of a surface. The internal boxes can be computed:
Fig.3 Internal bounding boxes ![curve maximum internal bounding boxes](images/CGM_curve_maxInternalBB_0.png)   

---  
The `CATGeometry::GetBoundingBox` method can also be used to retrieve the external bounding box. It is based on the current limits. Internal Bounding Boxes The internal bounding boxes are mathematical boxes encompassing the internal arcs of a curve or the internal patches of a surface. The internal boxes can be computed:
Fig.3 Internal bounding boxes ![curve maximum internal bounding boxes](images/CGM_curve_maxInternalBB_0.png)
Accuracy of Bounding Box Computation A bounding box is a portion of the 3D space that fully encompasses the geometry. It is an estimate of the space surrounding the geometry and is not intended to provide an accurate result. The computation is a trade-off between accuracy and performance that sacrifices the former. The bounding boxes of canonical shapes is generally tight to the object while the bounding box of the same shapes described in the form of Nurbs for example is not tight. In Short To | Use  

Fig.3 Internal bounding boxes ![curve maximum internal bounding boxes](images/CGM_curve_maxInternalBB_0.png)
Accuracy of Bounding Box Computation A bounding box is a portion of the 3D space that fully encompasses the geometry. It is an estimate of the space surrounding the geometry and is not intended to provide an accurate result. The computation is a trade-off between accuracy and performance that sacrifices the former. The bounding boxes of canonical shapes is generally tight to the object while the bounding box of the same shapes described in the form of Nurbs for example is not tight. In Short To | Use
Retrieve the CATMathBox of a Curve or Surface based on the maximum limits | 

    * `CATCurve::GetBox`, `CATSurface::GetBox` with maximum limits  
Accuracy of Bounding Box Computation A bounding box is a portion of the 3D space that fully encompasses the geometry. It is an estimate of the space surrounding the geometry and is not intended to provide an accurate result. The computation is a trade-off between accuracy and performance that sacrifices the former. The bounding boxes of canonical shapes is generally tight to the object while the bounding box of the same shapes described in the form of Nurbs for example is not tight. In Short To | Use
Retrieve the CATMathBox of a Curve or Surface based on the maximum limits |
Retrieve the CATMathBox of a Curve or Surface based on the current limits | 

    * `CATCurve::GetBox`, `CATSurface::GetBox` with current limits 
    * `CATGeometry::GetBoundingBox`  
Retrieve the CATMathBox of a Curve or Surface based on the maximum limits |
Retrieve the CATMathBox of a Curve or Surface based on the current limits |
Retrieve the internal CATMathBox of a Curve or Surface based on the maximum limits | 

    * `CATCurve::GetInternalMaxBoundingBox`, `CATSurface::GetInternalMaxBoundingBox`  
Retrieve the CATMathBox of a Curve or Surface based on the current limits |
Retrieve the internal CATMathBox of a Curve or Surface based on the maximum limits |
Retrieve the internal CATMathBox of a Curve or Surface based on the current limits | 

    * `CATCurve::GetInternalBoundingBox`, `CATSurface::GetInternalBoundingBox`  
Retrieve the internal CATMathBox of a Curve or Surface based on the maximum limits |
Retrieve the internal CATMathBox of a Curve or Surface based on the current limits |
Run an operator within a restricted range of limits | 

    * `_Operator_ ::SetLimits`  
Retrieve the internal CATMathBox of a Curve or Surface based on the current limits |
Run an operator within a restricted range of limits |
Modify the limits of a curve or surface | 

    * `CATCurve::SetLimits, CATSurface::SetLimits`  
Run an operator within a restricted range of limits |
Modify the limits of a curve or surface |
History Version: **1** [Sept 2012] | Document created  
