---
title: "Detail Of API Changes"
category: "general"
module: "CAACenAPIChangesR7"
tags: ["CAA2Usage", "CAA2Level"]
source_file: "Doc\online\CAACenAPIChangesR7\CAACenAPIChangeDetail.htm"
converted: "2026-05-11T17:33:51.920474"
---

|  |  Detail Of V5R7 API Changes _What changes in the API compared with CAA V5R6_  
---|---|---  
Technical Article  
  
* * *

Abstract This article presents by frameworks the detail of CAA resources modified in V5R7 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.  
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

AnalysisMeshingModel | [R7GA vs R6GA](AnalysisMeshingModel.htm) | [R7SP vs R7GA](AnalysisMeshingModelSP.htm)  
---|---|---  
ApplicationFrame | [R7GA vs R6GA](ApplicationFrame.htm) | [R7SP vs R7GA](ApplicationFrameSP.htm)  
BasicTopologicalOpe |  | [R7SP vs R7GA](BasicTopologicalOpeSP.htm)  
CATAnalysisBase | [R7GA vs R6GA](CATAnalysisBase.htm) | [R7SP vs R7GA](CATAnalysisBaseSP.htm)  
CATAnalysisInterfaces | [R7GA vs R6GA](CATAnalysisInterfaces.htm) | [R7SP vs R7GA](CATAnalysisInterfacesSP.htm)  
CATAnalysisResources |  | [R7SP vs R7GA](CATAnalysisResourcesSP.htm)  
CATSchPlatformInterfaces |  | [R7SP vs R7GA](CATSchPlatformInterfacesSP.htm)  
CATTPSInterfaces | [R7GA vs R6GA](CATTPSInterfaces.htm) | [R7SP vs R7GA](CATTPSInterfacesSP.htm)  
CORBAServerBase | [R7GA vs R6GA](CORBAServerBase.htm) |   
Dialog | [R7GA vs R6GA](Dialog.htm) | [R7SP vs R7GA](DialogSP.htm)  
DialogEngine |  | [R7SP vs R7GA](DialogEngineSP.htm)  
DNBInspectSharedInterfaces |  | [R7SP vs R7GA](DNBInspectSharedInterfacesSP.htm)  
DraftingInterfaces | [R7GA vs R6GA](DraftingInterfaces.htm) | [R7SP vs R7GA](DraftingInterfacesSP.htm)  
ENOVDDManager | [R7GA vs R6GA](ENOVDDManager.htm) | [R7SP vs R7GA](ENOVDDManagerSP.htm)  
ENOVDesktopDocument | [R7GA vs R6GA](ENOVDesktopDocument.htm) | [R7SP vs R7GA](ENOVDesktopDocumentSP.htm)  
ENOVIAPlugIn | [R7GA vs R6GA](ENOVIAPlugIn.htm) |   
ENOVInterfaces | [R7GA vs R6GA](ENOVInterfaces.htm) | [R7SP vs R7GA](ENOVInterfacesSP.htm)  
ENOVaultClientCPP | [R7GA vs R6GA](ENOVaultClientCPP.htm) | [R7SP vs R7GA](ENOVaultClientCPPSP.htm)  
GSMInterfaces | [R7GA vs R6GA](GSMInterfaces.htm) | [R7SP vs R7GA](GSMInterfacesSP.htm)  
GSOInterfaces |  | [R7SP vs R7GA](GSOInterfacesSP.htm)  
GeometricObjects | [R7GA vs R6GA](GeometricObjects.htm) | [R7SP vs R7GA](GeometricObjectsSP.htm)  
InteractiveInterfaces |  | [R7SP vs R7GA](InteractiveInterfacesSP.htm)  
KinematicsInterfaces | [R7GA vs R6GA](KinematicsInterfaces.htm) |   
LiteralFeatures | [R7GA vs R6GA](LiteralFeatures.htm) | [R7SP vs R7GA](LiteralFeaturesSP.htm)  
ManufacturingInterfaces | [R7GA vs R6GA](ManufacturingInterfaces.htm) | [R7SP vs R7GA](ManufacturingInterfacesSP.htm)  
Mathematics |  | [R7SP vs R7GA](MathematicsSP.htm)  
MecModInterfaces | [R7GA vs R6GA](MecModInterfaces.htm) | [R7SP vs R7GA](MecModInterfacesSP.htm)  
MechanicalModeler | [R7GA vs R6GA](MechanicalModeler.htm) | [R7SP vs R7GA](MechanicalModelerSP.htm)  
NewTopologicalObjects | [R7GA vs R6GA](NewTopologicalObjects.htm) |   
ObjectModelerBase | [R7GA vs R6GA](ObjectModelerBase.htm) | [R7SP vs R7GA](ObjectModelerBaseSP.htm)  
ObjectSpecsModeler | [R7GA vs R6GA](ObjectSpecsModeler.htm) | [R7SP vs R7GA](ObjectSpecsModelerSP.htm)  
PartInterfaces | [R7GA vs R6GA](PartInterfaces.htm) | [R7SP vs R7GA](PartInterfacesSP.htm)  
Print | [R7GA vs R6GA](Print.htm) | [R7SP vs R7GA](PrintSP.htm)  
ProductStructure | [R7GA vs R6GA](ProductStructure.htm) |   
System | [R7GA vs R6GA](System.htm) | [R7SP vs R7GA](SystemSP.htm)  
TopologicalOperators | [R7GA vs R6GA](TopologicalOperators.htm) | [R7SP vs R7GA](TopologicalOperatorsSP.htm)  
Tessellation |  | [R7SP vs R7GA](TessellationSP.htm)  
VPMDesktopObjects | [R7GA vs R6GA](VPMDesktopObjects.htm) | [R7SP vs R7GA](VPMDesktopObjectsSP.htm)  
VPMInterfaces | [R7GA vs R6GA](VPMInterfaces.htm) | [R7SP vs R7GA](VPMInterfacesSP.htm)  
VPMXBom | [R7GA vs R6GA](VPMXBom.htm) |   
VPMServices |  | [R7SP vs R7GA](VPMServicesSP.htm)  
Visualization | [R7GA vs R6GA](Visualization.htm) | [R7SP vs R7GA](VisualizationSP.htm)  
  
* * *

References [1] | [Migration to CATBoolean](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean)  
---|---  
[Top]  
  
* * *

History Version: **1** [May 2001] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
