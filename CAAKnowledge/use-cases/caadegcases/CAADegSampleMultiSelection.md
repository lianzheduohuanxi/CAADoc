---
```vbscript
title: "Managing Multi-Selection"
category: "use case"
module: "CAADegUseCases"
tags: ["CAADegCreateNumericCmd", "CAADegAnalysisNumericCmd", "CAADegChoiceBehaviorDlg", "CAADialogEngine", "CAAGeometry", "CAADegAnalysisNumericDlg", "CAADegGeoCommands"]
source_file: "Doc/online/CAADegUseCases/CAADegSampleMultiSelection.htm"
converted: "2026-05-11T17:33:49.728334"
```

---
tags: ["CAADegCreateNumericCmd", "CAADegAnalysisNumericCmd", "CAADegChoiceBehaviorDlg", "CAADialogEngine", "CAAGeometry", "CAADegAnalysisNumericDlg", "CAADegGeoCommands"]
source_file: "Doc/online/CAADegUseCases/CAADegSampleMultiSelection.htm"
converted: "2026-05-11T17:33:49.728334"
3D PLM Enterprise Architecture |  User Interface - Commands |  Managing Multi-Selection _Retrieving existing objects from mouse click or trap selection_  

converted: "2026-05-11T17:33:49.728334"
3D PLM Enterprise Architecture |  User Interface - Commands |  Managing Multi-Selection _Retrieving existing objects from mouse click or trap selection_
Use Case  

* * *

Abstract This article details the multi-selection in a state command class. 
    * **What You Will Learn With This Use Case**
    * **The Numeric Command Use Case**
      * What Does the Numeric Command Do
      * How to Launch the Numeric Command
      * Where to Find the Numeric Command Code
    * **Step-by-Step**
    * **In Short**
    * **References**  
---  

* * *

What You Will Learn With This Use Case The goal of this article is to show and explain the several ways to select a set of objects in a _CATStateCommand_ command. The selection is possible by using a _CATPathElementAgent_ object. This object is a _CATDialogAgent_ whose the behaviors to enable the multi selection are the following:
    * CATDlgEngMultiAcquisition

> Accepts indication or multi-selection with a polygon trap without an user interface.

    * CATDlgEngMultiAcquisitionSelModes

> Accepts indication or multi-selection, with the help of an user interface. The end user can select the selection mode. Triggered as soon as a selection is performed. 

    * CATDlgEngMultiAcquisitionCtrl

> Accepts indication or multi-selection, with the help of an user interface. The end user can select the selection mode. Triggered as soon as the end user validates the selection. 

    * CATDlgEngMultiAcquisitionUserCtrl

> Accepts indication or multi-selection, with the help of an user interface. Triggered as soon as a selection is performed unless the end user toggle to the CATDlgEngMultiAcquisitionCtrl behavior thanks to the user interface. 

This use case shows the usage of the last three behaviors.  [Top] The Numeric Command Use Case The Numeric command is a use case of the CAADialogEngine.edu framework that illustrates the DialogEngine framework capabilities. [Top] What Does the Numeric Command Do The  _CAADegAnalysisNumericCmd_ is a state dialog command which uses three _CATPathElementAgent:_ One for each behavior to test. Its UML statechart diagram [1] is the following: _Fig.1: The UML state chart for the Numeric command_ ![](images/CAADlgMultiSel_UML.jpg)  
---  
This use case shows the usage of the last three behaviors.  [Top] The Numeric Command Use Case The Numeric command is a use case of the CAADialogEngine.edu framework that illustrates the DialogEngine framework capabilities. [Top] What Does the Numeric Command Do The  _CAADegAnalysisNumericCmd_ is a state dialog command which uses three _CATPathElementAgent:_ One for each behavior to test. Its UML statechart diagram [1] is the following: _Fig.1: The UML state chart for the Numeric command_ ![](images/CAADlgMultiSel_UML.jpg)
The dialog is as follows: Select the Numeric command  in the Mathematical Analysis toolbar of the "CAA V5: Geometrical Analysis" workbench. The active state becomes `stChoiceBehaviorState.` ![](images/CAADlgMultiSel_1.jpg) The  "Agent Behavior Choice" dialog box appears: [Fig.2] ![](images/CAADlgMultiSel_10.jpg)Fig.2  

