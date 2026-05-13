---
title: "CAAEMaiToolPathDrillingCustomization"
type: "LocalClass"
module: "CAAManufacturingItf"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAManufacturingItf.edu/CAAMaiToolPathCustomization.m/LocalInterfaces/CAAEMaiToolPathDrillingCustomization.h"
---

# CAAEMaiToolPathDrillingCustomization

> Data extension of the "Drilling" Late Type. Usage: Launch CATIA V5, Create a "Drilling" operation inside Prismatic Machining Programmer, then replay it. Inheritance: CATBaseUnknown (System Framework) Main Method: ComputeToolPath

**基类**: CATBaseUnknown | **模块**: CAAManufacturingItf | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`
- `CATIContainer.h`
- `CATIMfgToolPath.h`

## 虚方法

### ComputeToolPath

```cpp
virtual HRESULT ComputeToolPath(const CATIContainer_var &ispContainer, CATIMfgToolPath_var &ospToolPath) ;
```

ComputeToolPath Compute the tool path of the current Drilling operation ispContainer : Interface on the tool path container ospToolPath  : Computed tool path

| 参数 | 类型 |
|------|------|
| &ispContainer | `const CATIContainer_var` |
| &ospToolPath | `CATIMfgToolPath_var` |


---

**源文件**: `CAAManufacturingItf.edu/CAAMaiToolPathCustomization.m/LocalInterfaces/CAAEMaiToolPathDrillingCustomization.h`
