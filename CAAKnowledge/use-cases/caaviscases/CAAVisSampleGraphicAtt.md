---
```vbscript
title: "Using Graphic Attributes"
category: "use case"
module: "CAAVisUseCases"
tags: ["CAAVisBaseView", "CAAVisRepWindow", "CAAVisualization", "CAAVisRep", "CAAVisRepApplication"]
source_file: "Doc/online/CAAVisUseCases/CAAVisSampleGraphicAtt.htm"
converted: "2026-05-11T17:31:52.107319"
```

---
# 3D PLM Enterprise Architecture

|
## 3D Visualization

|
### Using Graphic Attributes

_Setting colors, linetypes, and thicknesses to representations, and understanding graphic attribute inheritance_
---|---|---
Use Case

* * *
### Abstract

This article discusses the CAAVisRep use case. This use case explains how to use graphic attributes.

  * **What You Will Learn With This Use Case**
  * **The CAAVisRep Use Case**
    * What Does CAAVisRep Do
    * How to Launch CAAVisRep
    * Where to Find the CAAVisRep Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to show how to set graphic attributes to graphic representations, how to manage graphic attribute inheritance, and describes some of these attributes.

[Top]
### The CAAVisRep Use Case

CAAVisRep is a use case of the CAAVisualization.edu framework that illustrates Vizualization framework capabilities.

[Top]
#### What Does CAAVisRep Do

CAAVisRep is a use case of the CAAVisualization.edu framework that illustrates Vizualization framework capabilities.
CAAVisRep creates two line representations, and two cuboid representations, and sets graphic attributes to these representations to display them as shown in Fig. 1.

_Fig. 1: The CAAVisRep Representations_ ![](images/CAAVisSampleGraphicAtt1.jpg)

---

[Top]
#### How to Launch the CAAVisRep

To launch CAAVisRep, you will need to set up the build time environment, then compile CAAVisRep along with its prerequisites, set up the run time environment, and then execute the use case [1].

[Top]
#### Where to Find the CAAVisRep Code

To launch CAAVisRep, you will need to set up the build time environment, then compile CAAVisRep along with its prerequisites, set up the run time environment, and then execute the use case [1].
The CAAVisRep use case is made of two classes named _CAAVisRepApplication_ and _CAAVisRepWindow_ located in the CAAVisRep code is located in the CAAVisRep.m use case module of the CAAVisualization.edu framework:

Windows | `InstallRootDirectory\CAAVisualization.edu\CAAVisRep.m`

The CAAVisRep use case is made of two classes named _CAAVisRepApplication_ and _CAAVisRepWindow_ located in the CAAVisRep code is located in the CAAVisRep.m use case module of the CAAVisualization.edu framework:
Windows | `InstallRootDirectory\CAAVisualization.edu\CAAVisRep.m`
Unix | `InstallRootDirectory/CAAVisualization.edu/CAAVisRep.m`

where `InstallRootDirectory` is the root directory of your CAA V5 installation.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the root directory of your CAA V5 installation.
To manage graphic attributes, there are four main steps:

  1. Creating a 3D Navigation Viewer Instance
  2. Creating a 3D Representation Bag
  3. Creating a Green Dotted Line with Two Yellow Points at Its Ends
  4. Creating a Magenta Solid Line with Two Magenta Points at Its Ends
  5. Creating a Red Cube without Top Face and with Faces Lighted on One Side
  6. Creating a White Cube with Faces Lighted on Their Two Sides
  7. Displaying the Representation in the Viewer

[Top]
#### Creating a 3D Navigation Viewer Instance

The 3D navigation viewer is an instance of the _CATNavigation3DViewer_ class. It is created in the `CreateViewer` method of the _CAAVisBaseView_ class that is called when the application is launched.

