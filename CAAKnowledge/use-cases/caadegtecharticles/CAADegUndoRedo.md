---
title: "Managing Undo/Redo"
category: "use-case"
module: "CAADegTechArticles"
tags: ["CAACreateTriangleCmd", "CAACreateTriangleCmdGlobalUndo", "CATIUndoTransaction", "CAAIPolyline"]
source_file: "Doc/online/CAADegTechArticles/CAADegUndoRedo.md"
converted: "2026-05-11T17:33:49.900168"
---

3D PLM Enterprise Architecture |  User Interface - Commands |  Managing Undo/Redo _How to undo and redo end user input, transition actions, and command results_  
---|---|---  
Technical Article  
  
* * *

Abstract This article shows how to enable the end user to undo and redo interactions in the active command, and to undo and redo previous command results. 
    * **Managing Undo/Redo**
      * Input Undo/Redo without Object Undo/Redo
      * Input Undo/Redo with Object Undo/Redo
      * Command Undo/Redo without Object Undo/Redo
      * Command Undo/Redo with Object Undo/Redo
    * **In Short**  
---  
  
* * *

Managing Undo/Redo Undo/redo is managed at two levels: 
    1. Input undo/redo
    2. Command undo/redo.
Input undo/redo is available for the current state dialog command only. It enables the end user to successively undo each input, that is to cancel previous input and associated action to restore the document content as it was in each state the command passes through, up to the beginning of the command, and of course to redo, that is to replay canceled input and execute associated actions up to the state where the undo began. If successive undos reach the initial state, the command is deleted and the default command, usually Select, becomes the current one. Command undo/redo takes place to undo previous command global effects, up to the last recorded command. Each command can also be redone in one step, except the command that was current when the end user began to undo, since it was not completed and its effect was not recorded. An object undo/redo can be added to both input and command undo/redo. It is available when the object created or modified by the state dialog command implements the _CATIUndoTransaction_ interface. In this case, the object manages itself its own undo/redo. [Top] Input Undo/Redo without Object Undo/Redo The state dialog command records an input history that allows the end user to undo previous input up to its initial state. Since an input is most of the time an agent valuation, an input usually triggers a transition, and if the guard condition evaluates True, the transition fires and executes an action. Whe the end user clicks Undo, the state dialog command reverses this transition to restore the transition's source state and unvaluates the dialog agent. To reverse the transition, an undo action must be associated with the transition. The dialog agent unvaluation is automatic. In the same way, to enable for redo, that is, to take again the input into account, and restores the transition's final state, a redo action must be associated with the transition. As a result, you must provide an undo action for each action in order to restore the document as it was in the previous state, and a redo action to redo what is undone, along with the corresponding methods. The undo and redo action methods are declared using the second and third parameters of the `Action` method. For example, the transition between two states of a state dialog command that creates triangles could be.
    
    ...
    AddTransition(stStartState,
                  stSecondState,
                  AndCondition(
                     IsOutputSetCondition(_daPathElement),
                     Condition((ConditionMethod) & CAACreateTriangleCmd::CheckPoint1)),
                  Action( 
                     (ActionMethod) & CAACreateTriangleCmd::CreatePoint,
                     (ActionMethod) & CAACreateTriangleCmd::UndoCreatePoint,
                     (ActionMethod) & CAACreateTriangleCmd::RedoCreatePoint)) ;
    ...      
  
---  
[Top] Input Undo/Redo with Object Undo/Redo In this case, the object(s) modified by the command implement the _CATIUndoTransaction_ interface and manage themselves their undo and redo. As a result, the action methods you provide for undo/redo must not modify them. You can provide these methods as in Input Undo/Redo without Object Undo/Redo. They are executed before the undo and redo methods of the _CATIUndoTransaction_ interface. You can also create the action using the `Action` method, and use the `SetBeforeUndo` and `SetBeforeRedo` methods.
    
    ...
    MyAction = Action((ActionMethod) & CAACreateTriangleCmd::CreatePoint);
    MyAction->SetBeforeUndo((ActionMethod) & CAACreateTriangleCmd::BeforeUndoCreatePoint);
    MyAction->SetBeforeRedo((ActionMethod) & CAACreateTriangleCmd::BeforeRedoCreatePoint);
    ...
    AddTransition(stStartState,
                  stSecondState,__              AndCondition(
                     IsOutputSetCondition(_daPathElement),
                     Condition((ConditionMethod) & CAACreateTriangleCmd::CheckPoint1)),
                  MyAction);
    ...  
  
