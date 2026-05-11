---
title: "Creating an Interruptible Task"
category: "use case"
module: "CAAAfrUseCases"
tags: ["CATIProgressTask", "CAAAfrProgressTaskSampleCmd", "CAAApplicationFrame", "CAAProgressClock", "CAAGeometry", "CAAAfrProgressTaskSampleId", "CAAAfrProgressTask", "CATIA", "CATIProgressTaskUI"]
source_file: "Doc\online\CAAAfrUseCases\CAAAfrSampleProgressTask.htm"
converted: "2026-05-11T17:17:55.806965"
---

# 3D PLM Enterprise Architecture

| 

## User Interface - Frame

| 

### Creating an Interruptible Task

_Using CATIProgressTask, CATIProgressTaskUI,and CATTaskController_  
---|---|---  
Use Case  
  
* * *

### Abstract

This article shows how to create an interruptible task with an indicator of progression. 

  * **What You Will Learn With This Use Case**
  * **The CAAAfrProgressTask Use Case**
    * What Does CAAAfrProgressTask Do
    * How to Launch CAAAfrProgressTask
    * Where to Find the CAAAfrProgressTask Code
  * **Step-by-Step**
  * **In Short**
  * **References**



* * *

### What You Will Learn With This Use Case

Some processes can take so long that a user interface indicating the progression can be very useful. It can be also interesting to give the end user the ability to stop the task. This article shows how this information and control can be implemented by a DS component. You will need to:

  * Implement the _CATIProgressTask_ interface to perform the task and control the end user interface through the _CATIProgressTaskUI_  interface,
  * Use the _CATTaskController_ class to launch the task.

[Top]

### The CAAAfrProgressTask Use Case

CAAAfrProgressTask is a use case of the CAAApplicationFrame.edu framework that illustrates ApplicationFrame framework capabilities. [Top]

#### What Does CAAAfrProgressTask Do

This use case simulates a long process . The task is composed of fifty steps, each step consisting in to execution of the following code: | 
    
    
    for ( int j= 0 ; j<= 5000000 ; j++)
    {
       double k = 24.25 * (double) j ;
    }  
  
---  
  
The progression of the process is indicated by using a DS component which displays the following dialog box:

_Fig.1: Interface User_ ![](images/CAAAfrProgressTaskDlgWithCancel.jpg)  
---  
  
In this dialog box there are four parts (surrounded in red) that the programmer can customize:

  * The title of the dialog box
  * The icon,  located at top left, symbolizing the task
  * The name  of the object concerned by the task
  * A comment just above the progress bar



The others parts are:

  * Three ways of estimating the progress of the process 
    * A progress bar
    * The percentage of the task already executed
    * An estimation of the remaining time 
  * A Cancel button used to stop the process ( this button is optional)



This task is launched from an interactive command, that has been added to the  " CAA V5 Geometrical Analysis" workbench of the CAAGeometry document. This command, "Progress Task", has been defined in the "Analysis" menu and in the  "Mathematical Analysis"  toolbar:

_Fig.2: The "_Mathematical Analysis" Toolbar ![](images/CAAAfrProgressTaskCommandHdr1.jpg)  
---  
  
This command is a _CATDlgDialog_ having the following user interface:

_Fig.3: The "_Progress Task" Command ![](images/CAAAfrProgressTaskCommandDlg.jpg)  
---  
  
  * The "Interruptible Task" check button enables the display of the  "Cancel" button in the dialog box containing the progress bar [Fig.1].
  * If the end use clicks on the "Compute" button, the task is launched.



[Top]

#### How to Launch CAAAfrProgressTask

See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.htm)" use case for a detailed description of how this use case should be launched. For the specific scenario :

