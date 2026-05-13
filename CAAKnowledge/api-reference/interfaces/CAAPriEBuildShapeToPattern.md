---
title: "CAAPriEBuildShapeToPattern"
type: "LocalClass"
module: "CAAPartInterfaces"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAPartInterfaces.edu/CAAPriPattern.m/LocalInterfaces/CAAPriEBuildShapeToPattern.h"
---

# CAAPriEBuildShapeToPattern

> In this sample we have enriched the CATIBuilShape implementation described in the CAAPriEBuildShape sample to allow the implemented feature to be patterned. The differents steps are : 1- Defines if the BuildShape method is called in pattern context 2- In pattern context, you do not delete the scope 3- Sets the list of operands 4- Transform geometries generated from specifications 5- Sets topological journal and the geometry performed. Return code of the BuildShape method: 0. Successful creation 1. Not closed profile 2. Problem on querying an Update Error interface on Pattern Pad

**基类**: CATBaseUnknown | **模块**: CAAPartInterfaces | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### BuildShape

```cpp
int BuildShape() ;
```

Destructor


---

**源文件**: `CAAPartInterfaces.edu/CAAPriPattern.m/LocalInterfaces/CAAPriEBuildShapeToPattern.h`
