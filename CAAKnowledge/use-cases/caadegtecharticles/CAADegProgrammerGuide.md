---
title: "DialogEngine Programmer's Guide"
category: "general"
module: "CAADegTechArticles"
tags: []
source_file: "Doc\online\CAADegTechArticles\CAADegProgrammerGuide.htm"
converted: "2026-05-11T17:33:49.859894"
---

3D PLM Enterprise Architecture |  User Interface - Commands |  DialogEngine Programmer's Guide _Programming step-by-step_  
---|---|---  
Technical Article  
  
* * *

Abstract This article is the state dialog command programmer's guide. Organized as a step-by-step, it deals with all you can do to program your state dialog command. 
    * **Creating a State Dialog Command**
    * **In Short**.  
---  
  
* * *

Creating a State Dialog Command Once you have designed your state dialog command and you have drawn its statechart diagram, you can go on with creating the command class. To do this, follow these steps: 
    * [Create the state dialog command class](CAADegCreatingCommand.htm): This includes the declaration of the objects and methods needed by your command in the class header file
    * [Manage the command lifecycle](CAADegLifecycle.htm): To decide what should happen when your command completes, or when another command is selected while your command is the current one, provide the body of the three methods `Activate`, `Desactivate`, and `Cancel`.
    * [Implement the statechart diagram](CAADegGraph.htm): This is done in the overridden CATStateCommand `BuildGraph` method. You will create the states, the transitions, declare the conditions and actions, and create dialog agents to take care of the end user input
    * Provide [condition](CAADegGraph.htm#700000) and [action](CAADegGraph.htm#800000) methods: They are function members of your state dialog command class
    * [Enable for undo/redo](CAADegUndoRedo.htm): You can enable your command with two kinds of undo/redo, the first to undo a given transition result and restore the transition source state, and the second to undo the whole command result after the command completes.
    * [Provide the command resources](CAADegResources.htm): These are the prompts associated with the states and with undo/redo. Other resources, such as the command name, help, and the icon to display in the toolbar, are provided with the command header.
[Top]

* * *

In Short A dialog state command is a dialog command designed as a state machine, each state enabling end user input, that enables the end user to pass from state to state using transitions between these states triggered when requested events happen and when requested guard conditions are satisfied, and that execute the declared actions. It is modeled using a class deriving from the CATStateCommand class. The statechart diagram is implemented using the `BuildGraph` method, and the command life cycle is managed by the `Activate`, `Desactivate`, and `Cancel` methods in addition to the command class constructor and destructor. [Top]

* * *

History Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
