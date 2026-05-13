---
title: "CAATpiAccessGeometryCmd"
type: "LocalClass"
module: "CAATPSInterfaces"
base: "CATStateCommand"
method_count: 2
source_file: "CAATPSInterfaces.edu/CAATpiAccessGeometry.m/LocalInterfaces/CAATpiAccessGeometryCmd.h"
---

# CAATpiAccessGeometryCmd

> Interactive command Command to select a 3D annotation and then retrieve and highlight the geometry on which annotation is applied. The topological composition (faces and edges count) of the geometry is displayed in a panel. A cloud of point is displayed on the faces. An arrow that indicate the outside material side is also displayed. Illustrates: Using TPS (Technological Product Specifications) and Mechanical Modeler interfaces to retrieve the geometry of a 3D Annotation. The main APIs used here  are CATITPS, CATITTRS, CATIRGE and CATIRGETopology. Usage: Build the fw containing that command and create run time view. Start CATIA V5 Menu Start + Mechanical Design + Functional Tolerancing & Annotation Menu : View + Toolbar + CAA Samples to make the toolbar appear. "Access Geometry" command can be launched from the toolbar. Notice that the toolbar CAA Samples is also available in the following workbenches : Mechanical Design + Product Fonctionnal Tolerancing & Annotations DPM Powertrain + Process Tolerancing & Annotations

**基类**: CATStateCommand | **模块**: CAATPSInterfaces | **方法数**: 2

## 依赖

- `CATStateCommand.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```


### Cancel

```cpp
virtual CATStatusChangeRC Cancel(CATCommand * ipCmd, CATNotification * ipNotif) ;
```

| 参数 | 类型 |
|------|------|
| ipCmd | `CATCommand *` |
| ipNotif | `CATNotification *` |


---

**源文件**: `CAATPSInterfaces.edu/CAATpiAccessGeometry.m/LocalInterfaces/CAATpiAccessGeometryCmd.h`
