---
title: "CAAEAfrEditorDocument"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAApplicationFrame.edu/CAAAfrGeoDocument.m/LocalInterfaces/CAAEAfrEditorDocument.h"
---

# CAAEAfrEditorDocument

> Data Extension of the Late type CAAGeom. Usage: Launch CATIA V5, File/New In the Dialog Box the new document type appears. Inheritance: CATBaseUnknown (System Framework) Main Method: GetEditor

**基类**: CATBaseUnknown | **模块**: CAAApplicationFrame | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`
- `CATEventSubscriber.h`

## 公共方法

### SetEditorToNullWhenClosed

```cpp
void SetEditorToNullWhenClosed(CATCallbackEvent iEvent, void *iFrom, CATNotification *iNotification, CATSubscriberData iData, CATCallback iCallBack) ;
```

| 参数 | 类型 |
|------|------|
| iEvent | `CATCallbackEvent` |
| *iFrom | `void` |
| *iNotification | `CATNotification` |
| iData | `CATSubscriberData` |
| iCallBack | `CATCallback` |


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrGeoDocument.m/LocalInterfaces/CAAEAfrEditorDocument.h`
