---
title: "Untitled"
category: "use-case"
module: "CAAScdInfUseCases"
tags: ["CAAScrBase", "CAALaunch7b", "CAALaunch6", "CAALaunch7a", "CAALaunch1", "CAAInstallation", "CAADoc"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfLauchMacro.htm"
converted: "2026-05-11T11:27:02.701952"
---

---

CAA V5 Automation Uses Cases are macros that may access existing files. To 
make replaying such macros as straightforward as possible, they  most of 
the time follows coding conventions that may require specific SetUp of the V5 
session. This article explains:
**
	

where to find CAA V5 Automation Uses Cases macros,
	

how to launch a macro,
	

which specific setup may be required. 

Note: topics explained in this article, launching macros and 
retrieving existing files from the documentation installation, do not doesn't 
apply to documentation in HtmlHelp format or accessed through a http server.

### Where to find CAA V5 Automation Uses Cases macros

Samples come with a documentation that most of the time contains the name of 
the macro and the module it belongs to.

![](images/CAALaunch7a.jpg)

A module is the folder, in the documentation installation, that contains the documentation 
of the sample along with the macros, located in the `macros` sub folder, and 
required documents in any, located in the `samples` sub folder. 

The URL pointed by the *Execute Macro* text directly points on the macro 
and can be used, on Windows plaforms, to launch the replay of the macro. 

![](images/CAALaunch7b.jpg)

 

A few samples documentations only contain a html view of the content of the 
macro, in this case, the macro must be retrieved from the documentation file, 
for example

`    xxx/myModule/myMacroSource.htm`

is the documentation view of the 

    `xxx/myModule/macros/myMacro.catvbs` or `
xxx/myModule/macros/myMacro.CATScript`

macro.

### How to launch a macro

Macros can also be launched from the V5 session.

 

Please note that the Macro Library must be set to the folder containing the 
macro. 

For more details, on how to run a macro, and set macro libraries, consult in 
the V5 documentation, *Infrastructure Solutions*, *Infrastructure Users 
Guide*, the *Recording, Running And Editing Macros* topic.

### Specific Setups

Unless explicitely specified, CAA Automation Use Cases macros that use 
documents search those documents in a location relative to where the 
documentation is installed and look for the documentation installation path in 
the `CATDocView` environment variable. If this variable is required by the macro but not set, when running the 
macro, the *No Doc Path Defined* error message is diplayed:

![](images/CAALaunch6.jpg) 

If it is set to a place where documents cannot be retrieved, an error message
*Cannot Load Document* is displayed.

	
- If you access the CAA V5 Automation documentation in a V5 product 
	documentation installation linked to a V5 product installation, this 
	variable is already set to

**
	**
		

`<DocInstallation>`
	
	

To be able to replay macros directly from the documentation, use the *Environment Editor* to create a *
	new User Environment* and 
	set the value to:
	**
		

`<DocInstallation>/<Language>`
	
	

Where <Language> is the language for which the documentation has been 
	installed (for example `<DocInstallation>/English`).
	

Remark: you have to use the *Environment Editor* for this 
	purpose, you cannot use the *Tools Options* commands.

	
- If you access the CAA V5 Automation documentation in a CAA installation, 
	use the *Environment Editor* to create a *new User Environment* and 
	set the value to:
	**
		

`<CAAInstallation>/CAADoc/Doc`
	
	

For more details, on how to create and modifiy *Environments*, 
	consult in the V5 documentation, *Infrastructure Solutions*, *
	Installation And Deployment Guide*, the *Managing Environments* 
	topic.

![](images/aendtask.gif)

[Top]

---

*Copyright  1994-2004, Dassault Systmes. All rights reserved.*