Launch CATIA. When the application is ready:

  * On the **Start** menu, point to **Infrastructure** , and then click **CAA V5: Geometrical Analysis**
  * Launch the **Progress Task** command to see the **Interruptible Task** dialog box: 
    * In the **Mathematical Analysis** toolbar or
    * In the**Analyse** menu, click **Progress Task**  
  * Click **Compute**  
    * The **Computing** Dialog box appears without the **Cancel** button. Wait until the end of the process
  * Check  **Interruptible Task**  in the  **Interruptible Task** dialog box
  * Click **Compute**  
    * The **Computing** Dialog box appears with the **Cancel** button. 
    * Click **Cancel** before the end of the process.
  * Click **Compute**  
    * The **Computing** Dialog box appears with the **Cancel** button. Wait until the end of the process
  * Click **Close** in the **Interruptible Task** dialog box.



[Top]

#### Where to Find the CAAAfrProgressTask Code

The CAAAfrProgressTask use case is made of a single file located in the CAAAfrProgressTask.m module of the CAAApplicationFrame.edu framework:

Windows | `InstallRootDirectory\``CAAApplicationFrame.edu\CAAAfrProgressTask.m\`  
---|---  
Unix | `InstallRootDirectory/``CAAApplicationFrame.edu/CAAAfrProgressTask.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]

### Step-by-Step

There are two logical steps in CAAAfrProgressTask:

  1. Creating the Interactive Command
  2. Implementing the CATIProgressTask Interface



[Top]

#### Creating the Interactive Command

This command is called _CAAAfrProgressTaskSampleCmd_. This section describes:

  1. The header file
  2. The source file
  3. The NLS resource file


  1. The header file
    
    // Dialog Framework
    #include "CATDlgDialog.h"     // Needed to derive from CATDlgDialog
    
    // Dialog Framework
    class CATDlgCheckButton;
    // ApplicationFrame Framework
    class CATFrmEditor;
    
    class CAAAfrProgressTaskSampleCmd : public CATDlgDialog
    {
      ...
      **DeclareResource**(CAAAfrProgressTaskSampleCmd, CATDlgDialog);
      
      public :
        
        CAAAfrProgressTaskSampleCmd();
    
        virtual ~CAAAfrProgressTaskSampleCmd();  
    
        ...
    
      private : 
    
        void **ClickCompute**(CATCommand            *iPublishingCommand, 
                        CATNotification         *iNotification, 
                        CATCommandClientData     iUsefulData);
     
        void **ClickClose**(CATCommand              *iPublishingCommand, 
                        CATNotification         *iNotification, 
                        CATCommandClientData     iUsefulData);
                        
        void **EditorClose**  (CATCallbackEvent  iEvent,
                               void             *iFrom,
                               CATNotification  *iNotification,
                               CATSubscriberData iData,
                               CATCallback       iCallBack );
                               
        CAAAfrProgressTaskSampleCmd(const CAAAfrProgressTaskSampleCmd &iObjectToCopy);
    
        CAAAfrProgressTaskSampleCmd & operator = (const CAAAfrProgressTaskSampleCmd &iObjectToCopy);
    
      private : 
    
        **CATDlgCheckButton** * _pInterruptTask  ;
        **CATFrmEditor**      * _pEditor ;
    
    };  
  
---  
  
This header file contains the following declaration: 
     * The class derives from _CATDlgDialog_
     * The `DeclareResource` macro states that the resources of the _CAAAfrProgressTaskSampleCmd_ command class are located in the CAAAfrProgressTaskSampleCmd.CATNls file. If  resources were assigned to the _CATDlgDialog_ class, they would be concatenated with those of _CAAAfrProgressTaskSampleCmd_
     * As usual, the class has a constructor and a destructor 
     * The copy constructor and the "=" operator are set as private to prevent the compiler from automatically creating them as public. 
     * Two callback methods contain the code to be executed when the end user presses either Compute or Close 
     * A callback method, `EditorClose` , to be prevent when an editor is closed. If this editor, referenced by `_pEditor`, is those which has launched the command,  the command kills it. 
     * A  check button 

 

  2. The source file
     * The necessary  header files:
    
    // COPYRIGHT DASSAULT SYSTEMES 2002
    
    //Local Framework
    #include "CAAAfrProgressTaskSampleCmd.h"
    
    // Dialog Framework
    #include "CATDlgCheckButton.h"
    #include "CATDlgPushButton.h"
    #include "CATDlgGridConstraints.h"
    ...
    
    //Application Frame Framework
    #include "CATApplicationFrame.h"
    #include "CATFrmEditor.h"
    #include "CATTaskController.h"
    ...
    
    // C++ standard library
    #include "iostream.h"
    ...  
  
