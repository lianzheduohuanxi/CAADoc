---
title: "CAAMcaUdfAdn"
type: "LocalClass"
module: "CAAMechanicalCommands"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAMechanicalCommands.edu/CAAMcaUdfAddin.m/LocalInterfaces/CAAMcaUdfAdn.h"
---

# CAAMcaUdfAdn

> Class which represents an addin of the Generative Shape Design Workbench. It implements the CATIShapeDesignWorkshopAddin interface. Illustrates: creating a workbench addin instantiating a command which creates and edits a user feature How to launch 1) Remove the # sign before the following line in the interface dictionary CAAMcaUdfAddin  CATIShapeDesignWorkshopAddin libCAAMcaUdfAddin 2) Launch CNext 3) Select the Generative Shape Design workbench in the Start menu Main Method: CreateCommands Instantiates the command headers CreateToolbars Creates toolbars and arranges the commands inside System framework

**基类**: CATBaseUnknown | **模块**: CAAMechanicalCommands | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### CreateCommands

```cpp
void CreateCommands() ;
```


---

**源文件**: `CAAMechanicalCommands.edu/CAAMcaUdfAddin.m/LocalInterfaces/CAAMcaUdfAdn.h`
