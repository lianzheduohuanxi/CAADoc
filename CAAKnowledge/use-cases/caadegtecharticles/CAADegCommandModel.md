---
title: "The CAA Command Model"
category: "general"
module: "CAADegTechArticles"
tags: []
source_file: "Doc\online\CAADegTechArticles\CAADegCommandModel.htm"
converted: "2026-05-11T17:33:49.754845"
---

3D PLM Enterprise Architecture |  User Interface - Frame |  The CAA Command Model _Understanding commands and how they work_  
---|---|---  
Technical Article  
  
* * *

Abstract This article introduces the commands as the key objects allowing for CAA application interactivity. 
    * **Why Commands?**
    * **What Is a CAA Command?**
    * **CAA Command Typology**
    * **The Command Tree Structure**
    * **Command Running Mode and Command Focus and Lifecycle Management**
    * **In Short**
    * **References**  
---  
  
* * *

Why Commands? The high-level interactivity proposed by CAA requires that the basic interactive mechanisms be processed efficiently and consistently. These interactive mechanisms make it possible to: 
    * Propose to the end user the appropriate tools to do intended tasks, possibly using different ways
    * Provide appropriate dialog sequences to do and undo any kind of simple or complex task
    * Manage the end user intent from the mouse click to the active command
    * Enable document object access and update
The last two items illustrate a part of the Model View Controller (MVC) paradigm. CAA offers an object that provides these mechanisms as its behavior: the CAA command. It is the key object to make up the CAA User Interface Model interactive. [Top] What Is a CAA Command? A CAA command is an instance of a class deriving from the CATCommand class and that supports these interactive mechanisms: 
    * Propose to the end user the appropriate tools to do intended tasks, possibly using different ways 
      * Commands are shown in menus and toolbars [1] and can be triggered and executed from there
      * Commands are encapsulated by the direct manipulation
      * Commands can be triggered by the object's contextual menu
    * Provide appropriate dialog sequences to do and undo any kind of simple or complex task 
      * Commands are instances of different command classes to allow the application programmer to create and cover all possible kinds of tasks
      * Commands feature a global and a local undo mechanisms to make it possible to recover a previous document state among the successive document states, as if they were stacked
    * Manage the end user intent from the mouse click to the active command 
      * Command instances build a run time parent/child tree structure
      * Commands use the Send/Receive notification protocol [2] along this tree structure to convey notifications created by end user interactions to the appropriate command
      * Command use a callback mechanism based on the Send/Receive notification protocol, or on typed events, with a callback manager set by default on each command, to enable the appropriate command to receive only the notifications that it can process
    * Enable document object access and update 
      * Commands use a protocol to access document objects through their selected representation in a view
[Top] CAA Command Typology CAA commands fall into the following categories: 
    * Commands seen by the end user as commands and referred to as _dialog commands_. These dialog commands can be: 
      * _One-shot commands_ that are run with no possible additional choice from the end user. The class of a one-shot command should directly derive from the _CATCommand_ class
      * _Dialog boxes_ [3] that enable the end user to enter parameter values or select options. The class of a dialog box class should derive from the _CATDlgDialog_ class
      * _State dialog commands_ [4]: they are built as state machines, to make up high level dialog commands with states and transitions between these states. The class of a state dialog command should derive from the _CATStateCommand_ class.
These dialog commands are available to the end user through menu items in the menu bar, icons or combos in toolbars, or menu items in objects' contextual menus. They are triggered thanks to a command starter that stands for the command behind the push item in the menu bar or push button featuring an icon in a toolbar. This command starter is associated with a command header that holds the command class name and the shared library or DLL containing the command executable code. As soon as the end user clicks the push item or icon, the link is made with the corresponding command starter that requests the command header to load the appropriate shared library or DLL and instantiates the command class.
    * Commands seen by the end user, but either 
      * Not seen as commands, such as a control in a dialog box, or a dialog box part of a state command
      * Implicitly handled using the object direct manipulation, such as manipulators.
