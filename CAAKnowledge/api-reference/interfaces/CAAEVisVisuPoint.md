---
title: "CAAEVisVisuPoint"
type: "LocalClass"
module: "CAAVisualization"
base: "CATExtIVisu"
method_count: 1
source_file: "CAAVisualization.edu/CAAVisGeoModel.m/LocalInterfaces/CAAEVisVisuPoint.h"
---

# CAAEVisVisuPoint

> Data extension of the CAASysPoint component, implementing the CATI3DGeoVisu interface to enable the visualization of the points. This class derives from the CATExtIVisu adapter. Inheritance: CATExtIVisu ( Visualization Framework) CATBaseUnknown (System Framework). Main Method: BuildRep Visualization Framework

**基类**: CATExtIVisu | **模块**: CAAVisualization | **方法数**: 1

## 依赖

- `CATExtIVisu.h`

## 虚方法

### BuildRep

```cpp
virtual CATRep * BuildRep() ;
```

Constructs the CAT3DRep for the Point. This rep is kept in the CATExtIVisu code


---

**源文件**: `CAAVisualization.edu/CAAVisGeoModel.m/LocalInterfaces/CAAEVisVisuPoint.h`
