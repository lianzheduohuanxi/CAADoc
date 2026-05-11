// COPYRIGHT DASSAULT SYSTEMES 2003

//Local Framework
#include "CAAAfrMRUAddElementCmd.h"
#include "CAAAfrGetMRUManager.h"
#include "CAAIAfrMRUManagement.h"

// ApplicationFrame Framework
#include "CATApplicationFrame.h"

// Dialog Framework
#include "CATDlgEditor.h"
#include "CATDlgGridConstraints.h"

//C++ standard library
#include "iostream.h"

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAAAfrMRUAddElementCmd);

//-----------------------------------------------------------------------------

CAAAfrMRUAddElementCmd::CAAAfrMRUAddElementCmd():  
                CATDlgDialog((CATApplicationFrame::GetFrame())->GetMainWindow(),
                "CAAAfrMRUAddElementCmdId",
                CATDlgWndModal | CATDlgWndBtnOKCancel| CATDlgGridLayout),_pEditor(NULL)
{
  cout << "constructor CAAAfrMRUAddElementCmd" << endl;  

  Build();
}

//-------------------------------------------------------------------------

CAAAfrMRUAddElementCmd::~CAAAfrMRUAddElementCmd()
{
  cout << "destructor CAAAfrMRUAddElementCmd" << endl; 
  _pEditor = NULL ;
}

//-------------------------------------------------------------------------
void CAAAfrMRUAddElementCmd::Build()
{
  cout << " CAAAfrMRUAddElementCmd::Build" << endl;
   
     _pEditor = new CATDlgEditor(this, "Editor");
     _pEditor-> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);

     // subscribes to dialog box's notification in order to terminate the
     // command
     AddAnalyseNotificationCB(this, 
                              GetDiaOKNotification(),
                              (CATCommandMethod)&CAAAfrMRUAddElementCmd::OkCloseBox,
                              NULL);

     AddAnalyseNotificationCB(this, 
                              GetDiaCANCELNotification(),
                              (CATCommandMethod)&CAAAfrMRUAddElementCmd::CloseBox,
                              NULL);

     AddAnalyseNotificationCB(this, 
                             GetWindCloseNotification(),
                             (CATCommandMethod)&CAAAfrMRUAddElementCmd::CloseBox,
                              NULL);

  SetVisibility(CATDlgShow);
  
}

//---------------------------------------------------------------------------

void CAAAfrMRUAddElementCmd::CloseBox (CATCommand          *iPublisher   , 
                              CATNotification     *iNotification,
                              CATCommandClientData iUsefulData)
{
   cout << "CAAAfrMRUAddElementCmd::CloseBox "<< endl ;

   SetVisibility(CATDlgHide);

   RequestDelayedDestruction() ;
}


//---------------------------------------------------------------------------

void CAAAfrMRUAddElementCmd::OkCloseBox (CATCommand          *iPublisher   , 
                              CATNotification     *iNotification,
                              CATCommandClientData iUsefulData)
{
   cout << "CAAAfrMRUAddElementCmd::OkCloseBox "<< endl ;

   if ( NULL != _pEditor)
   {
       CATUnicodeString CurrentText = _pEditor->GetText();

       // Modify the MRU manager

       CAAIAfrMRUManagement * pIAfrMRUManagement = NULL;
       HRESULT rc =::CAAAfrGetMRUManager(IID_CAAIAfrMRUManagement, (void**)&pIAfrMRUManagement);
       if ( SUCCEEDED(rc) )
       {
          pIAfrMRUManagement->AddElement(CurrentText);

          pIAfrMRUManagement->Release();
          pIAfrMRUManagement = NULL ;
       }
   }

   SetVisibility(CATDlgHide);

   RequestDelayedDestruction() ;
}

