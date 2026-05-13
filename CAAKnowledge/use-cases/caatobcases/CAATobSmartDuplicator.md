---
```vbscript
title: "Using the Smart Duplicator"
category: use-case case"
module: "CAATobUseCases"
tags: ["CATICGMContainer", "CAATopologicalOjects", "CATICGMObject", "CAATobSmartDuplicator", "CAATopSmartDuplicator", "CAATopologicalObjects"]
source_file: "Doc/online/CAATobUseCases/CAATobSmartDuplicator.htmmd"
converted: "2026-05-11T17:33:45.823962"
```

---
# Geometric Modeler

|
## Topology

|
###  Using the Smart Duplicator

_How to Modify a "Touched" Topology _
---|---|---
Use Case

* * *
### Abstract

Right after its creation a topology is modifiable. But when the body which contains this topology is frozen, you can no longer modify this topology. With the smart duplicator, you can modify only a part of a body. The part to be modified has to be "touched". This results in a new body sharing the untouched topologies with the initial body. This use case illustrates the smart mechanism with a skin body which has a holed face. Touching the holed face allows you to remove the internal domain to fill in the hole.

  * **What You Will Learn With This Use Case**
  * **The CAATobSmartDuplicator Use Case**
    * What Does CAATobSmartDuplicator Do?
    * How to Launch CAATobSmartDuplicator
    * Where to Find the CAATobSmartDuplicator Code
  * **Step-by-Step**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to help you use the CATSmartBodyDuplicator operator.

[Top]
### The CAATobSmartDuplicator Use Case

CAATobSmartDuplicator is a use case of the CAATopologicalObjects.edu framework that illustrates the NewTopologicalObjects framework capabilities.

[Top]
#### What Does CAATobSmartDuplicator Do?

The CAATobSmartDuplicator use case:

  * loads the container and retrieves the skin body to be duplicated
  * retrieves the holed face and the inner loop of that face
  * specifies the cell to be modified in the smart duplication operation
  * creates a smart duplicator in order to modify the holed face and retrieves the duplicated face associated with the holed face.
  * removes the internal loop in the duplicated face.

[Top]
#### How to Launch CAATobSmartDuplicator

To launch CAATobSmartDuplicator , you will need to set up the build time environment, then compile CAATobSmartDuplicator.m along with its prerequisites, set up the run time environment, and then execute the use case [1].

To launch CAATobSmartDuplicator , you will need to set up the build time environment, then compile CAATobSmartDuplicator.m along with its prerequisites, set up the run time environment, and then execute the use case [1].
With Windows CAATobSmartDuplicator `e/partwithhole.NCGM`

With UNIX CAATobSmartDuplicator `/u/partwithhole.NCGM`

where partwithhole.NCGM is an input file delivered in the CAATopologicalObjects.edu/FunctionTests/InputData file.

[Top]
#### Where to Find the CAATobSmartDuplicator Code

where partwithhole.NCGM is an input file delivered in the CAATopologicalObjects.edu/FunctionTests/InputData file.
The CAATobSmartDuplicator use case is made of a main named CAATopSmartDuplicator.cpp located in the CAATobSmartDuplicator.m module of the CAATopologicalObjects.edu framework:

Windows | `InstallRootDirectory/CAATopologicalObjects.edu/`CAATobSmartDuplicator`.m/`

