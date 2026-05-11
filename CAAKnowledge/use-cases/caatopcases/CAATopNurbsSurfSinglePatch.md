---
title: "Creating a Single Patch NURBS Surface"
category: "use case"
module: "CAATopUseCases"
tags: ["CAAGemBrowser", "CATICGMObject", "CATIA", "CAATopOverview", "CAATopNurbsSurfSinglePatch", "CAATopologicalOperators"]
source_file: "Doc/online/CAATopUseCases/CAATopNurbsSurfSinglePatch.htm"
converted: "2026-05-11T17:31:50.734376"
---
# Geometric Modeler

| 
## Topology

| 
### Creating a Single Patch NURBS Surface

_How to create and dress a single patch NURBS_  
---|---|---  
Use Case  
  
* * *
### Abstract

A NURBS can be dressed by using the CATTopSkin operator. You can do this operation either on a single patch or a multi patch NURBS. This article explains how to proceed for a single patch NURBS. 

  * **What You Will Learn With This Use Case**
  * **The CAATopNurbsSurfSinglePatch Use Case**
    * What Does CAATopNurbsSurfSinglePatch Do?
    * How to Launch CAATopNurbsSurfSinglePatch
    * Where to Find the CAATopNurbsSurfSinglePatch Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *
### What You Will Learn With This Use Case

This use case is intended to help you create a single patch NURBS surface, then transform it into a skin.

[Top]
### The CAATopNurbsSurfSinglePatch Use Case

CAATopNurbsSurfSinglePatch is a use case of the CAATopologicalOperators.edu framework that illustrates the TopologicalOperators framework capabilities.

[Top]
#### What Does CAATopNurbsSurfSinglePatch Do?

The CAATopNurbsSurfSinglePatch use case:

  * creates the geometry factory
  * creates the grid of poles to be used for the NURBS surface
  * creates the knot vectors along U and V
  * creates a rational NURBS surface and modifies one of the pole weight
  * creates a skin relying on the NURBS
  * writes the model and closes the container.

[Top]
#### How to Launch CAATopNurbsSurfSinglePatch

To launch CAATopNurbsSurfSinglePatch , you will need to set up the build time environment, then compile CAATopNurbsSurfSinglePatch .m along with its prerequisites, set up the run time environment, and then execute the use case [1].

If you simply type CAATopNurbsSurfSinglePatch with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example:

With Windows CAATopNurbsSurfSinglePatch `e/`NurbsSurfSinglePatch `.NCGM`

With UNIX CAATopNurbsSurfSinglePatch `/u/`NurbsSurfSinglePatch `.NCGM`

This NCGM file can be displayed using the CAAGemBrowser use case.

[Top]
#### Where to Find the CAATopNurbsSurfSinglePatch Code

The CAATopNurbsSurfSinglePatch use case is made of a main named CAATopNurbsSurfSinglePatch .cpp located in the CAATopNurbsSurfSinglePatch .m module of the CAATopologicalOperators.edu framework:

Windows | `InstallRootDirectory\CAATopologicalOperators.edu\`CAATopNurbsSurfSinglePatch `.m\`  
---|---  
Unix | `InstallRootDirectory/CAATopologicalOperators.edu/`CAATopNurbsSurfSinglePatch `.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

There are six steps in CAATopNurbsSurfSinglePatch.cpp: 

  1. Creating the geometry factory
  2. Creating the grid of poles
  3. Creating the knot vector
  4. Creating of the Nurbs surface
  5. Creating the skin
  6. Writing the model and closing thecontainer

[Top]
#### Creating the Geometry Factory

The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject. This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.
    
    
    CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**() ;
    if (NULL==piGeomFactory) return (1);  
  
---  
  
[Top]
#### Creating the grid of poles

Before going any further, do not skip the warning below: 

**warning** When creating a knot vector in CATIA, the number of knots to be specified in the CATKnotVector constructor is the number of knots **with different values**. The total number of nodes is deduced from the multiplicity array. Given this:  
**Total** number of nodes (including nodes with same value) = number of poles + degree + 1  
Number of poles = sum of multiplicities - last multiplicity  
Number of poles = sum of multiplicities - (degree + 1)  
---  
  
In the CAATopNurbsSurfSinglePatch sample, a single patch (two nodes along U and V) NURBS is to be created. The following set of data is selected for the NURBS vectors (the same along U and V).

  * degree of the basis functions = 4
  * number of knots with different value = 2
  * array of multiplicities = {degree+1, degree+1} = { 5 , 5 }

