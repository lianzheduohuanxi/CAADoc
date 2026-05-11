---
```vbscript
title: "Creating Contextual Menus"
category: "use-case"
module: "CAADegTechArticles"
tags: ["CAAAnalysisEltTypeCmd", "CAAAnalysisLogCmd", "CAAILine", "CAAxxxCmd"]
source_file: "Doc/online/CAADegTechArticles/CAADegCtxMenu.htm"
converted: "2026-05-11T17:33:49.774351"
```

---
tags: ["CAAAnalysisEltTypeCmd", "CAAAnalysisLogCmd", "CAAILine", "CAAxxxCmd"]
source_file: "Doc/online/CAADegTechArticles/CAADegCtxMenu.htm"
converted: "2026-05-11T17:33:49.774351"
3D PLM Enterprise Architecture |  User Interface - Commands |  Creating Contextual Menus _How to add items to contextual menus when your command is the current one_

converted: "2026-05-11T17:33:49.774351"
3D PLM Enterprise Architecture |  User Interface - Commands |  Creating Contextual Menus _How to add items to contextual menus when your command is the current one_
Technical Article

* * *

Abstract Menus available using the right button of the mouse are called contextual menus because they are created with respect to the object that lies under the mouse. They illustrate the object/action paradigm. Contextual menus can be displayed either when the Select command is active, or with any other command. You can leave the default contextual menu as is, customize it, or create your owns on each of your objects.
    * **What Are Contextual Menus?**
    * **Contextual Menus with A Dialog Command**
      * For Objects Implementing a Given Interface
      * For All Objects and the Viewer Background
      * For the Viewer Background Only
    * **In Short**
---

* * *

What Are Contextual Menus? When you click on an object, a toolbar, or the window background, using the right button of the mouse, a menu generally appears. This menu's contents depends on the object under the mouse when you right-clicked, and is therefore called a contextual menu. Such contextual menus are very handy for the end user since they gather and show the commands available for the object, and only those, without moving the mouse from the object area to the menu bar or to a toolbar. This increases the end user productivity while ensuring that the commands presented are applicable to the object. This prevents from dialog errors. Contextual menus illustrate the object/action paradigm, since the object itself proposes the applicable commands without requiring any knowledge of this applicability from the end user. This article deals with contextual menus triggered from displayed objects or from the background only, and not contextual menus triggered from the status bar or the toolbar areas. Contextual menus onto an object can be found in any state dialog command. The items you add launch member function of the state dialog command class. [Top]

* * *

Contextual Menus with A Dialog Command You can customize contextual menus triggered on any objects, or even when the end user right clicks in the viewer background, when your dialog command is the active one. We'll take as examples dialog commands with only one state that uses a repeatable dialog agent. [Top]

* * *

```vbscript
For Objects Implementing a Given Interface The command we use as example enables the end user to right click only lines, that is object implementing the _CAAILine_ interface. A right click on such objects display a contextual menu with three items, concatenated to the items provided by the window, since we use a _CATFrmGraphAnd3DWindow_ for the document. ![](images/CAACtxMenu1.jpg) | Window's items      Contextual menu's items
```

  Clicking on one of these items displays the start, medium, or end point of the line. To display this contextual menu whenever the end user right clicks on such an object, the following should be done:
    * Create a selection dialog agent [1] that is dedicated to selecting objects that implement _CAAILine_
    * Create a state and a self transition [2] from/to this state triggered by the selection dialog agent valuation and whose action is to create the contextual menu
    * Set callbacks [3] for each menu item
Below is the code to write in the `BuildGraph` method:

    ...
    void CAAxxxCmd::BuildGraph()
    {
      ...
void CAAxxxCmd::BuildGraph()
      _daPathElement = new **CATPathElementAgent**("SelFirstLine");
      _daPathElement->**AddElementType**("CAAILine");
      _daPathElement->**SetBehavior**(**CATDlgEngWithContext** | **CATDlgEngRepeat**);

      CATDialogState * stGetEltState = **AddDialogState**("stGetEltStateId");
      stGetEltState->**AddDialogAgent**(_daPathElement);

      CATDialogTransition * pCntxMenuTransition = **AddTransition**
               (stGetEltState,
                stGetEltState,

                **IsLastModifiedAgentCondition**(_daPathElement),
                **Action**((ActionMethod) & CAAAnalysisLogCmd::CreateCntxMenu));
      ...
    }
    ...

---
A _CATPathElement_ instance is created as a data member of the dialog command class. It is valued for objects implementing the _CAAILine_ interface using the `AddElementType` method, and when right clicking on their representations thanks to the `CATDlgEngWithContext` behavior in the `SetBehavior` method. The `CATDlgEngRepeat` behavior makes this dialog agent repeatable. The dialog agent is added to the appropriate state. The transition loops on this state, and whenever right clicking on a object values the dialog agent, the `CreateCntxMenu` method is executed. This method creates the contextual menus and sets a callback method for each of its item. A method must correspond to each of these callbacks. [Top]

