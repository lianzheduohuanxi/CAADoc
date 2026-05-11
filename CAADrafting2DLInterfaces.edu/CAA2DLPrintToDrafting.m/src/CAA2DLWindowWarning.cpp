// ================================
// COPYRIGHT DASSAULT SYSTEMES 2007
// ================================
#include "CAA2DLWindowWarning.h"

#include "CATDlgNotify.h"
#include "CATApplicationFrame.h"
#include "CATDlgWindow.h"

CAA2DLWindowWarning::CAA2DLWindowWarning(CATDialog *iParent, const CATString & name, const CATUnicodeString & text, CATDlgStyle nStyle)				    
:CATDlgNotify(iParent,name, nStyle|CATDlgNfyOK)
{	
	this->SetText(text);  
	AddAnalyseNotificationCB(this,GetNfyOKNotification(),(CATCommandMethod)&CAA2DLWindowWarning::PushOk, NULL);
  SetVisibility(CATDlgShow);				
}

CAA2DLWindowWarning::~CAA2DLWindowWarning()
{	
}

void CAA2DLWindowWarning::PushOk (CATCommand *sendObject, CATNotification *evt,CATCommandClientData data)
{  
  RequestDelayedDestruction();
}

CAA2DLWindowWarning* CAA2DLWindowCreateMsgBox(const CATString & iName, const CATUnicodeString & iText, CATDlgStyle iStyle)
{
  CATApplicationFrame *frame = CATApplicationFrame::GetApplicationFrame();
  CAA2DLWindowWarning * pMsgBox = NULL;
  if(frame)
  {
    CATDlgWindow *window = frame->GetMainWindow();
    if(window)
      pMsgBox = new CAA2DLWindowWarning(window, iName, iText, iStyle);
  }
  return pMsgBox;
}

