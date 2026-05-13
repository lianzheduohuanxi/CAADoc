---
title: "CAAOmbNavigateObjectRoot"
type: "LocalClass"
module: "CAAObjectModelerBase"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAObjectModelerBase.edu/CAAOmbGeoNavigate.m/LocalInterfaces/CAAOmbNavigateObjectRoot.h"
---

# CAAOmbNavigateObjectRoot

> This use case illustrates how to implement the CATINavigateObject interface on an element with children Execute the Use Case: To execute this Use Case, you must be in a CATIA V5 session.  Create a new document of type CAAGeometry.  Create geometric elements in the document.

**基类**: CATBaseUnknown | **模块**: CAAObjectModelerBase | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`

## 虚方法

### GetIdentificators

```cpp
virtual CATListValCATUnicodeString * GetIdentificators() ;
```

GetIdentificators ----------------- Returns node identifiers.


### GetChildren

```cpp
virtual CATListValCATBaseUnknown_var * GetChildren() ;
```

GetChildren ------------ Returns a list of the direct children of the current node.


---

**源文件**: `CAAObjectModelerBase.edu/CAAOmbGeoNavigate.m/LocalInterfaces/CAAOmbNavigateObjectRoot.h`
