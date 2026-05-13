---
title: "CAAESmiUserOperationStrategyEditor"
type: "LocalClass"
module: "CAASurfaceMachiningItf"
base: "CATIMfgStrategyActivity"
method_count: 1
source_file: "CAASurfaceMachiningItf.edu/CAASmiUserOperationUI.m/LocalInterfaces/CAAESmiUserOperationStrategyEditor.h"
---

# CAAESmiUserOperationStrategyEditor

**基类**: CATIMfgStrategyActivity | **模块**: CAASurfaceMachiningItf | **方法数**: 1

## 依赖

- `CATIMfgStrategyActivity.h`
- `CATDialog.h`
- `CATDlgFrame.h`

## 公共方法

### GetMainPanelEditor

```cpp
HRESULT GetMainPanelEditor(CATDialog * iFather, CATDlgFrame*& oFrame, CATDlgStyle iStyle=NULL) ;
```

Writes the strategy tabpage frame.

| 参数 | 类型 |
|------|------|
| iFather | `CATDialog *` |
| oFrame | `CATDlgFrame*&` |
| iStyle=NULL | `CATDlgStyle` |


---

**源文件**: `CAASurfaceMachiningItf.edu/CAASmiUserOperationUI.m/LocalInterfaces/CAAESmiUserOperationStrategyEditor.h`
