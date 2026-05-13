---
title: "CAAEPstINFCCPFeature"
type: "LocalClass"
module: "CAAProductStructure"
base: "ObjectCCP_SPEC"
method_count: 1
source_file: "CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFCCPFeature.h"
---

# CAAEPstINFCCPFeature

> Data extension of the CAAPstINFLine, CAAPstINFPoint and CAAPstINFWire components, implementing the CATICutAndPastable interface to execute CCP operations on these features. This class derives from the ObjectCCP_SPEC adapter. Illustrates programming the Update method for an object by implementing the CATICutAndPastable interface of the ObjectModelerBase framework. Inheritance: ObjectCCP_SPEC (ObjectSpecsModeler Framework) CATBaseUnknown (System Framework)

**基类**: ObjectCCP_SPEC | **模块**: CAAProductStructure | **方法数**: 1

## 依赖

- `ObjectCCP_SPEC.h`

## 公共方法

### Update

```cpp
int Update(CATBaseUnknown_Associations &iopAssociationOfObjects, const CATFormat *ipAnImposedFormat=NULL, ListOfVarBaseUnknown *ipToCurObjects=NULL) ;
```

| 参数 | 类型 |
|------|------|
| &iopAssociationOfObjects | `CATBaseUnknown_Associations` |
| *ipAnImposedFormat=NULL | `const CATFormat` |
| *ipToCurObjects=NULL | `ListOfVarBaseUnknown` |


---

**源文件**: `CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFCCPFeature.h`
