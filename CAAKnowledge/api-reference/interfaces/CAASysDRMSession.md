---
title: "CAASysDRMSession"
type: "interface"
module: "CAAxPDMInterfaces"
base: "CATBaseUnknown"
method_count: 6
visibility: "local"
verified: true
---

# CAASysDRMSession

**基类**: CATBaseUnknown  
**模块**: CAAxPDMInterfaces  
**可见性**: local  
**方法数**: 6

## 方法列表

### DRMInitSession
```cpp
HRESULT DRMInitSession();
```

### DRMGetPolicy
```cpp
HRESULT DRMGetPolicy(DWORD iPolicy);
```

### DRMCloseSession
```cpp
HRESULT DRMCloseSession();
```

### DRMGetProviderName
```cpp
HRESULT DRMGetProviderName(CATUnicodeString &oName);
```

### BuildAboutFrame
```cpp
HRESULT BuildAboutFrame(CATDlgFrame *iParentFrame);
```

### BuildEditRightFrame
```cpp
HRESULT BuildEditRightFrame(CATDlgFrame *iParentFrame,
     const void *iDRMAuthorization,
     size_t iDRMAuthorizationSize,
     CATDlgFrame **oCreatedFrame);
```

## 依赖

- `CATBaseUnknown.h`
- `CATUnicodeString.h`

