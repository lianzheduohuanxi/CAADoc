---
title: "CAAPbiUECreate"
type: "LocalClass"
module: "CAAPSNInteroperability"
base: "CATBaseUnknown"
method_count: 7
source_file: "CAAPSNInteroperability.edu/CAAPbiUECreate.m/LocalInterfaces/CAAPbiUECreate.h"
---

# CAAPbiUECreate

**基类**: CATBaseUnknown | **模块**: CAAPSNInteroperability | **方法数**: 7

## 依赖

- `CATBaseUnknown.h`
- `CATListOfCATUnicodeString.h`
- `CATBoolean.h`
- `CATUnicodeString.h`

## 公共方法

### GetProductEnvironment

```cpp
HRESULT GetProductEnvironment(const CATBaseUnknown* iObj, CATUnicodeString& oEnv, CATUnicodeString& oType) ;
```

| 参数 | 类型 |
|------|------|
| iObj | `const CATBaseUnknown*` |
| oEnv | `CATUnicodeString&` |
| oType | `CATUnicodeString&` |


### GetDocumentEnvironment

```cpp
HRESULT GetDocumentEnvironment(const CATDocument* iDoc, CATUnicodeString& oEnv, CATUnicodeString& oTable) ;
```

| 参数 | 类型 |
|------|------|
| iDoc | `const CATDocument*` |
| oEnv | `CATUnicodeString&` |
| oTable | `CATUnicodeString&` |


### GetDocumentEnvironment

```cpp
HRESULT GetDocumentEnvironment(const char* Filepath, CATUnicodeString& oEnv, CATUnicodeString& oTable) ;
```

| 参数 | 类型 |
|------|------|
| Filepath | `const char*` |
| oEnv | `CATUnicodeString&` |
| oTable | `CATUnicodeString&` |


### GetProductAttributesValue

```cpp
HRESULT GetProductAttributesValue(const CATBaseUnknown* iObj, const CATUnicodeString& iType, int& oNbAttr, CATListOfCATUnicodeString& oAttrName, CATListOfCATUnicodeString& oAttrType, void**& oAttrValues, CATBoolean& oCreateOrUpdate) ;
```

| 参数 | 类型 |
|------|------|
| iObj | `const CATBaseUnknown*` |
| iType | `const CATUnicodeString&` |
| oNbAttr | `int&` |
| oAttrName | `CATListOfCATUnicodeString&` |
| oAttrType | `CATListOfCATUnicodeString&` |
| oAttrValues | `void**&` |
| oCreateOrUpdate | `CATBoolean&` |


### GetDocumentAttributesValue

```cpp
HRESULT GetDocumentAttributesValue(const CATDocument* iDoc, int& oNbAttr, CATListOfCATUnicodeString& oAttrName, CATListOfCATUnicodeString& oAttrType, void**& oAttrValues, CATBoolean& oCreateOrUpdate) ;
```

| 参数 | 类型 |
|------|------|
| iDoc | `const CATDocument*` |
| oNbAttr | `int&` |
| oAttrName | `CATListOfCATUnicodeString&` |
| oAttrType | `CATListOfCATUnicodeString&` |
| oAttrValues | `void**&` |
| oCreateOrUpdate | `CATBoolean&` |


### GetDocumentAttributesValue

```cpp
HRESULT GetDocumentAttributesValue(const char* Filepath, int& oNbAttr, CATListOfCATUnicodeString& oAttrName, CATListOfCATUnicodeString& oAttrType, void**& oAttrValues) ;
```

| 参数 | 类型 |
|------|------|
| Filepath | `const char*` |
| oNbAttr | `int&` |
| oAttrName | `CATListOfCATUnicodeString&` |
| oAttrType | `CATListOfCATUnicodeString&` |
| oAttrValues | `void**&` |


### GetProductAttributesValue

```cpp
HRESULT GetProductAttributesValue(const char* Filepath, int& oNbAttr, CATListOfCATUnicodeString& oAttrName, CATListOfCATUnicodeString& oAttrType, void**& oAttrValues) ;
```

| 参数 | 类型 |
|------|------|
| Filepath | `const char*` |
| oNbAttr | `int&` |
| oAttrName | `CATListOfCATUnicodeString&` |
| oAttrType | `CATListOfCATUnicodeString&` |
| oAttrValues | `void**&` |


---

**源文件**: `CAAPSNInteroperability.edu/CAAPbiUECreate.m/LocalInterfaces/CAAPbiUECreate.h`
