---
title: "CAAEPstINFInitCont"
type: "LocalClass"
module: "CAAProductStructure"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFInitCont.h"
---

# CAAEPstINFInitCont

> Data extension of the CAAPstINFCont component, implementing the CATInit interface to allow specific treatments to be executed during the initialization of the applicative container. Illustrates programming the Init method of the CATInit interface of the ObjectModelerBase framework, for an applicative container containing objects whose integration in the Product document is dependent on the declaration of its provider implementations. Inheritance: CATBaseUnknown (System Framework)

**基类**: CATBaseUnknown | **模块**: CAAProductStructure | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`
- `CATBoolean.h`

## 公共方法

### Init

```cpp
void Init(CATBoolean iDestroyExistingData) ;
```

| 参数 | 类型 |
|------|------|
| iDestroyExistingData | `CATBoolean` |


---

**源文件**: `CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFInitCont.h`
