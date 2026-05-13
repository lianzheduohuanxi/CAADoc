---
title: "Cone"
category: "use-case case"
module: "CAACgmModel"
tags: "["CAAGMModelConeCreation", "CAAGMModelInterfaces"]"
source_file: "Doc/online/CAACgmModel/CAACgmUcConeCreation.htm"
converted: "2026-05-11T17:33:48.181947"
---
# Creating a Frustum of a Right Circular Cone

    ---

    		Use Case

    ## Abstract

    		A right circular cone geometry can be created directly from the
    		geometry factory. The created cone cannot be a cylinder. When the value
    		of the cone angle gets close to 90 deg, the apex may exit the model
    		size. The surface can however be generated but a "Data Checker" message
    		can be issued. Oblique cones are not supported.

            * API to be Used

            * Use Case Description

            * References

    ---

    ## API to be Used

    To create a cone or a frustum of a circular cone, use the CATGeoFactory::CreateCone
    method in the GeometricObjects framework.

    ## Use Case Description

    The CAAGMModelConeCreation.m module in CAAGMModelInterfaces.edu
    illustrates how to create a cone. This use case creates the input data required
    for the cone creation. If you are not already
    familiar with geometric modeler use cases, go to

    [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).

    With the code below:

    CATMathAxis  axis;
    CATMathDirection D1(1.,0.,0.);
    CATMathDirection D2(0.,1.,0.);
    CATMathDirection D3(0.,0.,1.);
    CATMathPoint  mathpoint(5.,15.,50.);
    axis.Set(mathpoint,D1,D2,D3);
    double slantLengthEnd(80);
    double slantLengthStart(18);
    double coneAngle = 0.25*CATPI;
    double startAngle = -0.2*CAT2PI;
    double endAngle = +0.1*CAT2PI;
    double radius(25.);

    //
double coneAngle = 0.25*CATPI;
double startAngle = -0.2*CAT2PI;
double endAngle = +0.1*CAT2PI;
double radius(25.);
    cout << "Cone creation" << endl;
    CATCone * pCone =  piGeomFactory->CreateCone(axis,radius,ConeAngle,StartAngle, EndAngle, slantLengthStart,slantLengthEnd);

---

CATCone * pCone =  piGeomFactory->CreateCone(axis,radius,ConeAngle,StartAngle, EndAngle, slantLengthStart,slantLengthEnd);
you get this result:

Fig.1 Frustum of a right circular cone  ![Frustrum of a circular cone](images/CGM_cone_0.png)  |  Base radius: 25mm
The base radius relies on the plane defined by the first and second direction of the cone axis. This plane passes through the axis origin.
Slant height: 62mm = slant length end (80mm) - slant length start (18mm)
Cone angle = 45 deg (0.25*CATPI) = angle between the cone and the base plane.

## References

[1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)
## History

Version: **1** [Sept 2012] | Document created
---|---
