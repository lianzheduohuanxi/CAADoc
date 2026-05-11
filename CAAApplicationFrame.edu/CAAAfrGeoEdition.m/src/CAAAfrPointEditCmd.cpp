// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAAfrPointEditCmd.h"
#include "CAAAfrPointEditDlg.h"

//Application Frame Framework
#include "CATApplicationFrame.h"

// CAASystem.edu Framework
#include "CAAISysPoint.h" 

//C++ standard libray
#include "iostream.h"

//----------------------------------------------------------------------------

CAAAfrPointEditCmd::CAAAfrPointEditCmd(CAAISysPoint * ipEdit)
             : CATCommand (NULL,"PointEditCommandId") ,
	     	_piSysPointEdit(ipEdit),_pDialogPoint(NULL)
{
  cout << "constructor CAAAfrPointEditCmd" << endl;   
  
  // This command is set exclusive, by default a CATCommand is undefined
  RequestStatusChange(CATCommandMsgRequestExclusiveMode);

  if ( NULL != _piSysPointEdit) 
  {
     _piSysPointEdit -> AddRef();
  }
}

//----------------------------------------------------------------------------

CAAAfrPointEditCmd::~CAAAfrPointEditCmd()
{
  cout << "destructor CAAAfrPointEditCmd" << endl; 

  if ( NULL != _pDialogPoint )
  {   
     _pDialogPoint->RequestDelayedDestruction();
     _pDialogPoint = NULL ;
  }

  if (NULL != _piSysPointEdit) 
  {
     _piSysPointEdit -> Release();
     _piSysPointEdit = NULL ;
  }
}

//----------------------------------------------------------------------------
CATStatusChangeRC CAAAfrPointEditCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAAAfrPointEditCmd::Activate" << endl;

  if ( NULL == _pDialogPoint)
  {
    // Creates the point dialog box and builds it

    // Style of the point dialog box
    CATDlgStyle style = CATDlgGridLayout| CATDlgWndBtnOKCancelPreview ;
                                       
    // Identifier for the file resource
    CATString idDialogBox ("CAAAfrPointEditDlgId");

    // Parent dialog of this point dialog box 
    // This dialog is the dialog object dedicated to the document
    //
    CATApplicationFrame * pFrame = CATApplicationFrame::GetFrame() ;
    if ( NULL != pFrame )
    {
       CATDialog * pParent = pFrame->GetMainWindow() ;

       if ( NULL != pParent )
       {
          // Instantiates the Point Dialog Box
          _pDialogPoint = new CAAAfrPointEditDlg(pParent,idDialogBox,style,_piSysPointEdit);
   
          // Sets callbacks. CloseBox is called when the end user clicks 
          // Ok, Cancel or Close in the point dialog box because these
          // 3 actions close the box. 
          //
          // It receives this notification because it is the current command:
          // the notification sent to the MainWindow is sent to the command selector
          // which sends it to the current command. 
          //
          AddAnalyseNotificationCB(_pDialogPoint, 
                             _pDialogPoint->GetWindCloseNotification(),
                             (CATCommandMethod)&CAAAfrPointEditCmd::CloseBox,
                             NULL);

          // Creates the dialog objects
          _pDialogPoint->Build();
        }
     }
   }

   if ( NULL != _pDialogPoint) 
   {
      _pDialogPoint->SetVisibility(CATDlgShow);
   }

   return (CATStatusChangeRCCompleted) ;
}

//----------------------------------------------------------------------------

CATStatusChangeRC CAAAfrPointEditCmd::Desactivate( CATCommand      *iPublisher,
                                                   CATNotification *iNotification)
{
   cout << " CAAAfrPointEditCmd::Desactivate" << endl;
  
   if ( NULL != _pDialogPoint) 
   {
      _pDialogPoint->SetVisibility(CATDlgHide);
   }
   return (CATStatusChangeRCCompleted) ;
}

//----------------------------------------------------------------------------

CATStatusChangeRC CAAAfrPointEditCmd::Cancel( CATCommand      *iPublisher,
                                              CATNotification *iNotification)
{
  cout << " CAAAfrPointEditCmd::Cancel" << endl;
  
  if ( NULL != _pDialogPoint) 
  {
     _pDialogPoint->SetVisibility(CATDlgHide);
  }
  
  RequestDelayedDestruction();  

  return (CATStatusChangeRCCompleted) ;
}

//----------------------------------------------------------------------------

void CAAAfrPointEditCmd::CloseBox (CATCommand          *iPublisher, 
                                   CATNotification     *iNotification,
                                   CATCommandClientData iUsefulData)
{
   cout << "CAAAfrPointEditCmd::CloseBox "<< endl ;

   if ( NULL != _pDialogPoint) 
   {
      _pDialogPoint->SetVisibility(CATDlgHide);
   }

   RequestDelayedDestruction() ;
}
