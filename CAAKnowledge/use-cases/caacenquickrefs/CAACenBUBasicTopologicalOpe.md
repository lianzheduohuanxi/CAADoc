---
```vbscript
title: "BasicTopologicalOpe Changed Classes or Interfaces"
category: "use-case"
module: "CAACenQuickRefs"
tags: ["CATICGMTopLineTangentCrvCrvOperator", "CATICGMTopPolarExtremumOperator", "CATICGMTopSurToNurbsSurOperator", "CATICGMTopCrvToNurbsCrvOperator", "CATICGMTopPointOperator", "CATICGMTopCurveOperator", "CATICGMTopSplineOperator", "CATICGMTopHelixOperator", "CATICGMTopLineOperator", "CATICGMTopEdgePropagation", "CATICGMTopGeodesicLineOperator", "CATICGMComputePointOnWire", "CATICGMTopLineTangentPtCrvOperator", "CATICGMLengthFromBodyOnWire"]
source_file: "Doc/online/CAACenQuickRefs/CAACenBUBasicTopologicalOpe.htm"
converted: "2026-05-11T17:33:46.253424"
```

---
tags: ["CATICGMTopLineTangentCrvCrvOperator", "CATICGMTopPolarExtremumOperator", "CATICGMTopSurToNurbsSurOperator", "CATICGMTopCrvToNurbsCrvOperator", "CATICGMTopPointOperator", "CATICGMTopCurveOperator", "CATICGMTopSplineOperator", "CATICGMTopHelixOperator", "CATICGMTopLineOperator", "CATICGMTopEdgePropagation", "CATICGMTopGeodesicLineOperator", "CATICGMComputePointOnWire", "CATICGMTopLineTangentPtCrvOperator", "CATICGMLengthFromBodyOnWire"]
source_file: "Doc/online/CAACenQuickRefs/CAACenBUBasicTopologicalOpe.htm"
converted: "2026-05-11T17:33:46.253424"
BasicTopologicalOpe Changed Classes or Interfaces

---
converted: "2026-05-11T17:33:46.253424"
BasicTopologicalOpe Changed Classes or Interfaces
This table summarizes the CAA V5 BasicTopologicalOpe classes, interfaces, methods, and global functions that you may have used in your applications built on top of CAA V5 and that have been replaced in the [New V5R20 CGM Interfaces Layer](CAACenGobInterfacesMigration.md). For each of these:

  * If a one-to-one mapping exists to replacing classes, interfaces, methods, or global functions, links to these substitutes are listed and pointed to
  * Otherwise, an article is pointed to to explain how to replace or get rid of them.

This table summarizes the CAA V5 BasicTopologicalOpe classes, interfaces, methods, and global functions that you may have used in your applications built on top of CAA V5 and that have been replaced in the [New V5R20 CGM Interfaces Layer](CAACenGobInterfacesMigration.md). For each of these:
Class or Interface | Comment

CATComputePointOnWire | Not supported any longer.
**1 replacing class**
| Framework | Class or Interface
---|---
CATComputePointOnWire | Not supported any longer.
GMModelInterfaces | CATICGMComputePointOnWire
Class or Interface | Comment
CATLengthFromBodyOnWire | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATLengthFromBodyOnWire | Not supported any longer.
GMModelInterfaces | CATICGMLengthFromBodyOnWire
Class or Interface | Comment
CATTopCrvToNurbsCrvOperator | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATTopCrvToNurbsCrvOperator | Not supported any longer.
GMOperatorsInterfaces | CATICGMTopCrvToNurbsCrvOperator
Class or Interface | Comment
CATTopCurveOperator | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATTopCurveOperator | Not supported any longer.
GMOperatorsInterfaces | CATICGMTopCurveOperator
Class or Interface | Comment
CATTopEdgePropagation | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATTopEdgePropagation | Not supported any longer.
GMModelInterfaces | CATICGMTopEdgePropagation
Class or Interface | Comment
CATTopGeodesicLineOperator | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATTopGeodesicLineOperator | Not supported any longer.
GMOperatorsInterfaces | CATICGMTopGeodesicLineOperator
Class or Interface | Comment
CATTopHelixOperator | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATTopHelixOperator | Not supported any longer.
GMOperatorsInterfaces | CATICGMTopHelixOperator
Class or Interface | Comment
CATTopLineOperator | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATTopLineOperator | Not supported any longer.
GMOperatorsInterfaces | CATICGMTopLineOperator
Class or Interface | Comment
CATTopLineTangentCrvCrvOperator | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATTopLineTangentCrvCrvOperator | Not supported any longer.
GMOperatorsInterfaces | CATICGMTopLineTangentCrvCrvOperator
Class or Interface | Comment
CATTopLineTangentPtCrvOperator | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATTopLineTangentPtCrvOperator | Not supported any longer.
GMOperatorsInterfaces | CATICGMTopLineTangentPtCrvOperator
Class or Interface | Comment
CATTopPointOperator | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATTopPointOperator | Not supported any longer.
GMOperatorsInterfaces | CATICGMTopPointOperator
Class or Interface | Comment
CATTopPolarExtremumOperator | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATTopPolarExtremumOperator | Not supported any longer.
GMModelInterfaces | CATICGMTopPolarExtremumOperator
Class or Interface | Comment
CATTopSplineOperator | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATTopSplineOperator | Not supported any longer.
GMOperatorsInterfaces | CATICGMTopSplineOperator
Class or Interface | Comment
CATTopSurToNurbsSurOperator | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATTopSurToNurbsSurOperator | Not supported any longer.
GMOperatorsInterfaces | CATICGMTopSurToNurbsSurOperator
Global Functions | Signature | Comment
CATCreateComputePointOnWire | CATComputePointOnWire* CATCreateComputePointOnWire(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iWire,
double iValue) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATTopData* iTopData,
CATBody* iWire,
double iValue) |  Not supported any longer.
GMModelInterfaces | Global function | CATCGMCreateComputePointOnWire
CATCreateGeodesicLinePtPt | CATTopGeodesicPtPt* CATCreateGeodesicLinePtPt(CATGeoFactory* iFacto,
CATTopData* iData,
CATBody* iPtOrig,
CATBody* iPtFin,
CATBody* iShellSupport) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATBody* iPtOrig,
CATBody* iPtFin,
CATBody* iShellSupport) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateGeodesicLinePtPt
CATCreateTopCrvToNurbsCrvOperator | CATTopCrvToNurbsCrvOperator* CATCreateTopCrvToNurbsCrvOperator(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iWireBody,
CATLISTP_CATEdge_* iEdgeList) |  Not supported any longer.

