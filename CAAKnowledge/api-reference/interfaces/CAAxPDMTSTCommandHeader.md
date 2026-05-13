---
title: "CAAxPDMTSTCommandHeader"
type: "LocalClass"
module: "CAAxPDMInterfaces"
base: "CATCommandHeader"
method_count: 2
source_file: "CAAxPDMInterfaces.edu/CAAxPDMToolbar.m/LocalInterfaces/CAAxPDMTSTCommandHeader.h"
---

# CAAxPDMTSTCommandHeader

**基类**: CATCommandHeader | **模块**: CAAxPDMInterfaces | **方法数**: 2

## 依赖

- `CATCommandHeader.h`

## 公共方法

### OnSettingsChange

```cpp
void OnSettingsChange(CATCallbackEvent iEvt, void * iSrv, CATNotification * iNotif, CATSubscriberData iData, CATCallback iCB) ;
```

| 参数 | 类型 |
|------|------|
| iEvt | `CATCallbackEvent` |
| iSrv | `void *` |
| iNotif | `CATNotification *` |
| iData | `CATSubscriberData` |
| iCB | `CATCallback` |


### UpdateHeader

```cpp
void UpdateHeader() ;
```


---

**源文件**: `CAAxPDMInterfaces.edu/CAAxPDMToolbar.m/LocalInterfaces/CAAxPDMTSTCommandHeader.h`
