---
title: "CAAVisBaseApplicationFrame"
type: "LocalClass"
module: "CAAVisualization"
base: "CATDlgDocument"
method_count: 3
source_file: "CAAVisualization.edu/CAAVisBasics.m/LocalInterfaces/CAAVisBaseApplicationFrame.h"
---

# CAAVisBaseApplicationFrame

> Frame of the application. This frame is made with a menu bar, itself made with a file menu, a render menu, a viewpoint menu, a manipulator menu. Inheritance: CAAVisBaseApplicationFrame CATDlgDocument (Dialog Framework) Main Method:

**基类**: CATDlgDocument | **模块**: CAAVisualization | **方法数**: 3

## 依赖

- `CATDlgDocument.h`

## 公共方法

### Build

```cpp
void Build() ;
```


### OnWindowActivated

```cpp
void OnWindowActivated(int iActiveDocIndex) ;
```

| 参数 | 类型 |
|------|------|
| iActiveDocIndex | `int` |


### OnDeleteWindow

```cpp
void OnDeleteWindow(int iActiveDocIndex) ;
```

| 参数 | 类型 |
|------|------|
| iActiveDocIndex | `int` |


---

**源文件**: `CAAVisualization.edu/CAAVisBasics.m/LocalInterfaces/CAAVisBaseApplicationFrame.h`
