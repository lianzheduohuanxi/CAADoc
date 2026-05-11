---
```vbscript
title: "Making Your Document Independent Command Available in All Workbenches"
category: "use case"
module: "CAAAfrUseCases"
tags: ["CAAAfrGeneralWksAddinHeader", "CAAAfrGeneralViewFBStr", "CAAAfrViewerFeedbackStr", "CAAAfrGeneralView", "CAAAfrGeneralWksTlb", "CAAAfrGeneralWksMbr", "CATIWorkbenchAddin", "CAAMmrGeneralSearchStr", "CAAAfrGeneralEditMnu", "CAAAfrViewerFeedbackHdr", "CAAAfrGeneralEditSearchStr", "CAASearch", "CAAAfrGeneralWksAddin", "CAACafSearchCmd", "CAAApplicationFrame", "CAACafSearch", "CAAAfrSearchHdr", "CAAAfrSearchStr", "CATIAfrGeneralWksAddin"]
source_file: "Doc/online/CAAAfrUseCases/CAAAfrSampleGeneralWksAddin.htm"
converted: "2026-05-11T17:17:55.744995"
```

---
# 3D PLM Enterprise Architecture

| 
## User Interface - Frame

| 
### Making Your Document Independent Command Available in All Workbenches

_Using CATIAfrGeneralWksAddin_  
---|---|---  
Use Case  

* * *
### Abstract

This article shows how to insert a document independent command in all workbenches of a V5 application. 

  * **What You Will Learn With This Use Case**
  * **The CAAAfrGeneralWksAddin Use Case**
    * What Does CAAAfrGeneralWksAddin Do
    * How to Launch CAAAfrGeneralWksAddin
    * Where to Find the CAAAfrGeneralWksAddin Code
  * **Step-by-Step**
  * **In Short**
  * **References**

* * *
### What You Will Learn With This Use Case

This use case is intended to show you how to create a toolbar and modify the menu bar to integrate your document independent command in all workbenches. You will learn to implement an interface, the _CATIAfrGeneralWksAddin interface,_ which is an Add-in [1] of the "General" workshop [2]. This workshop contains the commands which are always available even if no document is open: New, Open, Cut,....  [Top]
### The CAAAfrGeneralWksAddin Use Case

CAAAfrGeneralWksAddin is a use case of the CAAApplicationFrame.edu framework that illustrates ApplicationFrame framework capabilities. [Top]
#### What Does CAAAfrGeneralWksAddin Do

The CAAAfrGeneralWksAddin creates an add-in to the **General** workshop. Is is made up of: 

  * a single toolbar

---  

The **General** toolbar. It contains in first position the Search Demonstrator [3] command, then the Viewer Feedback demonstrator [9] command, and at last the "Add Item in MRU" command [11].

  * menu items 

The Search Demonstrator command is included in the Edit menu, just before Search, whereas the Viewer Feedback demonstrator command is set in the View menu.

[Top]
#### How to Launch CAAAfrGeneralWksAddin

The Search Demonstrator command is included in the Edit menu, just before Search, whereas the Viewer Feedback demonstrator command is set in the View menu.
To launch CAAAfrGeneralWksAddin , you will need to set up the build time environment, then compile CAAAfrGeneralWksAddin along with its prerequisites, set up the run time environment, and then execute the use case [4].

But just before launching the execution, edit the CAAApplicationFrame.edu.dico interface dictionary file located in the dictionary directory of the CAAApplicationFrame.edu framework:

Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CNext\code\dictionary\`  

But just before launching the execution, edit the CAAApplicationFrame.edu.dico interface dictionary file located in the dictionary directory of the CAAApplicationFrame.edu framework:
Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CNext\code\dictionary\`
UNIX | `InstallRootDirectory/CAAApplicationFrame.edu/CNext/code/dictionary/`  

In this file, remove the "**#** " character before the two following lines:

    ...
    #CAAAfrGeneralWksAddin       CATIWorkbenchAddin          libCAAAfrGeneralWksAddin  
    #CAAAfrGeneralWksAddin       CATIAfrGeneralWksAddin      libCAAAfrGeneralWksAddin
    ...  

---  

and run mkCreateRuntimeView.

[Top]
#### Where to Find the CAAAfrGeneralWksAddin Code

and run mkCreateRuntimeView.
The CAAAfrGeneralWksAddin use case is made of a single class named _CAAAfrGeneralWksAdn_ located in the CAAAfrGeneralWksAddin.m module of the CAAApplicationFrame.edu framework:

Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CAAAfrGeneralWksAddin.m\`  

The CAAAfrGeneralWksAddin use case is made of a single class named _CAAAfrGeneralWksAdn_ located in the CAAAfrGeneralWksAddin.m module of the CAAApplicationFrame.edu framework:
Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CAAAfrGeneralWksAddin.m\`
Unix | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeneralWksAddin.m/`  

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
To create the add-in, you should create the module directory to store the add-in code along with its two subdirectories LocalInterfaces and src. For this example, this directory is named CAAAfrGeneralWksAddin.m and can be found in the CAAApplicationFrame.edu framework. Then you will need to create the following files.

