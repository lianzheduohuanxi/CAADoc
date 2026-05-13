---
title: "CAAEPstINFVisPropertiesPoint"
type: "LocalClass"
module: "CAAProductStructure"
base: "CATExtIVisProperties"
method_count: 2
source_file: "CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFVisPropertiesPoint.h"
---

# CAAEPstINFVisPropertiesPoint

> Data extension of the CAAPstINFPoint component, implementing the CATIVisProperties interface to enable its graphic properties modification.

**基类**: CATExtIVisProperties | **模块**: CAAProductStructure | **方法数**: 2

## 依赖

- `CATExtIVisProperties.h`

## 公共方法

### IsGeomTypeDefined

```cpp
HRESULT IsGeomTypeDefined(CATVisGeomType & iGeomType) ;
```

CATIVisProperties interface

| 参数 | 类型 |
|------|------|
| iGeomType | `CATVisGeomType &` |


### GetSubTypeFromPath

```cpp
HRESULT GetSubTypeFromPath(CATPathElement & iPathElement, CATVisPropertyType iPropertyType, CATVisGeomType & oGeomType, unsigned int & oPropertyNumber) ;
```

| 参数 | 类型 |
|------|------|
| iPathElement | `CATPathElement &` |
| iPropertyType | `CATVisPropertyType` |
| oGeomType | `CATVisGeomType &` |
| oPropertyNumber | `unsigned int &` |


---

**源文件**: `CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFVisPropertiesPoint.h`
