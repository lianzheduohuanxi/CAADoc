---
title: "CAADegAnalysisNumericDlg"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATDlgDialog"
method_count: 2
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegAnalysisNumericDlg.h"
---

# CAADegAnalysisNumericDlg

> Dialog window which enables the user to enter the two radius of an ellipse. This window is used by the CAADegCreateEllipseCmd. Main Method: Build       : creation of the dialog object UpdateValues: Set values on label from the current selection Dialog Framework

**基类**: CATDlgDialog | **模块**: CAADialogEngine | **方法数**: 2

## 依赖

- `CATDlgDialog.h`

## 公共方法

### Build

```cpp
void Build() ;
```


### UpdateValues

```cpp
void UpdateValues(int iNbplane, int iNbpoint, int iNbline, int iNbcircle, int iNbellipse) ;
```

| 参数 | 类型 |
|------|------|
| iNbplane | `int` |
| iNbpoint | `int` |
| iNbline | `int` |
| iNbcircle | `int` |
| iNbellipse | `int` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegAnalysisNumericDlg.h`
