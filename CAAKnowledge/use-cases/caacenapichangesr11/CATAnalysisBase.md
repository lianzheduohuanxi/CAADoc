---
title: "CATAnalysisBase Modifications"
category: "use-case"
module: "CAACenAPIChangesR11"
version: "V5R11"
tags: []
source_file: "Doc/online/CAACenAPIChangesR11/CATAnalysisBase.md"
converted: "2026-05-11T17:33:50.332054"
---

CAA C++ API Modifications |  CATAnalysisBase |   
---|---|---  
  
* * *

** Entity | SP | Modification | To Do** | CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/CATSamDimension | GA | MHBDM | [see dedicated article](../CAAAniQuickRefs/CAAAniFaq.htm#Dimension11)  
---|---|---|---  
CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/Fill | GA | MHBDM | [see dedicated article](../CAAAniQuickRefs/CAAAniFaq.htm#Dimension11)  
CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/SetNbPositions | GA | MHBDM | [see dedicated article](../CAAAniQuickRefs/CAAAniFaq.htm#Dimension11)  
CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/SetNbLaminates | GA | MHBDM | [see dedicated article](../CAAAniQuickRefs/CAAAniFaq.htm#Dimension11)  
CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/SetNbSMI | GA | MHBDM | [see dedicated article](../CAAAniQuickRefs/CAAAniFaq.htm#Dimension11)  
CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/SetNbRepeat | GA | MHBDM | [see dedicated article](../CAAAniQuickRefs/CAAAniFaq.htm#Dimension11)  
CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/SetNbComponents | GA | MHBDM | [see dedicated article](../CAAAniQuickRefs/CAAAniFaq.htm#Dimension11)  
CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/SetUnitaryValueSize | GA | MHBDM | [see dedicated article](../CAAAniQuickRefs/CAAAniFaq.htm#Dimension11)  
CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/GetNbRepeat | GA | MHBDM | [see dedicated article](../CAAAniQuickRefs/CAAAniFaq.htm#Dimension11)  
CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/GetRepeat | GA | MHBDM | [see dedicated article](../CAAAniQuickRefs/CAAAniFaq.htm#Dimension11)  
CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/GetAggregationMode | GA | MHBDM | [see dedicated article](../CAAAniQuickRefs/CAAAniFaq.htm#Dimension11)  
CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/GetNbValues | GA | MHBDM | [see dedicated article](../CAAAniQuickRefs/CAAAniFaq.htm#Dimension11)  
CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/GetSizeValues | GA | MHBDM | [see dedicated article](../CAAAniQuickRefs/CAAAniFaq.htm#Dimension11)  
CATAnalysisBase/Protected/CATAnalysisExplicitListATo.h/CATAnalysisExplicitListATo/GetContents | GA | ADVHC | In all overloaded _GetContents_ functions, the default value of the last argument has been chaged from _CATSamMeshTypePhysical_ to _CATSamMeshTypeAll_.  
CATAnalysisBase/Protected/CATAnalysisExplicitParent.h/CATAnalysisExplicitParent/FindCharacCollector | GA | MHBDM | A new parameter iEntityFlagsNumber has been added, with a default value but not at the end because it's the most frequently used among parameters with a default value.  
CATAnalysisBase/Protected/CATAnalysisExplicitTopology.h/CATAnalysisExplicitTopology/SetMeshManager | GA | INDM | Check that you don't use it
