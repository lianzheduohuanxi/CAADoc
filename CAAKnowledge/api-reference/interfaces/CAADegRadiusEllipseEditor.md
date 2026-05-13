---
title: "CAADegRadiusEllipseEditor"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATDlgDialog"
method_count: 2
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegRadiusEllipseEditor.h"
---

# CAADegRadiusEllipseEditor

> Dialog window which enables the user to enter the two radius of an ellipse. This window is used by the CAADegCreateEllipseCmd. Main Method: Build  : creation of the editors and subscribes to the Ok button. ClickOK: callback subscribed to the Ok button. Stores the radius values. Dialog Framework

**基类**: CATDlgDialog | **模块**: CAADialogEngine | **方法数**: 2

## 依赖

- `CATDlgDialog.h`

## 公共方法

### GetValues

```cpp
void GetValues(float *oU, float *oV) ;
```

| 参数 | 类型 |
|------|------|
| *oU | `float` |
| *oV | `float` |


### Build

```cpp
void Build() ;
```


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegRadiusEllipseEditor.h`
