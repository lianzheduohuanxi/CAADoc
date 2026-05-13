---
title: "Detail Of C++ API Changes"
category: "use-case"
module: "CAACenAPIChangesR21"
tags: "["CAA2Usage", "CAA2Level", "CATInstantCollabDesignCAAItf"]"
source_file: "Doc/online/CAACenAPIChangesR21/CAACenAPIChangeDetail.htm"
converted: "2026-05-11T17:33:51.652100"
---
|
#

|
##

|
### Detail Of V5R21 C++ API Changes

_What changes in the API compared with CAA V5R20_
---|---|---
Technical Article

* * *
### Abstract

This article presents by frameworks the detail of CAA C++ resources modified in V5R21 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.
| Classification | Meaning
---|---
This article presents by frameworks the detail of CAA C++ resources modified in V5R21 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.
LHC | @CAA2Level Has Changed: a L1 file is no more L1.
UHC | @CAA2Usage Has Changed: usage has changed for a more restricted usage. For example a class tagged as derivable is not derivable anymore.
CHBD | Class Has Been Deleted
FHBD | File Has Been Deleted
ADVHC | Argument Default Value Has Changed
MHBDM | Method Has Been Deleted or Modified
MRTHC | Method Returned Type Has Changed
NPVM | New Pure Virtual Method. A new pure virtual method has been added on a derivable class or on an interface to be implemented without an adapter.
INDM | Method is no more documented. It does not break your code in any way but means that you are not supposed to use it anymore. Check that you don't use it or look for replacement informations.
MINMV | Method is no more virtual. If occurs on a U1 class, may require modifications in Imakefile.mk of client code. If occurs on a U2 class, see details on the documentation of the concerned resource modification.

* * *

CATInstantCollabDesignCAAItf | [R21GA vs R20GA](CATInstantCollabDesignCAAItf.md) |
---|---|---
CATInstantCollabDesignCAAItf | [R21GA vs R20GA](CATInstantCollabDesignCAAItf.md) |
BasicTopologicalOpe | [R21GA vs R20GA](BasicTopologicalOpe.md) |
CATPlantShipInterfaces | [R21GA vs R20GA](CATPlantShipInterfaces.md) |
GeometricObjects | [R21GA vs R20GA](GeometricObjects.md) |
GMOperatorsInterfaces | [R21GA vs R20GA](GMOperatorsInterfaces.md) |
Mathematics | [R21GA vs R20GA](Mathematics.md) |
SketcherInterfaces | [R21GA vs R20GA](SketcherInterfaces.md) |
TopologicalOperatorsLight | [R21GA vs R20GA](TopologicalOperatorsLight.md) |  | VisualizationBase | [R21GA vs R20GA](VisualizationBase.md) |

* * *
### References

[1] | [Migration to CATBoolean](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean)
---|---
[2] | [Details Of V5R20 API Changes](../CAACenAPIChangesR20/CAACenAPIChangeDetail.md)
  |
[Top]

* * *
### History

Version: **1** [Dev 2010] | Document created
---|---
[Top]

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
