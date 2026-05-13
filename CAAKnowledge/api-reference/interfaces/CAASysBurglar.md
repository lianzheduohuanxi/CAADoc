---
title: "CAASysBurglar"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAASystem.edu/CAASysCallBack.m/LocalInterfaces/CAASysBurglar.h"
---

# CAASysBurglar

> Class which subscribes to an event ==================================================================================

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATEventSubscriber.h`

## 公共方法

### Approach

```cpp
void Approach(CAASysAlarm *iAlarm) ;
```

| 参数 | 类型 |
|------|------|
| *iAlarm | `CAASysAlarm` |


### RunAway

```cpp
void RunAway(CATCallbackEvent iEventAlarm, void *iAlarm, CATNotification *iNotifAlarm, CATSubscriberData iBurglarData, CATCallback iCallBack) ;
```

| 参数 | 类型 |
|------|------|
| iEventAlarm | `CATCallbackEvent` |
| *iAlarm | `void` |
| *iNotifAlarm | `CATNotification` |
| iBurglarData | `CATSubscriberData` |
| iCallBack | `CATCallback` |


---

**源文件**: `CAASystem.edu/CAASysCallBack.m/LocalInterfaces/CAASysBurglar.h`
