---
title: "Creating a Multi Patch NURBS Surface"
category: "use case"
module: "CAACgmOperators"
tags: "["CAAGMOperatorsOverview", "CAAGMOperatorsInterfaces", "CAATopNurbsSurfMultiPatch", "CAADoc", "CATICGMObject", "CAAGMModelGemBrowser", "CAAGMOperatortsNurbsSurfMultiPatch", "CATICGMTopSkin", "CATIA", "CAAGMOperatorsNurbsSurfMultiPatch"]"
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopNurbsSurfMultiPatch.htm"
converted: "2026-05-11T17:33:49.224912"
---
tags: ["CAAGMOperatorsOverview", "CAAGMOperatorsInterfaces", "CAATopNurbsSurfMultiPatch", "CAADoc", "CATICGMObject", "CAAGMModelGemBrowser", "CAAGMOperatortsNurbsSurfMultiPatch", "CATICGMTopSkin", "CATIA", "CAAGMOperatorsNurbsSurfMultiPatch"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopNurbsSurfMultiPatch.htmmd"
converted: "2026-05-11T17:33:49.224912"
Creating a Multi Patch NURBS Surface

---
converted: "2026-05-11T17:33:49.224912"
Creating a Multi Patch NURBS Surface
Use Case
Abstract A NURBS can be dressed by using the CATICGMTopSkin operator. You can do this operation either on a single patch or a multi patch NURBS. This article explains how to proceed for a multi patch NURBS.

    * What You Will Learn With This Use Case
    * The CAAGMOperatorsNurbsSurfMultiPatch Use Case
      * What Does CAAGMOperatorsNurbsSurfMultiPatch Do?
      * How to Launch CAAGMOperatorsNurbsSurfMultiPatch
      * Where to Find the CAAGMOperatorsNurbsSurfMultiPatch Code
    * Step-by-Step
    * In Short
    * References
---
What You Will Learn With This Use Case This use case is intended to help you create a multi patch NURBS surface, then transform one of its patches into a skin. The CAAGMOperatorsNurbsSurfMultiPatch Use Case CAAGMOperatorsNurbsSurfMultiPatch is a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates the GMOperatorsInterfaces framework capabilities. What Does CAAGMOperatorsNurbsSurfMultiPatch Do? The CAAGMOperatorsNurbsSurfMultiPatch use case:
    * Creates the geometry factory.
    * Creates the knot vectors along U and V.
    * Creates the grid of poles to be used for the NURBS surface.
    * Creates a rational NURBS surface and modifies one of the pole weight.
    * Creates a skin relying on the NURBS
    * Writes the model and closes the container.
How to Launch CAAGMOperatorsNurbsSurfMultiPatch To launch CAAGMOperatortsNurbsSurfMultiPatch , you will need to set up the build time environment, then compile CAAGMOperatorsNurbsSurfMultiPatch.m along with its prerequisites, set up the run time environment, and then execute the use case [1]. If you simply type CAAGMOperatorsNurbsSurfMultiPatch with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example: `CAAGMOperatorsNurbsSurfMultiPatch e/NurbsSurfMultiPatch .NCGM` This NCGM file can be displayed using the CAAGMModelGemBrowser use case. Where to Find the CAAGMOperatorsNurbsSurfMultiPatch Code The CAAGMOperatorsNurbsSurfMultiPatch use case is made of a main named CAATopNurbsSurfMultiPatch.cpp located in the CAAGMOperatorsNurbsSurfMultiPatch .m module of the CAAGMOperatorsInterfaces.edu framework: `InstallRootFolder/CAADoc/CAAGMOperatorsInterfaces.edu/CAAGMOperatorsNurbsSurfMultiPatch.m/` where `InstallRootFolder` [1] is the folder where the API CD-ROM is installed. Step-by-Step There are six steps in CAATopNurbsSurfMultiPatch.cpp:
    1. Creating the Geometry Factory
    2. Creating the Knot Vector
    3. Creating the Grid of Poles
    4. Creating the Nurbs Surface
    5. Creating the Skin
    6. Writing the Model and Closing the Container
Creating the Geometry Factory The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject. This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.

    CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**(#) ;
```vbscript
    if (NULL==piGeomFactory) return (1);

```

Creating the Knot Vector Note that CATIA Version 5 does not support periodic NURBS. You can create a periodic NURBS but the geometric modeler does not guarantee that the operations that can be applied to such NURBS surface later on will be performed properly.

    long IsPeriodic= 0;
    long Degree= 3;
    long IndexOffset= 1;

    // a - Create the knot vector along U
    //
long Degree= 3;
long IndexOffset= 1;
    long KnotsCount1= 4;                    // 4 knots -> 3 arcs/patches along U
    double Knots1[]= {0., 2., 3., 4.};
    long Multiplicities1[]= {4, 2, 1, 4};

    CATKnotVector NonUniformU(Degree,IsPeriodic,KnotsCount1,Knots1,
            Multiplicities1,IndexOffset);

    // b - Create the knot vector along V
    //
CATKnotVector NonUniformU(Degree,IsPeriodic,KnotsCount1,Knots1,
Multiplicities1,IndexOffset);
    long KnotsCount2= 3;                    // 3 knots -> 2 arcs/patches along V
    double Knots2[]= {0.,10.,11.};

    long Multiplicities2[]= {4,2,4};

    CATKnotVector NonUniformV(Degree,IsPeriodic,KnotsCount2,Knots2,
            Multiplicities2,IndexOffset);

Creating the Grid of Poles Before going any further, do not skip the warning below: Warning: When creating a knot vector in CATIA, the number of knots to be specified in the CATKnotVector constructor is the number of knots **with different values**. The total number of nodes is deduced from the multiplicity array. Given this:

`**Total** number of nodes (including nodes with same value) = number of poles + degree + 1`
`Number of poles = sum of multiplicities - last multiplicity`
`Number of poles = sum of multiplicities - (degree + 1)`
---
Creating the Grid of Poles Before going any further, do not skip the warning below: Warning: When creating a knot vector in CATIA, the number of knots to be specified in the CATKnotVector constructor is the number of knots **with different values**. The total number of nodes is deduced from the multiplicity array. Given this:
In the CAAGMOperatorsNurbsSurfMultiPatch sample, a multi patch (4 nodes along U and 3 nodes along V) NURBS is to be created. The following sets of data is choosen for the NURBS vectors:

    * along U:
In the CAAGMOperatorsNurbsSurfMultiPatch sample, a multi patch (4 nodes along U and 3 nodes along V) NURBS is to be created. The following sets of data is choosen for the NURBS vectors:
degree of the basis functions = 3
number of knots with different value = 4  giving three patches
array of multiplicities = {degree+1, 2, 1, degree+1} = {4, 2, 1, 4}

    * along V:
degree of the basis functions = 3
number of knots with different value = 4  giving three patches
array of multiplicities = {degree+1, 2, 1, degree+1} = {4, 2, 1, 4}
degree of the basis functions = 3
number of knots with different value = 3 giving two patches
array of multiplicities = {degree+1, 2, degree+1} = {4, 2, 4}
Therefore the number of poles to be specified along U is  7 while the number of poles along V is 6 and the total number of poles is nbPolesU* nbPolesV = 42.

    int nbPoleU = 7;
    int nbPoleV = 6;

    CATMathGridOfPoints gridOfPoints(nbPoleU,nbPoleV);

    // Row 0
    //
    gridOfPoints.SetPoint(CATMathPoint( 0., 0., 0.),0,0);
    ...

    // Display the control points
    //
gridOfPoints.SetPoint(CATMathPoint( 0., 0., 0.),0,0);
```vbscript
    for (int i = 0; i < nbPoleU; i++)

```

        {
```vbscript
for (int i = 0; i < nbPoleU; i++)
```vbscript
            for (int j = 0; j < nbPoleV; j++)
```

```

            {
```vbscript
for (int i = 0; i < nbPoleU; i++)
```vbscript
for (int j = 0; j < nbPoleV; j++)
```

                CATMathPoint ptToBeDisplayed = gridOfPoints.GetPoint(i,j);
                CATCartesianPoint* piCartPt = piGeomFactory->CreateCartesianPoint(ptToBeDisplayed);
```

            }
        }

CATMathPoint ptToBeDisplayed = gridOfPoints.GetPoint(i,j);
CATCartesianPoint* piCartPt = piGeomFactory->CreateCartesianPoint(ptToBeDisplayed);
Displaying the control points allows you to check their position with respect to the NURBS. Creating the NURBS Surface Prior to creating the NURBS, the control point weights are initialized.

    long isRational=1;
    double * aWeights=new double[nbPoleU*nbPoleV];
```vbscript
    for (i = 0; i < nbPoleU*nbPoleV; i++)

```

      {
long isRational=1;
double * aWeights=new double[nbPoleU*nbPoleV];
for (i = 0; i < nbPoleU*nbPoleV; i++)
          aWeights[i] = 1.;   // Initialize the control point weights

      }

    // NURBS Surface creation
    //
aWeights[i] = 1.;   // Initialize the control point weights
    CATNurbsSurface * piSurf1 = piGeomFactory->
            CATCreateNurbsSurface(NonUniformU, NonUniformV,isRational,gridOfPoints,aWeights);

Then the weight of the (5, 5) and (3,5) control point is modified.

    piSurf1->SetOneWeight(5,5,150);
    piSurf1->SetOneWeight(3,5,150);

Creating the Skin For how to create a skin, see the CAAGMOperatorsOverview use case[2]. You have to define the limits on which the skin is to be applied. To specify the limits of a given patch, you must use the GetInternalMaxLimits of the CATSurface class which takes as its arguments the numbers allowing to locate the patch on the surface.

    / Retrieve the (1,0) patch limits
Creating the Skin For how to create a skin, see the CAAGMOperatorsOverview use case[2]. You have to define the limits on which the skin is to be applied. To specify the limits of a given patch, you must use the GetInternalMaxLimits of the CATSurface class which takes as its arguments the numbers allowing to locate the patch on the surface.
    CATSurLimits surMaxLimits ;
    piSurf1->GetInternalMaxLimits(1,0,surMaxLimits) ;

    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration(#);
    CATTopData topdata(pConfig);

    CATICGMTopSkin * pSkinOpe =::CATCGMCreateTopSkin(piGeomFactory,

            &topdata,
CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration(#);
CATTopData topdata(pConfig);
CATICGMTopSkin * pSkinOpe =::CATCGMCreateTopSkin(piGeomFactory,
            piSurf1,

            &surMaxLimits);
    ...

The resulting skin looks something like this (the green bullets are the control points):  ![Resulting Skin](images/CAACgmTopmultipatch.gif) This is to be compared with the global surface (rational with a weight of 150 applied to pole [5,5] and [3,5])
![Global Surface](images/CAACgmTopmultirational.gif) For your information, this would be the corresponding rational surface: ![Ratioanl Surface](images/CAACgmTopmultinonrational.gif) Writing the Model and Closing the Container To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved. The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.

    if(1==toStore)
     {
    #ifdef _WINDOWS_SOURCE
```cpp
if(1==toStore)
       ofstream filetowrite(pfileName, ios::binary ) ;
```

    #else
```cpp
if(1==toStore)
ofstream filetowrite(pfileName, ios::binary ) ;
       ofstream filetowrite(pfileName,ios::out,filebuf::openprot) ;
```

    #endif

       **::CATSaveCGMContainer**(piGeomFactory,filetowrite);
       filetowrite.close(#);
     }

     //
     // Closes the container
     //
     **::CATCloseCGMContainer**(piGeomFactory);

In Short Here are a few relations to remember when creating a NURBS `**Total** number of nodes = number of poles + degree + 1`
`Number of poles = sum of multiplicities - last multiplicity`
`Number of poles = sum of multiplicities - (degree + 1)` References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] | [Overview of the Topological Operators](CAACgmUcTopOverview.md)
[3] |  [ About NURBS](../CAACgmModel/CAACgmTaGobAboutNurbs.md)
History Version: **1** [Feb 2000] | Document created
---|---
