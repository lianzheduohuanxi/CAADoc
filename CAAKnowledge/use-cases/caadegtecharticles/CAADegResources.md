---
```vbscript
title: "Assigning Resources to a State Dialog Command"
category: "use-case"
module: "CAADegTechArticles"
tags: ["CAAGeometry", "CAADegCreateTriangleCmd"]
source_file: "Doc/online/CAADegTechArticles/CAADegResources.htmmd"
converted: "2026-05-11T17:33:49.875645"
```

---
tags: ["CAAGeometry", "CAADegCreateTriangleCmd"]
source_file: "Doc/online/CAADegTechArticles/CAADegResources.htmmd"
converted: "2026-05-11T17:33:49.875645"
3D PLM Enterprise Architecture |  User Interface - Commands |  Assigning Resources to a State Dialog Command _How to refer to external resources for the command prompts_

converted: "2026-05-11T17:33:49.875645"
3D PLM Enterprise Architecture |  User Interface - Commands |  Assigning Resources to a State Dialog Command _How to refer to external resources for the command prompts_
Technical Article

* * *

Abstract The resources that you can assign to a state dialog command are the prompts displayed in the status bar for each proposed interaction as a help for the end user, and the prompts for each Undo and Redo step to inform the end user of what can be undone or redone.
    * **Internationalization and Localization**
    * **Internationalizing Prompts of State Dialog Commands**
      * **Prompt Description**
      * **Resource Filename Declaration**
      * **State Prompts**
      * **Undo/Redo Prompts**
        * **Command Undo/Redo Prompts**
        * **Agent Undo/Redo Prompts**
        * **Transition Undo/Redo Prompts**
        * **Recommendations **
    * **In Short**
    * **References**
---

* * *

Internationalization and Localization Even if your don't know if your client application will be used abroad and by people of a different culture and speaking a language different from yours, it is always easier, safer, and cheaper to design and code it as if it should be. Internationalizing a client application means that no assumptions are made about the language, and more generally the locale, used to run your application when you design and code it. When such an application is presented in front of end users from different countries, the same look and feel, and the same functions, are expected whatever the language and locale used. The localized versions of the application should then behave as the version in the original language. Internationalizing an application is also called National Language enabling. This means that the application should be designed and coded in such a way that it could be afterwards localized. Localizing means translating the user interface into the target languages, and possibly do some additional customization. The key point is that localization never requires to recompile any part of the application. To enable for that, any character string displayed in front of the end user must be located in a external text file. CAA V5 is natively National Language enabled, that is includes all the necessary stuff for internationalization, and provides you with any tools and mechanisms to facilitate you internationalizing job. [Top] Internationalizing Prompts of State Dialog Commands You can put the following prompts in a resource file: state prompts and undo/redo prompts. This section first describes them and next explains how to assign them to the state dialog objects. Prompt Description
    * The **state** prompt
The state prompt is displayed:
      * When? when the state becomes active
      * Where? in the message area
    * The **undo/redo** prompts
The undo/redo prompts are related to either a command, an agent or a transition:
      * The **command** undo prompt is displayed when the command is completed, and the redo prompt is displayed when it's just undone.
      * The **agent** undo prompt is displayed when the agent input is completed, and the redo prompt is displayed when the agent input is just undone. However these two prompts are mandatory only if the agent has the CATDlgEngWithUndoStep behavior. For the two other behaviors (CATDlgEngWithUndo and CATDlgEngWithoutUndo) they are useless [2].
      * The **transition** undo prompt is displayed when the transition is completed, and the redo prompt is displayed when it's just undone.
The undo/redo prompts are visible at several places in an interactive session. Here is an example with the _CAADegCreateTriangleCmd_ command [1].
      * In **Edit** menu, in place of the Undo/Redo command Titles
![](images/CAADegResourcesUndoRedoEditMenu.jpg)
---
      * In **toolbars** , when you pass over the Undo/Redo icons:

      * Inside  "**Undo with history** "/ "**Redo with history** "  dialog boxes.
![](images/CAADegResourcesUndoRedoStackTlb.jpg)These dialog boxes are undefined commands which are accessible through the icon boxes of the Standard toolbar. ![](images/CAADegResourcesUndoRedoDlg.jpg)
---
Resource Filename Declaration The resource filenam for a dialog command should be declared using the `CmdDeclareResource` or `CmdDeclareResourceFile` macro in the dialog command class header file. The suffix of this file is CATNls. (The CATRsc file is usually not necessary for a dialog state command)
    * `CmdDeclareResource`