---  
This use case shows the usage of the last three behaviors.  [Top] The Numeric Command Use Case The Numeric command is a use case of the CAADialogEngine.edu framework that illustrates the DialogEngine framework capabilities. [Top] What Does the Numeric Command Do The  _CAADegAnalysisNumericCmd_ is a state dialog command which uses three _CATPathElementAgent:_ One for each behavior to test. Its UML statechart diagram [1] is the following: _Fig.1: The UML state chart for the Numeric command_ ![](images/CAADlgMultiSel_UML.jpg)
The dialog is as follows: Select the Numeric command  in the Mathematical Analysis toolbar of the "CAA V5: Geometrical Analysis" workbench. The active state becomes `stChoiceBehaviorState.` ![](images/CAADlgMultiSel_1.jpg) The  "Agent Behavior Choice" dialog box appears: [Fig.2] ![](images/CAADlgMultiSel_10.jpg)Fig.2
If the end user clicks Ok, the current state becomes:

    * `StMultiAcquisitionSelModesState`, if the first radio button is selected
    * `StMultiAcquisitionStateCtrl`, if the second radio button is selected
    * `StMultiAcquisitionStateUserCtrl`, if the last radio button is selected
If the end user clicks the Cancel button or closes the "Agent Behavior Choice" dialog box, the active state becomes the NULL state. The command is canceled. The end user has chosen the first behavior, `CATDlgEngMultiAcquisitionSelModes`, so the active state is `StMultiAcquisitionStateSelModes`. The "Tools Palette" toolbar appears with a set of selection modes as follows: ![](images/CAADlgMultiSel_3.jpg) To valuate the selection's agent there is two possibilities: 
    * Selection such as the Select toolbar
      * The first icon by indicating or making a trap ( completely in)
      * The second icon by making a trap (completely in)
      * The third icon by making a trap (completely or partially in)
      * The forth icon by making a polygon trap ( completely in)
      * The five icon by selecting object under a paint stroke
    * Use the Search command 
After the selection, the current state becomes `StEndChoiceState`.  The end user has chosen the second behavior, `CATDlgEndMultiAcquisitionCtrl`, so the active state is `StMultiAcquisitionCtrlState`. The "Tools Palette" toolbar appears as follows: ![](images/CAADlgMultiSel_5.jpg)Fig.3  
---  
The Tools Palette contains:
    * A row of icons to choose the selection mode (such as the Select toolbar) 
      * The first icon by indicating or making a trap ( completely in)
      * The second icon by making a trap (completely in)
      * The third icon by making a trap (completely or partially in)
      * The forth icon by making a polygon trap ( completely in)
      * The five icon by selecting object under a paint stroke
Notice that you can always also use the Search command to fill the _CATPathElementAgent_. 
    * A "Selection" editor 
      * if one element selected, its complete path is displayed
      * otherwise the count of selected elements is displayed 
    * A "List Of Selected Item" button which is grayed on the Fig.3. It enables to display all the path when there are several.
    * A Finish button to end the selection. 
In using the Ctrl key, you can de-select an element already selected or add a new element in the current selection. The end user has chosen the third and last behavior, `CATDlgEngMultiAcquisitionUserCtrl`, so the active state is `StMultiAcquisitionUserCtrlState`. The "Tools Palette" toolbar appears as follows: ![](images/CAADlgMultiSel_2.jpg)Fig.4  
---  
Tools Palette contains:
    * A row of icons to choose the selection mode  (same as the previous behavior) 
      * The first icon by indicating or making a trap ( completely in)
      * The second icon by making a trap (completely in)
      * The third icon by making a trap (completely or partially in)
      * The forth icon by making a polygon trap ( completely in)
      * The five icon by selecting object under a paint stroke
