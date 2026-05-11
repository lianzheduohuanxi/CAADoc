---
```vbscript
title: "Editing Object During a Command"
category: "use case"
module: "CAADegUseCases"
tags: ["CAAPriPrtCfgAddin", "CAAPriEditSketchCmd", "CAAPriEditSketch", "CAAPriPrtCfgAdn", "CATISpecObject", "CATIBuildPath", "CATIWorkbenchAddin", "CATISketch", "CAAPriEditSketchNotification", "CATIPrtCfgAddin", "CAAPartInterfaces", "CAAPriCommands", "CAAPriEditSketchDlg", "CATIPad"]
source_file: "Doc/online/CAADegUseCases/CAADegSampleCATEditAgent.htm"
converted: "2026-05-11T17:33:49.575815"
```

---
tags: ["CAAPriPrtCfgAddin", "CAAPriEditSketchCmd", "CAAPriEditSketch", "CAAPriPrtCfgAdn", "CATISpecObject", "CATIBuildPath", "CATIWorkbenchAddin", "CATISketch", "CAAPriEditSketchNotification", "CATIPrtCfgAddin", "CAAPartInterfaces", "CAAPriCommands", "CAAPriEditSketchDlg", "CATIPad"]
source_file: "Doc/online/CAADegUseCases/CAADegSampleCATEditAgent.htm"
converted: "2026-05-11T17:33:49.575815"
3D PLM Enterprise Architecture |  User Interfaces - Commands |  Editing Object During a Command How to stack a workbench using CATEditAgent class  

converted: "2026-05-11T17:33:49.575815"
3D PLM Enterprise Architecture |  User Interfaces - Commands |  Editing Object During a Command How to stack a workbench using CATEditAgent class
Use Case  

* * *

Abstract This article shows how to use the _CATEditAgent_ class to stack a workbench during a state command. In particular, it details how to edit a sketch during a Part command. 
    * **What You Will Learn With This Use Case**
    * **The CAAPriEditSketch Use Case**
      * What Does CAAPriEditSketch Do
      * How to Launch CAAPriEditSketch
      * Where to Find the CAAPriEditSketch Code
    * **Step-by-Step**
    * **In Short**
    * **References**

* * *

What You Will Learn With This Use Case This use case is intended to show you how to use the _CATEditAgent_ class to stack a workbench during a state command in order to edit an object. Activate this agent launches the specified workbench, and the end user comes back to the interrupted command by exiting the stacked workbench. After the edition, the edited object is set in the selection set (_CATCSO_). This use case explains how to:
    * Create a _CATEditAgent_ ,
    * Specify the workbench,
    * Specify and manage the object to edit, 
    * Specify available commands in the stacked workbench thanks to the _CATStackableCommandSet_ class.
[Top] The CAAPriEditSketch Use Case CAAPriEditSketch is a use case of the CAAPartInterfaces.edu framework that illustrates DialogEngine and ApplicationFrame framework capabilities. [Top] What Does CAAPriEditSketch Do CAAPriEditSketch is a use case which edits a Pad. This command is integrated in a Part Design add-in.  _Fig.1: The Part Design Add-in_ 
---  
This add-in contains one toolbar (the "Frame tools" toolbar) which has one command the "Part Modification" command ![](images/CAADegCATEditAgentIcon.jpg). This command enables the end user to edit a pad which has a sketch as profile. _Fig.2: The Part Modification Command_ ![](images/CAADegEditAgentDlg.jpg)  
---  
This add-in contains one toolbar (the "Frame tools" toolbar) which has one command the "Part Modification" command ![](images/CAADegCATEditAgentIcon.jpg). This command enables the end user to edit a pad which has a sketch as profile. _Fig.2: The Part Modification Command_ ![](images/CAADegEditAgentDlg.jpg)
The "Pad Modification" command ( ![](images/CAADegCATEditAgentIcon.jpg) ) launches the "Pad Modification" dialog box. This dialog object contains the sketch icon (![](images/CAADegEditAgentSketchIcon.jpg)) to edit the profile of the selected Pad. The name of the profile is displayed just beside the sketch icon. (here is it Sketch.1). The use case explains how the state command is awaked when the end user clicks the sketch icon, and how the Sketcher workbench can be launched.  When the sketch icon  is pushed, the Sketcher workbench is launched. Only a set of commands are available.  _Fig.3: The Sketcher Workbench_ ![](images/CAADegEditAgentStack.jpg)  

