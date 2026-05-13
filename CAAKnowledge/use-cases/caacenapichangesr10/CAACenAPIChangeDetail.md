---
title: "Detail Of C++ API Changes"
category: "api-changes"
module: "CAACenAPIChangesR10"
tags: "["CAA2Usage", "CATIAApplicationFrame", "CAA2Level"]"
source_file: "Doc/online/CAACenAPIChangesR10/CAACenAPIChangeDetail.htm"
converted: "2026-05-11T17:33:50.095851"
---
|  |  Detail Of V5R10 C++ API Changes _What changes in the API compared with CAA V5R9_
---|---|---
Technical Article

* * *

Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5R10 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.
| Classification | Meaning
---|---
Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5R10 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.
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
AdvancedMathematics | [R10GA vs R9GA](AdvancedMathematics.md) |

AdvancedTopologicalOpe | [R10GA vs R9GA](AdvancedTopologicalOpe.md) |
ApplicationFrame | [R10GA vs R9GA](ApplicationFrame.md) |
AnalysisMeshingModel | [R10GA vs R9GA](AnalysisMeshingModel.md) |
CATAnalysisBase | [R10GA vs R9GA](CATAnalysisBase.md) |
CATAnalysisInterfaces | [R10GA vs R9GA](CATAnalysisInterfaces.md) |
CATAnalysisResources | [R10GA vs R9GA](CATAnalysisResources.md) |
CATIAApplicationFrame | [R10GA vs R9GA](CATIAApplicationFrame.md) |
CATSchPlatformInterfaces | [R10GA vs R9GA](CATSchPlatformInterfaces.md) |
CATTPSInterfaces | [R10GA vs R9GA](CATTPSInterfaces.md) |
Dialog | [R10GA vs R9GA](Dialog.md) |
DialogEngine | [R10GA vs R9GA](DialogEngine.md) |
DNBInspectInterfaces | [R10GA vs R9GA](DNBInspectInterfaces.md) |
DraftingInterfaces | [R10GA vs R9GA](DraftingInterfaces.md) |
ENOVInterfaces | [R10GA vs R9GA](ENOVInterfaces.md) |
ENOVReportSolutionServer | [R10GA vs R9GA](ENOVReportSolutionServer.md) |
GeometricObjects | [R10GA vs R9GA](GeometricObjects.md) |
GSMInterfaces | [R10GA vs R9GA](GSMInterfaces.md) |
ManufacturingInterfaces | [R10GA vs R9GA](ManufacturingInterfaces.md) |
Mathematics | [R10GA vs R9GA](Mathematics.md) | [R10rel vs R10GA](MathematicsSP.md)
MechanicalModeler | [R10GA vs R9GA](MechanicalModeler.md) |
MechanicalModelerUI | [R10GA vs R9GA](MechanicalModelerUI.md) |
MecModInterfaces | [R10GA vs R9GA](MecModInterfaces.md) | [R10rel vs R10GA](MecModInterfacesSP.md)
NewTopologicalObjects | [R10GA vs R9GA](NewTopologicalObjects.md) |
ObjectModelerBase | [R10GA vs R9GA](ObjectModelerBase.md) |
ObjectSpecsModeler | [R10GA vs R9GA](ObjectSpecsModeler.md) |
Print | [R10GA vs R9GA](Print.md) |
System | [R10GA vs R9GA](System.md) |
SDMRuntime | [R10GA vs R9GA](SDMRuntime.md) |
TopologicalOperators | [R10GA vs R9GA](TopologicalOperators.md) |
Visualization | [R10GA vs R9GA](Visualization.md) |
VPMInterfaces | [R10GA vs R9GA](VPMInterfaces.md) |
VPMPersistency | [R10GA vs R9GA](VPMPersistency.md) |
VPMServices | [R10GA vs R9GA](VPMServices.md) |

* * *

VPMPersistency | [R10GA vs R9GA](VPMPersistency.md) |
VPMServices | [R10GA vs R9GA](VPMServices.md) |
References [1] | [Migration to CATBoolean](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean)

[2] | [Details Of V5R7 API Changes](../CAACenAPIChangesR7/CAACenAPIChangeDetail.md)
[3] | [Details Of V5R9 API Changes](../CAACenAPIChangesR9/CAACenAPIChangeDetail.md)
[4] | [Split of the Visualization framework](../CAACenQuickRefs/CAACenWhatsNew.htm#VisuSplit)
[5] | [Move of CAA API resources from MechanicalComands into InteractiveInterfaces](../CAACenQuickRefs/CAACenWhatsNew.htm#MecComMov)
[Top]

* * *

History Version: **1** [Mar 2002] | Document created
---|---
[Top]

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
