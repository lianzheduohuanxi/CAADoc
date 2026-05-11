---
title: "Creating Contextual Menus in a State Dialog Command"
category: "use case"
module: "CAADegUseCases"
tags: ["CAADegAnalysisLogCmd", "CAAISysGeomFactory", "CAAISysLine", "CAAISysPoint", "CATISO", "CAADialogEngine", "CAAGeometry", "CAADegGeoCommands"]
source_file: "Doc/online/CAADegUseCases/CAADegSampleCtxMenu.md"
converted: "2026-05-11T17:33:49.611686"
---

3D PLM Enterprise Architecture |  User Interface - Commands |  Creating Contextual Menus in a State Dialog Command _Customizing object's contextual menus in a state dialog command_  
---|---|---  
Use Case  
  
* * *

Abstract This article shows how to create, in a state dialog command, a contextual menu displayed when right clicking on objects that implement a given interface.
    * **What You Will Learn With This Use Case**
    * **The Logical Command Use Case**
      * What Does the Logical Command Do
      * How to Launch the Logical Command
      * Where to Find the Logical Command Code
    * **Step-by-Step**
    * **Displaying the Contextual Menu when Clicking on Any Object and on the Background**
    * **In Short**
    * **References**  
---  
  
* * *

What You Will Learn With This Use Case This use case is intended to show how to create a contextual menu that displays on objects that implement a given interface. [Top] The Logical Command Case The Logical command is a use case of the CAADialogEngine.edu framework that illustrates the DialogEngine framework capabilities. [Top] What Does the Logical Command Do The Logical command is a state dialog command that creates a contextual menu, that is, a menu displayed when the end user right clicks on objects. This menu is displayed only if the object implements a given interface, namely _CAAISysLine_. A right click on such objects displays a contextual menu with three items, concatenated to the items provided by the window, since the document is displayed in a _CATFrmGraphAnd3DWindow_ instance. ![Contextual Menu](../CAADegTechArticles/images/CAACtxMenu1.jpg) | Window's items      Items added by the Logical command  
---|---  
  Clicking on one of these items displays the start, medium, or end point of the line. These points are temporary points ( CAAISysPoint objects) displayed by the ISO. [Top] How to Launch the Logical Command See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched. Then, in the window where you run the mkrun command, do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following:
    * Select the Start->Infrastructure->CAA V5: Geometrical Analysis 
    * Select Insert->Line
    * Click twice to create the line
    * Select Analyze->Logical
    * Right click the line, and click one of the proposed item. The corresponding point is displayed.
