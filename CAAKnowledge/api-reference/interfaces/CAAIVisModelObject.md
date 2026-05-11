---
title: "CAAIVisModelObject"
type: "interface"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 6
visibility: "protected"
verified: true
---

# CAAIVisModelObject

**基类**: CATBaseUnknown  
**模块**: CAAVisualization  
**可见性**: protected  
**方法数**: 6

> /Visualization FrameWork

## 方法列表

### GetType
```cpp
HRESULT GetType(char ** oType);
```

### SetType
```cpp
HRESULT SetType(const char * iType);
```

### AddChild
```cpp
HRESULT AddChild(CATBaseUnknown *iObject);
```

### RemChild
```cpp
HRESULT RemChild(CATBaseUnknown *iObject);
```

### AddParent
```cpp
HRESULT AddParent(CATBaseUnknown *iObject);
```

### RemParent
```cpp
HRESULT RemParent(CATBaseUnknown *iObject);
```

## 依赖

- `CATBaseUnknown.h`
- `CAAVisManagerInt.h`

