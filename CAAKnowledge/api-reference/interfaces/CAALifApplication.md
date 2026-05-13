---
title: "CAALifApplication"
type: "LocalClass"
module: "CAALiteralFeatures"
base: "CATInteractiveApplication"
method_count: 3
source_file: "CAALiteralFeatures.edu/CAALifParamFrame.m/LocalInterfaces/CAALifApplication.h"
---

# CAALifApplication

> This sample illustrates: 1  - The creation of parameters and formulas 2  - The creation of a manipulator 3  - The display of a parameter constrained by a formula in a dialog frame with a spinner How to launch : Type : CAALifParamFrame Inheritance: CATInteractiveApplication (Dialog Framework) CATApplication (System Framework)

**基类**: CATInteractiveApplication | **模块**: CAALiteralFeatures | **方法数**: 3

## 依赖

- `CAALifServices.h`
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


## 公共方法

### GetServices

```cpp
void GetServices(CAALifServices** oServices) ;
```

| 参数 | 类型 |
|------|------|
| oServices | `CAALifServices**` |


---

**源文件**: `CAALiteralFeatures.edu/CAALifParamFrame.m/LocalInterfaces/CAALifApplication.h`
