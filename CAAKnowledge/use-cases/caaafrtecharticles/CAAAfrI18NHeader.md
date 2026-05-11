---
```vbscript
title: "Creating Resources for Command Headers"
category: "use-case"
module: "CAAAfrTechArticles"
tags: ["CAAAfrPointHdr", "CAAGeometryWksHeader", "CAAAfrGeometryWksHeader", "CAAAfrCircleHdr", "CAAPoint", "CATImplementHeaderResources", "CAAAfrQueryExploreHdr", "CAACircle"]
source_file: "Doc/online/CAAAfrTechArticles/CAAAfrI18NHeader.htm"
converted: "2026-05-11T17:17:55.887253"
```

---
# 3D PLM Enterprise Architecture

| 
## User Interface - Frame

| 
### Creating Resources for Command Headers

_How to provide the title, help messages, and icons for command headers_  
---|---|---  
Technical Article  

* * *
### Abstract

This article shows how to create the resource files, and fill them in with the resources, for command headers. It is in connection with the article describing the workshop creation [1], since it uses as examples command headers created with this workshop. 

  * **Declaring the Command Header Resource Files**
  * **Filling in the Command Header CATNls File**
  * **Filling in the Command Header CATRsc File**
  * **Providing the Icons**
  * **In Short**
  * **References**

---  

* * *
### Declaring the Command Header Resource Files

If you use the macros `MacDefineHeader` and `MacImplementHeader`, or `MacDeclareHeader`, the resource files searched for at run time should have the same name than you command header class. This is the case of the CAAGeometryWksHeader [1].

If you create the command header class by yourself, you need to declare the resource file to use. Assume the command header class is named MyHeaderClass. You should insert the `CATDeclareHeaderResources` macro in MyHeaderClass.h:

    ...
