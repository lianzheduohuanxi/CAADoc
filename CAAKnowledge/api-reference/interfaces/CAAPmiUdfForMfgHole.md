---
title: "CAAPmiUdfForMfgHole"
type: "interface"
module: "CAAPrismaticMachiningItf"
base: "CATBaseUnknown"
method_count: 6
visibility: "local"
verified: true
---

# CAAPmiUdfForMfgHole

**基类**: CATBaseUnknown  
**模块**: CAAPrismaticMachiningItf  
**可见性**: local  
**方法数**: 6

> ===================================================================

## 方法列表

### GetDiameter
```cpp
HRESULT GetDiameter(CATICkeParm_var &oDiameter);
```

### GetDepth
```cpp
HRESULT GetDepth(CATICkeParm_var &oDepth);
```

### GetOrigin
```cpp
HRESULT GetOrigin(double& oX, double& oY, double& oZ);
```

### GetDirection
```cpp
HRESULT GetDirection(double& oX, double& oY, double& oZ);
```

### get_Parameter
```cpp
HRESULT get_Parameter(const CATString &iParameterName, double &oParameter);
```

### get_Parameter
```cpp
HRESULT get_Parameter(const CATString &iParameterName, int &oParameter);
```

## 依赖

- `CATBaseUnknown.h`
- `CATICkeParm.h`
- `CATString.h`

