---
title: "CAAPmiUdfForPocketing"
type: "LocalClass"
module: "CAAPrismaticMachiningItf"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAPrismaticMachiningItf.edu/CAAPmiUserDefFeatureMappedWithMfgFeature.m/LocalInterfaces/CAAPmiUdfForPocketing.h"
---

# CAAPmiUdfForPocketing

**基类**: CATBaseUnknown | **模块**: CAAPrismaticMachiningItf | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CATLISTV_CATBaseUnknown.h`

## 公共方法

### GetPart

```cpp
HRESULT GetPart(CATBaseUnknown_var & oPartElement) ;
```

| 参数 | 类型 |
|------|------|
| oPartElement | `CATBaseUnknown_var &` |


### GetRelimitingPlane

```cpp
HRESULT GetRelimitingPlane(CATBaseUnknown_var & oRelimitingPlane) ;
```

| 参数 | 类型 |
|------|------|
| oRelimitingPlane | `CATBaseUnknown_var &` |


### GetGuidingCurves

```cpp
HRESULT GetGuidingCurves(CATListValCATBaseUnknown_var & oGuidingElements) ;
```

| 参数 | 类型 |
|------|------|
| oGuidingElements | `CATListValCATBaseUnknown_var &` |


### GetIslands

```cpp
HRESULT GetIslands(CATListValCATBaseUnknown_var& oListOfIslands, CATListOfInt& oNbOfCurvesByIsland) ;
```

| 参数 | 类型 |
|------|------|
| oListOfIslands | `CATListValCATBaseUnknown_var&` |
| oNbOfCurvesByIsland | `CATListOfInt&` |


---

**源文件**: `CAAPrismaticMachiningItf.edu/CAAPmiUserDefFeatureMappedWithMfgFeature.m/LocalInterfaces/CAAPmiUdfForPocketing.h`
