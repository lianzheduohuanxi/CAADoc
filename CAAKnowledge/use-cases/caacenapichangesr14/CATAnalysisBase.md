---
title: "CATAnalysisBase Framework Modifications in V5R14"
category: "general"
module: "CAACenAPIChangesR14"
tags: ["CATIMSHMeshManager"]
source_file: "Doc\online\CAACenAPIChangesR14\CATAnalysisBase.htm"
converted: "2026-05-11T17:33:50.841308"
---

CAA C++ API Modifications|  CATAnalysisBase Framework Modifications in V5R14 |   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | CATAnalysisBase/Public/CATAnalysisExplicitTopology.h/CATAnalysisExplicitTopology/CleanAllMemory  
**Prototype:**`virtual HRESULT CleanAllMemory()= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Removed because useless and data corruption-prone: life cycle of those objects is to be managed by the system and not by the application. Use CATAnalysisExplicitModel::GetExplicitTopology.  
---|---|---|---  
CATAnalysisBase/Public/CATAnalysisExplicitTopology.h/CATAnalysisExplicitTopology/CATAnalysisExplicitTopology  
**Prototype:**`CATAnalysisExplicitTopology(const CATAnalysisExplicitParent &iFEMModel;,const CATIMSHMeshManager*iMeshManager = NULL);`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Removed because useless and data corruption-prone: life cycle of those objects is to be managed by the system and not by the application. Use CATAnalysisExplicitModel::GetExplicitTopology.  
CATAnalysisBase/Public/CATAnalysisExplicitTopology.h/CATAnalysisExplicitTopology/~CATAnalysisExplicitTopology  
**Prototype:**`virtual ~CATAnalysisExplicitTopology();`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Removed because of memory corruption risks, don't use this destructor. Use CATAnalysisExplicitModel::GetExplicitTopology.  
CATAnalysisBase/Public/CATAnalysisExplicitAxis.h/CATAnalysisExplicitAxis/Convert  
**Prototype:**`HRESULT Convert(int iRepeat,double ioCoordinates[3],CATBoolean iReverse = FALSE);`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Deprecated with wrong syntax since V5R11. Beware: doesn't do what it is supposed to do. Use the GetImplicitDefinition method instead.  
CATAnalysisBase/Public/CATSamDimension.h/CATSamDimension/SetNbRepeat  
**Prototype:**`void SetNbRepeat(int iPositionIndex,int iNbRepeats,const int* const iRepeatsNumber = NULL,const CATSamAggregationMode* const iAggregationMode = NULL);`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| [Linked to V5R13 modification on CATAnalysisExplicitTopology usage.](../CAAAniQuickRefs/CAAAniFaq.htm)  
CATAnalysisBase/Public/CATSamDimension.h/CATSamDimension/GetNbRepeat  
**Prototype:**`int GetNbRepeat(int iPosition)const;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| [Linked to V5R13 modification on CATAnalysisExplicitTopology usage.](../CAAAniQuickRefs/CAAAniFaq.htm)  
CATAnalysisBase/Public/CATSamDimension.h/CATSamDimension/GetRepeat  
**Prototype:**`const int* GetRepeat(int iPosition)const;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| [Linked to V5R13 modification on CATAnalysisExplicitTopology usage.](../CAAAniQuickRefs/CAAAniFaq.htm)  
CATAnalysisBase/Public/CATSamDimension.h/CATSamDimension/GetAggregationMode  
**Prototype:**`const CATSamAggregationMode* GetAggregationMode(int iPosition)const;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| [Linked to V5R13 modification on CATAnalysisExplicitTopology usage.](../CAAAniQuickRefs/CAAAniFaq.htm)  
CATAnalysisBase/Public/CATSamDimension.h/CATSamDimension/GetNbValues  
**Prototype:**`int GetNbValues(int iPosition)const;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| [Linked to V5R13 modification on CATAnalysisExplicitTopology usage.](../CAAAniQuickRefs/CAAAniFaq.htm)  
CATAnalysisBase/Public/CATSamDimension.h/CATSamDimension/GetSizeValues  
**Prototype:**`int GetSizeValues(int iPosition)const;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| [Linked to V5R13 modification on CATAnalysisExplicitTopology usage.](../CAAAniQuickRefs/CAAAniFaq.htm)
