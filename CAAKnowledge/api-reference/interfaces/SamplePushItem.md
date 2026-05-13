---
title: "SamplePushItem"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATDlgPushItem"
method_count: 2
source_file: "CAACATIAApplicationFrm.edu/CAACafDlgView.m/LocalInterfaces/SamplePushItem.h"
---

# SamplePushItem

**基类**: CATDlgPushItem | **模块**: CAACATIAApplicationFrm | **方法数**: 2

## 依赖

- `CATDlgPushItem.h`
- `CATCommand.h`
- `CATString.h`

## 公共方法

### OnPushed

```cpp
void OnPushed(CATCommand *, CATNotification *, CATCommandClientData) ;
```

| 参数 | 类型 |
|------|------|
| * | `CATCommand` |
| * | `CATNotification` |
|  | `CATCommandClientData` |


### UnregisterItemActivatedEvent

```cpp
void UnregisterItemActivatedEvent(CATEventSubscriber *iSubscriber, CATCallback iActivateCallback) ;
```

| 参数 | 类型 |
|------|------|
| *iSubscriber | `CATEventSubscriber` |
| iActivateCallback | `CATCallback` |


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafDlgView.m/LocalInterfaces/SamplePushItem.h`
