---
title: "CAAXMLSAXCountErrHandler"
type: "interface"
module: "CAAXMLParser"
base: "CATSAXHandlerBase"
method_count: 2
visibility: "local"
verified: true
---

# CAAXMLSAXCountErrHandler

**基类**: CATSAXHandlerBase  
**模块**: CAAXMLParser  
**可见性**: local  
**方法数**: 2

> interfaces from which it is convenient to

## 方法列表

### Error
```cpp
HRESULT Error(CATSAXParseException* iException);
```

### FatalError
```cpp
HRESULT FatalError(CATSAXParseException* iException);
```

## 依赖

- `CATSAXHandlerBase.h`