---  
Since the action is created using the `Action` method, it is automatically deleted by the state dialog command. Additional undo and redo methods can be executed after the undo/redo methods of the _CATIUndoTransaction_ interface. They are declared using the `SetAfterUndo` and `SetAfterRedo` methods.
    
    ...
    MyAction->SetAfterUndo((ActionMethod) & CAACreateTriangleCmd::AfterUndoCreatePoint);
    MyAction->SetAfterRedo((ActionMethod) & CAACreateTriangleCmd::AfterRedoCreatePoint);
    ...  
  
---  
[Top] Command Undo/Redo without Object Undo/Redo A command history is managed for command undo/redo. This makes it possible to cancel the effects of the last state dialog commands recorded in this history, and to redo them. For example, the Point command undo deletes the point created, and its redo recreates the deleted point. To make this possible, the command should provide an undo/redo object, instance of the _CATCommandGlobalUndo_ class, using the `GetGlobalUndo` method overridden from the _CATStateCommand_ class. This undo/redo object has, as function members, the methods to be called when the command undo or redo is requested by the end  user, and a method to manage the memory used. The `GetGlobalUndo` method is called when the command completes to put the undo/redo object in the command history ready for use. Command undo/redo is illustrated using a command that creates a triangle. [Top] Providing the Global Undo Object This is possible by overriding the `GetGlobalUndo` method to return an instance of the _CATCommandGlobalUndo_ class with appropriate methods to undo and redo the triangle command effect.
    
    CATCommandGlobalUndo * CAACreateTriangleCmd::GetGlobalUndo()
    {
      CATCommandGlobalUndo * CAACreateTriangleCmdGlobalUndo = NULL;
    
      if ( _EltTriangle )
      {
        CAACreateTriangleCmdGlobalUndo = new CATCommandGlobalUndo(
                 (CATGlobalUndoMethod) & CAACreateTriangleCmd::UndoCreateTriangle,
                 (CATGlobalUndoMethod) & CAACreateTriangleCmd::RedoCreateTriangle,
                 (void *) _EltTriangle,
                 (CATGlobalUndoMethod) & CAACreateTriangleCmd::DeallocateTriangle);
      }
      return CAACreateTriangleCmdGlobalUndo;
    }  
  
---  
The argument of the _CATCommandGlobalUndo_ constructor are: 
    * The method to execute to undo the command effect
    * The method to execute to redo the command effect
    * The object that resulted from the command and that is deleted from the document using the undo method, and recreated in the document by the redo method
    * Since the command doesn't exist any more, the fourth argument sets a method to deallocate the object passed as the third argument.
[Top] Providing the Undo/Redo Methods The undo and redo methods are static, since the command is deleted when undo and redo occur, with the following signatures.
    
    static void UndoCreateTriangle(void * iUsefulData);
    static void RedoCreateTriangle(void * iUsefulData);  
  
---  
These methods are called with the `_EltTriangle` object passed as the third argument of the `GetGlobalUndo` method. They should manage the object deletion and creation in the document. [Top] Providing the Deallocation Method Like the undo and redo method, the deallocation method is also static. It has the following signature:
    
    static void DeallocateTriangle(void * iUsefulData);  
  
---  
It is called when the command undo/redo object is removed from the command history. It should simply delete the object used by the undo and redo method.
    
    void  CAACreateTriangleCmd::DesallocatTriangle(void * iUsefulData)
    {
      if (iUsefulData)
      {
        // iUsefulData is the object to deallocate
        CAAIPolyline * Elt = (CAAIPolyline *) iUsefulData;
        if (Elt) Elt->Release();
      }
    }  
  
