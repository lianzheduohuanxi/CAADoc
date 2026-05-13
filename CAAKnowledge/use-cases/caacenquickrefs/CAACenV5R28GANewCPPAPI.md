---
```vbscript
title: "New C++ Authorized APIs in CAA V5-6R2018 GA"
category: "use-case"
module: "CAACenQuickRefs"
tags: ["CATICGMTopDefeature", "CATIABFExport", "CATIGSMPlaneBetween", "CATIPrtCDSHoleManagement", "CATICGMTopWireContinuity", "CATIGSMUseSurfaceSimplification", "CATIGSMSurfaceSimplification", "CATICGMTopExtractCells", "CATIA", "CATIGSMUsePlaneBetween", "CATITPSManageAssociativity"]
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R28GANewCPPAPI.htmmd"
converted: "2026-05-11T17:33:47.595481"
```

---
tags: ["CATICGMTopDefeature", "CATIABFExport", "CATIGSMPlaneBetween", "CATIPrtCDSHoleManagement", "CATICGMTopWireContinuity", "CATIGSMUseSurfaceSimplification", "CATIGSMSurfaceSimplification", "CATICGMTopExtractCells", "CATIA", "CATIGSMUsePlaneBetween", "CATITPSManageAssociativity"]
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R28GANewCPPAPI.htmmd"
converted: "2026-05-11T17:33:47.595481"
CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5-6R2018 GA

* * *

The following are the new CAA V5-6R2018 GA C++ Authorized APIs, compared with CAA V5-6R2017 at GA level.

  * CATGSMUseItf framework
    * Macro or #define CATGSMWFPlaneBetween
    * Interface CATIGSMUsePlaneBetween
  * CATGSOUseItf framework
    * Interface CATIGSMUseSurfaceSimplification
  * CATGbfModelInterfaces framework
    * Interface CATIABFExport
  * CATPDMBase framework
```vbscript
    * Global Function GetIIsFromPVS
  * CATTPSInterfaces framework
```
    * Interface CATITPSManageAssociativity
  * GMModelCmpInterfaces framework
    * Class CATFeatureInfoPadCylindrical
    * Macro or #define bool_type
    * Enumeration CATExtractCellsFaceOrientation
    * Enumeration EndWallType
```vbscript
    * Global Function CATCGMCreateDefeature
    * Global Function CATCGMCreateTopExtractCells
    * Interface CATICGMTopDefeature
```
    * Interface CATICGMTopExtractCells
  * GMModelInterfaces framework
    * Enumeration CATBodyFromLengthOnWireMeasureType
    * Enumeration CATDynExtrapolationLimit
    * Enumeration CATDynExtrapolationMode
```vbscript
    * Global Function CATCGMCreateBodyFromLengthOnWire
    * Global Function CATCGMCreateBodyFromLengthOnWire
    * Interface CATCGMTessellateParam
```
  * GMOperatorsInterfaces framework
```vbscript
    * Global Function CATCGMCreateCoordSystemBody
    * Global Function CATCGMCreateTopWireContinuity
    * Interface CATICGMTopWireContinuity
```
  * GSMInterfaces framework
    * Macro or #define CATGSMWFPlaneBetween
    * Interface CATIGSMPlaneBetween
    * Interface CATIGSMSurfaceSimplification
  * GeometricObjects framework
    * Macro or #define CATButtonManifoldType
  * PartInterfaces framework
    * Enumeration CATPrtAssembleResultMode
    * Enumeration CATPrtBooleanSimplificationMode
    * Interface CATIPrtCDSHoleManagement

[Top]

* * *

History Version: **1** [Aug 2017] | Document created
---|---
[Top]

* * *

_Copyright © 1999-2017, Dassault Systèmes. All rights reserved._
```vbscript
Special Notices [CAA V5 CATIA](../CAADocQuickRefs/CAADocSpecialNoticesCATIA.md) | [CAA V5 DELMIA](../CAADocQuickRefs/CAADocSpecialNoticesDELMIA.md) | [CAA V5 ENOVIA](../CAADocQuickRefs/CAADocSpecialNoticesENOVIA.md)

```