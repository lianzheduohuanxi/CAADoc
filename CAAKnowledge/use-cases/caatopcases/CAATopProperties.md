---
```vbscript
title: "Computing the Area of a CATFace and the Length of a CATEdge"
category: use-case case"
module: "CAATopUseCases"
tags: ["CAAGemBrowser", "CAATopologicalOperators", "CATICGMObject", "CAATopProperties"]
source_file: "Doc/online/CAATopUseCases/CAATopProperties.htmmd"
converted: "2026-05-11T17:31:50.757850"
```

---
# Geometric Modeler

|
## Topology

|
### Computing the Area of a CATFace and the Length of a CATEdge

_How to calculate the area of a face and the length of an edge_
---|---|---
Use Case

* * *
### Abstract

The CATDynMassProperties3D class provides services whereby you can calculate the properties of a body as well as the properties of the cells making up the body. This use case explains how to calculate the area of a CATFace along with the length of a CATEdge

  * **What You Will Learn With This Use Case**
  * **The CAATopProperties Use Case**
    * What Does CAATopProperties Do?
    * How to Launch CAATopProperties
    * Where to Find the CATopProperties Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

In this use case, you learn how to compute the area of a face as well as the length of an edge.

[Top]
### The CAATopProperties Use Case

CAATopProperties is a use case of the CAATopologicalOperators.edu framework that illustrates TopologicalOperators framework capabilities.

[Top]
#### What Does CAATopProperties Do?

CAATopProperties is a use case of the CAATopologicalOperators.edu framework that illustrates TopologicalOperators framework capabilities.
This use case:

  1. creates the geometric factory
  2. creates a solid sphere
  3. computes the area of each face
  4. computes the length of each edge
  5. writes the model and closes the container.

[Top]
#### How to Launch CAATopProperties

5. writes the model and closes the container.
To launch CAATopProperties, you will need to set up the build time environment, then compile CAATopProperties.m along with its prerequisites, set up the run time environment, and then execute the use case [1].

```vbscript
If you simply type CAATopProperties with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example:

```

With Windows `CAATopProperties`` e/Properties.NCGM`

With UNIX `CAATopProperties`` /u/Properties.NCGM`

This NCGM file can be displayed using the CAAGemBrowser use case.

[Top]
#### Where to Find the CAATopProperties Code

The CAATopProperties use case is made of a main named CAATopProperties.cpp located in the CAATopProperties.m module of the CAATopologicalOperators.edu framework:

The CAATopProperties use case is made of a main named CAATopProperties.cpp located in the CAATopProperties.m module of the CAATopologicalOperators.edu framework:
Windows | `InstallRootDirectory/CAATopologicalOperators.edu/CAATopProperties.m/`

The CAATopProperties use case is made of a main named CAATopProperties.cpp located in the CAATopProperties.m module of the CAATopologicalOperators.edu framework:
Windows | `InstallRootDirectory/CAATopologicalOperators.edu/CAATopProperties.m/`
Unix | `InstallRootDirectory/CAATopologicalOperators.edu/CAATopProperties.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
The program:

  1. Creates the Geometry Factory
  2. Creates the sphere (CATSolidSphere)
  3. Computes the area of each face
  4. Computes the length of each edge
  5. Writes the Model and Closes the Container

[Top]
#### Creating the Geometry Factory

5. Writes the Model and Closes the Container
The geometry factory (CATGeoFactory) creates and manages all the `CATICGMObject` : it creates the points, curves, surfaces and bodies and remove them.

The CATGeoFactory creation itself is done by the global function `::CATCreateCGMContainer`.

Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.

    CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**(#) ;
```vbscript
    if (NULL==piGeomFactory) return (1);

