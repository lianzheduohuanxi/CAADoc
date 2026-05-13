---
title: "CAAMfgTPEOnePointSelectionUserCom"
type: "ProtectedInterface"
module: "CAAToolPathEditorItf"
base: "CATStateCommand"
method_count: 7
source_file: "CAAToolPathEditorItf.edu/ProtectedInterfaces/CAAMfgTPEOnePointSelectionUserCom.h"
---

# CAAMfgTPEOnePointSelectionUserCom

**基类**: CATStateCommand | **模块**: CAAToolPathEditorItf | **方法数**: 7

## 依赖

- `CATStateCommand.h`
- `CATDialogAgent.h`
- `CATSelector.h`
- `CATMathPoint.h`
- `CAT3DPointRep.h`
- `CAAMfgTPEAddCmdInCutAreaToolBar.h`

## 公共方法

### BuildGraph

```cpp
void BuildGraph() ;
```


### PreActivate

```cpp
void PreActivate(CATCommand* c1, CATNotification* c2, CATCommandClientData c3) ;
```

| 参数 | 类型 |
|------|------|
| c1 | `CATCommand*` |
| c2 | `CATNotification*` |
| c3 | `CATCommandClientData` |


### Move

```cpp
void Move(CATCommand* c1, CATNotification* c2, CATCommandClientData c3) ;
```

| 参数 | 类型 |
|------|------|
| c1 | `CATCommand*` |
| c2 | `CATNotification*` |
| c3 | `CATCommandClientData` |


### EndPreActivate

```cpp
void EndPreActivate(CATCommand* , CATNotification* , CATCommandClientData) ;
```

| 参数 | 类型 |
|------|------|
|  | `CATCommand*` |
|  | `CATNotification*` |
|  | `CATCommandClientData` |


### SelectPoint

```cpp
CATBoolean SelectPoint(void*) ;
```

| 参数 | 类型 |
|------|------|
|  | `void*` |


### HasPoint

```cpp
CATBoolean HasPoint(void*) ;
```

| 参数 | 类型 |
|------|------|
|  | `void*` |


### Valuate

```cpp
void Valuate(const CATMathPoint& point) ;
```

| 参数 | 类型 |
|------|------|
| point | `const CATMathPoint&` |


---

**源文件**: `CAAToolPathEditorItf.edu/ProtectedInterfaces/CAAMfgTPEOnePointSelectionUserCom.h`
