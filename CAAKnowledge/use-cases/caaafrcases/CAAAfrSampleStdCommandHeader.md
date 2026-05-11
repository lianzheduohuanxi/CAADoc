---
title: "Creating Standard Command Headers"
category: "use case"
module: "CAAAfrUseCases"
tags: ["CAADegGeoCommands", "CAAAfrChangeViewNormalCmd", "CAAAfrGeometryWksHeader", "CAAAfrGeometryWks", "CAAAfrGeometryWshop", "CAADegCreatePointCmd", "CAAGeometry", "CAAAfrGeoCommands", "CAADegCreateCircleCmd", "CATINT32ToPtr", "CAADegCreateLineCmd", "CAAApplicationFrame"]
source_file: "Doc/online/CAAAfrUseCases/CAAAfrSampleStdCommandHeader.md"
converted: "2026-05-11T17:17:55.814448"
---
# 3D PLM Enterprise Architecture

| 
## User Interface - Frame

| 
### Creating Standard Command Headers

_Exposing your commands_  
---|---|---  
Use Case  
  
* * *
### Abstract

This article shows how to create a standard command header class, and how to use it to expose several commands. 

  * **What You Will Learn With This Use Case**
  * **The CAAAfrGeometryWshop Use Case**
    * What Does CAAAfrGeometryWshop Do
    * How to Launch CAAAfrGeometryWshop
    * Where to Find the CAAAfrGeometryWshop Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *
### What You Will Learn With This Use Case

This use case is intended to show how to create a standard command header class, and how to use it to expose several commands.

[Top]
### The CAAAfrGeometryWshop Use Case

CAAAfrGeometryWshop is a use case of the CAAApplicationFrame.edu framework that illustrates the ApplicationFrame framework capabilities.

[Top]
#### What Does CAAAfrGeometryWshop Do

The CAAAfrGeometryWshop use case creates a workshop named **CAA V5: Geometry Creation** for the CAAGeometry document [1]. It is used here only to show and detail how to expose the workshop commands thanks to command headers.

[Top]
#### How to Launch CAAAfrGeometryWshop

See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched. For the specific scenario :

```vbscript
Do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following: 

```

  * Select File->New
  * In the New box, select CAAGeometry and click OK

The CAAAfrGeometryWshop is loaded with the CAAGeometry document. 

[Top]
#### Where to Find the CAAAfrGeometryWshop Code

