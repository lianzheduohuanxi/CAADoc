---
```vbscript
title: "Creating Explicit Objects"
category: use-case case"
module: "CAACgmModel"
tags: ["CATICGMContainer", "CAADoc", "CATICGMObject", "CAAGMModelLifeCycleImplit", "CAAGMModelGemBrowser", "CAAGMModelLifeCycleImplicit", "CAAGMModelInterfaces", "CATIA", "CAAGMModelLifeCycleExplicit"]
source_file: "Doc/online/CAACgmModel/CAACgmUcGobLifeCycleExplicit.htmmd"
converted: "2026-05-11T17:33:48.395998"
```

---
# Creating Explicit Objects

---
Use Case
## Abstract

The use case illustrates how to create explicit objects and how they are managed by the CATIA Geometric Modeler in terms of life cycle.
    * What You Will Learn With This Use Case
    * The CAAGMModelLifeCycleExplicit Use Case
      * What Does CAAGMModelLifeCycleExplicit Do
      * How to Launch CAAGMModelLifeCycleExplicit
      * Where to Find the CAAGMModelLifeCycleExplicit Code
    * Step- by- Step
    * In Short
    * References
---
## What You Will Learn With This Use Case

The use case explains how to create explicit objects and illustrates how their life cycle is managed. **This use case has to be compared with CAAGMModelLifeCycleImplicit** for a good understanding of the behavior of implicit objects with respect to explicit objects.
## The CAAGMModelLifeCycleExplicit Use Case

CAAGMModelLifeCycleExplicit is a use case of the CAAGMModelInterfaces.edu framework that illustrates GeometricObjects framework capabilities.
### What Does CAAGMModelLifeCycleExplicit Do

With this use case, you create an explicit CATPlane on which an explicit CATPline is created. Then this CATPLine is cloned. Because the CATCloneManager is created with the CatCGMSingleDuplicate option, the cloned CATPline points to the CATPlane. Then you remove the CATPline and make an attempt to re-use the initial CATPlane pointer.
### How to Launch CAAGMModelLifeCycleExplicit

With this use case, you create an explicit CATPlane on which an explicit CATPline is created. Then this CATPLine is cloned. Because the CATCloneManager is created with the CatCGMSingleDuplicate option, the cloned CATPline points to the CATPlane. Then you remove the CATPline and make an attempt to re-use the initial CATPlane pointer.
To launch CAAGMModelLifeCycleExplicit, you will need to set up the build time environment, then compile CAAGMModelLifeCycleExplicit.m along with its prerequisites, set up the run time environment, and then execute the use case [1].

```vbscript
If you simply type CAAGMModelLifeCycleExplicit with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example:

```

With Windows `CAAGMModelLifeCycleExplicit`` e/Obj.NCGM`

This NCGM file can be displayed using the CAAGMModelGemBrowser use case.

### Where to Find the CAAGMModelLifeCycleExplicit Code

With Windows `CAAGMModelLifeCycleExplicit`` e/Obj.NCGM`
This NCGM file can be displayed using the CAAGMModelGemBrowser use case.
The CAAGMModelLifeCycleExplicit use case is made of a main named CAAGMModelLifeCycleExplicit.cpp located in the CAAGMModelLifeCycleExplicit.m module of the CAAGMModelInterfaces.edu framework:

`InstallRootFolder/CAADoc/CAAGMModelInterfaces.edu/CAAGMModelLifeCycleExplicit.m/`

where `InstallRootFolder` [1] is the folder where the API CD-ROM is installed.
## Step-by-Step

where `InstallRootFolder` [1] is the folder where the API CD-ROM is installed.
The main program is divided into the following steps:

    1. Creating the Standard Geometry Factory
    2. Creating the Implicit Geometry Factory
    3. Creating the Explicit Objects: the CATPlane, the Initial CATPline and the Cloned CATPLine
    4. Removing the two Plines with RemoveDependancies and Attempting to Create a New CATPline
    5. Writing the Model and Closing the Container

### Creating the Sandard Geometry Factory

3. Creating the Explicit Objects: the CATPlane, the Initial CATPline and the Cloned CATPLine
4. Removing the two Plines with RemoveDependancies and Attempting to Create a New CATPline
5. Writing the Model and Closing the Container
The geometry factory (`CATGeoFactory`) creates and manages all the CATICGMObject. This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.

    CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer(#) ;
```vbscript
    if (NULL == piGeomFactory) return (1);

```

### Creating the Implicit Geometry Factory

CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer(#) ;
if (NULL == piGeomFactory) return (1);
The implicit factory is retrieved from the standard factory by using the CATGeoFactory::GetImplicitGeoFactory(#) method.

    CATGeoFactory * piImplicitFactory =piGeomFactory->GetImplicitGeoFactory(#);
```vbscript
    if (NULL == piImplicitFactory) return (1);

```

### Creating the Explicit Objects: the CATPlane, the Initial CATPline and the Cloned CATPLine

CATGeoFactory * piImplicitFactory =piGeomFactory->GetImplicitGeoFactory(#);
if (NULL == piImplicitFactory) return (1);
There are two ways to create a cloned objects:

    * Either in full duplication mode, in this case the objects referred to by the object to be cloned are duplicated  by the CATCloneManager (the CATPline underlying plane is duplicated).
    * Or in single duplication mode, in this case only the object to be cloned is duplicated.

There are two ways to create a cloned objects:
    CATPlane * piPlane = piGeomFactory->CreatePlane(CATMathOIJ);

    ...
    CATPLine * pPline =  piGeomFactory->CreatePLine   (p1, p2, piPlane );
    **// ----- Clone pPline - Single duplication mode
    //       The duplicated
    //       PLine points to the already existing plane.**
CATPLine * pPline =  piGeomFactory->CreatePLine   (p1, p2, piPlane );
    CATCloneManager * pCloneManager= new CATCloneManager(piGeomFactory, CatCGMSingleDuplicate);

    ...
CATCloneManager * pCloneManager= new CATCloneManager(piGeomFactory, CatCGMSingleDuplicate);
    pCloneManager->Add(pPline);
    pCloneManager->Run(#);
    CATICGMObject* piClonedPLine=NULL;
```vbscript
    piClonedPLine = pCloneManager->ReadImage(pPline);

```

### Removing the Two Plines with RemoveDependancies and Attempting to Create a New CATPline

pCloneManager->Run(#);
CATICGMObject* piClonedPLine=NULL;
piClonedPLine = pCloneManager->ReadImage(pPline);
The RemoveDependancies option only applies to implicit objects. By using it, you will remove all the implicit objects no longer used by the object which is to be removed. In this case all the objects are explicit. Removing pPline and or piClonedPLine will not affect the existence of piPlane. Whatever the CATCloneManager option, you will be able to re-use the piPlane pointer.

    piImplicitFactory->Remove(pPline,CATICGMContainer::RemoveDependancies);
    piImplicitFactory->Remove(piClonedPLine,CATICGMContainer::RemoveDependancies);

### Writing the Model and Closing the Container

piImplicitFactory->Remove(pPline,CATICGMContainer::RemoveDependancies);
piImplicitFactory->Remove(piClonedPLine,CATICGMContainer::RemoveDependancies);
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
       filetowrite.close(#);
     }

     //
     // Closes the container
     //
     **::CATCloseCGMContainer**(piGeomFactory);
## In Short

This use case to be compared with the `CAAGMModelLifeCycleImplit` use case, illustrates the behavior of explicit objects vs the behavior of implicit objects in terms of life cycle.
## References

[1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
## History

Version: **1** [Dec 2006] | Document created
---|---
