---
title: "CAAEVisHistogramChartVisuForRootObject"
type: "LocalClass"
module: "CAAVisualization"
base: "CATExtIVisu"
method_count: 1
source_file: "CAAVisualization.edu/CAAVisGeoModel.m/LocalInterfaces/CAAEVisHistogramChartVisuForRootObject.h"
---

# CAAEVisHistogramChartVisuForRootObject

> Data extension of the CAASysGeomRootObject and CAASysSampRootObject components (root objects of the ACOGeometry and ACODoc document), implementing the CATI3DGeoVisu interface to enable the visualization of the root objects. This class derives from the CATExtIVisu adapter. Inheritance: CATExtIVisu ( Visualization Framework) CATBaseUnknown (System Framework). Main Method: BuildRep Visualization Framework

**基类**: CATExtIVisu | **模块**: CAAVisualization | **方法数**: 1

## 依赖

- `CATExtIVisu.h`

## 虚方法

### BuildRep

```cpp
virtual CATRep * BuildRep() ;
```

Constructs a CAT2DRep with 2D GP to construct an histogram This rep is kept in the CATExtIVisu code


---

**源文件**: `CAAVisualization.edu/CAAVisGeoModel.m/LocalInterfaces/CAAEVisHistogramChartVisuForRootObject.h`
