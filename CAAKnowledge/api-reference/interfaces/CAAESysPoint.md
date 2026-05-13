---
title: "CAAESysPoint"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysPoint.h"
---

# CAAESysPoint

> Data extension ofd the CAASysPoint component and implementing the CAAISysPoint interface. Main Method: SetCoord/GetCoord System Framework

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`

## 虚方法

### SetCoord

```cpp
virtual HRESULT SetCoord(const float iX, const float iY, const float iZ) ;
```

| 参数 | 类型 |
|------|------|
| iX | `const float` |
| iY | `const float` |
| iZ | `const float` |


### GetCoord

```cpp
virtual HRESULT GetCoord(float & oX, float & oY, float & oZ) const ;
```

| 参数 | 类型 |
|------|------|
| oX | `float &` |
| oY | `float &` |
| oZ | `float &` |


---

**源文件**: `CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysPoint.h`
