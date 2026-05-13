---
title: "VPMInterfaces Modifications"
category: "use-case"
module: "CAACenAPIChangesR13"
tags: "["CATICfgFilter", "CATICfgManager", "CATIVpmFactoryManager", "CATICfgModification", "CATIConfigurableObject"]"
source_file: "Doc/online/CAACenAPIChangesR13/VPMInterfaces.htm"
converted: "2026-05-11T17:33:50.799862"
---
tags: ["CATICfgFilter", "CATICfgManager", "CATIVpmFactoryManager", "CATICfgModification", "CATIConfigurableObject"]
source_file: "Doc/online/CAACenAPIChangesR13/VPMInterfaces.htmmd"
converted: "2026-05-11T17:33:50.799862"
CAA C++ API Modifications|  VPMInterfaces  |

* * *

**Entity|  SP| Modification| To Do** | VPMInterfaces/Public/CATIVpmFactoryManager.h/CATIVpmFactoryManager/RunQuery| GA| MHBDM| An argument has been added to one of the overloaded methods. This overload should not be used, so if you encounter a compilation problem, please consider using the other one.
---|---|---|---
VPMInterfaces/Public/ENOVISessionEvent.h| GA| UHC| Usage changed fro U5 to U4, please use the provided adaptor (ENOVPackageListener) implementing the interface without this adapter was very difficult. It also avoids to be impacted by future evolutions of the interface.
VPMInterfaces/Public/VPMIListOfAttributes.h| GA| FHBD| Moved into VPMDesktopServices where the scalar class (VPMIQAttribute) is, so no impact in most of the cases while IdentityCard and Imakefile.mk of client code may have to be modified accordingly.
VPMInterfaces/Public/CATICfgFilter.h/CATICfgFilter/GetListOfFilters| GA| INDM| Check that you don't use it
VPMInterfaces/Public/CATICfgFilter.h/CATICfgFilter/Filter| GA| INDM| Check that you don't use it
VPMInterfaces/Public/CATICfgFilter.h/CATICfgFilter/Copy| GA| INDM| Check that you don't use it
VPMInterfaces/Public/CATICfgManager.h/CATICfgManager/Constrain| GA| INDM| Check that you don't use it
VPMInterfaces/Public/CATICfgManager.h/CATICfgManager/ConstrainRecursively| GA| INDM| Check that you don't use it
VPMInterfaces/Public/CATICfgModification.h/CATICfgModification/GetAsString| GA| INDM| Check that you don't use it
VPMInterfaces/Public/CATIConfigurableObject.h/CATIConfigurableObject/DisplayValueForUID2| GA| INDM| Check that you don't use it
VPMInterfaces/Public/CATIConfigurableObject.h/CATIConfigurableObject/GetRootConfigurableObjects| GA| INDM| Check that you don't use it
VPMInterfaces/Public/ENOVIExpandable.h/ENOVIExpandable/get_Tree2| GA| MHBDM|