Notice that you have always the possibility to use the Search command to fill the _CATPathElementAgent_
    * If the end user clicks the "Control Mode" button, the agent gets the `CATDlgEndMultiAcquisitionCtrl` behavior otherwise the agent is valuated after the first multi-selection or indication. 

> If the end user pushes the "Control Mode" button the "Selection" editor, the "List Of Selected Item" and "Finish" buttons are available.

Notice that you have always the possibility to use the Search command to fill the _CATPathElementAgent_
The active state is `StEndChoiceState`. The end user has finished the selection. The count by type of selected elements are displayed in the "Count of Selected Element" dialog box: ![](images/CAADlgMultiSel_9.jpg)Fig.4 

If the end user clicks the Close button, the Numeric command is canceled. [Top] How to Launch the Numeric Command See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched. Then, in the window where you run the mkrun command, do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following: 
    * On the **Start** menu, select **Infrastructure** and click **CAA V5: Geometrical Analysis**
    * Launch the **Point** command and indicates some points in the viewer 
    * Click **OK** or **Cancel** in the Point Definition dialog box 
    * Launch the **Numeric** ![](images/CAADegAnalysisNumericIcon.jpg)command 
      * The **Agent behavior choice** dialog box appears
      * Choose a behavior
      * Click **OK** to validate the choice, The **Count Of Selected Elements** dialog box appears
      * You have chosen the first behavior 
        * indicate a point or use a trap
      * You have chosen the second behavior, the **Tools Palette** dialog box appears 
        * indicate a point or use a trap
        * indicate a point or use a trap, to modify the selection
        * Ctrl Key + indicate a point or use a trap , to modify the selection
        * Click **Finish** to end the selection
      * You have chosen the third behavior, the **Tools Palette** dialog box appears 
        * indicate a point or use a trap
      * Click **Close** in the **Count Of Selected Elements** dialog box 
[Top] Where to Find the Numeric Command Code The Numeric command is made of three classes:
    * _CAADegAnalysisNumericCmd ,_ the _CATStateCommand  _
    * _CAADegAnalysisNumericDlg_ , the dialog box [Fig.4] to display the count of selected object. This class is not explained here.
    * _CAADegChoiceBehaviorDlg_ , the dialog box [Fig.2] to choose the behavior of the selection's agent. This class is not explained here.
