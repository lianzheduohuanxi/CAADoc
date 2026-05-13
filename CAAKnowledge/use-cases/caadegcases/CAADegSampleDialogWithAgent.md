---
title: "Associating a Dialog Box with a Dialog Agent - 1"
category: "use case"
module: "CAADegUseCases"
tags: "["CAADegCreatePolylineCmd", "CAADegPointEditor", "CAADialogEngine", "CAAGeometry", "CAADegCreatePointCmd", "CAADegGeoCommands"]"
source_file: "Doc/online/CAADegUseCases/CAADegSampleDialogWithAgent.htm"
converted: "2026-05-11T17:33:49.626183"
---
tags: ["CAADegCreatePolylineCmd", "CAADegPointEditor", "CAADialogEngine", "CAAGeometry", "CAADegCreatePointCmd", "CAADegGeoCommands"]
source_file: "Doc/online/CAADegUseCases/CAADegSampleDialogWithAgent.htmmd"
converted: "2026-05-11T17:33:49.626183"
3D PLM Enterprise Architecture |  User Interface - Commands |  Associating a Dialog Box with a Dialog Agent - 1 _Using an existing notification to value a dialog agent_

converted: "2026-05-11T17:33:49.626183"
3D PLM Enterprise Architecture |  User Interface - Commands |  Associating a Dialog Box with a Dialog Agent - 1 _Using an existing notification to value a dialog agent_
Use Case

* * *

Abstract This article shows how to use a dialog box to value a dialog agent. The agent is valuated by a notification sent by the Dialog box. In this article, the agent is valuated by an existing notification of the _CATDlgDialog_ class: either the OK, Cancel, Close, and so one notification. For a valuation by a new notification refer to the second part of this article [0]
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

What You Will Learn With This Use Case This use case is intended to show how to use a dialog box associated with a dialog agent in a state dialog command. The dialog box values the dialog agent when the end user presses the OK push button. This dialog box is used to input precise values rather than using the mouse to indicate a point on the screen. [Top] The Polyline Command Use Case The Polyline command is a use case of the CAADialogEngine.edu framework that illustrates the DialogEngine framework capabilities. [Top] What Does the Polyline Command Do The Polyline command creates a polyline by successively indicating or selecting points, or entering their coordinates using a dialog box. A right click stops the polyline creation and exits the command. The Polyline command is a state dialog command according to the following UML statechart diagram [1]. ![CAACreatePolylineStatechart.jpg /(26086 bytes/)](images/CAACreatePolylineStatechart.jpg) The dialog is as follows: ![CAACreatePolyline1.jpg /(18852 bytes/)](images/CAACreatePolyline1.jpg) | Select the Polyline command. The active state becomes StartState, and the dialog box is displayed. You can either indicate or select a point, or use the dialog box.
---|---
What You Will Learn With This Use Case This use case is intended to show how to use a dialog box associated with a dialog agent in a state dialog command. The dialog box values the dialog agent when the end user presses the OK push button. This dialog box is used to input precise values rather than using the mouse to indicate a point on the screen. [Top] The Polyline Command Use Case The Polyline command is a use case of the CAADialogEngine.edu framework that illustrates the DialogEngine framework capabilities. [Top] What Does the Polyline Command Do The Polyline command creates a polyline by successively indicating or selecting points, or entering their coordinates using a dialog box. A right click stops the polyline creation and exits the command. The Polyline command is a state dialog command according to the following UML statechart diagram [1]. ![CAACreatePolylineStatechart.jpg /(26086 bytes/)](images/CAACreatePolylineStatechart.jpg) The dialog is as follows: ![CAACreatePolyline1.jpg /(18852 bytes/)](images/CAACreatePolyline1.jpg) | Select the Polyline command. The active state becomes StartState, and the dialog box is displayed. You can either indicate or select a point, or use the dialog box.
 Click to indicate a point. The point is created. The transition makes the RepeatState the active state. The self transition that creates a temporary line is triggered as long as the mouse moves, even to locate it in the dialog box.
 Enter values in the dialog box spinners. Clicking OK creates the point whose coordinates were entered and creates a line segment between the two points. You can again either click to indicate or select a point, or use the dialog box.
 Enter another set of values in the dialog box spinners and click OK. A third point and a second line segment is created.
 Enter another set of values in the dialog box spinners and click OK. A fourth point and a third line segment is created. Go on indicating or selecting points, or entering values in the dialog box and clicking OK to add line segments to the polyline, or right click to end the command
