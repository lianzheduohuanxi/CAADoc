---
title: "CAAPeoUserAlgoSettingsFrame"
type: "LocalClass"
module: "CAAOptimizationInterfaces"
base: "CATDlgFrame"
method_count: 3
source_file: "CAAOptimizationInterfaces.edu/CAAPeoCreateUserAlgorithmUI.m/LocalInterfaces/CAAPeoUserAlgoSettingsFrame.h"
---

# CAAPeoUserAlgoSettingsFrame

**基类**: CATDlgFrame | **模块**: CAAOptimizationInterfaces | **方法数**: 3

## 依赖

- `CATIOptAlgorithm.h`
- `CATDlgFrame.h`
- `CATDlgRadioButton.h`
- `CATDlgEditor.h`
- `CATDlgCheckButton.h`
- `CATDlgLabel.h`
- `CATDlgCombo.h`

## 虚方法

### Build

```cpp
virtual HRESULT Build(CATIOptAlgorithm_var spiAlgo) ;
```

| 参数 | 类型 |
|------|------|
| spiAlgo | `CATIOptAlgorithm_var` |


## 公共方法

### OnChangeMaxEval

```cpp
void OnChangeMaxEval(CATCommand* cmd, CATNotification* evt, CATCommandClientData data) ;
```

| 参数 | 类型 |
|------|------|
| cmd | `CATCommand*` |
| evt | `CATNotification*` |
| data | `CATCommandClientData` |


### OnChangeTime

```cpp
void OnChangeTime(CATCommand* cmd, CATNotification* evt, CATCommandClientData data) ;
```

| 参数 | 类型 |
|------|------|
| cmd | `CATCommand*` |
| evt | `CATNotification*` |
| data | `CATCommandClientData` |


---

**源文件**: `CAAOptimizationInterfaces.edu/CAAPeoCreateUserAlgorithmUI.m/LocalInterfaces/CAAPeoUserAlgoSettingsFrame.h`
