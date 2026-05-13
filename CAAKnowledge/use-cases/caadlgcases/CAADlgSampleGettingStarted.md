---
title: "Getting Started with Dialog Boxes"
category: "use-case case"
module: "CAADlgUseCases"
tags: "["CAADlgHelloWindow", "CAADlgHelloWindowId", "CAADlgHelloApplication", "CATInteractiveApplication", "CATIA", "CAADialog"]"
source_file: "Doc/online/CAADlgUseCases/CAADlgSampleGettingStarted.htm"
converted: "2026-05-11T17:17:55.978720"
---
# 3D PLM Enterprise Architecture

|
## User Interface - Dialogs

|
### Getting Started with Dialog Boxes

_A first sample with dialog boxes_
---|---|---
Use Case

* * *
### Abstract

This article shows a simple example of dialog box created using the Dialog framework.

  * **What You Will Learn With This Use Case**
  * **The CAADlgHelloApplication Use Case**
    * What Does CAADlgHelloApplication Do
    * How to Launch CAADlgHelloApplication
    * Where to Find the CAADlgHelloApplication Code
  * **Step-by-Step**
  * **In Short**
  * **References**

* * *
### What You Will Learn With This Use Case

The Dialog framework is intended to help application developers to simply design an implement their dialog windows and boxes. Its main characteristics are:

  * Programmer productivity: it provides high-level objects that allow for component reusability
  * Portability: the objects created can be implemented on Motif and Windows platforms without any change or customization
  * Standard compliance: it is built on top of the OSF/Motif and MFC layers
  * Versatility: it can be used as a standalone framework, along with its prerequisites, or in a CATIA Version 4 or Version 5 environment.

Let's have a look at this framework through two examples. The first sample program shows how to build a very simple window and how to close it. The second sample introduces a larger number of dialog window components or objects and how to manage window layouts as well as triggering actions when clicking on Dialog framework objects [1]. [Top]
### The CAADlgHelloApplication Use Case

CAADlgHelloApplication is a use case of the CAADialog.edu framework that illustrates Dialog framework capabilities. [Top]
#### What Does CAADlgHelloApplication Do

```vbscript
```cpp
For this example, you will simply display a prompt box that prints "Hello, CAA V5". To do this, derive your own application class, called _CAADlgHelloApplication_ , from the class _CATInteractiveApplication_ [2]. This application will:

```

```

```cpp
For this example, you will simply display a prompt box that prints "Hello, CAA V5". To do this, derive your own application class, called _CAADlgHelloApplication_ , from the class _CATInteractiveApplication_ [2]. This application will:
  1. create a window to display "Hello, CAA V5" by deriving the class _CATDlgDocument_
  2. makes the window visible.

```

In addition, the mechanism to close the application from the window is included. The window is as follows:

---

[Top]
#### How to Launch CAADlgHelloApplication

To launch CAADlgHelloApplication, you will need to set up the build time environment, then compile CAADlgHelloApplication along with its prerequisites, set up the run time environment, and then execute the use case [3].

[Top]
#### Where to Find the CAADlgHelloApplication Code

To launch CAADlgHelloApplication, you will need to set up the build time environment, then compile CAADlgHelloApplication along with its prerequisites, set up the run time environment, and then execute the use case [3].
The CAADlgHelloApplication use case is made of a several classes located in the CAADlgHelloApplication.m module of the CAADialog.edu framework:

Windows | `InstallRootDirectory/CAADialog.edu/``CAADlgHelloApplication``.m/`

