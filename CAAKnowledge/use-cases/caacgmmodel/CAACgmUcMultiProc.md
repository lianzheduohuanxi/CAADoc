---
title: "How to Use MProc to Tessellate a Multi-Body Model"
category: "use case"
module: "CAACgmModel"
tags: ["CAAGMModelInterfaces", "CAAGMModelTesMProcImpl", "CAAGMModelTesMProcMain"]
source_file: "Doc\online\CAACgmModel\CAACgmUcMultiProc.htm"
converted: "2026-05-11T17:33:48.480630"
---

How to Use MProc to Tessellate a Multi-Body Model   
---  
Use Case  
Abstract Multiprocessing is used to compute particular operations as quickly as possible. A typical example is the tessellation of a multi-body model.
    * Classes to be Used
    * Use Case Description
    * References  
---  
Classes to be Used Task management is handled by the CATMProcTaskManagerCGM class. This class provides functionality for creating new tasks and for processing completed tasks. Custom implementations derive from this class to add task division and accumulation logic. Task containment, which defines a container to hold operational data, is handled by the CATMProcTaskContainerCGM class. It provides functionality to format computational data into buffers that are used for inter-process communication, and to compute tasks. Custom implementations derive from this class to add data in the form of inputs and outputs, and operators to compute the results.  Use Case Description The CAAGMModelTesMProcImpl.m CAAGMModelTesMProcMain.m modules in CAAGMModelInterfaces.edu illustrates how to tessellate a multi-body model by using the MProc capabilities of the geometric modeler. This use case uses as input data the plane.NCGM file which is delivered in the FunctionTests/InputData folder of the CAAGMModelInterfaces.edu framework.  To execute this use case, run the `CAAGMModelTesMProcMain inputFile.NCGM` command. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.htm). This use case:
    1. Loads a multi-body model.
    2. Instantiate a custom task manager. This custom task manager takes as input the list of bodies but only tessellate the first edge of each body (for simplification purpose).
    3. Run the parallel transactions.
Go to [Introduction to Multiprocessing](CAACgmTaMultiProcIntro.htm) for more information on the MProc classes and principles. References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.htm)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.htm)  
[3] |  [Introduction to Multiprocessing](CAACgmTaMultiProcIntro.htm)  
History Version: **1** [Oct 2011] | Document created  
---|---
