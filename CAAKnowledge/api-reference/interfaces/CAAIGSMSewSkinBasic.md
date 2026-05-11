---
title: "CAAIGSMSewSkinBasic"
type: "interface"
module: "CAAGSMInterfaces"
base: "CATBaseUnknown"
method_count: 7
verified: true
---

# CAAIGSMSewSkinBasic

**基类**: CATBaseUnknown  
**模块**: CAAGSMInterfaces  
**方法数**: 7

## 方法列表

### SetSurfaceToSew
```cpp
HRESULT SetSurfaceToSew(CATISpecObject_var ispSurfaceToSew);
```

### GetSurfaceToSew
```cpp
HRESULT GetSurfaceToSew(CATISpecObject_var & ospSurfaceToSew);
```

### SetSurfaceSupport
```cpp
HRESULT SetSurfaceSupport(CATISpecObject_var  ispSupport);
```

### GetSurfaceSupport
```cpp
HRESULT GetSurfaceSupport(CATISpecObject_var  & ospSupport);
```

### SetOrientation
```cpp
HRESULT SetOrientation(CATGSMOrientation iOrientation);
```

### GetOrientation
```cpp
HRESULT GetOrientation(CATGSMOrientation & oOrientation);
```

### InvertOrientation
```cpp
HRESULT InvertOrientation();
```

