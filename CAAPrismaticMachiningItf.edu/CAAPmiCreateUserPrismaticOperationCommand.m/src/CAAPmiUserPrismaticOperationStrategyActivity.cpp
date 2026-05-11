//===================================================================
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
//===================================================================
#include "CAAPmiUserPrismaticOperationStrategyActivity.h"
 
#include "CATDlgFrame.h"

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIMfgStrategyActivity.h"
TIE_CATIMfgStrategyActivity( CAAPmiUserPrismaticOperationStrategyActivity);

CATBeginImplementClass (CAAPmiUserPrismaticOperationStrategyActivity,CodeExtension,CATBaseUnknown,UserDrilling );
CATAddClassExtension   (UserPocketing);
CATAddClassExtension   (UserProfileContouring);
CATAddClassExtension   (UserCircularMilling);
CATEndImplementClass   (CAAPmiUserPrismaticOperationStrategyActivity);

//-----------------------------------------------------------------------------
// CAAPmiUserPrismaticOperationStrategyActivity : constructor
//-----------------------------------------------------------------------------
CAAPmiUserPrismaticOperationStrategyActivity::CAAPmiUserPrismaticOperationStrategyActivity():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAPmiUserPrismaticOperationStrategyActivity : destructor
//-----------------------------------------------------------------------------
CAAPmiUserPrismaticOperationStrategyActivity::~CAAPmiUserPrismaticOperationStrategyActivity()
{
}
 
//-----------------------------------------------------------------------------
// Implements CATIMfgStrategyActivity::GetMainPanelEditor
//-----------------------------------------------------------------------------
HRESULT CAAPmiUserPrismaticOperationStrategyActivity::GetMainPanelEditor (CATDialog * iFather , CATDlgFrame*&  oFrame , CATDlgStyle  iStyle)
{

   return S_OK;
}

