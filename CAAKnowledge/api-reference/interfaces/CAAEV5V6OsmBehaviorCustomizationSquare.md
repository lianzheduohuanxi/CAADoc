---
title: "CAAEV5V6OsmBehaviorCustomizationSquare"
type: "LocalClass"
module: "CAAV5V6ObjectSpecsModeler"
base: "CATFmFeatureCustomizationAdaptor"
method_count: 1
source_file: "CAAV5V6ObjectSpecsModeler.edu/CAAV5V6OsmBuildUpdate.m/LocalInterfaces/CAAEV5V6OsmBehaviorCustomizationSquare.h"
---

# CAAEV5V6OsmBehaviorCustomizationSquare

> This is the implementation of the CATIFmFeatureBehaviorCustomization interface for the "CAAOsmSquare" feature. A "Build" operation calculates the values of attributes according to their pre-defined function.  Its execution is triggered by the execution of an "Update" operation so as to update all current values.  To perform this "Build" operation, the two attributes of the "CAAOsmSquare" feature are retrieved, the value of the first, "Num", is squared and the result stored as the value of the second, "Square" attribute.  Thus, the attribute "Square" will have an updated value whenever an "Update" operation is requested on this feature.

**基类**: CATFmFeatureCustomizationAdaptor | **模块**: CAAV5V6ObjectSpecsModeler | **方法数**: 1

## 依赖

- `CATFmFeatureCustomizationAdaptor.h`

## 虚方法

### Build

```cpp
virtual HRESULT Build() ;
```


---

**源文件**: `CAAV5V6ObjectSpecsModeler.edu/CAAV5V6OsmBuildUpdate.m/LocalInterfaces/CAAEV5V6OsmBehaviorCustomizationSquare.h`
