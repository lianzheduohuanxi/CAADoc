---
title: "CAAEV5V6ExtMmrMultiMeasureVisProperties"
type: "LocalClass"
module: "CAAV5V6MechanicalModeler"
base: "CATExtIVisProperties"
method_count: 2
source_file: "CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrMultiMeasure.m/LocalInterfaces/CAAEV5V6ExtMmrMultiMeasureVisProperties.h"
---

# CAAEV5V6ExtMmrMultiMeasureVisProperties

**基类**: CATExtIVisProperties | **模块**: CAAV5V6MechanicalModeler | **方法数**: 2

## 依赖

- `CATExtIVisProperties.h`

## 公共方法

### IsGeomTypeDefined

```cpp
HRESULT IsGeomTypeDefined(CATVisGeomType & iGeomType) ;
```

IsGeomTypeDefined

| 参数 | 类型 |
|------|------|
| iGeomType | `CATVisGeomType &` |


### GetSubTypeFromPath

```cpp
HRESULT GetSubTypeFromPath(CATPathElement & iPathElement, CATVisPropertyType iPropertyType, CATVisGeomType & oGeomType, unsigned int & oPropertyNumber) ;
```

GetSubTypeFromPath : For Graphic Property table

| 参数 | 类型 |
|------|------|
| iPathElement | `CATPathElement &` |
| iPropertyType | `CATVisPropertyType` |
| oGeomType | `CATVisGeomType &` |
| oPropertyNumber | `unsigned int &` |


---

**源文件**: `CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrMultiMeasure.m/LocalInterfaces/CAAEV5V6ExtMmrMultiMeasureVisProperties.h`