In the CAAAfrGeneralWksAddin.m\LocalInterfaces directory:  

---  

  * CAAAfrGeneralWksAdn.h

| The header file of the add-in description class  
In the CAAAfrGeneralWksAddin.m\src directory:  

  * CAAAfrGeneralWksAdn.cpp

| The header file of the add-in description class  
In the dictionary, that is the CNext\code\dictionary directory, referenced at run time using the CATDictionaryPath environment variable, create or update:  

  * CAAApplicationFrame.edu.dico

| The interface dictionary  
In the CNext\resources\msgcatalog directory, referenced at run time using the CATMsgCatalogPath environment variable:  

  * CAAAfrGeneralWksAdn.CATNls

| The add-in message file  

  * CAAAfrGeneralWksAddinHeader.CATNls and  
  CAAAfrGeneralWksAddinHeader.CATRsc

| The command header resource files  

There are four logical steps in CAAAfrGeneralWksAddin:
# | Step | Where  
---|---|---  
There are four logical steps in CAAAfrGeneralWksAddin:
1 | Create the add-in description class | LocalInterfaces and src  
2 | Create the command headers | `CreateCommands` method  
3 | Create the add-in and arrange the commands | `CreateToolbars` method  
4 | Provide the resources  

[Top]
#### Create the add-in description class

  1. Create the CAAAfrGeneralWksAdn.h file 
         #include "CATBaseUnknown.h"

1. Create the CAAAfrGeneralWksAdn.h file
         class CATCmdContainer;

         class CAAAfrGeneralWksAdn : public CATBaseUnknown

         {
class CATCmdContainer;
class CAAAfrGeneralWksAdn : public CATBaseUnknown
           CATDeclareClass;

           public:
              CAAAfrGeneralWksAdn();
              virtual ~CAAAfrGeneralWksAdn();

              // Creates the command headers
public:
CAAAfrGeneralWksAdn();
virtual ~CAAAfrGeneralWksAdn();
              void CreateCommands();

              // Arranges the commands in toolbars and menubar
void CreateCommands();
              CATCmdContainer * CreateToolbars();

           private :

              // Copy constructor, not implemented
              // Set as private to prevent from compiler automatic creation as public.
              CAAAfrGeneralWksAdn(const CAAAfrGeneralWksAdn &iObjectToCopy);

              // Assigment operator, not implemented
              // Set as private to prevent from compiler automatic creation as public.
              CAAAfrGeneralWksAdn & operator = (const CAAAfrGeneralWksAdn &iObjectToCopy);
         };  

---  
  2. Create the CAAAfrGeneralWksAdn.cpp file

    // Local Framework
    #include "CAAAfrGeneralWksAdn.h"

    // ApplicationFrame Framework 
    #include <CATCreateWorkshop.h>    // To use NewAccess - SetAccess - SetAccessChild ...

    // Declaration of a new Command Header Class 
    #include "CATCommandHeader.h"        // See Creating the Command Headers
    MacDeclareHeader(CAAAfrGeneralWksAddinHeader);  

```vbscript
MacDeclareHeader(CAAAfrGeneralWksAddinHeader);
    CATImplementClass(CAAAfrGeneralWksAdn, DataExtension,
                      CATBaseUnknown, **CAAAfrGeneralWksAddin**);
```

    #include <TIE_**CATIAfrGeneralWksAddin**.h>
