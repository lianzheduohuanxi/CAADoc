// COPYRIGHT DASSAULT SYSTEMES 2003

//Local Framework
#include "CAAAfrMRUSelElementCmd.h"
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
CATCreateClass(CAAAfrMRUSelElementCmd);

//-----------------------------------------------------------------------------

CAAAfrMRUSelElementCmd::CAAAfrMRUSelElementCmd():  
                CATDlgDialog((CATApplicationFrame::GetFrame())->GetMainWindow(),
                "CAAAfrMRUSelElementCmdId",
                CATDlgWndModal|CATDlgWndBtnClose| CATDlgGridLayout)
{
  cout << "constructor CAAAfrMRUSelElementCmd" << endl;  
 
  Build();
}

//-------------------------------------------------------------------------

CAAAfrMRUSelElementCmd::~CAAAfrMRUSelElementCmd()
{
  cout << "destructor CAAAfrMRUSelElementCmd" << endl; 
}

//-------------------------------------------------------------------------
void CAAAfrMRUSelElementCmd::Build()
{
  cout << " CAAAfrMRUSelElementCmd::Build" << endl;

     CAAIAfrMRUManagement * pIAfrMRUManagement = NULL;
     HRESULT rc =::CAAAfrGetMRUManager(IID_CAAIAfrMRUManagement, (void**)&pIAfrMRUManagement);
     if ( SUCCEEDED(rc) )
     {
          CATListOfCATUnicodeString List ;
          pIAfrMRUManagement->GetElementList(List);

          pIAfrMRUManagement->Release();
          pIAfrMRUManagement = NULL ;

          if ( List.Size() >= 1 )
          {
             CATDlgEditor * pEditor = new CATDlgEditor(this, "Editor", CATDlgEdtReadOnly);
             pEditor-> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);

             // The selected element is the first in the list
             // 
             pEditor->SetText(List[1]);
          }

     }

     // subscribes to dialog box's notification in order to terminate the
     // command
     AddAnalyseNotificationCB(this, 
                              GetDiaCLOSENotification(),
                              (CATCommandMethod)&CAAAfrMRUSelElementCmd::CloseBox,
                              NULL);

     AddAnalyseNotificationCB(this, 
                             GetWindCloseNotification(),
                             (CATCommandMethod)&CAAAfrMRUSelElementCmd::CloseBox,
                              NULL);


  SetVisibility(CATDlgShow);
  
}

//---------------------------------------------------------------------------

void CAAAfrMRUSelElementCmd::CloseBox (CATCommand          *iPublisher   , 
                              CATNotification     *iNotification,
                              CATCommandClientData iUsefulData)
{
   cout << "CAAAfrMRUSelElementCmd::CloseBox "<< endl ;

   SetVisibility(CATDlgHide);

   RequestDelayedDestruction() ;
}


