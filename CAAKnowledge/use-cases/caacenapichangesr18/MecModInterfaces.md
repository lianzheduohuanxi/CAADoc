---
title: "MecModInterfaces Framework Modifications in V5R18"
category: "general"
module: "CAACenAPIChangesR18"
tags: ["CATIMfBRep", "CATIMmiPartInfrastructureSettingAtt"]
source_file: "Doc\online\CAACenAPIChangesR18\MecModInterfaces.htm"
converted: "2026-05-11T17:33:51.487243"
---

# CAA C++ API Modifications  
  
| 

##  MecModInterfaces Framework Modifications in V5R18 

|   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | MecModInterfaces/Public/CATIMfBRep.h/CATIMfBRep/UpdateSupport  
**Prototype:**`virtual void UpdateSupport(const CATMfBRepUpdateSupport iMode)=0;`| GA| [MRTHC](CAACenAPIChangeDetail.htm#Abstract)| Return type has changed frmo void to HRESULT: no impact.  
---|---|---|---  
MecModInterfaces/Public/CATIMmiPartInfrastructureSettingAtt.h/CATIMmiPartInfrastructureSettingAtt/GetModelSize  
**Prototype:**`virtual HRESULT GetModelSize(CatPartModelSize& oModelSize)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| The corresponding setting parameter doesn't exit anymore, this method so became useless and has been removed.  
MecModInterfaces/Public/CATIMmiPartInfrastructureSettingAtt.h/CATIMmiPartInfrastructureSettingAtt/GetModelSizeInfo  
**Prototype:**`virtual HRESULT GetModelSizeInfo(CATSettingInfo* oInfo)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| The correseponding setting parameter doesn't exit anymore, this method so became useless and has been removed.
