---
title: "What Is the Product Line Visual Identity"
category: "general"
module: "CAAAfrTechArticles"
tags: ["CATIA"]
source_file: "Doc\online\CAAAfrTechArticles\CAAAfrVisualIdentity.htm"
converted: "2026-05-11T17:17:55.938631"
---

# 3D PLM Enterprise Architecture

| 

## User Interface - Frame

| 

### What Is the Product Line Visual Identity

_The objects related to a product line that you can customize_  
---|---|---  
Technical Article  
  
* * *

### Abstract

A product line should be easily recognized from others using some visual features discerningly chosen, such as its launching icon or splash screen. This article describes the objects you can customize. A product visual identity use case [1] shows you how to do. 

  * **What Are the Visual Identity Components?**
  * **In Short**
  * **References**

  
---  
  
* * *

### What Are the Visual Identity Components?

The components that help to differentiate your product line from any other are the following: 

  * **The product line name** , such as CATIA. It appears in the Help menu and in the Help About dialog box, in the sentence "CATIA is a registered trademark ..." and must be used as the product line resource file names: CATIA.CATNls and CATIA.CATRsc. If the name includes several words, only the first one is used for the resource file names
  * **The product line version level**. It appears in:  ![](images/CAAAfrVICATIAWinTitle.jpg) | The application frame window title, either displayed or iconified, such as CATIA V5  
---|---  
![](images/CAAAfrVICATIAWelcome.gif) | The title of the welcome dialog box displayed when the application is just launched: "Welcome to CATIA V5"  
![](images/CAAAfrVICATIAHelpMenu.gif) | The Help menu  
![](images/CAAAfrVICATIAHelpAboutTitle.jpg) | The Help About dialog box title  
  * **The product line icon** ![](images/CAAAfrVICATIAIcon.gif) to be displayed: 
    * In the top left corner of the application frame window (Windows only)
    * In the top left corner of the document windows .

Its dimensions are 16 pixel width and 17 pixel height.
  * **The product line logo** ![](images/CAAAfrVICATIALogo.gif) displayed in the application window bottom left corner. The bitmap image (bmp) width must be 49 pixels, and its height must be 29 pixels. For Windows, it must be a real color 24 bits image, and for UNIX a 256 indexed color image.



There are shown at their right places on the figure below.

![](images/CAAAfrVICATIAScreenV5R9.gif)

  * **The splash screen** is an image or an animation that displays when the end user launches the application. A static image is used for the P1 level, and an animation for the P2 level. The two files must have the same name, such as Splash.bmp and Splash.avi respectively for CATIA.  
The image width must be 320 pixels and the height must be 240 pixels. 

![](images/CAAAfrVICATIASplash.gif)



  * **The shortcut icon** ![](images/CAAAfrVICATIAShortcutTransparent.gif) used for shortcuts dropped onto the desktop. This is available with Windows only. This icon is created in an .ico file and is included into the application EXE 

![](images/CAAAfrVICATIAResources.jpg)



  * **The background image** displayed with the P2 level. 

![](images/CAAAfrVICATIABackground.gif)

  * **The dialog box background image** to be displayed with dialog boxes. It is a bmp image whose width is 55 pixels and height is 1000 pixels. Here is the one for CATIA, cropped in height: ![](images/CAAAfrVICATIADlgBackground.jpg) and the New command dialog box as an example. 

![](images/CAAAfrVICATIABoxBkgd.gif)

  * **The legal information** to be displayed in the Help About dialog box  
![](images/CAAAfrVICATIAHelpAbout.gif)
  * **The mapping file** between the commands and their on line help html files. This mapping file makes the link between the current command and its online documentation when the end user presses F1, or clicks the first item of the Help menu.  Refer you to the "Contextual Help" technical article for details about this topic [2]



[Top]

* * *

### In Short

To provide a visual identity to your product line, you can, with Windows only, create an EXE to launch your application associated with an icon of your own that can also be used as a shortcut in the desktop. You can create with UNIX and Windows text and graphic resources to display with your applications.

[Top]

* * *

### References

[1] | [Creating a Product Line Visual Identity](../CAAAfrUseCases/CAAAfrSampleVisualIdentity.htm)  
---|---  
[2] | [Contextual Help](CAAAfrHelpOnLine.htm)  
[Top]  
  
* * *

### History

Version: **1** [Jul 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
