---
```vbscript
title: "CATAnalysisInterfaces Framework Modifications in V5R15"
category: "use-case"
module: "CAACenAPIChangesR15"
version: "V5R15"
tags: ["CATISamBasicComponent", "CATISpecObject", "CATISamAnalysisModelFactory"]
source_file: "Doc/online/CAACenAPIChangesR15/CATAnalysisInterfaces.htm"
converted: "2026-05-11T17:33:51.055882"
```

---
| 
# CAA C++ API Modifications

| 
##  CATAnalysisInterfaces Framework Modifications in V5R15 

* * *

**Entity|  SP| Modification| To Do** | CATAnalysisInterfaces/Public/CATISamBasicComponent.h/CATISamBasicComponent/SetValue  
**Prototype:**`virtual HRESULT SetValue(void* iValue,const CATUnicodeString& iLabel = NULL,int iLineIndex=0,int iColumnIndex=0,int iLayerIndex=0)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Has been removed, had never been implemented so was useless.  
---|---|---|---  
CATAnalysisInterfaces/Public/CATISamBasicComponent.h/CATISamBasicComponent/GetValue  
**Prototype:**`virtual HRESULT GetValue(void** oValue,const CATUnicodeString& iLabel = NULL,int iLineIndex=0,int iColumnIndex=0,int iLayerIndex=0)const = 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Has been removed, had never been implemented so was useless.  
CATAnalysisInterfaces/Public/CATISamAnalysisModelFactory.h/CATISamAnalysisModelFactory/CreateAnalysisModel  
**Prototype:**`virtual CATISpecObject* CreateAnalysisModel(const CATUnicodeString& iName)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Useless method presenting risks of data corruption: an Analysis Model always exist, no need to create a new one.