[Top] Where to Find the Use Case Code The Logical command is made of a single class named _CAADegAnalysisLogCmd_ located in the CAADegGeoCommands.m module of the CAADialogEngine.edu framework: Windows | `InstallRootDirectory\CAADialogEngine.edu\CAADegGeoCommands.m\`  
---|---  
Unix | `InstallRootDirectory/CAADialogEngine.edu/CAADegGeoCommands.m/`  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. [Top] Step-by-Step To create the CAADegAnalysisLogCmd `BuildGraph` method, there are seven steps: # | Step | Where  
---|---|---  
1 | Create the state dialog command header file | Header file  
2 | Enable the command to be instantiated by a command header | Source file  
3 | Implement the command state chart diagram | BuildGraph method  
4 | Create the Action Method | action method  
5 | Create the callback methods | action method  
6 | Manage the command lifecycle | callback method and destructor  
7 | Release the indication agent | Destructor or `Cancel` method  
[Top] Creating the State Dialog Command Header File Below is the header file of the _CAADegAnalysisLogCmd_ class that holds the code for this command.
    #include "CATStateCommand.h"  // Needed to derive from CATStateCommand
    
    class CATPathElementAgent; 
    class CATISO;
    class CAAISysPoint;
    class CATMathPoint;
    
    class CAADegAnalysisLogCmd : public CATStateCommand
    {
    
      CmdDeclareResource(CAADegAnalysisLogCmd,CATStateCommand);
      public :
        CAADegAnalysisLogCmd();
        virtual           ~CAADegAnalysisLogCmd(); 
    
        _// Manages the focus_
        CATStatusChangeRC Activate   ( CATCommand * iCmd,CATNotification * iNotif);
        CATStatusChangeRC Cancel     ( CATCommand * iCmd,CATNotification * iNotif);
        CATStatusChangeRC Desactivate( CATCommand * iCmd,CATNotification * iNotif);
    
        virtual void **BuildGraph**(); _// Implements the statechart_
    
        CATBoolean **CreateCntxMenu**(void * iUsefulData);
    
        void StartPoint (CATCommand           * iCmd , 
    		     CATNotification      * iNotif, 
    	             CATCommandClientData   iData) ;
        void MediumPoint(CATCommand           * iCmd , 
    		     CATNotification      * iNotif, 
    	             CATCommandClientData   iData) ;
        void EndPoint   (CATCommand           * iCmd , 
    		     CATNotification      * iNotif, 
    	             CATCommandClientData   iData) ;
      
      private :
    
        void ShowPoint(CATMathPoint &iPoint);
        CATPathElementAgent  * _daPathElement ;    
        CATISO               * _ISO ;
        CAAISysPoint         * _TemporaryPoint ;
        CATBaseUnknown       * _Container;      
    };  
  
---  
This class includes the following:
    * The ` CmdDeclareResource` macro states that the resources for this command, that is the prompts associated with the different states, are located in a file named CAADegAnalysisLogCmd.CATNls
    * The three methods `Activate`, `Desactivate`, and ` Cancel`, are called by the command selector to manage the command in the command stack
    * The ` BuildGraph` method creates the states, dialog agents, anf transitions of the dialog command
    * The ` CreateCntxMenu` method is called when the end user clicks a line
    * The `StartPoint`, `MediumPoint`, and ` EndPoint` methods are the methods called by the menu items
    * The ` ShowPoint` method creates and displays the required point.
The data members are pointers to the path element agent used by the ` BuildGraph` method, the Interactive Set of Objects used to display the start, medium, or end point as a temporary point that doesn't belong to the document, and the document container that implements the point factory interface used to create this point. [Top] Enabling the Command to Be Instantiated by a Command Header The CAADegAnalysisLogCmd.cpp begins by:
    
    ...
    #include "CATCreateExternalObject.h"
    CATCreateClass(CAADegAnalysisLogCmd);
    ...  
  
---  
This macro creates a C function that creates an instance of this class. This function is called by the command header to instantiate the command when the end user selects it if it weren't previously instantiated. [Top] Implementing the Command State chart Diagram Below is the code to write in the ` BuildGraph` method:
    
    ...
    void CAADegAnalysisLogCmd::BuildGraph()
    {
       _daPathElement = new CATPathElementAgent("SelFirstLine");
       _daPathElement->AddElementType("CAAISysLine");
       _daPathElement->SetBehavior( CATDlgEngWithContext |
    	                        CATDlgEngRepeat      |	                
                                    CATDlgEngWithUndo );
    
      CATDialogState *stGetEltState = GetInitialState("stGetEltStateId");
       stGetEltState->AddDialogAgent(_daPathElement);
    
      CATDialogTransition *pCntxMenuTransition =    AddTransition
    	   (
    		   stGetEltState,
    		   stGetEltState,
    		   IsLastModifiedAgentCondition(_daPathElement)  , 
    		   Action((ActionMethod) & CAADegAnalysisLogCmd::CreateCntxMenu)
    		) ; 
    }
    ...  
  
---  
A _CATPathElement_ instance is created as a data member of the dialog command class. It is valued for objects implementing the _CAAISysLine_ interface using the `AddElementType` method, and when right clicking on their representations thanks to the `CATDlgEngWithContext` behavior in the `SetBehavior` method. The `CATDlgEngRepeat` behavior makes this dialog agent repeatable. A single state is created, and the dialog agent is added to it. The transition loops on this state, and whenever right clicking on a object matches the dialog agent, the `CreateCntxMenu` method is executed. [Top] Creating the Action Method This method is as follows.
    
    ...
    CATBooleanCAADegAnalysisLogCmd::CreateCntxMenu(void * iData)
    {
      // Selected Line 
      CATPathElement * pLinePath = _daPathElement->GetValue();
      CATBaseUnknown * pLine = NULL;
      if ( pLinePath && pLinePath->GetSize() )
      {
        pLine = (*pLinePath)[pLinePath->GetSize()-1];
      }
    
      if ( pLine)
      {
        // Retrieves the contextual menu
        CATNotification *pNotif = GetLastNotification();
        CATDlgContextualMenu *pCntxMenu = ((CATContext*)pNotif)->GetContextualMenu();
    
        // Default Item Title 
        CATString StartString ("StartPoint");
        CATString MediumString("MediumPoint");
        CATString EndString ("EndPoint") ;
    
        // all these dialog objects are deleted when the contextual menu 
        // is deleted. The command does't delete them.
        CATDlgSeparatorItem *Separator = new CATDlgSeparatorItem(pCntxMenu,"separator");
        CATDlgPushItem * StartPoint    = new CATDlgPushItem(pCntxMenu,StartString) ;
        CATDlgPushItem * MediumPoint   = new CATDlgPushItem(pCntxMenu,MediumString) ;
        CATDlgPushItem * EndPoint      = new CATDlgPushItem(pCntxMenu,EndString) ;
        
        // NLS data in the NLS file of this command ( see this header file )
        StartPoint->SetTitle(CATMsgCatalog::BuildMessage(
                                          "CAADegAnalysisLogCmd",
                                          "StartPointTitle")); 
        MediumPoint->SetTitle(CATMsgCatalog::BuildMessage(
                                           "CAADegAnalysisLogCmd",
                                           "MediumPointTitle")); 
        EndPoint->SetTitle(CATMsgCatalog::BuildMessage(
                                           "CAADegAnalysisLogCmd",
                                           "EndPointTitle")); 
    
        // Callbacks
        AddAnalyseNotificationCB(EndPoint,
                                 EndPoint->GetMenuIActivateNotification(),
                                 (CATCommandMethod) & CAADegAnalysisLogCmd::EndPoint, 
    			     (void*) pLine );
    
        AddAnalyseNotificationCB(MediumPoint,
                                 MediumPoint->GetMenuIActivateNotification(),
    			  (CATCommandMethod) & CAADegAnalysisLogCmd::MediumPoint, 
    			  (void*) pLine );
    
        AddAnalyseNotificationCB(StartPoint,
                                 StartPoint->GetMenuIActivateNotification(),
    			  (CATCommandMethod) & CAADegAnalysisLogCmd::StartPoint, 
    			  (void*) pLine );
      }
      return TRUE ;
    }
    ...  
  
---  
This method is called when the transition of the `BuildGraph` method is executed. It:
    * Retrieves the last notification sent, that is a _CATContext_ instance, and retrieves from this notification a pointer to the contextual menu
    * Creates the three push items added as children of the contextual menu
    * Sets their displayed titles from the message file
    * Retrieves a pointer to the path element of the object right clicked from the dialog agent that holds it
    * Retrieves a pointer to the line implementation, as the last item in the path element table (its range is table size minus 1)
    * Sets callbacks for the three menu items. The pointer to the line is passed as the fourth parameter of the `AddAnalyseNotificationCB` method to the called methods.
Since the contextual menu is retrieved and updated with push items and a separator rather than being created, there is no need to delete the push items and the separator. They will be deleted when the contextual menu itself will be deleted by the destructor of the class that creates it. In the same way, there is no need to remove the callbacks. They will also be automatically removed when the contextual menu will be deleted. [Top] Creating the Callback Methods The callback methods retrieve each the appropriate point to display, and call the `ShowPoint` method. Only `StartPoint` is shown here
    
    ...
    void CAADegAnalysisLogCmd::StartPoint(CATCommand           * iSendingCommand, 
                                       CATNotification      * iSentNotification, 
                                       CATCommandClientData   iUsefulData)
    {
      CATBaseUnknown * pLine = (CATBaseUnknown *) iUsefulData;
      if ( pLine )
      {
        CAAISysLine * Line = NULL;                
        HRESULT rc = pLine->QueryInterface(IID_CAAISysLine, (void**)&Line);
        if (SUCCEEDED(rc))
        {
          CATMathPoint point ;
          Line->GetStartPoint(point) ;
          ShowPoint(point);
          Line -> Release();
        }
      }
    }
    
    ...  
  
---  
The `ShowPoint` method creates a point instance, if it doesn't already exist, that implements the _CAAISysPoint_ interface, and the point factory returns a pointer to this interface, and adds it to the Interactive Set of Objects. This makes it possible to display it. Then ` ShowPoint `assigns to that instance the coordinates of the _CATMathPoint_ instance passed from the called back method and updates the ISO with this point..
    
    ...
    void CAADegAnalysisLogCmd::ShowPoint(CATMathPoint & iPoint)
    {   
      if ( NULL == _piTemporaryPoint ) 
      {
        CAAISysGeomFactory * piSysGeomFactory = NULL;                
        HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                              (void**)&piSysGeomFactory);
        if (SUCCEEDED(rc))
        {
          piSysGeomFactory -> Create(CAAISysGeomFactory::Point, IID_CAAISysPoint, 
                            (CATBaseUnknown**)&_piTemporaryPoint);
          _pISO->AddElement(_piTemporaryPoint);
    
          piSysGeomFactory -> Release();
          piSysGeomFactory=NULL;
        }
      }
    
      if (  NULL != _piTemporaryPoint )
      {
        _piTemporaryPoint->SetCoord((float) iPoint.GetX(),
                                    (float) iPoint.GetY(), 
                                    (float) iPoint.GetZ());
        _pISO->**UpdateElement**(_piTemporaryPoint) ;
      }
    }
    ...  
  
---  
[Top] Managing the Command Lifecycle The following methods are called by the command selector to manage the command when it becomes the active one, or when another command becomes active instead.
    
    ...
    CATStatusChangeRC CAADegAnalysisLogCmd::Cancel(CATCommand *iCmd, CATNotification *iNotif)
    {
      if (_TemporaryPoint)
      {
        _ISO->**RemoveElement**(_TemporaryPoint);
        _TemporaryPoint->Release();
        _TemporaryPoint= NULL ;
      }
      return (CATStatusChangeRCCompleted);
    }
    ...  
  
---  
[Top] Releasing the Indication Agent A pointer to the selection agent was created in the command `BuildGraph` method as a data member to be accessed and used in different methods. It should be released when it becomes useless. This can be done in the command destructor, as shown here. This could also be done in the `Cancel` method called just before the destructor.
    
    CAADegAnalysisLogCmd::CAADegAnalysisLogCmd()
    {
      ...
      if ( NULL != _daPathElement  )
      {
         _daPathElement ->RequestDelayedDestruction() ;
         _daPathElement = NULL ;
      }  ...  
  
---  
[Top] Displaying the Contextual Menu when Clicking on Any Object and on the Background The same command should now react to any object whose representation is right clicked. This includes the viewer background. To do this, replace the ` AddElementType` method by the `AcceptOnNotify` method to make the dialog agent match any right click, and remove the `CATDlgEngWithContext` behavior from the `AddElementType` method. The rest of the method is unchanged.
    
    void CAADegAnalysisLogCmd::BuildGraph()
    {
      _daPathElement = new **CATPathElementAgent**("SelFirstLine");
      _daPathElement->**AcceptOnNotify**(NULL, "CATContext");
      _daPathElement->**SetBehavior**(CATDlgEngRepeat);
    
      CATDialogState * stGetEltState = **GetInitialState**("stGetEltStateId");
      stGetEltState->**AddDialogAgent**(_daPathElement);
    
      CATDialogTransition * pCntxMenuTransition = AddTransition
               (stGetEltState,        // From state
                stGetEltState,        // To state
                **IsLastModifiedAgentCondition**(_daPathElement), 
                **Action**((ActionMethod) & CAADegAnalysisLogCmd::CreateCntxMenu));
    }  
  
---  
The `CreateCtxMenu` method is the same as above. [Top]

* * *

In Short Contextual menus can be set onto objects implementing a given interface by any dialog command. [Top]

* * *

References [Top]  
---  
  
* * *

History Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