---  
[Top] Command Undo/Redo with Object Undo/Redo As with input undo/redo, the objects that implement the _CATIUndoTransaction_ interface manage themselves their undo and redo, and the action methods you provide for undo/redo must not modify them. These object undos are automatically registered when a command that modifies them completes. [Top] Providing the Global Undo Object The `GetGlobalUndo` method can be used to return an instance of the _CATCommandGlobalUndo_ class with appropriate methods. These methods are executed before the object undo/redo methods and must not modify the object.
    
    CATCommandGlobalUndo * CAACreateTriangleCmd::GetGlobalUndo()
    {
      CATCommandGlobalUndo * CAACreateTriangleCmdGlobalUndo = NULL;
    
      if ( _EltTriangle )
      {
        CAACreateTriangleCmdGlobalUndo = new CATCommandGlobalUndo(
                 (CATGlobalUndoMethod) & CAACreateTriangleCmd::BeforeUndoCreateTriangle,
                 (CATGlobalUndoMethod) & CAACreateTriangleCmd::BeforeRedoCreateTriangle,
                 (void *) UsefulObject,
                 (CATGlobalUndoMethod) & CAACreateTriangleCmd::Deallocate);
      }
      return CAACreateTriangleCmdGlobalUndo;
    }  
  
---  
The argument of the _CATCommandGlobalUndo_ constructor are: 
    * The method to execute to undo the command effect before the object undo method
    * The method to execute to redo the command effect before the object redo method
    * An object that can be useful for the command undo and redo method, but NOT the object created or modified by the state dialog command, since this is managed by the object undo/redo
    * The method to deallocate the object passed as the third argument.
You can also declare methods to execute after the object undo/redo. This is possible using the `SetAfterUndoMeth` and `SetAfterRedoMeth` methods.
    
    ...
    SetAfterUndoMeth((CATGlobalUndoMethod) & CAACreateTriangleCmd::AfterUndoCreateTriangle);
    SetAfterRedoMeth((CATGlobalUndoMethod) & CAACreateTriangleCmd::AfterRedoCreateTriangle);
    ...  
  
---  
[Top] Providing the Undo/Redo Methods The undo and redo methods are static, since the command is deleted when undo and redo occur, with the following signatures.
    
    static void BeforeUndoCreateTriangle(void * iUsefulData);
    static void BeforeRedoCreateTriangle(void * iUsefulData);
    static void AfterUndoCreateTriangle(void * iUsefulData);
    static void AfterRedoCreateTriangle(void * iUsefulData);  
  
---  
These methods are called with the `_EltTriangle` object passed as the third argument of the `GetGlobalUndo` method. They should manage the object deletion and creation in the document. [Top] Providing the Deallocation Method Like the undo and redo method, the deallocation method is also static. It has the following signature:
    
    static void Deallocate(void * iUsefulData);  
  
---  
It is called when the command undo/redo object is removed from the command history. It should simply delete the object used by the undo and redo methods. [Top] Deriving the CATCommandGlobalUndo Class Another way of providing command global undo is to create your own class deriving from the _CATCommandGlobalUndo_ class. In this case, you need to override its undo/redo methods.
    
    class MyCommandGlobalUndo : public CATCommandGlobalUndo
    {
      CATDeclareClass;
      public :
        MyCommandGlobalUndo();
        virtual ~MyCommandGlobalUndo();
        virtual HRESULT BeforeUndo();
        virtual HRESULT BeforeRedo();
        virtual HRESULT AfterUndo();
        virtual HRESULT AfterRedo();
    };  
  
---  
`BeforeUndo` and `BeforeRedo` are executed before the object undo/redo methods, and `AfterUndo` and `AfterRedo` are executed after these methods. [Top]

* * *

In Short The undo/redo can be managed for each end user input and for the whole command. If the used object implements the _CATIUndoTransaction_ interface, it manages its own undo/redo by itself, and the methods that implement undo/redo don't need to deal with object undo/redo. Otherwise, they do. The input undo/redo takes place as long as the command is active, and undo/redo methods are provided for each transition. The command undo redo is implemented in a _CATGlobalUndoRedo_ class instance to which pointers to the appropriate undo/redo methods are passed. [Top]

* * *

History Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
