---
title: "CAAIMmrCombinedCurve"
type: "interface"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 4
verified: true
---

# CAAIMmrCombinedCurve

**基类**: CATBaseUnknown  
**模块**: CAAMechanicalModeler  
**方法数**: 4

## 方法列表

### SetCurve
```cpp
HRESULT SetCurve(int iNum ,
                              CATISpecObject *ipCurve);
```

### GetCurve
```cpp
HRESULT GetCurve(int iNum ,
                              CATISpecObject **opCurve);
```

### SetDirection
```cpp
HRESULT SetDirection(int iNum , 
                                 CATISpecObject *ipDirection);
```

### GetDirection
```cpp
HRESULT GetDirection(int iNum ,
                                 CATISpecObject **opDirection);
```

