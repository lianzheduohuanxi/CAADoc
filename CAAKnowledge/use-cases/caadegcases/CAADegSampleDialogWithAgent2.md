---
```vbscript
title: "Associating a Dialog Box with a Dialog Agent - 2"
category: "use case"
module: "CAADegUseCases"
tags: ["CAADegHstChartWndDlg", "CAAGeometry", "CAADegHistogramChartWindowCmdDo", "CAADialogEngine", "CAADegHistogramChartWindowCmd", "CAADegEditor1DeselectedNotification", "CAADegEditor1SelectedNotification", "CAADegGeoCommands"]
source_file: "Doc/online/CAADegUseCases/CAADegSampleDialogWithAgent2.htm"
converted: "2026-05-11T17:33:49.642672"
```

---
tags: ["CAADegHstChartWndDlg", "CAAGeometry", "CAADegHistogramChartWindowCmdDo", "CAADialogEngine", "CAADegHistogramChartWindowCmd", "CAADegEditor1DeselectedNotification", "CAADegEditor1SelectedNotification", "CAADegGeoCommands"]
source_file: "Doc/online/CAADegUseCases/CAADegSampleDialogWithAgent2.htm"
converted: "2026-05-11T17:33:49.642672"
3D PLM Enterprise Architecture |  User Interface - Commands |  Associating a Dialog Box with a Dialog Agent - 2 _Using a new notification to value a dialog agent_  

converted: "2026-05-11T17:33:49.642672"
3D PLM Enterprise Architecture |  User Interface - Commands |  Associating a Dialog Box with a Dialog Agent - 2 _Using a new notification to value a dialog agent_
Use Case  

* * *

Abstract This article shows how to use a dialog box to value a dialog agent. The agent is valuated by a notification sent by the Dialog box. For a valuation by an existing notification, those of the _CATDlgDialog_ class, refer to the first part of the article [1]. In this article on the other hand, the notification has been specially created to distinguish the end-user interactions in the Dialog box. 
    * **What You Will Learn With This Use Case**
    * **The CAADegHistogramChartWindowCmd Use Case**
      * What Does CAADegHistogramChartWindowCmd Do
      * How to Launch CAADegHistogramChartWindowCmd
      * Where to Find the CAADegHistogramChartWindowCmd Code
    * **Step-by-Step**
    * **In Short**
    * **References**

* * *

What You Will Learn With This Use Case This use case is intended to show how to use a dialog box associated with a dialog agent in a state dialog command. The dialog box values the dialog agent when the end user clicks a specific editor and any other objects of the dialog box. [Top] The CAADegHistogramChartWindowCmd Use Case CAADegHistogramChartWindowCmd  is a use case of the CAADialogEngine.edu framework that illustrates Dialog and DialogEngine framework capabilities. [Top] What Does CAADegHistogramChartWindowCmdDo The CAADegHistogramChartWindowCmd is a dialog state command enabling you to open a new window [2] to display an histogram chart view of the document.  | The title of this command is "Histogram Chart Window". You find it in the "Chart Window" toolbar of the CAAGeometry document  
---|---  
What You Will Learn With This Use Case This use case is intended to show how to use a dialog box associated with a dialog agent in a state dialog command. The dialog box values the dialog agent when the end user clicks a specific editor and any other objects of the dialog box. [Top] The CAADegHistogramChartWindowCmd Use Case CAADegHistogramChartWindowCmd  is a use case of the CAADialogEngine.edu framework that illustrates Dialog and DialogEngine framework capabilities. [Top] What Does CAADegHistogramChartWindowCmdDo The CAADegHistogramChartWindowCmd is a dialog state command enabling you to open a new window [2] to display an histogram chart view of the document.  | The title of this command is "Histogram Chart Window". You find it in the "Chart Window" toolbar of the CAAGeometry document
 When you launch the "Histogram Chart Window" command, the "Customization of the Histogram Chart Window" dialog box appears. Before clicking OK, the end user can change some default parameters for the new window.    

