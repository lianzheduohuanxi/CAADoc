---
title: "CAAISysTextureProperties"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
visibility: "public"
verified: true
---

# CAAISysTextureProperties

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: public  
**方法数**: 4

> System Framework

## 方法列表

### GetMetal
```cpp
HRESULT GetMetal(int & oIsMetal);
```

### SetMetal
```cpp
HRESULT SetMetal(const int iIsMetal);
```

### GetRough
```cpp
HRESULT GetRough(int & oIsMetal);
```

### SetRough
```cpp
HRESULT SetRough(const int iIsMetal);
```

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

