---
title: "CAAESysPointProperties"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysPointProperties.h"
---

# CAAESysPointProperties

> Data extension implementing the CAAIPointProperties interface. Inheritance: CATBaseUnknown (System Framework)

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CAAISysPointProperties.h`

## 虚方法

### GetMarkerType

```cpp
virtual HRESULT GetMarkerType(CAAISysPointProperties::MarkerType & oMarkerType) ;
```

| 参数 | 类型 |
|------|------|
| oMarkerType | `CAAISysPointProperties::MarkerType &` |


### SetMarkerType

```cpp
virtual HRESULT SetMarkerType(const CAAISysPointProperties::MarkerType iMarkerType) ;
```

| 参数 | 类型 |
|------|------|
| iMarkerType | `const CAAISysPointProperties::MarkerType` |


---

**源文件**: `CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysPointProperties.h`
