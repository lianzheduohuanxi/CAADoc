---
title: "CAAESmiUserOperationGeometryEditor"
type: "LocalClass"
module: "CAASurfaceMachiningItf"
base: "CATIMfgGeometryActivity"
method_count: 1
source_file: "CAASurfaceMachiningItf.edu/CAASmiUserOperationGeomUI.m/LocalInterfaces/CAAESmiUserOperationGeometryEditor.h"
---

# CAAESmiUserOperationGeometryEditor

**基类**: CATIMfgGeometryActivity | **模块**: CAASurfaceMachiningItf | **方法数**: 1

## 依赖

- `CATIMfgGeometryActivity.h`
- `CATDlgFrame.h`
- `CATDialog.h`

## 公共方法

### GetMainPanelEditor

```cpp
HRESULT GetMainPanelEditor(CATDialog * iFather, CATDlgFrame*& oFrame, CATDlgStyle iStyle=NULL) ;
```

Writes the geometry tabpage frame.

| 参数 | 类型 |
|------|------|
| iFather | `CATDialog *` |
| oFrame | `CATDlgFrame*&` |
| iStyle=NULL | `CATDlgStyle` |


---

**源文件**: `CAASurfaceMachiningItf.edu/CAASmiUserOperationGeomUI.m/LocalInterfaces/CAAESmiUserOperationGeometryEditor.h`
