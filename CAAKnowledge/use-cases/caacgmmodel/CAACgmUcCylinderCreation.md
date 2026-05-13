---
```vbscript
title: "Cylinder"
category: use-case case"
module: "CAACgmModel"
tags: ["CAAGMModelCylinderCreation", "CAAGMModelInterfaces"]
source_file: "Doc/online/CAACgmModel/CAACgmUcCylinderCreation.htmmd"
converted: "2026-05-11T17:33:48.190455"
```

---
# Creating a Cylinder

---
Use Case
## Abstract

A portion of a geometric cylinder can be created by specifying an axis, the start and end lengthes and the start and end angles.
    * API to be Used
    * Use Case Description
    * References
---
## APIs to be Used

To create a cylinder or a piece of a cylinder, use the CATGeoFactory::CreateCylinder method in the GeometricObjects framework.  As surface periodicity is not supported, it is recommended to specify angles so that:

To create a cylinder or a piece of a cylinder, use the CATGeoFactory::CreateCylinder method in the GeometricObjects framework.  As surface periodicity is not supported, it is recommended to specify angles so that:
    1. start angle < end angle
    2. end angle - start angle <= 2*Pi

but if angle values are too large, the cylinder is created around 2*Pi.

## Use Case Description

2. end angle - start angle <= 2*Pi
but if angle values are too large, the cylinder is created around 2*Pi.
The CAAGMModelCylinderCreation.m module in CAAGMModelInterfaces.edu illustrates how to create a cylinder. This use case creates the input data required for the cylinder creation. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).

With the code below:

    CATMathAxis  axis;
    CATMathDirection D1(1.,0.,0.);
    CATMathDirection D2(0.,1.,0.);
    CATMathDirection D3(0.,0.,1.);
    CATMathPoint  mathpoint(5.,15.,50.);
    CATCartesianPoint * pCartP = piGeomFactory->CreateCartesianPoint (5.,15.,50.);
    axis.Set(mathpoint,D1,D2,D3);

    double startLength = 0.0;
    double endLength = -20.0;
    double startAngle =-0.20*CAT2PI;  // -72 deg
    double endAngle = +0.30*CAT2PI;   // 108 deg

    double radius(25.);

    // ----------------------------------------------
    // 3 -Create a cylinder
    // ----------------------------------------------
    //
    cout << "Cylinder creation" << endl;
    CATCylinder * pCylinder =  piGeomFactory->CreateCylinder(axis,radius,
    	startLength, endLength, startAngle, endAngle);

---

CATCylinder * pCylinder =  piGeomFactory->CreateCylinder(axis,radius,
startLength, endLength, startAngle, endAngle);
you get this result:

Fig.1 Cylinder parameters ![Cylinder start and end angles](images/CGM_cylinder_0.png)

---
you get this result:
Fig.1 Cylinder parameters ![Cylinder start and end angles](images/CGM_cylinder_0.png)
Start angle: -72 deg
End angle: + 108 deg
Right-hand rule defines positive angles
First direction of the cylinder axis is the angle reference

##
## References

[1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)
## History

Version: **1** [Sept 2012] | Document created
---|---
