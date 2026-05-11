---
title: "Creating Surface Machining Operations Overview"
category: "use-case"
module: "CAASmiTechArticles"
tags: ["CAASmiConnectUserOperationWithMA", "CAASmgGuide", "CAASmgOperation", "CAASmiUserOperationWithMA", "CAASmgMachiningFeature", "CAASmiUserOperationWithMAToolPath", "CAASmiUserOperationCommand", "CAASmiUserOperationUI", "CAASmiUserOperationWithUserMFToolPath", "CAASurfaceMachiningItf", "CAASmiUserOperationCatalog", "CAASmiUserOperationWithUserMF", "CATIA", "CAASmiUserOperationGeomUI", "CAASmiUserOperationToolPathReplay", "CAASmiUserMachFeatureCatalog", "CAASmgOperationWithMA"]
source_file: "Doc/online/CAASmiTechArticles/CAASmiOperationSampleOverview.htm"
converted: "2026-05-11T17:31:51.295307"
---
# Machining

| 
## 3 Axis Surface Machining

| 
### Creating Surface Machining Operations Overview

_A full example showing you how to add your own surface machining operations_  
---|---|---  
Technical Article  
  
* * *
### Abstract

This article discusses the CAASmiUserOperationCatalog, CAASmiUserOperationUI, CAASmiUserOperationWithMA, CAASmiUserOperationWithMAToolPath, CAASmiUserOperationWithUserMF and CAASmiUserOperationWithUserMFToolPath use cases. These use cases explain how to create and integrate **new surface machining operations** into CAA V5. 

  * **What You Will Learn With These Use Cases**
  * **Scenarios**
  * **The Use Cases**
    * What Does the Use Cases Do
    * How to Launch the Use Cases
    * Where to Find the Code
  * **In Short**
  * **References**

  
---  
  
* * *
### What You Will Learn With These Use Cases

These use cases are intended to help you make your first steps in creating new **Surface Machining Operations**. 

The main intent is to explain:

  * How to **define a surface machining operation** and how to store this definition (StartUp) in a file.
  * How to **customize** its dialog panel.
  * How to **manage its geometry** using surface machining geometry attributes.
  * How to connect it with **machining areas**.
  * How to **compute its tool path**.

These use cases include some knowledge from various V5 Frameworks, such as the Object Specs Modeler framework, or the Dialog and Dialog Engine Frameworks. Their intent is to focus on the use of the Surface Machining Infrastructure frameworks. A prerequisite knowledge of other Frameworks may be required to fully understand this use case, some links with other CAA use cases will help you navigate among them. 

Notice that some of these use cases can be put into practice in others Manufacturing Frameworks, like Prismatic Machining. 

Before getting to the tutorials, it is important to get an understanding of **the use case scenarios**. This is the goal of the next section.

[Top]
###  Scenarios

Two scenarios are available:

**Scenario 1** : Define a "Plunge" operation associated with a custom machining feature.

The goal of this scenario is to create a **new operation** CAASmgOperation. It has 3 parameters and it is connected with a **new machining feature** CAASmgMachiningFeature, linked to **geometry** by an **attribute** : CAASmgGuide. It computes a kind of "plunge roughing" tool path.

  
**Scenario 2** : Define a "Box" operation using machining areas.

The goal of this scenario is to create a second **operation** CAASmgOperationWithMA, illustrating the use of **machining areas**. It ****computes a tool path following the bounding boxes of the geometrical elements of a machining area.

  
[Top]
### The Use Cases

This section will describe the different tasks to perform to achieve this sample.
#### What Do These Use Cases Do

The final intent of these use cases is to create some new surface machining operations. This is an **end-to-end integration**. At the end of this use case "Tour", you should hardly notice any difference between these operations and an original V5 surface machining operation.