```

---

[Top]
#### Creating a sphere

The CATSolidSphere creation follows the scheme of all topological operators. You must create the operator by using the CATCreateSolidSphere global function, then run it and get the resulting body.

The CATSolidSphere creation follows the scheme of all topological operators. You must create the operator by using the CATCreateSolidSphere global function, then run it and get the resulting body.
    CATMathPoint p1(0,0,0);  // the sphere center

    CATSolidSphere * pSphereOpe = ::CATCreateSolidSphere(piGeomFactory,

         &topdata,
CATMathPoint p1(0,0,0);  // the sphere center
CATSolidSphere * pSphereOpe = ::CATCreateSolidSphere(piGeomFactory,
         p1,
         100.0); // the radius

    ...
CATSolidSphere * pSphereOpe = ::CATCreateSolidSphere(piGeomFactory,
p1,
100.0); // the radius
    pSphereOpe -> Run(#);
    CATBody * pBodySphere = pSphereOpe -> GetResult(#);

    ...

---
pSphereOpe -> Run(#);
CATBody * pBodySphere = pSphereOpe -> GetResult(#);
__

[Top]
#### Computing the area of a CATFace

To retrieve a face area, you must:

  * use the CATDynCreateMassProperties3D function and pass as its argument the face whose area is to be calculated
  * apply the GetWetArea method to the returned CATDynMassProperties3D.

    for (int i=1;(i <= nbFaces)  ;i++)
     {
```vbscript
for (int i=1;(i <= nbFaces)  ;i++)
         CATFace * pFace = (CATFace *)listFaces[i];
         CATDynMassProperties3D * pDynMassOpe0 =
             CATDynCreateMassProperties3D(pFace ) ;
```vbscript
         if (NULL == pDynMassOpe0)
```

```

         {
          ::CATCloseCGMContainer(piGeomFactory);
CATDynMassProperties3D * pDynMassOpe0 =
CATDynCreateMassProperties3D(pFace ) ;
```vbscript
if (NULL == pDynMassOpe0)
           return (1);

```

         }
         // Expected area 4*PI*(R**2)/4
return (1);
         cout << "Face " << i << " area: " << pDynMassOpe0->GetWetArea(#) << endl;
         delete pDynMassOpe0; pDynMassOpe0=NULL;

     }

---

[Top]
#### Computing the length of a CATEdge

To retrieve a face area, you must:

  * use the CATDynCreateMassProperties3D function and pass as its argument the edge whose length is to be calculated
  * apply the GetLength method to the returned CATDynMassProperties3D.

    for (i=1;(i <= nbEdges)  ;i++)
     {
```vbscript
for (i=1;(i <= nbEdges)  ;i++)
         CATEdge * pEdge = (CATEdge *)listEdges[i];
         if (pEdge == NULL) return 1;
         CATDynMassProperties3D * pDynMassOpe1 =
             CATDynCreateMassProperties3D(pEdge ) ;
```vbscript
         if (NULL == pDynMassOpe1)
```

```

         {
             ::CATCloseCGMContainer(piGeomFactory);
CATDynMassProperties3D * pDynMassOpe1 =
CATDynCreateMassProperties3D(pEdge ) ;
```vbscript
if (NULL == pDynMassOpe1)
             return (1);

```

         }

return (1);
         cout << "Edge " << i << " length: " << pDynMassOpe1->GetLength(#) << endl;
         cout << pEdge->GetPersistentTag(#) << endl;
         delete pDynMassOpe1; pDynMassOpe1=NULL;

     }

---

This is the length with is displayed on the standard output:

![](images/edge21.gif)
This is the length with is displayed on the standard output:
Edge 3 length: 157.08
Edge 2 length: 157.08

![](images/edge23.gif)
Edge 3 length: 157.08
Edge 2 length: 157.08
Edge 5 length: 157.08
Edge 6 length: 157.08

![](images/edge25.gif)
Edge 5 length: 157.08
Edge 6 length: 157.08
Edge 1 length: 314.159
Edge 4 length: 314.159

[Top]
#### Writing the Model and Closing the Factory

Before ending, we must first release the software configuration.

    // Releases the configuration
        pConfig->Release(#);

---

pConfig->Release(#);
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

     //
     // Close the container
     //

     **::CATCloseCGMContainer**(piGeomFactory);

---

[Top]

* * *
### In Short

This use case explains how to compute the area of a face and the length of an edge by using the CATDynMassProperties3D class.

[Top]

* * *
### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[Top]

* * *
### History

Version: **1** [Feb 2002] | Document created
---|---
[Top]

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
