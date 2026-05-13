---
```vbscript
title: "Managing Transitions between Workbenches"
category: use-case case"
module: "CAAAfrUseCases"
tags: ["CAAAfrGeometryWksTransition", "CAAAfrGeometryWks", "CAAAfrGeometryWks_trans", "CAAEAfrGeometryWksTransition", "CAAGeometry", "CATIWorkbenchTransition", "CAAApplicationFrame"]
source_file: "Doc/online/CAAAfrUseCases/CAAAfrSampleWorkbenchTransitions.htmmd"
converted: "2026-05-11T17:17:55.847355"
```

---
# 3D PLM Enterprise Architecture

|
## User Interface - Frame

|
### Managing Transitions between Workbenches

_Making a process-driven user interface_
---|---|---
Use Case

* * *
### Abstract

This article shows how to create the transition to the two workbenches of the Geometry workshop.

  * **What You Will Learn With This Use Case**
  * **The CAAAfrGeometryWksTransition Use Case**
    * What Does CAAAfrGeometryWksTransition Do
    * How to Launch CAAAfrGeometryWksTransition
    * Where to Find the CAAAfrGeometryWksTransition Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

CAAAfrGeometryWksTransition is a use case of the CAAApplicationFrame.edu framework that illustrates the ApplicationFrame framework capabilities.

[Top]
### The CAAAfrGeometryWksTransition Use Case

The CAAAfrGeometryWksTransition use case to manage the transitions between any workbench and the workbenches of the Geometry workshop.

[Top]
#### What Does the CAAAfrGeometryWksTransition Use Case Do

The CAAAfrGeometryWksTransition use case to manage the transitions between any workbench and the workbenches of the Geometry workshop. To do this, it is made of a class that implements the _CATIWorkbenchTransition_ interface as an extension of the _CAAAfrGeometryWks_trans_ late type, _CAAAfrGeometryWks_ being the Geometry workshop description class name.
#### How to Launch CAAAfrGeometryWksTransition

See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched. For the specific scenario :

```vbscript
Do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following:

```

  * Create any type of document, for example a Part document
  * Select a workbench of the CAAGeometry document, using the Start menu. For example, select Start->xxxx->CAA Geometrical Creation

This creates a new CAAGeometry document with the CAA Geometrical Creation workbench active.

[Top]
#### Where to Find the CAAAfrGeometryWksTransition Code

This creates a new CAAGeometry document with the CAA Geometrical Creation workbench active.
The CAAAfrGeometryWksTransition use case is made of a single class named _CAAEAfrGeometryWksTransition_ located in the CAAAfrGeometryWksTransition.m module of the CAAApplicationFrame.edu framework:

Windows | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeometryWksTransition.m/`

The CAAAfrGeometryWksTransition use case is made of a single class named _CAAEAfrGeometryWksTransition_ located in the CAAAfrGeometryWksTransition.m module of the CAAApplicationFrame.edu framework:
Windows | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeometryWksTransition.m/`
Unix | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeometryWksTransition.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

To manage transitions between any workbench and the workbenches of the CAAGeometry document, there are two steps:
# | Step | Where
---|---|---
To manage transitions between any workbench and the workbenches of the CAAGeometry document, there are two steps:
1 | Create the extension class that implements CATIWorkbenchTransition | CAAEAfrGeometryWksTransition class
2 | Update the interface dictionary | interface dictionary

[Top]
#### Creating the Extension Class that Implements CATIWorkbenchTransition

2 | Update the interface dictionary | interface dictionary
This class is a data extension of a made of the workshop identifier suffixed by `_trans`, that is here `CAAAfrGeometryWks_trans` for the Geometry workshop.

  1. Create the CAAEAfrGeometryWksTransition.h file

         #include "CATExtIWorkbenchTransition.h"

