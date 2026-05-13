---
title: "CAAPstINFUpdateProvider"
type: "LocalClass"
module: "CAAProductStructure"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAPstINFUpdateProvider.h"
---

# CAAPstINFUpdateProvider

> Implementation of the CATIUpdateProvider interface for a line or wire object, serving as the provider implementation for the inclusion of a user-defined line or wire feature, "CAAPstINFLine" or "CAAPstINFWire", in the update process of the Product root. Illustrates programming the Update method of the CATIUpdateProvider interface of the ObjectSpecsModeler framework. Inheritance: CATBaseUnknown (System Framework)

**基类**: CATBaseUnknown | **模块**: CAAProductStructure | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CATListOfCATBaseUnknown.h`
- `CATIDomain.h`

## 公共方法

### Update

```cpp
int Update(CATBaseUnknown *ipObj, CATIDomain_var ispDomain = NULL_var) ;
```

| 参数 | 类型 |
|------|------|
| *ipObj | `CATBaseUnknown` |
| NULL_var | `CATIDomain_var ispDomain =` |


### IsUpToDate

```cpp
CATBoolean IsUpToDate(CATBaseUnknown *ipObj, CATIDomain_var ispDomain = NULL_var) ;
```

| 参数 | 类型 |
|------|------|
| *ipObj | `CATBaseUnknown` |
| NULL_var | `CATIDomain_var ispDomain =` |


### SetUpToDate

```cpp
void SetUpToDate(CATBaseUnknown *ipObj, CATBoolean iFlag) ;
```

| 参数 | 类型 |
|------|------|
| *ipObj | `CATBaseUnknown` |
| iFlag | `CATBoolean` |


### IsInactive

```cpp
int IsInactive(CATBaseUnknown *ipObj) ;
```

| 参数 | 类型 |
|------|------|
| *ipObj | `CATBaseUnknown` |


---

**源文件**: `CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAPstINFUpdateProvider.h`
