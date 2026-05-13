---
```vbscript
title: "Creating Fillets"
category: use-case case"
module: "CAATopUseCases"
tags: ["CAAGemBrowser", "CATICGMObject", "CAAATopAllFillets", "CAATopConstantFillets", "CAATopAllFillet", "CAATopRollingEdges", "CAATopAllFillets", "CAATopologicalOperators", "CAATopFillet", "CAATopVariableFillets"]
source_file: "Doc/online/CAATopUseCases/CAATopAllFillets.htmmd"
converted: "2026-05-11T17:31:50.684779"
```

---
# Geometric Modeler

|
## Topology

|
### Creating Fillets

_How to create constant and variable radius fillets_
---|---|---
Use Case

* * *
### Abstract

This use case explains how to create constant fillets, variable fillets and fillets with rolling edges.

  * **What You Will Learn With This Use Case**
  * **The CAAATopAllFillets Use Case**
    * What Does CAATopAllFillets Do?
    * How to Launch CAATopAllFillet
    * Where to Find the CAATopFillet Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to help you use fillets in geometric modeler applications.

[Top]
### The CAATopAllFillets Use Case

CAATopAllFillets is a use case of the CAATopologicalOperators.edu framework that illustrates TopologicalOperators framework capabilities.

[Top]
#### What Does CAATopAllFillets Do?

CAATopAllFillets is a use case of the CAATopologicalOperators.edu framework that illustrates TopologicalOperators framework capabilities.
CAATopAllFillets creates two solid cuboids, performs a boolean union of the cubes, then creates fillets on the resulting solid.

 The CAATopConstantFillets function which is defined in the CAATopConstantFillets.cpp folder creates a constant fillet along the edges common to both cubes.

CAATopAllFillets creates two solid cuboids, performs a boolean union of the cubes, then creates fillets on the resulting solid.
The CAATopConstantFillets function which is defined in the CAATopConstantFillets.cpp folder creates a constant fillet along the edges common to both cubes.
 The CAATopRollingEdges function which is defined in the  CAATopRollingEdges.cpp folder creates a fillet along the common edges and specifies rolling edges.
 The CAATopVariableFillets function which is defined in the CAATopVariableFillets.cpp folder creates a variable radius fillet on one edge of the solid.

[Top]
#### How to Launch CAATopAllFillets

The CAATopVariableFillets function which is defined in the CAATopVariableFillets.cpp folder creates a variable radius fillet on one edge of the solid.
To launch CAATopAllFillets, you will need to set up the build time environment, then compile CAATopAllFillets.m along with its prerequisites, set up the run time environment, and then execute the use case [1].

```vbscript
If you simply type CAATopAllFillets with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example:

```

With Windows `CAATopAllFillets`` e/Fillets.NCGM`

With UNIX `CAATopAllFillets`` /u/Fillets.NCGM`

This NCGM file can be displayed using the CAAGemBrowser use case.

[Top]
#### Where to Find the CAATopAllFillets Code

This NCGM file can be displayed using the CAAGemBrowser use case.
The CAATopAllFillets use case is made of a main named CAATopAllFillets.cpp located in the CAATopAllFillets.m module of the CAATopologicalOperators.edu framework:

Windows | `InstallRootDirectory/CAATopologicalOperators.edu/CAATopAllFillets.m/`

The CAATopAllFillets use case is made of a main named CAATopAllFillets.cpp located in the CAATopAllFillets.m module of the CAATopologicalOperators.edu framework:
Windows | `InstallRootDirectory/CAATopologicalOperators.edu/CAATopAllFillets.m/`
Unix | `InstallRootDirectory/CAATopologicalOperators.edu/CAATopAllFillets.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are six steps in CAATopAllFillets.cpp:

  1. Creating the geometry factory
  2. Creating the solid cuboids
  3. Performing a boolean union on the cuboids
  4. Creating a constant fillet around the edges common to both cubes
  5. Creating a constant fillet by specifying rolling edges
  6. Creating a variable radius fillet.
  7. Writing the model and closing the Container

[Top]
#### Creating the Geometry Factory

The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject. This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.

The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject. This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.
    CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**(#) ;
```vbscript
    if (NULL==piGeomFactory) return (1);

```

---

[Top]
#### Creating the solid cuboids

See [2] which illustrates how to create a solid cuboid.

[Top]
#### Performing a boolean union on the cuboids

See also [2].

[Top]
#### Creating a constant radius fillet

See also [2].
To create a constant radius fillet, you must:

  1. define your CATDynFilletRadius.

         double * ratio= NULL;
         CATDynFilletRadius * pRadius = new CATDynFilletRadius(3.,    // radius value
                     NULL,
                     ratio,
                     NULL); __

---

ratio,
NULL); __
The arguments two, three and four of the constructor are only to be specified when the fillet to be created is of variable radius. The cells to be filleted with a constant radius are specified in the CATDynEdgeFilletRibbon constructor.
  2. define the CATDynEdgeFilletRibbon object whereby you specify what cells are to be filleted. If you create a constant radius fillet, the list to be passed as the second argument of the CATDynEdgeFilletRibbon is a single item list.

         CATLISTP(CATDynFilletRadius) listRadius;
         listRadius.Append(pRadius);
         CATDynEdgeFilletRibbon * pRibbon = new CATDynEdgeFilletRibbon(listEdges, listRadius);

---
```vbscript
CATLISTP(CATDynFilletRadius) listRadius;
listRadius.Append(pRadius);
CATDynEdgeFilletRibbon * pRibbon = new CATDynEdgeFilletRibbon(listEdges, listRadius);
  3. if need be, set the parameters of the CATDynFilletRibbon

         pRibbon ->SetSegmentationMode(CATDynTrim);

