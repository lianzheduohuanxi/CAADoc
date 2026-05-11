---
title: "Detail Of C++ API Changes"
category: "general"
module: "CAACenAPIChangesR11"
tags: ["CAA2Usage", "CAA2Level"]
source_file: "Doc\online\CAACenAPIChangesR11\CAACenAPIChangeDetail.htm"
converted: "2026-05-11T17:33:50.315021"
---

|  |  Detail Of V5R11 C++ API Changes _What changes in the API compared with CAA V5R10_  
---|---|---  
Technical Article  
  
* * *

Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5R11 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.  
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

AnalysisMeshingModel | [R11GA vs R10GA](AnalysisMeshingModel.htm) |   
---|---|---  
CATAnalysisBase | [R11GA vs R10GA](CATAnalysisBase.htm) |   
CATAssemblyInterfaces | [R11GA vs R10GA](CATAssemblyInterfaces.htm) |   
CATSchPlatformInterfaces | [R11GA vs R10GA](CATSchPlatformInterfaces.htm) |   
ComponentsCatalogsInterfaces | [R11GA vs R10GA](ComponentsCatalogsInterfaces.htm) |   
DNBInspectInterfaces | [R11GA vs R10GA](DNBInspectInterfaces.htm) |   
DialogEngine | [R11GA vs R10GA](DialogEngine.htm) |   
DraftingInterfaces | [R11GA vs R10GA](DraftingInterfaces.htm) |   
ENOVDDManager | [R11GA vs R10GA](ENOVDDManager.htm) |   
ENOVInterfaces | [R11GA vs R10GA](ENOVInterfaces.htm) |   
ENOVaultClientCPP | [R11GA vs R10GA](ENOVaultClientCPP.htm) |   
ElecDeviceItf | [R11GA vs R10GA](ElecDeviceItf.htm) |   
ElecRoutingItf | [R11GA vs R10GA](ElecRoutingItf.htm) |   
GeometricObjects | [R11GA vs R10GA](GeometricObjects.htm) |   
GSMInterfaces | [R11GA vs R10GA](GSMInterfaces.htm) |   
KnowHow | [R11GA vs R10GA](KnowHow.htm) |   
LiteralFeatures | [R11GA vs R10GA](LiteralFeatures.htm) |   
ManufacturingInterfaces | [R11GA vs R10GA](ManufacturingInterfaces.htm) |   
Mathematics | [R11GA vs R10GA](Mathematics.htm) |   
MecModInterfaces | [R11GA vs R10GA](MecModInterfaces.htm) |   
MechanicalCommands | [R11GA vs R10GA](MechanicalCommands.htm) |   
MechanicalModeler | [R11GA vs R10GA](MechanicalModeler.htm) |   
SimulationBase | [R11GA vs R10GA](SimulationBase.htm) |   
SketcherToolsUI | [R11GA vs R10GA](SketcherToolsUI.htm) |   
System | [R11GA vs R10GA](System.htm) |   
VPMInterfaces | [R11GA vs R10GA](VPMInterfaces.htm) |   
VPMPersistency | [R11GA vs R10GA](VPMPersistency.htm) |   
VisualizationBase | [R11GA vs R10GA](VisualizationBase.htm) |   
XMLParser | [R11GA vs R10GA](XMLParser.htm) |   
  
* * *

References [1] | [Migration to CATBoolean](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean)  
---|---  
[2] | [Details Of V5R7 API Changes](../CAACenAPIChangesR7/CAACenAPIChangeDetail.htm)  
[3] | [Details Of V5R10 API Changes](../CAACenAPIChangesR10/CAACenAPIChangeDetail.htm)  
[4] | [Split of the Visualization framework](../CAACenQuickRefs/CAACenWhatsNew.htm#VisuSplit)  
[5] | [Move of CAA API resources from MechanicalComands into InteractiveInterfaces](../CAACenQuickRefs/CAACenWhatsNew.htm#MecComMov)  
[Top]  
  
* * *

History Version: **1** [Mar 2002] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
