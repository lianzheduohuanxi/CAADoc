---
title: "Creating Levels of Details"
category: "use-case case"
module: "CAAVisUseCases"
tags: "["CAAVisBaseView", "CAAVisBaseDocument", "CAAVisBasics", "CAAVisBaseDefaultDocument", "CAAVisBaseApplication", "CATIA", "CAAVisBase", "CAAVisualization"]"
source_file: "Doc/online/CAAVisUseCases/CAAVisSampleLOD.htm"
converted: "2026-05-11T17:31:52.141771"
---
# 3D PLM Enterprise Architecture

|
## 3D Visualization

|
### Creating Levels of Details

_Enabling for multiple tessellations of the same object_
---|---|---
Use Case

* * *
### Abstract

This article shows how to create levels of details.

  * **What Will You Learn in this Use Case**
  * **The CAAVisBasics Use Case**
    * What Does CAAVisBasics Do
    * How to Launch CAAVisBasics
    * Where to Find the CAAVisBasics Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to show how to create levels of details, that is several representations of the same object that are each displayed in turn with respect to the modifications brought to the viewpoint and display characteristics.

[Top]
### The CAAVisBasics Use Case

CAAVisBasics is a set of use cases of the CAAVisualization.edu framework that illustrates CATIA Vizualization framework capabilities.

[Top]
#### What Does CAAVisBasics Do

CAAVisBasics is a set of use cases of the CAAVisualization.edu framework that illustrates CATIA Vizualization framework capabilities.
CAAVisBasics includes a MDI interactive application that displays viewers in its document windows. One of these viewers is displayed when the application is launched and contains the representation of a torus. This article focuses on how to create levels of details for this torus, that is several tessellations, each corresponding to a given sag value, in order to the render to select the most appropriate one depending on the viewpoint characteristics and on the object size.

The torus is displayed in a 3D navigation viewer as soon as the application is launched. It is displayed brighter blue with a representation that is computed with a sag of 1/8. When zooming in, the viewpoint characteristics change, and three other representations are successively displayed: a green one with a sag of 1/6, a blue one with a sag of 1/4, and a red one with a sag of 1/2.

![](images/CAAVisSampleTorusLOD1.jpg)

![](images/CAAVisSampleTorusLOD2.jpg)

![](images/CAAVisSampleTorusLOD3.jpg)

![](images/CAAVisSampleTorusLOD4.jpg)

[Top]
#### How to Launch CAAVisBasics

To launch CAAVisBasics, you will need to set up the build time environment, then compile CAAVisBasics along with its prerequisites, set up the run time environment, and then execute the use case [1].

The torus is displayed in a 3D navigation viewer as soon as the application is launched. Zoom in and out to show the different levels of details and their associated colors.

[Top]
#### Where to Find the CAAVisBasics Code?

The torus is displayed in a 3D navigation viewer as soon as the application is launched. Zoom in and out to show the different levels of details and their associated colors.
The CAAVisBasics use case is made of several classes located in the CAAVisBasics.m module of the CAAVisualization.edu framework:

Windows | `InstallRootDirectory/CAAVisualization.edu/CAAVisBasics.m/`

