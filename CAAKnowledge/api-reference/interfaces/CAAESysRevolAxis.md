---
title: "CAAESysRevolAxis"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
visibility: "local"
verified: true
---

# CAAESysRevolAxis

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: local  
**方法数**: 2

> Data extension of the CAASysRevolSurface component, implementing the

## 方法列表

### GetAxis
```cpp
HRESULT GetAxis(float &oX , float &oY ,float &oZ);
```

### SetAxis
```cpp
HRESULT SetAxis(const float iX,const float iY,const float iZ);
```

## 依赖

- `CATBaseUnknown.h`

