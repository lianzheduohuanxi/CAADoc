---
```vbscript
title: "Inserting Commands in Contextual Menus"
category: "use case"
module: "CAAAfrUseCases"
tags: ["CAASysEllipse", "CAAAfrEllipseHdr", "CAACafContextualMenu", "CAA2", "CAAEMmrCombinedCurveContSubMenu", "CAAECafContextualMenuEllipse", "CAACafContextualMenuCircleStr", "CAAAfrCircleHdr", "CAAAfrGeometryWks", "CAAGeometry", "CAACafContextualMenuEllipseStr", "CAACafContextualMenuSep", "CATIContextualMenu", "CATIA", "CATIAApplicationFrm", "CAACATIAApplicationFrm", "CATIAApplicationFrame"]
source_file: "Doc/online/CAAAfrUseCases/CAAAfrSampleContextualMenu.htm"
converted: "2026-05-11T17:17:55.668604"
```

---
# 3D PLM Enterprise Architecture

| 
## User Interface - Frame

| 
### Inserting Commands in Contextual Menus

_Implementing CATIContextualMenu_  
---|---|---  
Use Case  

* * *
### Abstract

This article shows how to insert commands in the contextual menu when the Select command is the active one. 

  * **What You Will Learn With This Use Case**
  * **The CAACafContextualMenu Use Case**
    * What Does CAACafContextualMenu Do
    * How to Launch CAACafContextualMenu
    * Where to Find the CAACafContextualMenu Code
  * **Step-by-Step**
  * **In Short**
  * **References**

* * *
### What You Will Learn With This Use Case

This use case is intended to show you how insert commands in the contextual menu of an object when the Select command is the current command. So in other words this article explains how to implement the _CATIContextualMenu_   interface.  [Top]
### The CAACafContextualMenu Use Case

CAACafContextualMenu is a use case of the CAACATIAApplicationFrm.edu framework that illustrates CATIAApplicationFrame framework capabilities. [Top]
#### What Does CAACafContextualMenu Do

CAACafContextualMenu enables you to display the following contextual menu when you right click on an Ellipse during  the Select command life: 
---  

CAACafContextualMenu enables you to display the following contextual menu when you right click on an Ellipse during  the Select command life:
This menu is separated in third parts: 

  1. The items added in the menu by the current window. `Center Graph, Reframe On` ... are items added by the _CATFrmGraphAnd3DWindow_ class. This part is independent of the _CATIContextualMenu_ implementation on the Ellipse. 
  2. The items defined in the contextual menu of the UIActive object [1] and added in the menu by the _CATIContextualMenu_ implementation on the Ellipse 
  3. The items defined and added by the _CATIContextualMenu_ implementation on the Ellipse in the menu

These two commands are `Ellipse` and `Circle`, two commands defined in the workshop of the "CAA Geometry" document. To reuse it, you should retrieve their command header identifiers [2].  The "Workshop Exposition" command enables you to find them.

Launch CATIA, when the application is ready:

  * On the **File** menu click **New**
  * In the **File New   **Dialog box select**CAA Geometry** and click **OK**
  * On the **Tools** menu click **Customize**
  * The**Customize** Dialog Box appears 
    * Click the **Command** page
    * Click the **XCAA2** category
    * Drag and Drop the **Workshop Exposition** command into a toolbar
    * Click **Close**  
  * Launch the **Workshop Exposition** command  ![](images/CAACafContextualMenuWshopExpo.jpg)  
---  
    * Select the **CAAAfrGeometryWks****** workshop 
    * Enter a Path in the **Directory** editor
    * Click **Print  \- **The **CAAAfrGeometryWks****.txt** file is generated
    * Click**OK**

In the **CAAAfrGeometryWks****.txt** find out the "`Ellipse` " and "`Circle`" strings: 

The identifiers of the command header instances are the **Id** strings, so **CAAAfrEllipseHdr** and **CAAAfrCircleHdr****** for the "`Ellipse` " and "`Circle`" commands respectively. These two identifiers will be associated with the starters of the menu. 

[Top]
#### How to Launch CAACafContextualMenu

