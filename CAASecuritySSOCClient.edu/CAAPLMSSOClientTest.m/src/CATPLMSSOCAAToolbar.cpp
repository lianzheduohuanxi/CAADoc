#include "CATPLMSSOCAAToolbar.h"
#include <TIE_CATIAfrGeneralWksAddin.h>
#include <CATCreateWorkshop.h>
#include <CATCommandHeader.h>
#include <CATLib.h>

CATImplementClass(CATPLMSSOCAAToolbar, CodeExtension, CATBaseUnknown, SSOGlobalAddinObject);
TIE_CATIAfrGeneralWksAddin(CATPLMSSOCAAToolbar);

CATPLMSSOCAAToolbar::CATPLMSSOCAAToolbar()
{}
CATPLMSSOCAAToolbar::~CATPLMSSOCAAToolbar()
{}

MacDeclareHeader (CATPLMSSOCAAHeader);

void CATPLMSSOCAAToolbar::CreateCommands()
{
  new CATPLMSSOCAAHeader("SSOCAAPanel", "CAAPLMSSOClientTest"  , "TestSSOCAACmd",(void *)NULL);
}

CATCmdContainer * CATPLMSSOCAAToolbar::CreateToolbars()
{
	NewAccess(CATCmdContainer,CATCmdSSOCAAContainer,SSOCAAToolBar);
    NewAccess(CATCmdStarter,CATCmdSSOCAA,SSOLoginBtn);
    SetAccessCommand(CATCmdSSOCAA,"SSOCAAPanel");

	SetAccessChild(CATCmdSSOCAAContainer,CATCmdSSOCAA);
    AddToolbarView(CATCmdSSOCAAContainer,-1,Top);

    return CATCmdSSOCAAContainer;
}

