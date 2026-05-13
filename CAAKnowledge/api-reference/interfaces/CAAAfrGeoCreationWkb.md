---
title: "CAAAfrGeoCreationWkb"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAApplicationFrame.edu/CAAAfrGeoCreationWbench.m/LocalInterfaces/CAAAfrGeoCreationWkb.h"
---

# CAAAfrGeoCreationWkb

> Class which represents the CAAAfrGeoCreationWkb workbench of the CATAfrGeometryWks  Workshop. It implements the CATIGeometryConfiguration interface which is specified by the workshop as the interface to implement in its workbenches. Illustrates: creating a workbench instantiating command headers Inheritance: CATBaseUnknown (System Framework) Main Method: CreateCommands Instantiates the command headers CreateWorkbench Creates toolbars and arranges the commands inside GetAddinInterface Returns the name of the interface that the addins must implement System Framework

**基类**: CATBaseUnknown | **模块**: CAAApplicationFrame | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATListPV.h`

## 公共方法

### CreateCommands

```cpp
void CreateCommands() ;
```


### GetCustomInterfaces

```cpp
void GetCustomInterfaces(CATListPV * oDefaultIIDList, CATListPV * oCustomIIDList) ;
```

| 参数 | 类型 |
|------|------|
| oDefaultIIDList | `CATListPV *` |
| oCustomIIDList | `CATListPV *` |


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrGeoCreationWbench.m/LocalInterfaces/CAAAfrGeoCreationWkb.h`
