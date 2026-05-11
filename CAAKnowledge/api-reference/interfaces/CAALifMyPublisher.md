---
title: "CAALifMyPublisher"
type: "interface"
module: "CAALiteralFeatures"
base: "CATParmPublisherAdapter"
method_count: 5
visibility: "local"
verified: true
---

# CAALifMyPublisher

**基类**: CATParmPublisherAdapter  
**模块**: CAALiteralFeatures  
**可见性**: local  
**方法数**: 5

> ------------

## 方法列表

### Append
```cpp
void Append(const CATISpecObject_var & iKBwareObject);
```

### RemoveChild
```cpp
void RemoveChild(const CATISpecObject_var & iKBwareObject);
```

### GetDirectChildren
```cpp
void GetDirectChildren(CATClassId iIntfName,CATListValCATISpecObject_var &iList);
```

### GetAllChildren
```cpp
void GetAllChildren(CATClassId iIntfName,CATListValCATISpecObject_var &ListFound);
```

### GetContainer
```cpp
CATIContainer_var GetContainer();
```

## 依赖

- `CATParmPublisherAdapter.h`
- `CATICkeRelationForwards.h`
- `CATICkeParm.h`
- `CATICkeType.h`
- `CATIVisitor.h`

