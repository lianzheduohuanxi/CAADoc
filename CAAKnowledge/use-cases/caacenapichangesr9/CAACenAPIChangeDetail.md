---
```vbscript
title: "Detail Of C++ API Changes"
category: "api-changes"
module: "CAACenAPIChangesR9"
version: "V5R9"
tags: ["CAA2Usage", "CAA2Level"]
source_file: "Doc/online/CAACenAPIChangesR9/CAACenAPIChangeDetail.htm"
converted: "2026-05-11T17:33:52.825711"
```

---
|  |  Detail Of V5R9 C++ API Changes _What changes in the API compared with CAA V5R8_
---|---|---
Technical Article

* * *

Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5R9 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.
| Classification | Meaning
---|---
Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5R9 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.
LHC | @CAA2Level Has Changed: a L1 file is no more L1.
UHC | @CAA2Usage Has Changed: usage has changed for a more restricted usage. For example a class tagged as derivable is not derivable anymore.
CHBD | Class Has Been Deleted
FHBD | File Has Been Deleted
ADVHC | Argument Default Value Has Changed
MHBDM | Method Has Been Deleted or Modified
MRTHC | Method Returned Type Has Changed
NPVM | New Pure Virtual Method. A new pure virtual method has been added on a derivable class or on an interface to be implemented without an adapter.
INDM | Method is no more documented. It does not break your code in any way but means that you are not supposed to use it anymore. Check that you don't use it or look for replacement informations.

* * *

INDM | Method is no more documented. It does not break your code in any way but means that you are not supposed to use it anymore. Check that you don't use it or look for replacement informations.
AdvancedMathematics | [R9GA vs R8GA](AdvancedMathematics.md) |

AdvancedMathematics | [R9GA vs R8GA](AdvancedMathematics.md) |
ApplicationFrame | [R9GA vs R8GA](ApplicationFrame.md) |
AnalysisMeshingModel | [R9GA vs R8GA](AnalysisMeshingModel.md) |
BasicTopologicalOpe | [R9GA vs R8GA](BasicTopologicalOpe.md) |
CATAnalysisBase | [R9GA vs R8GA](CATAnalysisBase.md) |
CATAnalysisInterfaces | [R9GA vs R8GA](CATAnalysisInterfaces.md) |
CATTPSInterfaces | [R9GA vs R8GA](CATTPSInterfaces.md) |  |
Dialog | [R9GA vs R8GA](Dialog.md) |
DMAPSInterfaces | [R9GA vs R8GA](DMAPSInterfaces.md) |
DNBDpmBIWInterfaces | [R9GA vs R8GA](DNBDpmBIWInterfaces.md) |
DNBInspectInterfaces | [R9GA vs R8GA](DNBInspectInterfaces.md) |
DraftingInterfaces | [R9GA vs R8GA](DraftingInterfaces.md) |
ENOVInterfaces | [R9GA vs R8GA](ENOVInterfaces.md) |
ENOVaultClientCPP | [R9GA vs R8GA](ENOVaultClientCPP.md) |
GeometricObjects | [R9GA vs R8GA](GeometricObjects.md) |
GSMInterfaces | [R9GA vs R8GA](GSMInterfaces.md) |
LiteralFeatures | [R9GA vs R8GA](LiteralFeatures.md) |
ManufacturingInterfaces | [R9GA vs R8GA](ManufacturingInterfaces.md) |
Mathematics | [R9GA vs R8GA](Mathematics.md) |
MechanicalCommands | [R9GA vs R8GA](MechanicalCommands.md) |
MechanicalModelerUI | [R9GA vs R8GA](MechanicalModelerUI.md) |
MecModInterfaces | [R9GA vs R8GA](MecModInterfaces.md) |
NewTopologicalObjects | [R9GA vs R8GA](NewTopologicalObjects.md) |
ObjectModelerBase | [R9GA vs R8GA](ObjectModelerBase.md) |
SetcherInterfaces | [R9GA vs R8GA](SketcherInterfaces.md) |
System | [R9GA vs R8GA](System.md) |
Visualization | [R9GA vs R8GA](Visualization.md) |
VPMInterfaces | [R9GA vs R8GA](VPMInterfaces.md) |
VPMPersistency | [R9GA vs R8GA](VPMPersistency.md) |
VPMPsManager | [R9GA vs R8GA](VPMPsManager.md) |
VPMDesktopServices | [R9GA vs R8GA](VPMDesktopServices.md) |
VPMTpManager | [R9GA vs R8GA](VPMTpManager.md) |
VPMXBom | [R9GA vs R8GA](VPMXBom.md) |

* * *

VPMTpManager | [R9GA vs R8GA](VPMTpManager.md) |
VPMXBom | [R9GA vs R8GA](VPMXBom.md) |
References [1] | [Migration to CATBoolean](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean)

[2] | [Details Of V5R7 API Changes](../CAACenAPIChangesR7/CAACenAPIChangeDetail.md)
[3] | [Details Of V5R8 API Changes](../CAACenAPIChangesR8/CAACenAPIChangeDetail.md)
[4] | [Split of the Visualization framework](../CAACenQuickRefs/CAACenWhatsNew.htm#VisuSplit)
[5] | [Move of CAA API resources from MechanicalComands into InteractiveInterfaces](../CAACenQuickRefs/CAACenWhatsNew.htm#MecComMov)
[Top]

* * *

History Version: **1** [Mar 2002] | Document created
---|---
[Top]

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