---  
     * This command is launched from a header command:
    
    ...
    #include "**CATCreateExternalObject**.h"
    **CATCreateClass**(CAAAfrProgressTaskSampleCmd);
    ...  
  
---  
  
The `CATCreateClass` macro enables the instantiation of the command by its class name. 

     * The constructor:
    
    ...
    CAAAfrProgressTaskSampleCmd::CAAAfrProgressTaskSampleCmd()
              :**CATDlgDialog** ((CATApplicationFrame::GetFrame())->GetMainWindow(), 
                              "CAAAfrProgressTaskSampleId",
                              CATDlgGridLayout | CATDlgWndBtnClose )
    {
      _pInterruptTask = new **CATDlgCheckButton**(this, "InterruptId" );
      _pInterruptTask->SetGridConstraints(0,0,1,1,CATGRID_CENTER);      
      
      CATDlgPushButton * pComputeButton   = NULL ;
      pComputeButton = new **CATDlgPushButton**(this, "ComputeButtonId" );
      pComputeButton->SetGridConstraints(1,0,1,1,CATGRID_CENTER);      
      
    
      AddAnalyseNotificationCB(pComputeButton, pComputeButton->GetPushBActivateNotification(),
                    (CATCommandMethod)&CAAAfrProgressTaskSampleCmd::**ClickCompute** ,
                                NULL);
      
      AddAnalyseNotificationCB(this, this->GetWindCloseNotification(),
                    (CATCommandMethod)&CAAAfrProgressTaskSampleCmd::**ClickClose** ,
                                NULL);
      AddAnalyseNotificationCB(this, this->GetDiaCLOSENotification(),
                    (CATCommandMethod)&CAAAfrProgressTaskSampleCmd::**ClickClose** ,
                                NULL);
    
      **_pEditor** = CATFrmEditor::GetCurrentEditor();
      if ( (NULL != _pEditor) && (NULL != CATFrmLayout::GetCurrentLayout()) )
      {
         ::**AddCallback**(this,
                    CATFrmLayout::GetCurrentLayout(),
    		  CATFrmEditor::EDITOR_CLOSE_ENDED(),
    		  (CATSubscriberMethod)&CAAAfrProgressTaskSampleCmd::EditorClose,
    		  NULL);
      }
      
      **SetVisibility**(CATDlgShow);
    }
    ...
      
  
---  
  
The application main window is the parent of the dialog box. The style of this dialog box is `CATDlgGridLayout` to enhance the positioning of each included dialog object and  `CATDlgWndBtnClose` to display only one button, the `Close` button, at the bottom of the box. 

This dialog box has two included dialog objects:

       * a check button, referenced by the `_pInterruptTask` pointer, to enable the end user to request the task to be interruptible or not.
       * a push button, referenced by the `pComputeButton`  pointer, to launch the task

The `ClickClose` callback method is called when the end user clicks:

       * on the Close Button: the `GetDiaCLOSENotification` notification is used
       * on the Close window (NT: the cross at upper right corner and UNIX the right mouse button on the banner): the `GetWindCloseNotification` notification is used

Finally, we set a callback to be prevent when an editor is closed. This notification is sent by the current layout (a singleton during the session). 

     * The destructor:

In the destructor code, it is not necessary to delete the dialog object created in this command, as it will be automatically deleted by the Dialog process, but it is strongly recommended to reset the data member to NULL. 
    
    ...
    CAAAfrProgressTaskSampleCmd::~CAAAfrProgressTaskSampleCmd() 
    {
       _pInterruptTask   = NULL ;
       
       if ( (NULL != _pEditor) && ( NULL != CATFrmLayout::GetCurrentLayout()) )
       {
          ::**RemoveSubscriberCallbacks**(this,CATFrmLayout::GetCurrentLayout());
       }
    
       _pEditor = NULL ;
    }
    ...  
  
