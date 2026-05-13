---
title: "CAAXMLSAXResolverHandlers"
type: "LocalClass"
module: "CAAXMLParser"
base: "CATSAXHandlerBase"
method_count: 3
source_file: "CAAXMLParser.edu/CAAXMLSAXResolver.m/LocalInterfaces/CAAXMLSAXResolverHandlers.h"
---

# CAAXMLSAXResolverHandlers

**基类**: CATSAXHandlerBase | **模块**: CAAXMLParser | **方法数**: 3

## 依赖

- `CATUnicodeString.h`
- `CATSAXHandlerBase.h`

## 虚方法

### ResolveEntity

```cpp
virtual HRESULT ResolveEntity(const CATUnicodeString & iPublicId, const CATUnicodeString & iSystemId, CATISAXInputSource_var& oInputSource) ;
```

Override the default implementation of the CATISAXErrorHandler methods we are interested in.

| 参数 | 类型 |
|------|------|
| iPublicId | `const CATUnicodeString &` |
| iSystemId | `const CATUnicodeString &` |
| oInputSource | `CATISAXInputSource_var&` |


### Error

```cpp
virtual HRESULT Error(CATSAXParseException* iException) ;
```

| 参数 | 类型 |
|------|------|
| iException | `CATSAXParseException*` |


### FatalError

```cpp
virtual HRESULT FatalError(CATSAXParseException* iException) ;
```

| 参数 | 类型 |
|------|------|
| iException | `CATSAXParseException*` |


---

**源文件**: `CAAXMLParser.edu/CAAXMLSAXResolver.m/LocalInterfaces/CAAXMLSAXResolverHandlers.h`
