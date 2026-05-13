---
title: "Untitled"
category: "use-case"
module: "CAADlgUseCases"
tags: ["CATInteractiveApplication", "CAADlgHelloWindowId", "CATIA", "CAADlgBurger", "CAADocStyleSheets", "CAADlgInteractiveApplication", "CAADocRunSample", "CAADlgHelloApplication", "CAADlgOverview", "CAADocUseCases", "CAADialog", "CAADlgTechArticles", "CAADlgHelloWindow"]
source_file: "Doc/online/CAADlgUseCases/CAADlgSampleGettingStarted.htmmd"
converted: "2026-05-11T11:27:02.797370"
---

---

---

### What You Will Learn With This Use Case

The Dialog framework is intended to help application developers to simply
design an implement their dialog windows and boxes. Its main characteristics
are:

  
- Programmer productivity: it provides high-level objects that allow for
    component reusability
  
- Portability: the objects created can be implemented on Motif and Windows
    platforms without any change or customization
  
- Standard compliance: it is built on top of the OSF/Motif and MFC layers
  
- Versatility: it can be used as a standalone framework, along with its
    prerequisites, or in a CATIA Version 4 or Version 5 environment.

Let's have a look at this framework through two examples. The first sample
program shows how to build a very simple window and how to close it. The second
sample introduces a larger number of dialog window components or objects and how
to manage window layouts as well as triggering actions when clicking on Dialog
framework objects [1].

[Top]

### The CAADlgHelloApplication Use Case

CAADlgHelloApplication is a use case of the CAADialog.edu framework that
illustrates Dialog framework capabilities.

[Top]

#### What Does CAADlgHelloApplication Do

For this example, you will simply display a prompt box that prints
"Hello, CAA V5". To do this, derive your own application class, called
*CAADlgHelloApplication*, from the class *CATInteractiveApplication* [2].
This application will:

  
- create a window to display "Hello, CAA V5" by deriving the class
    *CATDlgDocument*
  
- makes the window visible.

In addition, the mechanism to close the application from the window is
included. The window is as follows:

[Top]

#### How to Launch CAADlgHelloApplication

To launch CAADlgHelloApplication, you will need to set up the build time environment,
then compile CAADlgHelloApplication along with its prerequisites, set up the run time
environment, and then execute the use case [3].

[Top]

#### Where to Find the CAADlgHelloApplication Code

The CAADlgHelloApplication use case is made of a several classes located in
the CAADlgHelloApplication.m module of the CAADialog.edu framework:

where `InstallRootDirectory` is the directory where the CAA CD-ROM
is installed.

The CAADlgHelloApplication.m module includes four files:

The resource file CAADlgHelloWindow.CATNls is located in the CNext/resources/msgcatalog
directory.

[Top]

### Step-by-Step

There are two logical steps in CAADlgHelloApplication:

  
- Creating the Interactive Application
  
- Creating the Application Window

[Top]

#### Creating the Interactive Application

Let's look at CAADlgHelloApplication.h, the application header file:

We find here:

  
- the *CAADlgHelloApplication* class declaration which derives from the
    *CATInteractiveApplication* class
  
- its constructor and destructor
  
- the `BeginApplication` and `EndApplication` methods
    overridden from the *CATInteractiveApplication* class

The CAADlgHelloApplication.cpp looks like that:

The constructor is empty. It leaves the constructors of the inherited classes
run, and it automatically runs the method `BeginApplication` which
constructs the application window and makes it
visible. The method `EndApplication` only returns 0 to state that all
is Ok . The application
run is just triggerred by the its instantiation in the last statement.

[Top]

#### Creating the Application Window

Let's look at CAADlgHelloWindow.h, the application window header file:

We find here:

  
- The *CAADlgHelloWindow* class declaration which derives from the *CATDlgDocument*
    class
  
- The `DeclareResource` macro which allows to retrieve the class
    resources, such as character strings displayed in the window, from an
    external resource file
  
- The class constructor
  
- the `Build` method used to create and value the window
    components
  
- The `Exit` method used to close the application when the end
    user closes the window
  
- A reference to the application.

