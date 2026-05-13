---
title: "CAAESmiUserOperationMacroEditor"
type: "LocalClass"
module: "CAASurfaceMachiningItf"
base: "CATIMfgMacroEditorActivity"
method_count: 1
source_file: "CAASurfaceMachiningItf.edu/CAASmiUserOperationUI.m/LocalInterfaces/CAAESmiUserOperationMacroEditor.h"
---

# CAAESmiUserOperationMacroEditor

**基类**: CATIMfgMacroEditorActivity | **模块**: CAASurfaceMachiningItf | **方法数**: 1

## 依赖

- `CATIMfgMacroEditorActivity.h`
- `CATDlgFrame.h`
- `CATDialog.h`

## 公共方法

### GetMainPanelEditor

```cpp
HRESULT GetMainPanelEditor(CATDialog * iFather, CATDlgFrame*& oFrame, CATDlgStyle iStyle=NULL) ;
```

Writes the macro tabpage frame.

| 参数 | 类型 |
|------|------|
| iFather | `CATDialog *` |
| oFrame | `CATDlgFrame*&` |
| iStyle=NULL | `CATDlgStyle` |


---

**源文件**: `CAASurfaceMachiningItf.edu/CAASmiUserOperationUI.m/LocalInterfaces/CAAESmiUserOperationMacroEditor.h`
