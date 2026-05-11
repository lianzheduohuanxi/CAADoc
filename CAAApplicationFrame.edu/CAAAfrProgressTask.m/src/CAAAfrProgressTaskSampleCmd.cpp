// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAAfrProgressTaskSampleCmd.h"

// Dialog Framework
#include "CATDlgCheckButton.h"
#include "CATDlgPushButton.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"

//Application Frame Framework
#include "CATApplicationFrame.h"
#include "CATFrmEditor.h"
#include "CATIProgressTaskUI.h"
#include "CATTaskController.h"

// C++ standard library
#include "iostream.h"

// To declare that the class is a component main class which OM-derives from CATCommand
CATImplementClass(CAAAfrProgressTaskSampleCmd, Implementation, CATCommand, CATNull);


//-------------------------------------------------------------------------
// To create the TIE object
#include <TIE_CATIProgressTask.h> 
TIE_CATIProgressTask(CAAAfrProgressTaskSampleCmd);

// To declare that CAAAfrProgressTaskSampleCmd implements CATIProgressTask, insert 
// the following line in the interface dictionary:
//
//    CAAAfrProgressTaskSampleCmd CATIProgressTask  libCAAAfrProgressTask

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAAAfrProgressTaskSampleCmd);

//-----------------------------------------------------------------------------

CAAAfrProgressTaskSampleCmd::CAAAfrProgressTaskSampleCmd()
          :CATDlgDialog ((CATApplicationFrame::GetFrame())->GetMainWindow(), 
                          "CAAAfrProgressTaskSampleId",
                          CATDlgGridLayout | CATDlgWndBtnClose )
{
  //
  // The father of this command is (CATApplicationFrame::GetFrame())->GetMainWindow()
  // it's a Dialog object dedicated to the current document, Try to select an another
  // document, same type or not, during this command, the Dialog box is hidden.
  // 
  // This commmand is dedicated to CNEXT application, so CATApplicationFrame::GetFrame()
  // is not NULL when this command is launched
  //
  // This command is in Undefined Mode: not Shared and not Exclusive

  cout << "CAAAfrProgressTaskSampleCmd::CAAAfrProgressTaskSampleCmd" << endl; 

  _pInterruptTask = new CATDlgCheckButton(this, "InterruptId" );
  _pInterruptTask->SetGridConstraints(0,0,1,1,CATGRID_CENTER);      
  
  CATDlgPushButton * pComputeButton   = NULL ;
  pComputeButton = new CATDlgPushButton(this, "ComputeButtonId" );
  pComputeButton->SetGridConstraints(1,0,1,1,CATGRID_CENTER);      
  
  //========================================
  // Subscribes to the Button Compute event
  //========================================

  AddAnalyseNotificationCB(pComputeButton, pComputeButton->GetPushBActivateNotification(),
                (CATCommandMethod)&CAAAfrProgressTaskSampleCmd::ClickCompute,
                            NULL);


  //========================================
  // Subscribes to the Close event
  //========================================

  AddAnalyseNotificationCB(this, this->GetWindCloseNotification(),
                (CATCommandMethod)&CAAAfrProgressTaskSampleCmd::ClickClose,
                            NULL);
  AddAnalyseNotificationCB(this, this->GetDiaCLOSENotification(),
                (CATCommandMethod)&CAAAfrProgressTaskSampleCmd::ClickClose,
                            NULL);

  // To delete the command when the editor is closed, and the command
  // is already active
  //
  _pEditor = CATFrmEditor::GetCurrentEditor();
  if ( (NULL != _pEditor) && (NULL != CATFrmLayout::GetCurrentLayout()) )
  {
     ::AddCallback(this,
                CATFrmLayout::GetCurrentLayout(),
		  CATFrmEditor::EDITOR_CLOSE_ENDED(),
		  (CATSubscriberMethod)&CAAAfrProgressTaskSampleCmd::EditorClose,
		  NULL);
  }

  // The window is shown
  SetVisibility(CATDlgShow);
}

//-------------------------------------------------------------------------------

CAAAfrProgressTaskSampleCmd::~CAAAfrProgressTaskSampleCmd() 
{
   cout << "CAAAfrProgressTaskSampleCmd::~CAAAfrProgressTaskSampleCmd"<< endl ;  
   
  // Dialog's object delete by the current command
   _pInterruptTask   = NULL ;
   
   if ( (NULL !=  _pEditor) && ( NULL != CATFrmLayout::GetCurrentLayout()) )
   {
      ::RemoveSubscriberCallbacks(this,CATFrmLayout::GetCurrentLayout());
   }

   _pEditor = NULL ;
}

