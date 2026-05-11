// COPYRIGHT DASSAULT SYSTEMES 2006

// Local Framework
#include "CAABasicAuthenticationPanelWindow.h"

// Dialog Framework
#include "CATDlgPushButton.h"          // Dialog's object
#include "CATBasicAuthenticationPanel.h"

#include "CATMsgCatalog.h"             // NLS Message
#include "CATInteractiveApplication.h" // The class application
#include "CATDlgGridConstraints.h"     // To have easy Dialog's object alignment

// C++ Standard library
#include "iostream.h"

//--------------------------------------------------------------------------------------
CAABasicAuthenticationPanelWindow::CAABasicAuthenticationPanelWindow
                                   (CATInteractiveApplication * iParentCommand,
                                    const CATString           & iDialogboxId,
                                    CATDlgStyle                 iDialogBoxStyle)
                                  :CATDlgDocument(iParentCommand, iDialogboxId, iDialogBoxStyle),
                                   _pCAABasicApplication(iParentCommand)
{
  cout << "------- Basic Authentication Panel constructor -------" << endl;

  // Don't construct any Dialog's Object child in the constructor 
  // Use the Build Method to do this.

}

//--------------------------------------------------------------------------------------

CAABasicAuthenticationPanelWindow::~CAABasicAuthenticationPanelWindow()
{ 
  cout << "CAABasicAuthenticationPanelWindow::~CAABasicAuthenticationPanelWindow" << endl; 

  // All Dialog's Object children of this Window are
  // automatically deleted.

  _pCAABasicApplication = NULL ;
}

//--------------------------------------------------------------------------------------

void CAABasicAuthenticationPanelWindow::Build()
{
  cout << "CAABasicAuthenticationPanelWindow::Build" << endl;

  //---------------------------------------------------------------
  // All Dialog's object whose pointer are not kept as data member. 
  // while we don't have need after the new operation.
  //---------------------------------------------------------------
  CATDlgPushButton            *pDismiss = NULL;
  CATBasicAuthenticationPanel *pPanel = NULL;

  pDismiss = new CATDlgPushButton(this, "DismissId");
  pDismiss->SetGridConstraints(2,2,1,1,CATGRID_CENTER );

  CATUnicodeString label, value;
  pPanel = new CATBasicAuthenticationPanel();
  pPanel->SetTitle("Basic Authentication Panel");
  pPanel->AddLogo("Logon-3DS");
  if (! GetResourceValueFromKey ("Line1.Label", label)) label = "Line1 : label not found";
  if (! GetResourceValueFromKey ("Line1.Value", value)) value = "Line1 : value not found";
  pPanel->AddLabelAndEditor(label, value, 20, 0);
  if (! GetResourceValueFromKey ("Line2.Label", label)) label = "Line2 : label not found";
  pPanel->AddLabelAndEditor(label, "", 20, TRUE);
  pPanel->AddSeparator();
  if (! GetResourceValueFromKey ("Line3.Label", label)) label = "Line3 : label not found";
  pPanel->AddLabelAndEditor(label, "");

  CATUnicodeString foo0, foo1;
  int result = pPanel->WaitAuthentication(foo0, foo1);
  cout << result << " = CATBasicAuthenticationPanel->WaitAuthentication("
       << foo0.ConvertToChar() << ", " << foo1.ConvertToChar() << ")" << endl;

  CATUnicodeString foo[10];
  for (int i=0; i<10; i++)
  {
    pPanel->GetLine(foo[i], i);
    cout << foo[i].ConvertToChar() << " = CATBasicAuthenticationPanel->GetLine(" << i << ")" << endl;
  }

  pPanel->Release();
  pPanel = NULL;

  //-----------------------------------------------------------------
  // Associate callback functions to the various events which can be
  // triggered by the widgets of the dialog window.
  //-----------------------------------------------------------------
  
  AddAnalyseNotificationCB(pDismiss, pDismiss->GetPushBActivateNotification(),
                           (CATCommandMethod)&CAABasicAuthenticationPanelWindow::Dismiss, NULL);
  AddAnalyseNotificationCB(this, GetWindCloseNotification(),
                           (CATCommandMethod)&CAABasicAuthenticationPanelWindow::Dismiss, NULL);

  cout << "CAABasicAuthenticationPanelWindow::Build End" << endl;
}
                 
//--------------------------------------------------------------------------------------

void CAABasicAuthenticationPanelWindow::Dismiss(CATCommand         * iSendingCommand, 
                                 CATNotification    * iSentNotification, 
                                 CATCommandClientData iUsefulData)
{
  cout << "CAABasicAuthenticationPanelWindow::Dismiss Begin" << endl;

  if ( NULL == iSendingCommand ) return ;
  if ( NULL == _pCAABasicApplication ) return ;

  // -------------------------------------------
  // Application and Window will be soon deleted.
  // --------------------------------------------
  _pCAABasicApplication->Destroy();

  cout << "CAABasicAuthenticationPanelWindow::Dismiss End" << endl;
}
