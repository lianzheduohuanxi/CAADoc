---
```vbscript
title: "Creating Resources for Workshops or Workbenches"
category: "use-case"
module: "CAAAfrTechArticles"
tags: ["CAAAfrSubmenuId", "CAAAfrWorkbenchId", "CAAAfrIconBoxId", "CAAAfrWorkBenchPointer", "CAAAfrMenuId", "CAAAfrWorkbenchPointer", "CAAAfrToolbarId"]
source_file: "Doc/online/CAAAfrTechArticles/CAAAfrI18NWorkshop.htm"
converted: "2026-05-11T17:17:55.896732"
```

---
# 3D PLM Enterprise Architecture

|
## User Interface - Frame

|
### Creating Resources for Workshops or Workbenches

_How to provide the title, help messages, and icons for workshops or workbenches_
---|---|---
Technical Article

* * *
### Abstract

This article shows how to create the resource files, and fill them in with the appropriate resources, for a workshop or a workbench.

  * **Creating the Resource Files**
  * **Filling in the CATNls Resource File**
  * **Filling in the CATRsc Resource File**
  * **Providing the Icon Files**
  * **In Short**
  * **References**

---

* * *
### Creating the Resource Files

The resource files must have the workshop or workbench identifier as name. This identifier is declared in the `CreateWorkshop` or `CreateWorkbench` method of the workshop or workbench description class, as the third parameter of the `NewAccess` macro that creates the workshop or workbench. For example, for a workbench:

    NewAccess(CATCmdWorkbench,pCAAAfrWorkBenchPointer,**CAAAfrWorkbenchId**);

---

where:

  * `CATCmdWorkbench` is the workbench container class
  * `pCAAAfrWorkbenchPointer` is a pointer to the `CATCmdWorkbench` class instance that the macro creates
  * `**CAAAfrWorkbenchId**` is the workbench identifier.

There are two workbench resource files:

There are two workbench resource files:
  1. The resource file containing the title and help messages in the English language, and that can be translated into other languages. It is suffixed using CATNls
  2. The resource file containing the icons and other resources that should not be translated. It suffixed by CATRsc. This file is required to make the workshop or the workbench appear in the Start menu. If a workshop has workbenches, these workbenches are displayed in place of the workshop in the **Start** menu, and this workshop resource file is unused and can be omitted.

The two resource files for the CAAAfrWorkbenchId workshop or workbench are then: CAAAfrWorkbenchId.CATNls and CAAAfrWorkbenchId.CATRsc. These files are located in the CNext\resources\msgcatalog directory of the framework containing the workshop or workbench module. This directory includes subdirectories, one for each language into which the title and messages of the CAAAfrWorkbenchId.CATNls file can be translated.

Each resource is provided using a key and a text, or a file name without suffix, separated by the equal sign. The key is built as a concatenation of the object identifier you defined as the third parameter of the `NewAccess` macro, a dot, and a keyword designating the appropriate resource. The message is enclosed using double quotes and ended using a semicolon. For example, the workshop or workbench title is defined as follows:

```vbscript
    CAAAfrWorkbenchId.Title = "CAA V5: Geometrical Creation";

```

---

[Top]
### Filling in the CATNls Resource File

This file contains:

  * The resources for the workshop or workbench itself: the title used in the **Start menu** , its associated help message, the short help and the help messages repectively displayed in a balloon and in the status bar when the mouse is over the workshop or workbench icon, and the long help message displayed in a ballon when the end user clicks ![](../CAAIcons/images/I_WhatsThisP2.gif)and then clicks the workshop or workbench icon.

This file contains:
        CAAAfrWorkbenchId.**Title**     = "CAA V5: Geometrical Creation";
        CAAAfrWorkbenchId.**ShortHelp** = "Workbench to create Geometrical Elements";
        CAAAfrWorkbenchId.**Help**      = "Workbench to create Geometrical, Solid and Surfacic Elements";
        CAAAfrWorkbenchId.**LongHelp**  = "This is the CAA V5: Geometrical Creation Workbench.
        It is used to demonstrate workbenches.
        It contains two toolsbars:

        - One for some Solid Elements
        - The other for some Surfacic Elements";
        ...

