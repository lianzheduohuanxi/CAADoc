---
title: "Associating a Dialog Box with a State"
category: "use case"
module: "CAADegUseCases"
tags: ["CAADegGeoCommands", "CAADegPointEditor", "CATIndicationAgent", "CAADialogEngine", "CAAGeometry", "CAADegCreatePointCmd", "CAADegFileCmd"]
source_file: "Doc/online/CAADegUseCases/CAADegSampleDialogWithPanelState.htm"
converted: "2026-05-11T17:33:49.657183"
---

3D PLM Enterprise Architecture |  User Interface - Commands |  Associating a Dialog Box with a State _Using a dialog box to input data and to trigger several transition from a state_  
---|---|---  
Use Case  
  
* * *

Abstract This article shows how to use a Dialog box associated with a state in a state dialog command. 
    * **What You Will Learn With This Use Case**
    * **The Point Command Use Case**
      * What Does the Point Command Do
      * How to Launch the Point Command
      * Where to Find the Point Command Code
    * **Step-by-Step**
    * **In Short**
    * **References**  
---  
  
* * *

What You Will Learn With This Use Case This use case is intended to show how to use a dialog box associated with a state in a dialog command. This dialog box is used to input precise values rather than indicating a point on the screen. In addition, you will learn how to use the Cancel state. [Top] The Point Command Use Case The Point command is a use case of the CAADialogEngine.edu framework that illustrates the DialogEngine framework capabilities. [Top] What Does the Point Command Do The Point command is a state dialog command that creates a point in the 3D space according to the following UML statechart diagram [1]. ![CAACreatePointStatechart.jpg \(15193 bytes\)](images/CAACreatePointStatechart.jpg) The dialog is as follows: ![CAACreatePoint1.jpg \(19413 bytes\)](images/CAACreatePoint1.jpg) | Select the Point command. The active state becomes GetPoint, and the dialog box is displayed. You can either indicate a point or use the dialog box.  
---|---  
 Click to indicate a point. The transition loops to GetPoint and creates the point. You can click another point or use the dialog box.  
 Enter values in the dialog box spinners. Clicking Apply create the point whose coordinates were entered and you can again either click to indicate a point or use the dialog box. This is what's shown beside. Clicking OK creates the point and ends the command. Clicking Cancel doesn't create the point and ends the command.  
Indicating a point [2] means clicking on the screen at the desired location with the left mouse key. This is a very handy way, but sometimes it is not accurate enough, and a dialog box in which numerical values can be entered is often needed. The Point command enables both indication and dialog box input. Only the latter is described here. [Top] How to Launch the Point Command See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched [3]. Then, in the window where you run the mkrun command, do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following: 
    * Select **File** ->**New**
    * In the New box, select **CAAGeometry** and click **OK**
    * Select **Insert** ->**Point**
    * Click in the window background to create points, or enter the point coordinates in the dialog box and click OK or Apply.