**2 replacing methods** | Frameworks | Classes or Interfaces | Methods
---|---|---
CATTopData* iTopData,
CATBody* iWireBody,
CATLISTP_CATEdge_* iEdgeList) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopCrvToNurbsCrvOperator
GMOperatorsInterfaces | Global function | CATCGMCreateTopCrvToNurbsCrvOperator
CATCreateTopCrvToNurbsCrvOperator | CATTopCrvToNurbsCrvOperator* CATCreateTopCrvToNurbsCrvOperator(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iWireBody,
CATCell* iEdgeCell) |  Not supported any longer.

**2 replacing methods** | Frameworks | Classes or Interfaces | Methods
---|---|---
CATTopData* iTopData,
CATBody* iWireBody,
CATCell* iEdgeCell) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopCrvToNurbsCrvOperator
GMOperatorsInterfaces | Global function | CATCGMCreateTopCrvToNurbsCrvOperator
CATCreateTopGeodesicLineOperatorFromDirection | CATTopGeodesicLineOperator* CATCreateTopGeodesicLineOperatorFromDirection(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iSupport,
CATBody* iOriginPoint,
const CATMathVector& iDirection,
double iFirstLength,
double iSecondLength=0) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
const CATMathVector& iDirection,
double iFirstLength,
double iSecondLength=0) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopGeodesicLineOperatorFromDirection
CATCreateTopHelix | CATBody* CATCreateTopHelix(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iHelixAxis,
CATLONG32 HelixAxisOrientation,
CATBody* iHelixOrigin,
CATAngle iStartAngle,
CATAngle iEndAngle,
CATLength iPitch,
CATLONG32 iTrigoOrientation) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATAngle iEndAngle,
CATLength iPitch,
CATLONG32 iTrigoOrientation) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopHelix
CATCreateTopHelixOperator | CATTopHelixOperator* CATCreateTopHelixOperator(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iHelixAxis,
CATLONG32 iHelixAxisOrientation,
CATBody* iHelixOrigin,
CATAngle iStartAngle,
CATAngle iEndAngle,
CATLength iPitch,
CATLONG32 iTrigoOrientation) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATAngle iEndAngle,
CATLength iPitch,
CATLONG32 iTrigoOrientation) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopHelixOperator
CATCreateTopInfiniteLineFromDirection | CATBody* CATCreateTopInfiniteLineFromDirection(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iOriginPoint,
const CATMathVector& iDirection,
CATBoolean iIsSemiInfinite) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATBody* iOriginPoint,
const CATMathVector& iDirection,
CATBoolean iIsSemiInfinite) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopInfiniteLineFromDirection
CATCreateTopLineInfiniteOperatorFromDirection | CATTopLineOperator* CATCreateTopLineInfiniteOperatorFromDirection(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iOriginPoint,
const CATMathVector& iDirection,
CATBoolean iIsSemiInfinite) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATBody* iOriginPoint,
const CATMathVector& iDirection,
CATBoolean iIsSemiInfinite) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopLineInfiniteOperatorFromDirection
CATCreateTopLineNormalToShell | CATBody* CATCreateTopLineNormalToShell(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iFirstPoint,
CATBody* iShellOfPoint,
double iLength) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATBody* iFirstPoint,
CATBody* iShellOfPoint,
double iLength) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopLineNormalToShell
CATCreateTopLineOperatorNormalToShell | CATTopLineOperator* CATCreateTopLineOperatorNormalToShell(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iOriginPoint,
CATBody* iShellOfPoint,
double iLength) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATBody* iOriginPoint,
CATBody* iShellOfPoint,
double iLength) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopLineOperatorNormalToShell
CATCreateTopLineAngledTangentToWire | CATBody* CATCreateTopLineAngledTangentToWire(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iOriginPoint,
CATBody* iWire,
CATBody* iShellOfWire,
double iLength,
CATAngle iAngle) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATBody* iShellOfWire,
double iLength,
CATAngle iAngle) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopLineAngledTangentToWire
CATCreateTopLineOperatorAngledTangentToWire | CATTopLineOperator* CATCreateTopLineOperatorAngledTangentToWire(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iOriginPoint,
CATBody* iCurve,
CATBody* iShellOfCurve,
double iLength,
CATAngle iAngle) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATBody* iShellOfCurve,
double iLength,
CATAngle iAngle) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopLineOperatorAngledTangentToWire
CATCreateTopLineTangentToWire | CATBody* CATCreateTopLineTangentToWire(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iOriginPoint,
CATBody* iCurve,
double iLength) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATBody* iOriginPoint,
CATBody* iCurve,
double iLength) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopLineTangentToWire
CATCreateTopLineOperatorTangentToWire | CATTopLineOperator* CATCreateTopLineOperatorTangentToWire(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iOriginPoint,
CATBody* iCurve,
double iLength) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATBody* iOriginPoint,
CATBody* iCurve,
double iLength) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopLineOperatorTangentToWire
CATCreateTopLineFromDirection | CATBody* CATCreateTopLineFromDirection(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iOriginPoint,
const CATMathVector& iDirection,
double iLength) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATBody* iOriginPoint,
const CATMathVector& iDirection,
double iLength) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopLineFromDirection
CATCreateTopLineOperatorFromDirection | CATTopLineOperator* CATCreateTopLineOperatorFromDirection(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iOriginPoint,
const CATMathVector& iDirection,
double iLength) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATBody* iOriginPoint,
const CATMathVector& iDirection,
double iLength) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopLineOperatorFromDirection
CATCreateTopLineFromPoints | CATBody* CATCreateTopLineFromPoints(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iOriginPoint,
CATBody* iSecondPoint) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATTopData* iTopData,
CATBody* iOriginPoint,
CATBody* iSecondPoint) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopLineFromPoints
CATCreateTopLineOperatorFromPoints | CATTopLineOperator* CATCreateTopLineOperatorFromPoints(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iOriginPoint,
CATBody* iSecondPoint) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATTopData* iTopData,
CATBody* iOriginPoint,
CATBody* iSecondPoint) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopLineOperatorFromPoints
CATCreateTopLineTangentCrvCrvOperator | CATTopLineTangentCrvCrvOperator* CATCreateTopLineTangentCrvCrvOperator(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iWire1,
CATBody* iWire2,
CATBody* iPlane) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATBody* iWire1,
CATBody* iWire2,
CATBody* iPlane) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopLineTangentCrvCrvOperator
CATCreateTopLnTgtPtCrvOperator | CATTopLineTangentPtCrvOperator* CATCreateTopLnTgtPtCrvOperator(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iOriginPoint,
CATBody* iCurve,
CATBody* iPlane) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATBody* iOriginPoint,
CATBody* iCurve,
CATBody* iPlane) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopLnTgtPtCrvOperator
CATCreateTopPointOnSurface | CATBody* CATCreateTopPointOnSurface(CATGeoFactory* ioFactory,
CATTopData* iTopData,
CATBody* iSurface,
const CATMathVector& iDirection,
const double iGeodesicLength,
CATBody* iReferencePointOnSurface) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
const CATMathVector& iDirection,
const double iGeodesicLength,
CATBody* iReferencePointOnSurface) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopPointOnSurface
CATCreateTopPointUV | CATBody* CATCreateTopPointUV(CATGeoFactory* ioFactory,
CATTopData* iTopData,
const CATBody* iReferencePointOnSurface,
CATBody* iSurface,
const double iULength,
const double iVLength) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATBody* iSurface,
const double iULength,
const double iVLength) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopPointUV
CATCreateTopPointsTgtOnWire | CATBody* CATCreateTopPointsTgtOnWire(CATGeoFactory* ioFactory,
CATTopData* iTopData,
CATBody* iWire,
const CATMathVector& iTangent) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATTopData* iTopData,
CATBody* iWire,
const CATMathVector& iTangent) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopPointsTgtOnWire
CATCreateTopPointOnWire | CATBody* CATCreateTopPointOnWire(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iWire,
const double iLength,
CATBody* iRefPoint,
const CatTopPointLMode iLengthMode = CatTopPointLValue) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
const double iLength,
CATBody* iRefPoint,
const CatTopPointLMode iLengthMode = CatTopPointLValue) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopPointOnWire
CATCreateTopPointXYZ | CATBody* CATCreateTopPointXYZ(CATGeoFactory* iFactory,
CATTopData* iTopData,
double iX,
double iY,
double iZ) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
double iX,
double iY,
double iZ) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopPointXYZ
CATCreateTopPointOperator | CATTopPointOperator* CATCreateTopPointOperator(CATGeoFactory* iFactory,
CATTopData* iTopData) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
GMOperatorsInterfaces | Global function | CATCGMCreateTopPointXYZ
CATCreateTopPointOperator | CATTopPointOperator* CATCreateTopPointOperator(CATGeoFactory* iFactory,
CATTopData* iTopData) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopPointOperator
CATCreateTopPolarExtremumOperator | CATTopPolarExtremumOperator* CATCreateTopPolarExtremumOperator(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iWireBody,
CATBody* iPlanarShellBody,
CATBody* iPolarOriginVertexBody,
const CATMathVector& iPolarAxis,
const CatTopPolarExtremum iPolarExtremumExpected) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATBody* iPolarOriginVertexBody,
const CATMathVector& iPolarAxis,
const CatTopPolarExtremum iPolarExtremumExpected) |  Not supported any longer.
GMModelInterfaces | Global function | CATCGMCreateTopPolarExtremumOperator
CATCreateTopStableSpline | CATBody* CATCreateTopStableSpline(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATLONG32 iNbpts,
CATBody** iListOfPoints,
const CATMathVector* iTangents=NULL,
const CATMathVector* iCurvatures=NULL,
const CATLONG32* iImposition=NULL) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
const CATMathVector* iTangents=NULL,
const CATMathVector* iCurvatures=NULL,
const CATLONG32* iImposition=NULL) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopStableSpline
CATCreateTopSpline | CATBody* CATCreateTopSpline(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATLONG32 iNbpts,
CATBody** iListOfPoints,
const CATMathVector* iTangents=NULL,
const CATMathVector* iCurvatures=NULL,
const CATLONG32* iImposition=NULL) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
const CATMathVector* iTangents=NULL,
const CATMathVector* iCurvatures=NULL,
const CATLONG32* iImposition=NULL) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopSpline
CATCreateTopStableSplineOperator | CATTopSplineOperator* CATCreateTopStableSplineOperator(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATLONG32 iNbpts,
CATBody** iListOfPoints,
const CATMathVector* iTangents=NULL,
const CATMathVector* iCurvatures=NULL,
const CATLONG32* iImposition=NULL) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
const CATMathVector* iTangents=NULL,
const CATMathVector* iCurvatures=NULL,
const CATLONG32* iImposition=NULL) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopStableSplineOperator
CATCreateTopSplineOperator | CATTopSplineOperator* CATCreateTopSplineOperator(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATLONG32 iNbpts,
CATBody** iListOfPoints,
const CATMathVector* iTangents=NULL,
const CATMathVector* iCurvatures=NULL,
const CATLONG32* iImposition=NULL) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
const CATMathVector* iTangents=NULL,
const CATMathVector* iCurvatures=NULL,
const CATLONG32* iImposition=NULL) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopSplineOperator
CATCreateTopSurToNurbsSurOperator | CATTopSurToNurbsSurOperator* CATCreateTopSurToNurbsSurOperator(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iShellBody,
CATLISTP_CATFace_* iFaceList) |  Not supported any longer.

**2 replacing methods** | Frameworks | Classes or Interfaces | Methods
---|---|---
CATTopData* iTopData,
CATBody* iShellBody,
CATLISTP_CATFace_* iFaceList) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopSurToNurbsSurOperator
GMOperatorsInterfaces | Global function | CATCGMCreateTopSurToNurbsSurOperator
CATCreateTopSurToNurbsSurOperator | CATTopSurToNurbsSurOperator* CATCreateTopSurToNurbsSurOperator(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iSkinBody,
CATCell* iFaceCell) |  Not supported any longer.

**2 replacing methods** | Frameworks | Classes or Interfaces | Methods
---|---|---
CATTopData* iTopData,
CATBody* iSkinBody,
CATCell* iFaceCell) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateTopSurToNurbsSurOperator
GMOperatorsInterfaces | Global function | CATCGMCreateTopSurToNurbsSurOperator