This class is a data extension of a made of the workshop identifier suffixed by `_trans`, that is here `CAAAfrGeometryWks_trans` for the Geometry workshop.
1. Create the CAAEAfrGeometryWksTransition.h file
         class CAAEAfrGeometryWksTransition : public CATExtIWorkbenchTransition

         {
           **CATDeclareClass** ;
class CAAEAfrGeometryWksTransition : public CATExtIWorkbenchTransition
           public:
              CAAEAfrGeometryWksTransition(#);
              virtual ~CAAEAfrGeometryWksTransition(#);

         };

---

virtual ~CAAEAfrGeometryWksTransition(#);
The CATDeclareClass macro states that this class belongs to a component. The class has only a constructor and a destructor.

  2. Create the CAAEAfrGeometryWksTransition.cpp file.

         // Local FW
         #include "CAAEAfrGeometryWksTransition.h"

         **CATImplementClass**(CAAEAfrGeometryWksTransition,
                           **DataExtension** ,
                           CATBaseUnknown,
CATBaseUnknown,
                           CAAAfrGeometryWks_trans);

         #include <TIE_CATIWorkbenchTransition.h>
CATBaseUnknown,
CAAAfrGeometryWks_trans);
         TIE_CATIWorkbenchTransition(CAAEAfrGeometryWksTransition);

         CAAEAfrGeometryWksTransition::CAAEAfrGeometryWksTransition(#)

         {
```vbscript
TIE_CATIWorkbenchTransition(CAAEAfrGeometryWksTransition);
CAAEAfrGeometryWksTransition::CAAEAfrGeometryWksTransition(#)
           _newDoc = "CAAGeometry" ;
```

         }

CAAEAfrGeometryWksTransition::CAAEAfrGeometryWksTransition(#)
_newDoc = "CAAGeometry" ;
         CAAEAfrGeometryWksTransition::~CAAEAfrGeometryWksTransition(#) {}

---

CAAEAfrGeometryWksTransition::~CAAEAfrGeometryWksTransition(#) {}
The `CATImplementClass` macro reads: the _CAAEAfrGeometryWksTransition_ class is a data extension of the late type _CAAAfrGeometryWks_trans_. As any extension class, its third argument is _CATBaseUnknown_. The constructor assigns the type CAAGeometry to the document type to create using the `_newDoc` data member of the base class _CATExtIWorkbenchTransition_. This type is the one to which the workbench is dedicated.

Since the `DoTransition` method is not implemented, the one of the base class _CATExtIWorkbenchTransition_ is executed instead. It creates a new CAAGeometry document, except if:

  * The Geometry workshop is the active workshop, and the end user requests another workbench of this workshop. In this case, the active document was an CAAGeometry document, and remains an CAAGeometry document after the transition.
  * The Geometry workshop is the active workshop and the end user selects another workshop, or a worbench belonging to another workshop.

[Top]
#### Updating the Dictionary

Update the interface dictionary, that is a file named, for example, CAAApplicationFrame.dico, whose directory's pathname is concatenated at run time in the CATDictionaryPath environment variable, and containing the following declaration to state that the _CAAAfrGeometryWks_trans_ late type implements the _CATIWorkbenchTransition_ interface, and whose code is located in the libCAAAfrGeometryWksTransition shared library or DLL.

    CAAAfrGeometryWks_trans CATIWorkbenchTransition libCAAAfrGeometryWksTransition

---

[Top]

* * *
### In Short

The CAA process-centric user interface implies that the application should know what to do when the end user selects a workbench in the Start menu. This knowledge is provided by the workshop, or possibly the workbench, supplier by implementing the _CATIWorkbenchTransition_ interface.

```vbscript
```vbscript
For standalone documents, that is, documents that do not contain or are not linked to, or that are not contained or linked by, other documents, the _CATIWorkbenchTransition_ interface is implemented once by the document's workshop supplier, and applies to all the document's workbenches.

```

```

Otherwise, each workbench of the embedded or linked document should implement the _CATIWorkbenchTransition_ interface to create its incoming and outgoing transitions, that is what should happen when it is selected, or when it is active and when another workbench is selected.

[Top]

* * *
### References

[Top]
---

* * *
### History

Version: **1** [Jan 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
