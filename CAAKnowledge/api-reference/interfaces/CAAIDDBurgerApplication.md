---
title: "CAAIDDBurgerApplication"
type: "LocalClass"
module: "CAACodeGenTools"
base: "CATInteractiveApplication"
method_count: 2
source_file: "CAACodeGenTools.edu/CAAIDDBurger.m/LocalInterfaces/CAAIDDBurgerApplication.h"
---

# CAAIDDBurgerApplication

> Application class. This is the main object in the process. It avoids writing a main function. Event loop is managed automatically by deriving from CATInteractiveApplication. CAADlgBurgerApplication only creates the main window and subscribes to the window closing to terminate the application. Inheritance: CATInteractiveApplication (Dialog Framework) CATApplication (System Framework) Main Method: BeginApplication: Contains the whole application code. Dialog Framework

**基类**: CATInteractiveApplication | **模块**: CAACodeGenTools | **方法数**: 2

## 依赖

- `CATInteractiveApplication.h`

## 虚方法

### BeginApplication

```cpp
virtual void BeginApplication() ;
```


### EndApplication

```cpp
virtual int EndApplication() ;
```

Returns the application return code.


---

**源文件**: `CAACodeGenTools.edu/CAAIDDBurger.m/LocalInterfaces/CAAIDDBurgerApplication.h`