[Top] Where to Find the Point Command Code The Point command is made of a single class named _CAADegCreatePointCmd_ located in the CAADegGeoCommands.m module of the CAADialogEngine.edu framework: Windows | `InstallRootDirectory\CAADialogEngine.edu\CAADegGeoCommands.m\`  
---|---  
Unix | `InstallRootDirectory/CAADialogEngine.edu/CAADegGeoCommands.m/`  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. [Top] Step-by-Step To create the Point command, there are three steps: # | Step | Where  
---|---|---  
1 | Create the Point Command Class Header File | Header file  
2 | Implement the Statechart Diagram | `BuildGraph` method [4]  
3 | Releasing the Indication Agent and the Dialog Box | Destructor  
[Top] Creating the CreatePoint Command Class Header File The CAADegCreatePointCmd state command class derives from CATStateCommand.
    
    ...
    class CAADegCreatePointCmd : public CATStateCommand
    {
      CmdDeclareResourceFile(CAADegFileCmd,CAADegCreatePointCmd,CATStateCommand);
    
      public :
    
        CAADegCreatePointCmd();
        virtual ~CAADegCreatePointCmd();  
        ...
        virtual void BuildGraph() ; _// Implements the statechart_
    
        CATBoolean  CheckPoint(void * iData); _// Checks if the point can be created_
    
        CATBoolean  CreatePointByIndication(void * iData); 
        CATBoolean  CreatePointByBox       (void * iData);
    
      private :
        CATIndicationAgent * _daIndication; _// Indication agent_
        CAADegPointEditor  * _PointEditor;  _// Dialog box_
    
        void NewPoint(const CATMathPoint &iPoint); _// Action method to create a point_
        ...  
  
---  
This header file includes: 
    * The `CmdDeclareResource` macro states that the resources of the _CAADegCreatePointCmd_ command are located in the CAADegFileCmd.CATNls file. If resources were assigned to the CATStateCommand class, they would be concatenated with the resources for CAADegCreatePointCmd
    * The `BuildGraph` method implements the statechart diagram
    * CheckPoint is a condition method of the transitions that create points from a point indication or a dialog box entry using the action methods `CreatePointByIndication` or `CreatePointByBox` respectively
    * Private data members include the indication agent, the dialog box, and a method called by the action method that actually creates a 3D point in the document.
[Top] Implementing the Statechart Diagram This is done in the command `BuildGraph` method.
    
    void CAADegCreatePointCmd::BuildGraph()
    {
      //1- Creates the indication agent  
      _daIndication = new **CATIndicationAgent**("Indication");
      ...  
  
---  
The indication agent is instantiated. The default projection plane is used; it is a plane parallel to the screen plane  Then, the dialog box is instantiated and built. It is an instance of the _CAADegPointEditor_ class that derives from the _CATDlgDialog_ class and that simply includes a spinner for each coordinate, and three push buttons OK, Apply, and Cancel.
    
    ...
      //2- Creates the dialog box to input xyz 
      
      CATApplicationFrame * pFrame = NULL ;
      CATDialog * pParent = NULL ;
      pFrame = CATApplicationFrame::**GetFrame**() ;
      if ( NULL != pFrame )
      {
           pParent = pFrame->**GetMainWindow**() ;
      }
      _PointEditor = new **CAADegPointEditor**(pParent);
      _PointEditor->**Build**();
      ...  
  
---  
The parent of this dialog box is an invisible dialog object which contains all the windows of the same document. This object is returned by the `GetMainWindow` method on the application frame. Refer to the article entitled "Understanding the Application Frame Layout" [5] for complete details about this object. Dialog boxes should always be instantiated without controls (or other dialog objects). Instantiating these controls in a `Build` method called after the constructor has returned make sure that the control resources will be correctly allocated. The GetPoint state is an instance of the _CATPanelState_ class, dedicated to states associated with a dialog box.
    
    ...
      //3- Creates the state associated with the dialog box and containing the 
      //   Indication Agent
      CATPanelState * stState = new **CATPanelState**(this, "GetPointId", _PointEditor);
      **SetInitialState**(stState);
      stState->**AddDialogAgent**(_daIndication);
    ...  
  
---  
The state is also a _CATCommand_ instance and must be assigned a parent in the command tree structure. This parent is set as `this` in the first constructor argument, that is, as the state dialog command itself. A pointer to the dialog box is passed as the third argument to associate the dialog box with the state. Since the state is explicitly constructed, it must be added as a the command initial state using `SetInitialState`. Usually, this is `GetInitialState` that instantiates and sets the state as the initial state. Then the transition that loops on this state when the end user indicates a point is defined as follows.
    
    ...
      //4-Defines the transition triggered by the Indication Agent
      CATDialogTransition *pFirstTransition = **AddTransition**(
        stState,
        stState,
        **AndCondition**(**IsOutputSetCondition**(_daIndication),
                     **Condition**((ConditionMethod)&CAADegCreatePointCmd::CheckPoint)),
        **Action**((ActionMethod) & CAADegCreatePointCmd::CreatePointByIndication)
    
    );  
  
---  
The `AddTransition` method creates a transition and adds it to the transitions managed by the dialog command. Pointers to the transition's source and target states are the first and second arguments respectively. This self transition goes from/to the same GetPoint state. The transition trigger is defined in the guard condition as the first condition to be checked using the `IsOutputSetCondition` method applied to the indication agent. A second condition uses the `CheckPoint` method. Because we use `AndCondition` to create the guard condition, both condition methods must return True to fire the transition. In this case, the `CreatePointByIndication` action method is executed. The _CATPanelState_ class**** creates automatically transitions depending on the style of the associated Dialog box:
    * An **Ok** transition which fires when the Ok button is selected and whose target state is the NULL state.
    * An **Apply** transition which fires when the Apply button is selected and whose target state is the dialog state itself.
    * A **Cancel** transition which fires when the Cancel button is selected and whose target state is the cancel state.
The Apply and Ok transitions are retrieved from the state and assigned a condition and an action.
    
    ... 
      //5- Completes the Apply transition
      // Sets a condition to the Apply transition
      (stState->**GetApplyTransition**())->**SetCondition**(**Condition**((ConditionMethod)&CAADegCreatePointCmd::CheckPoint));
      // Sets an action to the Apply transition
      (stState->**GetApplyTransition**())->**SetAction**(**Action**((ActionMethod)&CAADegCreatePointCmd::CreatePointByBox));
    
      //6- Completes the Ok transition
      // Sets a condition to the Ok transition
      (stState->**GetOkTransition**())->**SetCondition**(**Condition**((ConditionMethod)&CAADegCreatePointCmd::CheckPoint));
      // Sets an action to the Ok transition
      (stState->**GetOkTransition**())->**SetAction**(**Action**((ActionMethod)&CAADegCreatePointCmd::CreatePointByBox));
       ...
    }  
  
---  
 Don't forget to release the state before getting out of scope.
    
    ... 
      // As the state was created explicitly by "new" instead of the 
      // GetInitialState method, it must be released.
      stState->**Release**();
    }  
  
---  
[Top] Releasing the Indication Agent and the Dialog Box A pointer to the indication agent was created in the command `BuildGraph` method as a data member to be accessed and used in different methods. It should be released when it becomes useless. This can be done in the command destructor, as shown here. This could also be done in the `Cancel` method called just before the destructor. In the same way, the dialog box should be destructed as soon as possible. This is possible using the `RequestDelayedDestruction` method.
    
    CAADegCreatePointCmd::~CAADegCreatePointCmd()
    {
      if (NULL != _daIndication) _daIndication->**RequestDelayedDestruction**();
      daIndication = NULL ;
      if (NULL !=_PointEditor)  _PointEditor->**RequestDelayedDestruction**();
      _PointEditor = NULL ;
      ...  
  
---  
[Top]

* * *

In Short This use case shows the objects involved when a dialog box is used in conjunction with a specific state dedicated to it (the "panel" state): the state dialog command, the statechart and its implementation in the `BuildGraph` method, the "panel" state, and the specific way to assign condition and action methods to transitions triggered when pressing the dialog box push buttons. [Top]

* * *

References [1] | [Describing State Dialog Commands Using UML](../CAADegTechArticles/CAADegUMLDescription.md)  
---|---  
[2] | [Managing Indication](../CAADegTechArticles/CAADegGraph.htm#510000)  
[3] | [The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)  
[4] | [Implementing the Command Statechart Diagram](../CAADegTechArticles/CAADegGraph.md)  
[5] | [Understanding the Application Frame Layout](../CAAAfrTechArticles/CAAAfrLayoutV5.md)  
[Top]  
  
* * *

History Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