* * *

```vbscript
```vbscript
For All Objects and the Viewer Background The same command should now react to any object whose representation is right clicked. This includes the viewer background. To do this, replace the `AddElementType` method by the `AcceptOnNotify` method to make the dialog agent match any right click, and remove the `CATDlgEngWithContext` behavior from the `AddElementType` method. The rest of the method is unchanged.

```

```

```vbscript
For All Objects and the Viewer Background The same command should now react to any object whose representation is right clicked. This includes the viewer background. To do this, replace the `AddElementType` method by the `AcceptOnNotify` method to make the dialog agent match any right click, and remove the `CATDlgEngWithContext` behavior from the `AddElementType` method. The rest of the method is unchanged.
    void CAAxxxCmd::BuildGraph()
```

    {
void CAAxxxCmd::BuildGraph()
      _daPathElement = new **CATPathElementAgent**("SelFirstLine");
      _daPathElement->**AcceptOnNotify**(NULL, "CATContext");
      _daPathElement->**SetBehavior**(**CATDlgEngRepeat**);

      CATDialogState * stGetEltState = **AddDialogState**("stGetEltStateId");
      stGetEltState->**AddDialogAgent**(_daPathElement);

      CATDialogTransition * pCntxMenuTransition = **AddTransition**
               (stGetEltState,        // From state
                stGetEltState,        // To state

                **IsLastModifiedAgentCondition**(_daPathElement),
                **Action**((ActionMethod) & CAAAnalysisLogCmd::CreateCntxMenu));
    }

---
[Top]

* * *

```vbscript
```vbscript
For the Viewer Background Only Another command should now only react to a right click in the viewer background. It proposes the following contextual menu. ![CAACtxMenu2.jpg \(2845 bytes\)](images/CAACtxMenu2.jpg) Clicking one of these items highlights the corresponding objects of the document. Below is the code to write in the `BuildGraph` method:

```

```

    ...
    void CAAAnalysisEltTypeCmd::BuildGraph()
    {
      ...
void CAAAnalysisEltTypeCmd::BuildGraph()
      _daPathElement = new **CATPathElementAgent**("pathelt");
      _daPathElement->**SetBehavior**( CATDlgEngWithContext | CATDlgEngRepeat );

      _daDialog = new **CATDialogAgent**("dialoagent");
      _daDialog->**SetBehavior**(CATDlgEngRepeat);
      _daDialog->**AcceptOnNotify**(NULL, "CATContext");

      CATDialogState *stBackGroundState = **AddDialogState**("stBackGroundState");
      stBackGroundState->**AddDialogAgent**(_daPathElement);
      stBackGroundState->**AddDialogAgent**(_daDialog);

      CATDialogTransition * pCntxMenuTransition = **AddTransition**
               (stBackGroundState,
                stBackGroundState,

                **IsOutputSetCondition**(_daDialog),
                **Action**((ActionMethod) & CAAAnalysisEltTypeCmd::CreateCntxMenu));
      ...
    }
    ...

---
Two dialog agents are needed: a _CATPathElementAgent_ instance to catch all right clicks on any object representation, and a _CATDialogAgent_ to catch remaining right clicks in the viewer background. These two dialog agents have the same behavior, that is react on right clicks with `CATDlgEngWithContext` for the path element agent, and with the `AcceptOnNotify` method for the dialog agent, and are repeatable with `CATDlgEngRepeat`. Only the last dialog agent is valued using the `AcceptOnNotify` method. The two dialog agents are added to the dialog state in the appropriate order to let the path element agent filter right clicks on any object representation for the dialog agent. The transition is triggered only for the _CATDialogAgent_ instance. As an alternative, rather than using `IsLastModifiedAgentCondition` in the `AddTransition` method, you can use `IsOutPutSetCondition` and recycle the dialog agent in the `CreateCtxMenu` method, as it is done here. The transition loops on this state, and whenever right clicking on a object matches the dialog agent, the `CreateCntxMenu` method is executed. This method creates the contextual menus and sets a callback method for each of its item. A method must correspond to each of these callbacks. [Top]

* * *

In Short Contextual menus can be set onto objects by any dialog command. They can be set onto objects implementing a given interface, onto all objects including the viewer background, and onto the bakground only, thanks to dialog agents filtering the notifications sent by the mouse right click. [Top]

* * *

References [1] | [Managing Selection](CAADegGraph.htm#510000)
---|---
[2] | [Implementing the Statechart Diagram](CAADegGraph.md)
[3] | [Using Callbacks to Trigger Actions](../CAADlgTechArticles/CAADlgCallbacks.md)
[Top]

* * *

History Version: **1** [Jan 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
