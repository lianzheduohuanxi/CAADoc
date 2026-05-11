---
title: "Detail Of C++ API Changes"
category: "general"
module: "CAACenAPIChangesR13"
tags: ["CAA2Usage", "CATIAV4Interfaces", "CAA2Level"]
source_file: "Doc\online\CAACenAPIChangesR13\CAACenAPIChangeDetail.htm"
converted: "2026-05-11T17:33:50.640808"
---

|  |  Detail Of V5R13 C++ API Changes _What changes in the API compared with CAA V5R12_  
---|---|---  
Technical Article  
  
* * *

Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5R13 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.  
| Classification | Meaning  
---|---  
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

CATAnalysisBase.htm | [R13GA vs R12GA](CATAnalysisBase.htm) |   
---|---|---  
CATAnalysisInterfaces.htm | [R13GA vs R12GA](CATAnalysisInterfaces.htm) |   
CATIAV4Interfaces.htm | [R13GA vs R12GA](CATIAV4Interfaces.htm) |   
DNBInspectInterfaces.htm | [R13GA vs R12GA](DNBInspectInterfaces.htm) |   
DMAPSInterfaces.htm | [R13GA vs R12GA](DMAPSInterfaces.htm) |   
ENOVaultClientCPP.htm | [R13GA vs R12GA](ENOVaultClientCPP.htm) |   
GeometryVisualization.htm | [R13GA vs R12GA](GeometryVisualization.htm) |   
GSOInterfaces.htm | [R13GA vs R12GA](GSOInterfaces.htm) |   
ManufacturingInterfaces.htm | [R13GA vs R12GA](ManufacturingInterfaces.htm) |   
MechanicalModeler.htm | [R13GA vs R12GA](MechanicalModeler.htm) |   
MecModInterfaces.htm | [R13GA vs R12GA](MecModInterfaces.htm) |   
ObjectModelerBase.htm | [R13GA vs R12GA](ObjectModelerBase.htm) |   
Visualization.htm | [R13GA vs R12GA](Visualization.htm) |   
VPMDesktopObjects.htm | [R13GA vs R12GA](VPMDesktopObjects.htm) |   
VPMInterfaces.htm | [R13GA vs R12GA](VPMInterfaces.htm) |   
V5ToV4Geo.htm | [R13GA vs R12GA](V5ToV4Geo.htm) |   
  
* * *

References [1] | [Migration to CATBoolean](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean)  
---|---  
[2] | [Details Of V511 API Changes](../CAACenAPIChangesR11/CAACenAPIChangeDetail.htm)  
[3] | [Details Of V5R12 API Changes](../CAACenAPIChangesR12/CAACenAPIChangeDetail.htm)  
[4] | [Split of the Visualization framework](../CAACenQuickRefs/CAACenWhatsNew.htm#VisuSplit)  
[5] | [Move of CAA API resources from MechanicalComands into InteractiveInterfaces](../CAACenQuickRefs/CAACenWhatsNew.htm#MecComMov)  
[Top]  
  
* * *

History Version: **1** [Mar 2002] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