```vbscript
MacDeclareHeader(CAAAfrGeneralWksAddinHeader);
CATImplementClass(CAAAfrGeneralWksAdn, DataExtension,
CATBaseUnknown, **CAAAfrGeneralWksAddin**);
    TIE_CATIAfrGeneralWksAddin(CAAAfrGeneralWksAdn);

    CAAAfrGeneralWksAdn::CAAAfrGeneralWksAdn()
```

    {}

```vbscript
TIE_CATIAfrGeneralWksAddin(CAAAfrGeneralWksAdn);
CAAAfrGeneralWksAdn::CAAAfrGeneralWksAdn()
    CAAAfrGeneralWksAdn::CAAAfrGeneralWksAdn()
```

    {}

    void CAAAfrGeneralWksAdn::CreateCommands()
    {
      ... // See Creating the Command Headers
    }

    CATCmdContainer * CAAAfrGeneralWksAdn::CreateToolbars()
    {
      ... // See Creating the Toolbar and Arranging the Commands
    }

---  

The _CAAAfrGeneralWksAdn_ class states that it implements the _CATIAfrGeneralWksAddin_ interface thanks to the `TIE_``CATIAfrGeneralWksAddin` macro. The `CATImplementClass` macro declares that the _CAAAfrGeneralWksAdn_ class is a data extension, thanks to the `DataExtension` keyword, that extends _CAAAfrGeneralWksAddin_. The third argument must always be set as _CATBaseUnknown_ or _CATNull_ for any kind of extension.

The _CAAAfrGeneralWksAdn_ class states that it implements the _CATIAfrGeneralWksAddin_ interface thanks to the `TIE_``CATIAfrGeneralWksAddin` macro. The `CATImplementClass` macro declares that the _CAAAfrGeneralWksAdn_ class is a data extension, thanks to the `DataExtension` keyword, that extends _CAAAfrGeneralWksAddin_. The third argument must always be set as _CATBaseUnknown_ or _CATNull_ for any kind of extension.
  3. Updating the Dictionary

Update the interface dictionary, that is a file named, for example, CAAApplicationFrame.dico, whose directory's pathname is concatenated at run time in the CATDictionaryPath environment variable, and containing the following declaration to state that the _CAAAfrGeneralWksAddin_ component implements the _CATIAfrGeneralWksAddin_ interface, and whose code is located in the libCAAAfrGeneralWksAddin shared library or DLL.

         CAAAfrGeneralWksAddin CATIAfrGeneralWksAddin libCAAAfrGeneralWksAddin  

---  

Note that the component main class name is used to refer to the component in the interface dictionary, and never the extension class names. Note also that the shared library or DLL to associate with the component/interface pair is the one that contains the code created by the call to the TIE macro (This is generally the same library than the one that contains the interface implementation code, since the TIE macro is usually included in the extension class source file.) This is because when a client asks a component for an interface pointer, the TIE class is instantiated first, and it either retrieves the existing instance of the appropriate extension class, or otherwise instantiates it.

[Top]
#### Create the command headers

Note that the component main class name is used to refer to the component in the interface dictionary, and never the extension class names. Note also that the shared library or DLL to associate with the component/interface pair is the one that contains the code created by the call to the TIE macro (This is generally the same library than the one that contains the interface implementation code, since the TIE macro is usually included in the extension class source file.) This is because when a client asks a component for an interface pointer, the TIE class is instantiated first, and it either retrieves the existing instance of the appropriate extension class, or otherwise instantiates it.
Before reading this section, you can you refer to the "The Command Headers" article [5] to have an overview of the command header concepts, and more precisely you have the "Defining Headers in CATIAfrGeneralWksAddin implementations" section, which details the specificities of command headers created in this general add-in.  

This is done by the `CreateCommands` method. Each command available in your add-in should be represent by a command header. A command header is an instance of a command header class.

The command header class, named CAAAfrGeneralWksAddinHeader, is created using the `MacDeclareHeader` macro. 

  1. Create the CAAAfrGeneralWksAddinHeader command header class. To do this, add the following lines in CAAAfrGeneralWksAdn.cpp: 

         #include "CATCommandHeader.h"
The command header class, named CAAAfrGeneralWksAddinHeader, is created using the `MacDeclareHeader` macro.
1. Create the CAAAfrGeneralWksAddinHeader command header class. To do this, add the following lines in CAAAfrGeneralWksAdn.cpp:
         MacDeclareHeader(CAAAfrGeneralWksAddinHeader);  

