---
title: "Analyzing the Parameters of a Point on a Curve"
category: "use case"
module: "CAACgmModel"
tags: ["CAADoc", "CAAGMModelAnalysisOpe", "CAAGMModelGemBrowser", "CAAGMModelInterfaces", "CATICGMLocalAnalysis1Db", "CATICGMLocalAnalysis1D"]
source_file: "Doc/online/CAACgmModel/CAACgmUcGMModelAnalysisOpe.md"
converted: "2026-05-11T17:33:48.237061"
---
# Analyzing the Parameters of a Point on a Curve  
  
---  
Use Case  
## Abstract

The CAAGMModelAnalysisOpe use case illustrates how to analyze the parameters (normals, curvature and torsion) of a point on a curve by using the _CATICGMLocalAnalysis1D_ operator.
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

This use case [1] is intended to help you to use the CATICGMLocalAnalysis1D operator. See [2] for an overview of this type of operators.
## The CAAGMModelAnalysisOpe Use Case

CAAGMModelAnalysisOpe is a use case of the CAAGMModelInterfaces.edu framework.
### What Does CAAGMModelAnalysisOpe Do

 This use case creates the input data to be passed to the CATICGMLocalAnalysis1D operator (a circle with a radius of 50mm), creates the operator and performs the geometric analyzes. The result can be optionally saved into an NCGM container and displayed using the CAAGMModelGemBrowser use case [3].  
---|---  
### How to Launch CAAGMModelAnalysisOpe 

To launch CAAGMModelAnalysisOpe, you will need to set up the build time environment, then compile CAAGMModelAnalysisOpe.m along with its prerequisites, set up the run time environment, and then execute the use case [4].

If you simply type CAAGMModelAnalysisOpe with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example:

`CAAGMModelAnalysisOpe e/analysis1D.NCGM`

This NCGM file can be displayed using the CAAGMModelGemBrowser use case [3].
### Where to Find the CAAGMModelAnalysisOpe Code

The CAAGMModelAnalysisOpe use case is made of a main named CAAGMModelAnalysisOpe .cpp located in the CAAGMModelAnalysisOpe .m module of the CAAGMModelInterfaces.edu framework:

`InstallRootFolder\CAADoc\CAAGMModelInterfaces.edu\CAAGMModelAnalysisOpe.m\`

where `InstallRootFolder` [4] is the folder where the API CD-ROM is installed.
## Step-by-Step

The initial step which consists in creating the geometry factory as well as the last step which consists in writing the model and closing the factory are described in [1]. The coding steps dedicated to the CATICGMLocalAnalysis1D operator are explained below: 

    1. Creating the Geometry Factory [1].
    2. Creating the Curve and the point to be analyzed
    3. Creating and Using the CATICGMLocalAnalysis1D operator
    4. Writing the Model and Closing the Factory [1].
### Creating the Curve and the Point to Be Analyzed
    
    // a - Create a circle
    //
    const double epsilon=1e-6;
    CATMathPlane plane;
    double radius = 50.;
    CATCircle * pCircle = piGeomFactory->CreateCircle(radius, plane);
    ...
    CATCrvParam paramcircle = pCircle->CreateParam(0.);

The geometry is created by the `CATGeoFactory` with the CreateCircle method. No geometric point is created, the point to be analyzed is specified by its parameter.
### Creating and Using the CATICGMLocalAnalysis1D Operator

The CATCGMCreateLocalAnalysis1D global function is used to create the operator.b> The normals, curvature and torsion are then analyzed and compared with the expected values which are round values easy to check for a circle. 
    
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
    
    angle main norma - bi normal 1.5708
    curvature 1
    torsion 0
    IsARegularParam 1
## In Short

CATICGMLocalAnalysis1Db> is a geometric operator which follows the same scheme as all geometric operators: it is a transient object and its execution does not modify the input operands. It must be operated within a single container. Its purpose is to analyze the parameters (derivatives) on a point on a curve.
## References

[1] | [An Introduction to Geometric Modeler Use Cases](CAACgmUcGMModelUseCaseOverw.md)  
---|---  
[2] | [How to Use Geometric Operators](CAACgmUcGMModelOpeOverw.md)  
[3] | [Browsing the Geometric Container](CAACgmUcGemBrowser.md)  
[4] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
## History

Version: **1** [Jan 2007] | Document created  
---|---
