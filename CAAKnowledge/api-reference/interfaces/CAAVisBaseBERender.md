---
title: "CAAVisBaseBERender"
type: "LocalClass"
module: "CAAVisualization"
base: "CATRender"
method_count: 9
source_file: "CAAVisualization.edu/CAAVisBasics.m/LocalInterfaces/CAAVisBaseBERender.h"
---

# CAAVisBaseBERender

> Bounding boxes render class. This object illustrates the way to do a render. It goes through the scene tree and calculates the bounding boxes for each rep. These bounding boxes are stored, and can be accessed thanks to a public method. The calculation of bounding boxes is the simpliest: while rendering a rep, we are looking for its maximum and minimum coordinates, which are the bounding box coordinates. Inheritance: CAAVisBERender CATRender(Visualization Framework) Main Method: Draw: parses the scene through the render. GetNumberOfBoxes: gets the number of boxes calculated into the scene. GetBoundingBox: Gets the bounding box of a rep, from its index.

**基类**: CATRender | **模块**: CAAVisualization | **方法数**: 9

## 依赖

- `CATRender.h`
- `list.h`

## 虚方法

### Draw

```cpp
virtual void Draw(list<CATViewpoint> &iViewpoints, const int, const float) ;
```

Overridden methods: Draws the scene through the render.

| 参数 | 类型 |
|------|------|
| &iViewpoints | `list<CATViewpoint>` |
| int | `const` |
| float | `const` |


### DrawRepresentation

```cpp
virtual void DrawRepresentation(CATRep &iRep) ;
```

Called each time we are begining a new rep.

| 参数 | 类型 |
|------|------|
| &iRep | `CATRep` |


### EndDraw

```cpp
virtual void EndDraw(CATViewpoint &iViewpoint) ;
```

| 参数 | 类型 |
|------|------|
| &iViewpoint | `CATViewpoint` |


### Draw3DFace

```cpp
virtual void Draw3DFace(CAT3DFaceGP &iGP) ;
```

Draws a 3D face through the render. Here we're going to look for maima and minima, and to compare them with the ones found for other faces of the rep.

| 参数 | 类型 |
|------|------|
| &iGP | `CAT3DFaceGP` |


### Draw3DPlanarFace

```cpp
virtual void Draw3DPlanarFace(CAT3DPlanarFaceGP &iGP) ;
```

| 参数 | 类型 |
|------|------|
| &iGP | `CAT3DPlanarFaceGP` |


### PushMatrix

```cpp
virtual CATRender * PushMatrix(CAT4x4Matrix &iMatrix) ;
```

Modifys the render so that it takes into account the fact that our local repair has changed. Called at the drawing of a CAT3DBagRep. Pushes the matrices in the order they come.

| 参数 | 类型 |
|------|------|
| &iMatrix | `CAT4x4Matrix` |


### PopMatrix

```cpp
virtual void PopMatrix(CATRender *ioRender) ;
```

Pops back the matrices stack so that we get back to the previous state.

| 参数 | 类型 |
|------|------|
| *ioRender | `CATRender` |


## 公共方法

### GetNumberOfBoxes

```cpp
int GetNumberOfBoxes() ;
```


### GetBox

```cpp
void GetBox(int iIndex, float *oBox) ;
```

| 参数 | 类型 |
|------|------|
| iIndex | `int` |
| *oBox | `float` |


---

**源文件**: `CAAVisualization.edu/CAAVisBasics.m/LocalInterfaces/CAAVisBaseBERender.h`
