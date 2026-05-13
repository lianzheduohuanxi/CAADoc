---
title: "CAAXMLSAXCountDocHandler"
type: "LocalClass"
module: "CAAXMLParser"
base: "CATSAXHandlerBase"
method_count: 5
source_file: "CAAXMLParser.edu/CAAXMLSAXCount.m/LocalInterfaces/CAAXMLSAXCountDocHandler.h"
---

# CAAXMLSAXCountDocHandler

**基类**: CATSAXHandlerBase | **模块**: CAAXMLParser | **方法数**: 5

## 依赖

- `CATSAXHandlerBase.h`

## 虚方法

### Characters

```cpp
virtual HRESULT Characters(const CATUnicodeString & iCharacters) ;
```

Override the default implementation of the CATISAXDocumentHandler methods we are interested in.

| 参数 | 类型 |
|------|------|
| iCharacters | `const CATUnicodeString &` |


### EndDocument

```cpp
virtual HRESULT EndDocument() ;
```


### IgnorableWhiteSpace

```cpp
virtual HRESULT IgnorableWhiteSpace(const CATUnicodeString & iCharacters) ;
```

| 参数 | 类型 |
|------|------|
| iCharacters | `const CATUnicodeString &` |


### ProcessingInstruction

```cpp
virtual HRESULT ProcessingInstruction(const CATUnicodeString & iTarget, const CATUnicodeString & iData) ;
```

| 参数 | 类型 |
|------|------|
| iTarget | `const CATUnicodeString &` |
| iData | `const CATUnicodeString &` |


### StartElement

```cpp
virtual HRESULT StartElement(const CATUnicodeString & iName, const CATISAXAttributeList_var& iAttributes) ;
```

| 参数 | 类型 |
|------|------|
| iName | `const CATUnicodeString &` |
| iAttributes | `const CATISAXAttributeList_var&` |


---

**源文件**: `CAAXMLParser.edu/CAAXMLSAXCount.m/LocalInterfaces/CAAXMLSAXCountDocHandler.h`