---
  * The titles of the toolbars and icon boxes

        ...
        // For a toolbar
        CAAAfrToolbarId.**Title**      = "Select";
        // For an icon box
        CAAAfrIconBoxId.**Title**      = "Icon Box";
        ...

---
  * The titles and mnemonics of the menus and submenus

        // For a menu
        CAAAfrMenuId.**Title**         = "Explore";
        CAAAfrMenuId.**Help**          = "Explores the document";
        CAAAfrMenuId.**Mnemonic**      = "x";

        // For a submenu
CAAAfrMenuId.**Title**         = "Explore";
CAAAfrMenuId.**Help**          = "Explores the document";
CAAAfrMenuId.**Mnemonic**      = "x";
        CAAAfrSubmenuId.**Title**      = "Normal View";
        CAAAfrSubmenuId.**Help**       = "Defines the normal to indicate points";
        CAAAfrSubmenuId.**Mnemonic**   = "N";

---

CAAAfrSubmenuId.**Help**       = "Defines the normal to indicate points";
CAAAfrSubmenuId.**Mnemonic**   = "N";
Below is a reminder of the keywords used in the resource keys that can be found in the CATNls resource file.

Title | Text displayed:

  * as the name of the workshop or workbench in the **Start** menu
  * as the toolbar title
  * as the icon box title when the icon box is teared off
  * as the menu or submenu title

Help | Text displayed in the status bar when the mouse moves over the workshop or workbench name or icon in the Start menu, or over the icon in the workshop or workbench toolbar
ShortHelp | Text displayed in a balloon as the workshop or workbench short help message when the mouse moves over the icon in the workshop or workbench toolbar
LongHelp | Text displayed in a balloon when the end user clicks ![](../CAAIcons/images/I_WhatsThisP2.gif), which turns the mouse cursor as a question mark, and then clicks on the icon representing the workshop or workbench in the Welcome dialog box workshop or workbench toolbar
Mnemonic | An "Alt+key" keystroke combination that activates menus, submenus, and menu items. The key character is underlined in the menu, submenu, or menu item title, and therefore must belong to this title. No duplicates should exist in the set of mnemonic keys for a given menu or submenu. The case is ignored when using the mnemonic. The mnemonic is declared in the workshop or workbench resource file for menus and submenus only. It is declared in the command header resource file for menu items.

[Top]
### Filling in the CATRsc Resource File

This file contains:

  * The submenu into which workshop or workbench should appear in the **Start** menu

        CAAAfrWorkbenchId.**Category**    = "Infrastructure" ;
        ...

---
  * An attribute to specify if the workbench should be displayed in the **Start** menu. Set to "True" to hide it, "False" to display it. The default value of this attribute is "False".

        CAAAfrWorkbenchId.**Transient**    = "False" ;
        ...

---
  * The icon names to be associated with the workshop or workbench in the **Start** menu

        ...
        CAAAfrWorkbenchId.**Icon.NormalCtx**   = "I_CtxGeometry";
        CAAAfrWorkbenchId.**Icon.PressedlCtx** = "IP_CtxGeometry";
        CAAAfrWorkbenchId.**Icon.FocusedlCtx** = "IF_CtxGeometry";

        ...

---
  * The icon names to be associated with the workshop or workbench in the Welcome window where the favorite workshops or worbenches are gathered

        ...
        CAAAfrWorkbenchId.**Icon.NormalPnl**   = "I_Geometry";
        CAAAfrWorkbenchId.**Icon.PressedPnl** = "IP_Geometry";
        CAAAfrWorkbenchId.**Icon.FocusedPnl**  = "IF_Geometry";

        ...

---
  * The icon names to be associated with the workshop in the workshop toolbar

        ...
        CAAAfrWorkbenchId.**Icon.NormalRep**   = "I_RepGeometry";
        CAAAfrWorkbenchId.**Icon.PressedlRep** = "IP_RepGeometry";
        CAAAfrWorkbenchId.**Icon.FocusedlRep** = "IF_RepGeometry";

