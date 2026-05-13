---
title: "CAAEV5V6FmExtBehaviorCustomizationAdd"
type: "LocalClass"
module: "CAAV5V6FeatureModelerExt"
base: "CATFmFeatureCustomizationAdaptor"
method_count: 1
source_file: "CAAV5V6FeatureModelerExt.edu/CAAV5V6FmExtBuildUpdate.m/LocalInterfaces/CAAEV5V6FmExtBehaviorCustomizationAdd.h"
---

# CAAEV5V6FmExtBehaviorCustomizationAdd

> This is the implementation of the CATIFmFeatureBehaviorCustomization interface for the "CAAOsmAdd" feature. A "Build" operation calculates the values of attributes according to their pre-defined function.  Its execution is triggered by the execution of an "Update" operation so as to update all current values.  To perform this "Build" operation, the three attributes of the "CAAOsmAdd" feature are retrieved, the values of the first two, "First" and "Second" are added together and their sum is stored as the value of the "Sum" attribute.  Thus, "Sum" wil have an updated value whenever an "Update" operation is requested.

**基类**: CATFmFeatureCustomizationAdaptor | **模块**: CAAV5V6FeatureModelerExt | **方法数**: 1

## 依赖

- `CATFmFeatureCustomizationAdaptor.h`

## 虚方法

### Build

```cpp
virtual HRESULT Build() ;
```

Standard constructors and destructors for an implementation class -----------------------------------------------------------------


---

**源文件**: `CAAV5V6FeatureModelerExt.edu/CAAV5V6FmExtBuildUpdate.m/LocalInterfaces/CAAEV5V6FmExtBehaviorCustomizationAdd.h`
