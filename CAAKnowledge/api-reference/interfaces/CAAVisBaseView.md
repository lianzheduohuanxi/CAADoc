---
title: "CAAVisBaseView"
type: "LocalClass"
module: "CAAVisualization"
base: "CATDlgDialog"
method_count: 2
source_file: "CAAVisualization.edu/CAAVisBasics.m/LocalInterfaces/CAAVisBaseView.h"
---

# CAAVisBaseView

> Document view class. This is a dialog object, which contains a viewer in which every 3D graphical representations are displayed. Inheritance: CAAVisBaseView CATDlgDialog (Dialog Framework) Main Method: CreateViewer: creates the viewer in which the 3D scene is dispayed. Add3DRep    : to visualize in the viewer the CAT3DRep given as an argument.

**基类**: CATDlgDialog | **模块**: CAAVisualization | **方法数**: 2

## 依赖

- `CATDlgDialog.h`

## 公共方法

### Add3DRep

```cpp
void Add3DRep(CAT3DRep *iRoot) ;
```

| 参数 | 类型 |
|------|------|
| *iRoot | `CAT3DRep` |


### Build

```cpp
void Build() ;
```


---

**源文件**: `CAAVisualization.edu/CAAVisBasics.m/LocalInterfaces/CAAVisBaseView.h`
