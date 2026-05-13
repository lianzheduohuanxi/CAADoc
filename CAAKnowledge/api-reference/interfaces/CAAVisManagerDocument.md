---
title: "CAAVisManagerDocument"
type: "LocalClass"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAVisualization.edu/CAAVisManagerAppli.m/LocalInterfaces/CAAVisManagerDocument.h"
---

# CAAVisManagerDocument

> Base class of the application document.

**基类**: CATBaseUnknown | **模块**: CAAVisualization | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATString.h`

## 虚方法

### CreateDefaultWindow

```cpp
virtual CAAVisManagerWindow * CreateDefaultWindow() ;
```


## 公共方法

### InsertCGR

```cpp
HRESULT InsertCGR(const char *iName) ;
```

Adds a CGR file in the current document

| 参数 | 类型 |
|------|------|
| *iName | `const char` |


---

**源文件**: `CAAVisualization.edu/CAAVisManagerAppli.m/LocalInterfaces/CAAVisManagerDocument.h`
