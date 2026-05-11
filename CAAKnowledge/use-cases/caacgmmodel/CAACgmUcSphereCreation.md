---
title: "Sphere"
category: "use case"
module: "CAACgmModel"
tags: ["CAAGMModelInterfaces", "CAAGMModelSphereCreation"]
source_file: "Doc/online/CAACgmModel/CAACgmUcSphereCreation.md"
converted: "2026-05-11T17:33:48.523639"
---

Creating a Frustum of a Sphere  
---  
Use Case  
Abstract A frustum is a portion of a sphere intercepted between two parallels and two meridians.
    * API to be Used
    * Use Case Description
    * References  
---  
APIs to be Used A frustum of a sphere is defined by:
    * an axis
    * a radius
    * the start and end parallel angles
    * the start and end meridian angles.
To create a frustum of a sphere, use the CATGeoFactory::CreateSphere method which takes as arguments the parallel and meridian angles. The CATGeoFactory class is in the GeometricObjects framework.  Use Case Description The CAAGMModelSphereCreation.m module in CAAGMModelInterfaces.edu illustrates how to create a frustum of a sphere. This use case creates the input data required for the sphere creation. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).  With the code below:
    
    CATMathAxis  axis;
    CATMathDirection D1(1.,0.,0.);
    CATMathDirection D2(0.,1.,0.);
    CATMathDirection D3(0.,0.,1.);
    CATMathPoint  mathpoint(5.,15.,50.);
    CATCartesianPoint * pCartP = piGeomFactory->CreateCartesianPoint (5.,15.,50.);
    axis.Set(mathpoint,D1,D2,D3); 
     
    double startMeridianAngle = -0.2*CAT2PI;  // -72 deg
    double endMeridianAngle = 0.2*CAT2PI;     // 72 deg
    double startParallelAngle = -0.20*CAT2PI; // -72 deg 
    double endParallelAngle = +0.10*CAT2PI;   // 36 deg
    double radius(25.);
     
    // ----------------------------------------------
    // 3 -Create a piece of a sphere
    // ----------------------------------------------
    //
    cout << "Sphere creation" << endl;
    CATSphere * pSphere =  piGeomFactory->CreateSphere(axis,radius,
    startMeridianAngle, endMeridianAngle, startParallelAngle, endParallelAngle);  
    	  
  
---  
you get this result: Fig.1 Sphere: meridian and parallel angles ![Major start and end angles of a torus](images/CGM_sphere_0.png) 
---|---  
Meridian start angle: -72 deg   
Meridian end angle: + 72 deg   
Right-hand rule defines positive angles  
First direction of the sphere axis is the  
angle reference |  Parallel start angle: -72 deg   
Parallel end angle: + 36 deg   
Positive angles: sphere axis direction.  
  
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)  
History Version: **1** [Sept 2012] | Document created  
---|---
