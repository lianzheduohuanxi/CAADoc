---
title: "CATIAV4Interfaces Framework Modifications in V5R15"
category: "use-case"
module: "CAACenAPIChangesR15"
version: "V5R15"
tags: ["CATIAV4Interfaces", "CATIV4IInteropSettingAtt"]
source_file: "Doc/online/CAACenAPIChangesR15/CATIAV4Interfaces.md"
converted: "2026-05-11T17:33:51.068143"
---
# CAA C++ API Modifications  
  
| 
##  CATIAV4Interfaces Framework Modifications in V5R15 

  
* * *

**Entity|  SP| Modification| To Do** | CATIAV4Interfaces/Public/CATIV4IInteropSettingAtt.h/CATIV4IInteropSettingAtt/GetPrj_Warn  
**Prototype:**`virtual HRESULT GetPrj_Warn(CATString & oDefaultWarn)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Removed, corresponding setting never implemented, so was useless.  
---|---|---|---  
CATIAV4Interfaces/Public/CATIV4IInteropSettingAtt.h/CATIV4IInteropSettingAtt/SetPrj_Warn  
**Prototype:**`virtual HRESULT SetPrj_Warn(CATString & iDefaultWarn)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Removed, corresponding setting never implemented, so was useless.  
CATIAV4Interfaces/Public/CATIV4IInteropSettingAtt.h/CATIV4IInteropSettingAtt/GetPrj_WarnInfo  
**Prototype:**`virtual HRESULT GetPrj_WarnInfo(CATSettingInfo* oInfo)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Removed, corresponding setting never implemented, so was useless.  
CATIAV4Interfaces/Public/CATIV4IInteropSettingAtt.h/CATIV4IInteropSettingAtt/SetPrj_WarnLock  
**Prototype:**`virtual HRESULT SetPrj_WarnLock(unsigned char iLocked)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Removed, corresponding setting never implemented, so was useless.
