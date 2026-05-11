---
title: "Managing the State Dialog Command Lifecycle"
category: "use-case"
module: "CAADegTechArticles"
tags: ["CAACmdWithArg", "CAACommandCmd"]
source_file: "Doc/online/CAADegTechArticles/CAADegLifecycle.md"
converted: "2026-05-11T17:33:49.851891"
---

3D PLM Enterprise Architecture |  User Interface - Commands |  Managing the State Dialog Command Lifecycle _Coding the command class constructor and destructor, and the methods Activate, Desactivate, and Cancel_  
---|---|---  
Technical Article  
  
* * *

Abstract This article shows the roles of the command class constructor and destructor, and of the methods `Activate`, `Desactivate`, and `Cancel` in the command lifecycle. 
    * **Managing the State Dialog Command Lifecycle**
      * Constructor
      * Destructor
      * Activate
      * Desactivate
      * Cancel
    * **In Short**  
---  
  
* * *

Managing the State Dialog Command Lifecycle The command lifecycle is managed using the constructor and the destructor, and using the three methods `Activate`, `Desactivate`, and `Cancel`. [Top] Constructor The command constructor instantiates the command class. It should instantiate or retrieve the command class data members, or retrieve the pointers to the appropriate interfaces set as data members, that should be created once during the command lifecycle, and that are required at the beginning of the command. Using the constructor, and using the _CATStateCommand_ constructor, you can also manage the command running mode and possibly the argument passed to the command from the command header: 
    * The command running (or start) mode, that can be set as the second argument of the _CATStateCommand_ constructor, as: 
      * **Exclusive** : an exclusive command is known by the command selector. It requests the command selector to clean the command stack before beginning to run and taking the focus, including the active command. All commands present in the stack are deleted. Use `CATCommandModeExclusive` to set a command as exclusive
      * **Shared** : a shared command is known by the command selector. It coexists with other commands already present in the stack, and requests the command selector to deactivate the active command before it takes the focus. Use `CATCommandModeShared` to set a command as shared.