located in the CAADegGeoCommands.m module of the CAADialogEngine.edu framework: Windows | `InstallRootDirectory\CAADialogEngine.edu\CAADegGeoCommands.m\`  
---|---  
located in the CAADegGeoCommands.m module of the CAADialogEngine.edu framework: Windows | `InstallRootDirectory\CAADialogEngine.edu\CAADegGeoCommands.m\`
Unix | `InstallRootDirectory/CAADialogEngine.edu/CAADegGeoCommands.m/`  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. [Top] Step-by-Step There is five logical steps: 
    1. Declaring the Selection Agents
    2. Instantiating the Selection Agents
    3. Creating the States and the Transitions
    4. Retrieving the Selected Objects
    5. Releasing the Selection Agents

[Top] Declaring the Selection Agents The state command class derives from CATStateCommand.

3. Creating the States and the Transitions
4. Retrieving the Selected Objects
5. Releasing the Selection Agents
    class CAADegCreateNumericCmd : public CATStateCommand

    {
      ...
class CAADegCreateNumericCmd : public CATStateCommand
      private :

        **CATPathElementAgent**  * _daMultiAcquisitionSelModes ;  
class CAADegCreateNumericCmd : public CATStateCommand
private :
        CATPathElementAgent  * _daMultiAcquisitionCtrl ;
        CATPathElementAgent  * _daMultiAcquisitionUserCtrl ;

        ...  

---  
A pointer for each selection agent is declared as a private data member. Selection agents are instances of the _CATPathElementAgent_ class. 
    * `_daMultiAcquisitionSelModes` will be used for the `CATDlgEngMultiAcquisitionSelModes `behavior`, `
    * `_daMultiAcquisitionCtrl` for the `CATDlgEngMultiAcquisitionCtrl `behavior` `and 
    * _daMultiAcquisitionUserCtrl for the `CATDlgEngMultiAcquisitionUserCtrl `behavior`.`
[Top] Instantiating the Selection Agents The selection agents are instantiated in the command `BuildGraph` method. For the `_daMultiAcquisitionSelModes `agent, 

    void CAADegCreateNumericCmd::BuildGraph()
    {
      ...
void CAADegCreateNumericCmd::BuildGraph()
       _daMultiAcquisitionSelModes = new **CATPathElementAgent**("PathEltMultiAcquisitionSelModes");

       _daMultiAcquisitionSelModes ->**SetBehavior**( CATDlgEngWithPSOHSO |CATDlgEngWithPrevaluation       

                                  **CATDlgEngMultiAcquisitionSelModes** ); 

_daMultiAcquisitionSelModes = new **CATPathElementAgent**("PathEltMultiAcquisitionSelModes");
_daMultiAcquisitionSelModes ->**SetBehavior**( CATDlgEngWithPSOHSO |CATDlgEngWithPrevaluation
       _daMultiAcquisitionSelModes ->**AddElementType**(IID_CAAISysPoint);
       _daMultiAcquisitionSelModes ->AddElementType(IID_CAAISysLine);
       _daMultiAcquisitionSelModes ->AddElementType(IID_CAAISysEllipse);
       _daMultiAcquisitionSelModes ->AddElementType(IID_CAAISysCircle);
       _daMultiAcquisitionSelModes ->AddElementType(IID_CAAISysPlane);

      ...  

---  
_daMultiAcquisitionSelModes ->AddElementType(IID_CAAISysCircle);
_daMultiAcquisitionSelModes ->AddElementType(IID_CAAISysPlane);
The character string `PathEltMultiAcquisitionSelModes` defined as the argument of the _CATPathElementAgent_ constructor is the selection agent identifier. This identifier can be used to assign undo/redo prompts replacing the Undo and Redo items in the Edit menu. To affect a specific behavior to the _CATPathElementAgent_ object, use the `SetBehavior `method. The `CATDlgEngWithPSOHSO` and `CATDlgEngWithPrevaluation`  styles enables to pre-highlight the available elements and to highlight the selected elements. The `CATDlgEngMultiAcquisitionSelModes` indicates a multi-selection. At last, thanks to the `AddElementType` method, the selection agent is valued only when an object that implements one of these five interfaces is selected. The selection agent remains impassive when any object that doesn't implement this interface is selected. For the `_daMultiAcquisitionCtrl` agent, only the behavior changes:

    ...
The character string `PathEltMultiAcquisitionSelModes` defined as the argument of the _CATPathElementAgent_ constructor is the selection agent identifier. This identifier can be used to assign undo/redo prompts replacing the Undo and Redo items in the Edit menu. To affect a specific behavior to the _CATPathElementAgent_ object, use the `SetBehavior `method. The `CATDlgEngWithPSOHSO` and `CATDlgEngWithPrevaluation`  styles enables to pre-highlight the available elements and to highlight the selected elements. The `CATDlgEngMultiAcquisitionSelModes` indicates a multi-selection. At last, thanks to the `AddElementType` method, the selection agent is valued only when an object that implements one of these five interfaces is selected. The selection agent remains impassive when any object that doesn't implement this interface is selected. For the `_daMultiAcquisitionCtrl` agent, only the behavior changes:
       _daMultiAcquisitionCtrl = new CATPathElementAgent("PathEltMultiAcquisitionCtrl");

       _daMultiAcquisitionCtrl->SetBehavior( CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation              

                                  **CATDlgEngMultiAcquisitionCtrl** ); 

_daMultiAcquisitionCtrl = new CATPathElementAgent("PathEltMultiAcquisitionCtrl");
_daMultiAcquisitionCtrl->SetBehavior( CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation
       _daMultiAcquisitionCtrl->AddElementType(IID_CAAISysPoint);
       _daMultiAcquisitionCtrl->AddElementType(IID_CAAISysLine);
       _daMultiAcquisitionCtrl->AddElementType(IID_CAAISysEllipse);
       _daMultiAcquisitionCtrl->AddElementType(IID_CAAISysCircle);
       _daMultiAcquisitionCtrl->AddElementType(IID_CAAISysPlane);

      ...  

---  
_daMultiAcquisitionCtrl->AddElementType(IID_CAAISysCircle);
_daMultiAcquisitionCtrl->AddElementType(IID_CAAISysPlane);
And for the `_daMultiAcquisitionUserCtrl` agent :

    ...
And for the `_daMultiAcquisitionUserCtrl` agent :
       _daMultiAcquisitionUserCtrl = new CATPathElementAgent("PathEltMultiAcquisitionUserCtrl");

       _daMultiAcquisitionUserCtrl ->SetBehavior( CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation                

                                  **CATDlgEngMultiAcquisitionUserCtrl**); 

_daMultiAcquisitionUserCtrl = new CATPathElementAgent("PathEltMultiAcquisitionUserCtrl");
_daMultiAcquisitionUserCtrl ->SetBehavior( CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation
       _daMultiAcquisitionUserCtrl ->AddElementType(IID_CAAISysPoint);
       _daMultiAcquisitionUserCtrl ->AddElementType(IID_CAAISysLine);
       _daMultiAcquisitionUserCtrl ->AddElementType(IID_CAAISysEllipse);
       _daMultiAcquisitionUserCtrl ->AddElementType(IID_CAAISysCircle);
       _daMultiAcquisitionUserCtrl ->AddElementType(IID_CAAISysPlane);

      ...  

---  
[Top] Creating the States and the Transitions After the agent's creation, the states are created and the agents are associated with them.

    ...
       CATDialogState *stMultiAcquisitionSelModesState = 
                       AddDialogState("stMultiAcquisitionSelModesStateId");
       stMultiAcquisitionSelModesStateId->**AddDialogAgent**(_daMultiAcquisitionSelModes);

       ...

CATDialogState *stMultiAcquisitionSelModesState =
AddDialogState("stMultiAcquisitionSelModesStateId");
stMultiAcquisitionSelModesStateId->**AddDialogAgent**(_daMultiAcquisitionSelModes);
       CATDialogState *stMultiAcquisitionCtrlState = 
                       AddDialogState("stMultiAcquisitionCtrlStateId");
       stMultiAcquisitionCtrlState->**AddDialogAgent**(_daMultiAcquisitionCtrl);

       ...
CATDialogState *stMultiAcquisitionCtrlState =
AddDialogState("stMultiAcquisitionCtrlStateId");
stMultiAcquisitionCtrlState->**AddDialogAgent**(_daMultiAcquisitionCtrl);
       CATDialogState *stMultiAcquisitionUserCtrlState = 
                       AddDialogState("stMultiAcquisitionUserCtrlStateId");
       stMultiAcquisitionUserCtrlState->**AddDialogAgent**(_daMultiAcquisitionUserCtrl);

       ...

---  
The `AddDialogState` method creates a new dialog state and adds it to the states managed by the dialog command. The `AddDialogAgent` method adds the selection agent to the state. `stMultiAcquisitionSelModesStateId, stMultiAcquisitionCtrlStateId `and` stMultiAcquisitionUserCtrlStateId` are identifiers used to set a prompt displayed in the status bar when the state is active. At last, the transitions are created:

    ...
The `AddDialogState` method creates a new dialog state and adds it to the states managed by the dialog command. The `AddDialogAgent` method adds the selection agent to the state. `stMultiAcquisitionSelModesStateId, stMultiAcquisitionCtrlStateId `and` stMultiAcquisitionUserCtrlStateId` are identifiers used to set a prompt displayed in the status bar when the state is active. At last, the transitions are created:
       CATDialogTransition *pTransition32 =    AddTransition

       (
The `AddDialogState` method creates a new dialog state and adds it to the states managed by the dialog command. The `AddDialogAgent` method adds the selection agent to the state. `stMultiAcquisitionSelModesStateId, stMultiAcquisitionCtrlStateId `and` stMultiAcquisitionUserCtrlStateId` are identifiers used to set a prompt displayed in the status bar when the state is active. At last, the transitions are created:
CATDialogTransition *pTransition32 =    AddTransition
          stMultiAcquisitionSelModesState,
          stEndState,

          **IsOutputSetCondition**(_daMultiAcquisitionSelModes), 
CATDialogTransition *pTransition32 =    AddTransition
stMultiAcquisitionSelModesState,
stEndState,
          Action((ActionMethod) & 
            CAADegAnalysisNumericCmd::**DisplaySelectedElement** ,NULL,NULL,(void*)**1**)

       ) ; 
       ...

```vbscript
Action((ActionMethod) &
CAADegAnalysisNumericCmd::**DisplaySelectedElement** ,NULL,NULL,(void*)**1**)
    CATDialogTransition *pTransition42 =    AddTransition
