---
title: "PartInterfaces Modifications"
category: "use-case"
module: "CAACenAPIChangesR7"
version: "V5R7"
tags: ["CATIPrtFactory", "CATIDraft", "CATISweep", "CATICircPatt", "CATIRectPatt", "CATIPrtToPattern", "CATIPrtManageFeatBuild"]
source_file: "Doc/online/CAACenAPIChangesR7/PartInterfaces.md"
converted: "2026-05-11T17:33:52.210420"
---

CAA API Modifications |  PartInterfaces |   
---|---|---  
  
* * *

** Entity | Modification | To Do** | PartInterfaces/Protected/CATICircPatt.h/CATICircPatt/GetSensa | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
---|---|---  
PartInterfaces/Protected/CATICircPatt.h/CATICircPatt/GetInstRot | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
PartInterfaces/Protected/CATICircPatt.h/CATICircPatt/ModifySensa | MHBDM | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
PartInterfaces/Protected/CATICircPatt.h/CATICircPatt/ModifyInstRot | MHBDM | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
PartInterfaces/Protected/CATIDraft.h/CATIDraft/ModifyAngle  
PartInterfaces/Protected/CATIDraft.h/CATIDraft/ModifyNeutral  
PartInterfaces/Protected/CATIDraft.h/CATIDraft/ModifyPullingDirection  
PartInterfaces/Protected/CATIDraft.h/CATIDraft/GetAngle  
PartInterfaces/Protected/CATIDraft.h/CATIDraft/GetMode  
PartInterfaces/Protected/CATIDraft.h/CATIDraft/GetPullingDirection  
PartInterfaces/Protected/CATIDraft.h/CATIDraft/GetPullingDirectionObject  
PartInterfaces/Protected/CATIDraft.h/CATIDraft/GetNeutral | MHBDM | An integer argument has been added to specify side in case of draft both sides. This argument takes a default value so no build impact on existing code, no runtime impact on existing features but you may have to modify your applications to correctly deal with draft both sides ...  
PartInterfaces/Protected/CATIPrtFactory.h/CATIPrtFactory/CreateStiffener | MHBDM | The method with no arguments has been removed.The overloaded method with an argument now takes a default value. No Impact.  
PartInterfaces/Protected/CATIPrtFactory.h/CATIPrtFactory/CreateRectPatt | MHBDM | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
PartInterfaces/Protected/CATIPrtFactory.h/CATIPrtFactory/CreateCircPatt | MHBDM | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
PartInterfaces/Protected/CATIPrtManageFeatBuild.h/CATIPrtManageFeatBuild/BuildNecessity | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
PartInterfaces/Protected/CATIPrtManageFeatBuild.h/CATIPrtManageFeatBuild/ReportNecessity | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
PartInterfaces/Protected/CATIRectPatt.h/CATIRectPatt/GetSens1 | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
PartInterfaces/Protected/CATIRectPatt.h/CATIRectPatt/GetSens2 | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
PartInterfaces/Protected/CATIRectPatt.h/CATIRectPatt/ModifySens1 | MHBDM | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
PartInterfaces/Protected/CATIRectPatt.h/CATIRectPatt/ModifySens2 | MHBDM | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
PartInterfaces/Protected/CATIPrtToPattern.h/CATIPrtToPattern/SpecificPatternNecessity | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
PartInterfaces/Protected/CATIPrtToPattern.h/CATIPrtToPattern/ValidForUserPattern | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
PartInterfaces/Protected/CATISweep.h/CATISweep/HasPullingDirection | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
PartInterfaces/Protected/CATPrtManageFeatBuildExt.h/CATPrtManageFeatBuildExt/BuildNecessity | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
PartInterfaces/Protected/CATPrtManageFeatBuildExt.h/CATPrtManageFeatBuildExt/ReportNecessity | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact
