---
title: "Defining the Activated Workbench"
category: "use-case case"
module: "CAAAfrUseCases"
tags: "["CAAEAfrActivateWorkbenchOnPart", "CATIAfrActivateWorkbench", "CAAAfrInitialWorkbench", "CATIAApplicationFrm", "CAACATIAApplicationFrm", "CAAAfrProduct", "CAAApplicationFrame"]"
source_file: "Doc/online/CAAAfrUseCases/CAAAfrInitialWorkbench.htm"
converted: "2026-05-11T17:17:55.614529"
---
# 3D PLM Enterprise Architecture

|
## User Interface - Frame

|
### Defining the Activated Workbench

_Using CATIAfrActivateWorkbench_
---|---|---
Use Case

* * *
### Abstract

This article shows how to use the _CATIAfrActivateWorkbench_ interface to define the workbench to activate when an object is UI-activated.

  * **What You Will Learn With This Use Case**
  * **The CAAAfrInitialWorkbench Use Case**
    * What Does CAAAfrInitialWorkbench Do
    * How to Launch CAAAfrInitialWorkbench
    * Where to Find the CAAAfrInitialWorkbench Code
  * **Step-by-Step**
  * **In Short**
  * **References**

* * *
### What You Will Learn With This Use Case

This use case is intended to show you how to use the _CATIAfrActivateWorkbench_ interface to define the workbench [1] to launch when an object is UI-activated. An UI-active object [2] is editable thanks commands distributed in workbenches. When the end user double clicks such object, opens or creates a document, the application must choose a workbench among those of the current UI-active object. The choice for a given UI-active object is done according to this protocol:

  * For its first UI-activation, it is the last used workbench in the previous session and kept in a setting file. If this setting file does not exist, it is the first workbench in the list of the application.
  * For the next UI-activations, it is the last used workbench in the session.

This interface enables you to modify this protocol. You have the possibility imposing such or such workbenches according to your criteria. This interface may be implemented on the following UI-active objects:

  * **ASMProduct** for Product documents,
  * **DrwDrawing** for Drawing,
  * **MechanicalPart** for Part,
  * **AnalysisManager** for Analysis.

However, for the following UI-active objects it is useless since this UI-active object has no workbench, but only a workshop [2].

  * PRTSketch for a sketcher,
  * this of Material documents,
  * this of Catalog.

This interface can be only once implemented for a given object. [Top]
### The CAAAfrInitialWorkbench Use Case

CAAAfrInitialWorkbench is a use case of the CAAApplicationFrame.edu framework that illustrates ApplicationFrame framework capabilities. [Top]
#### What Does CAAAfrInitialWorkbench Do

This article shows an implementation of the _CATIAfrActivateWorkbench_ interface __ on the **MechanicalPart** object. The activated workbench, among the Part workbenches, is the **Part Design** workbench. ![](images/CAAAfrInitialWkbPartDesign.gif) [Top]
#### How to Launch CAAAfrInitialWorkbench

This article shows an implementation of the _CATIAfrActivateWorkbench_ interface __ on the **MechanicalPart** object. The activated workbench, among the Part workbenches, is the **Part Design** workbench. ![](images/CAAAfrInitialWkbPartDesign.gif) [Top]
To launch CAAAfrInitialWorkbench, you will need to set up the build time environment, then compile CAAAfrInitialWorkbench along with its prerequisites, set up the run time environment, and then execute the use case [3]. But just before launching the execution, edit the CAAApplicationFrame.edu.dico interface dictionary file located in the dictionary directory of the CAAApplicationFrame.edu framework: | Windows | `InstallRootDirectory/CAAApplicationFrame.edu/CNext/code/dictionary/`

This article shows an implementation of the _CATIAfrActivateWorkbench_ interface __ on the **MechanicalPart** object. The activated workbench, among the Part workbenches, is the **Part Design** workbench. ![](images/CAAAfrInitialWkbPartDesign.gif) [Top]
To launch CAAAfrInitialWorkbench, you will need to set up the build time environment, then compile CAAAfrInitialWorkbench along with its prerequisites, set up the run time environment, and then execute the use case [3]. But just before launching the execution, edit the CAAApplicationFrame.edu.dico interface dictionary file located in the dictionary directory of the CAAApplicationFrame.edu framework: | Windows | `InstallRootDirectory/CAAApplicationFrame.edu/CNext/code/dictionary/`
UNIX | `InstallRootDirectory/CAAApplicationFrame.edu/CNext/code/dictionary/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

In this file, remove the "**#** " character before the following line,

    ...
    #MechanicalPart      CATIAfrActivateWorkbench  libCAAAfrInitialWorkbench
    ...

---

and run mkCreateRuntimeView.

Then, in the window where you run the mkrun command, do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following:

  1. On the **Start** menu, select **Shape** and click **FreeStyle**
  2. On the **Start** menu, select **Exit**
  3. Relaunch**CNEXT**
  4. On the **File** menu, click **New**
  5. **New** Dialog box click **Part** and click **OK** , you are in the **Part Design** workbench

Without the _CATIAfrActivateWorkbench_ implementation, the current workbench would have been **FreeStyle,** the last used workbench kept in a setting file.

  6. On the **Start** menu, select **Mechanical Design** , and click **Wireframe and Surface Design**

You have explicitly ask a workbench, it is the new current one.

  7. **New** Dialog box click **Part** and click **OK** , you are always in the **Part Design** workbench

Without the _CATIAfrActivateWorkbench_ implementation, the current workbench would have been **Wireframe and Surface Design,** the last used workbench in the session.

  8. On the **File** menu, click **Open**
  9. **File Selection** Dialog box click **CAAAfrProduct.CATProduct** (*) and click **Open**
  10. Edit**Part1** , you are in the **Part Design** workbench

Without the _CATIAfrActivateWorkbench_ implementation, the current workbench would have been **Wireframe and Surface Design,** the last used workbench for a Part.

  11. On the **Start** menu, select **Mechanical Design** , and click **Wireframe and Surface Design**

You have explicitly ask a workbench, it is the new current one.

  12. Edit******Part2** , you are always in the **Part Design** workbench

Without the _CATIAfrActivateWorkbench_ implementation, the current workbench would have been **Wireframe and Surface Design,** the last used workbench for a Part.

(*)The document is located in the InputData directory of the CAAApplicationFrame.edu framework:

Without the _CATIAfrActivateWorkbench_ implementation, the current workbench would have been **Wireframe and Surface Design,** the last used workbench for a Part.
Windows | `InstallRootDirectory/CAACATIAApplicationFrm.edu/InputData/`

Unix | `InstallRootDirectory/CAACATIAApplicationFrm.edu/InputData/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
#### Where to Find the CAAAfrInitialWorkbench Code

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
The CAAAfrInitialWorkbench use case is made of one single class, the _CAAEAfrActivateWorkbenchOnPart_ class, located in the CAAAfrInitialWorkbench.m module of the CAAApplicationFrame.edu framework:

Windows | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrInitialWorkbench.m/`

The CAAAfrInitialWorkbench use case is made of one single class, the _CAAEAfrActivateWorkbenchOnPart_ class, located in the CAAAfrInitialWorkbench.m module of the CAAApplicationFrame.edu framework:
Windows | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrInitialWorkbench.m/`
Unix | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrInitialWorkbench.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
To implement the _CATIAfrActivateWorkbench_ interface, there are two steps:

  1. Creating the Header File
  2. Creating the Source File

[Top]
#### Creating the Header File

    // System framework
    #include "CATBaseUnknown.h"
    #include "CATString.h"

    class CAAEAfrActivateWorkbenchOnPart: public CATBaseUnknown
    {
class CAAEAfrActivateWorkbenchOnPart: public CATBaseUnknown
      CATDeclareClass;

      public:

        CAAEAfrActivateWorkbenchOnPart(#);
        virtual ~CAAEAfrActivateWorkbenchOnPart(#);

        CATString & **GetInitialWorkbench**(#);

      private:

        CAAEAfrActivateWorkbenchOnPart(const CAAEAfrActivateWorkbenchOnPart &iObjectToCopy);
        CAAEAfrActivateWorkbenchOnPart & operator = (const CAAEAfrActivateWorkbenchOnPart &iObjectToCopy);

      private:

          CATString **_WbName** ;

    };

---

The _CAAEAfrActivateWorkbenchOnPart_ class derives from _CATBaseUnkown_. The `GetInitialWorkbench` method is the only one method of the _CATIAfrActivateWorkbench_ interface. The `CATDeclareClass` macro declares that the _CAAEAfrActivateWorkbenchOnPart_ class belongs to a component. Note that the copy constructor and the assignment operator are set as private, and are not implemented in the source file. This prevents the compiler from creating them as public without you know. **`_WbName`** is the data returned by the `GetInitialWorkbench` method.

[Top]
#### Creating the Source File

    #include "CAAEAfrActivateWorkbenchOnPart.h"
    #include "TIE_CATIAfrActivateWorkbench.h"
    TIE_CATIAfrActivateWorkbench(CAAEAfrActivateWorkbenchOnPart);

```cpp
TIE_CATIAfrActivateWorkbench(CAAEAfrActivateWorkbenchOnPart);
```cpp
    CATImplementClass (CAAEAfrActivateWorkbenchOnPart,**DataExtension** ,
```

                       CATBaseUnknown, **MechanicalPart**);

```

---

The _CAAEAfrActivateWorkbenchOnPart_ class states that it implements the _CATIAfrActivateWorkbench_ interface thanks to the `TIE_CATIAfrActivateWorkbench` macro. The `CATImplementClass` macro declares that the _CAAEAfrActivateWorkbenchOnPart_ class is a data extension, thanks to the `DataExtension` keyword, that extends `MechanicalPart`. The third argument must always be set as _CATBaseUnknown_ or _CATNull_ for any kind of extension.

    ...
    CAAEAfrActivateWorkbenchOnPart::CAAEAfrActivateWorkbenchOnPart(#)

    {
CAAEAfrActivateWorkbenchOnPart::CAAEAfrActivateWorkbenchOnPart(#)
        _WbName = "**PrtCfg** " ;

    }
CAAEAfrActivateWorkbenchOnPart::CAAEAfrActivateWorkbenchOnPart(#)
_WbName = "**PrtCfg** " ;
    CAAEAfrActivateWorkbenchOnPart::~CAAEAfrActivateWorkbenchOnPart(#)

    {
    }
_WbName = "**PrtCfg** " ;
CAAEAfrActivateWorkbenchOnPart::~CAAEAfrActivateWorkbenchOnPart(#)
    CATString & CAAEAfrActivateWorkbenchOnPart::**GetInitialWorkbench**(#)

    {

        return **_WbName** ;
    }

---

In this implementation, the workbench is always the Part Design workbench. The name of this workbench is **PrtCfg**.

[Top]

* * *
### In Short

This use case explains how to implement the _CATIAfrActivateWorkbench_ interface.

[Top]

* * *
### References

[1] | [Creating a Workbench](CAAAfrSampleWorkbench.md)
---|---
[2] | [Application Frame Overview](../CAAAfrTechArticles/CAAAfrOverview.md)
[3] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
[Top]

* * *
### History

Version: **1** [Aug 2003] | Document created
---|---
[Top]

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
