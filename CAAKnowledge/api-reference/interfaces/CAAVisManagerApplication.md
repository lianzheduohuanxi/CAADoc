---
title: "CAAVisManagerApplication"
type: "LocalClass"
module: "CAAVisualization"
base: "CATInteractiveApplication"
method_count: 3
source_file: "CAAVisualization.edu/CAAVisManagerAppli.m/LocalInterfaces/CAAVisManagerApplication.h"
---

# CAAVisManagerApplication

> Application class. This is the main object in the process. It avoids writing a main function. Event loop is managed automatically by deriving from CATInteractiveApplication. CAAVisManagerApplication does the following jobs: * creates the main window: the application frame. * subscribes to the window closing to terminate the application. * creates a default document (and it is then displayed into a 3D viewer). Inheritance: CATInteractiveApplication (Dialog Framework) CATApplication (System Framework) Main Method: * BeginApplication: Contains the whole application code.

**基类**: CATInteractiveApplication | **模块**: CAAVisualization | **方法数**: 3

## 依赖

- `CATInteractiveApplication.h`
- `list.h`
- `CAAVisManagerWindow.h`

## 虚方法

### BeginApplication

```cpp
virtual void BeginApplication() ;
```

Contains the application code


### EndApplication

```cpp
virtual int EndApplication() ;
```

Returns the application return code.


## 静态方法

### GetFrame

```cpp
static CATDlgDocument * GetFrame() ;
```


---

**源文件**: `CAAVisualization.edu/CAAVisManagerAppli.m/LocalInterfaces/CAAVisManagerApplication.h`
