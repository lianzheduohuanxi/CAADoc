---
title: "CAAEV5V6ExtMmrCCDataExtensionParmPublisher"
type: "LocalClass"
module: "CAAV5V6MechanicalModeler"
base: "CATParmPublisherAdapter"
method_count: 4
source_file: "CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrCCDataExtension.m/LocalInterfaces/CAAEV5V6ExtMmrCCDataExtensionParmPublisher.h"
---

# CAAEV5V6ExtMmrCCDataExtensionParmPublisher

**基类**: CATParmPublisherAdapter | **模块**: CAAV5V6MechanicalModeler | **方法数**: 4

## 依赖

- `CATIAV5Level.h`
- `CATParmPublisherAdapter.h`

## 公共方法

### VisitChildren

```cpp
void VisitChildren(CATIVisitor* , const int recursively = 0) ;
```

| 参数 | 类型 |
|------|------|
|  | `CATIVisitor*` |
| 0 | `const int recursively =` |


### RetrieveDirectChildren

```cpp
HRESULT RetrieveDirectChildren(CATClassId iIntfName, CATListValCATBaseUnknown_var &iListToFill) const ;
```

V6 only CATIParmDirectAccess

| 参数 | 类型 |
|------|------|
| iIntfName | `CATClassId` |
| &iListToFill | `CATListValCATBaseUnknown_var` |


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


---

**源文件**: `CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrCCDataExtension.m/LocalInterfaces/CAAEV5V6ExtMmrCCDataExtensionParmPublisher.h`
