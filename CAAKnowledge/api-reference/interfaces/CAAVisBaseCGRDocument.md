---
title: "CAAVisBaseCGRDocument"
type: "LocalClass"
module: "CAAVisualization"
base: "CAAVisBaseDocument"
method_count: 2
source_file: "CAAVisualization.edu/CAAVisBasics.m/LocalInterfaces/CAAVisBaseCGRDocument.h"
---

# CAAVisBaseCGRDocument

> CGR Document class. When opening a CGR file, this document is created to manage the model read from this file. It inherits from CAAVisBaseDocument, so, it also have an associated view. Inheritance: CAAVisBaseCGRDocument CAAVisBaseDocument CATCommand (System Framework) Main Method: CreateModel   : Creates the model, which is in fact a graphical representation, that will be visualized in the view. The creation of the model is here reduced to the reading of the CGR file. OpenCGR       : The effective reading of the CGR file.

**基类**: CAAVisBaseDocument | **模块**: CAAVisualization | **方法数**: 2

## 依赖

- `CAAVisBaseDocument.h`

## 虚方法

### CreateModel

```cpp
virtual void CreateModel() ;
```

Creates the model. Here, it is just a call to OpenCGR.


## 公共方法

### OpenCGR

```cpp
void OpenCGR(const char *iFileName) ;
```

| 参数 | 类型 |
|------|------|
| *iFileName | `const char` |


---

**源文件**: `CAAVisualization.edu/CAAVisBasics.m/LocalInterfaces/CAAVisBaseCGRDocument.h`
