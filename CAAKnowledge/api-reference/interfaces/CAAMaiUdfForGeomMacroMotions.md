---
title: "CAAMaiUdfForGeomMacroMotions"
type: "LocalClass"
module: "CAAManufacturingItf"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAManufacturingItf.edu/CAAMaiUserDefFeatureMapping.m/LocalInterfaces/CAAMaiUdfForGeomMacroMotions.h"
---

# CAAMaiUdfForGeomMacroMotions

**基类**: CATBaseUnknown | **模块**: CAAManufacturingItf | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATLISTV_CATBaseUnknown.h`

## 公共方法

### MapGeomOnApproachMacroMotion

```cpp
HRESULT MapGeomOnApproachMacroMotion(CATUnicodeString iActivityType, int iMacroMotionType, CATListOfInt iElementaryMotionTypeList, CATListValCATBaseUnknown_var &oGeometryList) ;
```

| 参数 | 类型 |
|------|------|
| iActivityType | `CATUnicodeString` |
| iMacroMotionType | `int` |
| iElementaryMotionTypeList | `CATListOfInt` |
| &oGeometryList | `CATListValCATBaseUnknown_var` |


### MapGeomOnRetractMacroMotion

```cpp
HRESULT MapGeomOnRetractMacroMotion(CATUnicodeString iActivityType, int iMacroMotionType, CATListOfInt iElementaryMotionTypeList, CATListValCATBaseUnknown_var &oGeometryList) ;
```

| 参数 | 类型 |
|------|------|
| iActivityType | `CATUnicodeString` |
| iMacroMotionType | `int` |
| iElementaryMotionTypeList | `CATListOfInt` |
| &oGeometryList | `CATListValCATBaseUnknown_var` |


---

**源文件**: `CAAManufacturingItf.edu/CAAMaiUserDefFeatureMapping.m/LocalInterfaces/CAAMaiUdfForGeomMacroMotions.h`