What You Will Learn With This Use Case This use case is intended to show how to use a dialog box associated with a dialog agent in a state dialog command. The dialog box values the dialog agent when the end user clicks a specific editor and any other objects of the dialog box. [Top] The CAADegHistogramChartWindowCmd Use Case CAADegHistogramChartWindowCmd  is a use case of the CAADialogEngine.edu framework that illustrates Dialog and DialogEngine framework capabilities. [Top] What Does CAADegHistogramChartWindowCmdDo The CAADegHistogramChartWindowCmd is a dialog state command enabling you to open a new window [2] to display an histogram chart view of the document.  | The title of this command is "Histogram Chart Window". You find it in the "Chart Window" toolbar of the CAAGeometry document
When you launch the "Histogram Chart Window" command, the "Customization of the Histogram Chart Window" dialog box appears. Before clicking OK, the end user can change some default parameters for the new window.
 When the end user clicks on the OK button, a new window is created. It contains a 2D viewer with the count of point, line, plane, circle and ellipse in the document.   

When you launch the "Histogram Chart Window" command, the "Customization of the Histogram Chart Window" dialog box appears. Before clicking OK, the end user can change some default parameters for the new window.
When the end user clicks on the OK button, a new window is created. It contains a 2D viewer with the count of point, line, plane, circle and ellipse in the document.
The CAADegHistogramChartWindowCmd command is a state dialog command according to the following UML state chart diagram [3]. ![](images/CAADegHistoChart4.jpg)  

---  
[Top] How to Launch CAADegHistogramChartWindowCmd  See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched [4]. Then, in the window where you run the mkrun command, do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following: 
    * Select **File** ->**New**
    * In the New box, select **CAAGeometry** and click OK 
    * Select **Window** ->**Histogram Chart Window**
    * Click in the **Point 1** editor
    * Click in the **Point 2** editor
[Top] Where to Find the CAADegHistogramChartWindowCmd Code The "Histogram Chart Window" command is made of a three classes:
    * _CAADegHistogramChartWindowCmd_ , the state command
    * _CAADegHstChartWndDlg,_ the Dialog box
    * _CAADegEditor1SelectedNotification_ , The notification sent when the Point.1 editor gets the focus
    * _CAADegEditor1DeselectedNotification_ , The notification sent when the Point.1 editor loses the focus
located in the CAADegGeoCommands.m module of the CAADialogEngine.edu framework: Windows | `InstallRootDirectory\CAADialogEngine.edu\CAADegGeoCommands.m\`  
---|---  
located in the CAADegGeoCommands.m module of the CAADialogEngine.edu framework: Windows | `InstallRootDirectory\CAADialogEngine.edu\CAADegGeoCommands.m\`
Unix | `InstallRootDirectory/CAADialogEngine.edu/CAADegGeoCommands.m/`  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.  [Top] Step-by-Step There are three logical steps in CAADegHistogramChartWindowCmd use case:
    1. Creating the Histogram Chart Window Command
    2. Creating the CAADegEditor1SelectedNotification Notification
    3. Creating the "Customization of the Histogram Chart Window"  Dialog Box

[Top] Creating the Histogram Chart Window Command This step can be divided in three parts:
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.  [Top] Step-by-Step There are three logical steps in CAADegHistogramChartWindowCmd use case:
1. Creating the Histogram Chart Window Command
2. Creating the CAADegEditor1SelectedNotification Notification
3. Creating the "Customization of the Histogram Chart Window"  Dialog Box
    1. Creating the Histogram Chart Window Header File
    2. Implementing the State Chart Diagram
    3. Releasing the Agents and the Dialog Box
    1. Creating the Histogram Chart Window Header File
The _CAADegHistogramChartWindowCmd_  state command class derives from _CATStateCommand_

    ...
3. Releasing the Agents and the Dialog Box
1. Creating the Histogram Chart Window Header File
The _CAADegHistogramChartWindowCmd_  state command class derives from _CATStateCommand_
    class CAADegHistogramChartWindowCmd : public CATStateCommand

    {
        ...
class CAADegHistogramChartWindowCmd : public CATStateCommand
      private :

        CAADegHstChartWndDlg   * _pHstChartWndDlg ;

        CATDialogAgent         * _daEditor1Selected ;

    };  

---  
This header file includes:
       * `_pHstChartWndDlg` is the pointer on the "Customization of the Histogram Chart Window"  Dialog Box. 
       * `_daEditor1Selected` is the dialog agent to associate with the dialog box. This is a _CATDialogAgent_ class instance.
This header file includes:
    2. Implementing the State Chart Diagram
It is done in the command `BuildGraph` method [5].

    void CAADegHistogramChartWindowCmd::BuildGraph()

    {
2. Implementing the State Chart Diagram
It is done in the command `BuildGraph` method [5].
void CAADegHistogramChartWindowCmd::BuildGraph()
       a/ Creating the Dialog Box
       b/ Creating the Dialog Agent
       c/ Creating the State    
       d/ Creating the Transition

    }  

---  
c/ Creating the State
d/ Creating the Transition
a/  Creating the Dialog Box

    CATApplicationFrame * pFrame = NULL ;
      CATDialog * pParent = NULL ;
      pFrame = CATApplicationFrame::**GetFrame**() ;
      if ( NULL != pFrame )

      {
CATApplicationFrame * pFrame = NULL ;
CATDialog * pParent = NULL ;
pFrame = CATApplicationFrame::**GetFrame**() ;
if ( NULL != pFrame )
           pParent = pFrame->**GetMainWindow**() ;

      }
      ...
```vbscript
if ( NULL != pFrame )
pParent = pFrame->**GetMainWindow**() ;
      _pHstChartWndDlg = new **CAADegHstChartWndDlg**(pParent);
      _pHstChartWndDlg->**Build**();  

