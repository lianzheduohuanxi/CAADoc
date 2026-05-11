---
```vbscript
title: "Creating and Transforming Geometry"
category: "use case"
module: "CAACgmModel"
tags: ["CAAGMModelForeignSurfaceData", "CATICGMContainer", "CAADoc", "CAAForeignSurfaceData", "CATICGMObject", "CATICGMProjectionPtSur", "CAAGMModelGemBrowser", "CAAGMModelCreation", "CAAGobCreation", "CAAGMModelInterfaces", "CAAGMModelForeign", "CATIA", "CATIForeignSurface"]
source_file: "Doc/online/CAACgmModel/CAACgmUcGobCreation.htm"
converted: "2026-05-11T17:33:48.368669"
```

---
# Creating and Transforming Geometry  

---  
Use Case  
## Abstract

The GeometricObjects framework exposes the interfaces for the geometry: points, curves, surfaces, and some related classes (such as knot vector or surface and curve parameters for example). The use cases illustrates the creation of geometric objects. First surface is created. Then a CATPLine is created upon it, that is later cloned and transformed. The way to create CATPLine, to use the clone and transformation managers, as well as to use the surface parameter class or the surface evaluator classes is not particular to the foreign surface, but common to all the CATIA surfaces. The same methodology can be used to introduce foreign curves, only differing by the parent class to derive. 
    * What You Will Learn With This Use Case
    * The CAAGMModelCreation Use Case
      * What Does CAAGMModelCreation Do
      * How to Launch CAAGMModelCreation
      * Where to Find the CAAGMModelCreation Code
    * Step-by-Step
    * In Short
    * References  
---  
## What You Will Learn With This Use Case

The use case creates an instance (`piEggBox`) of a surface. This surface is a "foreign" surface: its definition has been declared in another use case CAAGMModelForeign [5], but this do not change any operation that can be done on it. Once introduced according to the appropriate process, a foreign surface can be used as any CATIA surface.

Fig 1: The "Eggs Box" Using the New Type of Surface ![Foreign Surface](images/CAACgmGobForeignSurface.gif) | Using this instance, the use case defines a CATPLine on it (`piPLine`), transforms the created CATPLine (`piTransfLine`), retrieves the corresponding underlying surface (`piTransfEggBox`), evaluates the normal at the four corners of the transformed surface. All these operations are the same for any CATIA surfaces or geometry.  
---|---  
## The CAAGMModelCreation Use Case

CAAGMModelCreation is a use case of the CAAGMModelInterfaces.edu framework that illustrates GeometricObjects framework capabilities.
### What Does CAAGMModelCreation Do

This use case creates a surface and use it in several geometric operations. The created surface is a foreign surface, but what is done for the foreign surface is exactly the same as what must be done for any CATIA surface: the use is the same.
### How to Launch CAAGMModelCreation

This use case creates a surface and use it in several geometric operations. The created surface is a foreign surface, but what is done for the foreign surface is exactly the same as what must be done for any CATIA surface: the use is the same.
To launch CAAGMModelCreation, you will need to set up the build time environment, then compile CAAGMModelCreation.m and CAAGMModelForeign.m along with their prerequisites, set up the run time environment, and then execute the use case [6].

If you simply type CAAGMModelCreation with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example:

`CAAGMModelCreation e/GeomObjectCreation.NCGM`

This NCGM file can be displayed using the CAAGMModelGemBrowser use case.
### Where to Find the CAAGMModelCreation Code

The CAAGMModelCreation use case is made of a main named CAAGobCreation.cpp located in the CAAGMModelCreation.m module of the CAAGMModelInterfaces.edu framework:

