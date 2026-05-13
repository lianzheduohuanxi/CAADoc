---
```vbscript
title: "An Introduction to Geometric Modeler Use Cases"
category: use-case case"
module: "CAACgmModel"
tags: ["CATICGMContainer", "CATICGMObject", "CAAGMModelGemBrowser"]
source_file: "Doc/online/CAACgmModel/CAACgmUcGMModelUseCaseOverw.htmmd"
converted: "2026-05-11T17:33:48.319640"
```

---
# An Introduction to Geometric Modeler Use Cases

---
Use Case
## Abstract

This article describe the code portions which are common to most geometric modeler use cases. The purpose of use cases is to illustrate the use of CGM APIs and focus on the way to use these APIs in a geometric modeler environment. Use cases require input data which is:
    * Either created directly in the use case.
    * Or retrieved from an NCGM file.
This article explains how to create data from the geometry factory or retrieve special data from an NCGM container. Both operations are widely used in geometric modeler use cases. Results produced by use cases can be stored in an NCGM container which is displayable by using the CAAGMModelGemBrowser use case.
    * Creating Data Directly from the Geometry Factory
    * Retrieving Data from a Loaded NCGM Container
    * Writing the Model and Closing the Factory
    * In Short
---
## Creating Data Directly from the Geometry Factory

To create data directly, you must:

To create data directly, you must:
    1. Create the CATGeoFactory. The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular). This creation is done by using the global function `::CATCreateCGMContainer`.

           CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**(#)

    2. Create the geometric objects by using the geometry factory, for example:

           CATLine * piLine = piGeomFactory->**CreateLine**(CATMathO,     // (0,0,0) math point
                                                        CATMathVector(1.,1.,0.) );

           ...
2. Create the geometric objects by using the geometry factory, for example:
CATLine * piLine = piGeomFactory->**CreateLine**(CATMathO,     // (0,0,0) math point
CATMathVector(1.,1.,0.) );
           CATCylinder* piCylinder = piGeomFactory->**CreateCylinder**(CATMathOIJK, // canonical axis system
                                                                   radius,
                                                                   axisStart,
                                                                   axisEnd,
                                                                   angleStart,
                                                                   angleEnd);

**Note** : Although geometric objects are handled by the mean of interfaces, such as `CATCartesianPoint`, `CATLine`, or `CATBody`, the pointers on these objects must not be released. In fact, they are released at the closure of the factory (the `CATCloseCGMContainer` global function).
## Retrieving Data from a Loaded NCGM Container

angleEnd);
To retrieve input data from an already existing container, you must:

    1. Retrieve the CATGeoFactory from the input file by using the global function `::CATLoadCGMContainer`. In most use cases the input file is specified as an argument of the main program, so that the code to load it looks something like this:

           char *pFileName = NULL;
           pFileName = iArgv[1];

           ifstream filetoread(pFileName, ios::binary ) ;

           CATGeoFactory* piGeomFactory = **::CATLoadCGMContainer**(filetoread)

    2. Retrieve specific objects by using the CATICGMContainer::FindObjectFromTag method. This method requires a prerequisite knowledge of the persistent tag born by the object to be retrieved.

           CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(667827);

    3. You can also retrieve objects with a given type by scanning the container.

           cout << "Scanning the geometry... " << endl;
           CATGeometry * piCurG = NULL;
           CATULONG32 curtag;
           for (piCurG = piGeomFactory->Next(NULL,CATPLineType);
                piCurG != NULL;
```vbscript
                piCurG = piGeomFactory->Next(piCurG))

```

           {
           **// Find the PLine from its persistent tag
           //**
piCurG != NULL;
piCurG = piGeomFactory->Next(piCurG))
```vbscript
           curtag = piCurG->GetPersistentTag(#);
```

           CATICGMObject * piCGMObj = piGeomFactory->FindObjectFromTag(curtag);

           ...
           }
## Writing the Model and Closing the Factory

CATICGMObject * piCGMObj = piGeomFactory->FindObjectFromTag(curtag);
To save the use case result in a file, the `::CATSaveCGMContainer` global function is used. Notice that in most use cases, the save is conditioned by an input parameter representing the file inside which the model must be saved.

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

    * In GM use cases, input data can be created by using the geometry factory APIs or by loading an NCGM container.
    * GM use cases end by saving the result into an NCGM container and by closing the factory.
## History

Version: **1** [Jan 2007] | Document created
---|---
