---
title: "CAAIV5V6ExtMmrCombinedCurve"
type: "interface"
module: "CAAV5V6MechanicalModeler"
base: "CATBaseUnknown"
method_count: 4
visibility: "public"
verified: true
---

# CAAIV5V6ExtMmrCombinedCurve

**基类**: CATBaseUnknown  
**模块**: CAAV5V6MechanicalModeler  
**可见性**: public  
**方法数**: 4

## 方法列表

### SetCurve
```cpp
HRESULT SetCurve(int iNum , CATBaseUnknown *ipCurve);
```

### GetCurve
```cpp
HRESULT GetCurve(int iNum, CATBaseUnknown *&opCurve);
```

### SetDirection
```cpp
HRESULT SetDirection(int iNum, CATBaseUnknown *ipDirection);
```

### GetDirection
```cpp
HRESULT GetDirection(int iNum , CATBaseUnknown *&opDirection);
```

## 依赖

- `CAAV5V6ExtMmrCombinedCurve.h`
- `CATBaseUnknown.h`

