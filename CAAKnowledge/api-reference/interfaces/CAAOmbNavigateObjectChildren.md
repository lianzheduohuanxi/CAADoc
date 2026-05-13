---
title: "CAAOmbNavigateObjectChildren"
type: "LocalClass"
module: "CAAObjectModelerBase"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAObjectModelerBase.edu/CAAOmbGeoNavigate.m/LocalInterfaces/CAAOmbNavigateObjectChildren.h"
---

# CAAOmbNavigateObjectChildren

> This Use Case illustrates how to implement the CATINavigateObject interface. for elements without children Execute the Use Case: To execute this Use Case, you must be in a CATIA V5 session.  Create a new document of type CAAGeometry.  Create geometric elements in the document.

**基类**: CATBaseUnknown | **模块**: CAAObjectModelerBase | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`

## 虚方法

### GetIdentificators

```cpp
virtual CATListValCATUnicodeString * GetIdentificators() ;
```

GetIdentificators ----------------- Returns node identifier which here is the name of the component


### GetChildren

```cpp
virtual CATListValCATBaseUnknown_var * GetChildren() ;
```

GetChildren ------------ Returns an empty list


---

**源文件**: `CAAObjectModelerBase.edu/CAAOmbGeoNavigate.m/LocalInterfaces/CAAOmbNavigateObjectChildren.h`
