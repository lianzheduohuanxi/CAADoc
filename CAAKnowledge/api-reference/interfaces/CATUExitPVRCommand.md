---
title: "CATUExitPVRCommand"
type: "interface"
module: "CAACATPDMReconcile"
base: "CATBaseUnknown"
method_count: 3
visibility: "local"
verified: true
---

# CATUExitPVRCommand

**基类**: CATBaseUnknown  
**模块**: CAACATPDMReconcile  
**可见性**: local  
**方法数**: 3

> -----------------------------------------------------------------------

## 方法列表

### AfterPRCOpenFromPVR
```cpp
HRESULT AfterPRCOpenFromPVR(CATDocument * ixPVRDoc , CATDocument * ixPRCDoc);
```

### UpdateAttributeOnPvrSynchro
```cpp
HRESULT UpdateAttributeOnPvrSynchro(CATDocument      * ixPVRDoc
                                                , int                inIsyncNeeded
                                                , CATUnicodeString & ocAttrId 
                                                , CATUnicodeString & ocAttrVal);
```

### GetDefaultNamesForPVRCreation
```cpp
HRESULT GetDefaultNamesForPVRCreation(int                                ilNewFrom
                                                  , int                                ilFilteredPVR
                                                  , const CATListValCATUnicodeString & iAttributeIdLst
                                                  , const CATListValCATUnicodeString & iAttributeValueLst
                                                  , CATUnicodeString                 & iocPVRName
                                                  , CATUnicodeString                 & iocPVSName);
```

## 依赖

- `CATBaseUnknown.h`
- `CATIUExitPVRCommands.h`
- `CATErrorDef.h`

