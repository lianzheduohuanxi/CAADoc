---
title: "KnowledgeInterfaces Framework Modifications in V5R17"
category: "use-case"
module: "CAACenAPIChangesR17"
version: "V5R17"
tags: ["CATILieKnowledgeSheetSettingAtt"]
source_file: "Doc/online/CAACenAPIChangesR17/KnowledgeInterfaces.md"
converted: "2026-05-11T17:33:51.342726"
---
# CAA C++ API Modifications  
  
| 
##  KnowledgeInterfaces Framework Modifications in V5R17 

  
* * *

**Entity|  SP| Modification| To Do** | KnowledgeInterfaces/Public/CATILieKnowledgeSheetSettingAtt.h/CATILieKnowledgeSheetSettingAtt/GetPreviousIncremental  
**Prototype:**`virtual HRESULT GetPreviousIncremental(int& ioPreviousIncremental)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Setting does not exist anymore. Methods allowing to manipulate it have so been removed.  
---|---|---|---  
KnowledgeInterfaces/Public/CATILieKnowledgeSheetSettingAtt.h/CATILieKnowledgeSheetSettingAtt/SetPreviousIncremental  
**Prototype:**`virtual HRESULT SetPreviousIncremental(const int& iPreviousIncremental)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Setting does not exist anymore. Methods allowing to manipulate it have so been removed.  
KnowledgeInterfaces/Public/CATILieKnowledgeSheetSettingAtt.h/CATILieKnowledgeSheetSettingAtt/GetPreviousIncrementalInfo  
**Prototype:**`virtual HRESULT GetPreviousIncrementalInfo(CATSettingInfo* oInfo)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)Setting does not exist anymore. Methods allowing to manipulate it have so been removed.|   
KnowledgeInterfaces/Public/CATILieKnowledgeSheetSettingAtt.h/CATILieKnowledgeSheetSettingAtt/SetPreviousIncrementalLock  
**Prototype:**`virtual HRESULT SetPreviousIncrementalLock(unsigned char iLocked)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Setting does not exist anymore. Methods allowing to manipulate it have so been removed.
