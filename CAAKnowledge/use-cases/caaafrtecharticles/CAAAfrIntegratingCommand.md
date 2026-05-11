---
```vbscript
title: "Making Your Commands Available"
category: "use-case"
module: "CAAAfrTechArticles"
tags: []
source_file: "Doc/online/CAAAfrTechArticles/CAAAfrIntegratingCommand.htm"
converted: "2026-05-11T17:17:55.901724"
```

---
# 3D PLM Enterprise Architecture

| 
## User Interface - Frame

| 
### Making Your Commands Available

_How to integrate your commands into the application frame_  
---|---|---  
Technical Article  

* * *
### Abstract

Once you have completed your command development, or even during its development stage, your may want to test them in the application frame, and then make them available to your customers. To do this, you need to decide where to integrate them, and then proceed to the integration. This article gives you tips and explains how to carry out the integration depending on your location decision. Integrating a script as a command is also described. 

  * **Integrating Your Commands**
    * Into a Workbench
    * Into an Add-in
    * Into the Warm Start Mechanism
  * **Integrating a Script as a Command**
  * **In Short**
  * **References**

---  

* * *
### Integrating Your Commands

To make your brand new commands available to your customers, you need to integrate them into one of the following objects: 

  * A workbench: your commands will be available as long as this workbench is the active one. You can either create a new workbench, or modify an existing one. In this case, you should be able to modify the workbench source files
  * An add-in to either a workshop or a workbench, allowing you to add your commands without modifying the workshop or the workbench. Creating an add-in makes you fully independent from the workshop or the workbench provider, and protects your commands from future workshop or workbench evolutions. You can also modify an existing add-in, providing you can modify its source files. The add-in and the commands it contains are available with the workshop or the workbench.

[Top]
#### Into a Workbench

You can either create a new workbench or modify a existing one. 

  * To create a new workbench for you  commands, refer to the example [2]
  * To integrate your commands into an existing workbench, you need to do the following: 
You can either create a new workbench or modify a existing one.
    1. Decide where you want to integrate your commands: in which menus and possibly which submenus, in which toolbars and possibly in which icon boxes, and at which locations with respect to the other existing  commands
    2. Create one or several command header classes, or reuse existing ones you have already created for your workbench
    3. Modify the `CreateCommands` method of the workbench class to add your command header instantiations
    4. Modify the `CreateWorkbench` method to create the command starters and put them in the menus, submenus, toolbars, and icon boxes you choose
    5. Rebuild the workbench shared libraries and DLLs using mkmk
    6. Modify the command header resource files to add the resources you commands will use to display and provide help, such as the menu item titles, the icons for the toolbars, the various help messages, the accelerators and mnemonics, and so forth.

[Top]
#### Into an Add-in

Because you are not their provider, or because you don't want to modify them, you may prefer to remain independent from the workshop or from the workbench into which you intend to integrate your  commands. In this case, the add-in is the solution. You can either create a new add-in, or modify a existing one. 

  * To create an add-in for your  commands, refer to the example [3]
  * To integrate your  commands into an existing add-in, you need to do the following: 
Because you are not their provider, or because you don't want to modify them, you may prefer to remain independent from the workshop or from the workbench into which you intend to integrate your  commands. In this case, the add-in is the solution. You can either create a new add-in, or modify a existing one.
    1. Decide in which toolbars of the add-in you want to integrate your  commands. Remember that you can neither create nor modify a menu or a submenu in an add-in
    2. Create one or several command header classes, or reuse existing ones
    3. Modify the `CreateCommands` method of the add-in class to add your command header instantiations
    4. Modify the `CreateToolbars` method to create the command starters and put them in the toolbars you choose
    5. Rebuild the add-in shared libraries and DLLs
    6. Modify the command header resource files to add the resources your commands will use to display and provide help, such as the icons for the toolbars, the various help messages, the accelerators and mnemonics, and so forth.

[Top]
#### Into the Warm Start Mechanism

If your command modifies the contents of a V5 document, you should ensure its warm start integration. Refer to the technical article entitled "Warm Start Incremental Backup" [3].

[Top]
#### Integrating a Script as a  Command

```vbscript
If your command modifies the contents of a V5 document, you should ensure its warm start integration. Refer to the technical article entitled "Warm Start Incremental Backup" [3].
You can easily customize your toolbars by adding icons to trigger your favorite macros. This reduces the macro access time for the macros you often run.

 This task explains how to add a macro as a command in a toolbar.  
```

You can easily customize your toolbars by adding icons to trigger your favorite macros. This reduces the macro access time for the macros you often run.
This task explains how to add a macro as a command in a toolbar.
 1\. On the **Tools** menu, point to **Macro** , and then click **Macros**. Click **Select** to select the macro you want to add to make sure that the directory path of the file containing the requested macro is concatenated with those recognized by the application. Then click **Cancel**. 

 2\. On the **Tools** menu, click **Customize** , and then click the **Commands** tab. In the **Categories** list, click **Macros.** Drag the macro name and drop it onto the toolbar you wish. The default icon ![](images/CAAAfrCmdInt22.jpg) is used 

 3\. To select another icon than the default one, click **Show Properties** , and click ![](images/CAAAfrCmdInt25.jpg) to display the Icons Browser  box. 

 4\. Click the appropriate icon. The default icon changes to the one clicked. 

![aendtask.gif \(2990 bytes\)](images/aendtask.gif)  

The macro is now ready to use from the toolbar.

[Top]

* * *
### In Short

To make your command available to your customers, you need to integrate it into a workbench, or an add-in. You can also add scripts as commands in toolbars.

[Top]

* * *
### References

[1] | [Creating a Workbench](../CAAAfrUseCases/CAAAfrSampleWorkbench.md)  
---|---  
[2] | [Creating an Add-in](../CAAAfrUseCases/CAAAfrSampleAddin.md)  
[3] | [Warm Start Incremental Backup](CAAAfrWarmstart.md)  
[Top]  

* * *
### History

Version: **1** [Jan 2000] | Document created  
---|---  
Version: **2** [Sep 2003] | Warm Start Integration  
[Top]  

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
