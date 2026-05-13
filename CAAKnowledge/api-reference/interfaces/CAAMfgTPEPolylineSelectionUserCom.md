---
title: "CAAMfgTPEPolylineSelectionUserCom"
type: "ProtectedInterface"
module: "CAAToolPathEditorItf"
base: "CATStateCommand"
method_count: 4
source_file: "CAAToolPathEditorItf.edu/ProtectedInterfaces/CAAMfgTPEPolylineSelectionUserCom.h"
---

# CAAMfgTPEPolylineSelectionUserCom

**基类**: CATStateCommand | **模块**: CAAToolPathEditorItf | **方法数**: 4

## 依赖

- `CATStateCommand.h`
- `CATPathElementAgent.h`
- `CATDialogAgent.h`
- `CATIMfgCompoundTraject.h`
- `CATBooleanDef.h`
- `CATLISTV_CATMathPoint.h`
- `CATLISTP_CATMathPoint2D.h`
- `CATIMfgTPECutAreasEditor.h`
- `CAAMfgTPEAddCmdInCutAreaToolBar.h`

## 公共方法

### BuildGraph

```cpp
void BuildGraph() ;
```


### LineSelection

```cpp
CATBoolean LineSelection(void* Data) ;
```

| 参数 | 类型 |
|------|------|
| Data | `void*` |


### End

```cpp
CATBoolean End(void *Data) ;
```

| 参数 | 类型 |
|------|------|
| *Data | `void` |


### Valuate

```cpp
void Valuate(int iSwitch) ;
```

| 参数 | 类型 |
|------|------|
| iSwitch | `int` |


---

**源文件**: `CAAToolPathEditorItf.edu/ProtectedInterfaces/CAAMfgTPEPolylineSelectionUserCom.h`
