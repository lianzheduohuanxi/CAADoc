---
title: "Creating a Point on a Wire"
category: "use-case case"
module: "CAACgmModel"
tags: "["CAADoc", "CAAGMModelGemBrowser", "CAAGMModelInterfaces", "CAAGMModelComputePointOnWire", "CATICGMTopWire", "CATIA", "CATICGMComputePointOnWire"]"
source_file: "Doc/online/CAACgmModel/CAACgmUcBtoPointOnWire.htm"
converted: "2026-05-11T17:33:48.162955"
---
# Computing a Mathematical Point on a Wire

---
Use Case
## Abstract

You can create a point on a wire by using the CATICGMComputePointOnWire operator. How to use this operator is illustrated in the CAAGMModelComputePointOnWire use case.
    * What You Will Learn With This Use Case
    * The CATICGMComputePointOnWire Operator
    * The CAAGMModelComputePointOnWire Use Case
      * What Does CAAGMModelComputePointOnWire Do
      * How to Launch CAAGMModelComputePointOnWire
      * Where to Find the CAAGMModelComputePointOnWire Code
    * Step-by-Step
    * In Short
    * References
---
## What You Will Learn With This Use Case

This use case is intended to help you use the basic topological operators. It particularly details the creation of a point on a wire.
## The CATICGMComputePointOnWire Operator

This use case is intended to help you use the basic topological operators. It particularly details the creation of a point on a wire.
The CATICGMComputePointOnWire operator is to be used according to the following scheme:

    1. Creation of an operator instance from a global function.
    2. Run of the operator.
    3. Retrieve of the CATMathPoint which has been created.

**Note** : Unlike in most topological operators, there is no GetResult method whereby you access a CATBody. There is no BASIC or ADVANCED mode to be defined either.
## The CAAGMModelComputePointOnWire Use Case

CAAGMModelComputePointOnWire  is a use case of the CAAGMModelInterfaces.edu framework.
### What Does CAAGMModelComputePointOnWire Do

Fig. 1: The Geometry of the CAAGMModelComputePointOnWire Use Case ![Use Case Geometry](images/CAACgmBtoComputePointOnWire.gif) | This use case creates a CATMathPoint at a ratio of 0.5 from the start extremity of the CATWire. To visualize this point a cartesian point is created at the CATMathPoint location.
---|---
### How to Launch CAAGMModelComputePointOnWire

Fig. 1: The Geometry of the CAAGMModelComputePointOnWire Use Case ![Use Case Geometry](images/CAACgmBtoComputePointOnWire.gif) | This use case creates a CATMathPoint at a ratio of 0.5 from the start extremity of the CATWire. To visualize this point a cartesian point is created at the CATMathPoint location.
To launch CAAGMModelComputePointOnWire, you will need to set up the build time environment, then compile CAAGMModelComputePointOnWire.m along with its prerequisites, set up the run time environment, and then execute the use case [4].

By default, this use case is to be run with the CircleBody.NCGM input file which is delivered in the CAAGMModelInterfaces.edu/FunctionTests/InputData folder.  To launch this use case type the command below, this command saves the result in the outpufile.NCGM file:

`CAAGMModelComputePointOnWire e/CircleBody.NCGM outputfile.NCGM`

This NCGM file can be displayed using the CAAGMModelGemBrowser use case [4].
### Where to Find the CAAGMModelComputePointOnWire Code

The CAAGMModelComputePointOnWire use case is made of a main named CAAGMModelComputePointOnWire.cpp located in the CAAGMModelComputePointOnWire.m module of the CAAGMModelInterfaces.edu framework:

`InstallRootFolder/CAADoc/CAAGMModelInterfaces.edu/CAAGMModelComputePointOnWire.m/`

where `InstallRootFolder` [4] is the folder where the API CD-ROM is installed.
## Step-by-Step

where `InstallRootFolder` [4] is the folder where the API CD-ROM is installed.
CAAGMModelComputePointOnWire.cpp is divided into three logical steps:

    1. Loading the NCGM container containing the input wire [1]
    2. Creating and Manipulating the CATICGMComputePointOnWire Operator
    3. Writing the Model and Closing the Factory [1]

### Creating and Manipulating the CATICGMComputePointOnWire Operator

1. Loading the NCGM container containing the input wire [1]
2. Creating and Manipulating the CATICGMComputePointOnWire Operator
3. Writing the Model and Closing the Factory [1]
The CATCGMCreateComputePointOnWire global method is used to create an instance of operator. The body retrieved from the GetResult method **applied to the CATICGMTopWire object** is passed as the third function argument value. The ratio in the fourth argument is calculated from the wire start extremity.

The created point is retrieved by using the GetMathPoint method.

    CATICGMComputePointOnWire* pPointOnWire = ::CATCGMCreateComputePointOnWire(piGeomFactory,

                                                        &topdata,
The created point is retrieved by using the GetMathPoint method.
CATICGMComputePointOnWire* pPointOnWire = ::CATCGMCreateComputePointOnWire(piGeomFactory,
                                                        pWireBody,  0.5);

    ...
CATICGMComputePointOnWire* pPointOnWire = ::CATCGMCreateComputePointOnWire(piGeomFactory,
pWireBody,  0.5);
    CATMathPoint oPointOnWire;
    oPointOnWire->Run(#);
    pPointOnWire->GetMathPoint(oPointOnWire);

To visualize the created CATMathPoint, a cartesian point is created.

## In Short

pPointOnWire->GetMathPoint(oPointOnWire);
To visualize the created CATMathPoint, a cartesian point is created.
The CATICGMComputePointOnWire topological operators allows you to create a point on a CATWire. Once the operator is created, you just have to run it. The created point is retrieved by using the GetMathPoint method.

## References

[1] | [An Introduction to Geometric Modeler Use Cases](CAACgmUcGMModelUseCaseOverw.md)
---|---
[2] | [How to Use Geometric Operators](CAACgmUcGMModelOpeOverw.md)
[3] | [Browsing the Geometric Container](CAACgmUcGemBrowser.md)
[4] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
[5] | [The Objects of CATIA Geometric Modeler](CAACgmTaGobGeoObjects.md)
[6] | [The Curves of CATIA Geometric Modeler](CAACgmTaGobCurves.md)
## History

Version: **1** [Jan 2007] | Document created
---|---