One-shot Commands These are commands that are run from their beginning to their end from a single user interaction, with no means to stop them. Their dialog is limited to selecting the push item or the icon in a toolbar that represent them, and can display a confirmation dialog before proceeding. Dialog Box Commands These are commands that appear to the end user as a dialog box. The dialog box is the command itself, rather than being part of another command. The dialog sequence is limited to entering parameter values, or selecting options, and clicking push buttons such as OK, Apply, or Cancel. State Dialog Commands These are commands modeled as state machines. They can have several states. Each state lets the end user select objects, enter parameters, or choose options. Transitions depend on conditions set on what the end user selects, enters, or chooses. If these conditions are met, transitions trigger actions when skipping to the next state to progress to the command completion. Dialog boxes can be used to allow for parameter or option input. [Top] The Command Tree Structure At run time, most of the CAA commands make a tree structure. Each command is usually created with a parent command (or father command), either passed as a parameter in the command class constructor, or using the _CATCommand_ base class constructor, or possibly set or reset using the _CATCommand_ `SetFather` method. This parent has itself a parent, and so on up to the root of the tree named the command selector, a specific command that manages the availability and life cycle of dialog commands. Commands created without a parent, that is with a NULL parent, have automatically the command selector as parent. The figure below is a view of a CAA session as its command tree structure. Fig.1: The Command Tree Structure ![](images/CAAAfrUnderstandingLayout9.jpg)  
---  
This figure shows that:
    * At the top of the command tree, there is a _CATCommandSelector_ class instance created by the V5 application. It is the parent of commands with NULL as parent if there is no current editor. 
    * Each editor which controls the visualization of a document [5] creates a _CATCommandSelector_ class instance whose the parent is the top command selector. This command selector is itself the parent ( CATCommand sense) of: 
      * All the windows of the document (_CATFrmWindow_ class instances),
      * Commands created with NULL as parent. 
    * A dialog box, dependent of the document's life cycle, is created under a decorator. This decorator is created it self by the editor of the document. Whereas, a dialog box, independent of the document's life cycle, is created under the _CATApplicationDocument_ class instance. It is an unique instance returned by the `GetApplicationDocument` method of the _CATApplicationFrame_ class [5].
The dialog command seen by the end user and that is currently running is named the active command. It is said to have the focus, one command being active at a given instant. The command selector manages the focus and gives it to, or takes it from, the dialog commands that the end user selects. ![CAAAfrCommandTree2.gif \(21264 bytes\)](images/CAAAfrCommandTree2.gif) The command tree structure is used to convey end user intents from the object that detects the event up to the object that is able to process it. This is devoted to the Send/Receive notification protocol. For example, in a dialog box, the OK push button is a command created as a child of the dialog box itself, or as one of its subcommands, such as an invisible frame that groups the OK, Apply, and Cancel push buttons. By setting a callback on the push button, the dialog box expects to catch the end user intent when the end user will click OK. The method executed when such an event occurs is a member function of the dialog box class, declared as part of the callback. The object selected by the end user can be something else than a command. For example, in a viewer, an object representation is usually selected. In this case, a manipulator, that is another form of a command, is associated with the representation. [Top] Command Running Mode and Command Focus and Lifecycle Management The command selector manages the focus between the commands. It receives the notifications sent by commands below it to react to end user interactions that climb up along the command tree structure and that were not caught and processed by another command. It sends these notifications to the active command. To enable this management, a dialog command has a running (or start) mode. It can be set as: 
    * **Exclusive** : an exclusive command is known by the command selector. It requests the command selector to clean the command stack before beginning to run and taking the focus, including the previous active command. All commands present in the stack are canceled, that is called on their `Cancel` method. Use `CATCommandModeExclusive` to set a command as exclusive
    * **Shared** : a shared command is known by the command selector. It coexists with other commands already present in the stack, and requests the command selector to deactivate the active command before it takes the focus. Use `CATCommandModeShared` to set a command as shared.
    * **Undefined** : an undefined command is unknown by the command selector. It can run in parallel with the active command known by the command selector. Use `CATCommandModeUndefined` to set a command as undefined. Note that a state dialog command cannot be set as undefined.