---  
  
The callback set in the constructor must be removed, unless if the destruction has been requested  from the `EditorClose` method where the remove has already be done. 

     * The ClickCompute method:
    
    ...
    void CAAAfrProgressTaskSampleCmd::ClickCompute (   CATCommand          * iPublishingCommand,
                                                  CATNotification     * iNotification,
                                                  CATCommandClientData  iUsefulData)
    {
      **CATTaskController  Task** ;
    
      **CATIProgressTask** * pIProgressTask = NULL ;
      HRESULT rc = QueryInterface(IID_CATIProgressTask,(void**)& pIProgressTask);
    
      if ( SUCCEEDED(rc) && (NULL != _pInterruptTask ) )
      {
          if ( CATDlgCheck == _pInterruptTask->GetState() )
          {
             Task.**Schedule**(pIProgressTask,**TRUE** ,NULL);
          }else
          {
             Task.**Schedule**(pIProgressTask,**FALSE** ,NULL);
          }
    
          pIProgressTask->Release();
          pIProgressTask = NULL ;
      }
    }
    ...  
  
---  
  
The end user has clicked on the "Compute" button and the task must be launched. This is possible by using the _CATTaskControler_ (ApplicationFrame framework). The `Schedule` method will launch a command which contains the dialog box with the progress bar [Fig.1]. The arguments of this method are respectively :

       * The _CATIProgressTask_ interface pointer, referenced by `pIProgressTask`. In this case the command itself implements this interface, so it performs a `QueryInterface` on itself
       * A boolean to indicate if the Cancel button must be displayed. In this case, the `_pInterruptTask` check button contains the end user choice.
       * A value (here NULL) used as input data of the `PerformTask` method. 

 

     * The ClickClose method:
    
    ...
    void CAAAfrProgressTaskSampleCmd::ClickClose(CATCommand           * iPublishingCommand,
                                              CATNotification      * iNotification,
                                              CATCommandClientData   iUsefulData)
    {
      SetVisibility(CATDlgHide);
                             
      **RequestDelayedDestruction**();
    }
    ...  
  
---  
  
`RequestDelayedDestruction` enables to delete the command. 

     * The EditorClose method:
    
    ...
    void CAAAfrProgressTaskSampleCmd::EditorClose(CATCallbackEvent  iEvent, 
                                                  void            * iFrom,
                                                  CATNotification * iNotification,
                                                  CATSubscriberData iClientData,
                                                  CATCallback       iCallBack ) 
    {
      if ( **_pEditor == iFrom** )
       {
       
          // Now this extension will receive any message.
          //
          ::**RemoveSubscriberCallbacks**(this,CATFrmLayout::GetCurrentLayout());
    
          // Suicide
          **RequestDelayedDestruction**();
    
          _pEditor = NULL ; 
       }
    }
    ...  
  
---  
  
An editor is closed, i.e a document is closed. The layout sends a notification indicating that the publisher is the editor; The variable iFrom is the editor to be closed. If this editor is the same as the one that has launched the current command, it must be deleted. 

  3. The NLS resource file:

The `CAAAfrProgressTaskSampleCmd``.CATNls `file is` `located in the `CAAApplicationFrame.edu/Cnext/resources/msgcatalog `directory. It contains:

     * The title of the dialog box and titles of the included dialog objects: 
           
           **Title**                ="Interruptible Task" 
           ComputeButtonId.Title="Compute" ;
           InterruptId.Title    ="Interruptible Task" ;
           ...  
  
---  
     * The help message displayed in the status bar when you pass over the dialog box: 
           
           ...
           **Help** = "Dialog box which creates an interruptible task ";
           ...  
  