---
  * If you have several workbenches, you may want to classify them in a subcategory in the submenu of the **Start** menu . For that you have to specify this subcategory. You may also want to change the position of your workbench in the menu. The "Position" resource sets the position of the workbench in its subcategory if it has one, else in its category.

CAAAfrWorkbenchId.**Icon.FocusedlRep** = "IF_RepGeometry";
        CAAAfrWorkbenchId.**Subcategory**    = "MyInfrastructure" ;
        CAAAfrWorkbenchId.**Position**      = "2";

        ...

---

In this case, you have to create 2 resources files for the subcategory to specify the category it belongs to and its position under this category:

    * MyInfrastructure.CATNls

          MyInfrastructure.**Title**    = "MyInfrastructure" ;
          ...

---
    * MyInfrastructure.CATRsc

          MyInfrastructure.**Category**    = "Infrastructure" ;
          MyInfrastructure.**Position**   = "3";

          ...

---

**Remark:** The position resource is a string and the ordering is done alphabetically. The subcategory can be at first position in its category though its position resource is "3" if its position is the first one in the alphabetical order.

This is valid if the workshop doesn't not include any workbench. Otherwise, those of the workbenches are used and the workshop does not appear in the **Start** menu, in the Welcome window, and has no toolbar.

This is valid if the workshop doesn't not include any workbench. Otherwise, those of the workbenches are used and the workshop does not appear in the **Start** menu, in the Welcome window, and has no toolbar.
The files containing the icon bit maps are named, for example, I_CtxGeometry.bmp for the icon to be displayed in the Start menu, usually located in the CNext\resources\graphic\icons\normal.

Below is a reminder of the keywords used in the resource keys that can be found in the CATRsc resource file.

Category | An attribute associated with the the workshop or workbench to make it appear in the proper submenu of the Start menu. This is done by assigning a category to the workshop or workbench. Available categories are:

  * Infrastructure
  * MechanicalDesign
  * Shape
  * AnalysisSimulation
  * AECPlant
  * ProcessPlanning
  * NCManufacturing
  * DMUNavigator
  * Equipments
  * DPManufacturing
  * VNC
  * Inspection
  * DenebInfrastructure
  * IGRIP
  * Safework

Subcategory | An attribute associated with the workbench to classify them more precisely under the previous category
Position | An attribute to specify the position of a workbench in its subcategory if it has one, or else in its category
Transient | An attribute to specify if the workbench should be displayed in the **Start** menu
Icon.NormalCtx | Icon to display in the **Start** menu
Icon.PressedCtx | Icon replacing the "NormalCtx" icon when the end user clicks on it
Icon.FocusedCtx | Icon replacing the "NormalCtx" icon when the end user moves the mouse over it
Icon.NormalPnl | Icon to display in the Welcome window
Icon.PressedPnl | Icon replacing the "NormalPnl" icon when the end user clicks on it
Icon.FocusedPnl | Icon replacing the "NormalPnl" icon when the end user moves the mouse over it
Icon.NormalRep | Icon to display in the workshop toolbar
Icon.PressedRep | Icon replacing the "NormalRep" icon when the end user clicks on it
Icon.FocusedRep | Icon replacing the "NormalRep" icon when the end user moves the mouse over it

[Top]
### Providing the Icon Files

The icons are bit map files, suffixed by bmp. They should have a size of 24 by 24 pixels. The icon files are contained in the CNext\resources\graphic\icons\normal directory of the framework containing the workshop module.

* * *
### In Short

The workshop resources are provided in two files whose names are the workshop identifier. One file is for those that can be translated and is suffixed CATNls, the other for the icon names and is suffixed CATRsc. The resources are provided using keys built with the identifier of the object to which they apply.

* * *
### References

[1] | [Creating a Workbench](../CAAAfrUseCases/CAAAfrSampleWorkbench.md)
---|---
[2] | [Assigning Resources to a Dialog Box](../CAADlgTechArticles/CAADlgResources.md)
[Top]

* * *
### History

Version: **1** [Jan 2000] | Document created
---|---
Version: **2** [Jun 2007] | CATRsc Transient attribute addition
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