![warning.gif \(206 bytes\)](../CAAIcons/images/warning.gif) A state dialog command cannot be set as an undefined command. ![information.gif \(174 bytes\)](../CAAIcons/images/information.gif) A command that creates, modifies, or updates data in the document should always be declared as an **exclusive** command. A shared command, that is, a command that may interrupt another command, should never modify the document, because if it does so, when the previous command resumes after the shared command completion, this command may not found what it has left when interrupted. Any command should properly manage its interruptions using the `Desactivate` method called when a shared command takes the focus. The interrupted command should make the assumption that the interrupting command doesn't modify the document. Any command should also properly manage its deletion using the `Cancel` method called when an exclusive command takes the focus. For example, the _CAACommandCmd_ command is set as exclusive, as shown below.
    
    ...
    CAACommandCmd::CAACommandCmd()
                 : CATStateCommand("CommandId", **CATCommandModeExclusive**), ...
    {
    ...  
  
---  
Note that the exclusive mode is the default mode, and that consequently, `CATCommandModeExclusive` could be removed from the _CATStateCommand_ constructor arguments. Whatever its mode, such a command should have a creation function. It can then be proposed to the end user through a menu item or a toolbar, that is, using a command header that uses this creation function to create the command instance when the end user clicks on the menu item or on the icon in the toolbar. This creation function is itself created using the `CATCreateClass` macro, as shown below.
    
    ...
    #include "CATCreateExternalObject.h"
    CATCreateClass(CAACommandCmd);
    ...  
  
---  
    * The argument passed to the command from the command header as a pointer to an object. This is the case when different menu items or icons seem to run different commands through different command headers, but really activate the same command class by passing an argument to the command class constructor to differentiate from where the input comes, and to execute accordingly. For example, the state dialog command _CAACmdWithArg_ is passed an argument as a pointer to a _CATUnicodeString_ from its different command headers, as shown below.
          
          ...
          CAACmdWithArg::CAACmdWithArg(_CATUnicodeString_ * iArg)
                       : CATStateCommand("CommandId", ...
          {
          ...  
  
---  
Such a command should have its creation function created using the `CATCreateClassArg` macro, as shown below, with the intended pointer type passed as the second argument.
          
          ...
          #include "CATCreateExternalObject.h"
          CATCreateClassArg(CAACmdWithArg, CATUnicodeString);
          ...  
  
---  
Note that any kind of pointer can be passed in place of _CATUnicodeString_. The same type should be declared in both the command constructor and the  `CATCreateClassArg` macro.
[Top] Destructor You should explicitly delete or release the data members created or retrieved once for the command, usually in the constructor or in the `BuildGraph` method, such as the dialog agents, compared to the data members created in the `Activate` method that should generally be deleted in the `Cancel` method. Any state, transition, condition, or action created in `BuildGraph` using the methods proposed by the _CATStateCommand_ class are automatically deleted. These methods are: 
    * States: `GetInitiaState`, `AddDialogState`, `GetCancelState`
    * Transitions: `AddTransition`
    * Conditions: `Condition`, `IsOutputSetCondition`, `IsLastModifiedAgentCondition` `AndCondition`, `OrCondition`, `NotCondition`
    * Actions: `Action`, `AndAction`, `OrAction`
On the opposite, any state (_CATDialogState_), transition (_CATDialogTransition_), condition (_CATStateCondition_), or action (_CATDiaAction_) you explicitly instantiate using its constructor should be deleted in the command class destructor. [Top] Activate `Activate` is called when the state dialog command takes the focus. This happen in two cases: 
    1. The command is just selected by the end user. The command class is instantiated and the dialog starts from the beginning
    2. The command restarts at the state that was current when a shared command took the focus from it.
`Activate` can be used to create temporary objects that are needed from the beginning, either because they help the end user to perform the command, such as the outline of the created object, or a rubber band that follows the mouse, both known as interactive objects and added to the set of interactive objects (ISO), or construction objects that can be helpful. [Top] Desactivate `Desactivate` is called when a shared command takes the focus. The active command becomes inactive, is frozen in its current state and put in the command stack. When the shared command will complete, the frozen command will be reactivated from its current state using the `Activate` method. `Desactivate` should hide temporary objects created by `Activate`, or by the action methods, such as a dialog box, or temporary interactive objects that should be removed from the ISO. Some objects should be deleted, such as the rubber band, that will never be restored as it were since it follows the mouse. [Top] Cancel `Cancel` is called when the command completes, or when an exclusive command takes the focus and requests the command to be deleted. When the command completes, the focus is given to the default command (usually Select). If the command was set as a repeatable, the focus is given to it again. `Cancel` must delete or release temporary objects created by the command, possibly after having removed them from the sets of objects. It should also delete objects created in the action methods, or possibly in the condition methods, even if this code could be put in the destructor, except if the command were declared in repeat mode. When the command is canceled, you can request the command undo when the command completes by calling the `ExecuteUndoAtEnd` method. The following table summarizes the methods that go in pairs for creation/destruction of the command objects. Creation/Destruction | Destructor | Desactivate | Cancel | Undo  
---|---|---|---|---  
Constructor | X |  |  |   
BuildGraph | X |  |  |   
Activate |  |  | X |   
Action method |  |  | X |   
Redo |  |  |  | X  
[Top]

* * *

In Short A dialog state command is a dialog command designed as a state machine, each state enabling end user input, that enables the end user to pass from state to state using transitions between these states triggered when requested events happen and when requested guard conditions are satisfied, and that execute the declared actions. It is modeled using a class deriving from the _CATStateCommand_ class. The statechart diagram is implemented using the `BuildGraph` method, and the command life cycle is managed by the `Activate`, `Desactivate`, and `Cancel` methods in addition to the command class constructor and destructor. [Top]

* * *

History Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