The 3D navigation viewer is an instance of the _CATNavigation3DViewer_ class. It is created in the `CreateViewer` method of the _CAAVisBaseView_ class that is called when the application is launched.
    void CAAVisRepWindow::CreateViewer()

    {
The 3D navigation viewer is an instance of the _CATNavigation3DViewer_ class. It is created in the `CreateViewer` method of the _CAAVisBaseView_ class that is called when the application is launched.
void CAAVisRepWindow::CreateViewer()
```vbscript
      _p3DViewer = new CATNavigation3DViewer(this,

```

                                             "Navigation3DId",
void CAAVisRepWindow::CreateViewer()
_p3DViewer = new CATNavigation3DViewer(this,
                                             CATDlgFraNoTitle,
                                             800, 450);
      _p3DViewer->SetBackgroundColor(0.2f,0.2f,0.6f);
      Attach4Sides( _p3DViewer);

    }

---

The `_pViewer` pointer to the 3D navigation viewer is kept as a data member of the _CAAVisBaseView_ class. Its parameter are:

`this` | The viewer parent in the dialog containment tree structure and in the command tree structure [a]
---|---
`Navigation3DId` | The viewer identifier
`CATDlgFraNoTitle` | The viewer has no title [b]
`850, 450` | The viewer width and height expressed in pixels

The `SetBackgroundColor` method changes the viewer background color. The `Attach4Sides` method attaches the four sides of the viewer to those of the window. This makes the viewer occupy the whole window space.

