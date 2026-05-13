---
title: "CAAPmiUdfFor2DContouring"
type: "LocalClass"
module: "CAAPrismaticMachiningItf"
base: "CATBaseUnknown"
method_count: 5
source_file: "CAAPrismaticMachiningItf.edu/CAAPmiUserDefFeatureMappedWithMfgFeature.m/LocalInterfaces/CAAPmiUdfFor2DContouring.h"
---

# CAAPmiUdfFor2DContouring

**基类**: CATBaseUnknown | **模块**: CAAPrismaticMachiningItf | **方法数**: 5

## 依赖

- `CATBaseUnknown.h`
- `CATPoint.h`
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
HRESULT GetGuidingCurves(CATListValCATBaseUnknown_var & oGuidingElements, int & oSide, CATPoint * oExtremity) ;
```

| 参数 | 类型 |
|------|------|
| oGuidingElements | `CATListValCATBaseUnknown_var &` |
| oSide | `int &` |
| oExtremity | `CATPoint *` |


### GetChecks

```cpp
HRESULT GetChecks(CATListValCATBaseUnknown_var & oChecks) ;
```

| 参数 | 类型 |
|------|------|
| oChecks | `CATListValCATBaseUnknown_var &` |


### GetRelimitingElements

```cpp
HRESULT GetRelimitingElements(CATListValCATBaseUnknown_var & oFirstRelimitingElements, CATListValCATBaseUnknown_var & oSecondRelimitingElements) ;
```

| 参数 | 类型 |
|------|------|
| oFirstRelimitingElements | `CATListValCATBaseUnknown_var &` |
| oSecondRelimitingElements | `CATListValCATBaseUnknown_var &` |


---

**源文件**: `CAAPrismaticMachiningItf.edu/CAAPmiUserDefFeatureMappedWithMfgFeature.m/LocalInterfaces/CAAPmiUdfFor2DContouring.h`
