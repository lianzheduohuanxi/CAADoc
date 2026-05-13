---
title: "CAAMcaUdfLoftEditCreateCmd"
type: "LocalClass"
module: "CAAMechanicalCommands"
base: "CATPrtPanelStateCmd"
method_count: 0
source_file: "CAAMechanicalCommands.edu/CAAMcaUdfEdit.m/LocalInterfaces/CAAMcaUdfLoftEditCreateCmd.h"
---

# CAAMcaUdfLoftEditCreateCmd

> This command enables to edit and create an user feature which comes from the CAAUserFeatureSample user feature reference with the CAAUdfLoft type. This type of user feature has two inputs: two points. The end user selects a point feature and the name of the feature is displayed in a dialog box. To help the end user, the current point to select is indicated by the highlight of the linked editor. It can also pre-visualize the result in the 3D viewer. This use case illustrates: how to use the CATPrtPanelStateCmd class how to instantiate a user feature in an interactive command How to launch ? Edit mode: In the InstallRootDirectory/CAAMechanicalCommands.edu/InputData you find the CAAUdfModelWithTypeInst.CATPart document which contains one instance of the CAAUserFeatureSample user feature reference with the CAAUdfLoft type in Cnext, open this file and double click on the CAAUserFeatureSampleToEdit feature: the current command is launched Create mode: Select the Generative Shape Design workbench in the Start menu In the toolbar, User Feature Creation, click on the first icon: the current command is launched. (see CAAMcaUdfAddin.m/LocalInterfaces/CAAMcaUdfAdn.h) where InstallRootDirectory is the directory where the CAA CD-ROM is installed.

**基类**: CATPrtPanelStateCmd | **模块**: CAAMechanicalCommands | **方法数**: 0

## 依赖

- `CATPrtPanelStateCmd.h`

---

**源文件**: `CAAMechanicalCommands.edu/CAAMcaUdfEdit.m/LocalInterfaces/CAAMcaUdfLoftEditCreateCmd.h`
