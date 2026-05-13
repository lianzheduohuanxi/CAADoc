---
title: "CAAPriEBuildShape"
type: "LocalClass"
module: "CAAPartInterfaces"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAPartInterfaces.edu/CAAPriBuildUserPad.m/LocalInterfaces/CAAPriEBuildShape.h"
---

# CAAPriEBuildShape

> The method described here shows how to implemented the CATIBuildShape interface for a Mechanical Design form feature on a simplified pad named UserPad The UserPad specifications are: a sketch that defines the profile. The sketch must be closed. the direction is perpedicular to the sketch plane. the limits of the pad are defined by offset values: the first limit offset value is 30. the second limit offset value is 0, so the pad starts from the sketch plane. The differents steps are: 1- Retrieving the containers 2- Retrieving and defining the specifications of the UserPad operation 3- Creating the procedural report 4- Performing the shape building 5- Storing the procedural report

**基类**: CATBaseUnknown | **模块**: CAAPartInterfaces | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### BuildShape

```cpp
int BuildShape() ;
```


---

**源文件**: `CAAPartInterfaces.edu/CAAPriBuildUserPad.m/LocalInterfaces/CAAPriEBuildShape.h`
