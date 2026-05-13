---
title: "Detail Of C++ API Changes"
category: "api-changes"
module: "CAACenAPIChangesR13"
tags: "["CAA2Usage", "CATIAV4Interfaces", "CAA2Level"]"
source_file: "Doc/online/CAACenAPIChangesR13/CAACenAPIChangeDetail.htm"
converted: "2026-05-11T17:33:50.640808"
---
|  |  Detail Of V5R13 C++ API Changes _What changes in the API compared with CAA V5R12_
---|---|---
Technical Article

* * *

Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5R13 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.
| Classification | Meaning
---|---
Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5R13 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.
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
CATAnalysisBase.md | [R13GA vs R12GA](CATAnalysisBase.md) |

CATAnalysisInterfaces.md | [R13GA vs R12GA](CATAnalysisInterfaces.md) |
CATIAV4Interfaces.md | [R13GA vs R12GA](CATIAV4Interfaces.md) |
DNBInspectInterfaces.md | [R13GA vs R12GA](DNBInspectInterfaces.md) |
DMAPSInterfaces.md | [R13GA vs R12GA](DMAPSInterfaces.md) |
ENOVaultClientCPP.md | [R13GA vs R12GA](ENOVaultClientCPP.md) |
GeometryVisualization.md | [R13GA vs R12GA](GeometryVisualization.md) |
GSOInterfaces.md | [R13GA vs R12GA](GSOInterfaces.md) |
ManufacturingInterfaces.md | [R13GA vs R12GA](ManufacturingInterfaces.md) |
MechanicalModeler.md | [R13GA vs R12GA](MechanicalModeler.md) |
MecModInterfaces.md | [R13GA vs R12GA](MecModInterfaces.md) |
ObjectModelerBase.md | [R13GA vs R12GA](ObjectModelerBase.md) |
Visualization.md | [R13GA vs R12GA](Visualization.md) |
VPMDesktopObjects.md | [R13GA vs R12GA](VPMDesktopObjects.md) |
VPMInterfaces.md | [R13GA vs R12GA](VPMInterfaces.md) |
V5ToV4Geo.md | [R13GA vs R12GA](V5ToV4Geo.md) |

* * *

VPMInterfaces.md | [R13GA vs R12GA](VPMInterfaces.md) |
V5ToV4Geo.md | [R13GA vs R12GA](V5ToV4Geo.md) |
References [1] | [Migration to CATBoolean](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean)

[2] | [Details Of V511 API Changes](../CAACenAPIChangesR11/CAACenAPIChangeDetail.md)
[3] | [Details Of V5R12 API Changes](../CAACenAPIChangesR12/CAACenAPIChangeDetail.md)
[4] | [Split of the Visualization framework](../CAACenQuickRefs/CAACenWhatsNew.htm#VisuSplit)
[5] | [Move of CAA API resources from MechanicalComands into InteractiveInterfaces](../CAACenQuickRefs/CAACenWhatsNew.htm#MecComMov)
[Top]

* * *

History Version: **1** [Mar 2002] | Document created
---|---
[Top]

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
