---
title: "CAA2DLPrintToDraftingWatcher"
type: "LocalClass"
module: "CAADrafting2DLInterfaces"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAADrafting2DLInterfaces.edu/CAA2DLPrintToDrafting.m/LocalInterfaces/CAA2DLPrintToDraftingWatcher.h"
---

# CAA2DLPrintToDraftingWatcher

**基类**: CATBaseUnknown | **模块**: CAADrafting2DLInterfaces | **方法数**: 2

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

**源文件**: `CAADrafting2DLInterfaces.edu/CAA2DLPrintToDrafting.m/LocalInterfaces/CAA2DLPrintToDraftingWatcher.h`