Therefore the number of poles to be specified along U and V is 5 and the total number of poles is nbPolesU* nbPolesV = 25.
    
    
    int nbPoleU = 5;
    int nbPoleV = 5;
    CATMathGridOfPoints gridOfPoints(nbPoleU,nbPoleV);
        
    // Row 0
    gridOfPoints.SetPoint(CATMathPoint( 0., 0., 0.),0,0);
    ...
    
    // Display the control points
    //
    for (int i = 0; i < nbPoleU; i++)
        {
            for (int j = 0; j < nbPoleV; j++)
            {
                CATMathPoint ptToBeDisplayed = gridOfPoints.GetPoint(i,j);
                CATCartesianPoint* piCartPt = piGeomFactory->CreateCartesianPoint(ptToBeDisplayed);
            }
        }  
  
---  
  
Displaying the control points allows you to check their position with respect to the NURBS.

[Top]
#### Creating the knot vector

Note that CATIA Version 5 does not support periodic NURBS. You can create a periodic NURBS but the geometric modeler does not guarantee that the operations that can be applied to such NURBS surface later on will be performed properly.
    
    
    long IsPeriodic= 0;
    long Degree= 4;
    long KnotsCount= 2;
    double Knots[]= {0.,10.};
    long Multiplicities[]= {5,5};
    long IndexOffset= 1;
        
    CATKnotVector NonUniformU(Degree,IsPeriodic,KnotsCount,Knots,
            Multiplicities,IndexOffset);
    CATKnotVector NonUniformV(Degree,IsPeriodic,KnotsCount,Knots,
            Multiplicities,IndexOffset);__  
  
---  
  
[Top]
#### Creating the NURBS Surface

Prior to creating the NURBS, the control point weights are initialized.
    
    
    long isRational=1;    
    double * aWeights=new double[nbPoleU*nbPoleV];
    for (i = 0; i < nbPoleU*nbPoleV; i++) 
      {
          aWeights[i] = 1.;   // Initialize the control point weights
      }
        
    // NURBS Surface creation
    //
    CATNurbsSurface * piSurf1 = piGeomFactory->
            CreateNurbsSurface(NonUniformU, NonUniformV,isRational,gridOfPoints,aWeights);  
  
---  
  
Then the (3,3) control point weight is modified. 
    
    
    // Assign a weight value (80) to the (3,3) poles 
    //
    piSurf1->SetOneWeight(3,3,80);  
  
---  
  
[Top]
#### Creating the skin

```vbscript
For how to create a skin, see the [CAATopOverview](CAATopOverview.md) use case[2]. You have to define the limits on which the skin is to be applied. In this use case, the maximum limits are specified.
    
```

    
    // Retrieve the maximum limits 
    CATSurLimits surMaxLimits ;
    piSurf1->GetMaxLimits(surMaxLimits) ;
        
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig);
    
    // Create the CATTopSkin operator to be applied to the max limits    
    CATTopSkin * pSkinOpe =::CATCreateTopSkin(piGeomFactory,
            &topdata,
            piSurf1,
            &surMaxLimits);
    ...  
  
---  
  
This is the skin you obtain (the green bullets are the control points): 

![](images/singlepatchrational.gif)

this is to be compared with the equivalent non rational one:  

![](images/singlepatchnonrational.gif)

Note: The greater the weight is, the closer is the surface to the control point.

 

[Top]
#### Writing the Model and Closing the Factory

To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved.

The use case ends with the closure of the geometry factory, done by the `::CATCloseCGMContainer` global function.
    
    
     if(1==toStore)
     {
    #ifdef _WINDOWS_SOURCE
       ofstream filetowrite(pfileName, ios::binary ) ;
    #else
       ofstream filetowrite(pfileName,ios::out,filebuf::openprot) ;
    #endif
    
       **::CATSaveCGMContainer**(piGeomFactory,filetowrite);
       filetowrite.close();
     }	
    
     _//
     // Closes the container
     //_	
     **::CATCloseCGMContainer**(piGeomFactory);  
  
---  
  
[Top]

* * *
### In Short

Here are a few relations to remember when creating a NURBS

**Total** number of nodes = number of poles + degree + 1  
Number of poles = sum of multiplicities - last multiplicity  
Number of poles = sum of multiplicities - (degree + 1)

[Top]

* * *
### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] | [Overview of the Topological Operators](CAATopOverview.md)  
[3] | [About Nurbs](../CAAGobTechArticles/Nurbs.md)  
[Top]  
---  
  
* * *
### History

Version: **1** [Feb 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