//-----------------------------------------------------------------------------

void CAAAfrProgressTaskSampleCmd::ClickCompute (   CATCommand          * iPublishingCommand,
                                              CATNotification     * iNotification,
                                              CATCommandClientData  iUsefulData)
{
  cout << "CAAAfrProgressTaskSampleCmd::ClickCompute" << endl;

  CATTaskController  Task ;

  // The command implements CATIProgressTask
  CATIProgressTask * pIProgressTask = NULL ;
  HRESULT rc = QueryInterface(IID_CATIProgressTask,(void**)& pIProgressTask);

  if ( SUCCEEDED(rc) && (NULL != _pInterruptTask ) )
  {
     // no data for the PerformTask method, the last argument is NULL
      if ( CATDlgCheck == _pInterruptTask->GetState() )
      {
         Task.Schedule(pIProgressTask,TRUE,NULL);
      }else
      {
         Task.Schedule(pIProgressTask,FALSE,NULL);
      }

      pIProgressTask->Release();
      pIProgressTask = NULL ;
  }

}

//---------------------------------------------------------------------------

void CAAAfrProgressTaskSampleCmd::ClickClose(CATCommand           * iPublishingCommand,
                                          CATNotification      * iNotification,
                                          CATCommandClientData   iUsefulData)
{
  cout << "CAAAfrProgressTaskSampleCmd::ClickClose" << endl;

  SetVisibility(CATDlgHide);
                         
  //Suicide 
  RequestDelayedDestruction();

}

//-------------------------------------------------------------------------------

HRESULT CAAAfrProgressTaskSampleCmd::PerformTask (CATIProgressTaskUI  * iUI, void * iUserData)
{
    if ( NULL == iUI ) return E_FAIL ;

    // There are 100 steps for the task
    int min = 1 ;
    int max = 1000 ;
    iUI->SetRange(min,max);
    
    for ( int i= min ; i <= max ; i++)
    {
        iUI->SetProgress(i);

        // Create the comment for the i step
        CATUnicodeString usMessage ;
        CATUnicodeString usParam[1] ;
        usParam[0].BuildFromNum(i);

        usMessage = CATMsgCatalog::BuildMessage("CAAAfrProgressTaskSampleCmd",
                                        "ProgressTaskUI.CommentRuntime",usParam,1,
                                        "Step ...");

        iUI->SetComment(usMessage);

        // begin of the step'simulation 
        for ( int j= 0 ; j<= 5000000 ; j++)
        {
            double k = 24.25 * (double) j ;
        }
        // end of the step'simulation 

        // Test if the Cancel button has been pushed
        CATBoolean interrupt ;
        if ( S_OK != iUI->IsInterrupted(&interrupt) || (TRUE == interrupt) )
        {
            return E_FAIL ;
        }
    }

    return S_OK ;
}

//-------------------------------------------------------------------------------

HRESULT CAAAfrProgressTaskSampleCmd::GetCatalogName (CATString * oCatalogName)
{
    if ( NULL == oCatalogName ) return E_FAIL ;

    // The same NLS file as the current command
    *oCatalogName = CATString("CAAAfrProgressTaskSampleCmd");
    return S_OK ;
}

//-------------------------------------------------------------------------------

HRESULT CAAAfrProgressTaskSampleCmd::GetIcon(CATString  * oIcon) 
{
    if ( NULL == oIcon ) return E_FAIL ;

    // See in the CNext/resources/graphic/icones/normal directory
    *oIcon = CATString("I_CAAProgressClock");
    return S_OK ;
}

//-------------------------------------------------------------------------------

void CAAAfrProgressTaskSampleCmd::EditorClose(CATCallbackEvent  iEvent, 
                                              void            * iFrom,
                                              CATNotification * iNotification,
                                              CATSubscriberData iClientData,
                                              CATCallback       iCallBack ) 
{
  if ( _pEditor == iFrom )
   {
   
      // Now this extension will receive any message.
      //
      ::RemoveSubscriberCallbacks(this,CATFrmLayout::GetCurrentLayout());

      // Suicide
      RequestDelayedDestruction();

      _pEditor = NULL ; 
   }
}