```

       (
CATDialogTransition *pTransition42 =    AddTransition
          stMultiAcquisitionCtrlState,
          stEndState,

          **IsOutputSetCondition**(_daMultiAcquisitionCtrl), 
CATDialogTransition *pTransition42 =    AddTransition
stMultiAcquisitionCtrlState,
stEndState,
          Action((ActionMethod) & 
            CAADegAnalysisNumericCmd::**DisplaySelectedElement** ,NULL,NULL,(void*)**2**)

       ) ; 

    ...
```vbscript
Action((ActionMethod) &
CAADegAnalysisNumericCmd::**DisplaySelectedElement** ,NULL,NULL,(void*)**2**)
       CATDialogTransition *pTransition52 =    AddTransition
```

       (
CATDialogTransition *pTransition52 =    AddTransition
          stMultiAcquisitionUserCtrlState,
          stEndState,

          **IsOutputSetCondition**(_daMultiAcquisitionUserCtrl), 
CATDialogTransition *pTransition52 =    AddTransition
stMultiAcquisitionUserCtrlState,
stEndState,
          Action((ActionMethod) & 
            CAADegAnalysisNumericCmd::**DisplaySelectedElement** ,NULL,NULL,(void*)**3**)

       ) ; 
       ...

---  
Retrieving the Selected Objects In the `DisplaySelectedElement`**** Action method, executed when the transitions, defined in the previous step, are triggered. `iData` is the value set in the transition.

    CATBoolean CAADegAnalysisNumericCmd::DisplaySelectedElement(void * iData)
    {

Retrieving the Selected Objects In the `DisplaySelectedElement`**** Action method, executed when the transitions, defined in the previous step, are triggered. `iData` is the value set in the transition.
CATBoolean CAADegAnalysisNumericCmd::DisplaySelectedElement(void * iData)
      int CaseAgent = (int ) iData ;

      ...

      **CATSO * pSO = NULL ;**

```vbscript
      if ( 1 == CaseAgent ) pSO = _daMultiAcquisitionSelModes->**GetListOfValues**();
      if ( 2 == CaseAgent ) pSO = _daMultiAcquisitionCtrl->**GetListOfValues**();
      if ( 3 == CaseAgent ) pSO = _daMultiAcquisitionUserCtrl->**GetListOfValues**();

      if ( NULL != pSO )
