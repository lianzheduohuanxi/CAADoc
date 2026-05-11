---
```vbscript
title: "Managing Undo/Redo of Input and Actions"
category: "use case"
module: "CAADegUseCases"
tags: ["CAADegCreatePolylineCmd", "CATIUndoTransaction", "CAADialogEngine", "CAAGeometry", "CAADegGeoCommands"]
source_file: "Doc/online/CAADegUseCases/CAADegSampleInputAndActionUndoRedo.htm"
converted: "2026-05-11T17:33:49.696437"
```

---
tags: ["CAADegCreatePolylineCmd", "CATIUndoTransaction", "CAADialogEngine", "CAAGeometry", "CAADegGeoCommands"]
source_file: "Doc/online/CAADegUseCases/CAADegSampleInputAndActionUndoRedo.htm"
converted: "2026-05-11T17:33:49.696437"
3D PLM Enterprise Architecture |  User Interface - Commands |  Managing Undo/Redo of Input and Actions _Enabling the end user to move back and forth in the statechart diagram_

converted: "2026-05-11T17:33:49.696437"
3D PLM Enterprise Architecture |  User Interface - Commands |  Managing Undo/Redo of Input and Actions _Enabling the end user to move back and forth in the statechart diagram_
Use Case

* * *

Abstract This article shows how to add undo/redo capabilities to a command to enable the end user to go back and forth inside a state dialog command.
    * **What You Will Learn With This Use Case**
    * **The Polyline Command Use Case**
      * What Does the Polyline Command Do
      * How to Launch the Polyline Command
      * Where to Find the Polyline Command Code
    * **Step-by-Step**
    * **In Short**
    * **References**
---

* * *

What You Will Learn With This Use Case This use case is intended to show how to fit out you command with input and action undo/redo capabilities. It deals with a non transactional document model, that is a document model that doesn't include document object undo/redo by means of the _CATIUndoTransaction_ interface implementation. As a consequence, the document object undo/redo must be coded in the undo/redo methods. [Top] The Polyline Command Use Case The Polyline command is a use case of the CAADialogEngine.edu framework that illustrates the DialogEngine framework capabilities. [Top] What Does the Polyline Command Do The Polyline commmand creates a polyline by successively indicating or selecting points, or entering their coordinates using a dialog box. A right click stops the polyline creation and exits the command. During the polyline creation process, the Undo and Redo commands are available to undo each point and line segment creation, possibly up to the first point created, and to redo each point and line segment creation from this first point to the last one. Undoing the first point creation, that is undoing the first input, exits the command. The Polyline command is a state dialog command that creates a polyline according to the following UML statechart diagram [1]. ![CAACreatePolylineStatechart.jpg \(26086 bytes\)](images/CAACreatePolylineStatechart.jpg) Each end user input and associated action can be undone and redone, as shown by the scenario below: ![CAAInputUndo1.jpg \(18521 bytes\)](images/CAAInputUndo1.jpg) | The end user has already created a polyline with four points and thus three line segments. The fifth point is not yet clicked, but a rubber line segment joins the fourth point and the mouse location. The dialog loops onto the RepeatState.
---|---
What You Will Learn With This Use Case This use case is intended to show how to fit out you command with input and action undo/redo capabilities. It deals with a non transactional document model, that is a document model that doesn't include document object undo/redo by means of the _CATIUndoTransaction_ interface implementation. As a consequence, the document object undo/redo must be coded in the undo/redo methods. [Top] The Polyline Command Use Case The Polyline command is a use case of the CAADialogEngine.edu framework that illustrates the DialogEngine framework capabilities. [Top] What Does the Polyline Command Do The Polyline commmand creates a polyline by successively indicating or selecting points, or entering their coordinates using a dialog box. A right click stops the polyline creation and exits the command. During the polyline creation process, the Undo and Redo commands are available to undo each point and line segment creation, possibly up to the first point created, and to redo each point and line segment creation from this first point to the last one. Undoing the first point creation, that is undoing the first input, exits the command. The Polyline command is a state dialog command that creates a polyline according to the following UML statechart diagram [1]. ![CAACreatePolylineStatechart.jpg \(26086 bytes\)](images/CAACreatePolylineStatechart.jpg) Each end user input and associated action can be undone and redone, as shown by the scenario below: ![CAAInputUndo1.jpg \(18521 bytes\)](images/CAAInputUndo1.jpg) | The end user has already created a polyline with four points and thus three line segments. The fifth point is not yet clicked, but a rubber line segment joins the fourth point and the mouse location. The dialog loops onto the RepeatState.
 The end user has clicked Undo. The rubber segment has disappeared, the fourth point and the third line segment are erased from the document.
 The end user has clicked Undo again. The third point and the second line segment are erased from the document.
 The end user has clicked Redo. The third point and the second line segment are recreated.
