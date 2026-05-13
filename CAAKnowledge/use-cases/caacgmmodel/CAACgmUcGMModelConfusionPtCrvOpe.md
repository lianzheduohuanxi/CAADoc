---
title: "Checking the Confusion of Points on a Curve"
category: "use-case case"
module: "CAACgmModel"
tags: "["CATICGMConfusionPtOnCrvPtOnCrv", "CAADoc", "CAAGMModelConfusionOpe", "CAAGMModelGemBrowser", "CAAGMModelInterfaces", "CATICGMLocalAnalysis1D"]"
source_file: "Doc/online/CAACgmModel/CAACgmUcGMModelConfusionPtCrvOpe.htm"
converted: "2026-05-11T17:33:48.267654"
---
# Checking the Confusion of Points on a Curve

---
Use Case
## Abstract

The CAAGMModelConfusionOpe use case illustrates how to detect whether two points located on a curve are overlapping by using the _CATICGMConfusionPtOnCrvPtOnCrv_ operator.
    * What You Will Learn With This Use Case
    * The CAAGMModelConfusionOpe Use Case
      * What Does CAAGMModelConfusionOpe Do
      * How to Launch CAAGMModelConfusionOpe
      * Where to Find the CAAGMModelConfusionOpe Code
    * Step-by-Step
    * In Short
    * References
---
## What You Will Learn With This Use Case

This use case [1] is intended to help you to use the _CATICGMConfusionPtOnCrvPtOnCrv_ operator. See [2] for an overview of this type of operators.
## The CAAGMModelConfusionOpe Use Case

CAAGMModelConfusionOpe is a use case of the CAAGMModelInterfaces.edu framework. The first part of the use case illustrates how to use CATICGMConfusionPtOnCrvPtOnCrv.
### What Does CAAGMModelConfusionOpe Do

 This use case creates the input data to be passed to the _CATICGMConfusionPtOnCrvPtOnCrv_ operator:
    * A circular arc with a radius of 1mm.
    * The two points to be compared.
It creates the operator and performs the geometric tests. The result can be optionally saved into an NCGM container and displayed using the CAAGMModelGemBrowser use case [3]. However, if you want to display the circle on which the two points are created, the object which is highlighted on the figure, you must adjust the use case and convert the CATCircle into a CATWire.
---|---
### How to Launch CAAGMModelConfusionOpe

It creates the operator and performs the geometric tests. The result can be optionally saved into an NCGM container and displayed using the CAAGMModelGemBrowser use case [3]. However, if you want to display the circle on which the two points are created, the object which is highlighted on the figure, you must adjust the use case and convert the CATCircle into a CATWire.
To launch CAAGMModelConfusionOpe, you will need to set up the build time environment, then compile CAAGMModelConfusionOpe.m along with its prerequisites, set up the run time environment, and then execute the use case [4].

```vbscript
If you simply type CAAGMModelConfusionOpe with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example:

```

CAAGMModelConfusionOpe `e/confusion.NCGM`

This NCGM file can be displayed using the CAAGMModelGemBrowser use case [3].

### Where to Find the CAAGMModelConfusionOpe Code

CAAGMModelConfusionOpe `e/confusion.NCGM`
This NCGM file can be displayed using the CAAGMModelGemBrowser use case [3].
The CAAGMModelConfusionOpe use case is made of a main named CAAGMModelConfusionOpe.cpp located in the CAAGMModelConfusionOpe.m module of the CAAGMModelInterfaces.edu framework:

`InstallRootFolder/CAADoc/CAAGMModelInterfaces.edu/CAAGMModelConfusionOpe.m/`

where `InstallRootFolder` [4] is the folder where the API CD-ROM is installed.
## Step-by-Step

where `InstallRootFolder` [4] is the folder where the API CD-ROM is installed.
The initial step which consists in creating the geometry factory as well as the last step which consists in writing the model and closing the factory are described in [1]. The coding steps dedicated to the CATICGMLocalAnalysis1D operator are explained below:

    1. Creating the Geometry Factory [1].
    2. Creating the Curve and the Points to be Analyzed
    3. Creating and Using the CATICGMConfusionPtOnCrvPtOnCrv operator
    4. Writing the Model and Closing the Factory [1].

