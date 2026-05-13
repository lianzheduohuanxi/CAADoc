---
title: "CATTestListViewAppli"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATInteractiveApplication"
method_count: 2
source_file: "CAACATIAApplicationFrm.edu/CAACafDlgView.m/LocalInterfaces/CATTestListViewAppli.h"
---

# CATTestListViewAppli

> Application class. This is the main object in the process. It avoids writing a main function. Event loop is managed automatically by deriving from CATInteractiveApplication. CATTestListViewAppli only creates the main window and subscribes to the window closing to terminate the application. Inheritance: CATInteractiveApplication (Dialog Framework) CATApplication (System Framework) Main Method: BeginApplication: Contains the whole application code. CATIAApplicationFrame Framework

**基类**: CATInteractiveApplication | **模块**: CAACATIAApplicationFrm | **方法数**: 2

## 依赖

- `CATInteractiveApplication.h`

## 公共方法

### BeginApplication

```cpp
void BeginApplication() ;
```


### EndApplication

```cpp
int EndApplication() ;
```


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafDlgView.m/LocalInterfaces/CATTestListViewAppli.h`
