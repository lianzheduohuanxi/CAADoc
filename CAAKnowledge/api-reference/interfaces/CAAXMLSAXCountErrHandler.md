---
title: "CAAXMLSAXCountErrHandler"
type: "LocalClass"
module: "CAAXMLParser"
base: "CATSAXHandlerBase"
method_count: 2
source_file: "CAAXMLParser.edu/CAAXMLSAXCount.m/LocalInterfaces/CAAXMLSAXCountErrHandler.h"
---

# CAAXMLSAXCountErrHandler

**基类**: CATSAXHandlerBase | **模块**: CAAXMLParser | **方法数**: 2

## 依赖

- `CATSAXHandlerBase.h`

## 虚方法

### Error

```cpp
virtual HRESULT Error(CATSAXParseException* iException) ;
```

Override the default implementation of the CATISAXErrorHandler methods we are interested in.

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

**源文件**: `CAAXMLParser.edu/CAAXMLSAXCount.m/LocalInterfaces/CAAXMLSAXCountErrHandler.h`
