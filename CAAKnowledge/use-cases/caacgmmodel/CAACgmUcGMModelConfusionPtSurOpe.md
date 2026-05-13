---
title: "Checking the Confusion of Points on a Surface"
category: "use-case case"
module: "CAACgmModel"
tags: "["CAADoc", "CAAGMModelConfusionOpe", "CATICGMConfusionPtOnSurPtOnSur", "CAAGMModelGemBrowser", "CAAGMModelInterfaces", "CATICGMLocalAnalysis1D", "CATICGMTopSkin"]"
source_file: "Doc/online/CAACgmModel/CAACgmUcGMModelConfusionPtSurOpe.htm"
converted: "2026-05-11T17:33:48.280142"
---
# Checking the Confusion of Points on a Surface

---
Use Case
## Abstract

The CAAGMModelConfusionOpe use case illustrates how to detect whether two points located on a surface are overlapping by using the _CATICGMConfusionPtOnSurPtOnSur_ operator.
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

This use case [1] is intended to help you to use the _CATICGMConfusionPtOnSurPtOnSur_ operator. See [2] for an overview of this type of operators.
## The CAAGMModelConfusionOpe Use Case

CAAGMModelConfusionOpe is a use case of the CAAGMModelInterfaces.edu framework. The second part of the use case illustrates how to use CATICGMConfusionPtOnSurPtOnSur.
### What Does CAAGMModelConfusionOpe Do

 This use case creates the input data to be passed to the _CATICGMConfusionPtOnSurPtOnSur_ operator:
    * A cylinder.
    * The two points to be compared.
It creates the operator and performs the geometric tests. The result can be optionally saved into an NCGM container and displayed using the CAAGMModelGemBrowser use case [3]. However, if you want to display the circle on which the two points are created, the object which is highlighted on the figure, you must adjust the use case and convert the CATCylinder into a CATICGMTopSkin.
---|---
### How to Launch CAAGMModelConfusionOpe

It creates the operator and performs the geometric tests. The result can be optionally saved into an NCGM container and displayed using the CAAGMModelGemBrowser use case [3]. However, if you want to display the circle on which the two points are created, the object which is highlighted on the figure, you must adjust the use case and convert the CATCylinder into a CATICGMTopSkin.
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
    2. Creating the Surface and the Points to be Analyzed
    3. Creating and Using the CATICGMConfusionPtOnSurPtOnSur operator
    4. Writing the Model and Closing the Factory [1].

### Creating the Surface and the Points to Be Analyzed

    // a - Create a cylinder
3. Creating and Using the CATICGMConfusionPtOnSurPtOnSur operator
4. Writing the Model and Closing the Factory [1].
    CATMathAxis IJK;
    double Radius = 2., h = 2.;
    CATSurface * pSurf = piGeomFactory->CreateCylinder(IJK, Radius, -h, h, -CATPI, CATPI);
    CATSurLimits limits2 = pSurf->GetLimits(#);

    // b - Create two points on this cylinder
double Radius = 2., h = 2.;
CATSurface * pSurf = piGeomFactory->CreateCylinder(IJK, Radius, -h, h, -CATPI, CATPI);
CATSurLimits limits2 = pSurf->GetLimits(#);
    const double alpha = 0.37;
    double vparam = 0.5;
    CATSurParam param3(alpha, vparam, limits2);
    CATPointOnSurface * Pt3 = piGeomFactory->CreatePointOnSurface(param3, pSurf);

    //double uparam = 0.371; // confusion not achieved
const double alpha = 0.37;
double vparam = 0.5;
CATSurParam param3(alpha, vparam, limits2);
CATPointOnSurface * Pt3 = piGeomFactory->CreatePointOnSurface(param3, pSurf);
    double uparam = 0.3705;
    CATSurParam param4(uparam, vparam, limits2);
    CATPointOnSurface * Pt4 = piGeomFactory->CreatePointOnSurface(param4, pSurf);

The geometry is created by the `CATGeoFactory` with the CreateCylinder method and the geometric points by the CreatePointOnSurface method.

### Creating and Using the CATICGMConfusionPtOnSurPtOnSur Operator

CATPointOnSurface * Pt4 = piGeomFactory->CreatePointOnSurface(param4, pSurf);
The geometry is created by the `CATGeoFactory` with the CreateCylinder method and the geometric points by the CreatePointOnSurface method.
The CATCGMConfusion global function is used to create the operator. The specified tolerance being 0.0001 (to be compared with the distance between points), the confusion is expected to be achieved.

    // c - Create the CATICGMConfusionPtOnSurPtOnSur operator
The CATCGMConfusion global function is used to create the operator. The specified tolerance being 0.0001 (to be compared with the distance between points), the confusion is expected to be achieved.
    CATICGMConfusionPtOnSurPtOnSur * pConfusionOpe1 =::CATCGMCreateConfusion(piGeomFactory, pConfig, Pt1, Pt2, Resolution*0.1);

    ...
The CATCGMConfusion global function is used to create the operator. The specified tolerance being 0.0001 (to be compared with the distance between points), the confusion is expected to be achieved.
CATICGMConfusionPtOnSurPtOnSur * pConfusionOpe1 =::CATCGMCreateConfusion(piGeomFactory, pConfig, Pt1, Pt2, Resolution*0.1);
    cout << "Tolerance " << Resolution*0.1 << endl;

    // d - Check the confusion
CATICGMConfusionPtOnSurPtOnSur * pConfusionOpe1 =::CATCGMCreateConfusion(piGeomFactory, pConfig, Pt1, Pt2, Resolution*0.1);
cout << "Tolerance " << Resolution*0.1 << endl;
    if (pConfusionOpe1->GetConfusion(#))
      cout << "Confusion is achieved " << endl;
    else
      cout << "Confusion is not achieved " << endl;

Here are the messages on the standard output:

    Check the overlapping of two points created on a surface
    Tolerance 0.01
    Distance between points 0.00628319
    Confusion is achieved

## In Short

Tolerance 0.01
Distance between points 0.00628319
Confusion is achieved
CATICGMConfusionPtOnSurPtOnSur is a geometric operator which follows the same scheme as all geometric operators: it is a transient object and its execution does not modify the input operands. It must be operated within a single container. Its purpose is to detect whether two points on a surface are confused.

## References

[1] | [An Introduction to Geometric Modeler Use Cases](CAACgmUcGMModelUseCaseOverw.md)
---|---
[2] | [How to Use Geometric Operators](CAACgmUcGMModelOpeOverw.md)
[3] | [Browsing the Geometric Container](CAACgmUcGemBrowser.md)
[4] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
## History

Version: **1** [Jan 2007] | Document created
---|---