```

---
3. if need be, set the parameters of the CATDynFilletRibbon
pRibbon ->SetSegmentationMode(CATDynTrim);
  4. create the CATDynFillet operator by using the CATCreateDynFillet operator

         CATDynFillet * pFilletOp1 = CATCreateDynFillet(iFactory,iTopData,iBody);

---
4. create the CATDynFillet operator by using the CATCreateDynFillet operator
CATDynFillet * pFilletOp1 = CATCreateDynFillet(iFactory,iTopData,iBody);
  5. append the CATDynEdgeFilletRibbon to the operator instance

         pFilletOp1 ->Append(pRibbon);

---

[Top]
#### Creating a constant radius fillet with rolling edges

To create a variable radius fillet, you must:

To create a variable radius fillet, you must:
  1. proceed as you would do for a constant radius fillet.
  2. in the CATDynEdgeFilletRibbon constructor, specify the list of rolling edges as well as the fillet behavior (CATDynRolling).

         CATDynEdgeFilletRibbon * pRibbon = new CATDynEdgeFilletRibbon(listEdges, listRadius,
                     CATBody::CATEdgePropagAuto,
                     listRollingEdges,   // the rolling edges
                     CATDynRolling);

---

[Top]
####
#### Creating a variable radius fillet

To create a variable radius fillet, you must:

  1. define the CATDynFilletRadius necessary to define the fillet shape. You must specify:
     *  the radius value (in mm),
     * the pointer to the cell on which the fillet is to be applied,
     *  the pointer to the ratio of the edge length which defines the point where the radius is defined
     *  and the pointer to the tangency angle at the point where the radius is specified. Note that either a NULL pointer or a NULL angle are supported so far. If a NULL pointer is passed, the radius law is not constrained and the resulting fillet looks something like a "linear" one. If a NULL value is passed for the extremities, the resulting fillet looks something like a "cubic" one.

    double * ratio0= new double(0.0);
    CATDynFilletRadius * pRadius0 = new CATDynFilletRadius(4.,  // radius value
                listCells[2],
                ratio0,
                NULL);  // "free" tangency at this extremity

    ...
CATDynFilletRadius * pRadius0 = new CATDynFilletRadius(4.,  // radius value
listCells[2],
ratio0,
NULL);  // "free" tangency at this extremity
    double * ratio1= new double(0.25);
    CATDynFilletRadius * pRadius1 = new CATDynFilletRadius(0.2,  // radius value
                listCells[2],
                ratio1,
                NULL);  // "free" tangency for this location

---

ratio1,
NULL);  // "free" tangency for this location
The second and third arguments of the constructor must be specified when the fillet to be created is of variable radius.
  2. define the CATDynEdgeFilletRibbon object whereby you specify the list of radii to be applied along the edge to be filleted. The list of edges to be filleted is to be set to NULL.

         CATLISTP(CATDynFilletRadius) listRadius;
         listRadius.Append(pRadius0);
         listRadius.Append(pRadius1);
         listRadius.Append(pRadius2);
         listRadius.Append(pRadius3);

         // Create the CATDynEdgeFilletRibbon
         //
listRadius.Append(pRadius2);
listRadius.Append(pRadius3);
         CATDynEdgeFilletRibbon * pRibbon = new CATDynEdgeFilletRibbon(NULL, listRadius);

---
CATDynEdgeFilletRibbon * pRibbon = new CATDynEdgeFilletRibbon(NULL, listRadius);
  3. if need be, set the parameters of the CATDynFilletRibbon

         pRibbon ->SetSegmentationMode(CATDynTrim);

---
3. if need be, set the parameters of the CATDynFilletRibbon
pRibbon ->SetSegmentationMode(CATDynTrim);
  4. create the CATDynFillet operator by using the CATCreateDynFillet operator

         CATDynFillet * pFilletOp1 = CATCreateDynFillet(iFactory,iTopData,iBody);

---
4. create the CATDynFillet operator by using the CATCreateDynFillet operator
CATDynFillet * pFilletOp1 = CATCreateDynFillet(iFactory,iTopData,iBody);
  5. append the CATDynEdgeFilletRibbon to the operator instance

         pFilletOp1 ->Append(pRibbon);

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

[Top]

* * *
### In Short

To create fillets, you must specify a list of radii as well as a list of edges to be filleted. For a constant radius, the list of radii contains a single item that you can apply to one or more edges. When creating a variable fillet, you must specify the list of radii. The edge to be filleted is then specified in the radius definition.

[Top]

* * *
### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] | [Overview of the Topological Operators](CAATopOverview.md)
[Top]

* * *
### History

Version: **1** [March 2002] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