```vbscript
If you create the command header class by yourself, you need to declare the resource file to use. Assume the command header class is named MyHeaderClass. You should insert the `CATDeclareHeaderResources` macro in MyHeaderClass.h:
    class MyHeaderClass : public CATCommandHeader
```

    {
class MyHeaderClass : public CATCommandHeader
      CATDeclareClass;
      CATDeclareHeaderResources;
      public :

      ...  

---  

In MyHeaderClass.cpp, you should insert the `CATImplementHeaderResources` macro:

    ...
In MyHeaderClass.cpp, you should insert the `CATImplementHeaderResources` macro:
    CATImplementHeaderResources(CommandHeaderClass,
                                BaseCommandHeaderClass,
                                ResourceFile);

    ...  

---  

where: 

  * `CommandHeaderClass` is the command header class name
  * `BaseCommandHeaderClass` is the command header class from which `CommandHeaderClass` derives
  * `ResourceFile` is the name used to build the names of the resource files associated with `CommandHeaderClass`. Using the `CommandHeaderClass` name for this file in this macro is recommended.

There are two command header resource files: 

There are two command header resource files:
  1. The resource file containing the title and help messages in the English language, and that can be translated into other languages. It is suffixed using CATNls
  2. The resource file containing the icons and other resources that should not be translated. It suffixed by CATRsc

The two resource files for the CAAGeometryWksHeader command header are then: CAAGeometryWksHeader .CATNls and CAAGeometryWksHeader .CATRsc. These files are located in the CNext\resources\msgcatalog directory of the framework containing the module where the command header source files are located. This directory includes subdirectories, one for each language into which the title and messages of the CAAGeometryWksHeader .CATNls file can be translated.

[Top]
### Filling in the Command Header CATNls File

The two resource files for the CAAGeometryWksHeader command header are then: CAAGeometryWksHeader .CATNls and CAAGeometryWksHeader .CATRsc. These files are located in the CNext\resources\msgcatalog directory of the framework containing the module where the command header source files are located. This directory includes subdirectories, one for each language into which the title and messages of the CAAGeometryWksHeader .CATNls file can be translated.
This file contains the resources for each of the command header instances: title and help messages, and category.

Each resource is provided using a key and a text separated by the equal sign. The key is built as a concatenation of the command header resource file name, a dot, the command header identifier you defined as the first parameter of the `New` operator, a dot, and a keyword designating the appropriate resource. The message is enclosed using double quotes and ended using a semicolon. For example, the Query command of the Explore menu defined for the Geometry workshop in [2] has its title defined as follows:

    CAAAfrGeometryWksHeader.CAAAfrQueryExploreHdr.Title     = "Query" ;  

---  

where:

  * CAAGeometryWksHeader is the command header resource file name
  * CAAAfrQueryExploreHdr is the identifier of the CAAGeometryWksHeader class instance created for the Query command
  * `Title` is the keyword dedicated to the title of the command

The following is an extract of CAAGeometryWksHeader.CATNls, showing the resources for the Point and Circle commands:

    //# CATNls resource file for the command header: CAAGeometryWksHeader
    //# used in the Geometry Workshop
    //# --------------------------------------------------------------

    ...

    CAAAfrGeometryWksHeader.CAAAfrPointHdr.Title     = "Point" ;
    CAAAfrGeometryWksHeader.CAAAfrPointHdr.ShortHelp = "Point" ;
    CAAAfrGeometryWksHeader.CAAAfrPointHdr.Help      = "Creates points: indicate a point or enter coordinates";
    CAAAfrGeometryWksHeader.CAAAfrPointHdr.LongHelp  = "Point (Insert menu)
    Create points in two ways: 
     1- Indicate a point with the mouse left button 
     2- Enter the point coordinates in the dialog box
    This Command is in repeat mode, so you can create
    several points along the command life.
    To leave the command, select another command." ;
    CAAAfrGeometryWksHeader.CAAAfrPointHdr.Category  = "Element" ;

    ...

To leave the command, select another command." ;
CAAAfrGeometryWksHeader.CAAAfrPointHdr.Category  = "Element" ;
    CAAAfrGeometryWksHeader.CAAAfrCircleHdr.Title     = "Circle" ;
    CAAAfrGeometryWksHeader.CAAAfrCircleHdr.ShortHelp = "Circle" ;
    CAAAfrGeometryWksHeader.CAAAfrCircleHdr.Help      = "Creates circles" ;
    CAAAfrGeometryWksHeader.CAAAfrCircleHdr.LongHelp  = "Circle (Insert menu)
    Create circles:
     1- Select a projection plane: 
     2- Indicate a point for the circle center 
     3- Move the mouse and indicate a point to define the radius.";
    CAAAfrGeometryWksHeader.CAAAfrCircleHdr.Category  = "Element" ;

    ...  

---  

Below is a reminder of the keywords used in the resource keys that can be found in the CATNls resource file:

Below is a reminder of the keywords used in the resource keys that can be found in the CATNls resource file:
Title | Text displayed in the menu or submenu, and in the toolbar if no icon is provided  

Below is a reminder of the keywords used in the resource keys that can be found in the CATNls resource file:
Title | Text displayed in the menu or submenu, and in the toolbar if no icon is provided
Help | Text displayed in the status bar as the command help message when the mouse is over the command in the toolbar or in the menu or submenu  
ShortHelp | Text displayed in a balloon as the command short help message when the mouse is over the command. This is not applicable to commands only located in menus or submenus  
LongHelp | Text displayed in a balloon when the end user clicks ![](../CAAIcons/images/I_WhatsThisP2.gif), which turns the mouse cursor as a question mark, and then clicks on the icon representing the command. This is not applicable to commands located only in menu or submenus  
Mnemonic | An "Alt+key" keystroke combination that activates menus, submenus, and menu items. The key character is underlined in the menu, submenu, or menu item title, and therefore must belong to this title. No duplicates should exist in the set of mnemonic keys for a given menu or submenu. The case is ignored when using the mnemonic. The mnemonic is declared in the workshop resource file for menus and submenus only. It is declared in the command header resource file for menu items.  
Category | An attribute associated with the command and used to sort the commands in the Command tab page of the Customize window.  

[Top]
### Filling in the Command Header CATRsc File

Category | An attribute associated with the command and used to sort the commands in the Command tab page of the Customize window.
This file contains the icon names to be associated with the command header and displayed in the toolbars and in the menus. It can also include the LongHelpId, an pointer to the the URL where the file documenting the command is located. 

Each icon resource is provided using a key and a file name without suffix separated by the equal sign. The key is built as a concatenation of the command header resource file name, a dot, the command header identifier you defined as the first parameter of the `New` operator, a dot, and a keyword designating the appropriate resource. The message is enclosed using double quotes and ended using a semicolon. For example, the Point command header icon name to display in the Basic Elements toolbar is defined as follows

    CAAAfrGeometryWksHeader.CAAAfrPointHdr.Icon.Normal     = "I_CAAPoint" ;  

---  

```vbscript
For the URL, 

```

    CCAAAfrGeometryWksHeader.CAAAfrPointHdr.LongHelpId      = "CAAAfrGeometryWksHeader.CAAAfrPointHdr" ;  

---  

CCAAAfrGeometryWksHeader.CAAAfrPointHdr.LongHelpId      = "CAAAfrGeometryWksHeader.CAAAfrPointHdr" ;
It is recommended to build the URL  as a concatenation of the command header resource file name, a dot, the command header identifier you defined as the first parameter of the `New` operator.

The following is an extract of CAAGeometryWksHeader.CATRsc, showing the resources for the Point and Circle commands:

    //# CATRsc resource file for the command header: CAAGeometryWksHeader
    //# used in the Geometry Workshop
    //# --------------------------------------------------------------

    ...
    CCAAAfrGeometryWksHeader.CAAAfrPointHdr.Icon.Normal     = "I_CAAPoint" ;
    CAAAfrGeometryWksHeader.CAAAfrPointHdr.LongHelpId      = "CAAAfrGeometryWksHeader.CAAAfrPointHdr" ;

    ...
CCAAAfrGeometryWksHeader.CAAAfrPointHdr.Icon.Normal     = "I_CAAPoint" ;
CAAAfrGeometryWksHeader.CAAAfrPointHdr.LongHelpId      = "CAAAfrGeometryWksHeader.CAAAfrPointHdr" ;
    CAAAfrGeometryWksHeader.CAAAfrCircleHdr.Icon.Normal    = "I_CAACircle" ;  

---  

CAAAfrGeometryWksHeader.CAAAfrCircleHdr.Icon.Normal    = "I_CAACircle" ;
Below is a reminder of the keywords used in the resource keys that can be found in the CATRsc resource file:

Icon.Normal | Icon associated with the command and used in toolbars when the command is available. The greyed icon associated with the command when it is unavailable is computed from this one. The displayed icon is a shadowed icon computed from the Normal one too.  

Below is a reminder of the keywords used in the resource keys that can be found in the CATRsc resource file:
Icon.Normal | Icon associated with the command and used in toolbars when the command is available. The greyed icon associated with the command when it is unavailable is computed from this one. The displayed icon is a shadowed icon computed from the Normal one too.
Icon.Pressed | Icon associated with the command when it is pressed. This keyword is kept for compatibility. If not explicitly specified through this keyword, the Pressed icon is computed from the Normal one  
Icon.Focused | Icon associated with the command when the mouse moves or is located above. This keyword is kept for compatibility. If not explicitly specified through this keyword, the Focused icon is computed from the Normal one  
Accelerator | A keystroke combination, such as "Ctrl+key", used to activate the command directly. The keystroke combination is written beside the command title in the menu or submenu  
LongHelpId | Identifier to associate a URL to the command. The URL is stored in a  mapping file.   

[Top]
### Providing the Icon Files

The icons are bit map files, suffixed by bmp. They must be provided in "normal" and "small" sizes. "Normal" size and "small" size icon files are respectively contained in the CNext\resources\graphic\icons\normal and CNext\resources\graphic\icons\small directories of the framework containing the module where the command headers are created. "Normal" icons, that is corresponding to default button state, must respectively have a size of 22 by 22 pixels and 16 by 16 pixels for "normal" and "small" sizes. When specified, the Pressed and Focused icons must respectively have a size of 24 by 24 pixels and 18 by 18 pixels for "normal" and "small" sizes.

[Top]

* * *
### In Short

The command header resources are provided in two files whose names are the command header class, or the name set by the `CATImplementHeaderResources` macro in the command header cpp file. One file is for those that can be translated and is suffixed CATNls, the other for the icon names or pointer to a help file and is suffixed CATRsc. The resources are provided using keys built with the identifier of the object to which they apply.

[Top]

* * *
### References

[1] | [Application Frame Overview](CAAAfrOverview.md)  
---|---  
[2] | [Creating a Workbench](../CAAAfrUseCases/CAAAfrSampleWorkbench.md)  
[Top]  

* * *
### History

Version: **1** [Jan 2001] | Document created  
---|---  
[Top]  

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
