---
title: "CAADegClippingByBoxCmd"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATStateCommand"
method_count: 11
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegClippingByBoxCmd.h"
---

# CAADegClippingByBoxCmd

**基类**: CATStateCommand | **模块**: CAADialogEngine | **方法数**: 11

## 依赖

- `CATStateCommand.h`
- `CATMathPoint.h`
- `CATMathPoint2D.h`
- `CATBoolean.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

BuildGraph ----------- Implements the statechart. It is called once, even if the command is in repeat mode 1- Creates the dialog agents 2- Creates states 3- Defines transitions


## 公共方法

### CreateCenterBox

```cpp
CATBoolean CreateCenterBox(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### UndoCreateCenterBox

```cpp
CATBoolean UndoCreateCenterBox(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### RedoCreateCenterBox

```cpp
CATBoolean RedoCreateCenterBox(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CreateRepForCenterBox

```cpp
HRESULT CreateRepForCenterBox() ;
```

CreateRepForCenterBox --------------------- Creates a CAT3DCustomRep and three CAT3DFixedArrowGP. The color of these arrows are defined by the current color in the combo set in the "Tools Palette" toolbar. See CAAApplicationFrame.edu FW and its CAAAfrPaletteOptions.m module.


### UpdateClippingBox

```cpp
CATBoolean UpdateClippingBox(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CreateRepForText

```cpp
HRESULT CreateRepForText() ;
```

CreateRepForText ---------------- This method is called once during the command, at the first activation of the command. It enables us to create the graphic representation which has a text as graphic primitive.


### DisplayDialogBox

```cpp
CATBoolean DisplayDialogBox(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### UndoSelText

```cpp
CATBoolean UndoSelText(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### RedoSelText

```cpp
CATBoolean RedoSelText(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### ClippingByBox

```cpp
CATBoolean ClippingByBox(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegClippingByBoxCmd.h`