Any created point and line segment of the polyline can be undone as long as the command is active. This is a sequential process that enables the end user to go back to a previous state by successively going through the states from the current one. Redo is the process that recreates what was undone in the undo reverse order. This is input undo and action undo, because it is dedicated to undo the end user input, and the possible associated action. [Top] How to Launch the Polyline Command See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched. Then, in the window where you run the mkrun command, do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following:

    * Select File->New
    * In the New box, select CAAGeometry and click OK
    * Select Insert->Multi Lines->Polyline
    * Click to create the points that make up the polyline, and right click to end.
[Top] Where to Find the Polyline Command Code The Polyline command is made of a single class named _CAADegCreatePolylineCmd_ located in the CAADegGeoCommands.m module of the CAADialogEngine.edu framework: Windows | `InstallRootDirectory\CAADialogEngine.edu\CAADegGeoCommands.m\`
---|---
Unix | `InstallRootDirectory/CAADialogEngine.edu/CAADegGeoCommands.m/`
Unix | `InstallRootDirectory/CAADialogEngine.edu/CAADegGeoCommands.m/`
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. [Top] Step-by-Step To create the CreatePoint, there are three steps: # | Step | Where

Unix | `InstallRootDirectory/CAADialogEngine.edu/CAADegGeoCommands.m/`
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. [Top] Step-by-Step To create the CreatePoint, there are three steps: # | Step | Where
1 | Provide an undo behavior to the dialog agents (input undo) | `BuildGraph` method [2]
2 | Create the transition with undo and redo methods (action undo) | `BuildGraph` method
3 | Provide the undo and redo methods | Command member functions

[Top] Providing an Undo Behavior to the Dialog Agents The dialog agent undo behavior is set where they are instantiated, that is in the `BuildGraph` method. For example, for the _daEditor agent:

1 | Provide an undo behavior to the dialog agents (input undo) | `BuildGraph` method [2]
2 | Create the transition with undo and redo methods (action undo) | `BuildGraph` method
3 | Provide the undo and redo methods | Command member functions
    void CAADegCreatePolylineCmd::BuildGraph()

    {
      ...
void CAADegCreatePolylineCmd::BuildGraph()
      _daEditor = new **CATDialogAgent**("PointEditorId");
      _daEditor->**SetBehavior**(CATDlgEngRepeat | **CATDlgEngWithUndoStep**);

      ...

---
_daEditor = new **CATDialogAgent**("PointEditorId");
_daEditor->**SetBehavior**(CATDlgEngRepeat | **CATDlgEngWithUndoStep**);
The character string PointEditorId defined as the argument of the CATDialogAgent constructor is the dialog agent identifier. This identifier can be used to assign undo/redo prompts replacing the Undo and Redo items in the Edit menu. ![CAAInputUndo5.jpg \(6147 bytes\)](images/CAAInputUndo5.jpg) | For example, the active state is the target state of a transition triggered by a point indication that can be undone from this state to reach the previous state. In addition, this active state is the source state of a transition that triggers when the point editor dialog box sends an OK notification and is used to create the point using the entered coordinates.

The dialog agent behavior is set to `CATDlgEngWithUndoStep` to record an undo step when the dialog agent is valued. This enables this valuation step to be undone. This behavior is the default, that is, if `CATDlgEngWithUndoStep` were omitted in the SetBehavior method, an undo step were recorded anyway. Changing `CATDlgEngWithUndoStep` to `CATDlgEngWithUndo` doesn't record an undo step for the dialog agent. This means that clicking Undo in the state that follows the one to which the dialog agent is plugged undoes the actions up until a state to which a dialog agent with a `CATDlgEngWithUndoStep` behavior is associated is met, and exits the command if none is found. [Top] Creating the Transition with Undo and Redo Methods The transition are created in the `BuildGraph` method.

    ...
The character string PointEditorId defined as the argument of the CATDialogAgent constructor is the dialog agent identifier. This identifier can be used to assign undo/redo prompts replacing the Undo and Redo items in the Edit menu. ![CAAInputUndo5.jpg \(6147 bytes\)](images/CAAInputUndo5.jpg) | For example, the active state is the target state of a transition triggered by a point indication that can be undone from this state to reach the previous state. In addition, this active state is the source state of a transition that triggers when the point editor dialog box sends an OK notification and is used to create the point using the entered coordinates.
The dialog agent behavior is set to `CATDlgEngWithUndoStep` to record an undo step when the dialog agent is valued. This enables this valuation step to be undone. This behavior is the default, that is, if `CATDlgEngWithUndoStep` were omitted in the SetBehavior method, an undo step were recorded anyway. Changing `CATDlgEngWithUndoStep` to `CATDlgEngWithUndo` doesn't record an undo step for the dialog agent. This means that clicking Undo in the state that follows the one to which the dialog agent is plugged undoes the actions up until a state to which a dialog agent with a `CATDlgEngWithUndoStep` behavior is associated is met, and exits the command if none is found. [Top] Creating the Transition with Undo and Redo Methods The transition are created in the `BuildGraph` method.
      CATDialogTransition *pRepeatTransitionBox = **AddTransition**

      (
The dialog agent behavior is set to `CATDlgEngWithUndoStep` to record an undo step when the dialog agent is valued. This enables this valuation step to be undone. This behavior is the default, that is, if `CATDlgEngWithUndoStep` were omitted in the SetBehavior method, an undo step were recorded anyway. Changing `CATDlgEngWithUndoStep` to `CATDlgEngWithUndo` doesn't record an undo step for the dialog agent. This means that clicking Undo in the state that follows the one to which the dialog agent is plugged undoes the actions up until a state to which a dialog agent with a `CATDlgEngWithUndoStep` behavior is associated is met, and exits the command if none is found. [Top] Creating the Transition with Undo and Redo Methods The transition are created in the `BuildGraph` method.
CATDialogTransition *pRepeatTransitionBox = **AddTransition**
        stRepeatState,
        stRepeatState,
        AndCondition(IsLastModifiedAgentCondition(_daEditor),
```vbscript
                     Condition((ConditionMethod) & CAADegCreatePolylineCmd::CheckPointByBox)),

