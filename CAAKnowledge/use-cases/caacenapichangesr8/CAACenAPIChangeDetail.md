---
```vbscript
title: "Detail Of C++ API Changes"
category: "api-changes"
module: "CAACenAPIChangesR8"
version: "V5R8"
tags: ["CAA2Usage", "CAA2Level"]
source_file: "Doc/online/CAACenAPIChangesR8/CAACenAPIChangeDetail.htm"
converted: "2026-05-11T17:33:52.391824"
```

---
|  |  Detail Of V5R8 C++ API Changes _What changes in the API compared with CAA V5R7_  
---|---|---  
Technical Article  

* * *

Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5R8 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.  
| Classification | Meaning  
---|---  
Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5R8 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.
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
AdvancedMathematics |  | [R8SP vs R8GA](AdvancedMathematicsSP.md)  

AdvancedMathematics |  | [R8SP vs R8GA](AdvancedMathematicsSP.md)
AnalysisMeshingModel | [R8GA vs R7GA](AnalysisMeshingModel.md) |   
ApplicationFrame | [R8GA vs R7GA](ApplicationFrame.md) | [R8SP vs R8GA](ApplicationFrameSP.md)  
BasicTopologicalOpe | [R8GA vs R7GA](BasicTopologicalOpe.md) | [R8SP vs R8GA](BasicTopologicalOpeSP.md)  
CATAnalysisBase | [R8GA vs R7GA](CATAnalysisBase.md) | [R8SP vs R8GA](CATAnalysisBaseSP.md)  
CATAnalysisInterfaces | [R8GA vs R7GA](CATAnalysisInterfaces.md) | [R8SP vs R8GA](CATAnalysisInterfacesSP.md)  
CATAnalysisResources | [R8GA vs R7GA](CATAnalysisResources.md) |   
CATSchPlatformInterfaces | [R8GA vs R7GA](CATSchPlatformInterfaces.md) |   
CATTPSInterfaces | [R8GA vs R7GA](CATTPSInterfaces.md) [ | R8rel vs R8GA](CATTPSInterfacesSP.md) |   
CDMAInteroperability | [R8GA vs R7GA](CDMAInteroperability.md) |   
CORBAServerBase | [R8GA vs R7GA](CORBAServerBase.md) |   
Dialog | [R8GA vs R7GA](Dialog.md) | [R8SP vs R8GA](DialogSP.md)  
DialogEngine | [R8GA vs R7GA](DialogEngine.md) |   
DNBInspectInterfaces | [R8GA vs R7GA](DNBInspectInterfaces.md) |   
DNBInspectSharedInterfaces | [R8GA vs R7GA](DNBInspectSharedInterfaces.md) |   
DraftingInterfaces | [R8GA vs R7GA](DraftingInterfaces.md) | [R8SP vs R8GA](DraftingInterfacesSP.md)  
ElectricalInterfaces | [R8GA vs R7GA](ElectricalInterfaces.md) |   
ENOVDDManager | [R8GA vs R7GA](ENOVDDManager.md) |   
ENOVDesktopDocument | [R8GA vs R7GA](ENOVDesktopDocument.md) |   
ENOVInterfaces | [R8GA vs R7GA](ENOVInterfaces.md) | [R8SP vs R8GA](ENOVInterfacesSP.md)  
ENOVaultClientCPP | [R8GA vs R7GA](ENOVaultClientCPP.md) | [R8SP vs R8GA](ENOVaultClientCPPSP.md)  
FreeFormOperators | [R8GA vs R7GA](FreeFormOperators.md) |   
GeometricObjects | [R8GA vs R7GA](GeometricObjects.md) | [R8SP vs R8GA](GeometricObjectsSP.md)  
GSMInterfaces | [R8GA vs R7GA](GSMInterfaces.md) | [R8SP vs R8GA](GSMInterfacesSP.md)  
GSOInterfaces | [R8GA vs R7GA](GSOInterfaces.md) |   
InteractiveInterfaces | [R8GA vs R7GA](InteractiveInterfaces.md) |   
KnowHow |  | [R8SP vs R8GA](KnowHowSP.md)  
LiteralFeatures | [R8GA vs R7GA](LiteralFeatures.md) | [R8SP vs R8GA](LiteralFeaturesSP.md)  
ManufacturingInterfaces | [R8GA vs R7GA](ManufacturingInterfaces.md) |   
Mathematics | [R8GA vs R7GA](Mathematics.md) | [R8SP vs R8GA](MathematicsSP.md)  
MecModInterfaces | [R8GA vs R7GA](MecModInterfaces.md) |   
MechanicalModeler | [R8GA vs R7GA](MechanicalModeler.md) |   
MechanicalModelerUI |  | [R8SP vs R8GA](MechanicalModelerUISP.md)  
NewTopologicalObjects | [R8GA vs R7GA](NewTopologicalObjects.md) | [R8SP vs R8GA](NewTopologicalObjectsSP.md)  
ObjectModelerBase | [R8GA vs R7GA](ObjectModelerBase.md) | [R8SP vs R8GA](ObjectModelerBaseSP.md)  
ObjectSpecsModeler | [R8GA vs R7GA](ObjectSpecsModeler.md) |   
PartInterfaces | [R8GA vs R7GA](PartInterfaces.md) |   
Print | [R8GA vs R7GA](Print.md) |   
ProductStructure | [R8GA vs R7GA](ProductStructure.md) |   
System | [R8GA vs R7GA](System.md) |   
SetcherInterfaces |  | [R8SP vs R8GA](SketcherInterfacesSP.md)  
Tessellation | [R8GA vs R7GA](Tessellation.md) |   
TopologicalOperators | [R8GA vs R7GA](TopologicalOperators.md) |   
Visualization | [R8GA vs R7GA](Visualization.md) | [R8SP vs R8GA](VisualizationSP.md)  
VPMInterfaces | [R8GA vs R7GA](VPMInterfaces.md) | [R8SP vs R8GA](VPMInterfacesSP.md)  
VPMPersistency |  | [R8SP vs R8GA](VPMPersistencySP.md)  
VPMDesktopServices | [R8GA vs R7GA](VPMDesktopServices.md) | [R8SP vs R8GA](VPMDesktopServicesSP.md)  
VPMServices | [R8GA vs R7GA](VPMServices.md) |   
VPMXBom |  | [R8rel vs R8GA](VPMXBomSP.md)  

* * *

VPMServices | [R8GA vs R7GA](VPMServices.md) |
VPMXBom |  | [R8rel vs R8GA](VPMXBomSP.md)
References [1] | [Migration to CATBoolean](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean)  

[2] | [Details Of V5R7 API Changes](../CAACenAPIChangesR7/CAACenAPIChangeDetail.md)  
[Top]  

* * *

History Version: **1** [Dec 2001] | Document created  
---|---  
[Top]  

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
