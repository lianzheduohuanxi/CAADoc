---
title: "CAADegBoxCreationChoiceNotification"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATNotification"
method_count: 2
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegBoxCreationChoiceNotification.h"
---

# CAADegBoxCreationChoiceNotification

> This kind of notification are sent by the CAADegBoxPaletteChoiceCmd command when the end user clicks on a check header displayed in the Palette. Each check header defines a way to create a box. The box creation is defined by the CAADegCreateBoxCmd state command. It is this command which adds the check headers in the Palette.

**基类**: CATNotification | **模块**: CAADialogEngine | **方法数**: 2

## 依赖

- `CATNotification.h`

## 公共方法

### GetChoice

```cpp
HRESULT GetChoice(int & oChoiceValue) ;
```

This method will be used by the CAADegCreateBoxCmd command to know which check header has been pushed by the end user.

| 参数 | 类型 |
|------|------|
| oChoiceValue | `int &` |


### SetChoice

```cpp
HRESULT SetChoice(int iChoiceValue) ;
```

This method is used by the command which sends the notification. This command is CAADegBoxPaletteChoiceCmd

| 参数 | 类型 |
|------|------|
| iChoiceValue | `int` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegBoxCreationChoiceNotification.h`
