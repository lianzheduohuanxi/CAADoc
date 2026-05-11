---
```vbscript
title: "Detail Of API Changes"
category: "api-changes"
module: "CAACenAPIChangesR7"
version: "V5R7"
tags: ["CAA2Usage", "CAA2Level"]
source_file: "Doc/online/CAACenAPIChangesR7/CAACenAPIChangeDetail.htm"
converted: "2026-05-11T17:33:51.920474"
```

---
|  |  Detail Of V5R7 API Changes _What changes in the API compared with CAA V5R6_  
---|---|---  
Technical Article  

* * *

Abstract This article presents by frameworks the detail of CAA resources modified in V5R7 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.  
| Classification | Meaning  
---|---  
Abstract This article presents by frameworks the detail of CAA resources modified in V5R7 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.
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
AnalysisMeshingModel | [R7GA vs R6GA](AnalysisMeshingModel.md) | [R7SP vs R7GA](AnalysisMeshingModelSP.md)  

AnalysisMeshingModel | [R7GA vs R6GA](AnalysisMeshingModel.md) | [R7SP vs R7GA](AnalysisMeshingModelSP.md)
ApplicationFrame | [R7GA vs R6GA](ApplicationFrame.md) | [R7SP vs R7GA](ApplicationFrameSP.md)  
BasicTopologicalOpe |  | [R7SP vs R7GA](BasicTopologicalOpeSP.md)  
CATAnalysisBase | [R7GA vs R6GA](CATAnalysisBase.md) | [R7SP vs R7GA](CATAnalysisBaseSP.md)  
CATAnalysisInterfaces | [R7GA vs R6GA](CATAnalysisInterfaces.md) | [R7SP vs R7GA](CATAnalysisInterfacesSP.md)  
CATAnalysisResources |  | [R7SP vs R7GA](CATAnalysisResourcesSP.md)  
CATSchPlatformInterfaces |  | [R7SP vs R7GA](CATSchPlatformInterfacesSP.md)  
CATTPSInterfaces | [R7GA vs R6GA](CATTPSInterfaces.md) | [R7SP vs R7GA](CATTPSInterfacesSP.md)  
CORBAServerBase | [R7GA vs R6GA](CORBAServerBase.md) |   
Dialog | [R7GA vs R6GA](Dialog.md) | [R7SP vs R7GA](DialogSP.md)  
DialogEngine |  | [R7SP vs R7GA](DialogEngineSP.md)  
DNBInspectSharedInterfaces |  | [R7SP vs R7GA](DNBInspectSharedInterfacesSP.md)  
DraftingInterfaces | [R7GA vs R6GA](DraftingInterfaces.md) | [R7SP vs R7GA](DraftingInterfacesSP.md)  
ENOVDDManager | [R7GA vs R6GA](ENOVDDManager.md) | [R7SP vs R7GA](ENOVDDManagerSP.md)  
ENOVDesktopDocument | [R7GA vs R6GA](ENOVDesktopDocument.md) | [R7SP vs R7GA](ENOVDesktopDocumentSP.md)  
ENOVIAPlugIn | [R7GA vs R6GA](ENOVIAPlugIn.md) |   
ENOVInterfaces | [R7GA vs R6GA](ENOVInterfaces.md) | [R7SP vs R7GA](ENOVInterfacesSP.md)  
ENOVaultClientCPP | [R7GA vs R6GA](ENOVaultClientCPP.md) | [R7SP vs R7GA](ENOVaultClientCPPSP.md)  
GSMInterfaces | [R7GA vs R6GA](GSMInterfaces.md) | [R7SP vs R7GA](GSMInterfacesSP.md)  
GSOInterfaces |  | [R7SP vs R7GA](GSOInterfacesSP.md)  
GeometricObjects | [R7GA vs R6GA](GeometricObjects.md) | [R7SP vs R7GA](GeometricObjectsSP.md)  
InteractiveInterfaces |  | [R7SP vs R7GA](InteractiveInterfacesSP.md)  
KinematicsInterfaces | [R7GA vs R6GA](KinematicsInterfaces.md) |   
LiteralFeatures | [R7GA vs R6GA](LiteralFeatures.md) | [R7SP vs R7GA](LiteralFeaturesSP.md)  
ManufacturingInterfaces | [R7GA vs R6GA](ManufacturingInterfaces.md) | [R7SP vs R7GA](ManufacturingInterfacesSP.md)  
Mathematics |  | [R7SP vs R7GA](MathematicsSP.md)  
MecModInterfaces | [R7GA vs R6GA](MecModInterfaces.md) | [R7SP vs R7GA](MecModInterfacesSP.md)  
MechanicalModeler | [R7GA vs R6GA](MechanicalModeler.md) | [R7SP vs R7GA](MechanicalModelerSP.md)  
NewTopologicalObjects | [R7GA vs R6GA](NewTopologicalObjects.md) |   
ObjectModelerBase | [R7GA vs R6GA](ObjectModelerBase.md) | [R7SP vs R7GA](ObjectModelerBaseSP.md)  
ObjectSpecsModeler | [R7GA vs R6GA](ObjectSpecsModeler.md) | [R7SP vs R7GA](ObjectSpecsModelerSP.md)  
PartInterfaces | [R7GA vs R6GA](PartInterfaces.md) | [R7SP vs R7GA](PartInterfacesSP.md)  
Print | [R7GA vs R6GA](Print.md) | [R7SP vs R7GA](PrintSP.md)  
ProductStructure | [R7GA vs R6GA](ProductStructure.md) |   
System | [R7GA vs R6GA](System.md) | [R7SP vs R7GA](SystemSP.md)  
TopologicalOperators | [R7GA vs R6GA](TopologicalOperators.md) | [R7SP vs R7GA](TopologicalOperatorsSP.md)  
Tessellation |  | [R7SP vs R7GA](TessellationSP.md)  
VPMDesktopObjects | [R7GA vs R6GA](VPMDesktopObjects.md) | [R7SP vs R7GA](VPMDesktopObjectsSP.md)  
VPMInterfaces | [R7GA vs R6GA](VPMInterfaces.md) | [R7SP vs R7GA](VPMInterfacesSP.md)  
VPMXBom | [R7GA vs R6GA](VPMXBom.md) |   
VPMServices |  | [R7SP vs R7GA](VPMServicesSP.md)  
Visualization | [R7GA vs R6GA](Visualization.md) | [R7SP vs R7GA](VisualizationSP.md)  

* * *

VPMServices |  | [R7SP vs R7GA](VPMServicesSP.md)
Visualization | [R7GA vs R6GA](Visualization.md) | [R7SP vs R7GA](VisualizationSP.md)
References [1] | [Migration to CATBoolean](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean)  

[Top]  

* * *

History Version: **1** [May 2001] | Document created  
---|---  
[Top]  

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
