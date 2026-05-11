---
title: "CAAESysName"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
visibility: "local"
verified: true
---

# CAAESysName

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: local  
**方法数**: 2

> ----------------------

## 方法列表

### SetName
```cpp
HRESULT SetName(const CATUnicodeString & iName);
```

### GetName
```cpp
HRESULT GetName(CATUnicodeString & ioName);
```

## 依赖

- `CATBaseUnknown.h`
- `CATUnicodeString.h`

