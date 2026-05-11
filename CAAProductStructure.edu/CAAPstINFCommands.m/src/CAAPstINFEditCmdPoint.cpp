// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAPstINFEditCmdPoint.h"
#include "CAAPstINFEditDlgPoint.h"
#include "CAAIPstINFPoint.h"

// ApplicationFrame Framework
#include "CATApplicationFrame.h"

// Others
#include "iostream.h"

//----------------------------------------------------------------------------

CAAPstINFEditCmdPoint::CAAPstINFEditCmdPoint(CAAIPstINFPoint *piEdit)
                             : CATCommand (NULL,"PointEditCommandId"),
	     	                   _piPstINFPointEdit(piEdit),_pDialogPoint(NULL)
{
  cout << "***** CAAPstINFEditCmdPoint::CAAPstINFEditCmdPoint" << endl;   
  
  // This command is set exclusive; by default a CATCommand is undefined
  RequestStatusChange(CATCommandMsgRequestExclusiveMode);

  if ( NULL != _piPstINFPointEdit) 
  {
     _piPstINFPointEdit -> AddRef();
  }
}

//----------------------------------------------------------------------------

CAAPstINFEditCmdPoint::~CAAPstINFEditCmdPoint()
{
  cout << "*****CAAPstINFEditCmdPoint::CAAPstINFEditCmdPoint" << endl; 

  if ( NULL != _pDialogPoint )
  {   
     _pDialogPoint -> RequestDelayedDestruction();
     _pDialogPoint = NULL ;
  }

  if (NULL != _piPstINFPointEdit) 
  {
     _piPstINFPointEdit -> Release();
     _piPstINFPointEdit = NULL ;
  }
}

//----------------------------------------------------------------------------
CATStatusChangeRC CAAPstINFEditCmdPoint::Activate(CATCommand *pCmd,
												  CATNotification *pNotification)
{
  cout << "*****CAAPstINFEditCmdPoint::Activate" << endl;

  if (NULL == _pDialogPoint)
  {
    // Creates the point dialog box and builds it

    // Style of the point dialog box
    CATDlgStyle style = CATDlgGridLayout| CATDlgWndBtnOKCancelPreview ;
                                       
    // Identifier for the file resource
    CATString idDialogBox ("CAAPstINFPointEditDlgId");

    // Parent dialog of this point dialog box 
    // This dialog is the dialog object dedicated to the document
    CATApplicationFrame *pFrame = CATApplicationFrame::GetFrame() ;
    if ( NULL != pFrame )
    {
       CATDialog *pParent = pFrame -> GetMainWindow() ;

       if ( NULL != pParent )
       {
          // Instantiates the Point Dialog Box
          _pDialogPoint = new CAAPstINFEditDlgPoint(pParent, 
			                                        idDialogBox,
													style,
													_piPstINFPointEdit);
   
          // Sets callbacks. CloseBox is called when the end user clicks 
          // OK, Cancel or Close in the point dialog box because these
          // 3 actions close the box. 
          //
          // It receives this notification because it is the current command:
          // the notification sent to the MainWindow is sent to the command selector
          // which sends it to the current command. 
          AddAnalyseNotificationCB(_pDialogPoint, 
                                   _pDialogPoint -> GetWindCloseNotification(),
                                   (CATCommandMethod)&CAAPstINFEditCmdPoint::CloseBox,
                                   NULL);

          // Creates the dialog objects
          _pDialogPoint -> Build();
        }
     }
   }

   if ( NULL != _pDialogPoint) 
   {
      _pDialogPoint -> SetVisibility(CATDlgShow);
   }

   return (CATStatusChangeRCCompleted) ;
}

//----------------------------------------------------------------------------

CATStatusChangeRC CAAPstINFEditCmdPoint::Desactivate(CATCommand *pPublisher,
                                                     CATNotification *pNotification)
{
   cout << "*****CAAPstINFEditPointCmd::Desactivate" << endl;
  
   if ( NULL != _pDialogPoint) 
   {
      _pDialogPoint -> SetVisibility(CATDlgHide);
   }
   return (CATStatusChangeRCCompleted) ;
}

//----------------------------------------------------------------------------

CATStatusChangeRC CAAPstINFEditCmdPoint::Cancel(CATCommand *pPublisher,
                                                CATNotification *pNotification)
{
  cout << "*****CAAPstINFEditCmdPoint::Cancel" << endl;
  
  if ( NULL != _pDialogPoint) 
  {
     _pDialogPoint -> SetVisibility(CATDlgHide);
  }
  
  RequestDelayedDestruction();  

  return (CATStatusChangeRCCompleted) ;
}

//----------------------------------------------------------------------------

void CAAPstINFEditCmdPoint::CloseBox (CATCommand *pPublisher, 
                                      CATNotification *pNotification,
                                      CATCommandClientData usefulData)
{
   cout << "*****CAAPstINFEditCmdPoint::CloseBox "<< endl ;

   if ( NULL != _pDialogPoint) 
   {
      _pDialogPoint -> SetVisibility(CATDlgHide);
   }

   RequestDelayedDestruction() ;
}
