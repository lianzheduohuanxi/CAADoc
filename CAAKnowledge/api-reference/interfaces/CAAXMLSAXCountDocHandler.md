---
title: "CAAXMLSAXCountDocHandler"
type: "interface"
module: "CAAXMLParser"
base: "CATSAXHandlerBase"
method_count: 5
visibility: "local"
verified: true
---

# CAAXMLSAXCountDocHandler

**基类**: CATSAXHandlerBase  
**模块**: CAAXMLParser  
**可见性**: local  
**方法数**: 5

> interfaces from which it is convenient to

## 方法列表

### Characters
```cpp
HRESULT Characters(const CATUnicodeString & iCharacters);
```

### EndDocument
```cpp
HRESULT EndDocument();
```

### IgnorableWhiteSpace
```cpp
HRESULT IgnorableWhiteSpace(const CATUnicodeString & iCharacters);
```

### ProcessingInstruction
```cpp
HRESULT ProcessingInstruction(const CATUnicodeString & iTarget,
			const CATUnicodeString & iData);
```

### StartElement
```cpp
HRESULT StartElement(const CATUnicodeString & iName, 
			const CATISAXAttributeList_var& iAttributes);
```

## 依赖

- `CATSAXHandlerBase.h`