![CAAAfrCommandTree4.gif \(3433 bytes\)](images/CAAAfrCommandTree4.gif) | **Exclusive** : The active command is run in the exclusive mode. No other command exists on the command stack.  
---|---  
![CAAAfrCommandTree3.gif \(3776 bytes\)](images/CAAAfrCommandTree3.gif) | **Shared** : The active command is run in the shared mode. Other commands can be deactivated on the command stack If any, they are all shared commands, except the lower command that may be exclusive.  
A dialog command known by the command selector, that is created either as exclusive or shared, is managed by the command selector using the three methods `Activate`, `Desactivate`, and `Cancel`. As a general rule, these methods do the following: 
    * `Activate` is called when the dialog command takes the focus, if it is set as an exclusive or shared command. This happens in three cases:
      1. The command is just selected by the end user. The command class is instantiated and the dialog starts from the beginning
      2. The command is a state dialog command in repeat mode. Each time the command completes, it resumes from the beginning
      3. The command restarts at the state that was current when a shared command took the focus from it.
`Activate` can be used to create temporary objects that are needed from the beginning, either because they help the end user to perform the command, such as the outline of the created object, or a rubber band that follows the mouse, both known as interactive objects and added to the set of interactive objects (ISO), or construction objects that can be helpful.
    * `Desactivate` is called when a shared command takes the focus from the active command. The active command becomes inactive, is frozen in its current state and put in the command stack. When the shared command will complete, the frozen command will be reactivated from its current state using the `Activate` method. `Desactivate` should hide temporary objects created by `Activate`, or by the action methods, such as a dialog box, or temporary interactive objects that should be removed from the ISO. Some objects should be deleted, such as the rubber band, that will never be restored as it were since it follows the mouse.
    * `Cancel` is called when the command completes if it is a state dialog command, or when an exclusive command takes the focus and requests the command to be deleted. When the command completes, the focus is given to the default command (usually Select). `Cancel` must delete or release temporary objects created by the command, possibly after having removed them from the ISO.
The following table shows a summary of when these methods are called, and what they should contain, depending on the command type and running mode. Command Type | Possible Running Modes | Activate | Desactivate | Cancel  
---|---|---|---|---  
One shot | Exclusive | Called when the end user selects the command. Should contain the body of the command and should request the command destruction (*) when the job completes | Called when a shared command takes the focus. Should never be called if `Activate` includes a request to delete the command, since in this case, the command completes before the end user can select another command. Otherwise, should hide its temporary objects. | Called when an exclusive command takes the focus. Never called if `Activate` includes a request to delete the command. Otherwise, should do a clean up of  the command temporary objects ans request the command destruction (*)  
Undefined | Never called | Never called | Never called  
Dialog box | Exclusive or Shared | Called when the end user selects the command or when the command takes the focus again after being put on the command stack by a shared command. Shows the dialog box by default. The dialog box creation should be made in the constructor. | Called when a shared command takes the focus. Hides the dialog box by default | Called when an exclusive command takes the focus. Hides the dialog box box by default. Should request its destruction (*)  
State dialog command | Exclusive or Shared | Called as soon as the end user selects the command or when the command takes the focus again after being put on the command stack by a shared command. Should not contain the body of the command, since this is the role of the BuildGraph method, but can contain the creation of interactive objects that can be useful to the command. | Called when a shared command takes the focus. Should hide its temporary objects, such as dialog boxes, and delete interactive objects | Called when an exclusive command takes the focus, or when the command completes. The command is automatically deleted  
* Requesting a command destruction is made using the `RequestDelayedDestruction` method. [Top]

* * *

In Short The CAA commands are key objects to provide interactivity. They can have the one-shot, dialog boxes, or state dialog command type, depending from their base class. They can run in exclusive, shared, or undefined mode depending on their type. Most of them build a tree structure at run time, used to convey notifications emanating from end user interactions, up to the appropriate command, that is the command able to perform the end user intent. The command at the top of the tree structure, named the command selector, sends orphan notifications to the active command and manages the command focus thanks to the `Activate`, `Desactivate`, and `Cancel` methods that each command should override. [Top]

* * *

References [1] | [Making Your Dialog Commands Available](../CAAAfrTechArticles/CAAAfrIntegratingCommand.htm)  
---|---  
[2] | [The Send/Receive Communication Protocol](../CAASysTechArticles/CAASysSendReceive.htm)  
[3] | [Getting Started with Dialog Boxes](../CAADlgUseCases/CAADlgSampleGettingStarted.htm)  
[4] | [Getting Started with State Dialog Commands](CAADegGettingStarted.htm)  
[5] | [Understanding the Application Frame Layout](../CAAAfrTechArticles/CAAAfrLayoutV5.htm)  
[Top]  
  
* * *

History Version: **1** [Nov 2001] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
