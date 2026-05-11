---
```vbscript
title: "DNBD5IInterfaces Framework Modifications in V5R18"
category: "use-case"
module: "CAACenAPIChangesR18"
version: "V5R18"
tags: []
source_file: "Doc/online/CAACenAPIChangesR18/DNBD5IInterfaces.htm"
converted: "2026-05-11T17:33:51.466200"
```

---
# CAA C++ API Modifications

|
##  DNBD5IInterfaces Framework Modifications in V5R18

* * *

**Entity|  SP| Modification| To Do** | DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/GetVisCoorsys
**Prototype:**`virtual HRESULT GetVisCoorsys(CATBoolean& ioVisCoorsys)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| D5 Visibility has 3 possible states. All methods dealing with visibility have been modified accordingly: they now have arguments of enumerate type FrameVisibility instead of arguments of type CATBoolean.
---|---|---|---
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/SetVisCoorsys
**Prototype:**`virtual HRESULT SetVisCoorsys(const CATBoolean iVisCoorsys)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| See upper.
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/SetVisCoorsys
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/GetVisToolFrm

**Prototype:**`virtual HRESULT GetVisToolFrm(CATBoolean& ioVisToolFrm)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| See upper.
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/SetVisCoorsys
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/GetVisToolFrm
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/SetVisToolFrm

**Prototype:**`virtual HRESULT SetVisToolFrm(const CATBoolean iVisToolFrm)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| See upper.
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/GetVisToolFrm
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/SetVisToolFrm
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/GetVisBaseFrm

**Prototype:**`virtual HRESULT GetVisBaseFrm(CATBoolean& ioVisBaseFrm)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| See upper.
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/SetVisToolFrm
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/GetVisBaseFrm
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/SetVisBaseFrm

**Prototype:**`virtual HRESULT SetVisBaseFrm(const CATBoolean iVisBaseFrm)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| See upper.
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/GetVisBaseFrm
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/SetVisBaseFrm
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/GetVisWclPath

**Prototype:**`virtual HRESULT GetVisWclPath(CATBoolean& ioVisWclPath)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| See upper.
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/SetVisBaseFrm
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/GetVisWclPath
DNBD5IInterfaces/Public/DNBID5IImportD5SettingAtt.h/DNBID5IImportD5SettingAtt/SetVisWclPath

**Prototype:**`virtual HRESULT SetVisWclPath(const CATBoolean iVisWclPath)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| See upper.
