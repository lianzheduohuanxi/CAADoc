---
title: "CATBatchEventWatcher"
type: "LocalClass"
module: "CAABatchInfrastructure"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAABatchInfrastructure.edu/CAABatBatchLauncherSample.m/LocalInterfaces/CATBatchEventWatcher.h"
---

# CATBatchEventWatcher

**基类**: CATBaseUnknown | **模块**: CAABatchInfrastructure | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATEventSubscriber.h`
- `CATBatchPublicDefinitions.h`

## 公共方法

### SetUUID

```cpp
void SetUUID(char* uuid) ;
```

| 参数 | 类型 |
|------|------|
| uuid | `char*` |


### OnBatchEnd

```cpp
void OnBatchEnd(CATCallbackEvent iEvt, void *iAlarme, CATNotification *iNotif, CATSubscriberData iData, CATCallback iIdCbk) ;
```

| 参数 | 类型 |
|------|------|
| iEvt | `CATCallbackEvent` |
| *iAlarme | `void` |
| *iNotif | `CATNotification` |
| iData | `CATSubscriberData` |
| iIdCbk | `CATCallback` |


---

**源文件**: `CAABatchInfrastructure.edu/CAABatBatchLauncherSample.m/LocalInterfaces/CATBatchEventWatcher.h`