See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched. For the specific scenario :

  * On the **File** menu click **New**
  * In the **File New   **Dialog box select **CAAGeometry** and click **OK**
  * Create three **Points**
  * Create a **Plane**
  * Create an **Ellipse**
  * Right click on the **Ellipse** and select the **Circle** command

[Top]
#### Where to Find the CAACafContextualMenu Code

The CAACafContextualMenu use case is made of one single class, the CAAECafContextualMenuEllipse class, located in the CAACafContextualMenu.m module of the CAACATIAApplicationFrm.edu framework:

The CAACafContextualMenu use case is made of one single class, the CAAECafContextualMenuEllipse class, located in the CAACafContextualMenu.m module of the CAACATIAApplicationFrm.edu framework:
Windows | `InstallRootDirectory\CAACATIAApplicationFrm.edu\CAACafContextualMenu.m\`  

The CAACafContextualMenu use case is made of one single class, the CAAECafContextualMenuEllipse class, located in the CAACafContextualMenu.m module of the CAACATIAApplicationFrm.edu framework:
Windows | `InstallRootDirectory\CAACATIAApplicationFrm.edu\CAACafContextualMenu.m\`
Unix | `InstallRootDirectory/CAACATIAApplicationFrm.edu/CAACafContextualMenu``.m/`  

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
To implement the _CATIContextualMenu_ interface, there are two steps: 

  1. Creating the Contextual Menu Description Class
  2. Creating the Contextual Menu 

[Top]
#### Creating the Contextual Menu Description Class

  1. Create the CAAECafContextualMenuEllipse.h file
    #include "CATExtIContextualMenu.h"

1. Create the CAAECafContextualMenuEllipse.h file
    class CAAECafContextualMenuEllipse : public **CATExtIContextualMenu**

    {
1. Create the CAAECafContextualMenuEllipse.h file
class CAAECafContextualMenuEllipse : public **CATExtIContextualMenu**
      CATDeclareClass;

      public:

        CAAECafContextualMenuEllipse();
        virtual ~CAAECafContextualMenuEllipse();

      private:
        CAAECafContextualMenuEllipse(const CAAECafContextualMenuEllipse &iObjectToCopy);
        CAAECafContextualMenuEllipse& operator = (const CAAECafContextualMenuEllipse

                                                               &iObjectToCopy);

    };  

---  

The implementation class derives from the _CATExtIContextualMenu_ adapter class.

  2. Create the CAAECafContextualMenuEllipse.cpp file
    #include "CAAECafContextualMenuEllipse.h"
    #include "CATCreateWorkshop.h"

    **CATImplementClass**(CAAECafContextualMenuEllipse, 
                            DataExtension,CATBaseUnknown,
                            **CAASysEllipse**);
    #include "TIE_CATIContextualMenu.h"
    TIE_**CATIContextualMenu**(CAAECafContextualMenuEllipse);
    ...  

---  

The CAAECafContextualMenuEllipse class states that it implements the _CATIContextualMenu_ interface thanks to the `TIE_CATIContextualMenu` macro. The `CATImplementClass` macro declares that the CAAECafContextualMenuEllipse class is a data extension, thanks to the `DataExtension` keyword, that extends _CAASysEllipse_. The third argument must always be set as _CATBaseUnknown_ or _CATNull_ for any kind of extension.

    ...
    CAAEMmrCombinedCurveContSubMenu::CAAEMmrCombinedCurveContSubMenu()

    {
        Creating the Contextual Menu
    }

    CAAEMmrCombinedCurveContSubMenu::~CAAEMmrCombinedCurveContSubMenu()
    {
    }

---  

The constructor contains the main code, and the destructor is empty.

The constructor contains the main code, and the destructor is empty.
  3. Updating the Interface Dictionary

Update the interface dictionary, that is a file named, for example, CAACATIAApplicationFrm.dico, whose directory's pathname is concatenated at run time in the CATDictionaryPath environment variable, and containing the following declaration to state that the CAASysEllipse component implements the _CATIContextualMenu_ interface, and whose code is located in the libCAACafContextualMenu shared library or DLL.

    CAASysEllipse CATIContextualMenu libCAACafContextualMenu  

---  

#### Creating the  Contextual Menu 

In this use case, the contextual menu associated with the UIActive object is first retrieved. It is possible thanks to the `GetContextualMenu` method of the adapter class. This menu, `pMenu`, is completed with the two commands (Circle and Ellipse). A separator is also added.

       ...
       **CATCmdContainer** * pMenu = NULL ; 

       CATExtIContextualMenu::**GetContextualMenu**(pMenu);

       if ( NULL != pMenu )
       {
          **NewAccess**(CATCmdStarter,pStEllipse,CAACafContextualMenuEllipseStr);
CATExtIContextualMenu::**GetContextualMenu**(pMenu);
if ( NULL != pMenu )
          NewAccess(CATCmdStarter,pStCircle,CAACafContextualMenuCircleStr);
          NewAccess(CATCmdSeparator,pSep1,CAACafContextualMenuSep);

          **SetAccessCommand**(pStEllipse,"**CAAAfrEllipseHdr** ");
```vbscript
NewAccess(CATCmdStarter,pStCircle,CAACafContextualMenuCircleStr);
NewAccess(CATCmdSeparator,pSep1,CAACafContextualMenuSep);
          SetAccessCommand(pStCircle,"**CAAAfrCircleHdr** ");