The CAADlgHelloApplication use case is made of a several classes located in the CAADlgHelloApplication.m module of the CAADialog.edu framework:
Windows | `InstallRootDirectory/CAADialog.edu/``CAADlgHelloApplication``.m/`
Unix | `InstallRootDirectory/CAADialog.edu/CAADlgHelloApplication.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

The CAADlgHelloApplication.m module includes four files:

_CAADlgHelloApplication.h_ | The interactive application header file

The CAADlgHelloApplication.m module includes four files:
_CAADlgHelloApplication.h_ | The interactive application header file
_CAADlgHelloApplication.cpp_ | The interactive application source file
_CAADlgHelloWindow.h_ | The application window header file
_CAADlgHelloWindow.cpp_ | The application window source file

The resource file CAADlgHelloWindow.CATNls is located in the CNext/resources/msgcatalog directory.

[Top]
### Step-by-Step

The resource file CAADlgHelloWindow.CATNls is located in the CNext/resources/msgcatalog directory.
There are two logical steps in CAADlgHelloApplication:

  1. Creating the Interactive Application
  2. Creating the Application Window

[Top]
#### Creating the Interactive Application

Let's look at CAADlgHelloApplication.h, the application header file:

    #include "CATInteractiveApplication.h"

Let's look at CAADlgHelloApplication.h, the application header file:
    class CAADlgHelloApplication: public CATInteractiveApplication {

      public:

        CAADlgHelloApplication(const CATString &iIdentifier);

        virtual ~CAADlgHelloApplication(#);
        void **BeginApplication**(#);
        int **EndApplication**(#);

    };

---

We find here:

  * the _CAADlgHelloApplication_ class declaration which derives from the _CATInteractiveApplication_ class
  * its constructor and destructor
  * the `BeginApplication` and `EndApplication` methods overridden from the _CATInteractiveApplication_ class

The CAADlgHelloApplication.cpp looks like that:

    #include "CAADlgHelloApplication.h"
    #include "CAADlgHelloWindow.h"

    CAADlgHelloApplication::CAADlgHelloApplication(const CATString& iIdentifier):
                            **CATInteractiveApplication**(NULL, iIdentifier) {}

CAADlgHelloApplication::CAADlgHelloApplication(const CATString& iIdentifier):
    CAADlgHelloApplication::~CAADlgHelloApplication(#) {}

    void CAADlgHelloApplication::**BeginApplication**(#)

    {

CAADlgHelloApplication::~CAADlgHelloApplication(#) {}
void CAADlgHelloApplication::**BeginApplication**(#)
      CAADlgHelloWindow * pMainWindow = new **CAADlgHelloWindow**(this);

      pMainWindow->**Build**(#);

      pMainWindow->**SetVisibility**(CATDlgShow);

    }

pMainWindow->**Build**(#);
pMainWindow->**SetVisibility**(CATDlgShow);
    int CAADlgHelloApplication::**EndApplication**(#)

    {
pMainWindow->**SetVisibility**(CATDlgShow);
int CAADlgHelloApplication::**EndApplication**(#)
      return(**0**);

    }

int CAADlgHelloApplication::**EndApplication**(#)
return(**0**);
    CAADlgHelloApplication **ApplicationInstance**("Hello");

---

The constructor is empty. It leaves the constructors of the inherited classes run, and it automatically runs the method `BeginApplication` which constructs the application window and makes it visible. The method `EndApplication` only returns 0 to state that all is Ok . The application run is just triggerred by the its instantiation in the last statement.

[Top]
#### Creating the Application Window

Let's look at CAADlgHelloWindow.h, the application window header file:

    #include "CATDlgDocument.h"

Let's look at CAADlgHelloWindow.h, the application window header file:
    class CATInteractiveApplication;

    class CAADlgHelloWindow : public **CATDlgDocument**

    {

      **DeclareResource**(CAADlgHelloWindow, CATDlgDocument)

class CAADlgHelloWindow : public **CATDlgDocument**
      public:

        CAADlgHelloWindow(CATInteractiveApplication * iParentCommand);

        virtual ~CAADlgHelloWindow(#);

        void     **Build**(#);

      private:

        void **Exit** (CATCommand           * iSendingCommand,
                    CATNotification      * iSentNotification,
                    CATCommandClientData   iUsefulData);

      private:

        **CATInteractiveApplication** * _pHelloApplication;

    };

---

We find here:

  * The _CAADlgHelloWindow_ class declaration which derives from the _CATDlgDocument_ class
  * The `DeclareResource` macro which allows to retrieve the class resources, such as character strings displayed in the window, from an external resource file
  * The class constructor
  * the `Build` method used to create and value the window components
  * The `Exit` method used to close the application when the end user closes the window
  * A reference to the application.

The file CAADlgHelloWindow.cpp looks like that:

    #include "CAADlgHelloWindow.h"
    #include "CATInteractiveApplication.h"
    #include "CATDlgInclude.h"

    CAADlgHelloWindow::CAADlgHelloWindow(CATInteractiveApplication * iParentCommand)
    : **CATDlgDocument**(iParentCommand, "CAADlgHelloWindowId"),_pHelloApplication(iParentCommand)

    {
    }

    CAADlgHelloWindow::~CAADlgHelloWindow(#)
    {
      _pHelloApplication = NULL ;
    }

CAADlgHelloWindow::~CAADlgHelloWindow(#)
_pHelloApplication = NULL ;
    void CAADlgHelloWindow::Build(#)

    {

      CATDlgLabel * pLabel = new **CATDlgLabel**(this,"MessageId");

      AddAnalyseNotificationCB(this,
```vbscript
                                GetWindCloseNotification(#),
```

                               (CATCommandMethod)&CAADlgHelloWindow::**Exit** , NULL);

    }

```cpp
GetWindCloseNotification(#),
(CATCommandMethod)&CAADlgHelloWindow::**Exit** , NULL);
    void CAADlgHelloWindow::**Exit**(CATCommand         * iSendingCommand,
                               CATNotification    * iSentNotification,
                               CATCommandClientData iUsefulData)
```

    {
void CAADlgHelloWindow::**Exit**(CATCommand         * iSendingCommand,
CATNotification    * iSentNotification,
CATCommandClientData iUsefulData)
       _pHelloApplication->**Destroy**(#);
       _pHelloApplication = NULL ;

    }

---

_pHelloApplication = NULL ;
The constructor for _CAADlgHelloWindow_ only values the `_pHelloApplication` data member. The `Build` method creates the message to display as a _CATDlgLabel_ instance, sets character string to display in the message, and registers the method `Exit` to be called when the window is closed. This method destroys the application. This also deletes the window. Always use a `Build` method, and never instantiate dialog objects in the window constructor.

The message file that contains the displayed messages is as follows.

    Title           = "Hello Application";
```vbscript
    MessageId.Title = "Hello, CAA V5";

```

---

Title           = "Hello Application";
MessageId.Title = "Hello, CAA V5";
The first message is the window title and has the simple key `Title`. The second one is the displayed message and its key is built using the identifier passed as second argument of the label constructor, concatenated with a dot to the `Title` keyword.

[Top]

* * *
### In Short

This use case enables you to have a first approach with the Dialog framework concepts. In the `Build` method of the application window you can test the Dialog objects [4]

[Top]

* * *
### References

[1] | [The Burger Order Dialog Box](CAADlgBurger.md)
---|---
[2] | [Designing Your Interactive Application](../CAADlgTechArticles/CAADlgInteractiveApplication.md)
[3] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
[4] | [Dialog Overview](../CAADlgTechArticles/CAADlgOverview.md)
[Top]

* * *
### History

Version: **1** [Fev 2003] | Document created
---|---
[Top]

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
