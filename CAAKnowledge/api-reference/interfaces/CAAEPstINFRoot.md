---
title: "CAAEPstINFRoot"
type: "LocalClass"
module: "CAAProductStructure"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFRoot.h"
---

# CAAEPstINFRoot

> Data extension of the CAAPstINFRoot component, implementing the CAAIPstINFRoot interface defined in the CAAProductStructure.edu framework, allowing the adding and retrieving of the root's aggregated children. Illustrates programming the adding and retrieving methods necessary for the management of a CAAPstINFRoot feature. Inheritance: CATBaseUnknown (System Framework)

**基类**: CATBaseUnknown | **模块**: CAAProductStructure | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATLISTV_CATBaseUnknown.h`

## 公共方法

### AddChild

```cpp
HRESULT AddChild(CATISpecObject *ipiFeature) ;
```

Aggregates a new feature under the root.

| 参数 | 类型 |
|------|------|
| *ipiFeature | `CATISpecObject` |


### GetChildren

```cpp
HRESULT GetChildren(CATListValCATBaseUnknown_var **opList) ;
```

Returns a list of the direct children of the root node.

| 参数 | 类型 |
|------|------|
| **opList | `CATListValCATBaseUnknown_var` |


---

**源文件**: `CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFRoot.h`
