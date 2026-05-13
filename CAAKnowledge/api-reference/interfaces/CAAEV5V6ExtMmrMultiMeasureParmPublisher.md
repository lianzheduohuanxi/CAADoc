---
title: "CAAEV5V6ExtMmrMultiMeasureParmPublisher"
type: "LocalClass"
module: "CAAV5V6MechanicalModeler"
base: "CATParmPublisherAdapter"
method_count: 2
source_file: "CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrMultiMeasure.m/LocalInterfaces/CAAEV5V6ExtMmrMultiMeasureParmPublisher.h"
---

# CAAEV5V6ExtMmrMultiMeasureParmPublisher

**基类**: CATParmPublisherAdapter | **模块**: CAAV5V6MechanicalModeler | **方法数**: 2

## 依赖

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

CATIParmDirectAccess

| 参数 | 类型 |
|------|------|
| iIntfName | `CATClassId` |
| &iListToFill | `CATListValCATBaseUnknown_var` |


---

**源文件**: `CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrMultiMeasure.m/LocalInterfaces/CAAEV5V6ExtMmrMultiMeasureParmPublisher.h`
