---
title: "Detail Of C++ API Changes"
category: "general"
module: "CAACenAPIChangesR10"
tags: ["CAA2Usage", "CATIAApplicationFrame", "CAA2Level"]
source_file: "Doc\online\CAACenAPIChangesR10\CAACenAPIChangeDetail.htm"
converted: "2026-05-11T17:33:50.095851"
---

|  |  Detail Of V5R10 C++ API Changes _What changes in the API compared with CAA V5R9_  
---|---|---  
Technical Article  
  
* * *

Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5R10 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.  
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

AdvancedMathematics | [R10GA vs R9GA](AdvancedMathematics.htm) |   
---|---|---  
AdvancedTopologicalOpe | [R10GA vs R9GA](AdvancedTopologicalOpe.htm) |   
ApplicationFrame | [R10GA vs R9GA](ApplicationFrame.htm) |   
AnalysisMeshingModel | [R10GA vs R9GA](AnalysisMeshingModel.htm) |   
CATAnalysisBase | [R10GA vs R9GA](CATAnalysisBase.htm) |   
CATAnalysisInterfaces | [R10GA vs R9GA](CATAnalysisInterfaces.htm) |   
CATAnalysisResources | [R10GA vs R9GA](CATAnalysisResources.htm) |   
CATIAApplicationFrame | [R10GA vs R9GA](CATIAApplicationFrame.htm) |   
CATSchPlatformInterfaces | [R10GA vs R9GA](CATSchPlatformInterfaces.htm) |   
CATTPSInterfaces | [R10GA vs R9GA](CATTPSInterfaces.htm) |   
Dialog | [R10GA vs R9GA](Dialog.htm) |   
DialogEngine | [R10GA vs R9GA](DialogEngine.htm) |   
DNBInspectInterfaces | [R10GA vs R9GA](DNBInspectInterfaces.htm) |   
DraftingInterfaces | [R10GA vs R9GA](DraftingInterfaces.htm) |   
ENOVInterfaces | [R10GA vs R9GA](ENOVInterfaces.htm) |   
ENOVReportSolutionServer | [R10GA vs R9GA](ENOVReportSolutionServer.htm) |   
GeometricObjects | [R10GA vs R9GA](GeometricObjects.htm) |   
GSMInterfaces | [R10GA vs R9GA](GSMInterfaces.htm) |   
ManufacturingInterfaces | [R10GA vs R9GA](ManufacturingInterfaces.htm) |   
Mathematics | [R10GA vs R9GA](Mathematics.htm) | [R10rel vs R10GA](MathematicsSP.htm)  
MechanicalModeler | [R10GA vs R9GA](MechanicalModeler.htm) |   
MechanicalModelerUI | [R10GA vs R9GA](MechanicalModelerUI.htm) |   
MecModInterfaces | [R10GA vs R9GA](MecModInterfaces.htm) | [R10rel vs R10GA](MecModInterfacesSP.htm)  
NewTopologicalObjects | [R10GA vs R9GA](NewTopologicalObjects.htm) |   
ObjectModelerBase | [R10GA vs R9GA](ObjectModelerBase.htm) |   
ObjectSpecsModeler | [R10GA vs R9GA](ObjectSpecsModeler.htm) |   
Print | [R10GA vs R9GA](Print.htm) |   
System | [R10GA vs R9GA](System.htm) |   
SDMRuntime | [R10GA vs R9GA](SDMRuntime.htm) |   
TopologicalOperators | [R10GA vs R9GA](TopologicalOperators.htm) |   
Visualization | [R10GA vs R9GA](Visualization.htm) |   
VPMInterfaces | [R10GA vs R9GA](VPMInterfaces.htm) |   
VPMPersistency | [R10GA vs R9GA](VPMPersistency.htm) |   
VPMServices | [R10GA vs R9GA](VPMServices.htm) |   
  
* * *

References [1] | [Migration to CATBoolean](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean)  
---|---  
[2] | [Details Of V5R7 API Changes](../CAACenAPIChangesR7/CAACenAPIChangeDetail.htm)  
[3] | [Details Of V5R9 API Changes](../CAACenAPIChangesR9/CAACenAPIChangeDetail.htm)  
[4] | [Split of the Visualization framework](../CAACenQuickRefs/CAACenWhatsNew.htm#VisuSplit)  
[5] | [Move of CAA API resources from MechanicalComands into InteractiveInterfaces](../CAACenQuickRefs/CAACenWhatsNew.htm#MecComMov)  
[Top]  
  
* * *

History Version: **1** [Mar 2002] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
