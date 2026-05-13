---
title: "CAADlgModel"
type: "LocalClass"
module: "CAADialog"
base: "CATCommand"
method_count: 2
source_file: "CAADialog.edu/CAADlgSendReceive.m/LocalInterfaces/CAADlgModel.h"
---

# CAADlgModel

> This class derives from CATCommand. It shows how to send notifications by using the SendNotification method, and how to answer to a sending object request by redefining the SendCommandSpecificObject method.

**基类**: CATCommand | **模块**: CAADialog | **方法数**: 2

## 依赖

- `CATCommand.h`

## 公共方法

### Add

```cpp
void Add(CAADlgElement *iNewElement) ;
```

| 参数 | 类型 |
|------|------|
| *iNewElement | `CAADlgElement` |


### Remove

```cpp
void Remove(CAADlgElement *iElemenToRemove) ;
```

| 参数 | 类型 |
|------|------|
| *iElemenToRemove | `CAADlgElement` |


---

**源文件**: `CAADialog.edu/CAADlgSendReceive.m/LocalInterfaces/CAADlgModel.h`