```

      {
```vbscript
if ( 2 == CaseAgent ) pSO = _daMultiAcquisitionCtrl->**GetListOfValues**();
if ( 3 == CaseAgent ) pSO = _daMultiAcquisitionUserCtrl->**GetListOfValues**();
if ( NULL != pSO )
         int lg = pSO->**GetSize**();

         for ( int i=0 ; i < lg ; i++)
```

         {
int lg = pSO->**GetSize**();
for ( int i=0 ; i < lg ; i++)
           CATPathElement * pPath = (CATPathElement*) (*pSO)[i] ;

     ...
    }  

---  
To retrieve the selected element use the `GetListOfValues` method on the current agent. The list is a _CATSO_ object.  [Top] Releasing the Selection Agents A pointer to each selection agent was created in the command `BuildGraph` method as a data member to be accessed and used in different methods. It should be released when it becomes useless. This can be done in the command destructor, as shown here. This could also be done in the `Cancel` method called just before the destructor.

    CAADegCreateNumericCmd::~CAADegCreateNumericCmd()
    {
      ...
To retrieve the selected element use the `GetListOfValues` method on the current agent. The list is a _CATSO_ object.  [Top] Releasing the Selection Agents A pointer to each selection agent was created in the command `BuildGraph` method as a data member to be accessed and used in different methods. It should be released when it becomes useless. This can be done in the command destructor, as shown here. This could also be done in the `Cancel` method called just before the destructor.
CAADegCreateNumericCmd::~CAADegCreateNumericCmd()
      if ( NULL != _daMultiAcquisitionSelModes  )  

      {
CAADegCreateNumericCmd::~CAADegCreateNumericCmd()
if ( NULL != _daMultiAcquisitionSelModes  )
         _daMultiAcquisitionSelModes  -> **RequestDelayedDestruction**()  ;
         _daMultiAcquisitionSelModes  = NULL ;

      }
```vbscript
if ( NULL != _daMultiAcquisitionSelModes  )
_daMultiAcquisitionSelModes  -> **RequestDelayedDestruction**()  ;
_daMultiAcquisitionSelModes  = NULL ;
      if ( NULL != _daMultiAcquisitionCtrl )
