---
title: "CAATpiRetrieveAnnotationCmd"
type: "LocalClass"
module: "CAATPSInterfaces"
base: "CATStateCommand"
method_count: 1
source_file: "CAATPSInterfaces.edu/CAATpiRetrieveAnnotation.m/LocalInterfaces/CAATpiRetrieveAnnotationCmd.h"
---

# CAATpiRetrieveAnnotationCmd

> Interactive command Command to select a geometry and then retrieve and highlight all 3D annotations which are applied on selected geometry. Illustrates: Using TPS (Technological Product Specifications) interfaces to retrieve annotations and tolerances linked to a geometry. The main APIs used here are CATITPSRetrieveServices and CATIBuildPath. Usage: Build the fw containing that command and create run time view. Start CATIA V5 Menu Start + Mechanical Design + Functional Tolerancing & Annotation Menu : View + Toolbar + CAA Samples to make the toolbar appear. "Retrieve Annotation" command can be launched from the toolbar. Notice that the toolbar CAA Samples is also available in the following workbenches : Mechanical Design + Product Fonctionnal Tolerancing & Annotations DPM Powertrain + Process Tolerancing & Annotations

**基类**: CATStateCommand | **模块**: CAATPSInterfaces | **方法数**: 1

## 依赖

- `CATStateCommand.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```


---

**源文件**: `CAATPSInterfaces.edu/CAATpiRetrieveAnnotation.m/LocalInterfaces/CAATpiRetrieveAnnotationCmd.h`
