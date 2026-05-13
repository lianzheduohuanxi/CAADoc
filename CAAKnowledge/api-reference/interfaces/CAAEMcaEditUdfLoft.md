---
title: "CAAEMcaEditUdfLoft"
type: "LocalClass"
module: "CAAMechanicalCommands"
base: "CATExtIEdit"
method_count: 1
source_file: "CAAMechanicalCommands.edu/CAAMcaUdfEdit.m/LocalInterfaces/CAAEMcaEditUdfLoft.h"
---

# CAAEMcaEditUdfLoft

> Data extension of the CAAUdfLoft component implementing the CATIEdit interface. CAAUdfLoft is the type of the user feature reference, CAAUserFeatureSample, created by the CAAMcaUdfCreation use case. The command to edit the user feature, instance of the CAAUserFeatureSample, is defined in the CAAMcaUdfEdit.m module How to launch ? In the InstallRootDirectory/CAAMechanicalCommands.edu/InputData you find the following files: 1) CAAUdfLoft.CATPart document which contains the  CAAUserFeatureSample user feature reference without a type 2) CAAUdfModelWithInstances.CATPart document which contains two instances of the CAAUserFeatureSample user feature reference without the CAAUdfLoft type 3) CAAUdfLoftWithType.CATPart document which contains the  CAAUserFeatureSample user feature reference with the CAAUdfLoft type 4) CAAUdfModelWithTypeInst.CATPart document which contains one instance of the CAAUserFeatureSample user feature reference with the CAAUdfLoft type scenarios: in Cnext, open the  CAAUdfModelWithTypeInst.CATPart document, double click on the CAAUserFeatureSampleToEdit feature : the customized dialog box appears in Cnext, open the  CAAUdfModelWithInstances.CATPart document, double click on the CAAUserFeatureSample.1 or on the The Loft with Point2 and Point3 features: the default edit dialog box appears where InstallRootDirectory is the directory where the CAA CD-ROM is installed.

**基类**: CATExtIEdit | **模块**: CAAMechanicalCommands | **方法数**: 1

## 依赖

- `CATExtIEdit.h`

## 虚方法

### Activate

```cpp
virtual CATCommand * Activate(CATPathElement * iPath) ;
```

Activate -------- Creates a state command to modify a feature whose the type is CAAUdfLoft Caution: This interface is implemented on a late type, so to retrieve the object to modify, it is not this, but use the iPath argument.

| 参数 | 类型 |
|------|------|
| iPath | `CATPathElement *` |


---

**源文件**: `CAAMechanicalCommands.edu/CAAMcaUdfEdit.m/LocalInterfaces/CAAEMcaEditUdfLoft.h`
