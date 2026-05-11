---
```vbscript
title: "Using a Dialog Box as Input"
category: "use-case"
module: "CAADegTechArticles"
tags: ["CAACommandCmd", "CAAPointEditor"]
source_file: "Doc/online/CAADegTechArticles/CAADegDialogBox.htm"
converted: "2026-05-11T17:33:49.784465"
```

---
tags: ["CAACommandCmd", "CAAPointEditor"]
source_file: "Doc/online/CAADegTechArticles/CAADegDialogBox.htm"
converted: "2026-05-11T17:33:49.784465"
3D PLM Enterprise Architecture |  User Interface - Commands |  Using a Dialog Box as Input _How to take end user input from a dialog window_

converted: "2026-05-11T17:33:49.784465"
3D PLM Enterprise Architecture |  User Interface - Commands |  Using a Dialog Box as Input _How to take end user input from a dialog window_
Technical Article

* * *

Abstract This article shows the different ways of using a dialog box to input values used by a dialog command.
    * **Using a Dialog Box as Input**
    * **In Short**
---

* * *

Using a Dialog Box as Input Using a dialog box as input for a state dialog command is a very common way to get many parameters at the same time. This is possible thanks to a dialog agent created and plugged to the state that displays the dialog box. The dialog agent behavior should be modified using the `AcceptOnNotify` method in order to value the dialog agent, that is accept the end user input and trigger the transition, when, for example, the end user clicks the OK button in the dialog box. ![PointEditor.jpg \(8843 bytes\)](images/PointEditor.jpg) | For example, a command that creates 3D points can use a dialog box to input the point X,Y, and Z coordinates.
---|---
To do this, you should create the dialog box and the dialog agent, set the dialog agent behavior, plug the dialog agent to the state, and create the transition in the `BuildGraph` method. [Top] Creating the Point Editor Dialog Box The Point Editor dialog box is created using a class that derives from the _CATDlgDialog_ class that groups three labels and three spinners, and that features the OK, Apply, and Cancel buttons. This class is instantiated in the `BuildGraph` method and is made visible for the appropriate state.

    ...
Using a Dialog Box as Input Using a dialog box as input for a state dialog command is a very common way to get many parameters at the same time. This is possible thanks to a dialog agent created and plugged to the state that displays the dialog box. The dialog agent behavior should be modified using the `AcceptOnNotify` method in order to value the dialog agent, that is accept the end user input and trigger the transition, when, for example, the end user clicks the OK button in the dialog box. ![PointEditor.jpg \(8843 bytes\)](images/PointEditor.jpg) | For example, a command that creates 3D points can use a dialog box to input the point X,Y, and Z coordinates.
To do this, you should create the dialog box and the dialog agent, set the dialog agent behavior, plug the dialog agent to the state, and create the transition in the `BuildGraph` method. [Top] Creating the Point Editor Dialog Box The Point Editor dialog box is created using a class that derives from the _CATDlgDialog_ class that groups three labels and three spinners, and that features the OK, Apply, and Cancel buttons. This class is instantiated in the `BuildGraph` method and is made visible for the appropriate state.
    _pPointEditor = new CAAPointEditor();
    _pPointEditor->Build();

    ...

---
[Top] Creating the Dialog Agent The  dialog agent is created as an instance of the _CATDialogAgent_ class.

    ...
    _pdaEditorAgent = new CATDialogAgent("PointEditorId");
    ...

---
[Top] Setting the Dialog Agent Behavior The dialog agent behavior must be set in order to value the dialog agent when the end user clicks the OK button of the Point Editor. This is done by using the `AcceptOnNotify` method to which the point editor instance, that is, the notifier, is passed as first parameter, and the notification to react to as second parameter.

    ...
    _pdaEditorAgent->AcceptOnNotify(_pPointEditor,
                                    _pPointEditor->GetDiaOKNotification());
    ...

---
_pdaEditorAgent->AcceptOnNotify(_pPointEditor,
_pPointEditor->GetDiaOKNotification());
The object that sends the notification must always be used. Here, however, this is not the OK push button, but the point editor dialog box, because the dialog box class derives from _CATDlgDialog_ that sends itself the notifications for its OK, Apply, or Cancel push buttons. Once properly configured the `_daEditorAgent` dialog agent is used like any other dialog agent: it must be plugged to a dialog state using the `AddDialogAgent` method before being used in the guard condition as a parameter of the `IsOutputSetCondition` method.

    ...
The object that sends the notification must always be used. Here, however, this is not the OK push button, but the point editor dialog box, because the dialog box class derives from _CATDlgDialog_ that sends itself the notifications for its OK, Apply, or Cancel push buttons. Once properly configured the `_daEditorAgent` dialog agent is used like any other dialog agent: it must be plugged to a dialog state using the `AddDialogAgent` method before being used in the guard condition as a parameter of the `IsOutputSetCondition` method.
    pSourceState->AddDialogAgent(_pdaEditorAgent);

    ...
