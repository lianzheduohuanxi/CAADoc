//===================================================================
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
//===================================================================
#include "CAAPmiUserPrismaticOperationMacroEditorActivity.h"
 
#include "CATDlgFrame.h"

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIMfgMacroEditorActivity.h"
TIE_CATIMfgMacroEditorActivity( CAAPmiUserPrismaticOperationMacroEditorActivity);

CATBeginImplementClass (CAAPmiUserPrismaticOperationMacroEditorActivity,CodeExtension,CATBaseUnknown,UserDrilling );
CATAddClassExtension   (UserPocketing);
CATAddClassExtension   (UserProfileContouring);
CATAddClassExtension   (UserCircularMilling);
CATEndImplementClass   (CAAPmiUserPrismaticOperationMacroEditorActivity);
 
//-----------------------------------------------------------------------------
// CAAPmiUserPrismaticOperationMacroEditorActivity : constructor
//-----------------------------------------------------------------------------
CAAPmiUserPrismaticOperationMacroEditorActivity::CAAPmiUserPrismaticOperationMacroEditorActivity():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAPmiUserPrismaticOperationMacroEditorActivity : destructor
//-----------------------------------------------------------------------------
CAAPmiUserPrismaticOperationMacroEditorActivity::~CAAPmiUserPrismaticOperationMacroEditorActivity()
{
}
 
//-----------------------------------------------------------------------------
// Implements CATIMfgMacroEditorActivity::GetMainPanelEditor
//-----------------------------------------------------------------------------
HRESULT CAAPmiUserPrismaticOperationMacroEditorActivity::GetMainPanelEditor (CATDialog * iFather , CATDlgFrame*&  oFrame , CATDlgStyle  iStyle)
{

   return S_OK;
}