The CAATobSmartDuplicator use case is made of a main named CAATopSmartDuplicator.cpp located in the CAATobSmartDuplicator.m module of the CAATopologicalObjects.edu framework:
Windows | `InstallRootDirectory/CAATopologicalObjects.edu/`CAATobSmartDuplicator`.m/`
Unix | `InstallRootDirectory/CAATopologicalOjects.edu/`CAATobSmartDuplicator`.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are six main steps in CAATopSmartDuplicator.cpp:

  1. Loading the container and retrieving the body to be checked
  2. Retrieving the holed face
  3. Touching the topology to be modified
  4. Creating a smart duplicated body
  5. Modifying the touched topology
  6. Writing the model and closing the factory

[Top]
#### Loading the container and retrieving the body to be checked

The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular). In this use case, the factory is defined by reading a NCGM file that was previously stored, the global function `::CATLoadCGMContainer` must be used to retrieve the factory. The body is retrieved by using the CATICGMContainer::FindObjectFromTag method. There is only one body in the container which is loaded. 10990 is the body tag.

The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular). In this use case, the factory is defined by reading a NCGM file that was previously stored, the global function `::CATLoadCGMContainer` must be used to retrieve the factory. The body is retrieved by using the CATICGMContainer::FindObjectFromTag method. There is only one body in the container which is loaded. 10990 is the body tag.
    CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);

    ...
The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular). In this use case, the factory is defined by reading a NCGM file that was previously stored, the global function `::CATLoadCGMContainer` must be used to retrieve the factory. The body is retrieved by using the CATICGMContainer::FindObjectFromTag method. There is only one body in the container which is loaded. 10990 is the body tag.
CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
    CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(10990 );

---

The initial body looks something like this:

![Initial Body](images/smartDup1.gif)

[Top]
#### Retrieving the Holed Face

To retrieve the holed face, all the faces of the body are scanned and for each cell, the number of internal domains is computed. For the cells which have internal domains, the domains are scanned. The internal loop is detected by using CATDomain::GetLocation.

To retrieve the holed face, all the faces of the body are scanned and for each cell, the number of internal domains is computed. For the cells which have internal domains, the domains are scanned. The internal loop is detected by using CATDomain::GetLocation.
```vbscript
    for (int k = 1; k < faceList.Size(#)+1; k++)

```

        {
To retrieve the holed face, all the faces of the body are scanned and for each cell, the number of internal domains is computed. For the cells which have internal domains, the domains are scanned. The internal loop is detected by using CATDomain::GetLocation.
for (int k = 1; k < faceList.Size(#)+1; k++)
    	CATCell * pLocalCell = faceList[k];
```vbscript
            if (pLocalCell && pLocalCell->GetNbInternalDomains(#) > 0)

```

            {
```vbscript
for (int k = 1; k < faceList.Size(#)+1; k++)
CATCell * pLocalCell = faceList[k];
if (pLocalCell && pLocalCell->GetNbInternalDomains(#) > 0)
                int NbDomains=pLocalCell->GetNbDomains(#);
                for(int j=1;j<=NbDomains;j++)
```

                {
```vbscript
if (pLocalCell && pLocalCell->GetNbInternalDomains(#) > 0)
int NbDomains=pLocalCell->GetNbDomains(#);
for(int j=1;j<=NbDomains;j++)
                    CATDomain *pDomain=pLocalCell->GetDomain(j);
                    CATLocation Location=pDomain->GetLocation(#);
                    if(Location==CATLocationInner)
```

                    {
CATDomain *pDomain=pLocalCell->GetDomain(j);
CATLocation Location=pDomain->GetLocation(#);
if(Location==CATLocationInner)
                        pInnerLoop=pDomain;                    // the inner loop
                        holedFace = (CATFace *) faceList[k] ;  // the holed face
                        break;

                    }
                }
            }
        }

---

[Top]
#### Touching the Topology to be Modified

The CATTopology::Touch method is used to specify which topology is going to be modified.

     holedFace->Touch(piBody);

---

[Top]
#### Creating a Smart Duplicated Body

First, you must create an empty body from CATGeoFactory. The CATSmartBodyDuplicator operator is created from this new body. It must be run.

First, you must create an empty body from CATGeoFactory. The CATSmartBodyDuplicator operator is created from this new body. It must be run.
     CATBody * copBody = piGeomFactory->CreateBody(#);
        CATSmartBodyDuplicator * smartDuplicator =
            copBody->CreateSmartDuplicator(piBody, topdata);
        if (smartDuplicator == NULL) return (1);
        smartDuplicator->Run(#);
        CATFace * duplicatedFace = (CATFace *)smartDuplicator->GetDuplicatedCell(holedFace);

---
```vbscript
if (smartDuplicator == NULL) return (1);
smartDuplicator->Run(#);
CATFace * duplicatedFace = (CATFace *)smartDuplicator->GetDuplicatedCell(holedFace);
The cell which has been initially touched is retrieved by using the CATSmartBodyDuplicator::GetDuplicatedCell method.

```

[Top]
#### Modifying the Touched Topology

The face inner loop is retrieved by scanning its domains. A domain which is an internal domain is removed.

The face inner loop is retrieved by scanning its domains. A domain which is an internal domain is removed.
     int NbD=duplicatedFace->GetNbDomains(#);
        for(int j=1;j<=NbD;j++)

        {
int NbD=duplicatedFace->GetNbDomains(#);
for(int j=1;j<=NbD;j++)
            CATDomain *pDom=duplicatedFace->GetDomain(j);
            CATLocation Loc=pDom->GetLocation(#);
            if(Loc==CATLocationInner)

            {
CATDomain *pDom=duplicatedFace->GetDomain(j);
CATLocation Loc=pDom->GetLocation(#);
if(Loc==CATLocationInner)
               duplicatedFace->RemoveDomain(pDom);

            }
        }

---

[Top]
#### Writing the Model and Closing the Factory

To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved.

The use case ends with the closure of the geometry factory, done by the `::CATCloseCGMContainer` global function.

To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved.
The use case ends with the closure of the geometry factory, done by the `::CATCloseCGMContainer` global function.
     if(1==toStore)

     {
    #ifdef _WINDOWS_SOURCE
```vbscript
if(1==toStore)
       ofstream filetowrite(pfileName, ios::binary ) ;
```

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

     _//
     // Closes the container
     //_
     **::CATCloseCGMContainer**(piGeomFactory);

---
The resulting body looks something like this:
![Resulting Body](images/smartDup2.gif)

[Top]

* * *
### References

[1] |  [ Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[Top]
---

* * *
### History

Version: **1** [Jan 2009] | Document created
---|---
[Top]

* * *

_Copyright 2009, Dassault Systmes. All rights reserved._
