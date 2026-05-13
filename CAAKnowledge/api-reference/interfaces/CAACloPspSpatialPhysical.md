---
title: "CAACloPspSpatialPhysical"
type: "LocalClass"
module: "CAACommonLayoutItf"
base: "CAAPspBaseEnvProtected"
method_count: 2
source_file: "CAACommonLayoutItf.edu/CAACloPspSpatialPhysical.m/LocalInterfaces/CAACloPspSpatialPhysical.h"
---

# CAACloPspSpatialPhysical

**基类**: CAAPspBaseEnvProtected | **模块**: CAACommonLayoutItf | **方法数**: 2

## 依赖

- `CAAPspBaseEnvProtected.h`
- `CATError.h`
- `CATUnicodeString.h`

## 公共方法

### ListConnectedPhysicalsToSpatial

```cpp
HRESULT ListConnectedPhysicalsToSpatial() ;
```


### DoSample

```cpp
HRESULT DoSample(const CATUnicodeString &iuFileToBeLoaded) ;
```

Input: iuFileToBeLoaded - path of document name to be loaded (CATProduct containing geometry, objects ...

| 参数 | 类型 |
|------|------|
| &iuFileToBeLoaded | `const CATUnicodeString` |


---

**源文件**: `CAACommonLayoutItf.edu/CAACloPspSpatialPhysical.m/LocalInterfaces/CAACloPspSpatialPhysical.h`
