---
title: "AdvancedTopologicalOpe Changed Classes or Interfaces"
category: "general"
module: "CAACenQuickRefs"
tags: ["CATICGMThickenOp", "CATICGMTopologicalBlendCurve", "CATICGMTopSpine", "CATICGMTopBlend", "CATICGMTopMostContinuousGeoInWireOperator", "CATICGMTopSimilarCurve", "CATICGMTopCleanCrvOperator", "CATICGMTopShellOrientation", "CATICGMTopExtrapolWireOpe", "CATICGMTopologicalMatch", "CATICGMTopGeodesicPtPt", "CATICGMSkinExtrapolation", "CATICGMSketchGeodesic", "CATICGMTopologicalFill", "CATICGMGeometrySizeOptimization", "CATICGMFrFTopologicalSweep", "CATICGMSketchOperators", "CATICGMTopSweep"]
source_file: "Doc\online\CAACenQuickRefs\CAACenBUAdvancedTopologicalOpe.htm"
converted: "2026-05-11T17:33:46.211376"
---

AdvancedTopologicalOpe Changed Classes or Interfaces  
---  
This table summarizes the CAA V5 AdvancedTopologicalOpe classes, interfaces, methods, and global functions that you may have used in your applications built on top of CAA V5 and that have been replaced in the [New V5R20 CGM Interfaces Layer](CAACenGobInterfacesMigration.htm). For each of these:

  * If a one-to-one mapping exists to replacing classes, interfaces, methods, or global functions, links to these substitutes are listed and pointed to
  * Otherwise, an article is pointed to to explain how to replace or get rid of them.

