---
title: "CAAISysName"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
visibility: "public"
verified: true
---

# CAAISysName

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: public  
**方法数**: 2

> System Framework

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
- `CAASysGeoModelInf.h`

