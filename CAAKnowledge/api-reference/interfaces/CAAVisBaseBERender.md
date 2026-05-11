---
title: "CAAVisBaseBERender"
type: "interface"
module: "CAAVisualization"
base: "CATRender"
method_count: 7
visibility: "local"
verified: true
---

# CAAVisBaseBERender

**基类**: CATRender  
**模块**: CAAVisualization  
**可见性**: local  
**方法数**: 7

> ===========================================================================

## 方法列表

### Draw
```cpp
void Draw(list<CATViewpoint> &iViewpoints, const int, const float);
```

### DrawRepresentation
```cpp
void DrawRepresentation(CATRep &iRep);
```

### EndDraw
```cpp
void EndDraw(CATViewpoint &iViewpoint);
```

### Draw3DFace
```cpp
void Draw3DFace(CAT3DFaceGP &iGP);
```

### Draw3DPlanarFace
```cpp
void Draw3DPlanarFace(CAT3DPlanarFaceGP &iGP);
```

### PushMatrix
```cpp
CATRender * PushMatrix(CAT4x4Matrix &iMatrix);
```

### PopMatrix
```cpp
void PopMatrix(CATRender *ioRender);
```

## 依赖

- `CATRender.h`

