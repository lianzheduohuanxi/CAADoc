---
title: "CAAEMmrCCDataExtensionParmPublisher"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATParmPublisherAdapter"
method_count: 3
source_file: "CAAMechanicalModeler.edu/CAAMmrCCDataExtension.m/LocalInterfaces/CAAEMmrCCDataExtensionParmPublisher.h"
---

# CAAEMmrCCDataExtensionParmPublisher

**基类**: CATParmPublisherAdapter | **模块**: CAAMechanicalModeler | **方法数**: 3

## 依赖

- `CATParmPublisherAdapter.h`

## 公共方法

### GetDirectChildren

```cpp
void GetDirectChildren(CATClassId intfName, CATListValCATISpecObject_var &lst) ;
```

| 参数 | 类型 |
|------|------|
| intfName | `CATClassId` |
| &lst | `CATListValCATISpecObject_var` |


### GetAllChildren

```cpp
void GetAllChildren(CATClassId intfName, CATListValCATISpecObject_var &lst) ;
```

| 参数 | 类型 |
|------|------|
| intfName | `CATClassId` |
| &lst | `CATListValCATISpecObject_var` |


### VisitChildren

```cpp
void VisitChildren(CATIVisitor* , const int recursively = 0) ;
```

| 参数 | 类型 |
|------|------|
|  | `CATIVisitor*` |
| 0 | `const int recursively =` |


---

**源文件**: `CAAMechanicalModeler.edu/CAAMmrCCDataExtension.m/LocalInterfaces/CAAEMmrCCDataExtensionParmPublisher.h`
