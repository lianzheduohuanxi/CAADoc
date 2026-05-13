---
title: "CAADlgTessellation"
type: "LocalClass"
module: "CAADialog"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAADialog.edu/CAADlgOnIdle.m/LocalInterfaces/CAADlgTessellation.h"
---

# CAADlgTessellation

> Class which subscribes to an event ==================================================================================

**基类**: CATBaseUnknown | **模块**: CAADialog | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATEventSubscriber.h`

## 公共方法

### Init

```cpp
void Init(CAADlgObject *iObjectToTesselate) ;
```

| 参数 | 类型 |
|------|------|
| *iObjectToTesselate | `CAADlgObject` |


### Tessellate

```cpp
void Tessellate(CATCallbackEvent iEventObject, void *iObject, CATNotification *iNotifObject, CATSubscriberData iUsefulData, CATCallback iCallBack) ;
```

| 参数 | 类型 |
|------|------|
| iEventObject | `CATCallbackEvent` |
| *iObject | `void` |
| *iNotifObject | `CATNotification` |
| iUsefulData | `CATSubscriberData` |
| iCallBack | `CATCallback` |


---

**源文件**: `CAADialog.edu/CAADlgOnIdle.m/LocalInterfaces/CAADlgTessellation.h`