[Top]
#### Creating a 3D Representation Bag

    void CAAVisRepWindow::CreateModelRepresentation()
    {
      _pTheModelToDisplay = new CAT3DBagRep() ;
    ...

---

This is done at the beginning of the `CreateModelRepresentation` method of _CAAVisRepWindow_.

[Top]
#### Creating a Green Dotted Line with Two Yellow Points at Its Ends

    ...
      CAT3DCustomRep * pLineOnXAxis = NULL ;

CAT3DCustomRep * pLineOnXAxis = NULL ;
      CATMathPoint PositionXPoint1(20.f,0.f,0.f ) ;
      CATMathPoint PositionXPoint2(200.f,0.f,0.f ) ;

      int NONE = 0 ;
```vbscript
      pLineOnXAxis = CreateLineEndedByTwoPoints(PositionXPoint1,PositionXPoint2,NONE);

      if ( NULL != pLineOnXAxis )

```

      {
int NONE = 0 ;
pLineOnXAxis = CreateLineEndedByTwoPoints(PositionXPoint1,PositionXPoint2,NONE);
```vbscript
if ( NULL != pLineOnXAxis )
```

        _pTheModelToDisplay->**AddChild**(*pLineOnXAxis);

      }
    ...

---

The first line is carried by the X axis. It begins at the abscissa 20 and ends at the abscissa 200. The `CreateLineEndedByTwoPoints` method of _CAAVisRepWindow_ creates the line and sets its graphic attributes. If the custom representation is successfully created, it is added to the representation bag. `CreateLineEndedByTwoPoints` is as follows:

The first line is carried by the X axis. It begins at the abscissa 20 and ends at the abscissa 200. The `CreateLineEndedByTwoPoints` method of _CAAVisRepWindow_ creates the line and sets its graphic attributes. If the custom representation is successfully created, it is added to the representation bag. `CreateLineEndedByTwoPoints` is as follows:
    CAT3DCustomRep * CAAVisRepWindow::CreateLineEndedByTwoPoints(const CATMathPoint &iStartPoint,
                                                                 const CATMathPoint &iEndPoint,
                                                                 int                 iEdgeType)

    {
CAT3DCustomRep * CAAVisRepWindow::CreateLineEndedByTwoPoints(const CATMathPoint &iStartPoint,
const CATMathPoint &iEndPoint,
int                 iEdgeType)
      CAT3DCustomRep * pTheRepToReturn = NULL;
```vbscript
      pTheRepToReturn = new **CAT3DCustomRep**();

```

      // Creates a green dotted line
CAT3DCustomRep * pTheRepToReturn = NULL;
pTheRepToReturn = new **CAT3DCustomRep**();
      float coord[6] ;
      coord[0] = (float) iStartPoint.GetX();
      coord[1] = (float) iStartPoint.GetY();
      coord[2] = (float) iStartPoint.GetZ();
      coord[3] = (float) iEndPoint.GetX();
      coord[4] = (float) iEndPoint.GetY();
      coord[5] = (float) iEndPoint.GetZ();

      CAT3DLineGP * pLineGP = new **CAT3DLineGP**(coord, 2);

      **CATGraphicAttributeSet** LineGA;
coord[4] = (float) iEndPoint.GetY();
coord[5] = (float) iEndPoint.GetZ();
CAT3DLineGP * pLineGP = new **CAT3DLineGP**(coord, 2);
      LineGA.**SetColor**(GREEN);
      LineGA.**SetThickness**(4);  // Thickness ranges from 1 to 16
      LineGA.**SetLineType**(2);   // Line type ranges from 1 to
      LineGA.**SetType**(iEdgeType);

      pTheRepToReturn->**AddGP**(pLineGP,LineGA);

      // Creates two yellow points
LineGA.**SetType**(iEdgeType);
pTheRepToReturn->**AddGP**(pLineGP,LineGA);
      CAT3DMarkerGP * pPointGP = new **CAT3DMarkerGP**(coord, 2, CROSS);

      **CATGraphicAttributeSet** PointGA;
pTheRepToReturn->**AddGP**(pLineGP,LineGA);
CAT3DMarkerGP * pPointGP = new **CAT3DMarkerGP**(coord, 2, CROSS);
      PointGA.**SetColor**(YELLOW);

      pTheRepToReturn->**AddGP**(pPointGP,PointGA);

      // Computes the BoundingSphere and sets it to the representation
PointGA.**SetColor**(YELLOW);
pTheRepToReturn->**AddGP**(pPointGP,PointGA);
      CATMathPoint Center =  iStartPoint + ((iEndPoint-iStartPoint) / 2.f);
      float Radius = (float) iStartPoint.DistanceTo(Center);

      **CAT3DBoundingSphere** BoundingSphere(Center,Radius);
CATMathPoint Center =  iStartPoint + ((iEndPoint-iStartPoint) / 2.f);
float Radius = (float) iStartPoint.DistanceTo(Center);
      pTheRepToReturn->**SetBoundingElement**(BoundingSphere) ;

      return (pTheRepToReturn);

    }

---

The line and points are created as graphic primitives (GPs) added to a _CAT3DCustomRep_ with their respective graphic attributes using the `AddGP` method. The line GP is a _CAT3DLineGP_ instance created using the points passed as parameters. Its attribute set is an instance of the _CATGraphicAttributeSet_ class to which the following attribute values are set:

  * `SetColor` sets its color to green
  * `SetThickness` sets the line thickness to 4. The thickness ranges from 1 to 16, 1 being the thinnest and 16 the thickest
  * `SetLineType` sets the line type to 2. The line type ranges from 1 to 63. 2 means dotted
  * `SetType` sets its graphic type to 0. This means that the line is always seen, even if other representations are displayed in front of it.

The two points are created using a single instance of the _CAT3DMarkerGP_ class, and their color is set as yellow. Then, the bounding element associated with the custom representation is computed as a _CAT3DBoundingSphere_ instance, and set to the custom representation using the `SetBoundingElement` method.

[Top]
#### Creating a Magenta Solid Line with Two Magenta Points at Its Ends

The second line and its endpoints are also created using the `CreateLineEndedByTwoPoints` method, but uses the graphic attribute inheritance to get the attributes set to the GPs, and reset other graphic attributes.

    ...
The second line and its endpoints are also created using the `CreateLineEndedByTwoPoints` method, but uses the graphic attribute inheritance to get the attributes set to the GPs, and reset other graphic attributes.
      CAT3DCustomRep * pLineOnYAxis = NULL ;

      CATMathPoint PositionYPoint1(0.f,20.f,0.f );
      CATMathPoint PositionYPoint2(0.f,200.f,0.f ) ;

      int EDGE = 1 ;
```vbscript
      pLineOnYAxis = CreateLineEndedByTwoPoints(PositionYPoint1,PositionYPoint2,EDGE);

      if ( NULL != pLineOnYAxis )

```

      {
int EDGE = 1 ;
pLineOnYAxis = CreateLineEndedByTwoPoints(PositionYPoint1,PositionYPoint2,EDGE);
```vbscript
if ( NULL != pLineOnYAxis )
```

        pLineOnYAxis->**SetInheritanceMode**(LINEWIDTH_INHERITANCE | COLOR_INHERITANCE);
        pLineOnYAxis->**SetThickness**(1);
        pLineOnYAxis->**SetColor**(MAGENTA);

        _pTheModelToDisplay->**AddChild**(*pLineOnYAxis);

       }
    ...

---

The second line is carried by the Y axis. Once the custom representation is created, its graphic attributes are those of the GPs, that is, the line color is green, its thikness is set to 2, its line type is dotted, its type set to 1 makes it hidden by representations in front of it, and the endpoints are yellow, but keep the default type set to 0. The graphic attribute set associated with the custom representation is now used to reset some of the GP graphic attributes. The `SetInheritanceMode` method enables the GPs that make up the custom representation to inherit graphic attribute values set to the representation itself, namely the line thickness (`LINEWIDTH_INHERITANCE` ) and the color (`COLOR_INHERITANCE`). The line thickness is reset to 1, that is to solid, and the color is reset to magenta. These graphic attribute values are reset for all the GPs: the line GP and the marker GP are both magenta. (The line thickness makes no sense for markers.) If the custom representation is successfully created, it is added to the representation bag.

[Top]
#### Creating a Red Cube without Top Face and with Faces Lighted on One Side

    ...
      CAT3DCustomRep * pRedCube = NULL ;
      CATMathPoint RedCubePosition(50.f,50.f,0.f);
      int VOLUME = 3 ;
```vbscript
      pRedCube = CreateOpenCube(RedCubePosition,VOLUME);

      if ( NULL != pRedCube )

```

      {
int VOLUME = 3 ;
pRedCube = CreateOpenCube(RedCubePosition,VOLUME);
```vbscript
if ( NULL != pRedCube )
```

        pRedCube->**SetInheritanceMode**(COLOR_INHERITANCE);
        pRedCube->**SetColor**(RED);

        _pTheModelToDisplay->**AddChild**(*pRedCube);

      }
    ...

---

The first cube has its corner located at `RedCubePoint`. The `CreateOpenCube` method of _CAAVisRepWindow_ creates the cube and sets its graphic attributes. If the custom representation is successfully created, it is added to the representation bag. `CreateOpenCube` is as follows:

The first cube has its corner located at `RedCubePoint`. The `CreateOpenCube` method of _CAAVisRepWindow_ creates the cube and sets its graphic attributes. If the custom representation is successfully created, it is added to the representation bag. `CreateOpenCube` is as follows:
    CAT3DCustomRep * CAAVisRepWindow::CreateOpenCube(const CATMathPoint &iStartPoint,
                                                     int iTypeFace)

    {
CAT3DCustomRep * CAAVisRepWindow::CreateOpenCube(const CATMathPoint &iStartPoint,
int iTypeFace)
      CAT3DCustomRep * pTheRepToReturn = NULL ;

      ... // Creates Point1 to Point8 from iStartPoint
      // Creates a cube with 6 faces
int iTypeFace)
CAT3DCustomRep * pTheRepToReturn = NULL ;
      pTheRepToReturn = new CAT3DCustomRep();
      CAT3DPlanarFaceGP * pPlanGP = NULL ;

        // Top face is not shown
      **CATGraphicAttributeSet** FaceNoShowGA;
pTheRepToReturn = new CAT3DCustomRep();
CAT3DPlanarFaceGP * pPlanGP = NULL ;
      FaceNoShowGA.**SetShowMode**(1);
      pPlanGP = CreateFaceGP(Point5,Point6,Point8,Point7);
      pTheRepToReturn->**AddGP**(pPlanGP,**FaceNoShowGA**);

        // Bottom face
        // -----------
      **CATGraphicAttributeSet** FaceShowGA;
pTheRepToReturn->**AddGP**(pPlanGP,**FaceNoShowGA**);
      FaceShowGA.**SetType**(iTypeFace);
      pPlanGP = CreateFaceGP(Point4,Point3,Point1,Point2);
      pTheRepToReturn->AddGP(pPlanGP,**FaceShowGA**);

      ... // and so on for the other faces

      ... // Computes and sets the bounding element

      return pTheRepToReturn;
    }

