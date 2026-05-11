---
title: "Creating a Point on a Wire"
category: "use case"
module: "CAABtoUseCases"
tags: ["CAATopComputePointOnWire", "CATICGMObject", "CAABasicTopoOpe", "CAAGemBrowser"]
source_file: "Doc/online/CAABtoUseCases/CAABtoPointOnWire.md"
converted: "2026-05-11T17:33:46.169729"
---

Geometric Modeler |  Topology |  Creating a Point on a Wire _A topological operator to create a point on a wire_  
---|---|---  
Use Case  
  
* * *

Abstract You can create a point on a wire by using the CATComputePointOnWire operator. How to use this operator is illustrated in the CAATopComputePointOnWire use case. 

  * **What You Will Learn With This Use Case**
  * **The CATTopComputePointOnWire Operator**
  * **The CAATopComputePointOnWire Use Case**
    * What Does CAATopComputePointOnWire Do
    * How to Launch CAATopComputePointOnWire
    * Where to Find the CAATopComputePointOnWire Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *

What You Will Learn With This Use Case This use case is intended to help you use the basic topological operators. It particularly details the creation of a point on a wire. [Top] The CATTopComputePointOnWire Operator The CATTopComputePointOnWire operator is to be used according to the following scheme:

  1. creation of an operator instance from a global function
  2. run of the operator
  3. retrieve of the CATMathPoint which has been created.

Note: Unlike in most topological operators, there is no GetResult method whereby you access a CATBody. There is no BASIC or ADVANCED mode to be defined either. [Top] The CAATopComputePointOnWire Use Case CAATopComputePointOnWire is a use case of the CAABasicTopoOpe.edu framework that illustrates the Basic Topological Operators framework capabilities. [Top] What Does CAATopComputePointOnWire Do Fig. 1: The Geometry of the CAATopComputePointOnWire Use Case ![](images/CAAComputePointOnWire.gif) | This use case creates a CATMathPoint at a ratio of 0.5 from the start extremity of the CATWire. To visualize this point a cartesian point is created at the CATMathPoint location.  
---|---  
[Top] How to Launch CAATopComputePointOnWire To launch CAATopComputePointOnWire, you will need to set up the build time environment, then compile CAATopComputePointOnWire.m along with its prerequisites, set up the run time environment, and then execute the use case [3]. If you simply type CAATopComputePointOnWire with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example: With Windows CAATopComputePointOnWire `e/PointOnWire.NCGM` With UNIX CAATopComputePointOnWire `/u/PointOnWire.NCGM` This NCGM file can be displayed using the CAAGemBrowser use case. [Top] Where to Find the CAATopComputePointOnWire Code The CAATopComputePointOnWire use case is made of a main named CAATopComputePointOnWire.cpp located in the CAATopComputePointOnWire.m module of the CAABasicTopoOpe.edu framework: Windows | `InstallRootDirectory\CAABasicTopoOpe.edu\CAATopComputePointOnWire.m\`  
---|---  
Unix | `InstallRootDirectory/CAABasicTopoOpe.edu/CAATopComputePointOnWire.m/`  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. [Top] Step-by-Step CAATopComputePointOnWire.cpp is divided into four logical steps: 

  1. Creating the Geometry Factory
  2. Creating the CATWire
  3. Creating and Manipulating the CATComputePointOnWire Operator
  4. Writing the Model and Closing the Factory

[Top] Creating the Geometry Factory The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular) [1]. This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.
    
    
    CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**() ;
    if (NULL==piGeomFactory) return (1);  
  
---  
[Top] Creating the CATWire A wire is made up of a list of curves. To simplify the example, a CATCircle is created in the YZ plane. This CATCircle is created by the geometry factory by using the CreateCircle method. Then the wire is created:
    
    
    _// Define an open configuration for the operator_
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    /_/ Define the data of the operator: configuration - no journal_
    CATTopData topdata(pConfig);
    _// Define the limits and orientations of the curves to be specified_
    CATCrvLimits CurLim[1];
    CATOrientation Orient[1]={1};
    ListOfCurves[0]->GetLimits(CurLim[0]);
    CATTopWire * pWire1 = ::CATCreateTopWire(piGeomFactory, 
    	                                     &topdata,		
                                                         1,
    				      ListOfCurves, 
                                                    CurLim,
                                                   Orient);  
  
---  
The operator configuration is the level of software you want to use to run this operator. By default, define an open configuration as in this use case to run with the current level. Moreover here, the pointer to the journal is set to `NULL` in the operator data. So that the journal is not filled. The CATCreateTopWire global function is used to create a CATTopWire, then the Run and GetResult methods are applied like for most operators. [Top] Creating and Manipulating the CATComputePointOnWire Operator The CATCreateComputePointOnWire global method is used to create an instance of operator. The body retrieved from the GetResult method **applied to the CATTopWire object** is passed as the third function argument value. The ratio in the fourth argument is calculated from the wire start extremity. The created point is retrieved by using the GetMathPoint method. 
    
    
    CATComputePointOnWire* pPointOnWire = ::CATCreateComputePointOnWire(piGeomFactory,
                                                        &topdata, 
                                                        pWireBody,  0.5);
    ...                                  
    CATMathPoint oPointOnWire;
    oPointOnWire->Run();
    pPointOnWire->GetMathPoint(oPointOnWire);  
  
---  
To visualize the created CATMathPoint, a cartesian point is created. [Top] Writing the Model and Closing the Factory To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved. The use case ends with the closure of the geometry factory, done by the `::CATCloseCGMContainer` global function.
    
    
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
  
---  
[Top]

* * *

In Short The CATComputePointOnWire topological operators allows you to create a point on a CATWire. Once the operator is created, you just have to run it. The created point is retrieved by using the GetMathPoint method. [Top]

* * *

References [1] | [The CGM Objects](../CAAGobTechArticles/GeoObjects.md)  
---|---  
[2] | [The CGM Curves](../CAAGobTechArticles/Curves.md)  
[3] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
[Top]  
  
* * *

History Version: **1** [Feb 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
