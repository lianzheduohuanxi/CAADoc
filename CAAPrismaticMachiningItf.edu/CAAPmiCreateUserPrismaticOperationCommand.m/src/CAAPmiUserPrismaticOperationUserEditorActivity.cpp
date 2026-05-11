//===================================================================
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
//===================================================================
#include "CAAPmiUserPrismaticOperationUserEditorActivity.h"
 
#include "CATDlgFrame.h"

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIMfgUserEditorActivity.h"
TIE_CATIMfgUserEditorActivity( CAAPmiUserPrismaticOperationUserEditorActivity);

//CATImplementClass( CAAPmiUserPrismaticOperationUserEditorActivity,CodeExtension,CATBaseUnknown,UserDrilling );
CATBeginImplementClass (CAAPmiUserPrismaticOperationUserEditorActivity,CodeExtension,CATBaseUnknown,UserDrilling );
CATAddClassExtension   (UserPocketing);
CATAddClassExtension   (UserProfileContouring);
CATAddClassExtension   (UserCircularMilling);
CATEndImplementClass   (CAAPmiUserPrismaticOperationUserEditorActivity);
 
//-----------------------------------------------------------------------------
// CAAPmiUserPrismaticOperationUserEditorActivity : constructor
//-----------------------------------------------------------------------------
CAAPmiUserPrismaticOperationUserEditorActivity::CAAPmiUserPrismaticOperationUserEditorActivity():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAPmiUserPrismaticOperationUserEditorActivity : destructor
//-----------------------------------------------------------------------------
CAAPmiUserPrismaticOperationUserEditorActivity::~CAAPmiUserPrismaticOperationUserEditorActivity()
{
}
 
//-----------------------------------------------------------------------------
// Implements CATIMfgUserEditorActivity::GetMainPanelEditor
//-----------------------------------------------------------------------------
HRESULT CAAPmiUserPrismaticOperationUserEditorActivity::GetMainPanelEditor (CATDialog * iFather , CATDlgFrame*&  oFrame , CATDlgStyle  iStyle)
{

   return S_OK;
}