The sample is divided into several steps. Following them leads to full defined surface machining operations:

  1. Generates the Startups library. This is done in [CAASmiUserOperationCatalog](../CAASmiUseCases/CAASmiUserOperationCatalog.md) use case.
  2. Designs a command to create them. This is fully described in the referenced article [1].
  3. Customizes their editing panel. See [CAASmiUserOperationUI](../CAASmiUseCases/CAASmiUserOperationUI.md) use case.
  4. For the first operation only: 
     1. Generates the CAASmgMachiningFeature Startup catalog. This is fully described in the referenced article [2].
     2. Manages its geometry. See [CAASmiUserOperationWithUserMF](../CAASmiUseCases/CAASmiUserOperationWithUserMF.md) use case.
     3. Computes its tool path. See [CAASmiUserOperationWithUserMFToolPath](../CAASmiUseCases/CAASmiUserOperationWithUserMFToolPath.md) use case.
  5. For the second operation only: 
     1. Manages machining areas. See [CAASmiUserOperationWithMA](../CAASmiUseCases/CAASmiUserOperationWithMA.md) use case.
     2. Computes its tool path. See [CAASmiUserOperationWithMAToolPath](../CAASmiUseCases/CAASmiUserOperationWithMAToolPath.md) use case.

[Top]
#### How to Launch the Use Cases

To launch the use cases, you will need to set up the build time environment, then uncomment the lines of the interface dictionary, then compile all the modules of CAASurfaceMachiningItf.edu framework along with their prerequisites, and execute the use cases [3].

Be sure that use cases catalogs are stored in the CNext + resources + graphic directory of the runtime view. See [CAASmiUserOperationCatalog](../CAASmiUseCases/CAASmiUserOperationCatalog.md) use case.

When CATIA is opened,

  * In the **Start** menu choose **Machining** and click **Surface Machining**
  * Enable the "CAA SMG Tool Bar"
  * Click on the "CAA Plunge operation" command
  * The **first CAA SMG operation** is created and its dialog panel is displayed
  * Set parameters and select an edge
  * Click on "Replay" button. The tool path is created !
  * Click on the "CAA Box operation" command
  * The **second CAA SMG operation** is created and its dialog panel is displayed
  * Set parameters and select geometry
  * Click on "Replay" button. The tool path is created !

  
[Top]
#### Where to Find the Code

The sample is made of a several modules of the CAASurfaceMachiningItf.edu framework:

Windows | `InstallRootDirectory\CAASurfaceMachiningItf.edu\`  
---|---  
Unix | `InstallRootDirectory/CAASurfaceMachiningItf.edu/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

These modules are:

  * CAASmiUserOperationCatalog.m
  * CAASmiUserOperationCommand.m
  * CAASmiUserOperationUI.m
  * CAASmiUserMachFeatureCatalog.m
  * CAASmiUserOperationGeomUI.m
  * CAASmiUserOperationToolPathReplay.m
  * CAASmiConnectUserOperationWithMA.m

[Top]
### In Short

The CAASurfaceMachiningItf.edu sample shows how to add new operations inside _Surface Machining_ Infrastructure, using either an exisiting machining area, either a new user machining feature.

You can now successively go to:

  * [Creating a Surface Machining Operation Startup](../CAASmiUseCases/CAASmiUserOperationCatalog.md)
  * [Customizing the Surface Machining Operation Editor](../CAASmiUseCases/CAASmiUserOperationUI.md)
  * Operation 1: 
    * [Managing Geometry with User Machining Features](../CAASmiUseCases/CAASmiUserOperationWithUserMF.md)
    * [Computing Tool Path with User Machining Features](../CAASmiUseCases/CAASmiUserOperationWithUserMFToolPath.md)
  * Operation 2: 
    * [Managing Geometry with Machining Areas](../CAASmiUseCases/CAASmiUserOperationWithMA.md)
    * [Computing Tool Path with Machining Areas](../CAASmiUseCases/CAASmiUserOperationWithMAToolPath.md)

[Top

* * *
### References

[1] | [Creating an Add-in](../CAAAfrUseCases/CAAAfrSampleAddin.md)  
---|---  
[2] | [Creating Features in an Applicative Container](../CAAOsmUseCases/CAAOsmAppliCont.md)  
[3] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
[Top]  
  
* * *
### History

Version: **1** [Mar 2002] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
