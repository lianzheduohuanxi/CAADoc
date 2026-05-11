---
title: "CAAISysPointProperties"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
visibility: "public"
verified: true
---

# CAAISysPointProperties

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: public  
**方法数**: 2

> System Framework

## 方法列表

### GetMarkerType
```cpp
HRESULT GetMarkerType(CAAISysPointProperties::MarkerType & oMarkerType);
```

### SetMarkerType
```cpp
HRESULT SetMarkerType(const CAAISysPointProperties::MarkerType iMarkerType);
```

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

