---
title: "CAAMmrCombCrvPanelStCmd"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATMMUIPanelStateCmd"
method_count: 14
source_file: "CAAMechanicalModeler.edu/CAAMmrCombinedCurveUI.m/LocalInterfaces/CAAMmrCombCrvPanelStCmd.h"
---

# CAAMmrCombCrvPanelStCmd

**基类**: CATMMUIPanelStateCmd | **模块**: CAAMechanicalModeler | **方法数**: 14

## 依赖

- `CATMMUIPanelStateCmd.h`

## 公共方法

### BuildGraph

```cpp
void BuildGraph() ;
```


### OkAction

```cpp
CATBoolean OkAction(void *) ;
```

| 参数 | 类型 |
|------|------|
| * | `void` |


### CancelAction

```cpp
CATBoolean CancelAction(void *) ;
```

| 参数 | 类型 |
|------|------|
| * | `void` |


### GetMode

```cpp
int GetMode() ;
```


### CurveSelected

```cpp
CATBoolean CurveSelected(void *) ;
```

| 参数 | 类型 |
|------|------|
| * | `void` |


### DirectionSelected

```cpp
CATBoolean DirectionSelected(void *) ;
```

| 参数 | 类型 |
|------|------|
| * | `void` |


### ElementSelected

```cpp
void ElementSelected(CATFeatureImportAgent *pAgent) ;
```

| 参数 | 类型 |
|------|------|
| *pAgent | `CATFeatureImportAgent` |


### Curve1FieldSelected

```cpp
CATBoolean Curve1FieldSelected(void *) ;
```

| 参数 | 类型 |
|------|------|
| * | `void` |


### Direction1FieldSelected

```cpp
CATBoolean Direction1FieldSelected(void *) ;
```

| 参数 | 类型 |
|------|------|
| * | `void` |


### Curve2FieldSelected

```cpp
CATBoolean Curve2FieldSelected(void *) ;
```

| 参数 | 类型 |
|------|------|
| * | `void` |


### Direction2FieldSelected

```cpp
CATBoolean Direction2FieldSelected(void *) ;
```

| 参数 | 类型 |
|------|------|
| * | `void` |


### SetActiveField

```cpp
void SetActiveField(int ActiveField) ;
```

| 参数 | 类型 |
|------|------|
| ActiveField | `int` |


### UpdatePanelFields

```cpp
void UpdatePanelFields() ;
```


### CheckOKSensitivity

```cpp
void CheckOKSensitivity() ;
```


---

**源文件**: `CAAMechanicalModeler.edu/CAAMmrCombinedCurveUI.m/LocalInterfaces/CAAMmrCombCrvPanelStCmd.h`
