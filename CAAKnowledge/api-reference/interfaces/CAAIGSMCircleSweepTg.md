---
title: "CAAIGSMCircleSweepTg"
type: "interface"
module: "CAAGSMInterfaces"
base: "CATBaseUnknown"
method_count: 10
verified: true
---

# CAAIGSMCircleSweepTg

**基类**: CATBaseUnknown  
**模块**: CAAGSMInterfaces  
**方法数**: 10

## 方法列表

### SetCurveRef
```cpp
HRESULT SetCurveRef(const CATISpecObject_var ipCurveRef);
```

### GetCurveRef
```cpp
HRESULT GetCurveRef(CATISpecObject_var &ipCurveRef);
```

### SetSurfaceSupport
```cpp
HRESULT SetSurfaceSupport(const CATISpecObject_var  ipSupport);
```

### GetSurfaceSupport
```cpp
HRESULT GetSurfaceSupport(CATISpecObject_var &ipSupport);
```

### SetTrimMode
```cpp
HRESULT SetTrimMode(const int iTrimMode);
```

### GetTrimMode
```cpp
HRESULT GetTrimMode(int  & oTrimMode);
```

### SetRadius
```cpp
HRESULT SetRadius(const double iRadius);
```

### GetRadius
```cpp
HRESULT GetRadius(double  & oRadius);
```

### SetSolution
```cpp
HRESULT SetSolution(const int iSolution);
```

### GetSolution
```cpp
HRESULT GetSolution(int  & oSolution);
```