Class or Interface | Comment  
---|---  
CATFrFTopologicalSweep | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMFrFTopologicalSweep  
Class or Interface | Comment  
CATGeodesicDistanceTool | Not supported any longer.  
**1 replacing function**  
| Framework | Function  
---|---  
GMOperatorsInterfaces | CATCGMCreateTopGeodesicDistanceTool  
Class or Interface | Comment  
CATGeometrySizeOptimization | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMGeometrySizeOptimization  
Class or Interface | Comment  
CATSketchGeodesic | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMSketchGeodesic  
Class or Interface | Comment  
CATSketchOperators | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMSketchOperators  
Class or Interface | Comment  
CATSkinExtrapolation | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMSkinExtrapolation  
Class or Interface | Comment  
CATThickenOp | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMThickenOp  
Class or Interface | Comment  
CATTopBlend | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMTopBlend  
Class or Interface | Comment  
CATTopCleanCrvOperator | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMTopCleanCrvOperator  
Class or Interface | Comment  
CATTopExtrapolWireOpe | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMTopExtrapolWireOpe  
Class or Interface | Comment  
CATTopGeodesicPtPt | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMTopGeodesicPtPt  
Class or Interface | Comment  
CATTopMostContinuousGeoInWireOperator | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMTopMostContinuousGeoInWireOperator  
Class or Interface | Comment  
CATTopShellOrientation | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMTopShellOrientation  
Class or Interface | Comment  
CATTopSimilarCurve | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMTopSimilarCurve  
Class or Interface | Comment  
CATTopSpine | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMTopSpine  
Class or Interface | Comment  
CATTopSweep | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMTopSweep  
Class or Interface | Comment  
CATTopologicalBlend | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMTopBlend  
Class or Interface | Comment  
CATTopologicalBlendCurve | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMTopologicalBlendCurve  
Class or Interface | Comment  
CATTopologicalFill | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMTopologicalFill  
Class or Interface | Comment  
CATTopologicalMatch | Not supported any longer.  
**1 replacing class**  
| Framework | Class or Interface  
---|---  
GMOperatorsInterfaces | CATICGMTopologicalMatch  
Global Functions | Signature | Comment  
CATCreateGeodesicPointDir | CATSketchGeodesic* CATCreateGeodesicPointDir(CATGeoFactory* iFactory,  
CATTopData* iData,  
CATBody* iSupportShell,  
CATFace* iFaceSupportPoint,  
CATSurParam* iParamPoint,  
CATMathVector* iTangent,  
CATPositiveLength iLength,  
CATSkillValue iMode = BASIC) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateGeodesicPointDir  
CATCreateTopBlend | CATTopBlend* CATCreateTopBlend(CATGeoFactory* iFactory,  
CATTopData* iTopData,  
const CATBody* iWire1,  
const CATBody* iWire2,  
const CATBody* iSupport1,  
const CATBody* iSupport2) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopBlend  
CATCreateTopGeodesicDistanceTool | CATDistanceTool* CATCreateTopGeodesicDistanceTool(CATGeoFactory* iGeoFactory,  
CATTopData* iData,  
CATOrientation iOrientation,  
CATCompositeLaw*iDistance) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopGeodesicDistanceTool  
CATCreateTopShellOrientation | CATTopShellOrientation* CATCreateTopShellOrientation(CATGeoFactory* iFactory,  
CATTopData* iData,  
CATBody* inputBody) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopShellOrientation  
CATCreateSkinExtrapolation | CATSkinExtrapolation* CATCreateSkinExtrapolation(CATGeoFactory* iFactory,  
CATTopData* iTopData,  
CATBody* iSkin,  
CATBody* iWireOnSkin) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateSkinExtrapolation  
CATCreateThickenOp | CATThickenOp* CATCreateThickenOp(CATGeoFactory* iFactory,  
CATTopData* iTopData,  
CATBody* iBody,  
double iOffset1,  
double iOffset2) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateThickenOp  
CATCreateTopCleanCrvOperator | CATTopCleanCrvOperator* CATCreateTopCleanCrvOperator(CATGeoFactory* iFactory,  
CATTopData* iTopData,  
CATBody* iWireBody) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopCleanCrvOperator  
CATCreateTopMostContinuousGeoInWireOperator | CATTopMostContinuousGeoInWireOperator* CATCreateTopMostContinuousGeoInWireOperator(CATGeoFactory*iFactory,  
CATTopData*iTopData,  
CATBody*iWireBody) |  Not supported any longer.  
**3 replacing methods** | Frameworks | Classes or Interfaces | Methods  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopMostContinuousGeoInWireOperator  
GMOperatorsInterfaces | Global function | CATCGMCreateTopMostContinuousGeoInWireOperator  
GMOperatorsInterfaces | Global function | CATCGMCreateTopMostContinuousGeoInWireOperator  
CATCreateTopMostContinuousGeoInWireOperator | CATTopMostContinuousGeoInWireOperator* CATCreateTopMostContinuousGeoInWireOperator(CATGeoFactory*iFactory,  
CATTopData*iTopData,  
CATBody*iWireBody,  
CATBody*iShellBody1,  
CATBody*iShellBody2) |  Not supported any longer.  
**3 replacing methods** | Frameworks | Classes or Interfaces | Methods  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopMostContinuousGeoInWireOperator  
GMOperatorsInterfaces | Global function | CATCGMCreateTopMostContinuousGeoInWireOperator  
GMOperatorsInterfaces | Global function | CATCGMCreateTopMostContinuousGeoInWireOperator  
CATCreateTopMostContinuousGeoInWireOperator | CATTopMostContinuousGeoInWireOperator* CATCreateTopMostContinuousGeoInWireOperator(CATGeoFactory*iFactory,  
CATTopData*iTopData,  
CATBody*iWireBody,  
CATBody*iShellBody) |  Not supported any longer.  
**3 replacing methods** | Frameworks | Classes or Interfaces | Methods  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopMostContinuousGeoInWireOperator  
GMOperatorsInterfaces | Global function | CATCGMCreateTopMostContinuousGeoInWireOperator  
GMOperatorsInterfaces | Global function | CATCGMCreateTopMostContinuousGeoInWireOperator  
CATCreateTopologicalBlend | CATTopologicalBlend*CATCreateTopologicalBlend(CATGeoFactory*iFactory,  
CATTopData* iTopData,  
const CATBody*iWire,  
const CATBody*iSupport) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopBlend  
CATCreateTopologicalBlend | CATTopologicalBlend*CATCreateTopologicalBlend(CATGeoFactory*iFactory,  
CATTopData*iTopData,  
const CATBody*iWire1,  
const CATBody*iWire2,  
const CATBody*iSupport1,  
const CATBody*iSupport2) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopBlend  
CATCreateTopologicalBlendCurve | CATTopologicalBlendCurve* CATCreateTopologicalBlendCurve(CATGeoFactory*iFactory,  
CATTopData* iData,  
CATBody*iWire1,  
CATBody*iWireParam1,  
CATBody*iWire2,  
CATBody*iWireParam2) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopologicalBlendCurve  
CATCreateTopologicalFill | CATTopologicalFill* CATCreateTopologicalFill(CATGeoFactory*iFactory,  
CATTopData* iTopData,  
CATLONG32 iNumberOfWires,  
const CATBody**iArrayOfWires) |  Not supported any longer.  
**2 replacing methods** | Frameworks | Classes or Interfaces | Methods  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopologicalFill  
GMOperatorsInterfaces | Global function | CATCGMCreateTopologicalFill  
CATCreateTopologicalFill | CATTopologicalFill* CATCreateTopologicalFill(CATGeoFactory*iFactory,  
CATTopData* iTopData,  
const ListPOfCATEdge*iListOfEdges,  
const ListPOfCATFace*iListOfFaces,  
const CATBody*iBody) |  Not supported any longer.  
**2 replacing methods** | Frameworks | Classes or Interfaces | Methods  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopologicalFill  
GMOperatorsInterfaces | Global function | CATCGMCreateTopologicalFill  
CATCreateTopologicalFill | CATTopologicalFill* CATCreateTopologicalFill(CATGeoFactory*iFactory,  
CATTopData* iTopData,  
CATLONG32 iNumberOfWires,  
const CATBody**iArrayOfBodyWires,  
const CATBody**iArrayOfBodySupports) |  Not supported any longer.  
**2 replacing methods** | Frameworks | Classes or Interfaces | Methods  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopologicalFill  
GMOperatorsInterfaces | Global function | CATCGMCreateTopologicalFill  
CATCreateTopologicalMatch | CATTopologicalMatch* CATCreateTopologicalMatch(CATGeoFactory* iFactory,  
CATTopData* iTopData,  
CATBody** iWire1,  
CATBody** iWire2,  
CATLONG32 iNbWires,  
CATBody* iSupport1,  
CATBody** iSupport2,  
CATSkillValue iMode = BASIC) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopologicalMatch  
CATCreateTopSimilarCurve | CATTopSimilarCurve* CATCreateTopSimilarCurve(CATGeoFactory* iFacto,  
CATTopData* iData,  
CATBody* iBaseCurve,  
CATBody* iInputCurve1=NULL,  
CATBody* iInputCurve2=NULL) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopSimilarCurve  
CATCreateTopSpine | CATTopSpine* CATCreateTopSpine(CATGeoFactory* iGeoFactory,  
CATTopData* iTopData,  
CATLISTP_CATGeometry_ & iProfiles) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopSpine  
CATCreateTopSweep | CATTopSweep* CATCreateTopSweep(CATGeoFactory* iGeoFactory,  
CATTopData* iData,  
CATBody* iCenterBody,  
CATGeometry* iCenterSupport,  
CATBody* iSpineBody,  
CATBody* iProfile) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopSweep  
CATCreateFrFTopologicalConicSweep | CATFrFTopologicalSweep* CATCreateFrFTopologicalConicSweep(CATGeoFactory* iFactory,  
CATTopData* iTopData,  
CATLISTP_CATGeometry_* iLimitGuides) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateFrFTopologicalConicSweep  
CATCreateFrFTopologicalCircleSweep | CATFrFTopologicalSweep* CATCreateFrFTopologicalCircleSweep(CATGeoFactory* iFactory,  
CATTopData* iTopData,  
CATLISTP_CATGeometry_* iLimitGuides) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateFrFTopologicalCircleSweep  
CATCreateFrFTopologicalSegmentSweep | CATFrFTopologicalSweep* CATCreateFrFTopologicalSegmentSweep(CATGeoFactory* iFactory,  
CATTopData* iTopData,  
CATLISTP_CATGeometry_* iLimitGuides) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateFrFTopologicalSegmentSweep  
CATCreateFrFTopologicalSweep | CATFrFTopologicalSweep* CATCreateFrFTopologicalSweep(CATGeoFactory* iFactory,  
CATTopData* iTopData,  
CATLISTP_CATGeometry_* iGuides,  
CATLISTP_CATGeometry_* iProfiles,  
CATFrFTopologicalSweepType iSweepType =CATFrFTopologicalSweepType_Std) |  Not supported any longer.  
**2 replacing methods** | Frameworks | Classes or Interfaces | Methods  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateFrFTopologicalSweep  
GMOperatorsInterfaces | Global function | CATCGMCreateFrFTopologicalSweep  
CATCreateFrFTopologicalSweep | CATFrFTopologicalSweep* CATCreateFrFTopologicalSweep(CATGeoFactory* iFactory,  
CATTopData* iTopData,  
CATBody* iGuide,  
CATBody* iProfile) |  Not supported any longer.  
**2 replacing methods** | Frameworks | Classes or Interfaces | Methods  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateFrFTopologicalSweep  
GMOperatorsInterfaces | Global function | CATCGMCreateFrFTopologicalSweep  
CATCreateTopSweepWireSkinCircleVariable | CATTopSweepWireSkinCircle* CATCreateTopSweepWireSkinCircleVariable(CATGeoFactory* iFactory,  
CATTopData* iData,  
CATBody* iSupportShell,  
CATBody* iGuide,  
CATBody* iSpine,  
CATLaw* iRadiusLaw) |  Not supported any longer.  
**1 replacing method** | Framework | Class or Interface | Method  
---|---|---  
GMOperatorsInterfaces | Global function | CATCGMCreateTopSweepWireSkinCircleVariable  
CATCreateGeometrySizeOptimization | CATGeometrySizeOptimization* CATCreateGeometrySizeOptimization(CATGeoFactory* iFactory,  
CATTopData* iTopData) |  Refer to the following article: [Geometric Modeler Changes](CAACenGobInterfacesMigration.htm)
