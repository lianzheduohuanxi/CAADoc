---
title: "Creating a Nozzle Shape Thanks to Shape Design Features"
category: "use case"
module: "CAAGsiUseCases"
tags: ["CAAGSMInterfaces", "CAAGsiNozzle", "CATIGSMFactory", "CATISpecObject", "CAAGsiUserTools", "CAA2SampleSession", "CATIGSMTool_var", "CAAGsiObjTool", "CATISpecObject_var"]
source_file: "Doc/online/CAAGsiUseCases/CAAGsiNozzleSample.htm"
converted: "2026-05-11T17:31:50.638182"
---
# Shape Design & Styling

| 
## Generative Shape Design

| 
### Creating a Nozzle Shape Thanks to Shape Design Features

_Using the Shape Design factory to create point, line, plane, circle, split, sweep, and loft features_  
---|---|---  
Use Case  
  
* * *
### Abstract

This article discusses the CAAGsiNozzle use case. This use case explains how to create a nozzle shape thanks to shape design features. 

  * **What You Will Learn With This Use Case**
  * **Some Important Concepts Relevant to CATGsiToolkit**
  * **The CAAGsiNozzle Use Case**
    * What Does CAAGsiNozzle Do
    * How to Launch CAAGsiNozzle
    * Where to Find the CAAGsiNozzle Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *
### What You Will You Learn With This Use Case

This use case is intended to help you make your first steps in programming with Shape Design. Its main intent is to allow you to create a nozzle shape using shape design features[2]. 

[Top]
### Some Important Concepts Relevant to CATGsiUserTools

The CAAGsiNozzle use case uses many services of the CAAGsiUserTools class. This class embeds several calls to the _CATIGSMFactory_ interface. This decreases the number of lines to write. We use a list that contains the input for the specification (feature) we want to instantiate. The way it is coded, enables the user to call many times the same method by changing a few parameters in the input list.

This class _CAAGsiUserTools_ separates the sample CAAGsiNozzle from the interfaces used from GSMInterfaces framework. This could be a good solution to limit the impact of a change in these interfaces for your in-house code.

Moreover, if a common task has to be done for every feature created by the user, this can be done in the `CreateXXX` method instead of doing it in every file that creates that feature. (As an example, change the name or put it into NoShow.)

[Top]
### The CAAGsiNozzle Use Case

CAAGsiNozzle is a use case of the CAAGSMInterfaces.edu framework that illustrates GSMInterfaces framework capabilities.

[Top]
#### What Does CAAGsiNozzle Do

The goal of CAAGsiUserTools use case is to show how to create a nozzle shape using shape design features. We enrich the sample code CAAGsiNozzle.cpp and explains in more detail the way shape design features are created.

We have decided to split the creation of the Nozzle Shape in different steps: first the Wireframe (Point, Plane, Circle), then the Shape (Sweep, Loft). The result is shown below.

![](images/CAAGsiNozzle.jpg)

[Top]
#### How to Launch CAAGsiNozzle

To launch CAAGsiNozzle, you will need to set up the build time environment, then compile CAAGsiNozzle along with its prerequisites, and set up the run time environment, and then execute the use case [1].

CAAGsiUserTools API is used in CAAGsiNozzle use Case 

Launch the use case as follows: 

  * With Windows 
        
        e:>CAAGsiNozzle outputDirectory\CAAGsiNozzle.CATPart  
  
---  
  * With UNIX 
        
        $ CAAGsiNozzle outputDirectory/CAAGsiNozzle.CATPart  
  
---  

where:

`outputDirectory` | The directory into which `CAAGsiNozzle.CATPart is saved`  
---|---  
`CAAGsiNozzle.CATPart` | The file that contains the part created to contain the nozzle shape result  
  
[Top]
#### Where to Find the CAAGsiNozzle Code

The CAAGsiNozzle use case is made of main program located in the CAAGsiNozzle.m module of the CAAGSMInterfaces.edu framework:

Windows | `InstallRootDirectory\CAAGSMInterfaces.edu\CAAGsiNozzle.m\`  
---|---  
Unix | `InstallRootDirectory/CAAGSMInterfaces.edu/CAAGsiNozzle.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

There are six logical step in CAAGsiNozzle: 

  1. Prolog
  2. Create Point Features
  3. Create Plane and Line Features
  4. Create Circle Features
  5. Create Split and Spline Features
  6. Create Sweep and Loft Features

We will now comment each of those sections by looking at the code of the main method of file CAAGsiNozzle.

[Top]
#### Prolog

