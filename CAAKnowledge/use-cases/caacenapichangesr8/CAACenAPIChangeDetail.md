---
title: "Detail Of C++ API Changes"
category: "general"
module: "CAACenAPIChangesR8"
tags: ["CAA2Usage", "CAA2Level"]
source_file: "Doc\online\CAACenAPIChangesR8\CAACenAPIChangeDetail.htm"
converted: "2026-05-11T17:33:52.391824"
---

|  |  Detail Of V5R8 C++ API Changes _What changes in the API compared with CAA V5R7_  
---|---|---  
Technical Article  
  
* * *

Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5R8 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.  
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

AdvancedMathematics |  | [R8SP vs R8GA](AdvancedMathematicsSP.htm)  
---|---|---  
AnalysisMeshingModel | [R8GA vs R7GA](AnalysisMeshingModel.htm) |   
ApplicationFrame | [R8GA vs R7GA](ApplicationFrame.htm) | [R8SP vs R8GA](ApplicationFrameSP.htm)  
BasicTopologicalOpe | [R8GA vs R7GA](BasicTopologicalOpe.htm) | [R8SP vs R8GA](BasicTopologicalOpeSP.htm)  
CATAnalysisBase | [R8GA vs R7GA](CATAnalysisBase.htm) | [R8SP vs R8GA](CATAnalysisBaseSP.htm)  
CATAnalysisInterfaces | [R8GA vs R7GA](CATAnalysisInterfaces.htm) | [R8SP vs R8GA](CATAnalysisInterfacesSP.htm)  
CATAnalysisResources | [R8GA vs R7GA](CATAnalysisResources.htm) |   
CATSchPlatformInterfaces | [R8GA vs R7GA](CATSchPlatformInterfaces.htm) |   
CATTPSInterfaces | [R8GA vs R7GA](CATTPSInterfaces.htm) [ | R8rel vs R8GA](CATTPSInterfacesSP.htm) |   
CDMAInteroperability | [R8GA vs R7GA](CDMAInteroperability.htm) |   
CORBAServerBase | [R8GA vs R7GA](CORBAServerBase.htm) |   
Dialog | [R8GA vs R7GA](Dialog.htm) | [R8SP vs R8GA](DialogSP.htm)  
DialogEngine | [R8GA vs R7GA](DialogEngine.htm) |   
DNBInspectInterfaces | [R8GA vs R7GA](DNBInspectInterfaces.htm) |   
DNBInspectSharedInterfaces | [R8GA vs R7GA](DNBInspectSharedInterfaces.htm) |   
DraftingInterfaces | [R8GA vs R7GA](DraftingInterfaces.htm) | [R8SP vs R8GA](DraftingInterfacesSP.htm)  
ElectricalInterfaces | [R8GA vs R7GA](ElectricalInterfaces.htm) |   
ENOVDDManager | [R8GA vs R7GA](ENOVDDManager.htm) |   
ENOVDesktopDocument | [R8GA vs R7GA](ENOVDesktopDocument.htm) |   
ENOVInterfaces | [R8GA vs R7GA](ENOVInterfaces.htm) | [R8SP vs R8GA](ENOVInterfacesSP.htm)  
ENOVaultClientCPP | [R8GA vs R7GA](ENOVaultClientCPP.htm) | [R8SP vs R8GA](ENOVaultClientCPPSP.htm)  
FreeFormOperators | [R8GA vs R7GA](FreeFormOperators.htm) |   
GeometricObjects | [R8GA vs R7GA](GeometricObjects.htm) | [R8SP vs R8GA](GeometricObjectsSP.htm)  
GSMInterfaces | [R8GA vs R7GA](GSMInterfaces.htm) | [R8SP vs R8GA](GSMInterfacesSP.htm)  
GSOInterfaces | [R8GA vs R7GA](GSOInterfaces.htm) |   
InteractiveInterfaces | [R8GA vs R7GA](InteractiveInterfaces.htm) |   
KnowHow |  | [R8SP vs R8GA](KnowHowSP.htm)  
LiteralFeatures | [R8GA vs R7GA](LiteralFeatures.htm) | [R8SP vs R8GA](LiteralFeaturesSP.htm)  
ManufacturingInterfaces | [R8GA vs R7GA](ManufacturingInterfaces.htm) |   
Mathematics | [R8GA vs R7GA](Mathematics.htm) | [R8SP vs R8GA](MathematicsSP.htm)  
MecModInterfaces | [R8GA vs R7GA](MecModInterfaces.htm) |   
MechanicalModeler | [R8GA vs R7GA](MechanicalModeler.htm) |   
MechanicalModelerUI |  | [R8SP vs R8GA](MechanicalModelerUISP.htm)  
NewTopologicalObjects | [R8GA vs R7GA](NewTopologicalObjects.htm) | [R8SP vs R8GA](NewTopologicalObjectsSP.htm)  
ObjectModelerBase | [R8GA vs R7GA](ObjectModelerBase.htm) | [R8SP vs R8GA](ObjectModelerBaseSP.htm)  
ObjectSpecsModeler | [R8GA vs R7GA](ObjectSpecsModeler.htm) |   
PartInterfaces | [R8GA vs R7GA](PartInterfaces.htm) |   
Print | [R8GA vs R7GA](Print.htm) |   
ProductStructure | [R8GA vs R7GA](ProductStructure.htm) |   
System | [R8GA vs R7GA](System.htm) |   
SetcherInterfaces |  | [R8SP vs R8GA](SketcherInterfacesSP.htm)  
Tessellation | [R8GA vs R7GA](Tessellation.htm) |   
TopologicalOperators | [R8GA vs R7GA](TopologicalOperators.htm) |   
Visualization | [R8GA vs R7GA](Visualization.htm) | [R8SP vs R8GA](VisualizationSP.htm)  
VPMInterfaces | [R8GA vs R7GA](VPMInterfaces.htm) | [R8SP vs R8GA](VPMInterfacesSP.htm)  
VPMPersistency |  | [R8SP vs R8GA](VPMPersistencySP.htm)  
VPMDesktopServices | [R8GA vs R7GA](VPMDesktopServices.htm) | [R8SP vs R8GA](VPMDesktopServicesSP.htm)  
VPMServices | [R8GA vs R7GA](VPMServices.htm) |   
VPMXBom |  | [R8rel vs R8GA](VPMXBomSP.htm)  
  
* * *

References [1] | [Migration to CATBoolean](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean)  
---|---  
[2] | [Details Of V5R7 API Changes](../CAACenAPIChangesR7/CAACenAPIChangeDetail.htm)  
[Top]  
  
* * *

History Version: **1** [Dec 2001] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
