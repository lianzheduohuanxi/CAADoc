---
title: "CAAOsmAddOp"
type: "LocalClass"
module: "CAAObjectSpecsModeler"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAObjectSpecsModeler.edu/CAAOsmBuildUpdate.m/LocalInterfaces/CAAOsmAddOp.h"
---

# CAAOsmAddOp

> This is the implementation of the CATIBuild interface for the "CAAOsmAddOp" feature. A "Build" operation calculates the values of attributes according to their pre-defined function.  Its execution is triggered by the execution of an "Update" operation so as to update all current values.  To perform this "Build" operation, the three attributes of the "CAAOsmAdd" feature are retrieved, the values of the first two, "First" and "Second" are added together and their sum is stored as the value of the "Sum" attribute.  Thus, "Sum" wil have an updated value whenever an "Update" operation is requested.

**基类**: CATBaseUnknown | **模块**: CAAObjectSpecsModeler | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### Build

```cpp
HRESULT Build() ;
```


---

**源文件**: `CAAObjectSpecsModeler.edu/CAAOsmBuildUpdate.m/LocalInterfaces/CAAOsmAddOp.h`
