---
title: "CAAPeoUserAlgorithmNotif"
type: "ProtectedInterface"
module: "CAAOptimizationInterfaces"
base: "CATNotification"
method_count: 6
source_file: "CAAOptimizationInterfaces.edu/ProtectedInterfaces/CAAPeoUserAlgorithmNotif.h"
---

# CAAPeoUserAlgorithmNotif

> Class used to update the stop dialog while running algo in interactive mode. This notification is sent during the algorithm run each time an update is done.

**基类**: CATNotification | **模块**: CAAOptimizationInterfaces | **方法数**: 6

## 依赖

- `CAAPeoCreateUserAlgorithm.h`
- `CATNotification.h`
- `CATUnicodeString.h`

## 公共方法

### GetComment

```cpp
CATUnicodeString GetComment() ;
```


### SetComment

```cpp
HRESULT SetComment(const CATUnicodeString& iComment) ;
```

| 参数 | 类型 |
|------|------|
| iComment | `const CATUnicodeString&` |


### GetElapsedTime

```cpp
int GetElapsedTime() ;
```


### SetElapsedTime

```cpp
HRESULT SetElapsedTime(int iElapsedTime) ;
```

| 参数 | 类型 |
|------|------|
| iElapsedTime | `int` |


### GetCurrentUpdate

```cpp
int GetCurrentUpdate() ;
```


### SetCurrentUpdate

```cpp
HRESULT SetCurrentUpdate(int iCurrentUpdate) ;
```

| 参数 | 类型 |
|------|------|
| iCurrentUpdate | `int` |


---

**源文件**: `CAAOptimizationInterfaces.edu/ProtectedInterfaces/CAAPeoUserAlgorithmNotif.h`