---  
This add-in contains one toolbar (the "Frame tools" toolbar) which has one command the "Part Modification" command ![](images/CAADegCATEditAgentIcon.jpg). This command enables the end user to edit a pad which has a sketch as profile. _Fig.2: The Part Modification Command_ ![](images/CAADegEditAgentDlg.jpg)
The "Pad Modification" command ( ![](images/CAADegCATEditAgentIcon.jpg) ) launches the "Pad Modification" dialog box. This dialog object contains the sketch icon (![](images/CAADegEditAgentSketchIcon.jpg)) to edit the profile of the selected Pad. The name of the profile is displayed just beside the sketch icon. (here is it Sketch.1). The use case explains how the state command is awaked when the end user clicks the sketch icon, and how the Sketcher workbench can be launched.  When the sketch icon  is pushed, the Sketcher workbench is launched. Only a set of commands are available.  _Fig.3: The Sketcher Workbench_ ![](images/CAADegEditAgentStack.jpg)
The Sketcher workbench is active until the end user clicks the exit ( ![](images/CAADegEditAgentExitIcon.jpg)) command. The sketch associated with the Pad can be modified. The available commands are some global commands, such as Exit, Center Graph, Print ..., but only three specific commands to the Sketcher workbench: 

    * ![](images/CAADegEditAgentSktIcon1.jpg)  , Constraint 
    * ![](images/CAADegEditAgentSktIcon2.jpg), Auto Constraint
    * ![](images/CAADegEditAgentSktIcon3.jpg), Animate Constraint