The object that sends the notification must always be used. Here, however, this is not the OK push button, but the point editor dialog box, because the dialog box class derives from _CATDlgDialog_ that sends itself the notifications for its OK, Apply, or Cancel push buttons. Once properly configured the `_daEditorAgent` dialog agent is used like any other dialog agent: it must be plugged to a dialog state using the `AddDialogAgent` method before being used in the guard condition as a parameter of the `IsOutputSetCondition` method.
pSourceState->AddDialogAgent(_pdaEditorAgent);
    AddTransition(pSourceState, pTargetState,
```vbscript
                  AndCondition(
                     IsOutputSetCondition(_pdaEditorAgent),

```

                  ...
```vbscript
AddTransition(pSourceState, pTargetState,
```vbscript
AndCondition(
IsOutputSetCondition(_pdaEditorAgent),
                  Action(
```

                     (ActionMethod) & CAACommandCmd::CreatePointByBox));
```

    ...

---
```vbscript
Action(
(ActionMethod) & CAACommandCmd::CreatePointByBox));
The `CreatePointByBox` action method uses `_pPointEditor`, the pointer to the dialog box, to retrieve input values. This method should either know the dialog box content to ask the controls to return their value. The dialog box can also explore a method to enable any object to retrieve these values. [Top] Enabling Your Dialog Box for the Power Input Mode The Power Input mode lets the end user enter several values requested by editors or spinners of a dialog box in a single entry field of the main application window when the P2 style is selected. For example, the figure below shows the Hole creation dialog box and how it uses the Power Input field. ![PowerInput.gif \(53540 bytes\)](images/PowerInput.gif) The three spinner entry fields are repeated and concatenated in the status bar:
```

    * The three titles appear in the message area as the Power Input prompt. If the message to display is too long, it overrides the Power Input prompt. This prompt is made up of the three spinner titles separated by commas in English, but the separator associated with the current language is used. This implies to associate a title with the spinners, or more generally also with the editors, while this title is not displayed in the dialog box. The fields displayed in front of the spinners are labels that have their own titles
    * The values are displayed in the entry field. Values are separated using the separator associated with the current language used. The end user can enter the values one after the other, and press Enter. This updates the dialog window spinner values. The entry field has a constant length of 300 pixels
    * The push button at the right is a switch that shows or hides the dialog box.
When the field content doesn't match the expected one, it displayed in red. ![PowerInput2.jpg \(45827 bytes\)](images/PowerInput2.jpg) For example, on the figure above, three fields are expected, and only two are provided. To enable your dialog box to use the Power Input for its editors and spinners, create this box using the `CATDlgPowerInputLink` style. This will automatically enable all the descending editors and spinners to take advantage of the Power Input. This capability can be limited to a part of a dialog box, such as the editors and spinners contained in a frame. To do this, use the `CATDlgPowerInputLink` style in the frame constructor instead of using it in the dialog box constructor. You can dynamically set or reset the Power Input capability using the `SetPowerInputLink` method. You need to call the `UpdatePowerInput` method just after to update the Power Input prompt and entry field.

    ...
When the field content doesn't match the expected one, it displayed in red. ![PowerInput2.jpg \(45827 bytes\)](images/PowerInput2.jpg) For example, on the figure above, three fields are expected, and only two are provided. To enable your dialog box to use the Power Input for its editors and spinners, create this box using the `CATDlgPowerInputLink` style. This will automatically enable all the descending editors and spinners to take advantage of the Power Input. This capability can be limited to a part of a dialog box, such as the editors and spinners contained in a frame. To do this, use the `CATDlgPowerInputLink` style in the frame constructor instead of using it in the dialog box constructor. You can dynamically set or reset the Power Input capability using the `SetPowerInputLink` method. You need to call the `UpdatePowerInput` method just after to update the Power Input prompt and entry field.
    _PointEditor->SetPowerInputLink(0);  // disable
    _PointEditor->UpdatePowerInput();

    ...
_PointEditor->SetPowerInputLink(0);  // disable
_PointEditor->UpdatePowerInput();
    _PointEditor->SetPowerInputLink(1);  //enable
    _PointEditor->UpdatePowerInput();

    ...

---
_PointEditor->SetPowerInputLink(1);  //enable
_PointEditor->UpdatePowerInput();
A single dialog box can use the Power Input at a time. If several dialog boxes that enable the Power Input mode are simultaneously displayed, you must select the one that will use the Power Input using the `TakePowerInputFocus` method and disable the others using the `ReleasePowerInputFocus` method. [Top]

* * *

In Short A dialog state command is a dialog command designed as a state machine, each state enabling end user input, that enables the end user to pass from state to state using transitions between these states triggered when requested events happen and when requested guard conditions are satisfied, and that execute the declared actions. It is modeled using a class deriving from the _CATStateCommand_ class. The statechart diagram is implemented using the `BuildGraph` method, and the command life cycle is managed by the `Activate`, `Desactivate`, and `Cancel` methods in addition to the command class constructor and destructor. [Top]

* * *

History Version: **1** [Jan 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
