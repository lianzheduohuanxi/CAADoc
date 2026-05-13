---
title: "CAAVisBaseViewpointDlg"
type: "LocalClass"
module: "CAAVisualization"
base: "CATDlgDialog"
method_count: 2
source_file: "CAAVisualization.edu/CAAVisBasics.m/LocalInterfaces/CAAVisBaseViewpointDlg.h"
---

# CAAVisBaseViewpointDlg

> Viewpoint Dialog box class. The "Modify viewpoint" push item allows the user to control the Viewpoint parameters through this dialog box. The parameters controled by this dialog box are : Viewpoint origin Viewpoint sight direction Viewpoint projection type Viewpoint focus distance Viewpoint Angle Inheritance: CAAVisBaseViewpointDlg CATDlgDialog (Dialog Framework) Main Method: Build : to build the dialog objects: editors, radio buttons... Init  : to init the different dialog box fields to correct values.

**基类**: CATDlgDialog | **模块**: CAAVisualization | **方法数**: 2

## 依赖

- `CATDlgDialog.h`
- `CATProjectionType.h`

## 公共方法

### Build

```cpp
void Build() ;
```


### Init

```cpp
void Init(const CATMathPointf &iOrigin, const CATMathDirectionf &iSightDirection, CATProjectionType iProjectionType, float iFocusDistance, float iAngle) ;
```

| 参数 | 类型 |
|------|------|
| &iOrigin | `const CATMathPointf` |
| &iSightDirection | `const CATMathDirectionf` |
| iProjectionType | `CATProjectionType` |
| iFocusDistance | `float` |
| iAngle | `float` |


---

**源文件**: `CAAVisualization.edu/CAAVisBasics.m/LocalInterfaces/CAAVisBaseViewpointDlg.h`
