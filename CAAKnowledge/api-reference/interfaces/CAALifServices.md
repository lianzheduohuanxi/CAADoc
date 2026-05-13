---
title: "CAALifServices"
type: "PublicInterface"
module: "CAALiteralFeatures"
base: ""
method_count: 5
source_file: "CAALiteralFeatures.edu/PublicInterfaces/CAALifServices.h"
---

# CAALifServices

> Defines all the operations required to start a CATIA batch application: * Create a session * Create a document * Retrieve its root container * Close a session ===========================================================================

**基类**: 无 | **模块**: CAALiteralFeatures | **方法数**: 5

## 依赖

- `CAALifBasis.h`
- `CATCke.h`
- `CATUnicodeString.h`
- `CATIPrtPart.h`

## 公共方法

### CAALifCreateInstanceContainer

```cpp
HRESULT CAALifCreateInstanceContainer(CATIContainer** opiContainer) ;
```

| 参数 | 类型 |
|------|------|
| opiContainer | `CATIContainer**` |


### CAALifRetrievePublisherFromCurrentDoc

```cpp
HRESULT CAALifRetrievePublisherFromCurrentDoc(CATIParmPublisher** opiPublisher) ;
```

| 参数 | 类型 |
|------|------|
| opiPublisher | `CATIParmPublisher**` |


### DumpParameter

```cpp
void DumpParameter(CATICkeParm_var& iParm, CATUnicodeString& oString) ;
```

| 参数 | 类型 |
|------|------|
| iParm | `CATICkeParm_var&` |
| oString | `CATUnicodeString&` |


### CAALifInitSession

```cpp
int CAALifInitSession() ;
```


### CAALifCloseSession

```cpp
int CAALifCloseSession() ;
```


---

**源文件**: `CAALiteralFeatures.edu/PublicInterfaces/CAALifServices.h`
