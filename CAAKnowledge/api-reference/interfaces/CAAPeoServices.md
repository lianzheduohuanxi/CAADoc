---
title: "CAAPeoServices"
type: "ProtectedInterface"
module: "CAAOptimizationInterfaces"
base: ""
method_count: 5
source_file: "CAAOptimizationInterfaces.edu/ProtectedInterfaces/CAAPeoServices.h"
---

# CAAPeoServices

> Defines all the operations required to start a CATIA batch application: * Create a session * Create a document * Retrieve its root container * Close a session

**基类**: 无 | **模块**: CAAOptimizationInterfaces | **方法数**: 5

## 依赖

- `CAAPeoBasis.h`
- `CATUnicodeString.h`
- `CATIPrtPart.h`

## 公共方法

### CAAPeoCreateInstanceContainer

```cpp
HRESULT CAAPeoCreateInstanceContainer(CATIContainer** opiContainer) ;
```

| 参数 | 类型 |
|------|------|
| opiContainer | `CATIContainer**` |


### CAAPeoOpenInstanceContainer

```cpp
HRESULT CAAPeoOpenInstanceContainer(const CATUnicodeString& iFilePath, CATIContainer** opiContainer) ;
```

| 参数 | 类型 |
|------|------|
| iFilePath | `const CATUnicodeString&` |
| opiContainer | `CATIContainer**` |


### CAAPeoInitSession

```cpp
HRESULT CAAPeoInitSession() ;
```


### CAAPeoCloseSession

```cpp
HRESULT CAAPeoCloseSession(const CATUnicodeString& iSavingDocPath = "") ;
```

| 参数 | 类型 |
|------|------|
| "" | `const CATUnicodeString& iSavingDocPath =` |


### CAAPeoRetrievePublisherFromCurrentDoc

```cpp
HRESULT CAAPeoRetrievePublisherFromCurrentDoc(CATIParmPublisher** opiPublisher) ;
```

| 参数 | 类型 |
|------|------|
| opiPublisher | `CATIParmPublisher**` |


---

**源文件**: `CAAOptimizationInterfaces.edu/ProtectedInterfaces/CAAPeoServices.h`
