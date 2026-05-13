---
title: "CAAEwrUipBundleSegmentExt"
type: "LocalClass"
module: "CAAElecRoutingItf"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAElecRoutingItf.edu/CAAEwrRoutingImpl.m/LocalInterfaces/CAAEwrUipBundleSegmentExt.h"
---

# CAAEwrUipBundleSegmentExt

**基类**: CATBaseUnknown | **模块**: CAAElecRoutingItf | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATListOfDouble.h`

## 公共方法

### ComputeDiameter

```cpp
HRESULT ComputeDiameter(const CATListOfDouble iListOfWireDiameters, double & oBundleSegmentDiameter) ;
```

| 参数 | 类型 |
|------|------|
| iListOfWireDiameters | `const CATListOfDouble` |
| oBundleSegmentDiameter | `double &` |


### ComputeBendRadius

```cpp
HRESULT ComputeBendRadius(const CATListOfDouble iListOfWireBendRadius, double & oBundleSegmentBendRadius) ;
```

| 参数 | 类型 |
|------|------|
| iListOfWireBendRadius | `const CATListOfDouble` |
| oBundleSegmentBendRadius | `double &` |


---

**源文件**: `CAAElecRoutingItf.edu/CAAEwrRoutingImpl.m/LocalInterfaces/CAAEwrUipBundleSegmentExt.h`
