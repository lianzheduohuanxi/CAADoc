---
title: "CAAGSMSewSkinBasicCmd"
type: "LocalClass"
module: "CAAGSMInterfaces"
base: "CATMMUIPanelStateCmd"
method_count: 18
source_file: "CAAGSMInterfaces.edu/CAAGsiFeaturesSplSewSkinBasicUI.m/LocalInterfaces/CAAGSMSewSkinBasicCmd.h"
---

# CAAGSMSewSkinBasicCmd

**基类**: CATMMUIPanelStateCmd | **模块**: CAAGSMInterfaces | **方法数**: 18

## 依赖

- `CATBoolean.h`
- `CATMMUIPanelStateCmd.h`
- `CATShowAttribut.h`

## 公共方法

### CreateStartFeat

```cpp
void CreateStartFeat() ;
```


### BuildGraph

```cpp
void BuildGraph() ;
```


### Highlight_Field1

```cpp
CATBoolean Highlight_Field1(void *) ;
```

| 参数 | 类型 |
|------|------|
| * | `void` |


### Highlight_Field2

```cpp
CATBoolean Highlight_Field2(void *) ;
```

| 参数 | 类型 |
|------|------|
| * | `void` |


### Reset_Highlight

```cpp
CATBoolean Reset_Highlight(void *) ;
```

| 参数 | 类型 |
|------|------|
| * | `void` |


### ClearSelection

```cpp
CATBoolean ClearSelection(void * data) ;
```

| 参数 | 类型 |
|------|------|
| data | `void *` |


### GetMode

```cpp
int GetMode() ;
```


### GetActiveField

```cpp
int GetActiveField() ;
```


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


### SynchronizeViewWithModel

```cpp
CATBoolean SynchronizeViewWithModel(void* data) ;
```

| 参数 | 类型 |
|------|------|
| data | `void*` |


### UndoClearSelection

```cpp
CATBoolean UndoClearSelection(void *) ;
```

| 参数 | 类型 |
|------|------|
| * | `void` |


### OkAction

```cpp
CATBoolean OkAction(void * data) ;
```

| 参数 | 类型 |
|------|------|
| data | `void *` |


### PreviewAction

```cpp
CATBoolean PreviewAction(void *data) ;
```

| 参数 | 类型 |
|------|------|
| *data | `void` |


### CancelAction

```cpp
CATBoolean CancelAction(void* iData) ;
```

| 参数 | 类型 |
|------|------|
| iData | `void*` |


### UpdateOKAction

```cpp
CATBoolean UpdateOKAction(void*data) ;
```

| 参数 | 类型 |
|------|------|
|  | `void*data` |


### ErrorPanel

```cpp
void ErrorPanel(CATUnicodeString Title, CATUnicodeString Text, int iType) ;
```

| 参数 | 类型 |
|------|------|
| Title | `CATUnicodeString` |
| Text | `CATUnicodeString` |
| iType | `int` |


---

**源文件**: `CAAGSMInterfaces.edu/CAAGsiFeaturesSplSewSkinBasicUI.m/LocalInterfaces/CAAGSMSewSkinBasicCmd.h`
