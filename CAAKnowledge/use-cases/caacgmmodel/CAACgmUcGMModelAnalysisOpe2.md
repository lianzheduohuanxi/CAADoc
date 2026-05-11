---
title: "Analyzing the Parameters of a Point on a Surface"
category: "use case"
module: "CAACgmModel"
tags: ["CAADoc", "CAAGMModelAnalysisOpe", "CAAGMModelGemBrowser", "CAAGMModelInterfaces", "CATICGMLocalAnalysis2D", "CATICGMLocalAnalysis1D"]
source_file: "Doc/online/CAACgmModel/CAACgmUcGMModelAnalysisOpe2.htm"
converted: "2026-05-11T17:33:48.247650"
---
# Analyzing the Parameters of a Point on a Surface  
  
---  
Use Case  
## Abstract

The CAAGMModelAnalysisOpe use case illustrates how to analyze the parameters (normals, curvature and torsion) of a point on a surface by using the _CATICGMLocalAnalysis2D_ operator. This is the second part of the use case, the first part is dedicated to the _CATICGMLocalAnalysis1D_ operator.
    * What You Will Learn With This Use Case
    * The CAAGMModelAnalysisOpe Use Case
      * What Does CAAGMModelAnalysisOpe Do
      * How to Launch CAAGMModelAnalysisOpe
      * Where to Find the CAAGMModelAnalysisOpe Code
    * Step-by-Step
    * In Short
    * References  
---  
## What You Will Learn With This Use Case

This use case [1] is intended to help you to use the CATICGMLocalAnalysis2D operator. See [2] for an overview of this type of operators.
## The CAAGMModelAnalysisOpe Use Case

CAAGMModelAnalysisOpe is a use case of the CAAGMModelInterfaces.edu framework.
### What Does CAAGMModelAnalysisOpe Do

 This use case creates the input data to be passed to the CATICGMLocalAnalysis2D operator (a cylinder with a radius of 45.2mm), creates the operator and performs the geometric analyzes. The result can be optionally saved into an NCGM container and displayed using the CAAGMModelGemBrowser use case [3].  
---|---  
### How to Launch CAAGMModelAnalysisOpe 

To launch CAAGMModelAnalysisOpe, you will need to set up the build time environment, then compile CAAGMModelAnalysisOpe.m along with its prerequisites, set up the run time environment, and then execute the use case [4].

If you simply type CAAGMModelAnalysisOpe with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example:

CAAGMModelAnalysisOpe `e/analysis2D.NCGM`

This NCGM file can be displayed using the CAAGMModelGemBrowser use case [3].
### Where to Find the CAAGMModelAnalysisOpe Code

The CAAGMModelAnalysisOpe use case is made of a main named CAAGMModelAnalysisOpe.cpp located in the CAAGMModelAnalysisOpe .m module of the CAAGMModelInterfaces.edu framework:

`InstallRootFolder\CAADoc\CAAGMModelInterfaces.edu\`CAAGMModelAnalysisOpe `.m\`

where `InstallRootFolder` [4] is the folder where the API CD-ROM is installed.
## Step-by-Step

The initial step which consists in creating the geometry factory as well as the last step which consists in writing the model and closing the factory are described in [1]. The coding steps dedicated to the CATICGMLocalAnalysis2D operator are explained below: 

    1. Creating the Geometry Factory [1].
    2. Creating the Surface and the Point to be analyzed
    3. Creating and Using the CATICGMLocalAnalysis2D operator
    4. Writing the Model and Closing the Factory [1].
### Creating the Surface and the Point to Be Analyzed

The surface on which is located the point to be analyzed is a cylinder.
    
    CATCylinder * pCyl = piGeomFactory->CreateCylinder(axis,radius1,
    StartHeight,EndHeight,
    StartAngle,EndAngle);
    ...
    CATSurParam paramcyl = pCyl->CreateParam(0.,0.);
    paramcyl.SetLocalParamU(0.5);
    paramcyl.SetLocalParamV(0.5);
    CATSurface * pSurface = pCyl;

The geometry is created by the `CATGeoFactory` with the CreateCylinder method. No geometric point is created, the point to be analyzed is specified by its parameter.
### Creating and Using the CATICGMLocalAnalysis2D Operator

The CATCGMCreateLocalAnalysis2D global function is used to create the operator. The fundamental forms along with the mean and gaussian curvature are retrieved.
    
    CATICGMLocalAnalysis1D * pAnalysisCircle =:: **CATCGMCreateLocalAnalysis1D**(pConfig,pCircle,paramcircle); 
    ...
    // c - Retrieve the main normal and the binormal and check 
    // that the angle between them must be equal to PI/2
    //
    CATMathVector mainnormal = pAnalysisCircle->GetMainNormal();
    CATMathVector binormal = pAnalysisCircle->GetBiNormal();
    ...
    // d - Retrieve the curvature and check that it is equal to 1
    //
    double curvature = pAnalysisCircle->GetCurvature();
    cout << "curvature " << fabs(curvature*radius) << endl;
    ...
    // e - Retrieve the torsion and check that it is equal to 0
    //
    double torsion = pAnalysisCircle->GetTorsion(); 
    cout << "torsion " << fabs(torsion) << endl;
    ...
    // f - Test whether the specified point is regular
    //
    CATLONG32 regular = pAnalysisCircle->IsARegularParam();
    cout << "IsARegularParam " << regular << endl;
    ...

Here are the messages on the standard output:
    
    Mean curvature 0.0110619
    Gaussian curvature 0
    IsARegularParam 1
## In Short

CATICGMLocalAnalysis2D is a geometric operator which follows the same scheme as all geometric operators: it is a transient object and its execution does not modify the input operands. It must be operated within a single container. Its purpose is to analyze the parameters (derivatives) around a point on a surface.
## References

[1] | [An Introduction to Geometric Modeler Use Cases](CAACgmUcGMModelUseCaseOverw.md)  
---|---  
[2] | [How to Use Geometric Operators](CAACgmUcGMModelOpeOverw.md)  
[3] | [Browsing the Geometric Container](CAACgmUcGemBrowser.md)  
[4] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
## History

Version: **1** [Jan 2007] | Document created  
---|---