---

As with the lines and points, the cube is created as a _CAT3DCustomRep_ instance. It is made up of eight instances of _CAT3DPlanarFaceGP_ created using the `CreateFaceGP` method of _CAAVisRepWindow_ that are associated with a graphic attribute set when added to the custom representation. The top face is set as invisible using the `SetShowMode` method to which 1 is passed. (0 is the default and means shown.) The other faces share the same graphic attribute set and are considered as part of a volume, since 3 is passed to `SetType`. Each of these faces is displayed only if it is seen from the outside of the cube.

[Top]
#### Creating a White Cube with Faces Lighted on Their Two Sides

    ...
      CATMathPoint WhiteCubePosition(50.f,150.f,0.f );
CATMathPoint WhiteCubePosition(50.f,150.f,0.f );
      CAT3DCustomRep * pWhiteCube = NULL ;

      int SKIN = 2 ;
```vbscript
      pWhiteCube = CreateOpenCube(WhiteCubePosition,SKIN);

      if ( NULL != pWhiteCube )

```

      {
int SKIN = 2 ;
pWhiteCube = CreateOpenCube(WhiteCubePosition,SKIN);
```vbscript
if ( NULL != pWhiteCube )
```

        _pTheModelToDisplay->AddChild(*pWhiteCube);

      }
    }