```

      {
_daMultiAcquisitionSelModes  -> **RequestDelayedDestruction**()  ;
_daMultiAcquisitionSelModes  = NULL ;
if ( NULL != _daMultiAcquisitionCtrl )
         _daMultiAcquisitionCtrl -> RequestDelayedDestruction()  ;
         _daMultiAcquisitionCtrl = NULL ;

      }
```vbscript
if ( NULL != _daMultiAcquisitionCtrl )
_daMultiAcquisitionCtrl -> RequestDelayedDestruction()  ;
_daMultiAcquisitionCtrl = NULL ;
      if ( NULL != _daMultiAcquisitionUserCtrl )
```

      {
_daMultiAcquisitionCtrl -> RequestDelayedDestruction()  ;
_daMultiAcquisitionCtrl = NULL ;
if ( NULL != _daMultiAcquisitionUserCtrl )
         _daMultiAcquisitionUserCtrl -> RequestDelayedDestruction()  ;
         _daMultiAcquisitionUserCtrl = NULL ;

      }
      ...  

---  
[Top]

* * *

In Short This use case shows how to use a _CATPathElementAgent_ to have multi-selection in a _CATStateCommand_. [Top]

* * *

References [1] | [Describing State Dialog Commands Using UML](../CAADegTechArticles/CAADegUMLDescription.md)  
---|---  
[Top]  

* * *

History Version: **1** [Sep 2002] | Document created  
---|---  
History Version: **1** [Sep 2002] | Document created
Version: **2** [Nov 2002] | Document updated for new selection modes  
Version: **3** [May 2003] | Document updated for new behaviors and Tools Palette introduction  

[Top]  

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
