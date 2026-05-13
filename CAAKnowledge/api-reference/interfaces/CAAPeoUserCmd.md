---
title: "CAAPeoUserCmd"
type: "ProtectedInterface"
module: "CAAOptimizationInterfaces"
base: "CATCommand"
method_count: 1
source_file: "CAAOptimizationInterfaces.edu/ProtectedInterfaces/CAAPeoUserCmd.h"
---

# CAAPeoUserCmd

**基类**: CATCommand | **模块**: CAAOptimizationInterfaces | **方法数**: 1

## 依赖

- `CAAPeoCreateUserAlgorithm.h`
- `CATCommand.h`

## 公共方法

### OnReceiveNotification

```cpp
void OnReceiveNotification(CATCallbackEvent iCBEvent, void* iClientData, CATNotification *iData, CATSubscriberData iSubData, CATCallback iCB) ;
```

| 参数 | 类型 |
|------|------|
| iCBEvent | `CATCallbackEvent` |
| iClientData | `void*` |
| *iData | `CATNotification` |
| iSubData | `CATSubscriberData` |
| iCB | `CATCallback` |


---

**源文件**: `CAAOptimizationInterfaces.edu/ProtectedInterfaces/CAAPeoUserCmd.h`
