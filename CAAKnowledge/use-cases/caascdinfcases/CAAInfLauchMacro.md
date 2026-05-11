---
title: "Adding a Macro as a Command in a Toolbar"
category: "general"
module: "CAAScdInfUseCases"
tags: ["CAAInstallation", "CAADoc"]
source_file: "Doc\online\CAAScdInfUseCases\CAAInfLauchMacro.htm"
converted: "2026-05-11T17:31:52.379510"
---

| 

## Infrastructure

| 

## Launching a CAA V5 Automation Use Case  
  
---|---  
  
* * *

CAA V5 Automation Uses Cases are macros that may access existing files. To make replaying such macros as straightforward as possible, they  most of the time follows coding conventions that may require specific SetUp of the V5 session. This article explains:

> where to find CAA V5 Automation Uses Cases macros,
> 
> how to launch a macro,
> 
> which specific setup may be required. 

_Note:_ topics explained in this article, launching macros and retrieving existing files from the documentation installation, do not doesn't apply to documentation in HtmlHelp format or accessed through a http server.

### Where to find CAA V5 Automation Uses Cases macros

Samples come with a documentation that most of the time contains the name of the macro and the module it belongs to.

![](images/CAALaunch7a.jpg)

A module is the folder, in the documentation installation, that contains the documentation of the sample along with the macros, located in the `macros` sub folder, and required documents in any, located in the `samples` sub folder. 

The URL pointed by the _Execute Macro_ text directly points on the macro and can be used, on Windows plaforms, to launch the replay of the macro. 

![](images/CAALaunch7b.jpg)

 

A few samples documentations only contain a html view of the content of the macro, in this case, the macro must be retrieved from the documentation file, for example

`    xxx/myModule/myMacroSource.htm`

is the documentation view of the 

    `xxx/myModule/macros/myMacro.catvbs` or ` xxx/myModule/macros/myMacro.CATScript`

macro.

### How to launch a macro

Macros can also be launched from the V5 session.

 

![](images/atarget.gif) |  This task explains how to launch a CAA V5 Automation Use case macro  
---|---  
![](images/ascenari.gif) | 

  1. Select the **Tools- >Macro->Macros... **command to display the Macro dialog box, 

  
![](images/CAALaunch1.jpg)

  2. Select the macro to be launched.
  3. Click the Run button.

   
  
Please note that the Macro Library must be set to the folder containing the macro. 

For more details, on how to run a macro, and set macro libraries, consult in the V5 documentation, _Infrastructure Solutions_ , _Infrastructure Users Guide_ , the _Recording, Running And Editing Macros_ topic.

### Specific Setups

Unless explicitely specified, CAA Automation Use Cases macros that use documents search those documents in a location relative to where the documentation is installed and look for the documentation installation path in the `CATDocView` environment variable. If this variable is required by the macro but not set, when running the macro, the _No Doc Path Defined_ error message is diplayed:

![](images/CAALaunch6.jpg)

If it is set to a place where documents cannot be retrieved, an error message _Cannot Load Document_ is displayed.

  * If you access the CAA V5 Automation documentation in a _V5 product documentation installation_ linked to a V5 product installation, this variable is already set to



> > `<DocInstallation>`
> 
> To be able to replay macros directly from the documentation, use the _Environment Editor_ to create a _new User Environment_ and set the value to:
>
>> `<DocInstallation>/<Language>`
> 
> Where <Language> is the language for which the documentation has been installed (for example `<DocInstallation>/English`).
> 
> _Remark:_ you have to use the _Environment Editor_ for this purpose, you cannot use the _Tools Options_ commands.

  * If you access the CAA V5 Automation documentation in a _CAA installation_ , use the _Environment Editor_ to create a _new User Environment_ and set the value to:

> `<CAAInstallation>/CAADoc/Doc`

For more details, on how to create and modifiy _Environments_ , consult in the V5 documentation, _Infrastructure Solutions_ , _Installation And Deployment Guide_ , the _Managing Environments_ topic.
 
 ![](images/aendtask.gif)
 
 [Top]
 
 * * *
 
 _Copyright 1994-2004, Dassault Systmes. All rights reserved._