```

          **AddAccessChild**(pMenu,pStEllipse);

          **SetAccessNext**(pStEllipse,pStCircle);
          SetAccessNext(pStCircle,pSep1);

       }
       ...  

---  

The menu, `pMenu,` is completed thanks macros contained in the `CATCreateWorkshop` file:

  * NewAccess

The menu, `pMenu,` is completed thanks macros contained in the `CATCreateWorkshop` file:
A command starter is created as a _CATCmdStarter_ instance using the `NewAccess` macro. `pStEllipse` is the variable used to handle a pointer to the instance, and `CAACafContextualMenuEllipseStr` is its identifier.

A separator access is created as a _CATCmdSeparator_ instance using also the `NewAccess` macro. `pSep1` is the variable used to handle a pointer to the instance and `CAACafContextualMenuSep` is its identifier.

  * SetAccessCommand

A command header is associated with a command starter using the `SetAccessCommand` macro. The second parameter of the macro is the command header identifier defined as the first parameter of the command header constructor.  For example, `CAAAfrEllipseHdr.`

![](../CAAIcons/images/warning.gif)In a contextual menu or in a contextual sub menu implementation, it is not recommended to create command headers. So you should reuse command header identifiers created previously. To be sure that the command header will be created when the menu will be invoked you should use an identifier created in the workshop, or in Add-ins of the workshop. 

Refer to the technical article entitled "The Command Headers" [2] for complete details about the re-usage of the command header identifiers. 

  * AddAccessChild/SetAccessNext

Refer to the technical article entitled "The Command Headers" [2] for complete details about the re-usage of the command header identifiers.
The `AddAccessChild` macro enables you to link the `pStEllipse`` `access to the last access of `_pMenu`. The `SetAccessNext` macro enables you to chain the other accesses to the `pStEllipse` access.

The picture below shows `_pMenu` before and after :

![](images/CAACafContextualMenuChain.jpg)  
---  

**Note1** : The `GetContextualMenu` method returns a pointer on a _CATCmdContainer_ instance class. The _CATExtIContextualMenu_ class keeps this pointer, and at the _CATExtIContextualMenu_ class instance destruction, the container and the accesses created in this current implementation will be released.

**Note2** : In this use case, the contextual menu of the UIActive object has been retrieved and completed. But it is also possible to create your own contextual menu. You overwrite the `GetContextualMenu` method which returns your own _CATCmdContainer_ class instance. This instance will be created in the constructor (if constant menu) or in the `GetContextualMenu`  method (if variable menu). 

**Note3** : A _CATCmdContainer_ class instance destruction (by a Release call) implies automatically the destruction of its children.

[Top]

* * *
### In Short

This use case explains how to implement a contextual menu and how to retrieve command header identifiers. 

[Top]

* * *
### References

[1] | [Application Frame Overview](../CAAAfrTechArticles/CAAAfrOverview.md)  
---|---  
[2] | [The Command Headers](../CAAAfrTechArticles/CAAAfrCommandHeaders.md)  
[Top]  

* * *
### History

Version: **1** [Fev 2003] | Document created  
---|---  
[Top]  

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