---

The second cube is created with the default color, that is, white, and with its type set to 2, that is the faces are lighted on both sides.

[Top]
#### Displaying the Representation in the Viewer

The `AddRepToViewer` method displays the created representation.

The `AddRepToViewer` method displays the created representation.
    void CAAVisRepWindow::VisualizeModel()

    {
The `AddRepToViewer` method displays the created representation.
void CAAVisRepWindow::VisualizeModel()
```vbscript
      if ( (NULL != _p3DViewer) && ( NULL != _pTheModelToDisplay) )

```

      {
void CAAVisRepWindow::VisualizeModel()
if ( (NULL != _p3DViewer) && ( NULL != _pTheModelToDisplay) )
        _p3DViewer->**AddRep**((CAT3DRep*)_pTheModelToDisplay);
        _p3DViewer->**Draw**();

      }
    }

---

The 3D representation bag created to contain all the created representations is added to the 3D navigation viewer using the `AddRep` method, and the viewer is drawn using the `Draw` method. `AddRep` is called one for all, but `Draw` must be called whenever the representation bag is modified.

[Top]

* * *
### In Short

This use case shows how to create and manage graphic attribute on graphic representation. It also has shown how to make graphic representations inherit from the graphic attributes set to the custom representation that holds them.

[Top]

* * *
### References

[1] | [Building and Launching CAA V5 Samples](../CAADocUseCases/CAADocRunSample.md)
---|---
[Top]

* * *
### History

Version: **1** [Feb 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
