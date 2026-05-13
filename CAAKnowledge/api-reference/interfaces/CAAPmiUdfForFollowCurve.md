---
title: "CAAPmiUdfForFollowCurve"
type: "LocalClass"
module: "CAAPrismaticMachiningItf"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAPrismaticMachiningItf.edu/CAAPmiUserDefFeatureMappedWithMfgFeature.m/LocalInterfaces/CAAPmiUdfForFollowCurve.h"
---

# CAAPmiUdfForFollowCurve

**基类**: CATBaseUnknown | **模块**: CAAPrismaticMachiningItf | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CATLISTV_CATBaseUnknown.h`

## 公共方法

### GetGuidingCurves

```cpp
HRESULT GetGuidingCurves(CATListValCATBaseUnknown_var & oAuxGuidingElements) ;
```

| 参数 | 类型 |
|------|------|
| oAuxGuidingElements | `CATListValCATBaseUnknown_var &` |


### GetAuxiliaryGuidingCurves

```cpp
HRESULT GetAuxiliaryGuidingCurves(CATListValCATBaseUnknown_var & oAuxGuidingElements) ;
```

| 参数 | 类型 |
|------|------|
| oAuxGuidingElements | `CATListValCATBaseUnknown_var &` |


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

**源文件**: `CAAPrismaticMachiningItf.edu/CAAPmiUserDefFeatureMappedWithMfgFeature.m/LocalInterfaces/CAAPmiUdfForFollowCurve.h`