`InstallRootFolder\CAADoc\CAAGMModelInterfaces.edu\CAAGMModelCreation.m\`

The CAAGMModelCreation use case is made of a main named CAAGobCreation.cpp located in the CAAGMModelCreation.m module of the CAAGMModelInterfaces.edu framework:
where `InstallRootFolder` [6] is the folder where the API CD-ROM is installed.

The use case uses a class defined in the CAAGMModelForeign use case [5].

## Step-by-Step

where `InstallRootFolder` [6] is the folder where the API CD-ROM is installed.
The use case uses a class defined in the CAAGMModelForeign use case [5].
The main program peforms the following steps: 

    * Creating the Geometry Factory
    * Creating a CATIForeignSurface with an attribute `CAAForeignSurfaceData`
    * Creating a CATPLine on the foreign surface
    * Cloning the CATPLine
    * Applying a Transform to the CATPLine
    * Evaluating the Normals at the four corners of the transformed surface
    * Writing the Model and Closing the Container
### Creating the Geometry Factory

The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular) [3]. This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.

The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular) [3]. This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.
    CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**() ;
    if (NULL==piGeomFactory) return (1);

### Creating a CATIForeignSurface

CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**() ;
if (NULL==piGeomFactory) return (1);
The data is an attribute of the new type `CAAGMModelForeignSurfaceData`. The attribute instance is allocated here, its deletion is directly managed by the CATIForeignSurface.

The foreign surface instance is created by the method `CreateForeignSurface` of the CATGeoFactory, using the created attribute.

If an error occurs, the program closes the factory and returns an error code.

    CATMathPoint origin(50.,-10.,5.);
    CATMathDirection directionU(1.,0.,0.), directionV(0.,1.,0.);
    double uPeriod = 3. ;
    double vPeriod = 5. ;
    double height  = 7. ;
    double uMin    = -10. ;
    double uMax    = 23. ;
    double vMin    = -11. ;
    double vMax    = 34. ;

     // ------------ Creates the foreign data 
double uMax    = 23. ;
double vMin    = -11. ;
double vMax    = 34. ;
    CAAGMModelForeignSurfaceData* pData = 
         new **CAAGMModelForeignSurfaceData**(origin, 
                                      uPeriod*directionU,
                                      vPeriod*directionV,
                                      height/(uPeriod * vPeriod),
                                      uMin,
                                      uMax,
                                      vMin,
                                      vMax) ;
    if (NULL==pData)

    {
      **::CATCloseCGMContainer**(piGeomFactory);
vMin,
vMax) ;
if (NULL==pData)
      return (1);

    }

    // ------------ Creates the surface
return (1);
    CATIForeignSurface* piEggBox = NULL;
    piEggBox = piGeomFactory ->**CreateForeignSurface**(pData) ;
    if (NULL==piEggBox)

    {
      ::CATCloseCGMContainer(piGeomFactory);
CATIForeignSurface* piEggBox = NULL;
piEggBox = piGeomFactory ->**CreateForeignSurface**(pData) ;
if (NULL==piEggBox)
      return (1);

    }
### Creating a CATPLine

A CATPLine is a line in the space of a surface [4], whatever the surface is: directly a CATIA surface or a CATIForeignSurface. To create a CATPLine, one must specifies the starting and end points: these points are expressed in terms of parameters on the surface. No assumption must be made on the parameterization of the surface. The ways to define a CATSurParameter are: 

    * Projecting a 3D point on the surface with the geometric operator CATICGMProjectionPtSur.
    * Using the `CATSurface::GetParam` method (only for canonical surfaces and a point that is known to be on the surface).
    * Using the barycentric constructor, after retrieving the limits (`CATSurface::GetLimits`) of the surface: this way is illustrated below.

Now, the CATPLine can be created by using the `CATGeoFactory::CreatePLine` method.

Now, the CATPLine can be created by using the `CATGeoFactory::CreatePLine` method.
    _// Retrieves the limits of the surface_
    CATSurLimits surLimits;
    piEggBox ->**GetLimits**(surLimits);
    CATSurParam lowParam, highParam;
    surLimits.GetExtremities(lowParam, highParam); 

    // Defines the starting and end parameters
piEggBox ->**GetLimits**(surLimits);
CATSurParam lowParam, highParam;
surLimits.GetExtremities(lowParam, highParam);
    double iLambdaU = 0.5;
    double iLambdaV = 0.2;

    // barycenter of surLimits affected with the 0.5 and 0.2 coefficients
    **CATSurParam** start **(0.5,0.2,surLimits)** ; 
double iLambdaU = 0.5;
double iLambdaV = 0.2;
    iLambdaU = 0.8;
    iLambdaV = 0.3;
    CATSurParam end   (0.8,0.3,surLimits);

    _// Creates the Pline_
    CATPLine * piPLine = piGeomFactory->**CreatePLine**(start,end,piEggBox);
    if (NULL==piPLine)

    {
      ::CATCloseCGMContainer(piGeomFactory);
_// Creates the Pline_
CATPLine * piPLine = piGeomFactory->**CreatePLine**(start,end,piEggBox);
if (NULL==piPLine)
      return (1);

    }
### Cloning the CATPLine

This operation is done by the CATCloneManager [2], whose interest is in taking into account the links between the objects during the duplication. The clone manager is used as any CGM operator. To follow the general scheme:

    * Create it.
    * Set the parameters: here, `Add` the objects to clone
    * `Run` it.
    * Retrieve the duplicated object: `ReadImage`.
    * `delete` it.

The clone manager can be used in two modes, defined at its creation:

    * The `CatCGMSingleDuplicate` default mode only duplicates the objects that are added to the clone manager.
    * The `CatCGMFullDuplicate` mode duplicates the added objects and their forward links.

The clone manager can be used in two modes, defined at its creation:
In the use case, the default mode is used: hence, the surface on which the CATPLine is lying is not duplicated. This is tested by comparing the tags of the underlying surface of the CATPLine before and after duplication. The tag is an unique numeric identifier inside the geometry factory. Each CATICGMObject has a persistent tag, that can be retrieved with the `CATICGMContainer::GetPersistentTag` method.

Notice that this process is independent from the type of surface.

    // single duplication by default
In the use case, the default mode is used: hence, the surface on which the CATPLine is lying is not duplicated. This is tested by comparing the tags of the underlying surface of the CATPLine before and after duplication. The tag is an unique numeric identifier inside the geometry factory. Each CATICGMObject has a persistent tag, that can be retrieved with the `CATICGMContainer::GetPersistentTag` method.
Notice that this process is independent from the type of surface.
    CATCloneManager * pCloneManager= **new CATCloneManager**(piGeomFactory,
                                                         CatCGMSingleDuplicate);
    if (NULL==pCloneManager)

    {
       ::CATCloseCGMContainer(piGeomFactory);
CATCloneManager * pCloneManager= **new CATCloneManager**(piGeomFactory,
CatCGMSingleDuplicate);
if (NULL==pCloneManager)
       return (1);

    }

    // Asks for the duplication of the PLine
    pCloneManager->**Add**(piPLine);

    // Runs the operator
    pCloneManager->**Run**();

    // Retrieves the object corresponding to the transformation of the PLine
pCloneManager->**Run**();
    CATICGMObject* piClonedPLine=NULL;
    piClonedPLine = pCloneManager->**ReadImage**(piPLine);
    if (NULL==piClonedPLine)

    {
       ::CATCloseCGMContainer(piGeomFactory);
CATICGMObject* piClonedPLine=NULL;
piClonedPLine = pCloneManager->**ReadImage**(piPLine);
if (NULL==piClonedPLine)
       return (1);

    }

    // Retrieves the persistent tags of the underlying surface of the initial 
    // and duplicated Plines
    // as the duplication mode is single, the underlying surface must be the same
    unsigned long tagSurfCloned = 
         ( ((CATPLine *)piClonedPLine )->GetSurface())->GetPersistentTag();
    unsigned long tagSurfPLine  = 
         (              piPLine        ->GetSurface())->GetPersistentTag();

unsigned long tagSurfCloned =
unsigned long tagSurfPLine  =
    if (**tagSurfCloned != tagSurfPLine**)    

    {
       ::CATCloseCGMContainer(piGeomFactory);
       return (3);
    }          
    **delete** pCloneManager;
    pCloneManager = NULL;
### Applying a Transform to the CATPLine

This operation is done by the `CATTransfoManager` [2], whose interest is in taking into account the links between the objects during the transformation. The transfo manager is used as any CGM operator: To follow the general scheme:

    * Create it.
    * Set the parameters: here, `Add` the objects to transform.
    * `Run` it.
    * Retrieve the transformed object: `ReadImage`.
    * `delete` it ( this deletion is delayed at the end of the next step, because the manager is still used to retrieve other information).

The transfo manager can be used in three modes, defined at its creation:

    * The `CATTransfoManager::Duplicate` default mode duplicates and transforms the objects that are added to the manager. The forward linked objects are not duplicated if they are invariant by the transformation.
    * The `CATTransfoManager::FullDuplicate` mode duplicates and transforms the objects that are added to the manager. But now, the forward linked objects are duplicated, even if they are invariant by the transformation.
    * The `CATTransfoManager::Replace` mode replaces the objects added to the manager, and their forward linked objects if they are not invariant.

In the use case, the default mode is used: hence, the CATPLine is duplicated and the surface on which the CATPLine is lying is duplicated, because it is not invariant. This is tested by comparing the tags of the underlying surface of the CATPLine before and after transformation.

In the use case, the default mode is used: hence, the CATPLine is duplicated and the surface on which the CATPLine is lying is duplicated, because it is not invariant. This is tested by comparing the tags of the underlying surface of the CATPLine before and after transformation.
Notice that this process is independent from the type of surface.

    CATMathTransformation mathTransf(CATMathVector(20.,10.,40.));

    // duplication of non-invariant objects by default
Notice that this process is independent from the type of surface.
CATMathTransformation mathTransf(CATMathVector(20.,10.,40.));
    CATTransfoManager * pTransfoManager = 
                        new **CATTransfoManager**(mathTransf,piGeomFactory); 
    if (NULL==pTransfoManager)

    {
       ::CATCloseCGMContainer(piGeomFactory);
CATTransfoManager * pTransfoManager =
new **CATTransfoManager**(mathTransf,piGeomFactory);
if (NULL==pTransfoManager)
       return (1);

    }

    // Asks for the transformation of piPLine
    pTransfoManager->**Add**(piPLine);

    // Runs the operator
    pTransfoManager->**Run**();

    // Retrieves the object corresponding to the transformation of the PLine
pTransfoManager->**Run**();
    CATICGMObject* piTransfPLine=NULL;
    piTransfPLine = pTransfoManager->**ReadImage**(piPLine);
    if (NULL==piTransfPLine)

    {
       ::CATCloseCGMContainer(piGeomFactory);
CATICGMObject* piTransfPLine=NULL;
piTransfPLine = pTransfoManager->**ReadImage**(piPLine);
if (NULL==piTransfPLine)
       return (1);

    }

    // In this case, the underlying surface is also duplicated.
return (1);
    unsigned long tagSurfTransf = 

                ( ((CATPLine *)piTransfPLine )->GetSurface())->GetPersistentTag();
    if (tagSurfTransf == tagSurfPLine)    
    {
       ::CATCloseCGMContainer(piGeomFactory);
unsigned long tagSurfTransf =
if (tagSurfTransf == tagSurfPLine)
       return (4);

    }     
### Evaluating the Normals

The evaluation is independent from the type of surface. 

    * The duplicated surface is first retrieved from the transfo manager.
    * Then, one gets the surface limits (`GetLimits`).
    * Using the barycentric constructor of the surface parameter, the parameters of a corner is computed.
    * The evaluation of this parameter as a 3D point is then done: notice that the parameterization of the surface cannot be assumed: the mapping must be done by the object, even for canonical objects such as planes or lines. The normal is also computed.
    * A geometric line representing the mathematical normal is created.

    // Retrieves the duplicated surface
     CATSurface * piTransfEggBox = (CATSurface*)(pTransfoManager->**ReadImage**(piEggBox));
     if (NULL==piTransfEggBox)
     {
       ::CATCloseCGMContainer(piGeomFactory);
CATSurface * piTransfEggBox = (CATSurface*)(pTransfoManager->**ReadImage**(piEggBox));
if (NULL==piTransfEggBox)
       return (1);

     }

     // Gets its limits
     piTransfEggBox ->**GetLimits**(surLimits); 

     // First corner
piTransfEggBox ->**GetLimits**(surLimits);
     CATSurParam surParam(1.,1.,surLimits);
     CATMathDirection normal;
     CATMathPoint mPoint;
     piTransfEggBox->**EvalPoint**(surParam, mPoint);
     piTransfEggBox->**EvalNormal**(surParam, normal);
     _// Creates thetrimmed line representing the tangent_
     piGeomFactory->**CreateLine**(mPoint,mPoint+10*normal);

    // ... and so one for the three remaining corners
    **delete** pTransfoManager;
piTransfEggBox->**EvalNormal**(surParam, normal);
_// Creates thetrimmed line representing the tangent_
piGeomFactory->**CreateLine**(mPoint,mPoint+10*normal);
    pTransfoManager = NULL;

### Writing the Model and Closing the Container

pTransfoManager = NULL;
To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved.

The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.

    if(1==toStore)

     {
    #ifdef _WINDOWS_SOURCE
The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.
if(1==toStore)
       ofstream filetowrite(pfileName, ios::binary ) ;

    #else
```vbscript
if(1==toStore)
ofstream filetowrite(pfileName, ios::binary ) ;
       ofstream filetowrite(pfileName,ios::out,filebuf::openprot) ;
```

    #endif

       **::CATSaveCGMContainer**(piGeomFactory,filetowrite);
       filetowrite.close();
     }	

     //
     // Closes the container
     //

     **::CATCloseCGMContainer**(piGeomFactory);
## In Short

The use case illustrates how to create and use geometry.
## References

[1] | [The Management of Foreign Data](CAACgmTaGobAttribute.md)  
---|---  
[2] | [The Clone and Transformation Managers](CAACgmTaGobClone.md)  
[3] | [The Objects of CATIA Geometric Modeler](CAACgmTaGobGeoObjects.md)  
[4] | [The Curves of CATIA Geometric Modeler](CAACgmTaGobCurves.md)  
[5] | [Creating Foreign Surfaces](CAACgmUcGobForeign.md)  
[6] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
## History

Version: **1** [Apr 2000] | Document created  
---|---
