---
title: "CAALifMyPublisher"
type: "LocalClass"
module: "CAALiteralFeatures"
base: "CATParmPublisherAdapter"
method_count: 6
source_file: "CAALiteralFeatures.edu/CAALifBasis.m/LocalInterfaces/CAALifMyPublisher.h"
---

# CAALifMyPublisher

> This class defines the CAAMyPublisher type which implements CATIParmPublisher It derives from CATCkeDescendants and redefine the GetDirectChildren and CompAttrKey methods. Any object intended to be added parameters and relations and benefit from the f(x) capabilities must implement the CATIParmPublisher interface. The LiteralFeatures framework provides you with the CATCkeDescendants adapter you can extend to redefine the GetDirectChildren and GetAllChildren methods. =========================================================================== Usage: Type  CAALifPublishMain Inheritance: CATParmPublisherAdapter Main Method: CAALifParametersVolatile

**基类**: CATParmPublisherAdapter | **模块**: CAALiteralFeatures | **方法数**: 6

## 依赖

- `CATParmPublisherAdapter.h`
- `CATICkeRelationForwards.h`
- `CATICkeParm.h`
- `CATICkeType.h`
- `CATIVisitor.h`

## 虚方法

### Append

```cpp
virtual void Append(const CATISpecObject_var & iKBwareObject) ;
```

| 参数 | 类型 |
|------|------|
| iKBwareObject | `const CATISpecObject_var &` |


### RemoveChild

```cpp
virtual void RemoveChild(const CATISpecObject_var & iKBwareObject) ;
```

| 参数 | 类型 |
|------|------|
| iKBwareObject | `const CATISpecObject_var &` |


### GetDirectChildren

```cpp
virtual void GetDirectChildren(CATClassId iIntfName, CATListValCATISpecObject_var &iList) ;
```

| 参数 | 类型 |
|------|------|
| iIntfName | `CATClassId` |
| &iList | `CATListValCATISpecObject_var` |


### GetAllChildren

```cpp
virtual void GetAllChildren(CATClassId iIntfName, CATListValCATISpecObject_var &ListFound) ;
```

| 参数 | 类型 |
|------|------|
| iIntfName | `CATClassId` |
| &ListFound | `CATListValCATISpecObject_var` |


### GetContainer

```cpp
virtual CATIContainer_var GetContainer() ;
```


## 公共方法

### VisitChildren

```cpp
void VisitChildren(CATIVisitor* , const int iRecursively = 0) ;
```

| 参数 | 类型 |
|------|------|
|  | `CATIVisitor*` |
| 0 | `const int iRecursively =` |


---

**源文件**: `CAALiteralFeatures.edu/CAALifBasis.m/LocalInterfaces/CAALifMyPublisher.h`
