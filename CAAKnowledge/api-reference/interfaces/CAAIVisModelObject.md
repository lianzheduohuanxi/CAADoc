---
title: "CAAIVisModelObject"
type: "interface"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 6
verified: true
---

# CAAIVisModelObject

**基类**: CATBaseUnknown  
**模块**: CAAVisualization  
**方法数**: 6

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