---  
     * The long help message displayed in a balloon when you select a dialog object with the question mark: 
           
           ...
           InterruptId.**LongHelp**     ="Check if the task is interruptible or not" ;
           ComputeButtonId.LongHelp ="Launch the task. It is interruptible if the previous
           button is checked" ;
           ...  
  
---  
     * The short help message displayed in a balloon when you pass over a dialog object: 
           
           ...
           InterruptId.**ShortHelp**     ="Check if the task is interruptible or not" ;
           ComputeButtonId.ShortHelp ="Launch the task" ;
           ...  
  
---  
     * The help message displayed in the status bar when you pass over a dialog object: 
           
           ...
           InterruptId.**Help**     ="Check if the task is interruptible or not" ;
           ComputeButtonId.Help ="Launch the task" ;
           ...  
  
---  



[Top]

#### Implementing the CATIProgressTask  Interface

The _CAAAfrProgressTaskSampleCmd_ class implements the _CATIProgressTask_ interface. This section describes how this is done:

  1. Declaring the methods of the _CATIProgressTask_ interface in the header file
  2. Adding the necessary included files in the source file
  3. Coding the PerformTask method
  4. Coding the GetCatalogName method
  5. Coding the GetIcon method
  6. Modifying the CAAAfrProgressTaskSampleCmd.CATNls file
  7. Declaring the command as a component 


  1. Declaring the methods of the _CATIProgressTask_ interface in the header file
    
    ...
    **class CATIProgressTaskUI** ;
    
    class CAAAfrProgressTaskSampleCmd : public CATDlgDialog
    {
        ...      
     public :
     
        ...
        virtual HRESULT **PerformTask**    (CATIProgressTaskUI  * iUI, void * iUserData);
        
        virtual HRESULT **GetCatalogName** (CATString           * oCatalogName);
    
        virtual HRESULT **GetIcon**        (CATString           * oIcon) ;
        ...
    }
            
  
---  
  
These are the three methods of the _CATIProgressTask_ interface.

  2. Adding the necessary  include files:
    
    ...
    // Dialog Framework
    ...
    #include "CATMsgCatalog.h"
    ...
    
    //Application Frame Framework
    ...
    #include "CATIProgressTaskUI.h"
    ...  
  
---  
  3. Coding the PerformTask method
    
    ...
    HRESULT CAAAfrProgressTaskSampleCmd::PerformTask (CATIProgressTaskUI  * iUI, void * iUserData)
    {
        if ( NULL == iUI ) return E_FAIL ;
    
        int min = 1 ;
        int max = 50 ;
        iUI->**SetRange**(min,max);
        
        for ( int i= min ; i <= max ; i++)
        {
            iUI->**SetProgress**(i);
    
            CATUnicodeString usMessage ;
            CATUnicodeString usParam[1] ;
            
            **usParam[0].BuildFromNum(i);**
    
            usMessage = CATMsgCatalog::**BuildMessage**("CAAAfrProgressTaskSampleCmd",
                                            "ProgressTaskUI.**CommentRuntime** ",usParam,1,
                                            "Step ...");
    
            iUI->**SetComment**(usMessage);
    
            // begin of the step'simulation 
            for ( int j= 0 ; j<= 5000000 ; j++)
            {
                double k = 24.25 * (double) j ;
            }
            // end of the step'simulation 
    
            CATBoolean interrupt ;
            if ( S_OK != iUI->**IsInterrupted**(&interrupt) || (TRUE == interrupt) )
            {
                return E_FAIL ;
            }
        }
    
        return S_OK ;
    }
    ...       
  
---  
  
This method consists in executing the task and giving information to the dialog box managed by the _CATIProgressTaskUI_   interface [Fig 1]. 

At first, before beginning the task, it is necessary to define the range of the process by using the `SetRange `method.

At each step, the dialog box is modified:

     * The progress bar, the estimated time remaining and the percentage of the progression:  using the `SetProgress `method. 
     * The comment above the progress bar: using the `BuildMessage` to construct the NLS message and `SetComment` to modify the text