```

---  
_pHstChartWndDlg = new **CAADegHstChartWndDlg**(pParent);
_pHstChartWndDlg->**Build**();
The dialog box is instantiated and built. It is an instance of the _CAADegHstChartWndDlg_**** class that derives from the _CATDlgDialog_ class and that simply includes some dialog objects such as two _CATDlgEditor_ class instances and two push buttons OK and Cancel. Dialog boxes should always be instantiated without controls (or other dialog objects). Instantiating these controls in a ` Build` method called after the constructor has returned make sure that the control resources will be correctly allocated. The parent of this dialog box is an invisible dialog object which contains all the windows of the same document. This object is returned by the `GetMainWindow` method on the application frame. Refer to the article entitled "Understanding the Application Frame Layout" [6] for complete details about this object. b/  Creating the Dialog AgentThe dialog agent is created as following:

    ...
The dialog box is instantiated and built. It is an instance of the _CAADegHstChartWndDlg_**** class that derives from the _CATDlgDialog_ class and that simply includes some dialog objects such as two _CATDlgEditor_ class instances and two push buttons OK and Cancel. Dialog boxes should always be instantiated without controls (or other dialog objects). Instantiating these controls in a ` Build` method called after the constructor has returned make sure that the control resources will be correctly allocated. The parent of this dialog box is an invisible dialog object which contains all the windows of the same document. This object is returned by the `GetMainWindow` method on the application frame. Refer to the article entitled "Understanding the Application Frame Layout" [6] for complete details about this object. b/  Creating the Dialog AgentThe dialog agent is created as following:
         _daEditor1Selected = new **CATDialogAgent**("Editor1SelectedId");	
         _daEditor1Selected->**SetBehavior**(**CATDlgEngRepeat**);
         _daEditor1Selected->**AcceptOnNotify**(_pHstChartWndDlg,"

                                     **CAADegEditor1SelectedNotification** ");
    ...  

---  
The character string `Editor1SelectedId` defined as the argument of the _CATDialogAgent_ constructor is the dialog agent identifier. This identifier can be used to assign undo/redo prompts replacing the Undo and Redo items in the Edit menu.  The dialog agent behavior is set to `CATDlgEngRepeat` to enable the dialog agent to be valued more than once without being reiniatilized and nevertheless remain usable to trigger a transition using the `IsLastModifiedAgentCondition` method. The `AcceptOnNotify` method enables the dialog agent to be valued whenever the dialog box sends a _CAADegEditor1SelectedNotification_**** notification.  c/  Creating the StateThe `PanelState` and the `PanelState1` (not described here) states are _CATPanelState_ instances. 

    ...   
The character string `Editor1SelectedId` defined as the argument of the _CATDialogAgent_ constructor is the dialog agent identifier. This identifier can be used to assign undo/redo prompts replacing the Undo and Redo items in the Edit menu.  The dialog agent behavior is set to `CATDlgEngRepeat` to enable the dialog agent to be valued more than once without being reiniatilized and nevertheless remain usable to trigger a transition using the `IsLastModifiedAgentCondition` method. The `AcceptOnNotify` method enables the dialog agent to be valued whenever the dialog box sends a _CAADegEditor1SelectedNotification_**** notification.  c/  Creating the StateThe `PanelState` and the `PanelState1` (not described here) states are _CATPanelState_ instances.
         CATPanelState * stPanelState = new **CATPanelState** (this, "stPanelStateId",
                                                                   _pHstChartWndDlg);

         **SetInitialState**(stPanelState);
CATPanelState * stPanelState = new **CATPanelState** (this, "stPanelStateId",
_pHstChartWndDlg);
         stPanelState->**AddDialogAgent**(_daEditor1Selected);

    ...  

---  
stPanelState->**AddDialogAgent**(_daEditor1Selected);
The state is also a _CATCommand_ instance and must be assigned a parent in the command tree structure. This parent is set as `this` in the first constructor argument, that is, as the state dialog command itself. A pointer to the dialog box is passed as the third argument to associate the dialog box with the state. Since the state is explicitly constructed, it must be added as a the command initial state using `SetInitialState`. For the next states ( such as `PanelState1` ) the method is `AddDialogState.` Caution: A panel state pointer must be released when it becomes useless (In general at the end of the `BuildGraph` method) [7]. d/  Creating the Transition Only the transition which used the `_daEditor1Selected` agent is explained. Refer to the C++ code for details.

    CATDialogTransition *pTransition1 = AddTransition

         (
The state is also a _CATCommand_ instance and must be assigned a parent in the command tree structure. This parent is set as `this` in the first constructor argument, that is, as the state dialog command itself. A pointer to the dialog box is passed as the third argument to associate the dialog box with the state. Since the state is explicitly constructed, it must be added as a the command initial state using `SetInitialState`. For the next states ( such as `PanelState1` ) the method is `AddDialogState.` Caution: A panel state pointer must be released when it becomes useless (In general at the end of the `BuildGraph` method) [7]. d/  Creating the Transition Only the transition which used the `_daEditor1Selected` agent is explained. Refer to the C++ code for details.
CATDialogTransition *pTransition1 = AddTransition
            stPanelState,
            stPanelState1,

            **IsLastModifiedAgentCondition**(_daEditor1Selected),
CATDialogTransition *pTransition1 = AddTransition
stPanelState,
stPanelState1,
            Action( (ActionMethod) & CAADegHistogramChartWindowCmd::Editor1Selected)

         ) ;
         ...  

---  
```vbscript
Action( (ActionMethod) & CAADegHistogramChartWindowCmd::Editor1Selected)
The `AddTransition` method creates a transition and adds it to the transitions managed by the dialog command. Pointers to the transition's source and target states are the first and second arguments respectively. This transition goes from the `PanelState` state to the `PanelState1` state (not explained). The transition trigger is defined in the guard condition as the condition to be checked using the `IsLastModifiedAgentCondition` method applied to the dialog agent. When the dialog agent prevalue is modified, the transition fire. In this case, the ` Editor1Selected` action method is executed. (method without interest for the use case, so not explained)
    3. Releasing the Agents and the Dialog Box
