---
title: "An Introduction to Geometric Modeler Use Cases"
category: "use case"
module: "CAACgmModel"
tags: ["CAAGMOperatorsOverview", "CATICGMContainer", "CAAGMOperatorsChamfer", "CATICGMObject", "CAAGMModelGemBrowser"]
source_file: "Doc/online/CAACgmModel/CAACgmUcGMUseCases.md"
converted: "2026-05-11T17:33:48.329658"
---
# About Geometric Modeler Use Cases  
  
---  
Use Case  
## Abstract

The purpose of geometric modeler use cases is to explain how to use CGM public APIs.  Geometric modeler use cases are intended to be used in a purely geometric modeler environment. The NCGM format is specifically dedicated to geometric modeler data. Most use cases require input data which are either created directly in the use case or retrieved from an NCGM file. Most use cases share the same code structure, are launched the same way and use operators sharing the same behavior. All this is described in this article. 
    * Use Case Code Structure
      * Creating Data Directly from the Geometry Factory
      * Retrieving Data from a Loaded NCGM Container
      * Writing the Model and Closing the Factory
    * Building and Launching a Use Case
    * Using Geometric Modeler Operators
    * Viewing Use Case Results  
---  
## Use Case Code Structure 

There are different steps in a use case:

    1. Data creation from the geometry factory or data loading from an input NCGM file
    2. Data creation or operator creation, option setting, run, access to the generated result
    3. Model saving/data writing.
### Creating Data Directly from the Geometry Factory

To create data directly, you must:

    1. Create the CATGeoFactory. The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular). This creation is done by using the global function `::CATCreateCGMContainer`. 
           
           CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**()

    2. Create the geometric objects by using the geometry factory, for example: 
           
           CATLine * piLine = piGeomFactory->**CreateLine**(CATMathO,     // (0,0,0) math point
                                                        CATMathVector(1.,1.,0.) );
           ...
           CATCylinder* piCylinder = piGeomFactory->**CreateCylinder**(CATMathOIJK, // canonical axis system
                                                                   radius,
                                                                   axisStart,
                                                                   axisEnd,
                                                                   angleStart,
                                                                   angleEnd);

**Note** : Although geometric objects are handled by the mean of interfaces, such as `CATCartesianPoint`, `CATLine`, or `CATBody`, the pointers on these objects must not be released. In fact, they are released at the closure of the factory (the `CATCloseCGMContainer` global function).
### Retrieving Data from a Loaded NCGM Container

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
                piCurG = piGeomFactory->Next(piCurG)) 
           {
           **// Find the PLine from its persistent tag
           //**
           curtag = piCurG->GetPersistentTag();
           CATICGMObject * piCGMObj = piGeomFactory->FindObjectFromTag(curtag);
           ...
           }
### Writing the Model and Closing the Factory

To save the use case result in a file, the `::CATSaveCGMContainer` global function is used. Notice that in most use cases, the save is conditioned by an input parameter representing the file inside which the model must be saved.

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
    
     //
     // Closes the container
     //
     **::CATCloseCGMContainer**(piGeomFactory);
## Using Geometric Modeler Operators

Operators are objects to be used not only for 3D modeling operations but also for surfacic or wireframe operations. They can also be used for other operations which do not modify the input data (analysis for example). Operators are delivered in the GMModelInterfaces and GMOperatorsInterfaces frameworks.

Refer to [How to Use Geometric Operators](../CAACgmModel/CAACgmUcGMModelOpeOverw.md) and [How to Use Topological Operators](CAACgmTaUseTopoOperators.md).
## Building and Launching a Use case

To launch a use case, you need to set up the build time environment, then compile the module which contains the use case along with its prerequisites, set up the run time environment, and then execute the use case. This is explained in detail in [Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md). 

    * If the use case creates its own data, you have to type the command name  (module name) with one argument, the name of the .NCGM output file.  
Example:  
`CAAGMOperatorsOverview e/OverviewResult.NCGM`
    * If the use case loads data from an NCGM file, you have to type the command name with two arguments: the input file  and the output file.  
Example:  
`CAAGMOperatorsChamfer e/ChamferInputs.NCGM e/ChamferResult.NCGM`

Very few use cases load two or more input files or generate two or more files. Check the instructions and comments in the use case code for more information on how to launch the use case if this were to happen.

The input files are delivered in the FunctionTests/InputData folder of the framework in which the use case is delivered. 
## Viewing Use Case Results

Results produced by use cases can be stored in an NCGM container which is displayable by using the CAAGMModelGemBrowser use case.  Only topological objects can be displayed. To start the browser, just type the CAAGMModelGemBrowser command to display the application below:

Fig.1 NCGM Browser  ![NCGM Browser](images/CGM_ncgm_browser_0.png)  
---  
## 

Not all objects can be displayed in the browser. For more information, refer to [Browsing the Geometric Container](CAACgmUcGemBrowser.md).
## References

[1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [How to Use Geometric Operators](../CAACgmModel/CAACgmUcGMModelOpeOverw.md)  
[3] |  [ How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)  
[4] |  [Browsing the Geometric Container](CAACgmUcGemBrowser.md)  
## History

Version: **1** [Sept 2011] | Document created  
---|---