```

        **Action**(
stRepeatState,
stRepeatState,
AndCondition(IsLastModifiedAgentCondition(_daEditor),
```vbscript
Condition((ConditionMethod) & CAADegCreatePolylineCmd::CheckPointByBox)),
```

               (ActionMethod) & CAADegCreatePolylineCmd::CreateLineByBox,

               **(ActionMethod) & CAADegCreatePolylineCmd::UndoCreateLine**,
               **(ActionMethod) & CAADegCreatePolylineCmd::RedoCreateLine**
              )
      );
      ...

---
The second and third parameters of the `Action` method are the undo and redo method declarations respectively. These methods are usually member functions of the state dialog command class, as shown here. The `UndoCreateLine` method undoes the line segment craeted by `CreateLineByBox`, and the `RedoCreateLine` redoes this line segment creation. [Top] Providing the Undo and Redo Methods The `UndoCreateLine` and `RedoCreateLine` methods have the following signatures.

    ...
    CATBoolean CAADegCreatePolylineCmd::UndoCreateLine(void *iUsefulData)
    {
      ... _// Provide ubdo code here_
    }

    CATBoolean CAADegCreatePolylineCmd::RedoCreateLine(void *iUsefulData)
    {
      ... _// Provide redo code here_
    }
    ...

---
[Top]

* * *

In Short This use case shows how to include input and action undo/redo capabilities to a command. Input undo/redo is for dialog agents and set using the dialog agent behavior. Action undo/redo is added to transitions to undo and redo what action methods do when transition fire. [Top]

* * *

References [1] | [Describing State Dialog Commands Using UML](../CAADegTechArticles/CAADegUMLDescription.md)
---|---
[2] | [Implementing the Statechart Diagram](../CAADegTechArticles/CAADegGraph.md)
[Top]

* * *

History Version: **1** [Jan 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