---  

```vbscript
MacDeclareHeader(CAAAfrGeneralWksAddinHeader);
The `MacDeclareHeader` macro creates the header file and the source file for the CAAAfrGeneralWksAddinHeader class, and associates with this class the resource files CAAAfrGeneralWksAddinHeader.CATNls and CAAAfrGeneralWksAddinHeader.CATRsc. See Providing the Resources.

  2. Create the command headers in the `CreateCommands` method. This method should contain one instantiation statement of the command header class per command header. Each statement has the following form. 

         void CAAAfrGeneralWksAdn::CreateCommands()
```

         {
           ...
2. Create the command headers in the `CreateCommands` method. This method should contain one instantiation statement of the command header class per command header. Each statement has the following form.
void CAAAfrGeneralWksAdn::CreateCommands()
            new **CAAAfrGeneralWksAddinHeader**("**CAAAfrSearchHdr** ", 

                                      "CAACafSearch", 
                                      "CAACafSearchCmd", (void *)NULL);
           ...
         }    

---  

The command header constructor has the following arguments: 
     * `CAAAfrSearchHdr` is the identifier you need to assign to the command header. It will be used afterwards: 
       * To associate the command starters you will define to put the command in a menu and in toolbars with the command header. This is done for this add-in in Creating the Toolbar and Arranging the Commands. 
       * To build the variables that define the command header resources, such as the help messages seen by the end user in his/her own language, or the icon to display in the toolbar. This is explained in Providing the Resources
     * `CAACafSearch` is the name of the shared library or DLL containing the Search Demonstrator command's code, without the prefix lib, and without the suffix depending on the operating system. 
     * `CAACafSearchCmd` is the name of the Search Demonstrator command class 
     * the last argument is the possible pointer to the object to pass to the command when executing it. 

The command header associated with the Viewer Feedback demonstrator - see What Does CAAAfrGeneralWksAddin Do \- is described in the use case [10].

The command header associated with the Most Recent Used header is described in the use case [11].

[Top]

#### Create the add-in and arrange the commands

Finally, we'll create the toolbar and arrange the commands. This is the job of the `CreateToolbars` method.

  * Creating the toolbar 

Finally, we'll create the toolbar and arrange the commands. This is the job of the `CreateToolbars` method.
        CATCmdContainer * CAAAfrGeneralWksAdn::CreateToolbars()

        {
CATCmdContainer * CAAAfrGeneralWksAdn::CreateToolbars()
          NewAccess(CATCmdContainer, pCAAAfrGeneralWksTlb, CAAAfrGeneralWksTlb);

          NewAccess(CATCmdStarter, pCAAAfrSearchStr, CAAMmrGeneralSearchStr);
          SetAccessCommand(pCAAAfrSearchStr, "**CAAAfrSearchHdr** ");
          SetAccessChild(pCAAAfrGeneralWksTlb, pCAAAfrSearchStr);

          NewAccess(CATCmdStarter, pCAAAfrViewerFeedbackStr, CAAAfrViewerFeedbackStr);
          SetAccessCommand(pCAAAfrViewerFeedbackStr, "**CAAAfrViewerFeedbackHdr** ");
          SetAccessNext(pCAAAfrSearchStr, pCAAAfrViewerFeedbackStr);

          NewAccess(CATCmdStarter, pCAAAfrMRUAddElementStr, CAAAfrMRUAddElementStr);
          SetAccessCommand(pCAAAfrMRUAddElementStr, "CAAAfrMRUAddElementHdr");
          SetAccessNext(pCAAAfrViewerFeedbackStr, pCAAAfrMRUAddElementStr);

          **AddToolbarView**(pCAAAfrGeneralWksTlb, 1, Right); 

          ...
        }  

---  

Here is what's happen: 
    * The General toolbar is created as an instance of the _CATCmdContainer_ class using the `NewAccess` macro. `pCAAAfrGeneralWksTlb` is the variable used to handle the General toolbar command container instance pointer, and `CAAAfrGeneralWksTlb` is the identifier used to refer to it in the add-in resource files. This identifier must be unique among all the toolbar identifiers that can be found within the application [6]. The General toolbar default location is defined using the `AddToolbarView` macro, where `1` means that the toolbar is visible by default (-`1` means invisible), and `Right` means that the toolbar is docked at the right side of the application window. 
    * Three macros are required for each command. 
