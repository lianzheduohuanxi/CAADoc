---
title: "CAAEPstINFCCPRoot"
type: "LocalClass"
module: "CAAProductStructure"
base: "ObjectCCP_SPEC"
method_count: 3
source_file: "CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFCCPRoot.h"
---

# CAAEPstINFCCPRoot

> Data extension of the CAAPstINFRoot component, implementing the CATICutAndPastable interface to execute CCP operations on this features. This class derives from the ObjectCCP_SPEC adapter. Illustrates programming the required methods for a root object by implementing the CATICutAndPastable interface of the ObjectModelerBase framework. Inheritance: ObjectCCP_SPEC (ObjectSpecsModeler Framework) CATBaseUnknown (System Framework)

**基类**: ObjectCCP_SPEC | **模块**: CAAProductStructure | **方法数**: 3

## 依赖

- `ObjectCCP_SPEC.h`

## 公共方法

### BoundaryExtract

```cpp
int BoundaryExtract(ListOfVarBaseUnknown &iopObjectsAlreadyInBoundary, const ListOfVarBaseUnknown *ipObjectsToAdd=NULL, const CATFormat *ipAnImposedFormat=NULL) const ;
```

| 参数 | 类型 |
|------|------|
| &iopObjectsAlreadyInBoundary | `ListOfVarBaseUnknown` |
| *ipObjectsToAdd=NULL | `const ListOfVarBaseUnknown` |
| *ipAnImposedFormat=NULL | `const CATFormat` |


### BoundaryRemove

```cpp
int BoundaryRemove(ListOfVarBaseUnknown &iopObjectsAlreadyInBoundary, const ListOfVarBaseUnknown *ipObjectsToRemove=NULL, const CATFormat *ipAnImposedFormat=NULL) const ;
```

| 参数 | 类型 |
|------|------|
| &iopObjectsAlreadyInBoundary | `ListOfVarBaseUnknown` |
| *ipObjectsToRemove=NULL | `const ListOfVarBaseUnknown` |
| *ipAnImposedFormat=NULL | `const CATFormat` |


### Remove

```cpp
int Remove(ListOfVarBaseUnknown &ipObjectToRemove, const CATFormat *ipAnImposedFormat=NULL) ;
```

| 参数 | 类型 |
|------|------|
| &ipObjectToRemove | `ListOfVarBaseUnknown` |
| *ipAnImposedFormat=NULL | `const CATFormat` |


---

**源文件**: `CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFCCPRoot.h`
