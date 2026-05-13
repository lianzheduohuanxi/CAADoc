---
title: "CAAEPstINFWire"
type: "LocalClass"
module: "CAAProductStructure"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFWire.h"
---

# CAAEPstINFWire

> Data extension of the CAAPstINFWire component, implementing the CAAIPstINFWire interface defined in the CAAProductStructure.edu framework, allowing the setting and retrieval of point values defining a CAAPstINFWire feature. Illustrates programming the setting and retrieval methods necessary for the definition of a CAAPstINFWire feature. Inheritance: CATBaseUnknown (System Framework)

**基类**: CATBaseUnknown | **模块**: CAAProductStructure | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATListPtrCATISpecObject.h`

## 公共方法

### GetPoints

```cpp
HRESULT GetPoints(CATListPtrCATISpecObject **opPointList) ;
```

Retrieves the list of CATISpecObject pointers to "CAAPstINFPoint" features defining the wire.

| 参数 | 类型 |
|------|------|
| **opPointList | `CATListPtrCATISpecObject` |


### SetPoints

```cpp
HRESULT SetPoints(CATListPtrCATISpecObject *ipPointList) ;
```

Define or update a "CAAPstINFWire" feature by valuating its attribute containing a list of CATISpecObject pointers to "CAAPstINFPoint" features.

| 参数 | 类型 |
|------|------|
| *ipPointList | `CATListPtrCATISpecObject` |


---

**源文件**: `CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFWire.h`
