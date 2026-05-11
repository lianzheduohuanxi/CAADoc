---
title: "CAAXMLSAXResolverHandlers"
type: "interface"
module: "CAAXMLParser"
base: "CATSAXHandlerBase"
method_count: 3
visibility: "local"
verified: true
---

# CAAXMLSAXResolverHandlers

**基类**: CATSAXHandlerBase  
**模块**: CAAXMLParser  
**可见性**: local  
**方法数**: 3

> interfaces from which it is convenient to

## 方法列表

### ResolveEntity
```cpp
HRESULT ResolveEntity(const CATUnicodeString & iPublicId, 
			const CATUnicodeString & iSystemId, 
			CATISAXInputSource_var& oInputSource);
```

### Error
```cpp
HRESULT Error(CATSAXParseException* iException);
```

### FatalError
```cpp
HRESULT FatalError(CATSAXParseException* iException);
```

## 依赖

- `CATUnicodeString.h`
- `CATSAXHandlerBase.h`