Here is what's happen:
      1. First, the command starter is created as a _CATCmdStarter_ instance using the `NewAccess` macro. `pCAAAfrSearchStr` is the variable used to handle a pointer to that instance, and `CAAMmrGeneralSearchStr` is its identifier. 
      2. Then the command header is associated with this command starter using the `SetAccessCommand` macro. The second parameter is the command header identifier defined as the first parameter of the command header constructor. Refer to Creating the Command Headers
      3. Finally the command starter is set as the child of the General toolbar thanks to the `SetAccessChild `macro or next of the previous starter with the `SetAccessNext` macro.

  * Creating the menu items 

1. First, the command starter is created as a _CATCmdStarter_ instance using the `NewAccess` macro. `pCAAAfrSearchStr` is the variable used to handle a pointer to that instance, and `CAAMmrGeneralSearchStr` is its identifier.
2. Then the command header is associated with this command starter using the `SetAccessCommand` macro. The second parameter is the command header identifier defined as the first parameter of the command header constructor. Refer to Creating the Command Headers
3. Finally the command starter is set as the child of the General toolbar thanks to the `SetAccessChild `macro or next of the previous starter with the `SetAccessNext` macro.
        CATCmdContainer * CAAAfrGeneralWksAdn::CreateToolbars()

        {
          ...
CATCmdContainer * CAAAfrGeneralWksAdn::CreateToolbars()
          NewAccess(CATCmdContainer,pCAAAfrGeneralWksMbr,CAAAfrGeneralWksMbr);

          NewAccess(CATCmdContainer,pCAAAfrGeneralEditMnu,**CATAfrEditMnu**);
               SetAccessChild(pCAAAfrGeneralWksMbr,pCAAAfrGeneralEditMnu);

               NewAccess(CATCmdStarter,pCAAAfrGeneralEditSearchStr,CAAAfrGeneralEditSearchStr);
               SetAccessChild(pCAAAfrGeneralEditMnu,pCAAAfrGeneralEditSearchStr);
               SetAccessCommand(pCAAAfrGeneralEditSearchStr,"**CAAAfrSearchHdr** ");

               **SetAccessAnchorName**(pCAAAfrGeneralEditSearchStr,"CATAfrEditSearchStr");

```vbscript
NewAccess(CATCmdStarter,pCAAAfrGeneralEditSearchStr,CAAAfrGeneralEditSearchStr);
SetAccessChild(pCAAAfrGeneralEditMnu,pCAAAfrGeneralEditSearchStr);
SetAccessCommand(pCAAAfrGeneralEditSearchStr,"**CAAAfrSearchHdr** ");
          NewAccess(CATCmdContainer,pCAAAfrGeneralView,**CATAfrView**);
             SetAccessNext(pCAAAfrGeneralEditMnu,pCAAAfrGeneralView);

               NewAccess(CATCmdStarter,pCAAAfrGeneralViewFBStr,CAAAfrGeneralViewFBStr);
               SetAccessChild(pCAAAfrGeneralView,pCAAAfrGeneralViewFBStr);
               SetAccessCommand(pCAAAfrGeneralViewFBStr,"**CAAAfrViewerFeedbackHdr** ");

```

          **SetAddinMenu**(pCAAAfrGeneralWksTlb,pCAAAfrGeneralWksMbr);
          ...
        }  

---  

Here is what's happen: 
    * A container,`pCAAAfrGeneralWksMbr,` is created to receive two menus: 
      * pCAAAfrGeneralEditMnu for which the name is `CATAfrEditMnu`, the name of the Edit menu. pCAAAfrGeneralEditMnu is a child of `pCAAAfrGeneralWksMbr`
      * pCAAAfrGeneralView for which the name is `CATAfrView`, the name of the View menu. pCAAAfrGeneralView is the next of pCAAAfrGeneralEditMnu. 
    * Three macros are required for each command. 
Here is what's happen:
      1. First, the command starter is created as a CATCmdStarter instance using the `NewAccess` macro. `pCAAAfrGeneralEditSearchStr` is the variable used to handle a pointer to that instance, and `CAAAfrGeneralEditSearchStr` is its identifier. 
      2. Then the command header is associated with this command starter using the `SetAccessCommand` macro. The second parameter is the command header identifier defined as the first parameter of the command header constructor. Refer to Creating the Command Headers
      3. Finally the command starter is set as the child of the Menu bar