In CAAGsiNozzle, we use an instance (named CAAGsiObjTool) of the class _CAAGsiUserTools_ to create shape design features. We call the `Init` method to create a session and a Part document.
    
    
    int **main**(int argc, char **argv, char **envp)
    {
      HRESULT rc = S_OK;
    
      char* pSessionName = "CAA2SampleSession";
      rc = CAAGsiObjTool.**Init**( pSessionName);
      if (FAILED(rc)) return 1;
    
      int setAsCurrent = 1;
      CATIGSMTool_var spTool = CAAGsiObjTool.[CreateGSMTool](../CAAGsiTechArticles/CAAGsiCreateGSMTool.md)("Nozzle",setAsCurrent);
      ...  
  
---  
  
Then, we create an open body to insert generative shape design features inside it. We call the `CreateGSMTool` method that returns the GSMTool that has been created.

[Top]
#### Create Point Features

How to create a point coordinate feature:
    
    
      ...
      CATLISTV(CATISpecObject_var) aObjectParameters;
      ...
      CATISpecObject_var spCurrent = NULL_var;
    
      CAAGsiObjTool.**CreateLength**("X", 17.0, **spCurrent**)
      aObjectParameters.Append(spCurrent);
      CAAGsiObjTool.**CreateLength**("Y", 0.0, spCurrent);
      aObjectParameters.Append(spCurrent);
      CAAGsiObjTool.**CreateLength**("Z", 0.0, spCurrent);
      aObjectParameters.Append(spCurrent);
    
      CATISpecObject_var spPoint1 = CAAGsiObjTool.**CreatePointCoord**(aObjectParameters);
      aObjectParameters.RemoveAll();
      ...  
  
---  
  
Here we create a point coordinate at location (17,0,0). For this purpose, we first create three length parameters with values 17, 0, and 0 millimeters respectively, and put each into `spCurrent`, and then append `spCurrent` in the input list `aObjectParameters` that is bound to store the ordered parameters needed to create a feature. Finally, we create a point coordinate using `aObjectParameters` as input by calling the `CreatePointCoord`**** method.

How to create a point on curve feature:
    
    
      ...
      spCurrent = NULL_var;
      aObjectParameters.Append(spSplit2);
      aObjectParameters.Append(spCurrent);
      CAAGsiObjTool.**CreateReal**("Parm", 0.0, spCurrent);
      aObjectParameters.Append(spCurrent);  
      CATISpecObject_var spPoint14 = CAAGsiObjTool.**CreatePointOnCurve**(aObjectParameters,TRUE);
      aObjectParameters.RemoveAll();
      ...  
  
---  
  
We create a point on curve feature using Split.12 feature at curvilinear length 0 First, we get the spSplit12 CATISpecObject smart pointer and add it in `aObjectParameters`**.** Second, we set `spCurrent` to null and store it in the input list, that means that the reference for the curvilinear length will be computed taking into account the start extremity of Split.12 feature. We create a real parameter that represents the caviling length on the curve by calling `CreateReal` method. Finally we create a point on curve feature using `CreatePlaneEquation` method.

[Top]

* * *
#### Create Plane and Line Features

Now that we have created points, we can use them to create planes and lines.
    
    
      ...
      CAAGsiObjTool.**CreateLength**("A", 0.0, spCurrent);
      aObjectParameters.Append(spCurrent);
      CAAGsiObjTool.**CreateLength**("B", 1.0, spCurrent);
      aObjectParameters.Append(spCurrent);
      CAAGsiObjTool.**CreateLength**("C", 0.0, spCurrent);
      aObjectParameters.Append(spCurrent);
      CAAGsiObjTool.**CreateLength**("D",10.0, spCurrent);
      aObjectParameters.Append(spCurrent);
            
      CATISpecObject_var spPlaneY10 = CAAGsiObjTool.**CreatePlaneEquation**(aObjectParameters);
      aObjectParameters.RemoveAll();
      ...  
  
---  
  
Here we create the plane Y = 10. To do this, we create a plane equation with the `aObjectParameters` input list Here the parameters created are length for the plane coefficients, and after having created the four length parameters, we call the `CreatePlaneEquation`**** method.

We can also create lines like this: 
    
    
      ...
      aObjectParameters.Append(spPoint3);
      aObjectParameters.Append(spPoint5);
      CATISpecObject_var spLine3 = CAAGsiObjTool.**CreateLinePtPt**(aObjectParameters);
      aObjectParameters.RemoveAll();
      ...  
  
---  
  
We create a simple line defined by two points. We get `spPoint3` (respectively `spPoint5`), a _CATISpecObject_ smart pointer on Point.3 (respectively Point.5) feature and store it in the `aObjectParameters` input list used by `CreateLinePtPt`**** method to create the line point-point feature.

[Top]

* * *
#### Create Circle Features

How to create circles:
    
    
      ...
      aObjectParameters.Append(spPoint5);
      aObjectParameters.Append(spPoint6);
      aObjectParameters.Append(spPlaneY15);
      CAAGsiObjTool.**CreateLength**("Radius", 15.0, spCurrent);
      aObjectParameters.Append(spCurrent);
      CATISpecObject_var spCircle3 = CAAGsiObjTool.**CreateCircle2PointsRad**(aObjectParameters,FALSE,TRUE);
      aObjectParameters.RemoveAll();
      ...  
  
---  
  
We want to create a circle profile in plane Y=15. On this purpose, we first retrieve the `spPoint5`, `spPoint6` and `spPlaneY15` _CATISpecObject_ smart pointers and append them into the `aObjectParameters` input list used by the `CreateCircle2PointsRad`**** method to create a circle defined by two points and a radius.

The circle will pass through Point.5 and Point.6 and will have for reference plane the plane Y=15. The circle Circle.3 will not be a geodesic circle and will keep the same orientation defined by the input. The part of the circle arc will depend on the orientation given to the method `CreateCircle2PointsRad`.

[Top]

* * *
#### Create Split and Spline Features

We can now create split features that will relimit a feature by intersection with another one.
    
    
      ...
      aObjectParameters.Append(spCircle6);
      aObjectParameters.Append(spPlaneAngle35);
      CATISpecObject_var spSplit1 = CAAGsiObjTool.**CreateSplit**(aObjectParameters,TRUE);
      aObjectParameters.RemoveAll();
      ...  
  
---  
  
We create a split feature that will be the relimitation of Circle.6 by Plane.6. To do this, we set `spCircle6` and `spPlaneAngle35` in the `aObjectParameters` input list and call `CreateSplit`**** to create Split.1 feature. The orientation (`TRUE` argument) enable us to choose between the two parts of the circle that is splitted.

How to create a spline feature:
    
    
      ...
      aObjectParameters.Append(spPoint15);
      aObjectParameters.Append(spPoint16);
      CATISpecObject_var spDir1 = CAAGsiObjTool.**CreateDirection**(spLine7);
      CATISpecObject_var spDir2 = CAAGsiObjTool.**CreateDirection**(spLine8);
      CATISpecObject_var spSpline = CAAGsiObjTool.**CreateSpline**(aObjectParameters,spDir1,FALSE,spDir2,TRUE);
      aObjectParameters.RemoveAll();
      ...  
  
---  
  
The spline will go through Point.15 and Point.16. Then we create two directions that are defined relatively to a line feature. We create a spline feature that goes through Point.15 and Point.16, and that have two tangents defined at the extremity.We will take the inverse direction for `spDir1` and the same direction for `spDir2`.

We have created two directions above that will not be seen in the Procedural View [3]. Indeed, direction features are internal features for shape design features.

[Top]

* * *
#### Create Sweep and Loft Features

Now that we have created the wireframe we need, we can create skins, let see how to create sweep and loft.
    
    
      ...
      aObjectParameters.Append(spLine2);
      aObjectParameters.Append(spCircle1);
      CATISpecObject_var spSweep1 = CAAGsiObjTool.**CreateSweepOneGuide**(aObjectParameters);
      aObjectParameters.RemoveAll();
      ...  
  
---  
  
We create a sweep unspec feature with a guide Line.2 and a profile Circle.1. Line.2 will be used also as the spine of the explicit sweep.

The same for the loft feature:
    
    
      ...
      CATLISTV(CATISpecObject_var) aObjectParametersSections;
      aObjectParametersSections.Append(spCircle2);
      aObjectParametersSections.Append(spCircle3);
      aObjectParameters.Append(spLine3);
      CATISpecObject_var spUnused = NULL_var;
    
      CATISpecObject_var spLoft1 = CAAGsiObjTool.**CreateLoft**(aObjectParametersSections,
                                                            aObjectParameters,
                                                            spUnused);
    
      aObjectParameters.RemoveAll();
      aObjectParametersSections.RemoveAll();
      ...  
  
---  
  
We create a loft feature with sections Circle.2, Circle.3 and with guide Line.3. The input list `aObjectParameters` contains the guide curve and the sections are stored in the `aObjectParametersSections` dedicated list. We call the `CreateLoft`**** method with `spUnused` set to `NULL_var` which represents the spine of the loft. Here we use the automatic spine capability of the loft feature.

[Top]

* * *
### In Short

This use case has demonstrated the way to create a nozzle shape thanks to shape design primitives. We illustrates the use of the _CAAGsiUserTools_ class that encapsulates the _CATIGSMFactory_ method for a set of capabilities. We illustrates also the creation of wireframe and almost simple skin features. We also show that there is different ways to design points, lines, planes, circles depending on what are the driving parameters the user want to manipulate and also the way he wants the shape to behave in a modification scenario.

[Top]

* * *
### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] | [About Generative Shape Design Features](../CAAGsiTechArticles/CAAGsiShapeDesignFeature.md)  
[3] | [Inserting a Shape Design Feature in the procedural view ](../CAAGsiTechArticles/CAAGsiInsertInProceduralView.md)  
[4] |  [Updating a shape Design feature ](../CAAGsiTechArticles/CAAGsiUpdateShapeDesign.md)  
[Top]  
  
* * *
### History

Version: **1** [Apr 2000] | Document created  
---|---  
Version: **2** [Apr 2003] | Update  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
