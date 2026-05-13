---
title: "CAAPrtApplication"
type: "LocalClass"
module: "CAAPrint"
base: "CATInteractiveApplication"
method_count: 3
source_file: "CAAPrint.edu/CAAPrtApplication.m/LocalInterfaces/CAAPrtApplication.h"
---

# CAAPrtApplication

> Application class. This is the main object in the process. It avoids writing a main function. Event loop is managed automatically by deriving from CATInteractiveApplication. CAAPrtApplication only creates the main window and subscribes to the window closing to terminate the application. Inheritance: CATInteractiveApplication (Dialog Framework) CATApplication (System Framework) Main Method: BeginApplication: Contains the whole application code.

**基类**: CATInteractiveApplication | **模块**: CAAPrint | **方法数**: 3

## 依赖

- `CATInteractiveApplication.h`

## 公共方法

### DestroyCB

```cpp
void DestroyCB(CATCommand *iPublishingCommand, CATNotification *iNotification, CATCommandClientData iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| *iPublishingCommand | `CATCommand` |
| *iNotification | `CATNotification` |
| iUsefulData | `CATCommandClientData` |


### BeginApplication

```cpp
void BeginApplication() ;
```


### EndApplication

```cpp
int EndApplication() ;
```


---

**源文件**: `CAAPrint.edu/CAAPrtApplication.m/LocalInterfaces/CAAPrtApplication.h`