In this case, a last macro has been used: `NewAccessAnchorName `which enables you to locate the Search Demonstrator command just before the Search command (`CATAfrEditSearchStr`) [5]

    * The container, `pCAAAfrGeneralWksMbr`, declared as menu thanks to the `SetAddinMenu` method. The first argument of this method, `pCAAAfrGeneralWksTlb`, is the first chained toolbar, those returned by the method- see the next section. The second argument is the container itself `pCAAAfrGeneralWksMbr`. 

  * Returning the toolbar 

        CATCmdContainer * CAAAfrGeneralWksAdn::CreateToolbars()
        {
          ...

          return pCAAAfrGeneralWksTlb;
        }  

---  

The first chained toolbar, `pCAAAfrGeneralWksTlb`,  is returned by this method.

[Top]
#### Provide the resources

You should provide the resources for the toolbar, the menu and for all its commands. They are classified into the following: 

  * The toolbar's title. The Creating Resources for Workshops and Workbenches article details all the resources [7]. 

You should provide the resources for the toolbar, the menu and for all its commands. They are classified into the following:
The CAAAfrGeneralWksAdn.CATNls:

        CAAAfrGeneralWksTlb.Title   = "General" ;  

---  

  * The command header resources in the command header resource files: titles, messages, icons, and the accelerators associated with the commands. This is described in Creating Resources for Command Headers [8]

The CAAAfrGeneralWksAddinHeader.CATNls:

The CAAAfrGeneralWksAddinHeader.CATNls:
    CAAAfrGeneralWksAddinHeader.CAAAfrSearchHdr.Category  = "Edit" ;
    CAAAfrGeneralWksAddinHeader.CAAAfrSearchHdr.Title     = "Search Demonstrator..." ;
    CAAAfrGeneralWksAddinHeader.CAAAfrSearchHdr.ShortHelp = "Search Demonstrator" ;
    CAAAfrGeneralWksAddinHeader.CAAAfrSearchHdr.Help      = "Demonstrator of the Search CAA API" ;
    CAAAfrGeneralWksAddinHeader.CAAAfrSearchHdr.LongHelp  = "Search Demonstrator 
    This Command launches some queries on the current document. The result is put
    into the HSO." ;  

---  

This Command launches some queries on the current document. The result is put
into the HSO." ;
The CAAAfrGeneralWksAddinHeader.CATRsc:

    CAAAfrGeneralWksAddinHeader.CAAAfrSearchHdr.Icon.Normal    = "I_CAASearch" ;  

---  

> For the resources of the CAAAfrViewerFeedbackHdr command header, refer to the CAAAfrViewerFeedbackHdr use case [10].

[Top]

* * *
### In Short

This use case explains how by implementing the _CATIAfrGeneralWksAddin_ interface you can add your document independent command in all workbenches. 

[Top]

* * *
### References

[1] | [Creating an Add-in](CAAAfrSampleAddin.md)  
---|---  
[2] | [ApplicationFrame Overview](../CAAAfrTechArticles/CAAAfrOverview.md)  
[3] | [Creating Search Queries ](../CAACafUseCases/CAACafSampleSearch.md)  
[4] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
[5] | [The Command Headers](../CAAAfrTechArticles/CAAAfrCommandHeaders.md)  
[6] | [Checklist for CAA V5 C++ Naming Rules](../CAADocQuickRefs/CAADocCppNamingRulesChecklist.md)  
[7] | [Creating Resources for Workshop and Workbenches](../CAAAfrTechArticles/CAAAfrI18NWorkshop.md)  
[8] | [Creating Resources for Command Headers](../CAAAfrTechArticles/CAAAfrI18NHeader.md)  
[9] | [Viewer Feedback](../CAAVisUseCases/CAAVisViewerFeedback.md)  
[10] | [Creating Check Button](CAAAfrCheckHeader.md)  
[11] | [Creating a Most Recent Used command Header](CAAAfrSampleMRUHdr.md)  
[Top]  

* * *
### History

Version: **1** [May 2003] | Document created  
---|---  
[Top]  

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
