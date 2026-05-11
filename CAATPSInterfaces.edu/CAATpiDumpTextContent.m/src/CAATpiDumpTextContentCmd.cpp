// COPYRIGHT DASSAULT SYSTEMES 2009
//=============================================================================
//
// CAATpiDumpTextContentCmd
//

//---------------------------------------------- Include File of this extension
#include "CAATpiDumpTextContentCmd.h"

//---------------------------------------------------------------------- System
#include "CATCreateExternalObject.h"
#include "CATUnicodeString.h"
#include "CATUnicodeChar.h"
#include "CATMsgCatalog.h"
#include "CATI18NTypes.h"

//--------------------------------------------------------------- Visualization
#include "CATPathElement.h"

//------------------------------------------------------------ ApplicationFrame
#include "CATApplicationFrame.h"

//---------------------------------------------------------------- DialogEngine
#include "CATPathElementAgent.h"
#include "CATDlgDialog.h"
#include "CATDlgEditor.h"
#include "CATDialogState.h"

//------------------------------------------------------------ CATTPSInterfaces
#include "CATITPS.h"
#include "CATITPSTextContent.h"

CATCreateClass (CAATpiDumpTextContentCmd);
CATString catalogName = "CAATpiDumpTextContentCmd";	

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAATpiDumpTextContentCmd::CAATpiDumpTextContentCmd ()
: CATStateCommand ("CAATpiDumpTextContentCmd", CATDlgEngRepeat),
_pAcquisitionAgent (NULL),
_pFrame (NULL),
_pEditor (NULL)
{}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAATpiDumpTextContentCmd::~CAATpiDumpTextContentCmd ()
{
  if (_pAcquisitionAgent)
  {
    _pAcquisitionAgent->RequestDelayedDestruction();
    _pAcquisitionAgent = NULL;
  }
  if (_pFrame)
  {
    _pFrame->RequestDelayedDestruction();
    _pFrame = NULL;
  }
  _pEditor = NULL;
}


//-----------------------------------------------------------------------------
// BuildGraph
//-----------------------------------------------------------------------------
void CAATpiDumpTextContentCmd::BuildGraph ()
{
  _pAcquisitionAgent = new CATPathElementAgent("TPSSelection");
  _pAcquisitionAgent->AddElementType("CATITPS");

  CATDialogState * State0 = GetInitialState("State0");
  State0->AddDialogAgent(_pAcquisitionAgent);

  AddTransition(State0, NULL,
    IsOutputSetCondition(_pAcquisitionAgent),
    Action((ActionMethod)& CAATpiDumpTextContentCmd::DumpTextContentOnSelection));
}

//-----------------------------------------------------------------------------
// BuildGraph
//-----------------------------------------------------------------------------
CATStatusChangeRC CAATpiDumpTextContentCmd::Activate(CATCommand *,CATNotification *)
{
  if (!_pFrame) // premier passage
  {
    _pFrame = new CATDlgDialog((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(), "DumpTextContent", CATDlgWndNoButton);
    _pFrame->AddResourcePath(catalogName, "DumpTextContent");
    _pEditor = new CATDlgEditor(_pFrame, "Editor", CATDlgEdtReadOnly | CATDlgEdtMultiline);
    _pFrame->Attach4Sides(_pEditor);
    _pEditor->SetVisibleTextWidth(40);
    _pEditor->SetVisibleTextHeight(5);
    _pFrame->SetVisibility(CATDlgShow);
    AddAnalyseNotificationCB(_pFrame, _pFrame->GetWindCloseNotification(), (CATCommandMethod) &CAATpiDumpTextContentCmd::MyClose, NULL);
  }
  return CATStatusChangeRCCompleted;
}

//-----------------------------------------------------------------------------
// MyClose
//-----------------------------------------------------------------------------
void CAATpiDumpTextContentCmd::MyClose(CATCommand * iCommand, CATNotification * iNotif, CATCommandClientData iData)
{
  RequestDelayedDestruction();
}

//-----------------------------------------------------------------------------
// CreateWeldOnSelection
//-----------------------------------------------------------------------------
boolean CAATpiDumpTextContentCmd::DumpTextContentOnSelection (void * ipData)
{
  _pEditor->ClearLine();

  CATPathElement * pPath = _pAcquisitionAgent->GetValue();
  if (!pPath)
    return FALSE;

  CATITPS * pTPS = NULL;
  if (!SUCCEEDED(pPath->Search(IID_CATITPS,(void**) &pTPS)) || !pTPS)
    return FALSE;

  CATUnicodeString TextToDisplay;
  CATITPSTextContent * pTextContent = NULL;
  if (SUCCEEDED(pTPS->QueryInterface(IID_CATITPSTextContent, (void**) &pTextContent)))
  {
    if (FAILED(pTextContent->GetValidationString(TextToDisplay)))
      TextToDisplay = CATMsgCatalog::BuildMessage(catalogName, "NoTextContent1");
    else
      AddHexaDisplayToText(TextToDisplay);
    pTextContent->Release();
    pTextContent = NULL;
  }
  else
    TextToDisplay = CATMsgCatalog::BuildMessage(catalogName, "NoTextContent2");

  _pEditor->SetText(TextToDisplay);

  pTPS->Release();
  pTPS = NULL;

  return (TRUE);
}

void CAATpiDumpTextContentCmd::AddHexaDisplayToText(CATUnicodeString & ioText)
{
  // This method add to the origin Unicode Text the list of its Unicode characters displayed as hexedecimal
  CATUnicodeString TextToAdd = CATMsgCatalog::BuildMessage(catalogName, "DumpAsHexa");
  CATUnicodeString SautDeLigne("\n");
  CATUnicodeString Gap(" ");

  int length = ioText.GetLengthInChar();
  if (!length)return;

  const CATUC2Bytes *buffer = ioText.ConvertToUCChar();
  if (buffer != NULL) 
  {
    TextToAdd += SautDeLigne;
    for (int i = 0; i < length; i++)
    {
      unsigned short iHexa = buffer[i];
      int iInt = iHexa;
      CATUnicodeString Text;
      Text.BuildFromNum(iInt, "%.4x");

      CATUnicodeChar iChar = ioText[(size_t)i];
      CATUnicodeString iString(iChar);

      TextToAdd += iString;   
      TextToAdd += Gap;
      TextToAdd += Text;
      TextToAdd += SautDeLigne;
    }
  }
  ioText += TextToAdd;
}
