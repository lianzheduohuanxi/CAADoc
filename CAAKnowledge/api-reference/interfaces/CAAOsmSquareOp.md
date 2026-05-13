---
title: "CAAOsmSquareOp"
type: "LocalClass"
module: "CAAObjectSpecsModeler"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAObjectSpecsModeler.edu/CAAOsmBuildUpdate.m/LocalInterfaces/CAAOsmSquareOp.h"
---

# CAAOsmSquareOp

> This is the implementation of the CATIBuild interface for the "CAAOsmSquareOp" feature. A "Build" operation calculates the values of attributes according to their pre-defined function.  Its execution is triggered by the execution of an "Update" operation so as to update all current values.  To perform this "Build" operation, the two attributes of the "CAAOsmSquare" feature are retrieved, the value of the first, "Num", is squared and the result stored as the value of the second, "Square" attribute.  Thus, the attribute "Square" will have an updated value whenever an "Update" operation is requested on this feature. Main Methods: GetAttrKey:   Retrieves the attribute key for a given attribute name on a given feature. GetInteger:   Retrieves the integer value for a given attribute key on a given feature. SetInteger:   Assigns an integer value to a given attribute key on a given feature.

**基类**: CATBaseUnknown | **模块**: CAAObjectSpecsModeler | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### Build

```cpp
HRESULT Build() ;
```


---

**源文件**: `CAAObjectSpecsModeler.edu/CAAOsmBuildUpdate.m/LocalInterfaces/CAAOsmSquareOp.h`
