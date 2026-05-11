---
title: "Creating a Single Patch NURBS Surface"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsOverview", "CAAGMOperatorsInterfaces", "CAATopNurbsSurfSinglePatch", "CAADoc", "CAAGMOperatorsNurbsSurfSinglePatch", "CATICGMObject", "CAAGMModelGemBrowser", "CATICGMTopSkin", "CATIA"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopNurbsSurfSinglePatch.md"
converted: "2026-05-11T17:33:49.236921"
---

Creating a Single Patch NURBS Surface  
---  
Use Case  
Abstract A NURBS can be dressed by using the CATICGMTopSkin operator. You can do this operation either on a single patch or a multi patch NURBS. This article explains how to proceed for a single patch NURBS.
    * What You Will Learn With This Use Case
    * The CAAGMOperatorsNurbsSurfSinglePatch Use Case
      * What Does CAAGMOperatorsNurbsSurfSinglePatch Do?
      * How to Launch CAAGMOperatorsNurbsSurfSinglePatch
      * Where to Find the CAAGMOperatorsNurbsSurfSinglePatch Code
    * Step-by-Step
    * In Short
    * References  
---  
What You Will Learn With This Use Case This use case is intended to help you create a single patch NURBS surface, then transform it into a skin. The CAAGMOperatorsNurbsSurfSinglePatch Use Case CAAGMOperatorsNurbsSurfSinglePatch is a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates the GMOperatorsInterfaces framework capabilities. What Does CAAGMOperatorsNurbsSurfSinglePatch Do? The CAAGMOperatorsNurbsSurfSinglePatch use case:
    * Creates the geometry factory.
    * Creates the grid of poles to be used for the NURBS surface.
    * Creates the knot vectors along U and V.
    * Creates a rational NURBS surface and modifies one of the pole weight.
    * Creates a skin relying on the NURBS.
    * Writes the model and closes the container.
How to Launch CAAGMOperatorsNurbsSurfSinglePatch To launch CAAGMOperatorsNurbsSurfSinglePatch , you will need to set up the build time environment, then compile CAAGMOperatorsNurbsSurfSinglePatch.m along with its prerequisites, set up the run time environment, and then execute the use case [1]. If you simply type CAAGMOperatorsNurbsSurfSinglePatch with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example: `CAAGMOperatorsNurbsSurfSinglePatch e/NurbsSurfSinglePatch.NCGM` This NCGM file can be displayed using the CAAGMModelGemBrowser use case. Where to Find the CAAGMOperatorsNurbsSurfSinglePatch Code The CAAGMOperatorsNurbsSurfSinglePatch use case is made of a main named CAATopNurbsSurfSinglePatch.cpp located in the CAAGMOperatorsNurbsSurfSinglePatch .m module of the CAAGMOperatorsInterfaces.edu framework: `InstallRootFolder\CAADoc\CAAGMOperatorsInterfaces.edu\CAAGMOperatorsNurbsSurfSinglePatch.m\` where `InstallRootFolder` [1] is the folder where the API CD-ROM is installed. Step-by-Step There are six steps in CAATopNurbsSurfSinglePatch.cpp:
    1. Creating the Geometry Factory
    2. Creating the Grid of Poles
    3. Creating the Knot Vector
    4. Creating of the Nurbs Surface
    5. Creating the Skin
    6. Writing the Model and Closing the Container
Creating the Geometry Factory The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject. This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.
    
    CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**() ;
    if (NULL==piGeomFactory) return (1);

Creating the Grid of Poles Before going any further, do not skip the warning below: Warning: When creating a knot vector in CATIA, the number of knots to be specified in the CATKnotVector constructor is the number of knots **with different values**. The total number of nodes is deduced from the multiplicity array. Given this:  
`**Total** number of nodes (including nodes with same value) = number of poles + degree + 1`  
`Number of poles = sum of multiplicities - last multiplicity`  
`Number of poles = sum of multiplicities - (degree + 1)`  
---  
In the CAATopNurbsSurfSinglePatch.cpp sample, a single patch (two nodes along U and V) NURBS is to be created. The following set of data is selected for the NURBS vectors (the same along U and V).
    * Degree of the basis functions = 4
    * Number of knots with different value = 2
    * Array of multiplicities = {degree+1, degree+1} = { 5 , 5 }
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

Displaying the control points allows you to check their position with respect to the NURBS. Creating the Knot Vector Note that CATIA Version 5 does not support periodic NURBS. You can create a periodic NURBS but the geometric modeler does not guarantee that the operations that can be applied to such NURBS surface later on will be performed properly.
    
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

Creating the NURBS Surface Prior to creating the NURBS, the control point weights are initialized.
    
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

Then the (3,3) control point weight is modified.
    
    // Assign a weight value (80) to the (3,3) poles 
    //
    piSurf1->SetOneWeight(3,3,80);

Creating the Skin For how to create a skin, see the CAAGMOperatorsOverview use case[2]. You have to define the limits on which the skin is to be applied. In this use case, the maximum limits are specified.
    
    // Retrieve the maximum limits
    CATSurLimits surMaxLimits ;
    piSurf1->GetMaxLimits(surMaxLimits) ;
        
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig);
    
    // Create the CATTopSkin operator to be applied to the max limits
    CATICGMTopSkin * pSkinOpe =::CATCGMCreateTopSkin(piGeomFactory,
            &topdata,
            piSurf1,
            &surMaxLimits);
    ...

This is the skin you obtain (the green bullets are the control points):  ![Result Skin](images/CAACgmTopsinglepatchrational.gif) This is to be compared with the equivalent non rational one:  
![Equivalent Non-rational Skin](images/CAACgmTopsinglepatchnonrational.gif) **Note** : The greater the weight is, the closer is the surface to the control point. Writing the Model and Closing the Container To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved. The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.
    
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

In Short Here are a few relations to remember when creating a NURBS `**Total** number of nodes = number of poles + degree + 1`  
`Number of poles = sum of multiplicities - last multiplicity`  
`Number of poles = sum of multiplicities - (degree + 1)` References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] | [Overview of the Topological Operators](CAACgmUcTopOverview.md)  
[3] |  [ About NURBS](../CAACgmModel/CAACgmTaGobAboutNurbs.md)  
History Version: **1** [Feb 2000] | Document created  
---|---
