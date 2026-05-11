---
```vbscript
title: "Computing the Area of a CATFace and the Length of a CATEdge"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CAADoc", "CATICGMDynMassProperties3D", "CAAGMProperties", "CATICGMObject", "CATICGMDynCreateMassProperties3D", "CAAGMModelGemBrowser", "CAAGMOperatorsProperties", "CATICGMSolidSphere", "CAATopProperties"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopProperties.htm"
converted: "2026-05-11T17:33:49.289425"
```

---
tags: ["CAAGMOperatorsInterfaces", "CAADoc", "CATICGMDynMassProperties3D", "CAAGMProperties", "CATICGMObject", "CATICGMDynCreateMassProperties3D", "CAAGMModelGemBrowser", "CAAGMOperatorsProperties", "CATICGMSolidSphere", "CAATopProperties"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopProperties.htm"
converted: "2026-05-11T17:33:49.289425"
Computing the Area of a CATFace and the Length of a CATEdge

---
converted: "2026-05-11T17:33:49.289425"
Computing the Area of a CATFace and the Length of a CATEdge
Use Case
Abstract The CATICGMDynMassProperties3D class provides services whereby you can calculate the properties of a body as well as the properties of the cells making up the body. This use case explains how to calculate the area of a CATFace along with the length of a CATEdge.

    * What You Will Learn With This Use Case
    * The CAAGMOperatorsProperties Use Case
      * What Does CAAGMOperatorsProperties Do?
      * How to Launch CAAGMOperatorsProperties
      * Where to Find the CAGMOperatorsProperties Code
    * Step-by-Step
    * In Short
    * References
---
What You Will Learn With This Use Case In this use case, you learn how to compute the area of a face as well as the length of an edge. The CAAGMOperatorsProperties Use Case CAAGMOperatorsProperties is a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates GMOperatorsInterfaces framework capabilities. What Does CAAGMOperatorsProperties Do? This use case:
    1. Creates the geometric factory.
    2. Creates a solid sphere.
    3. Computes the area of each face.
    4. Computes the length of each edge.
    5. Writes the model and closes the container.
How to Launch CAAGMOperatorsProperties To launch CAAGMOperatorsProperties, you will need to set up the build time environment, then compile CAAGMOperatorsProperties.m along with its prerequisites, set up the run time environment, and then execute the use case [1]. If you simply type CAAGMOperatorsProperties with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example: `CAAGMOperatorsProperties e/Properties.NCGM` This NCGM file can be displayed using the CAAGMModelGemBrowser use case. Where to Find the CAAGMOperatorsProperties Code The CAAGMOperatorsProperties use case is made of a main named CAATopProperties.cpp located in the CAAGMOperatorsProperties.m module of the GMOperatorsInterfaces framework: `InstallRootFolder\CAADoc\CAAGMOperatorsInterfaces.edu\CAAGMProperties.m\` where `InstallRootFolder` [1] is the folder where the API CD-ROM is installed. Step-by-Step The program:
    1. Creates the Geometry Factory
    2. Creates the Sphere (CATICGMSolidSphere)
    3. Computes the Area of Each Face
    4. Computes the Length of Each Edge
    5. Writes the Model and Closes the Container
Creating the Geometry Factory The geometry factory (CATGeoFactory) creates and manages all the `CATICGMObject`: it creates the points, curves, surfaces and bodies and remove them. The CATGeoFactory creation itself is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.

    CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**() ;
```vbscript
    if (NULL==piGeomFactory) return (1);

```

Creating a Sphere The CATICGMSolidSphere creation follows the scheme of all topological operators. You must create the operator by using the CATCGMCreateSolidSphere global function, then run it and get the resulting body.

    CATMathPoint p1(0,0,0);  // the sphere center

    CATICGMSolidSphere * pSphereOpe = ::CATCGMCreateSolidSphere(piGeomFactory,

         &topdata,
CATMathPoint p1(0,0,0);  // the sphere center
CATICGMSolidSphere * pSphereOpe = ::CATCGMCreateSolidSphere(piGeomFactory,
         p1,
         100.0); // the radius

    ...
CATICGMSolidSphere * pSphereOpe = ::CATCGMCreateSolidSphere(piGeomFactory,
p1,
100.0); // the radius
    pSphereOpe -> Run();
    CATBody * pBodySphere = pSphereOpe -> GetResult();

    ...

pSphereOpe -> Run();
CATBody * pBodySphere = pSphereOpe -> GetResult();
Computing the Area of a CATFace To retrieve a face area, you must:

    * Use the CATICGMDynCreateMassProperties3D function and pass as its argument the face whose area is to be calculated.
    * Apply the GetWetArea method to the returned CATICGMDynMassProperties3D.

Computing the Area of a CATFace To retrieve a face area, you must:
```vbscript
    for (int i=1;(i <= nbFaces)  ;i++)

```

    {
```vbscript
for (int i=1;(i <= nbFaces)  ;i++)
      CATFace * pFace = (CATFace *)listFaces[i];
      CATICGMDynMassProperties3D * pDynMassOpe0 =
             CATCGMDynCreateMassProperties3D(pFace ) ;
```vbscript
      if (NULL == pDynMassOpe0)
```

```

      {
        ::CATCloseCGMContainer(piGeomFactory);
CATICGMDynMassProperties3D * pDynMassOpe0 =
CATCGMDynCreateMassProperties3D(pFace ) ;
```vbscript
if (NULL == pDynMassOpe0)
        return (1);

```

      }
      // Expected area 4*PI*(R**2)/4
return (1);
      cout << "Face " << i << " area: " << pDynMassOpe0->GetWetArea() << endl;
      delete pDynMassOpe0; pDynMassOpe0=NULL;

     }

cout << "Face " << i << " area: " << pDynMassOpe0->GetWetArea() << endl;
delete pDynMassOpe0; pDynMassOpe0=NULL;
Computing the Length of a CATEdge To retrieve a face area, you must:

    * Use the CATCGMDynCreateMassProperties3D function and pass as its argument the edge whose length is to be calculated.
    * Apply the GetLength method to the returned CATICGMDynMassProperties3D.

Computing the Length of a CATEdge To retrieve a face area, you must:
```vbscript
    for (i=1;(i <= nbEdges)  ;i++)

```

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
      cout << "Edge " << i << " length: " << pDynMassOpe1->GetLength() << endl;
      cout << pEdge->GetPersistentTag() << endl;
      pDynMassOpe1->Release(); pDynMassOpe1=NULL;

     }

cout << "Edge " << i << " length: " << pDynMassOpe1->GetLength() << endl;
cout << pEdge->GetPersistentTag() << endl;
pDynMassOpe1->Release(); pDynMassOpe1=NULL;
This is the length with is displayed on the standard output: ![Edge 21](images/CAACgmTopedge21.gif)
Edge 3 length: 157.08
Edge 2 length: 157.08

![Edge 23](images/CAACgmTopedge23.gif)
This is the length with is displayed on the standard output: ![Edge 21](images/CAACgmTopedge21.gif)
Edge 3 length: 157.08
Edge 2 length: 157.08
Edge 5 length: 157.08
Edge 6 length: 157.08

![Edge 25](images/CAACgmTopedge25.gif)
Edge 5 length: 157.08
Edge 6 length: 157.08
Edge 1 length: 314.159
Edge 4 length: 314.159
Writing the Model and Closing the Container Before ending, we must first release the software configuration.

    // Releases the configuration
Edge 1 length: 314.159
Edge 4 length: 314.159
Writing the Model and Closing the Container Before ending, we must first release the software configuration.
        pConfig->Release();

To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved. The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.

    if(1==toStore)

     {
    #ifdef _WINDOWS_SOURCE
To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved. The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.
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
     // Close the container
     //

     **::CATCloseCGMContainer**(piGeomFactory);

In Short This use case explains how to compute the area of a face and the length of an edge by using the CATICGMDynMassProperties3D class. References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
History Version: **1** [Feb 2002] | Document created
---|---
