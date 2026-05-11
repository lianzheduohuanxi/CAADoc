---
```vbscript
title: "Creating a Multi Patch NURBS Surface"
category: "use case"
module: "CAATopUseCases"
tags: ["CATICGMObject", "CAATopBopdyChecker", "CAATopBodyChecker", "CAATopologicalOperators", "CATICGMContainer"]
source_file: "Doc/online/CAATopUseCases/CAATopBodyChecker.htm"
converted: "2026-05-11T17:31:50.690774"
```

---
# Geometric Modeler

| 
## Topology

| 
### Using the Body Checker

_How to check the validity of a surface_  
---|---|---  
Use Case  

* * *
### Abstract

A CGM surface which exhibits curvature radii less than the resolution is not valid. The "Body Checker" can be used to determine whether a surface is valid with respect to this criteria. 

  * **What You Will Learn With This Use Case**
  * **The CAATopBodyChecker Use Case**
    * What Does CAATopBodyChecker Do?
    * How to Launch CAATopBopdyChecker
    * Where to Find the CAATopBodyChecker Code
  * **Step-by-Step**
  * **References**

---  

* * *
### What You Will Learn With This Use Case

This use case is intended to help you determine whether a surface is valid in terms of curvature radius. This is done by using the CATBodyChecker.h interface. Today, the rule to check whether a shell self-intersects is not implemented yet (see the interface documentation in the encyclopedia).

[Top]
### The CAATopBodyChecker Use Case

CAATopBodyChecker is a use case of the CAATopologicalOperators.edu framework that illustrates the TopologicalOperators framework capabilities.

[Top]
#### What Does CAATopBodyChecker Do?

The CAATopBodyChecker use case:

  * loads the container and retrieves the body to be checked
  * creates and uses the body checker
  * displays the diagnosis
  * closes the container.

[Top]
#### How to Launch CAATopBodyChecker

To launch CAATopBodyChecker , you will need to set up the build time environment, then compile CAATopBodyChecker .m along with its prerequisites, set up the run time environment, and then execute the use case [1].

To launch CAATopBodyChecker , you will need to set up the build time environment, then compile CAATopBodyChecker .m along with its prerequisites, set up the run time environment, and then execute the use case [1].
With Windows CAATopBodyChecker `e/bodyChecker1.NCGM`

With UNIX CAATopBodyChecker `/u/bodyChecker1.NCGM`

where bodyChecker1.NCGM is the input file delivered in the CAATopologicalOperators.edu/FunctionTests/InputData file.

[Top]
#### Where to Find the CAATopBodyChecker Code

where bodyChecker1.NCGM is the input file delivered in the CAATopologicalOperators.edu/FunctionTests/InputData file.
The CAATopBodyChecker use case is made of a main named CAATopBodyChecker .cpp located in the CAATopBodyChecker .m module of the CAATopologicalOperators.edu framework:

Windows | `InstallRootDirectory\CAATopologicalOperators.edu\`CAATopBodyChecker `.m\`  

The CAATopBodyChecker use case is made of a main named CAATopBodyChecker .cpp located in the CAATopBodyChecker .m module of the CAATopologicalOperators.edu framework:
Windows | `InstallRootDirectory\CAATopologicalOperators.edu\`CAATopBodyChecker `.m\`
Unix | `InstallRootDirectory/CAATopologicalOperators.edu/`CAATopBodyChecker `.m/`  

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are thee main steps in CAATopBodyChecker.cpp: 

  1. Loading the container and retrieving the body to be checked
  2. Creating the CATBodyChecker object 
  3. Displaying the diagnosis
  4. Closing the container

[Top]
#### Loading the container and retrieving the body to be checked

The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular). In this use case, the factory is defined by reading a NCGM file that was previously stored,  the global function `::CATLoadCGMContainer` must be used to retrieve the factory. The body is retrieved by using the CATICGMContainer::FindObjectFromTag method. There is only one body in the container which is loaded. 2353356 is the body tag.

The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular). In this use case, the factory is defined by reading a NCGM file that was previously stored,  the global function `::CATLoadCGMContainer` must be used to retrieve the factory. The body is retrieved by using the CATICGMContainer::FindObjectFromTag method. There is only one body in the container which is loaded. 2353356 is the body tag.
    CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);

    ...
The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular). In this use case, the factory is defined by reading a NCGM file that was previously stored,  the global function `::CATLoadCGMContainer` must be used to retrieve the factory. The body is retrieved by using the CATICGMContainer::FindObjectFromTag method. There is only one body in the container which is loaded. 2353356 is the body tag.
CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
    CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(2353356);   

---  

[Top]
#### Creating and Running the CATBodyChecker

The CATBodyChecker object is created by using the CATBodyChecker::Create static function. To activate all the checker rules, you must specify the BodyChkModeFull mode. So far, only the check of the curvature radius is implemented for curves and surfaces.

    CATBodyChecker * pBodyChecker = CATBodyChecker::Create(piGeomFactory, &topdata, piBodyToBeChecked);
    //
    // b - Specify the Full Mode
CATBodyChecker * pBodyChecker = CATBodyChecker::Create(piGeomFactory, &topdata, piBodyToBeChecked);
    if (NULL != pBodyChecker)

    {
CATBodyChecker * pBodyChecker = CATBodyChecker::Create(piGeomFactory, &topdata, piBodyToBeChecked);
if (NULL != pBodyChecker)
    CATBodyChecker::CheckMode eChkMode = CATBodyChecker::BodyChkModeFull;
    pBodyChecker->SetCheckMode(eChkMode);

    //
    // c - Run the operator
CATBodyChecker::CheckMode eChkMode = CATBodyChecker::BodyChkModeFull;
pBodyChecker->SetCheckMode(eChkMode);
    CATBoolean bRet = FALSE;
    bRet = pBodyChecker->Run();

    ....  

---  

[Top] 
#### Displaying the Diagnosis

All the errors found in the body to be checked are displayed if you have specified the Full Mode. If the light mode is specified, several errors of the same type can be diagnosed.

All the errors found in the body to be checked are displayed if you have specified the Full Mode. If the light mode is specified, several errors of the same type can be diagnosed.
    pBodyChecker->BeginningDiagnosis();
    while( pBodyChecker->NextDiagnosis() )

    {
pBodyChecker->BeginningDiagnosis();
while( pBodyChecker->NextDiagnosis() )
    CATUnicodeString strDiagnosis;
    pBodyChecker->GetDiagnosis(strDiagnosis);

    cout << strDiagnosis.ConvertToChar() << endl;

    }  

---  

cout << strDiagnosis.ConvertToChar() << endl;
This is the message which is displayed on the standard output at execution:

CATTabulatedCylinder[2353360] : Surface has invalid curvature  
Invalid curvature radius found = 0.000403962 <= Allowed [0.001]  
At surface parameter = (PatchU=48, ParamU=373.951; PatchV=1, ParamV=0)

[Top]
#### Closing the Factory

The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.

     _//
     // Closes the container
     //_	
     **::CATCloseCGMContainer**(piGeomFactory);  

---  

[Top]

* * *
### References

[1] |  [ Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] | [Overview of the Topological Operators](CAATopOverview.md)  
[Top]  
---  

* * *
### History

Version: **1** [Aug 2004] | Document created  
---|---  
[Top]  

* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
