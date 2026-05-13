---
title: "CAAEPstINFVisuWire"
type: "LocalClass"
module: "CAAProductStructure"
base: "CATExtIVisu"
method_count: 2
source_file: "CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFVisuWire.h"
---

# CAAEPstINFVisuWire

> Data extension of the CAAPstINFWire component, implementing the CATI3DGeoVisu interface to enable the visualization of a line. This class derives from the CATExtIVisu adapter. Illustrates programming the visualization of an object by implementing the CATI3DGeoVisu interface of the Visualization framework. Inheritance: CATExtIVisu (Visualization) CATBaseUnknown (System Framework)

**基类**: CATExtIVisu | **模块**: CAAProductStructure | **方法数**: 2

## 依赖

- `CATExtIVisu.h`

## 虚方法

### SetPointGraphicAttribute

```cpp
virtual void SetPointGraphicAttribute(CATRep * iRep, CATVisPropertyType iPropertyType, CATVisPropertiesValues & iPropertyValue) ;
```

Modify the point graphic properties

| 参数 | 类型 |
|------|------|
| iRep | `CATRep *` |
| iPropertyType | `CATVisPropertyType` |
| iPropertyValue | `CATVisPropertiesValues &` |


### SetLineGraphicAttribute

```cpp
virtual void SetLineGraphicAttribute(CATRep * iRep, CATVisPropertyType iPropertyType, CATVisPropertiesValues & iPropertyValue) ;
```

Modify the lineic graphic properties

| 参数 | 类型 |
|------|------|
| iRep | `CATRep *` |
| iPropertyType | `CATVisPropertyType` |
| iPropertyValue | `CATVisPropertiesValues &` |


---

**源文件**: `CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFVisuWire.h`
