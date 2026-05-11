---
title: "CAAESysUExitIO"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 3
visibility: "local"
verified: true
---

# CAAESysUExitIO

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: local  
**方法数**: 3

> The component CATUExitIO is defined in the System FW.

## 方法列表

### OnOpen
```cpp
HRESULT OnOpen(const CATUnicodeString *iFileName,
                            CATAccessRight iMode, 
                            HRESULT *oGranted, 
                             CATFileSystemError *oError);
```

### CreationMask
```cpp
HRESULT CreationMask(const CATUnicodeString *iFileName, 
                                  DWORD *oMode, 
                                  CATFileSystemError *oError);
```

### OnClose
```cpp
HRESULT OnClose(const CATUnicodeString *iFileName,
			     CATFileSystemError *oError);
```

## 依赖

- `CATBaseUnknown.h`
- `CATIUExitIO.h`
- `CATBoolean.h`

