---
title: "New C++ Authorized APIs in CAA V5-6R2012 GA"
category: "use-case"
module: "CAACenQuickRefs"
tags: "["CATIVpmLightQueryManager", "CATIPrtExplodeServices", "CATIGSMMultiSelAccess", "CATIGSMUIFactory", "CATIGSMGrid", "CATICGMObjectsSaveDiagnosis", "CATIEwrWire", "CATIGSMWorkingSupport", "CATIGSMMultiSelManager", "CATIGSMCartesianGrid", "CATIGSMAutomaticFillGeo", "CATIGSMFactoryGeo", "CATIDdeDxfSettingAtt", "CATIDdeIg2SettingAtt", "CATIGSM3DFurtiveGrid", "CATIA", "CATIGSMTransfer", "CATIGSMWorkingSupportFactory", "CATIGSMWorkingSupportSet"]"
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R22GANewCPPAPI.htm"
converted: "2026-05-11T17:33:47.519115"
---
tags: ["CATIVpmLightQueryManager", "CATIPrtExplodeServices", "CATIGSMMultiSelAccess", "CATIGSMUIFactory", "CATIGSMGrid", "CATICGMObjectsSaveDiagnosis", "CATIEwrWire", "CATIGSMWorkingSupport", "CATIGSMMultiSelManager", "CATIGSMCartesianGrid", "CATIGSMAutomaticFillGeo", "CATIGSMFactoryGeo", "CATIDdeDxfSettingAtt", "CATIDdeIg2SettingAtt", "CATIGSM3DFurtiveGrid", "CATIA", "CATIGSMTransfer", "CATIGSMWorkingSupportFactory", "CATIGSMWorkingSupportSet"]
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R22GANewCPPAPI.htmmd"
converted: "2026-05-11T17:33:47.519115"
CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5-6R2012 GA

* * *

The following are the new CAA V5-6R2012 GA C++ Authorized APIs, compared with CAA V5R21 at GA level.

  * CATDdeSettingsInterfaces framework
    * Interface CATIDdeDxfSettingAtt
    * Interface CATIDdeIg2SettingAtt
  * CATFmtModelInterfaces framework
    * Class CATFmtElementIter
    * Class CATFmtNodeIter
  * CATSurfacicOpeInterfaces framework
    * Interface CATIGSMAutomaticFillGeo
    * Interface CATIGSMFactoryGeo
  * ElecRoutingItf framework
    * Interface CATIEwrWire
  * FreeFormOperators framework
```cpp
    * Global Function CATCreateCrvFittingToNurbsCrv
    * Global Function CATCreateSurFittingToNurbsSur
  * GMOperatorsInterfaces framework
```
```cpp
    * Global Function CATCGMCreateCrvFittingToNurbsCrv
    * Global Function CATCGMCreateGeodesicLinePtPt
    * Global Function CATCGMCreateSurFittingToNurbsSur
  * GSMInterfaces framework
```
    * Class CATGSMPublicServices
    * Macro or #define CATGSMWFCircle2Pts
    * Macro or #define CATGSMWFCircle3Pts
    * Macro or #define CATGSMWFCircleBitgtPt
    * Macro or #define CATGSMWFCircleBitgtRad
    * Macro or #define CATGSMWFCircleCtrAxis
    * Macro or #define CATGSMWFCircleCtrPt
    * Macro or #define CATGSMWFCircleCtrTgt
    * Macro or #define CATGSMWFCircleExplicit
    * Macro or #define CATGSMWFCirclePtRad
    * Macro or #define CATGSMWFCircleTritgt
    * Macro or #define CATGSMWFFilletBiTangent
    * Macro or #define CATGSMWFFilletTriTangent
    * Macro or #define CATGSMWFLineAngle
    * Macro or #define CATGSMWFLineBiTangent
    * Macro or #define CATGSMWFLineBisecting
    * Macro or #define CATGSMWFLineExplicit
    * Macro or #define CATGSMWFLineNormal
    * Macro or #define CATGSMWFLinePtDir
    * Macro or #define CATGSMWFLinePtPt
    * Macro or #define CATGSMWFLineTangency
    * Macro or #define CATGSMWFPlane1Pt1Ln
    * Macro or #define CATGSMWFPlaneAngle
    * Macro or #define CATGSMWFPlaneEquation
    * Macro or #define CATGSMWFPlaneExplicit
    * Macro or #define CATGSMWFPlaneMean
    * Macro or #define CATGSMWFPlaneNormal
    * Macro or #define CATGSMWFPlaneOffsetPt
    * Macro or #define CATGSMWFPlaneOffset
    * Macro or #define CATGSMWFPlaneTangency
    * Macro or #define CATGSMWFPlaneThrg1
    * Macro or #define CATGSMWFPlaneThrg2
    * Macro or #define CATGSMWFPlaneThrg3
    * Macro or #define CATGSMWFPointBetween
    * Macro or #define CATGSMWFPointCenter
    * Macro or #define CATGSMWFPointCoord
    * Macro or #define CATGSMWFPointExplicit
    * Macro or #define CATGSMWFPointOnCurve
    * Macro or #define CATGSMWFPointOnSurf
    * Macro or #define CATGSMWFPointPlanar
    * Macro or #define CATGSMWFPointTangent
    * Macro or #define CATGSMWFSweepCircle
    * Macro or #define CATGSMWFSweepConic
    * Macro or #define CATGSMWFSweepSegment
    * Macro or #define CATGSMWFSweepUnspec
```cpp
    * Global Function CATGSMCreateMultiSelManager
    * Interface CATIGSM3DFurtiveGrid
```
    * Interface CATIGSMCartesianGrid
    * Interface CATIGSMGrid
    * Interface CATIGSMMultiSelAccess
    * Interface CATIGSMMultiSelManager
    * Interface CATIGSMUIFactory
    * Interface CATIGSMWorkingSupportFactory
    * Interface CATIGSMWorkingSupportSet
    * Interface CATIGSMWorkingSupport
  * GSOInterfaces framework
    * Interface CATIGSMTransfer
  * GeometricObjects framework
    * Macro or #define CATCGMObjectsVersion
    * Enumeration CATICGMObjectsSaveDiagnosis
  * Mathematics framework
    * Macro or #define CATToleranceCheckValidity
  * PartInterfaces framework
    * Enumeration CATPrtChamferExtremities
    * Enumeration CATPrtTrimSupportMode
    * Interface CATIPrtExplodeServices
  * SDMRuntime framework
    * Macro or #define SDAIAGGR
  * TopologicalOperators framework
    * Macro or #define CATExtrapolateBody_NewR21SP2Methods
```cpp
    * Global Function CATCreateTopPattern
    * Global Function CATLoadCATExtrapolateBody
    * Interface CATTopPattern
```
  * VPMInterfaces framework
    * Enumeration QueryType
    * Interface CATIVpmLightQueryManager
  * VisualizationBase framework
    * Macro or #define FILL
    * Macro or #define NOFILL

[Top]

* * *

History Version: **1** [Sep 2011] | Document created
---|---
[Top]

* * *

_Copyright © 1999-2011, Dassault Systèmes. All rights reserved._
```cpp
Special Notices [CAA V5 CATIA](../CAADocQuickRefs/CAADocSpecialNoticesCATIA.md) | [CAA V5 DELMIA](../CAADocQuickRefs/CAADocSpecialNoticesDELMIA.md) | [CAA V5 ENOVIA](../CAADocQuickRefs/CAADocSpecialNoticesENOVIA.md)

```