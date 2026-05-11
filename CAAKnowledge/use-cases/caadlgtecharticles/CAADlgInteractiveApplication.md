---
```vbscript
title: "Designing Your Interactive Application"
category: "use-case"
module: "CAADlgTechArticles"
tags: ["CAADlgWindowApplication", "CAADlgInterWindow", "CAADlgInterWindowId", "CAADlgInterApplication", "CATInteractiveApplication", "CAADialog"]
source_file: "Doc/online/CAADlgTechArticles/CAADlgInteractiveApplication.htm"
converted: "2026-05-11T17:17:56.042541"
```

---
# 3D PLM Enterprise Architecture

| 
## User Interface - Dialogs

| 
### Designing Your Interactive Application

_How to create a separate interactive application_  
---|---|---  
Technical Article  

* * *
### Abstract

This article explains you how to create an interactive application, along with the methods you should overwrite from the interactive application base class 

  * **What Is an Interactive Application?**
  * **An Interactive Application Example**
  * **In Short**

---  

* * *
### What Is an Interactive Application?

A CAA V5 interactive application is a program that you can launch and that can execute generally with end user input until the end-user stops it. The base class for CAA V5 interactive applications is the the _CATInteractiveApplication_ class. The Dialog framework gives you some key components to design you interactive application. They include: 

  * The _CATInteractiveApplication_ class to derive to create your application
  * The _[CATDlgDocument](../CAADlgQuickRefs/CAADlgCATDlgDocument.md)_ class to derive to create your application main window and presentations
  * The _[CATDlgDialog](../CAADlgQuickRefs/CAADlgCATDlgDialog.md)_ class to derive to create the transient window your dialog requires.

The figure below shows the objects involved and their main methods using the Unified Modeling Language (UML).

![CATInteractiveApplication.jpg \(30073 bytes\)](images/CATInteractiveApplication.jpg)

The application derives from the _CATInteractiveApplication_ class while the window derives from the _CATDlgDocument_ class. The application aggregates a pointer to the window and instantiates it in the `BeginApplication` method. Symmetrically, the window aggregates a pointer to the application.

![warning.gif \(206 bytes\)](../CAAIcons/images/warning.gif) Note that the window constructor does not include any statement. It only instantiates, that is allocates memory areas for the window and its base classes. The `Build` method is dedicated to create the objects with the proper values. This is because the external resources to allocate use virtual methods, and as long as the constructor is not exited, the virtual method table update may not be completed and thus its contents may be inaccurate. This `Build` method does not exist in any Dialog framework base class and thus can not be redefined. You must create it when deriving a Dialog framework class.

[Top]
### An Interactive Application Example

The following sample is a standard application skeleton with a main window. It includes the main objects shown in the figure and their related methods. You retrieve the two classes, _CAADlgInterApplication_ and _CAADlgInterWindow_ in the CAADialog.edu framework in the CAADlgInterApplication.m module.

First look at the _CAADlgInterApplication_ header file:

    #include "CATInteractiveApplication.h"
The following sample is a standard application skeleton with a main window. It includes the main objects shown in the figure and their related methods. You retrieve the two classes, _CAADlgInterApplication_ and _CAADlgInterWindow_ in the CAADialog.edu framework in the CAADlgInterApplication.m module.
First look at the _CAADlgInterApplication_ header file:
    class CAADlgInterApplication : public CATInteractiveApplication

    {
First look at the _CAADlgInterApplication_ header file:
class CAADlgInterApplication : public CATInteractiveApplication
      public:
        CAADlgInterApplication (const CATString & iAppliName);
        virtual void BeginApplication();
        virtual int  EndApplication();
        virtual ~MyApplication();

    };

---  

and at the CAADlgInterWindow header file:

    #include "CATDlgDocument.h"
and at the CAADlgInterWindow header file:
    class CATInteractiveApplication;
    class CAADlgInterWindow: public CATDlgDocument

    {
class CATInteractiveApplication;
class CAADlgInterWindow: public CATDlgDocument
      public:
        CAADlgInterWindow(CATInteractiveApplication * pp);
        virtual ~CAADlgInterWindow();
        void Build();    
      private:                                          
        void CloseAppli(CATCommand           * iSendingCommand,    
                        CATNotification      * iSentNotification,
                        CATCommandClientData   UsefulData);

        ...
private:
void CloseAppli(CATCommand           * iSendingCommand,
CATNotification      * iSentNotification,
CATCommandClientData   UsefulData);
      private:            
        CATInteractiveApplication * _pApplication;

    };  

---  

CATInteractiveApplication * _pApplication;
These class declarations follow the diagram. A pointer to the application is stored as a document data member. The document includes a `Build` method to valuate its objects rather than doing this in the constructor. The method `CloseAppli` is used to close both the application and the document when the user requests it.

The _CAADlgInterApplication_ source file:

    CAADlgInterApplication ::CAADlgInterApplication (const CATString & IAppliName)

                 :**CATInteractiveApplication**(NULL, IAppliName)
    { }

CAADlgInterApplication ::CAADlgInterApplication (const CATString & IAppliName)
    void CAADlgInterApplication ::**BeginApplication**() 

    {
void CAADlgInterApplication ::**BeginApplication**()
      MyDoc = new CAADlgInterWindow(this);
      MyDoc->Build();
      SetVisibility(CATDlgShow);          // make window visible

    }

MyDoc = new CAADlgInterWindow(this);
MyDoc->Build();
SetVisibility(CATDlgShow);          // make window visible
    int  CAADlgInterApplication ::**EndApplication**()    // called by Destroy

    { return **0** ; }

int  CAADlgInterApplication ::**EndApplication**()    // called by Destroy
    CAADlgInterApplication ::~MyApplication() { }

    CAADlgInterApplication **ApplicationInstance** ("MyNiceApplication"); // instantiate the application  

---  

The _CAADlgWindowApplication_ source file is the following:

    ...
The _CAADlgWindowApplication_ source file is the following:
    CAADlgInterWindow ::CAADlgInterWindow (CATInteractiveApplication * iParentCommand)

       :**CATDlgDocument**(iParentCommand, "CAADlgInterWindowId"),
       _pApplication(iParentCommand)  
    {
      // Empty constructor to allocate, but not to valuate
    }

    void CAADlgInterWindow ::Build() {
      ... // Put here the code required to build the window
      // set a callback to close the application when closing the window
void CAADlgInterWindow ::Build() {
      AddAnalyseNotificationCB(this,
                               GetWindCloseNotification(),
                               (CATCommandMethod)&MyDocument::CloseAppli,
                               NULL);

    }
```vbscript
AddAnalyseNotificationCB(this,
GetWindCloseNotification(),
(CATCommandMethod)&MyDocument::CloseAppli,
NULL);
    CAADlgInterWindow ::~CAADlgInterWindow () { }

    void CAADlgInterWindow ::CloseAppli            // close the application
                   (CATCommand * _ICommand,
                    CATNotification * _INotification,
                    CATCommandClientData UsefulData)
```

    { _pApplication->**Destroy**(); 
void CAADlgInterWindow ::CloseAppli            // close the application
(CATCommand * _ICommand,
CATNotification * _INotification,
CATCommandClientData UsefulData)
      _pApplication = NULL ; 

    }

---  

[Top]

* * *
### In Short

The interactive application is simply instantiated without the need of creating any main program. The main dialog window derives from the appropriate dialog window class, and includes a Build method to create the containers and controls that make up the window, rather than using the window constructor to do this. The application and the window aggregates the other by reference.

[Top]

* * *
### History

Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
