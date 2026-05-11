---
```vbscript
title: "Detail Of C++ API Changes"
category: "api-changes"
module: "CAACenAPIChangesR12"
version: "V5R12"
tags: ["CAA2Usage", "CAA2Level"]
source_file: "Doc/online/CAACenAPIChangesR12/CAACenAPIChangeDetail.htm"
converted: "2026-05-11T17:33:50.507188"
```

---
|  |  |  Detail Of V5R12 C++ API Changes _What changes in the API compared with CAA V5R11_  
---|---|---  
Technical Article  

* * *

Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5R11 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.  
| Classification | Meaning  
---|---  
Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5R11 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.
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
AdvancedTopologicalOpe | [R12GA vs R11GA](AdvancedTopologicalOpe.md) |   

AdvancedTopologicalOpe | [R12GA vs R11GA](AdvancedTopologicalOpe.md) |
CATAnalysisInterfaces | [R12GA vs R11GA](CATAnalysisInterfaces.md) |   
CATSchPlatformInterfaces | [R12GA vs R11GA](CATSchPlatformInterfaces.md) |   
CATSchPlatformModeler | [R12GA vs R11GA](CATSchPlatformModeler.md) |   
ENOVInterfaces | [R12GA vs R11GA](ENOVInterfaces.md) |   
GSMInterfaces | [R12GA vs R11GA](GSMInterfaces.md) |   
ObjectModelerBase | [R12GA vs R11GA](ObjectModelerBase.md) |   
SDMRuntime | [R12GA vs R11GA](SDMRuntime.md) |   
System | [R12GA vs R11GA](System.md) |   
VisualizationBase | [R12GA vs R11GA](VisualizationBase.md) |   
VPMDesktopServices | [R12GA vs R11GA](VPMDesktopServices.md) |   
VPMInterfaces | [R12GA vs R11GA](VPMInterfaces.md) |   
VPMPersistency | [R12GA vs R11GA](VPMPersistency.md) |   

* * *

VPMInterfaces | [R12GA vs R11GA](VPMInterfaces.md) |
VPMPersistency | [R12GA vs R11GA](VPMPersistency.md) |
References [1] | [Migration to CATBoolean](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean)  

[2] | [Details Of V5R7 API Changes](../CAACenAPIChangesR7/CAACenAPIChangeDetail.md)  
[3] | [Details Of V5R10 API Changes](../CAACenAPIChangesR10/CAACenAPIChangeDetail.md)  
[4] | [Split of the Visualization framework](../CAACenQuickRefs/CAACenWhatsNew.htm#VisuSplit)  
[5] | [Move of CAA API resources from MechanicalComands into InteractiveInterfaces](../CAACenQuickRefs/CAACenWhatsNew.htm#MecComMov)  
[Top]  

* * *

History Version: **1** [Mar 2002] | Document created  
---|---  
[Top]  

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
