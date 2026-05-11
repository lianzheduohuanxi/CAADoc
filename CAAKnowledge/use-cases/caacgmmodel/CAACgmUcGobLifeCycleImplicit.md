---
title: "Creating Implicit Objects"
category: "use case"
module: "CAACgmModel"
tags: ["CATICGMContainer", "CAADoc", "CATICGMObject", "CAAGMModelGemBrowser", "CAAGMModelLifeCycleImplicit", "CAAGMModelInterfaces", "CATIA"]
source_file: "Doc/online/CAACgmModel/CAACgmUcGobLifeCycleImplicit.md"
converted: "2026-05-11T17:33:48.407972"
---
# Creating Implicit Objects  
  
---  
Use Case  
## Abstract

The use case illustrates how to create implicit objects and how they are managed by the CATIA Geometric Modeler in terms of life cycle.. 
    * What You Will Learn With This Use Case
    * About Implicit Objects
    * The CAAGMModelLifeCycleImplicit Use Case
      * What Does CAAGMModelLifeCycleImplicit Do
      * How to Launch CAAGMModelLifeCycleImplicit
      * Where to Find the CAAGMModelLifeCycleImplicit Code
    * Step- by- Step
    * In Short
    * References  
---  
## What You Will Learn With This Use Case

The use case explains how to create implicit objects and illustrates how their life cycle is managed.
## About Implicit Objects

Implicit objects are created by the implicit factory. They are automatically removed when all the objects that point to them are removed with the RemoveDependancies option of the CATICGMContainer::Remove method.
## The CAAGMModelLifeCycleImplicit Use Case

CAAGMModelLifeCycleImplicit is a use case of the CAAGMModelInterfaces.edu framework that illustrates GeometricObjects framework capabilities.
### What Does CAAGMModelLifeCycleImplicit Do

With this use case, you create an implicit CATPlane on which an implicit CATPline is created. Then this CATPLine is cloned. Because the CATCloneManager is created with the CatCGMFullDuplicate option, a duplicate plane is created.
### How to Launch CAAGMModelLifeCycleImplicit

To launch CAAGMModelLifeCycleImplicit, you will need to set up the build time environment, then compile CAAGMModelLifeCycleImplicit.m along with its prerequisites, set up the run time environment, and then execute the use case [1].

If you simply type CAAGMModelLifeCycleImplicit with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example:

`CAAGMModelLifeCycleImplicit`` e/ObjCreation.NCGM`

This NCGM file can be displayed using the CAAGMModelGemBrowser use case.
### Where to Find the CAAGMModelLifeCycleImplicit Code

The CAAGMModelLifeCycleImplicit use case is made of a main named CAAGMModelLifeCycleImplicit.cpp located in the CAAGMModelLifeCycleImplicit.m module of the CAAGMModelInterfaces.edu framework:

`InstallRootFolder\CAADoc\CAAGMModelInterfaces.edu\CAAGMModelLifeCycleImplicit.m\`

where `InstallRootFolder` [1] is the folder where the API CD-ROM is installed.
## Step-by-Step

The main program is divided into the following steps:

    1. Creating the Standard Geometry Factory
    2. Creating the Implicit Geometry Factory
    3. Creating the Implicit Objects: the CATPlane, the Initial CATPline and the Cloned CATPLine
    4. Removing the two Plines with RemoveDependancies and Attempting to create a New CATPline
    5. Writing the Model and Closing the Container
### Creating the Standard Geometry Factory

The geometry factory (`CATGeoFactory`) creates and manages all the CATICGMObject This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.
    
    CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer() ;
    if (NULL == piGeomFactory) return (1);
### Creating the Implicit Geometry Factory

The implicit factory is retrieved from the standard factory by using the `CATGeoFactory::GetImplicitGeoFactory` method.
    
    CATGeoFactory * piImplicitFactory =piGeomFactory->GetImplicitGeoFactory( );
    if (NULL == piImplicitFactory) return (1); 
### Creating the Implicit Objects: the CATPlane, the Initial CATPline and the Cloned CATPLine

You create implicit objects exactly like you would create standard or explicit objects, except that the implicit factory is to be used.

There are two ways to create a cloned objects:

    * Either in full duplication mode, in this case the objects referred to by the object to be cloned are duplicated by the CATCloneManager (the CATPline underlying plane is duplicated).
    * Or in single duplication mode, in this case only the object to be cloned is duplicated.
    
    CATPlane * piPlane = piImplicitFactory->CreatePlane(CATMathOIJ);
    ...
    CATPLine * pPline =  piImplicitFactory->CreatePLine   (p1, p2, piPlane );
    **// ----- Clone pPline - Full duplication mode
    //       A duplicate plane is created because the CatCGMFullDuplicate
    //       is specified - if the default option is used, the duplicated 
    //       PLine points to the already existing plane.**
    CATCloneManager * pCloneManager= new CATCloneManager(piImplicitFactory, CatCGMFullDuplicate); 
    ...
    pCloneManager->Add(pPline);
    pCloneManager->Run();
    CATICGMObject* piClonedPLine=NULL;
    piClonedPLine = pCloneManager->ReadImage(pPline);
### Removing the Two Plines with RemoveDependancies and Attempting to Create a New CATPline

The RemoveDependancies option only applies to implicit objects. By using it, you will remove all the implicit objects no longer used by the object which is to be removed.

    * Case 1: CATCloneManager in full duplication option

If you remove pPline with the RemoveDependancies options, piPlane being an implicit object, it is removed. Any attempt to re-use it to create another Pline will result in a throw. Removing the cloned CATPLine will not change anything.

    * Case 2: CATCloneManager is single duplication option 

If you remove pPline with RemoveDependancies but not piClonedPLine, piPlane will not be removed because it is still pointed to by piClonedPLine and you will be able to re-use it to create a new PLine.  
but, if you remove pPline as well as piClonedPLine with the RemoveDependancies option, piPlane will be removed because it is no longer pointed to by other objects and you will not be able to re-use piPlane.
    
    piImplicitFactory->Remove(pPline,CATICGMContainer::RemoveDependancies);
    piImplicitFactory->Remove(piClonedPLine,CATICGMContainer::RemoveDependancies);
### Writing the Model and Closing the Container

To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved.

The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.
    
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
## In Short

This use case describes how to create implicit objects and illustrates how the RemoveDependancies option affects their life cycle.
## References

[1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
## History

Version: **1** [Jun 2003] | Document created  
---|---