> This macro has two arguments: the dialog command class name is the first parameter, and its base class is the second one.

    class ClassName: public BaseClassName
    {
       **CmdDeclareResource** (ClassName,BaseClassName);
       public :
    }

---
This means that the ` ClassName` class can use the resources defined for the ` BaseClassName` class, if any, according to the rules explained in Understanding Resource Inheritance and Concatenation [3].  The resource file name is `ClassName.CATNls`. Each line of this file begins by the command class name :

    **ClassName.** xxxxxx = "" ;

---
    * `CmdDeclareResourceFile`

> In addition to the `CmdDeclareResource` capabilities, the `CmdDeclareResourceFile` macro enables you to set a resource file name different from the command class name. The first parameter of this macro is the prefix of the resource file, the dialog command class name is the second one, and the command base class is the last one.

    class ClassName: public BaseClassName
    {
       **CmdDeclareResourceFile** (Filename,ClassName,BaseClassName);
       public :
    }

---
This means that the ` ClassName` class can use the resources defined for the ` BaseClassName` class, if any, according to the rules explained in Understanding Resource Inheritance and Concatenation [3].  The resource file name is `FileName.CATNls.` In this resource file, each line begins with the name of the resource file followed by the command class name:

    **FileName.****ClassName.** xxxxxx = "" ;

---
[Top] State Prompts A state prompt is associated with a given state of the state dialog command. The link between the state and the state prompt is done using the state identifier declared when creating the state using `GetInitialState` or `AddDialogState`. For example, assume that these two states are defined in the `BuildGraph` method of the _CAADegCreateTriangleCmd_ state dialog command:

    CATDialogState *stStartState = **GetInitialState**("stFirstPointId");
     ...
    CATDialogState *stSecondState = **AddDialogState**("stSecondPointId");
     ...

---
CATDialogState *stSecondState = **AddDialogState**("stSecondPointId");
The parameters `stFirstPointId` and `stSecondPointId` of the methods `GetInitialState` and `AddDialogState` are the identifiers of the states `stFirstState `and `stSecondState` respectively. The state prompt key used to define the state prompt in the message file is built using the dialog command class name, the state identifier, and the keyword `Message`.

    (Filename.)ClassName.StateId.Message = "The prompted message";

---
```vbscript
```vbscript
For example, the prompts associated with these two states in the message file for _CAADegCreateTriangleCmd_ , that is `CAADegCreateTriangleCmd.CATNls`, are as follows:

```

```

```vbscript
For example, the prompts associated with these two states in the message file for _CAADegCreateTriangleCmd_ , that is `CAADegCreateTriangleCmd.CATNls`, are as follows:
    CAADegCreateTriangleCmd.stFirstPointId.Message   = "Select the first point";
    CAADegCreateTriangleCmd.stSecondPointId.Message  = "Select the second point";

```

---
CAADegCreateTriangleCmd.stFirstPointId.Message   = "Select the first point";
CAADegCreateTriangleCmd.stSecondPointId.Message  = "Select the second point";
```vbscript
If not any message is assigned to a state, the displayed prompt is the identifier of the state. [Top] Undo/Redo Prompts Undo/redo is managed at both the command level and inside the command. At the command level, undo or redo applies to what you did with the command until the command completed. Inside the command, undo or redo applies to the last acquisition managed by a dialog agent, or to the last transition.  [Top] Command Undo/Redo Prompts The prompt keys are built in the message file using the dialog command class name and the keywords `UndoTitle` and `RedoTitle` respectively.

```

    (Filename.)ClassName.UndoTitle="The undo message";
    (Filename.)ClassName.RedoTitle="The redo message";

---
(Filename.)ClassName.UndoTitle="The undo message";
(Filename.)ClassName.RedoTitle="The redo message";
The undo message should not contain the "Undo" word and the redo message should not contain the "Redo" word. These two words are automatically added. It is the reason why the redo prompt can be useless. If the redo prompt is not specified the undo prompt is used.  For example, the undo prompt associated with the _CAADegCreateTriangleCmd_ command in the `CAADegCreateTriangleCmd.CATNls` file is as follows:

```vbscript
    CAADegCreateTriangleCmd.UndoTitle="Triangle Creation";

```

