---
title: "Constructing Graphic Representations in Batch Mode"
category: "use case"
module: "CAAVisUseCases"
tags: ["CATI3DGeoVisu", "CATIPrtContainer", "CAAGviVisuBatchuse", "CAAGviVisuBatch", "CAAVisuBatch", "CAAGeometryVisualization"]
source_file: "Doc\online\CAAVisUseCases\CAAVisSampleVisuBatch.htm"
converted: "2026-05-11T17:31:52.235473"
---

# 3D PLM Enterprise Architecture

| 

## 3D Visualization

| 

### Constructing Graphic Representations in Batch Mode

_How to use the CATVisManager in batch mode_  
---|---|---  
Use Case  
  
* * *

### Abstract

This article shows how to construct graphic representations in batch mode. 

  * **What You Will Learn With This Use Case**
  * **The CAAGviVisuBatch Use Case**
    * What Does CAAGviVisuBatch Do
    * How to Launch CAAGviVisuBatch
    * Where to Find the CAAGviVisuBatch Code
  * **Step-by-Step**
  * **In Short**
  * **References**



* * *

### What You Will Learn With This Use Case

This use case is intended to show you how to use the _CATVisManager_ to construct the graphic representations (rep) of a model.  [Top]

### The CAAGviVisuBatch Use Case

CAAGviVisuBatch is a use case of the CAAGeometryVisualization.edu framework that illustrates Visualization and VisualizationBase framework capabilities. [Top]

#### What Does CAAGviVisuBatch Do

CAAGviVisuBatch constructs the graphic representations associated with the MechanicalPart (`Part1`) of the following Model: _Fig.1 The CAAVisuBatch Part Document_ | ![](images/CAAVisSampleVisuBatch.jpg)  
---  
  
[Top]

#### How to Launch CAAGviVisuBatch

To launch CAAGviVisuBatch , you will need to set up the build time environment, then compile CAAGviVisuBatch along with its prerequisites, set up the run time environment, and then execute the use case [1].

`mkrun -c `CAAGviVisuBatch `InputPart `

where `InputPart` is the complete path of a Part document. You can use the following Part document:

  * Unix : `InstallRootDirectory/CAAGeometryVisualization.edu/InputData/CAAVisuBatch.CATPart`
  * Windows : `InstallRootDirectory\CAAGeometryVisualization.edu\InputData\CAAVisuBatch.CATPart`



[Top]

#### Where to Find the CAAGviVisuBatch Code

The CAAGviVisuBatch use case is made of a single file, _CAAGviVisuBatch.cpp_ , located in the CAAGviVisuBatch.m module of the CAAGeometryVisualization.edu framework:

Windows | `InstallRootDirectory\CAAGeometryVisualization.edu\CAAGviVisuBatch.m\`  
---|---  
Unix | `InstallRootDirectory/CAAGeometryVisualization.edu/CAAGviVisuBatch.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]

### Step-by-Step

There are seven logical steps in CAAGviVisuBatch:

  1. Prolog
  2. Creates a Path with the MechanicalPart feature of the Part Document
  3. Retrieves the unique CATVisManager Instance 
  4. Attaches the Root Model to the CATVisManager
  5. Retrieves the Graphic Representation of the MechanicalPart feature
  6. Detaches the Root Model from the CATVisManager
  7. Epilog



[Top]

#### Prolog

CAAGviVisuBatch begins by creating a session, and opening a Part document. Next it retrieves the root container of this Part as a pointer to _CATIPrtContainer_ , `pISpecContainer.` This is the usual sequence for loading a Part document. 

Thanks to  the `GetPart` method on the root container we retrieve the Mechanical Part. This part is handled by the smart pointer `spSpecObjectOnMechanicalPart`.

#### Creates a Path with the MechanicalPart feature of the Part Document
    
    
    ...
     **CATPathElement** * pRootObjectPath = new CATPathElement(spSpecObjectOnMechanicalPart);       
    ...  
  
---  
  
In this use case, the _CATPathElement_ is built with the root feature of the Part Document. This feature is the MechanicalPart feature, those called Part1 in the specification tree. Refer to the Mechanical Modeler articles. But anyhow, you can create this path with any feature of the model. 

#### Retrieves the unique CATVisManager Instance 
    
    
    ...
     **CATVisManager** * pVisManager = CATVisManager::**GetVisManager**();   
    ...  
  
---  
  
There is only one instance of the _CATVisManager_ class in a session. The `GetVisManager` static method enables you to retrieve it.

#### Attaches the Root Model to  the CATVisManager
    
    
    ...
        list<IID> ListIVisu3d;
        IID * pIIDInf = new IID(IID_CATI3DGeoVisu) ;
        ListIVisu3d.**fastadd**(pIIDInf);
    
        CAT3DViewpoint * pVP = new **CAT3DViewpoint**();
        
        rc = pVisManager->**AttachTo** ( pRootObjectPath, pVP, ListIVisu3d);
    ...  
  
---  
  
On the _CATVisManager_ you attach to the _CATVisManager_ :

  * The Path of the root model to build, p`RootObjectPath, `
  * For a default viewpoint, `pVP,`
  * For a given list of the visualization interfaces, `ListIVisu3d`. Here, it is a list with only the _CATI3DGeoVisu_ interface, once the Mechanical features implement it.



![](../CAAIcons/images/warning.gif)The `AttachTo` method constructs the graphic representations. 

#### Retrieves the Graphic Representation of the MechanicalPart feature
    
    
    ...
        **CATI3DGeoVisu** * pIVisuOnRoot =NULL ;    
        rc = spSpecObjectOnMechanicalPart->QueryInterface(IID_CATI3DGeoVisu,
                                                              (void **) & pIVisuOnRoot);
        ...
           CATRep * pRep = pIVisuOnRoot->**GiveRep**();
           if ( NULL != pRep )
           {
              CAT3DRep * p3DRep = (CAT3DRep *) pRep;
    
              CAT3DBoundingSphere pBe = p3DRep->GetBoundingElement();
              ...
    
    ...  
  
---  
  
After the `AttachTo` method, it is possible to retrieve the graphic representations (rep) of an element thanks to the `GiveRep` method of the _CATI3DGeoVisu_ interface. In this use case, the rep of the MechanicalPart feature (the root) is asked. 

#### Detaches the Root Model from the CATVisManager
    
    
    ...
     rc = pVisManager->**DetachFrom**(pVP,0) ;
    
    
     pVP->Release();
     pVP = NULL ;
    ...  
  
---  
  
When the graphic representations are useless, you should detach the root model from the _CATVisManager_. With the `DetachFrom` method with only the viewpoint, all the root models and the list of interfaces attached with this viewpoint will be detached too. (The same root model can be attached with different viewpoints and with different interfaces)

[Top]

#### Epilog

The last part of the CAAGviVisuBatchuse case shows how to removes the Part document from the session and delete the session. This is also described in the "Loading a Document" use case (see Data Access entry in the CAA Encyclopedia home page)

[Top]

* * *

### In Short

This use case explains how to use the CATVisManager to create the graphic representations of model in a batch.

[Top]

* * *

### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.htm)  
---|---  
[Top]  
  
* * *

### History

Version: **1** [Fev 2003] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