The CAAAfrGeometryWshop use case is made of classes and interfaces located in the CAAAfrGeometryWshop.m module and in the ProtectedInterfaces directory of the CAAApplicationFrame.edu framework:

Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CAAAfrGeometryWshop.m\`  
---|---  
Unix | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeometryWshop.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

The only class referred to in this article is the workshop description class named _CAAAfrGeometryWks_

[Top]
### Step-by-Step

To create the command headers for the command of the Geometry workshop, there are three steps:
# | Step | Where  
---|---|---  
1 | Create the command header class | Workshop class  
2 | Instantiate the command header class | `CreateCommands` method  
3 | Assign Resources to the command header instance | Resource files  
  
[Top]
#### Creating the Command Header Class

To create a command header class, you should use the `MacDeclareHeader` macro. It creates for you a class that derives from _CATCommandHeader_ , that is the base class for command headers and that should never be directly instantiated.

The command header class for the CAAAfrGeometryWks workshop is named _CAAAfrGeometryWksHeader_. The two lines of code below create this class.
    
    #include "CATCommandHeader.h"
    **MacDeclareHeader**(CAAAfrGeometryWksHeader);  
  
---  
  
This macro creates a class that is ready to use.

[Top]
#### Instantiating the Command Header Class

To instantiate this command header for the Point command, for example, the following constructor created by the macro should be used.
    
    
    new CAAAfrGeometryWksHeader("Point",
                                "CAADegGeoCommands",
                                "CAADegCreatePointCmd",
                                (void *) NULL);  
  
---  
  
where: 

  * `Point` is the identifier assigned to the command header. It will be used afterwards to associate the command starters defined to put the command in a menu and in toolbars with the command header. This is described in Exposing Your Commands in Menus and Toolbars. This identifier is also used to build the variables that define the command header resources, such as the name seen by the end user in his/her own language in the menu, or the icon to display in a toolbar. This is explained in Creating Resources for Command Headers
  * `CAADegGeoCommands` is the name of the shared library or DLL containing the command's code, without the prefix lib, and without the suffix depending on the operating system
  * `CAADegCreatePointCmd` is the name of the command class
  * the last argument is the possible pointer to the object to pass to the command constructor when starting the command. It is often a character string that indicates the action to carry out when the same command can perform several actions depending on the active document and data, such as "update" or "update all", or "cut" or "copy".

Different commands can share the same command header class to create their command headers. For example, to creating a workshop [1], we have created the following instances of the _CAAAfrGeometryWksHeader_ class in the `CreateCommands` method of the CAAAfrGeometryWshop workshop description class:
    
    
    void CAAAfrGeometryWks::CreateCommands()
    {
      ...
      //     1-a Cases without argument 
      new CAAAfrGeometryWksHeader("Point",  "CAADegGeoCommands",
                                  "CAADegCreatePointCmd",    (void *) NULL);
      new CAAAfrGeometryWksHeader("Line",   "CAADegGeoCommands",
                                  "CAADegCreateLineCmd",     (void *) NULL);
      new CAAAfrGeometryWksHeader("Circle", "CAADegGeoCommands",
                                  "CAADegCreateCircleCmd",   (void *) NULL);
      ...
      //     1-b Cases with argument 
      new CAAAfrGeometryWksHeader("xNormal", "CAAAfrGeoCommands",
                                  "CAAAfrChangeViewNormalCmd",(void *)**CATINT32ToPtr**(1));
      new CAAAfrGeometryWksHeader("yNormal", "CAAAfrGeoCommands",
                                  "CAAAfrChangeViewNormalCmd",(void *)CATINT32ToPtr(2));
      new CAAAfrGeometryWksHeader("zNormal", "CAAAfrGeoCommands",
                                  "CAAAfrChangeViewNormalCmd",(void *)CATINT32ToPtr(3));
      ...
    }  
  
---  
  
See the referenced article [2] to see the definition of the _CAAAfrChangeViewNormalCmd_ class. The `CATINT32ToPtr` macro enables you to be 64 bits compliant.

[Top]
#### Assigning Resources to the Command Header Instance

The _CAAAfrGeometryWksHeader_ class is automatically associated with two resources files whose names are built using the class name: 

  * CAAAfrGeometryWksHeader.CATNls for titles and help message that can be translated
  * CAAAfrGeometryWksHeader.CATRsc for other resources, such as the icons to display in the toolbars

The resources are designated using a key built as a concatenation of the command header class name, the command header instance identifier, and the resource keyword, separated by dots. The CAAAfrGeometryWksHeader.CATNls file includes the following for the Point command:
    
    
    ...
    CAAAfrGeometryWksHeader.Point.**Title**     = "Point";
    CAAAfrGeometryWksHeader.Point.**ShortHelp** = "Point";
    CAAAfrGeometryWksHeader.Point.**Help**      = "Creates points: indicate a point or enter coordinates";
    CAAAfrGeometryWksHeader.Point.**LongHelp**  = "Point (Insert menu)
    Create points in two ways:
     1- Indicate a point with the mouse left button 
     2- Enter the point coordinates in the dialog box
    This Command is in repeat mode, so you can create
    several points along the command life.
    To leave the command, select another command.";
    CAAAfrGeometryWksHeader.Point.**Category**  = "Element";
    ...  
  
---  
  
These resources are:

Title | Text displayed in the menu bar for the command  
---|---|---  
ShortHelp | Text displayed in a balloon as the command short help message when the mouse moves over the command. This is not applicable to commands located in the menu bar  
Help | Text displayed in the status bar as the command help message when the mouse moves over the command. This is not applicable to commands located only in the menu bar, but is applicable for commands located in both the menu bar and a toolbar  
LongHelp | Text displayed in a balloon when the end user clicks ![I_WhatsThisP2.gif \(235 bytes\)](images/I_WhatsThisP2.gif), which turns the mouse cursor as a question mark, and then clicks on the icon representing the command. This is not applicable to commands located in the menu bar  
Category | An attribute associated with the command and used to sort the commands in the Command tab page of the Customize window  
  
The CAAAfrGeometryWksHeader.CATRsc file includes the following for the Point command:
    
    
    ...
    CAAAfrGeometryWksHeader.Point.**Icon.Normal**  = "I_EduPoint" ;
    ...  
  
---  
  
This is the file name of the icon used to show the Point command in the toolbar:

Icon.Normal | Icon associated with the command and used in toolbars when the command is available. The greyed icon associated with the command when it is unavailable is computed from this one. In a P2 session, the shadowed icon displayed for default state and the Pressed and Focused icons are computed from the Normal one too.  
---|---|---  
  
* * *
### In Short

A command header is a light object that stands for a command and avoids to load the command as long as the end user does not require it. A command header is an instance of a command header class. A standard command header class is created using the `MacDeclareHeader` macro, and can be used for several commands. Resources that help to expose and access the command are assigned to the command header in order to be available even if the command is not loaded.

[Top]

* * *
### References

[1] | [Creating a Workbench](CAAAfrSampleWorkbench.md)  
---|---  
[2] | [Using Cameras](CAAAfrSampleCamera.md)  
[Top]  
  
* * *
### History

Version: **1** [Jan 2000] | Document created  
---|---  
Version: **2** [Mar 2004] | 64 bits  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