Indicating a point [2] means clicking on the screen at the desired location with the left mouse key. Selecting a point [3] means clicking on an existing point. A third way to create points is to enter their absolute coordinates in a dialog box. The dialog box is associated with a dialog agent and pressing OK in the dialog box values the dialog agent. This triggers a transition that creates a point with the entered coordinates, and that creates a line segment using the last two created points. We focus on the RepeatState and its self transition that is triggered by the dialog box. [Top] How to Launch the Polyline Command See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched. Then, in the window where you run the mkrun command, do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following:

    * Select **File** ->**New**
    * In the New box, select **CAAGeometry** and click **OK**
    * Select **Insert** ->**Multi Lines** ->**Polyline**
    * Click to create the points that make up the polyline, and right click to end.
[Top] Where to Find the Polyline Command Code The Polyline command is made of a single class named _CAADegCreatePolylineCmd_ located in the CAADegGeoCommands.m module of the CAADialogEngine.edu framework: Windows | `InstallRootDirectory/CAADialogEngine.edu/CAADegGeoCommands.m/`
---|---
Unix | `InstallRootDirectory/CAADialogEngine.edu/CAADegGeoCommands.m/`
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. [Top] Step-by-Step To create the CreatePoint, there are seven steps: # | Step | Where

Unix | `InstallRootDirectory/CAADialogEngine.edu/CAADegGeoCommands.m/`
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. [Top] Step-by-Step To create the CreatePoint, there are seven steps: # | Step | Where
1 | Declare the dialog agent and the dialog box | Header file
2 | Instantiate the dialog agent | `BuildGraph` method [4]
3 | Instantiate the dialog box | `BuildGraph` method
4 | Associate the dialog box with the dialog agent | `BuildGraph` method
5 | Create the RepeatState and plug the dialog agent | `BuildGraph` method
6 | Create the self transition | `BuildGraph` method
7 | Release the indication agent and the dialog box | Destructor

[Top] Declaring the Dialog Agent and the Dialog Box The CAADegCreatePolylineCmd state command class derives from CATStateCommand.

    ...
