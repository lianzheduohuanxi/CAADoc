---
title: "Determining available parsers"
category: "use-case case"
module: "CAAXmlUseCases"
tags: "["CAAXMLInfo", "CAAXMLParser"]"
source_file: "Doc/online/CAAXmlUseCases/CAAXMLInfo.htm"
converted: "2026-05-11T17:33:45.634065"
---
# 3D PLM Enterprise Architecture

|
## Middleware Abstraction

|
### Determining Available Parsers

_Listing DOM and SAX parsers installed on a machine_
---|---|---
Use Case

* * *
### Abstract

This article shows how to determine at runtime if a given V5 XML parser component is available.

  * **What You Will Learn With This Use Case**
  * **The CAAXMLInfo Use Case**
    * What Does CAAXMLInfo Do
    * How to Launch CAAXMLInfo
    * Where to Find the CAAXMLInfo Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case shows how to determine at runtime if a given V5 XML parser component is available.

[Top]
### The CAAXMLInfo Use Case

The CAAXMLInfo Use Case is a use case of the CAAXMLParser.edu framework that illustrates XMLParser framework capabilities.

[Top]
#### What Does CAAXMLInfo Do

This use case gathers information about the parsers installed on the machine and prints a report in the console.

    <?xml version="1.0"?>
This use case gathers information about the parsers installed on the machine and prints a report in the console.
    DOM parsers on the host:
    XML4C version 5.0 : Installed
    XML4C version 3.0.1 : Installed
    MSXML version 5.0 : Installed
    MSXML version 4.0 : Installed
    MSXML version 3.0 : Installed
    SAX parsers on the host:
    XML4C version 5.0 : Installed
    XML4C version 3.0.1 : Installed
    MSXML version 5.0 : Installed
    MSXML version 4.0 : Installed
    MSXML version 3.0 : Installed

---

[Top]
#### How to Launch CAAXMLInfo

To launch CAAXMLInfo, you will need to set up the build time environment, then compile CAAXMLInfo along with its prerequisites, set up the run time environment, and then execute the use case [1].

The use case should be launched as follows from the command line:

To launch CAAXMLInfo, you will need to set up the build time environment, then compile CAAXMLInfo along with its prerequisites, set up the run time environment, and then execute the use case [1].
The use case should be launched as follows from the command line:
    CAAXMLInfo

[Top]
#### Where to Find the CAAXMLInfo Code

CAAXMLInfo
The CAAXMLInfo use case is made of one class located in the CAAXMLInfo.m module of the CAAXMLParser.edu framework:

Windows | `InstallRootDirectory/CAAXMLParser.edu/CAAXMLInfo.m/`

The CAAXMLInfo use case is made of one class located in the CAAXMLInfo.m module of the CAAXMLParser.edu framework:
Windows | `InstallRootDirectory/CAAXMLParser.edu/CAAXMLInfo.m/`
Unix | `InstallRootDirectory/CAAXMLParser.edu/CAAXMLInfo.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

To check the availability of XML parsers, there are two main steps:
# |  Step
---|---
To check the availability of XML parsers, there are two main steps:
1 | Check the Availability of V5 DOM Components
2 | Check the Availability of V5 SAX Components

[Top]
#### Check the Availability of V5 DOM Components

    ...
    HRESULT hr = ::DetectCATIXMLDOMDocumentBuilder(&domClsidArray;[i], 1, implIndex);
    ...

---

To test the availability of V5 DOM components, use the `DetectCATIXMLDOMDocumentBuilder` function. This function takes the following parameters:

`&domClsidArray;[i]` | An array of CLSID identifying the parsers you want to test for availability.
---|---
`1` | The size of this array.
`implIndex` | The array index of the first available parser successfully detected, returned by reference by the function.

The function returns E_FAIL if no suitable parser has been found. For more details on V5 DOM components, see [2].

[Top]
#### Check the Availability of V5 SAX Components

    ...
    HRESULT hr = ::DetectCATIXMLSAXFactory(&saxClsidArray;[i], 1, implIndex);
    ...

---

To test the availability of V5 SAX components, use the `DetectCATIXMLSAXFactory` function. This function takes the following parameters:

`&saxClsidArray;[i]` | An array of CLSID identifying the parsers you want to test for availability.
---|---
`1` | The size of this array.
`implIndex` | The array index of the first available parser successfully detected, returned by reference by the function.

The function returns E_FAIL if no suitable parser has been found. For more details on V5 DOM components, see [2].

[Top]
### In Short

This use case shows you how o determine at runtime if a given V5 XML parser component is available.

[Top]

* * *
### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] | [ Using XML in V5](../CAAXmlTechArticles/CAAXmlV5Overview.md)

* * *
### History

Version: **1** [May 2005] | Document created
---|---
[Top]

* * *

_Copyright 2005, Dassault Systmes. All rights reserved._
