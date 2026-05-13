---
title: "CAAESmiUserMachFeature"
type: "LocalClass"
module: "CAASurfaceMachiningItf"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAASurfaceMachiningItf.edu/CAASmiUserMachFeature.m/LocalInterfaces/CAAESmiUserMachFeature.h"
---

# CAAESmiUserMachFeature

**基类**: CATBaseUnknown | **模块**: CAASurfaceMachiningItf | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATListOfCATGeometries.h`

## 公共方法

### GetGuideParameter

```cpp
HRESULT GetGuideParameter(CATBaseUnknown_var &oParameter) ;
```

Gets parameter of the guide of our Machining Feature.

| 参数 | 类型 |
|------|------|
| &oParameter | `CATBaseUnknown_var` |


### IsComplete

```cpp
HRESULT IsComplete(int &oIsComplete) ;
```

Determines if all the necessary datas are filled up.

| 参数 | 类型 |
|------|------|
| &oIsComplete | `int` |


---

**源文件**: `CAASurfaceMachiningItf.edu/CAASmiUserMachFeature.m/LocalInterfaces/CAAESmiUserMachFeature.h`