In this use case, the message is "Step i ..." where i is the number of the step.

The task is stopped if the end user clicks on the Cancel button. The `IsInterrupted `method returns `FALSE` if the end user has clicked on the button or if the Cancel button does not exist. If the command has been interrupted, the method returns` E_FAIL`, and the dialog box will be closed. 

  4. Coding the GetCatalogName method
    
    ...
    HRESULT CAAAfrProgressTaskSampleCmd::GetCatalogName (CATString * oCatalogName)
    {
        if ( NULL == oCatalogName ) return E_FAIL ;
    
        *oCatalogName = CATString("CAAAfrProgressTaskSampleCmd");
        return S_OK ;
    }
    ...       
  
---  
  
This method returns the name of the NLS file which contains the title, the default name of the object concerned and the default comment. See the next section "Modifying the Nls file"

  5. Coding the GetIcon method
    
    ...
    HRESULT CAAAfrProgressTaskSampleCmd::GetIcon(CATString  * oIcon) 
    {
        if ( NULL == oIcon ) return E_FAIL ;
    
        *oIcon = CATString("I_CAAProgressClock");
        return S_OK ;
    }
    ...       
  
---  
  
The  I_CAAProgressClock.bmp icon can be found in the CNext/resources/graphic/icons/normal of the CAAApplicationFrame.edu.

  6. Modifying the CAAAfrProgressTaskSampleCmd.CATNls file

Each label of the dialog box is prefixed by the keyword `ProgressTaskUI:`
    
    ...
    ProgressTaskUI.**Title** = "Computing...";
    ProgressTaskUI.**ObjectName** = "Model";
    ProgressTaskUI.**Comment** = "Step ..."; // Not used in the use case
    ...   
  
---  
  
In this use case, only the `Title` and the `ObjectName` are useful. For the comment, the message is changed at each step, so the default text "Step ..." is not used. At each step the message is constructed thanks to the `CommentRuntime` keyword. The parameter is the number of the step. 
    
    ...
    ProgressTaskUI.CommentRuntime = "Step /p1 ...";   
  
---  
  7. Declaring the command as a component

An object which implements an interface must be a component. 
    
    ...
    class CAAAfrProgressTaskSampleCmd : public CATDlgDialog
    {
        **CATDeclareClass** ;
        ...      
     public :      
    
    ...  
  
---  
The `CATDeclareClass` macro declares that the class _CAAAfrProgressTaskSampleCmd_ belongs to a component. 
    
    ...
    **CATImplementClass**(CAAAfrProgressTaskSampleCmd, Implementation, **CATCommand** , CATNull);
    ...  
  
---  
  
The `CATImplementClass` macro declares that the _CAAAfrProgressTaskSampleCmd_ class is a component main class thanks the `Implementation` keyword, and OM-derives [1] from _CATCommand_. 
    
    ...
    #include <TIE_CATIProgressTask.h> 
    TIE_CATIProgressTask(CAAAfrProgressTaskSampleCmd);
    ...  
  
---  
The _CAAAfrProgressTaskSampleCmd_ class states that it implements the _CATIProgressTask_ interface thanks to the `TIE_CATIProgressTask` macro. 

The interface dictionary, the CAAApplicationFrame.edu.dico file, located in the CNext/code/dictionary of the CAAApplicationFrame.edu framework contains the following line:
    
    ...
    CAAAfrProgressTaskSampleCmd CATIProgressTask  libCAAAfrProgressTask
    ...  
  
---  



[Top]

* * *

### In Short

This article shows how to create an interruptible task with an indicator of progression. The object which contains the task implements the _CATIProgressTask_ interface and the task is itself launched by an _CATTaskControler_ class instance.

_[_Top]

* * *

### References

[1] | [Object Modeler Component and Implementation Inheritance](../CAASysTechArticles/CAASysOMInheritance.htm)  
---|---  
[Top]  
  
* * *

### History

Version: **1** [Mar 2002] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