### Creating the Curve and the Points to Be Analyzed

    // a - Create a circular segment
    ...
4. Writing the Model and Closing the Factory [1].
    double ThetaRange = CAT2PI*0.66;
    CATCircle * pCircle = piGeomFactory->CreateCircle(radius,Plane, 0, ThetaRange);
```vbscript
    if (NULL==pCircle )

```

    ..
double ThetaRange = CAT2PI*0.66;
CATCircle * pCircle = piGeomFactory->CreateCircle(radius,Plane, 0, ThetaRange);
if (NULL==pCircle )
    CATCrvLimits limits = pCircle->GetLimits(#);

    // b - Create two points on this circular circle
```cpp
if (NULL==pCircle )
CATCrvLimits limits = pCircle->GetLimits(#);
    double l1 = 0.5;
```

    //double l2 = 0.500025; // confusion not not achieved for tol = Res*0.1
CATCrvLimits limits = pCircle->GetLimits(#);
double l1 = 0.5;
    double l2 = 0.500024; // confusion is achieved for tol = Res*0.1
    CATCrvParam param1(l1,limits);
    CATCrvParam param2(l2,limits);
    CATPointOnCurve * Pt1 = piGeomFactory->CreatePointOnCurve(param1,pCircle);
    CATPointOnCurve * Pt2 = piGeomFactory->CreatePointOnCurve(param2,pCircle);

The geometry is created by the `CATGeoFactory` with the CreateCircle method and the geometric points by the CreatePointOnCurve method.

### Creating and Using the CATICGMConfusionPtOnCrvPtOnCrv Operator

CATPointOnCurve * Pt2 = piGeomFactory->CreatePointOnCurve(param2,pCircle);
The geometry is created by the `CATGeoFactory` with the CreateCircle method and the geometric points by the CreatePointOnCurve method.
The CATCGMConfusion global function is used to create the operator. The specified tolerance being 0.0001 (to be compared with the distance between points), the confusion should be achieved.

    // c - Create the CATICGMConfusionPtOnCrvPtOnCrv operator
The CATCGMConfusion global function is used to create the operator. The specified tolerance being 0.0001 (to be compared with the distance between points), the confusion should be achieved.
    CATICGMConfusionPtOnCrvPtOnCrv * pConfusionOpe1 =::CATCGMCreateConfusion(piGeomFactory, pConfig, Pt1, Pt2, Resolution*0.1);

    ...
The CATCGMConfusion global function is used to create the operator. The specified tolerance being 0.0001 (to be compared with the distance between points), the confusion should be achieved.
CATICGMConfusionPtOnCrvPtOnCrv * pConfusionOpe1 =::CATCGMCreateConfusion(piGeomFactory, pConfig, Pt1, Pt2, Resolution*0.1);
    cout << "Tolerance " << Resolution*0.1 << endl;

    // d - Check the confusion
CATICGMConfusionPtOnCrvPtOnCrv * pConfusionOpe1 =::CATCGMCreateConfusion(piGeomFactory, pConfig, Pt1, Pt2, Resolution*0.1);
cout << "Tolerance " << Resolution*0.1 << endl;
    if (pConfusionOpe1->GetConfusion(#))
      cout << "Confusion is achieved " << endl;
    else
      cout << "Confusion is not achieved " << endl;

Here are the messages on the standard output:

    Check the overlapping of two points created on a curve
    Distance between points 9.95257e-005
    Tolerance 0.0001
    Confusion is achieved

## In Short

Distance between points 9.95257e-005
Tolerance 0.0001
Confusion is achieved
CATICGMConfusionPtOnCrvPtOnCrv is a geometric operator which follows the same scheme as all geometric operators: it is a transient object and its execution does not modify the input operands. It must be operated within a single container. Its purpose is to detect whether two points on a curve are confused.

## References

[1] | [An Introduction to Geometric Modeler Use Cases](CAACgmUcGMModelUseCaseOverw.md)
---|---
[2] | [How to Use Geometric Operators](CAACgmUcGMModelOpeOverw.md)
[3] | [Browsing the Geometric Container](CAACgmUcGemBrowser.md)
[4] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
## History

Version: **1** [Jan 2007] | Document created
---|---
