---
title: "New C++ Authorized APIs in CAA V5-6R2015 GA"
category: "use-case"
module: "CAACenQuickRefs"
tags: "["CATIThreadManagement", "CATICGMDistanceBodyBody", "CATITPSExtendedCylinder", "CATIACbdUserImportIDF", "CATIPrdHandlePDMObject", "CATIAVPMVDACreateExtension", "CATIA", "CATICGMHealGaps", "CATIPDMSaveContext", "CATIAV4Interfaces", "CATIMfgSpiralMilling3x"]"
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R25GANewCPPAPI.htm"
converted: "2026-05-11T17:33:47.564481"
---
tags: ["CATIThreadManagement", "CATICGMDistanceBodyBody", "CATITPSExtendedCylinder", "CATIACbdUserImportIDF", "CATIPrdHandlePDMObject", "CATIAVPMVDACreateExtension", "CATIA", "CATICGMHealGaps", "CATIPDMSaveContext", "CATIAV4Interfaces", "CATIMfgSpiralMilling3x"]
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R25GANewCPPAPI.htmmd"
converted: "2026-05-11T17:33:47.564481"
CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5-6R2015 GA

* * *

The following are the new CAA V5-6R2015 GA C++ Authorized APIs, compared with CAA V5-6R2014 at GA level.

  * AdvancedMathematics framework
```cpp
    * Global Function CreateCombination
  * CATIAV4Interfaces framework
```
```cpp
    * Global Function CAT4iGetCompositsNumber
    * Global Function CATV4iGirema
  * CATPDMBaseInterfaces framework
```
    * Enumeration CATPDMSaveContext
    * Interface CATIPDMSaveContext
  * CATTPSInterfaces framework
    * Interface CATITPSExtendedCylinder
  * GMModelInterfaces framework
    * Class CATLISTP(CATCGMDiagnosis)
    * Interface CATCGMRefCounted
  * GMOperatorsInterfaces framework
```cpp
    * Global Function CATCGMCreateDistanceBodyBodyOp
    * Global Function CATCGMCreateHealGaps
    * Interface CATICGMDistanceBodyBody
```
    * Interface CATICGMHealGaps
  * GeometricObjects framework
    * Macro or #define CATBoneFilletConstantType
```cpp
    * Global Function CATCreateCGMContainer
  * GeometricOperators framework
```
```vbscript
    * Global Function CreatePlanarMapping
  * ManufacturingInterfaces framework
```
    * Interface CATIMfgSpiralMilling3x
  * Mathematics framework
    * Class CATLISTV(CATMathAxis)
    * Macro or #define CATGeometricModelTransactionEndTryWithoutRethrow
    * Macro or #define CATToleranceCheckDefault
```cpp
    * Global Function CATTan
  * Multimedia framework
```
    * Enumeration CATPrintVertexOption
  * ObjectModelerBase framework
```vbscript
    * Global Function UpdateDocumentAccessStatus
  * ObjectModelerCollection framework
```
    * Class CORBAAny
    * Class sequence
    * Macro or #define max
  * PCBoardBase framework
    * Class CATCbdUserImportAdapter
    * Interface CATIACbdUserImportIDF
  * PartInterfaces framework
    * Interface CATIThreadManagement
  * ProductStructureInterfaces framework
    * Interface CATIPrdHandlePDMObject
  * VPMDesktopObjects framework
    * Interface CATIAVPMVDACreateExtension
  * VPMInterfaces framework
    * Class ENOVQObjectIdentity
    * Enumeration VPM_Boolean
    * Enumeration VPM_Logical
    * Structure VPM_Access
    * Typedef CATListOfENOVQObjectIdentity

[Top]

* * *

History Version: **1** [Jul 2014] | Document created
---|---
[Top]

* * *

_Copyright © 1999-2014, Dassault Systèmes. All rights reserved._
```cpp
Special Notices [CAA V5 CATIA](../CAADocQuickRefs/CAADocSpecialNoticesCATIA.md) | [CAA V5 DELMIA](../CAADocQuickRefs/CAADocSpecialNoticesDELMIA.md) | [CAA V5 ENOVIA](../CAADocQuickRefs/CAADocSpecialNoticesENOVIA.md)

```