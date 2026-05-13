---
title: "CAATpiAnnotSetGlobalCopyCmd"
type: "LocalClass"
module: "CAATPSInterfaces"
base: "CATStateCommand"
method_count: 1
source_file: "CAATPSInterfaces.edu/CAATpiAnnotationSetGlobalCopy.m/LocalInterfaces/CAATpiAnnotSetGlobalCopyCmd.h"
---

# CAATpiAnnotSetGlobalCopyCmd

> Interactive command Command to select a geometry and then create a 3D annotation text linked on selection. Illustrates: Using TPS (Technological Product Specifications) interfaces to create a 3D Text Annotation. The main API used here is CATITPSFactoryAdvanced. Usage: Build the fw containing that command and create run time view. Start CATIA V5 Menu Start + Mechanical Design + Functional Tolerancing & Annotations Menu : View + Toolbar + CAA Samples to make the toolbar appear. "Create Text" command can be launched from the toolbar. Notice that the toolbar CAA Samples is also available in the following workbenches : Mechanical Design + Product Fonctionnal Tolerancing & Annotation DPM Powertrain + Process Tolerancing & Annotation

**基类**: CATStateCommand | **模块**: CAATPSInterfaces | **方法数**: 1

## 依赖

- `CATStateCommand.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```


---

**源文件**: `CAATPSInterfaces.edu/CAATpiAnnotationSetGlobalCopy.m/LocalInterfaces/CAATpiAnnotSetGlobalCopyCmd.h`