The CAAVisBasics use case is made of several classes located in the CAAVisBasics.m module of the CAAVisualization.edu framework:
Windows | `InstallRootDirectory/CAAVisualization.edu/CAAVisBasics.m/`
Unix | `InstallRootDirectory/CAAVisualization.edu/CAAVisBasics.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

This use case deals with the following classes:

_CAAVisBaseApplication_ | Class for the interactive application that hosts the viewer

This use case deals with the following classes:
_CAAVisBaseApplication_ | Class for the interactive application that hosts the viewer
_CAAVisBaseDocument_ | Class for the document base class
_CAAVisBaseDefaultDocument_ | Class for the document that creates a representation and four level of details for a torus model
_CAAVisBaseView_ | Class for the document window containing a viewer to display the document

[Top]
### Step-by-Step

To create levels of details, there are three main steps:
# | Step | Where
---|---|---
To create levels of details, there are three main steps:
1 | Create a _CAT3DLodRep_ | `CreateModel` method of _CAAVisBaseDefaultDocument_
2 | Loop for each sag value onto the _CAT3DFaceGP_ creation | `CreateModel` method of _CAAVisBaseDefaultDocument_
3 | Create the bounding sphere for each level of details | `AddLOD` method of _CAAVisBaseDefaultDocument_

The torus is displayed when the CAAVisBase application is launched. The torus levels of details creation and display is performed in the _CAAVisBaseDefaultDocument_ constructor that creates a _CAT3DLodRep_ instance and that loops on calling the `CreateRep` method that creates a _CAT3DFaceGP_ instance with the passed sag, and that adds it to the _CAT3DLodRep_ instance. The representation is displayed thanks to calling the `AddRepToViewer` method. Only the constructor and the part of `CreateRep` that deals with the _CAT3DLodRep_ management are described below. The remaining parts, namely the torus tessellation and the creation of _CAT3DLodRep_ instance are already dealt with in [2].

[Top]
#### Creating a CAT3DLodRep

The _CAAVisBaseDefaultDocument_ constructor creates the representation bag to attach to the viewer, creates a _CAT3DLodRep_ instance for the torus, calls `CreateRep` as many time as there are sag values to the corresponding torus representations, adds the resulting 3D Lod representation to the representation bag, and calls `AddRepToViewer` for display.

    void CAAVisBaseDefaultDocument::CreateModel(#)

    {
The _CAAVisBaseDefaultDocument_ constructor creates the representation bag to attach to the viewer, creates a _CAT3DLodRep_ instance for the torus, calls `CreateRep` as many time as there are sag values to the corresponding torus representations, adds the resulting 3D Lod representation to the representation bag, and calls `AddRepToViewer` for display.
void CAAVisBaseDefaultDocument::CreateModel(#)
      _pRootContainer  = new CAT3DBagRep;
      _pTorusLodRep = new CAT3DLodRep(#);
      float sag = 0.125f;

      ... // Loop on the torus tessellation
      //Adding of the CAT3DLodRep to the CAT3DBagRep
_pRootContainer  = new CAT3DBagRep;
_pTorusLodRep = new CAT3DLodRep(#);
float sag = 0.125f;
      _pRootContainer->AddChild(*_pTorusLodRep);

      AddRepToViewer(#);

    }

---

This 3D representation to accommodate the different tessellations of the torus is a _CAT3DLodRep_ instance. This representation is dedicated to contain several representations of the same object, each being associated with the sag value used to create it.

[Top]
#### Looping for Each Sag Value onto the CAT3DFaceGP Creation

    ...
      int color[3] = {255, 255, 255}; //White color

      int colors[] = {200, 200, 255, //bright blue
                      200, 0,   0,   //red
                      0,   0,   255, //blue
                      0,   200, 0};  //green
      for(int i=NLOD; i>0; i--)

      {
200, 0,   0,   //red
0,   0,   255, //blue
0,   200, 0};  //green
for(int i=NLOD; i>0; i--)
```vbscript
        sag = float(MAX_SAG)/(float)(2*i);
```

        color[0] = colors[3*(i%NLOD)];
        color[1] = colors[3*(i%NLOD)+1];
        color[2] = colors[3*(i%NLOD)+2];
        AddLOD(sag, color);

      }
    ...

---

The sag values are computed and passed to the `AddLOD` method as well as the associated color.

[Top]
#### Adding the CAT3DCustomRep to the CAT3DLodRep

The `AddLOD` method is the same as the one explained in [2], except that it has the sag as argument, and computes the theta and phi angles from the sag value. It also update the 3D Lod representation with the created 3D custom representation.

    void CAAVisBaseDefaultDocument::AddLOD(float sag, int *iColor)

    {
The `AddLOD` method is the same as the one explained in [2], except that it has the sag as argument, and computes the theta and phi angles from the sag value. It also update the 3D Lod representation with the created 3D custom representation.
void CAAVisBaseDefaultDocument::AddLOD(float sag, int *iColor)
      int R = TORUS_RADIUS;
      int r = CIRCLE_RADIUS;

      float theta = sqrt(sag/r);
      float phi   = sqrt(sag/R);

      int nVertexPerCircle = floor(2*PI/theta)+1;
      int nCircles         = floor(2*PI/phi)+1;

      theta = 2*PI/nVertexPerCircle;
      phi   = 2*PI/nCircles;

      ... // Refer to [2] for the 3D graphic primitive and 3D custom representation creation

theta = 2*PI/nVertexPerCircle;
phi   = 2*PI/nCircles;
      _pTorusLodRep->AddLod(_pTorusCustomRep, sag);

    }

---

The angles theta and phi are computed using the sag value and the rotating circle radius and the torus radius respectively. **sag/R to be explained**. The number of vertices per circle and the number of circles are deduced from the angle values. Then, these angle values are adjusted to partition the circles. The 3D graphic primitive and the 3D custom representation are created  as described in [2]. `_pTorusCustomRep` is the pointer to the 3D custom representation. It is added to the 3D Lod representation along with the associated sag value

[Top]

* * *
### In Short

This use case shows the objects involved when creating several representations for a given object and to bind them in a 3D Lod representation. This enables the object to provide representations that match the different accuracies required when the viewpoint and display characteristics change.

[Top]

* * *
### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] | [Tessallating a Torus](CAAVisSampleCAT3DFaceGP.md)
[Top]

* * *
### History

Version: **1** [Feb 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