---
The undo message should not contain the "Undo" word and the redo message should not contain the "Redo" word. These two words are automatically added. It is the reason why the redo prompt can be useless. If the redo prompt is not specified the undo prompt is used.  For example, the undo prompt associated with the _CAADegCreateTriangleCmd_ command in the `CAADegCreateTriangleCmd.CATNls` file is as follows:
CAADegCreateTriangleCmd.UndoTitle="Triangle Creation";
The following picture shows the undo and the redo prompts for the Triangle command : ![](images/CAADegResourcesUndoRedoEditMenu.jpg)

---
[Top] Agent Undo/Redo Prompts For example, assume that the following dialog agent is created in the `BuildGraph` method of the _CAADegCreateTriangleCmd_ dialog command:

    ...
    _daPathElement = new CATPathElementAgent("SelStartPoint");
    ...

---
_daPathElement = new CATPathElementAgent("SelStartPoint");
The parameter `SelStartPoint` of the dialog agent constructor is the dialog agent identifier. The prompt keys are built in the message file using the dialog command class name, the dialog agent identifier passed as an argument of its constructor, and the keywords `UndoTitle` and `RedoTitle` respectively.

    (Filename.)ClassName.AgentId.UndoTitle="The undo message";
    (Filename.)ClassName.AgentId.RedoTitle="The redo message";

---
(Filename.)ClassName.AgentId.UndoTitle="The undo message";
(Filename.)ClassName.AgentId.RedoTitle="The redo message";
The undo message should not contain the "Undo" word and the redo message should not contain the "Redo" word. These two words are automatically added. It is the reason why the redo prompt can be useless. If the redo prompt is not specified the undo prompt is used.  For example, the undo prompt associated with the `_daPathElement` agent in the `CAADegCreateTriangleCmd`.`CATNls` file is as follows:

    CAADegCreateTriangleCmd.SelStartPoint.UndoTitle  = "First point selection";

---
The undo message should not contain the "Undo" word and the redo message should not contain the "Redo" word. These two words are automatically added. It is the reason why the redo prompt can be useless. If the redo prompt is not specified the undo prompt is used.  For example, the undo prompt associated with the `_daPathElement` agent in the `CAADegCreateTriangleCmd`.`CATNls` file is as follows:
CAADegCreateTriangleCmd.SelStartPoint.UndoTitle  = "First point selection";
The following pictures show the undo and the redo prompts for the `_daPathElement` agent:  ![](images/CAADegResourcesUndoAgent.jpg)

CAADegCreateTriangleCmd.SelStartPoint.UndoTitle  = "First point selection";
The following pictures show the undo and the redo prompts for the `_daPathElement` agent:  ![](images/CAADegResourcesUndoAgent.jpg)
Transition Undo/Redo Prompts For example, assume that the following transition is created in the `BuildGraph` method of the _CAADegCreateTriangleCmd_ dialog command:

    ...
The following pictures show the undo and the redo prompts for the `_daPathElement` agent:  ![](images/CAADegResourcesUndoAgent.jpg)
Transition Undo/Redo Prompts For example, assume that the following transition is created in the `BuildGraph` method of the _CAADegCreateTriangleCmd_ dialog command:
    CATDialogTransition *pSecondTransition = **AddTransition**

      (
Transition Undo/Redo Prompts For example, assume that the following transition is created in the `BuildGraph` method of the _CAADegCreateTriangleCmd_ dialog command:
CATDialogTransition *pSecondTransition = **AddTransition**
         stSecondState,
         stEndState,
         AndCondition(IsOutputSetCondition(_daPathElement),
```vbscript
                      Condition((ConditionMethod) & CAADegCreateTriangleCmd::CheckPoint2)),
         Action((ActionMethod) & CAADegCreateTriangleCmd::CreateLine,
```

                (ActionMethod) & CAADegCreateTriangleCmd::UndoCreateLine,
                (ActionMethod) & CAADegCreateTriangleCmd::RedoCreateLine)

      ) ;

```vbscript
Action((ActionMethod) & CAADegCreateTriangleCmd::CreateLine,
(ActionMethod) & CAADegCreateTriangleCmd::UndoCreateLine,
(ActionMethod) & CAADegCreateTriangleCmd::RedoCreateLine)
      pSecondTransition->**SetResourceID**("SecondTransition");
```

    ...

---
pSecondTransition->**SetResourceID**("SecondTransition");
In this case, you need to use the ` SetResourceID` method to set the transition identifier. The prompt keys are built in the message file using the dialog command class name, the transition identifier, and the keywords `UndoTitle` and `RedoTitle` respectively.

    (Filename.)ClassName.TransitionId.UndoTitle="The undo transition message";
    (Filename.)ClassName.TransitionId.RedoTitle="The redo transition message";

