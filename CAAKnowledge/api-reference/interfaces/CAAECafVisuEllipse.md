---
title: "CAAECafVisuEllipse"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATExtIVisu"
method_count: 1
source_file: "CAACATIAApplicationFrm.edu/CAACafUseToolsOptions.m/LocalInterfaces/CAAECafVisuEllipse.h"
---

# CAAECafVisuEllipse

> Data extension of the CAASysEllipse component, implementing the CATI3DGeoVisu interface to enable the visualization of the ellipses. This class derives from the CATExtIVisu adapter. Inheritance: CATExtIVisu ( Visualization Framework) CATBaseUnknown (System Framework). Main Method: BuildRep

**基类**: CATExtIVisu | **模块**: CAACATIAApplicationFrm | **方法数**: 1

## 依赖

- `CATExtIVisu.h`

## 虚方法

### BuildRep

```cpp
virtual CATRep * BuildRep() ;
```

Constructs the CAT3DRep for the Ellipse. This rep is kept in the CATExtIVisu code


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafUseToolsOptions.m/LocalInterfaces/CAAECafVisuEllipse.h`