6 | Create the self transition | `BuildGraph` method
7 | Release the indication agent and the dialog box | Destructor
    class CAADegCreatePolylineCmd : public CATStateCommand

    {
      ...
class CAADegCreatePolylineCmd : public CATStateCommand
```vbscript
      private :

```

        ...
class CAADegCreatePolylineCmd : public CATStateCommand
private :
        CATDialogAgent    * _daEditor;     _// Dialog agent to associate with the dialog box_
        CAADegPointEditor * _PointEditor;  _// Dialog box_

        ...

---
CATDialogAgent    * _daEditor;     _// Dialog agent to associate with the dialog box_
CAADegPointEditor * _PointEditor;  _// Dialog box_
The private part of its header file includes the dialog agent declaration, as well as other members. The dialog agent to associate with the dialog box is a _CATDialogAgent_ instance. The dialog box is a _CAADegPointEditor_ instance that contains a spinner for each coordinate, and the OK, Apply, and Cancel push buttons. [Top] Instantiating the Dialog Agent The dialog agent is instantiated in the `BuildGraph` method.

    void CAADegCreatePolylineCmd::BuildGraph(#)

    {
      ...
The private part of its header file includes the dialog agent declaration, as well as other members. The dialog agent to associate with the dialog box is a _CATDialogAgent_ instance. The dialog box is a _CAADegPointEditor_ instance that contains a spinner for each coordinate, and the OK, Apply, and Cancel push buttons. [Top] Instantiating the Dialog Agent The dialog agent is instantiated in the `BuildGraph` method.
void CAADegCreatePolylineCmd::BuildGraph(#)
      _daEditor = new **CATDialogAgent**("PointEditorId");
      _daEditor->**SetBehavior**(CATDlgEngRepeat);

      ...

---
_daEditor = new **CATDialogAgent**("PointEditorId");
_daEditor->**SetBehavior**(CATDlgEngRepeat);
The character string `PointEditorId` defined as the argument of the _CATDialogAgent_ constructor is the dialog agent identifier. This identifier can be used to assign undo/redo prompts replacing the Undo and Redo items in the Edit menu. The dialog agent behavior is set to `CATDlgEngRepeat` to enable the dialog agent to be valued more than once without being reinitialized and nevertheless remain usable to trigger a transition using the `IsLastModifiedAgentCondition` method. [Top] Instantiating the Dialog Box This is done in the `BuildGraph` method.

    ...
The character string `PointEditorId` defined as the argument of the _CATDialogAgent_ constructor is the dialog agent identifier. This identifier can be used to assign undo/redo prompts replacing the Undo and Redo items in the Edit menu. The dialog agent behavior is set to `CATDlgEngRepeat` to enable the dialog agent to be valued more than once without being reinitialized and nevertheless remain usable to trigger a transition using the `IsLastModifiedAgentCondition` method. [Top] Instantiating the Dialog Box This is done in the `BuildGraph` method.
        CATApplicationFrame * pFrame = NULL ;
        CATDialog * pParent = NULL ;
        pFrame = CATApplicationFrame::**GetFrame**(#) ;
```vbscript
```vbscript
        if ( NULL != pFrame ){
           pParent = pFrame->**GetMainWindow**(#) ;

```

```

        }
pFrame = CATApplicationFrame::**GetFrame**(#) ;
```vbscript
```vbscript
if ( NULL != pFrame ){
pParent = pFrame->**GetMainWindow**(#) ;
       _PointEditor = new **CAADegPointEditor**(pParent);
```

```

       _PointEditor->**Build**(#);

      ...

---
_PointEditor = new **CAADegPointEditor**(pParent);
_PointEditor->**Build**(#);
The dialog box is instantiated and built. It is an instance of the _CAADegPointEditor_ class that derives from the _CATDlgDialog_ class and that simply includes a spinner for each coordinate, and three push buttons OK, Apply, and Cancel. Dialog boxes should always be instantiated without controls (or other dialog objects). Instantiating these controls in a `Build` method called after the constructor has returned make sure that the control resources will be correctly allocated. The parent of this dialog box is an invisible dialog object which contains all the windows of the same document. This object is returned by the `GetMainWindow` method on the application frame. Refer to the article entitled "Understanding the Application Frame Layout" [6] for complete details about this object. [Top] Associating the Dialog Box with the Dialog Agent This association is declared in the `BuildGraph` method.

    ...
      _daEditor->**AcceptOnNotify**(_PointEditor, _PointEditor->**GetDiaOKNotification**(#));
      ...

---
The `AcceptOnNotify` method enables the dialog agent to be valued whenever the dialog box sends an OK notification. This is an instance of the _CATDlgDiaOKNotification_ class retrieved thanks to the `GetDiaOKNotification` method. [Top] Creating the RepeatState and Plugging the Dialog Agent This is still done in the `BuildGraph` method.

    ...
The `AcceptOnNotify` method enables the dialog agent to be valued whenever the dialog box sends an OK notification. This is an instance of the _CATDlgDiaOKNotification_ class retrieved thanks to the `GetDiaOKNotification` method. [Top] Creating the RepeatState and Plugging the Dialog Agent This is still done in the `BuildGraph` method.
      CATDialogState *stRepeatState = **AddDialogState**("stRepeatPointId");

      ...
The `AcceptOnNotify` method enables the dialog agent to be valued whenever the dialog box sends an OK notification. This is an instance of the _CATDlgDiaOKNotification_ class retrieved thanks to the `GetDiaOKNotification` method. [Top] Creating the RepeatState and Plugging the Dialog Agent This is still done in the `BuildGraph` method.
CATDialogState *stRepeatState = **AddDialogState**("stRepeatPointId");
      stRepeatState->**AddDialogAgent**(_daEditor);

    ...

---
The RepeatState is not the first state in the command statechart diagram and is therefore created using the `AddState` method. The `AddDialogAgent` method plugs the dialog agent to the state. [Top] Creating the Self Transition The last to do is to create the self transition triggered when the dialog agent is valued by the OK notification, and that creates the point with the entered coordinates and the corresponding line segment.

    ...
The RepeatState is not the first state in the command statechart diagram and is therefore created using the `AddState` method. The `AddDialogAgent` method plugs the dialog agent to the state. [Top] Creating the Self Transition The last to do is to create the self transition triggered when the dialog agent is valued by the OK notification, and that creates the point with the entered coordinates and the corresponding line segment.
      CATDialogTransition *pRepeatTransitionBox = **AddTransition**

      (
The RepeatState is not the first state in the command statechart diagram and is therefore created using the `AddState` method. The `AddDialogAgent` method plugs the dialog agent to the state. [Top] Creating the Self Transition The last to do is to create the self transition triggered when the dialog agent is valued by the OK notification, and that creates the point with the entered coordinates and the corresponding line segment.
CATDialogTransition *pRepeatTransitionBox = **AddTransition**
        stRepeatState,
        stRepeatState,
        AndCondition(**IsLastModifiedAgentCondition**(_daEditor),

                     **Condition**((ConditionMethod) & CAADegCreatePolylineCmd::CheckPointByBox)),
        **Action**(
stRepeatState,
stRepeatState,
AndCondition(**IsLastModifiedAgentCondition**(_daEditor),
               (ActionMethod) & CAADegCreatePolylineCmd::CreateLineByBox,
               (ActionMethod) & CAADegCreatePolylineCmd::UndoCreateLine,
               (ActionMethod) & CAADegCreatePolylineCmd::RedoCreateLine

              )
      );

---
The `AddTransition` method creates a transition and adds it to the transitions managed by the dialog command. Pointers to the transition's source and target states are the first and second arguments respectively. This self transition goes from/to the same RepeatState. The transition trigger is defined in the guard condition as the first condition to be checked using the `IsLastModifiedAgentCondition` method applied to the indication agent. This method returns True when the dialog agent is valued or if its value is modified. Modifying the value of the dialog agent is made possible because the dialog agent behavior is set to CATDlgEngRepeat. Using `IsLastModifiedAgentCondition` doesn't require to reinitialize the dialog agent. A second condition uses the `CheckPointByBox` method. Because we use `AndCondition` to create the guard condition, both condition methods must return True to fire the transition. In this case, the `CreateLineByBox` action method is executed. The two other action methods are dedicated to respectively undo and redo the action. [Top] Releasing the Indication Agent and the Dialog Box A pointer to the dialog agent was created in the command `BuildGraph` method as a data member to be accessed and used in different methods. It should be released (`RequestDelayedDestruction`) when it becomes useless. This can be done in the command destructor, as shown here. This could also be done in the `Cancel` method called just before the destructor. In the same way, the dialog box should be destructed by using the `RequestDelayedDestruction` method.

    CAADegCreatePolylineCmd::~CAADegCreatePointCmd(#)

    {
The `AddTransition` method creates a transition and adds it to the transitions managed by the dialog command. Pointers to the transition's source and target states are the first and second arguments respectively. This self transition goes from/to the same RepeatState. The transition trigger is defined in the guard condition as the first condition to be checked using the `IsLastModifiedAgentCondition` method applied to the indication agent. This method returns True when the dialog agent is valued or if its value is modified. Modifying the value of the dialog agent is made possible because the dialog agent behavior is set to CATDlgEngRepeat. Using `IsLastModifiedAgentCondition` doesn't require to reinitialize the dialog agent. A second condition uses the `CheckPointByBox` method. Because we use `AndCondition` to create the guard condition, both condition methods must return True to fire the transition. In this case, the `CreateLineByBox` action method is executed. The two other action methods are dedicated to respectively undo and redo the action. [Top] Releasing the Indication Agent and the Dialog Box A pointer to the dialog agent was created in the command `BuildGraph` method as a data member to be accessed and used in different methods. It should be released (`RequestDelayedDestruction`) when it becomes useless. This can be done in the command destructor, as shown here. This could also be done in the `Cancel` method called just before the destructor. In the same way, the dialog box should be destructed by using the `RequestDelayedDestruction` method.
CAADegCreatePolylineCmd::~CAADegCreatePointCmd(#)
      if (_daEditor)    _daEditor->**RequestDelayedDestruction**(#) ;
      _daEditor =  NULL ;
      if (_PointEditor) _PointEditor->**RequestDelayedDestruction**(#);
      _PointEditor = NULL ;

      ...

---
[Top]

* * *

In Short This use case shows how to valuate a dialog agent by a notification sent by a Dialog box. [Top]

* * *

References [0] | [Associating a Dialog Box with a Dialog Agent - 2](CAADegSampleDialogWithAgent2.md)
---|---
[1] | [Describing State Dialog Commands Using UML](../CAADegTechArticles/CAADegUMLDescription.md)
[2] | [Managing Indication](../CAADegTechArticles/CAADegGraph.htm#510000)
[3] | [Managing Selection](../CAADegTechArticles/CAADegGraph.htm#520000)
[4] | [Implementing the Command Statechart Diagram](../CAADegTechArticles/CAADegGraph.md)
[Top]

* * *

History Version: **1** [Jan 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
