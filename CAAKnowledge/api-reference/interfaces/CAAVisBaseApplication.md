---
title: "CAAVisBaseApplication"
type: "LocalClass"
module: "CAAVisualization"
base: "CATInteractiveApplication"
method_count: 2
source_file: "CAAVisualization.edu/CAAVisBasics.m/LocalInterfaces/CAAVisBaseApplication.h"
---

# CAAVisBaseApplication

> Application class. This is the main object in the process. It avoids writing a main function. The event loop is managed automatically by deriving from CATInteractiveApplication. It contains the ignition and end steps. Inheritance: CAAVisBaseApplication CATInteractiveApplication (Dialog Framework) CATApplication (System Framework) Main Method: BeginApplication: Contains the whole application code. EndApplication

**基类**: CATInteractiveApplication | **模块**: CAAVisualization | **方法数**: 2

## 依赖

- `CATInteractiveApplication.h`
- `list.h`

## 虚方法

### BeginApplication

```cpp
virtual void BeginApplication() ;
```

Build and destroy the application


### EndApplication

```cpp
virtual int EndApplication() ;
```

Returns the application return code.


---

**源文件**: `CAAVisualization.edu/CAAVisBasics.m/LocalInterfaces/CAAVisBaseApplication.h`