A pointer to the dialog agent was created in the command `BuildGraph` method as a data member to be accessed and used in different methods. It should be released when it becomes useless. This can be done in the command destructor, as shown here. This could also be done in the `Cancel` method called just before the destructor. In the same way, the dialog box should be destructed by using the `RequestDelayedDestruction` method.

```

    ...
The `AddTransition` method creates a transition and adds it to the transitions managed by the dialog command. Pointers to the transition's source and target states are the first and second arguments respectively. This transition goes from the `PanelState` state to the `PanelState1` state (not explained). The transition trigger is defined in the guard condition as the condition to be checked using the `IsLastModifiedAgentCondition` method applied to the dialog agent. When the dialog agent prevalue is modified, the transition fire. In this case, the ` Editor1Selected` action method is executed. (method without interest for the use case, so not explained)
3. Releasing the Agents and the Dialog Box
A pointer to the dialog agent was created in the command `BuildGraph` method as a data member to be accessed and used in different methods. It should be released when it becomes useless. This can be done in the command destructor, as shown here. This could also be done in the `Cancel` method called just before the destructor. In the same way, the dialog box should be destructed by using the `RequestDelayedDestruction` method.
    CAADegHistogramChartWindowCmd::~CAADegHistogramChartWindowCmd()

    {
A pointer to the dialog agent was created in the command `BuildGraph` method as a data member to be accessed and used in different methods. It should be released when it becomes useless. This can be done in the command destructor, as shown here. This could also be done in the `Cancel` method called just before the destructor. In the same way, the dialog box should be destructed by using the `RequestDelayedDestruction` method.
CAADegHistogramChartWindowCmd::~CAADegHistogramChartWindowCmd()
      if ( NULL != _pHstChartWndDlg ) 

      {
CAADegHistogramChartWindowCmd::~CAADegHistogramChartWindowCmd()
if ( NULL != _pHstChartWndDlg )
         _pHstChartWndDlg->**RequestDelayedDestruction**() ;
         _pHstChartWndDlg = NULL ;

      }

_pHstChartWndDlg->**RequestDelayedDestruction**() ;
_pHstChartWndDlg = NULL ;
      if ( NULL != _daEditor1Selected )

      {
_pHstChartWndDlg = NULL ;
if ( NULL != _daEditor1Selected )
         _daEditor1Selected->**RequestDelayedDestruction**();
         _daEditor1Selected = NULL ;

      }
      ...
    }
    ...  

---  
[Top] Creating the CAADegEditor1SelectedNotification Notification This step can be divided in two parts:
    1. Creating the Notification Header file
1. Creating the Notification Header file
The _CAADegEditor1SelectedNotification_ class derives from the _CATNotification_ class.

    #include "CATNotification.h"   
1. Creating the Notification Header file
The _CAADegEditor1SelectedNotification_ class derives from the _CATNotification_ class.
    class CAADegEditor1SelectedNotification : public CATNotification

    {
      **CATDeclareClass** ;

class CAADegEditor1SelectedNotification : public CATNotification
      public:
        CAADegEditor1SelectedNotification();
        virtual ~CAADegEditor1SelectedNotification();

      private:
        CAADegEditor1SelectedNotification(const CAADegEditor1SelectedNotification 

                                                  &iObjectToCopy);
    };  

---  
```vbscript
CAADegEditor1SelectedNotification(const CAADegEditor1SelectedNotification
The `CATDeclareClass` macro declares that the `CAADegEditor1SelectedNotification` class belongs to a component.
    2. Creating the Notification source file
```

    #include "CAADegEditor1SelectedNotification.h"

    **CATImplementClass**(CAADegEditor1SelectedNotification,Implementation,
                              **CATNotification** ,CATNull);

    CAADegEditor1SelectedNotification::CAADegEditor1SelectedNotification()
                            : CATNotification(**CATNotificationDeleteOn**)
    {
    }

    CAADegEditor1SelectedNotification::~CAADegEditor1SelectedNotification()
    {
    }  

---  
       * The `CATImplementClass` macro declares that the `CAADegEditor1SelectedNotification` class is a implementation class, thanks to the `Implementation` keyword, and that it extends the component whose main class is `CATNotification`. The forth parameter must always be set to CATNull.
       * The _CATNotification_ base class constructor is called with the `CATNotificationDeleteOn` parameter to state that we want this notification to be automatically deleted at the end of the next transaction, that is, as soon as the dialog between sending and receiving commands is completed. 
       * The class destructor is empty.  [Top] Creating the "Customization of the Histogram Chart Window"  Dialog Box This step can be divided in three parts:
    1. Creating the Dialog box Header File
    2. Creating the Build method
    3. Creating the Callback method
    1. Creating the Dialog box Header File

    ...
2. Creating the Build method
3. Creating the Callback method
1. Creating the Dialog box Header File
    class CAADegHstChartWndDlg : public CATDlgDialog

    {
      ...
class CAADegHstChartWndDlg : public CATDlgDialog
      public :
        CAADegHstChartWndDlg(CATDialog *iParent);
        virtual ~CAADegHstChartWndDlg(); 

        void **Build**();
      private : 

        ...
void **Build**();
private :
        void **Editor1Selected** (CATCommand        * iPublisher, 
    		          CATNotification      * iNotification, 
    		          CATCommandClientData   iUsefulData);

        ...
    };  

---  
CATCommandClientData   iUsefulData);
As usual the Dialog box has a `Build` method to construct all the dialog objects and arrange them. The `Editor1Selected` method is a callback method called when the end user clicks in the first editor. This editor is not a data member once it is not used in the different methods of the class.
    2. Creating the Build method
As usual the `Build` method constructs the dialog objects inside the dialog box. `pEditor1` is a _CATDlgEditor_ class instance. The` ``Editor1Selected` callback method is declared to be executed when the editor will send a `GetEditFocusInNotification` notification. 

    ...
As usual the Dialog box has a `Build` method to construct all the dialog objects and arrange them. The `Editor1Selected` method is a callback method called when the end user clicks in the first editor. This editor is not a data member once it is not used in the different methods of the class.
2. Creating the Build method
As usual the `Build` method constructs the dialog objects inside the dialog box. `pEditor1` is a _CATDlgEditor_ class instance. The` ``Editor1Selected` callback method is declared to be executed when the editor will send a `GetEditFocusInNotification` notification.
    void CAADegHstChartWndDlg::Build()

    {
      ...
void CAADegHstChartWndDlg::Build()
      CATDlgEditor * pEditor1 = new CATDlgEditor(pFrameMaxHeight,"Editor1Id" );

      ...
void CAADegHstChartWndDlg::Build()
CATDlgEditor * pEditor1 = new CATDlgEditor(pFrameMaxHeight,"Editor1Id" );
      AddAnalyseNotificationCB(pEditor1, pEditor1->**GetEditFocusInNotification**(),
                    (CATCommandMethod)&CAADegHstChartWndDlg::Editor1Selected,
                                NULL);

      ...
    }  

---  
NULL);
    3. Creating the Callback method
The Dialog box must send a `CAADegEditor1SelectedNotification` notification. The Send/Receive mechanism is used [8].

    ...
3. Creating the Callback method
The Dialog box must send a `CAADegEditor1SelectedNotification` notification. The Send/Receive mechanism is used [8].
    void CAADegHstChartWndDlg::Editor1Selected    (CATCommand           * iPublisher ,
                                        CATNotification      * iNotification,
                                        CATCommandClientData   iUsefulData)

    {
void CAADegHstChartWndDlg::Editor1Selected    (CATCommand           * iPublisher ,
CATNotification      * iNotification,
CATCommandClientData   iUsefulData)
       CAADegEditor1SelectedNotification * pEdt1Notification = NULL ;
       pEdt1Notification = new **CAADegEditor1SelectedNotification**();     

       **SendNotification**(**GetFather**(),pEdt1Notification);
CATCommandClientData   iUsefulData)
CAADegEditor1SelectedNotification * pEdt1Notification = NULL ;
pEdt1Notification = new **CAADegEditor1SelectedNotification**();
       pEdt1Notification = NULL ;

    }
    ...  

---  
The notification, `pEdt1Notification`, is sent by the `SendNotification` method to the parent's command. Once the current command, those seen by the focus manager, is ` CAADegHistogramChartWindowCmd`, it will be awaken and its agents concerned by this notification will be valuated [9]. Once the _CAADegEditor1SelectedNotification_ instance is created with the `CATNotificationDeleteOn` state, see the Creating the CAADegEditor1SelectedNotification Notification section, you do not have to release it.  [Top]

* * *

In Short This use case shows how: 
    * To create a notification for the Send/Receive protocol,
    * To valuate a dialog agent by this notification.
[Top]

* * *

References [1] | [Associating a Dialog Box with a Dialog Agent - 1](CAADegSampleDialogWithAgent.md)  
---|---  
[2] | [Creating a Document's Window -1](../CAAAfrUseCases/CAAAfrSampleCustomWindow1.md)  
[3] | [Describing State Dialog Commands Using UML](../CAADegTechArticles/CAADegUMLDescription.md)  
[4] | [The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)  
[5] | [Implementing the Command Statechart Diagram](../CAADegTechArticles/CAADegGraph.md)  
[6] | [Understanding the Application Frame Layout](../CAAAfrTechArticles/CAAAfrLayoutV5.md)  
[7] | [Associating a Dialog Box with a State](CAADegSampleDialogWithPanelState.md)  
[8] | [The Send/Receive Communication Protocol](../CAASysTechArticles/CAASysSendReceive.md)  
[9] | [The CAA Command Model ](../CAADegTechArticles/CAADegCommandModel.md)  
[Top]  

* * *

History Version: **1** [Fev 2003] | Document created  
---|---  
[Top]  

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