The "Part Modification" command is a state command which uses the _CATEditAgent_. Its UML statechart diagram [1] is the following: _Fig.4: The UML state chart for the Part Modification Command_ ![](images/CAADegCATEditAgentUML.jpg)  
---  
[Top] How to Launch CAAPriEditSketch To launch CAAPriEditSketch , you will need to set up the build time environment, then compile CAAPriEditSketch along with its prerequisites, set up the run time environment, and then execute the use case [2]. But just before launching the execution, edit the CAAPartInterfaces.edu.dico interface dictionary file located in the dictionary directory of the CAAPartInterfaces.edu framework: Windows | `InstallRootDirectory\``CAAPartInterfaces.edu\CNext\code\dictionary\`  
---|---  
The "Part Modification" command is a state command which uses the _CATEditAgent_. Its UML statechart diagram [1] is the following: _Fig.4: The UML state chart for the Part Modification Command_ ![](images/CAADegCATEditAgentUML.jpg)
UNIX | `InstallRootDirectory/``CAAPartInterfaces.edu/CNext/code/dictionary/`  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. In this file, remove the "**#** " character before the two following lines:

    ...
    #CAAPriPrtCfgAddin     CATIPrtCfgAddin             libCAAPriPrtCfgAddin
    #CAAPriPrtCfgAddin     CATIWorkbenchAddin          libCAAPriPrtCfgAddin
    ...  

---  
Then, in the window where you run the mkrun command, do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following:
    * On the **File** menu, click **Open**
    * **File Selection** Dialog box select **CAAPriEditSketch.CATPart**   and click **Open**
    * On the **Tools** menu, click **Pad Modification...**
    * Select the green Pad
    * In the **Pad****Modification** Dialog box click ![](images/CAADegEditAgentSketchIcon.jpg)
    * Modify the sketch
    * click ![](images/CAADegEditAgentExitIcon.jpg)
    * click **OK** in the **Pad Modification** dialog box
  [Top] Where to Find the CAAPriEditSketch Code The CAAPriEditSketch use case is made of several classes located 
    * In the **CAAPriCommands**.m module of the CAAPartInterfaces.edu framework:
      * _CAAPriEditSketchCmd_ : The state command to modify a Pad. This command uses the _CATEditAgent_ class to edit the profile of the selected Pad.
      * _CAAPriEditSketchDlg_ : The dialog box associated with the _CAAPriEditSketchCmd_ command.
      * _CAAPriEditSketchNotification_ : The notification class to inform the _CAAPriEditSketchCmd_ command that the sketch icon has been pushed.
Windows | `InstallRootDirectory\CAAPartInterfaces.edu\CAAPriCommands.m\`  
---|---  
Windows | `InstallRootDirectory\CAAPartInterfaces.edu\CAAPriCommands.m\`
Unix | `InstallRootDirectory/CAAPartInterfaces.edu/CAAPriCommands.m/`  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed

    * In the **CAAPriPrtCfgAddin**.m module of the CAAPartInterfaces.edu framework
      * _CAAPriPrtCfgAdn_ : The implementation class of the _CATIPrtCfgAddin_ interface. Refer to the use case [3] for details.
Unix | `InstallRootDirectory/CAAPartInterfaces.edu/CAAPriCommands.m/`
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed
Windows | `InstallRootDirectory\CAAPartInterfaces.edu\CAAPriPrtCfgAddin.m\`  

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed
Windows | `InstallRootDirectory\CAAPartInterfaces.edu\CAAPriPrtCfgAddin.m\`
Unix | `InstallRootDirectory/CAAPartInterfaces.edu/CAAPriPrtCfgAddin.m/`  
where `InstallRootDirectory` is the directory where the CAA CD-ROM

[Top] Step-by-Step There are five logical steps in CAAPriEditSketch:
Windows | `InstallRootDirectory\CAAPartInterfaces.edu\CAAPriPrtCfgAddin.m\`
Unix | `InstallRootDirectory/CAAPartInterfaces.edu/CAAPriPrtCfgAddin.m/`
where `InstallRootDirectory` is the directory where the CAA CD-ROM
    1. Creating the Edit Agent 
    2. Creating Agent to Trigger the Sketcher Workbench Activation
    3. Creating States
    4. Creating Transitions
    5. Providing the Object to Edit

[Top] Creating the Edit Agent  The edit agent is a dialog agent created as usual in the `BuildGraph` method [4] of a state command.

    ...
4. Creating Transitions
5. Providing the Object to Edit
       _pEditAgent = new CATEditAgent("EditAgentId");

    ...  

---  
    * `_pEditAgent,` a data member of the _CAAPriEditSketchCmd_ class, is a _CATEditAgent_ class instance . It is created in the `BuildGraph` method, and released in the class destructor thanks to the `RequestDelayedDestruction` method. 
    * `EditAgentId` is the agent identifier. This name is used to retrieve the undo/redo titles in the command resource file. This file is located in the CNext/resources/msgcatalog directory of the CAAPartInterfaces.edu framework.  
Once the edit agent is created, you have to specify the following information:
    * The dialog box associated with the state command,
    * The name of the workbench to launch,
    * The list of available commands,
    * The name of the method which returns the object to edit.
All these methods can be called outside the `BuildGraph` method, and can be called several times once the edit agent is created. There are information used each time the edit agent is activated. 
    * ``The dialog box associated with the state command

    ...
       _pEditAgent->**SetPanel**(_pDialogBox);
    ...  

---  
`_pDialogBox` is the _CAAPriEditSketchDlg_ class instance pointer associated with the _CAAPriEditSketchCmd_ class. It is the "Pad modification" dialog box Fig.2 . When the stacked workbench is launched, the edit agent disables the sensitivity of this dialog box. The `SetPanel` method enables you to specify to the edit agent the dialog box pointer. However hiding the dialog box is of your responsibility. See the Creating Transitions section. 
    * The name of the workbench to launch
The name of the workbench should be set with the `SetWorkbench` method. But the Sketcher is a specific case because it has only one workbench, so the UI activation [5] of the Sketch launches the Sketcher workbench. It is not necessary to specify this information.
    * The list of available commands

    ...
The name of the workbench should be set with the `SetWorkbench` method. But the Sketcher is a specific case because it has only one workbench, so the UI activation [5] of the Sketch launches the Sketcher workbench. It is not necessary to specify this information.
           CATStackableCommandSet * pCommandSet = new **CATStackableCommandSet**();
            pCommandSet->**AddCommand**("2DConstraint");
            pCommandSet->AddCommand("2DAutoCst");
            pCommandSet->AddCommand("2DAnimateCst");

            _pEditAgent->**SetCommandSet**(pCommandSet);
            pCommandSet->Release();
            pCommandSet = NULL ;

    ...  

---  
pCommandSet->Release();
pCommandSet = NULL ;
The _CATStackableCommandSet_ class is a set of _CATCommandHeader_ class instance identifiers. The default constructor creates a non-empty list of commands: Hide/Show, Exit, ...... You should add the available commands of the workbench.  The `2DConstraint`, `2DAutoCst` and `2DAnimateCst` (Fig.3) are commands of the Sketcher workbench. To be exact, they are identifiers of _CATCommandHeader_ class instances. Refer to "How to (Re-)Use Command Header Identifiers" section of the "The Command Headers" technical article [6] to retrieve the name of identifiers.   `pCommandSet` must be released, since the `SetCommandSet` method addref's the class pointer.

    * The name of the method which returns the object to edit

    ...
       _pEditAgent->**SetElementProvider**(this, 
                            (**CATEditAgent::ElementProvider**)&CAAPriEditSketchCmd::ProvideProfileToEdit);
    ...  

---  
With the `SetElementProvider` method, you specify which is the method to call, and on which object this method should be called. Here the object is `this`, the _CAAPriEditSketchCmd_ class instance pointer itself. The `ProvideProfileToEdit` method is explained in the Providing the Object to Edit section.  [Top] Creating Agent to Trigger the Sketcher Workbench Activation You are always in the `BuildGraph` method of the _CAAPriEditSketchCmd_ state command.

    ...
With the `SetElementProvider` method, you specify which is the method to call, and on which object this method should be called. Here the object is `this`, the _CAAPriEditSketchCmd_ class instance pointer itself. The `ProvideProfileToEdit` method is explained in the Providing the Object to Edit section.  [Top] Creating Agent to Trigger the Sketcher Workbench Activation You are always in the `BuildGraph` method of the _CAAPriEditSketchCmd_ state command.
            _pTriggerAgent = new CATDialogAgent("TriggerAgentid");
            _pTriggerAgent->**AcceptOnNotify**(_pDialogBox,"CAAPriEditSketchNotification");

    ...  

---  
`_pTriggerAgent,` a data member of the _CAAPriEditSketchCmd_ class, is a _CATDialogAgent_ class instance . It is created in the `BuildGraph` method, and released in the class destructor thanks to the `RequestDelayedDestruction` method.  `TriggerAgentid` is the agent identifier. This name is used to retrieve the undo/redo titles in the command resource file. This file is located in the CNext/resources/msgcatalog directory of the CAAPartInterfaces.edu framework.  This agent is valuated when the _CAAPriEditSketchDlg_ dialog box sends a _CAAPriEditSketchNotification_ notification.  This agent is important as it is explained in the next sections.  [Top] Creating States After the agent creations, the second step of a `BuildGraph` method is to create the states. The Fig.4 shows the UML diagram of the _CAAPriEditSketchCmd_ state command. There are two important states:
    * `DialogState`: the state to click OK, Cancel to finish the command or click the Sketch icon to edit the profile. 
    * EditSkethState: the state to activate the edit agent
The first one, InputPadState, which enables the end user to select a Pad, is outside the scope of this use case and therefore, not explained. DialogState

    ...
The first one, InputPadState, which enables the end user to select a Pad, is outside the scope of this use case and therefore, not explained. DialogState
            CATPanelState * pDialogState = new **CATPanelState**(this,"**DialogStateId** ",_pDialogBox);
            if ( NULL != pDialogState )

            {
               **AddDialogState**(pDialogState);
CATPanelState * pDialogState = new **CATPanelState**(this,"**DialogStateId** ",_pDialogBox);
if ( NULL != pDialogState )
               pDialogState->**AddDialogAgent**(**_pTriggerAgent**); 

            }
    ...  

---  
The `DialogStateId` state is a _CATPanelState_ class. This class creates agents to react to the end user action on Ok and Cancel buttons of the dialog box given as argument. Refer to the specific article to understand this class [7]. On this state, `_pTriggerAgent` has been added. `pDialogState` must be released at the end of the `BuildGraph` method. EditSketchState

    ...
The `DialogStateId` state is a _CATPanelState_ class. This class creates agents to react to the end user action on Ok and Cancel buttons of the dialog box given as argument. Refer to the specific article to understand this class [7]. On this state, `_pTriggerAgent` has been added. `pDialogState` must be released at the end of the `BuildGraph` method. EditSketchState
            CATDialogState * pEditSketchState = **AddDialogState**("**EditSketchStateId** ");
            if ( NULL != pEditSketchState )

            {
CATDialogState * pEditSketchState = **AddDialogState**("**EditSketchStateId** ");
if ( NULL != pEditSketchState )
               pEditSketchState->**AddDialogAgent**(**_pEditAgent**);

            }
    ...  

---  
The `EditSketchStateId `is a simple _CATDialogState_ class created by the `AddDialogState` method. The only one agent associated with this state is `_pEditAgent` the edit agent.** **`pEditSketchState` will be automatically released at the end of the command. **![](../CAAIcons/images/warning.gif)**The _CATEditAgent_ dialog agent is itself a _CATStateCommand_ class. A state command used as agent must always be the unique agent of a state.  It is the reason for which the `_pTriggerAgent` is important. It enables to activate the `EditSketchState` state, since it will be not possible to associate with the `DialogState` state the `_pEditAgent` agent.  [Top] Creating Transitions The last step of a `BuildGraph` method is to create transitions. There are the following transitions Fig.4:
    * From DialogState ` ` to final state:  They are managed by the _CATPanelState_ class and not by the `BuildGraph` method of the _CAAPriEditSketchCmd_ class _._ [7]
    * From `InputPadState` to `DialogState`: Out of the scope of this use case, therefore not detailed.
    * From DialogState to**** EditSketchState: when the Sketch icon is pushed
    * From EditSketchState to DialogState: when the stacked workbench is closed.
From DialogState to**** EditSketchState

    ...
From DialogState to**** EditSketchState
               CATDialogTransition * pEditSketchTransition = AddTransition(pDialogState,pEditSketchState,
                        IsOutputSetCondition(_pTriggerAgent),
                        Action((ActionMethod) & CAAPriEditSketchCmd::**TriggerEditSketch**));   

    ...  

---  
    * `pEditSketchTransition` comes from the  `DialogState`  state to the `EditSketchState `state. This transition is triggered as soon as the sketch icon is pushed, in other words when a _CAAPriEditSketchNotification_ notification is sent by the _CAAPriEditSketchDlg_ dialog box.
    * The `pEditSketchTransition` transition is managed by the state command, it will be automatically released at the end of the command.
    * The `TriggerEditSketch `method is called just before the edit agent activation. 

    ...
    CATBoolean CAAPriEditSketchCmd::TriggerEditSketch(void *iDummy)
    {
CATBoolean CAAPriEditSketchCmd::TriggerEditSketch(void *iDummy)
          _pDialogBox->SetVisibility(**CATDlgHide**) ;

    ...
CATBoolean CAAPriEditSketchCmd::TriggerEditSketch(void *iDummy)
_pDialogBox->SetVisibility(**CATDlgHide**) ;
          _pTriggerAgent->**InitializeAcquisition**();

    ...  

---  
`_pDialogBox,` the _CAAPriEditSketchDlg_ dialog box is hidden, and `_pTriggerAgent` is reinitialized for a next re-usage.  From EditSketchState to DialogState

    ...
               CATDialogTransition * pBackTransition = AddTransition(pEditSketchState,pDialogState,
                        IsOutputSetCondition(_pEditAgent),
                        Action((ActionMethod) & CAAPriEditSketchCmd::**EditSketch**)); 

    ...  

---  
    * `pBackTransition` comes from the `EditSketchState` state to the `DialogState` state. This transition is triggered as soon as the end user clicks the exit button. 
    * The `EditSketch `method is called when the `_pEditAgent`, a state command, reaches the final state. The Sketcher workbench is "unloaded" and the previous workbench becomes the current one again.

    ...
    CATBoolean CAAPriEditSketchCmd::EditSketch(void *iDummy)
    {
CATBoolean CAAPriEditSketchCmd::EditSketch(void *iDummy)
           _pDialogBox->SetVisibility(**CATDlgShow**) ;

     ...
CATBoolean CAAPriEditSketchCmd::EditSketch(void *iDummy)
_pDialogBox->SetVisibility(**CATDlgShow**) ;
           _pEditAgent->**InitializeAcquisition**();

    ...  

---  
`_pDialogBox,` the _CAAPriEditSketchDlg_ dialog box is shown, and `_pEditAgent` is reinitialized for a next re-usage. [Top] Providing the Object To Edit The `ProvideProfileToEdit` method is called each time the edit agent is activated. The goal of this method is to provide the object to edit by the edit agent. This object will be set in the selection set (_CATCSO_) when the edit agent will reach the final state. The value returned by this method is released by the edit agent. Once the `ProvideProfileToEdit` method is called, the `GetValue` method of the _CATEditAgent_ class returns it. 

    ...
    CATPathElement * CAAPriEditSketchCmd::**ProvideProfileToEdit**(CATClassId iDummy)
    {
CATPathElement * CAAPriEditSketchCmd::**ProvideProfileToEdit**(CATClassId iDummy)
       CATPathElement * pPathToReturn = NULL ;

       if ( (NULL == GetEditor()) || (NULL == _pFeatureAgent) ) return NULL ;

       CATBaseUnknown * pSelectedElt= _pFeatureAgent->**GetElementValue**();

       CATISpecObject * pISpecObjectOnProfile = NULL ;
       HRESULT rc = **FindProfile**(pSelectedElt,&pISpecObjectOnProfile) ;

       if ( SUCCEEDED(rc) && (NULL!=pISpecObjectOnProfile))

       {
          **CATIBuildPath** *piBuildPath = NULL;
HRESULT rc = **FindProfile**(pSelectedElt,&pISpecObjectOnProfile) ;
if ( SUCCEEDED(rc) && (NULL!=pISpecObjectOnProfile))
          rc = pISpecObjectOnProfile->QueryInterface( IID_CATIBuildPath, (void**) &piBuildPath );

          if ( SUCCEEDED(rc) )

          {
rc = pISpecObjectOnProfile->QueryInterface( IID_CATIBuildPath, (void**) &piBuildPath );
if ( SUCCEEDED(rc) )
             CATPathElement Context = GetEditor()->GetUIActiveObject();
             rc = piBuildPath->**ExtractPathElement**(&Context,&pPathToReturn);

             piBuildPath->Release();
             piBuildPath = NULL ;

          }

piBuildPath->Release();
piBuildPath = NULL ;
          pISpecObjectOnProfile->Release();
          pISpecObjectOnProfile = NULL ;

       }

pISpecObjectOnProfile->Release();
pISpecObjectOnProfile = NULL ;
       return pPathToReturn ;

    }
    ...  

---  
In this use case, the object to return is the sketch associated with the selected pad. In fact, to be exact it is the complete path of this sketch: from the root (the MechanicalPart) to the sketch itself.  `_pFeatureAgent` is the agent to select a Pad. It is a _CATFeatureImportAgent_ filtered with the _CATIPad_ interface. The `GetElementValue` method retrieves the selected pad. The local `FindProfile `method extracts from the pad its sketch. Refer to the code for details. `pISpecObjectOnProfile` is a _CATISpecObject_ interface pointer on a sketch ( an object implementing _CATISketch_). The _CATIBuildPath_ interface enables you to build the path from the root ( the context) to the sketch. [Top]

* * *

In Short This use case explains how to create a dialog agent to stack a workbench into a state command. This agent is a _CATEditAgent_ . [Top]

* * *

References [1] | [Describing State Dialog Command Using UML](../CAADegTechArticles/CAADegUMLDescription.md)  
---|---  
[2] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
[3] | Creating an Add-in of the Part Design Workbench  
[4] | [Implementing the Statechart Diagram](CAADegSampleGraph.md)  
[5] | [Application Frame overview](../CAAAfrTechArticles/CAAAfrOverview.md)  
[6] | [The Command Headers](../CAAAfrTechArticles/CAAAfrCommandHeaders.md)  
[7] | [Associating a Dialog Box with a State](CAADegSampleDialogWithPanelState.md)  
[Top]  

* * *

History Version: **1** [Aug 2003] | Document created  
---|---  
[Top]  

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
