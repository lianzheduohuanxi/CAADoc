---
title: "CAAISysColorProperties"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
visibility: "public"
verified: true
---

# CAAISysColorProperties

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: public  
**方法数**: 2

> System Framework

## 方法列表

### GetColor
```cpp
HRESULT GetColor(int & oRed,int & oGreen,int & oBlue);
```

### SetColor
```cpp
HRESULT SetColor(const int iRed,const int iGreen,const int iBlue);
```

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

