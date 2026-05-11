---
title: "CAAEPstINFVisuWire"
type: "interface"
module: "CAAProductStructure"
base: "CATExtIVisu"
method_count: 2
visibility: "local"
verified: true
---

# CAAEPstINFVisuWire

**基类**: CATExtIVisu  
**模块**: CAAProductStructure  
**可见性**: local  
**方法数**: 2

> Visualization Framework

## 方法列表

### SetPointGraphicAttribute
```cpp
void SetPointGraphicAttribute(CATRep * iRep, 
                                          CATVisPropertyType iPropertyType, 
                                          CATVisPropertiesValues & iPropertyValue);
```

### SetLineGraphicAttribute
```cpp
void SetLineGraphicAttribute(CATRep * iRep, 
                                          CATVisPropertyType iPropertyType, 
                                          CATVisPropertiesValues & iPropertyValue);
```

## 依赖

- `CATExtIVisu.h`