---
(Filename.)ClassName.TransitionId.UndoTitle="The undo transition message";
(Filename.)ClassName.TransitionId.RedoTitle="The redo transition message";
The undo message should not contain the "Undo" word and the redo message should not contain the "Redo" word. These two words are automatically added. It is the reason why the redo prompt can be useless. If the redo prompt is not specified the undo prompt is used.  For example, the undo prompt associated with the `pSecondTransition` transition  in the `CAADegCreateTriangleCmd`.`CATNls` file is as follows:

    CAADegCreateTriangleCmd.SecondTransition.UndoTitle  = "First line creation";

---
The undo message should not contain the "Undo" word and the redo message should not contain the "Redo" word. These two words are automatically added. It is the reason why the redo prompt can be useless. If the redo prompt is not specified the undo prompt is used.  For example, the undo prompt associated with the `pSecondTransition` transition  in the `CAADegCreateTriangleCmd`.`CATNls` file is as follows:
CAADegCreateTriangleCmd.SecondTransition.UndoTitle  = "First line creation";
The following pictures show the undo and the redo prompts for the  first transition of the `Triangle` command: ![](images/CAADegResourcesUndoTrans.jpg)

![](../CAAIcons/images/warning.gif)If a transition is triggered when a dialog agent is valued, and if both the dialog agent and the transition have prompts, only the transition prompt is displayed. Recommendations
    * The contents of each undo/redo message depends on the command, the agent and the transition, but prefer a noun to a verb. Prefer "Triangle Creation" to "Create Triangle".
    * Do not assign a specific prompt for the redo, the same message for the undo/redo will be used
    * If you have forgot an undo/redo prompt, you can detect them thanks to the syntax used to display a default undo/redo title.
            The left image shows the default title, whereas the right image shows the title coming from the NLS resource file: ![](images/CAADegResourcesWithoutUndoRedo.jpg)
---|---
The **(#)** and the **[]** signs are added to the undo/redo prompts.
      * **(** xxx**) ...** where xxx is the default undo title of the command which is the short help of the last triggered command header.
      * **[** xxx**] ...** where xxx is the identifier of the agent.
[Top]

* * *

In Short The following keywords should be used to build the keys associated with the prompts: Message | Prompt associated with a given state. It should be concatenated with the command and the state identifiers, as follows: `(FileName.)ClassName.StateId.Message`
---|---
In Short The following keywords should be used to build the keys associated with the prompts: Message | Prompt associated with a given state. It should be concatenated with the command and the state identifiers, as follows: `(FileName.)ClassName.StateId.Message`
UndoTitle | Prompt to describe what the undo does. Applies to commands, agents, and transitions, and is built using their identifiers.  | Command | `(FileName.)ClassName.UndoTitle`

In Short The following keywords should be used to build the keys associated with the prompts: Message | Prompt associated with a given state. It should be concatenated with the command and the state identifiers, as follows: `(FileName.)ClassName.StateId.Message`
UndoTitle | Prompt to describe what the undo does. Applies to commands, agents, and transitions, and is built using their identifiers.  | Command | `(FileName.)ClassName.UndoTitle`
Agent | `(FileName.)ClassName.AgentId.UndoTitle`
Transition | `(FileName.)ClassName.TransitionId.UndoTitle`
RedoTitle | Prompt to describe what the redo does. Applies to commands, agents, and transitions, and is built using their identifiers. This prompt is mandatory only if you want a specific text for the redo, otherwise the undo prompt is used.   | Command | `(FileName.)ClassName.RedoTitle`

Agent | `(FileName.)ClassName.AgentId.UndoTitle`
Transition | `(FileName.)ClassName.TransitionId.UndoTitle`
RedoTitle | Prompt to describe what the redo does. Applies to commands, agents, and transitions, and is built using their identifiers. This prompt is mandatory only if you want a specific text for the redo, otherwise the undo prompt is used.   | Command | `(FileName.)ClassName.RedoTitle`
Agent | `(FileName.)ClassName.AgentId.RedoTitle`
Transition | `(FileName.)ClassName.TransitionId.RedoTitle`

[Top]

* * *

References [1] | [The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)
---|---
[2] | [Implementing the Command Statechart Diagram](CAADegGraph.md)
[3] | [Assigning Resources to a Dialog Box](../CAADlgTechArticles/CAADlgResources.md)
[Top]

* * *

History Version: **1** [Jan 2000] | Document created
---|---
Version: **2** [Aug 2003] | Document updated
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