The file CAADlgHelloWindow.cpp looks like that:

The constructor for *CAADlgHelloWindow* only values the `_pHelloApplication`
data member. The `Build` method creates the message to display as a *CATDlgLabel*
instance, sets character string to display in the message, and registers the
method `Exit` to be called when the window is closed. This method
destroys the application. This also deletes the window. Always use a `Build`
method, and never instantiate dialog objects in the window constructor.

The message file that contains the displayed messages is as follows.

The first message is the window title and has the simple key `Title`.
The second one is the displayed message and its key is built using the
identifier passed as second argument of the label constructor, concatenated with
a dot to the `Title` keyword.

[Top]

---

### In Short

This use case enables you to have a first approach with the Dialog framework
concepts. In the `Build` method of the application window you can
test the Dialog objects [4]

[Top]

---

### References

---

### History

---

*Copyright  2003, Dassault Systmes. All rights reserved.*

```vbscript
#include &quot;CATInteractiveApplication.h&quot;

class CAADlgHelloApplication: public CATInteractiveApplication {

  public:

    CAADlgHelloApplication(const CATString &amp;iIdentifier);

    virtual ~CAADlgHelloApplication(#);
    void BeginApplication(#);
    int EndApplication(#);

};
```

```vbscript
#include &quot;CAADlgHelloApplication.h&quot;
#include &quot;CAADlgHelloWindow.h&quot;

CAADlgHelloApplication::CAADlgHelloApplication(const CATString&amp; iIdentifier):
                        CATInteractiveApplication(NULL, iIdentifier) {}
                        
CAADlgHelloApplication::~CAADlgHelloApplication(#) {}

void CAADlgHelloApplication::BeginApplication(#) 
{
 
  CAADlgHelloWindow * pMainWindow = new CAADlgHelloWindow(this);

  pMainWindow-&gt;Build(#);

  pMainWindow-&gt;SetVisibility(CATDlgShow);
}

int CAADlgHelloApplication::EndApplication(#) 
{
  return(0);
}

CAADlgHelloApplication ApplicationInstance(&quot;Hello&quot;);
```

```vbscript
#include &quot;CATDlgDocument.h&quot;   

class CATInteractiveApplication;   

class CAADlgHelloWindow : public CATDlgDocument
{
 
  DeclareResource(CAADlgHelloWindow, CATDlgDocument)

  public:
 
    CAADlgHelloWindow(CATInteractiveApplication * iParentCommand);

    virtual ~CAADlgHelloWindow(#);

    void     Build(#);

  private:

    void Exit (CATCommand           * iSendingCommand, 
                CATNotification      * iSentNotification, 
                CATCommandClientData   iUsefulData);

  private:
    CATInteractiveApplication * _pHelloApplication;

    
};
```

```vbscript
#include &quot;CAADlgHelloWindow.h&quot;

#include &quot;CATInteractiveApplication.h&quot; 
#include &quot;CATDlgInclude.h&quot;

CAADlgHelloWindow::CAADlgHelloWindow(CATInteractiveApplication * iParentCommand)                              
: CATDlgDocument(iParentCommand, &quot;CAADlgHelloWindowId&quot;),_pHelloApplication(iParentCommand)

{
}

CAADlgHelloWindow::~CAADlgHelloWindow(#)
{ 
  _pHelloApplication = NULL ;
}

void CAADlgHelloWindow::Build(#)
{
 
  CATDlgLabel * pLabel = new CATDlgLabel(this,&quot;MessageId&quot;);

  
  AddAnalyseNotificationCB(this,
                            GetWindCloseNotification(#),
                           (CATCommandMethod)&amp;CAADlgHelloWindow::Exit, NULL);

}

void CAADlgHelloWindow::Exit(CATCommand         * iSendingCommand, 
                           CATNotification    * iSentNotification, 
                           CATCommandClientData iUsefulData)
{
   _pHelloApplication-&gt;Destroy(#);
   _pHelloApplication = NULL ;
}
```

```vbscript
Title           = &quot;Hello Application&quot;;
MessageId.Title = &quot;Hello, CAA V5&quot;;
```