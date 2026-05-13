---
title: "CAAEnoviaV5SaveToPDMCmd"
type: "LocalClass"
module: "CAAProductStructureE5i"
base: "CATStateCommand"
method_count: 5
source_file: "CAAProductStructureE5i.edu/CAAEnoviaV5SaveToPDM.m/LocalInterfaces/CAAEnoviaV5SaveToPDMCmd.h"
---

# CAAEnoviaV5SaveToPDMCmd

**基类**: CATStateCommand | **模块**: CAAProductStructureE5i | **方法数**: 5

## 依赖

- `CATStateCommand.h`
- `CATBoolean.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

Define the Cmd State Sharts


### Activate

```cpp
virtual CATStatusChangeRC Activate(CATCommand *iFromClient, CATNotification *iEvtDat) ;
```

Action Triggered when the Command Gains Focus

| 参数 | 类型 |
|------|------|
| *iFromClient | `CATCommand` |
| *iEvtDat | `CATNotification` |


### Desactivate

```cpp
virtual CATStatusChangeRC Desactivate(CATCommand *iFromClient, CATNotification *iEvtDat) ;
```

Actions Triggered when the Command Loses Focus

| 参数 | 类型 |
|------|------|
| *iFromClient | `CATCommand` |
| *iEvtDat | `CATNotification` |


### Cancel

```cpp
virtual CATStatusChangeRC Cancel(CATCommand *iFromClient, CATNotification *iEvtDat) ;
```

| 参数 | 类型 |
|------|------|
| *iFromClient | `CATCommand` |
| *iEvtDat | `CATNotification` |


## 公共方法

### OnOKSelected

```cpp
CATBoolean OnOKSelected(void *data) ;
```

| 参数 | 类型 |
|------|------|
| *data | `void` |


---

**源文件**: `CAAProductStructureE5i.edu/CAAEnoviaV5SaveToPDM.m/LocalInterfaces/CAAEnoviaV5SaveToPDMCmd.h`
