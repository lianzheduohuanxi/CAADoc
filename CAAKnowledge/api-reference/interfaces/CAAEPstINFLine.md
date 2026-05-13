---
title: "CAAEPstINFLine"
type: "LocalClass"
module: "CAAProductStructure"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFLine.h"
---

# CAAEPstINFLine

> Data extension of the CAAPstINFLine component, implementing the CAAIPstINFLine interface defined in the CAAProductStructure.edu framework, allowing the setting and retrieval of point values defining a CAAPstINFLine feature. Illustrates programming the setting and retrieval methods necessary for the definition of a CAAPstINFLine feature. Inheritance: CATBaseUnknown (System Framework)

**基类**: CATBaseUnknown | **模块**: CAAProductStructure | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### GetPoint

```cpp
HRESULT GetPoint(int iNum, CATISpecObject **opiPoint) ;
```

Retrieves the value of one of the two point features defining the line.

| 参数 | 类型 |
|------|------|
| iNum | `int` |
| **opiPoint | `CATISpecObject` |


### SetPoint

```cpp
HRESULT SetPoint(int iNum, CATISpecObject *ipiPoint) ;
```

Valuates one of the line feature's attribute with a point feature.

| 参数 | 类型 |
|------|------|
| iNum | `int` |
| *ipiPoint | `CATISpecObject` |


---

**源文件**: `CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFLine.h`
