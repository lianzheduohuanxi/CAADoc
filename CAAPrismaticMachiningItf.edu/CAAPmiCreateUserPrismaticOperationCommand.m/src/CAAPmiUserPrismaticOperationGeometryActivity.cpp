//===================================================================
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
//===================================================================
#include "CAAPmiUserPrismaticOperationGeometryActivity.h"

#include "CATDlgFrame.h"
 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIMfgGeometryActivity.h"
TIE_CATIMfgGeometryActivity( CAAPmiUserPrismaticOperationGeometryActivity);

CATBeginImplementClass (CAAPmiUserPrismaticOperationGeometryActivity,CodeExtension,CATBaseUnknown,UserDrilling );
CATAddClassExtension   (UserPocketing);
CATAddClassExtension   (UserProfileContouring);
CATAddClassExtension   (UserCircularMilling);
CATEndImplementClass   (CAAPmiUserPrismaticOperationGeometryActivity);
 
//-----------------------------------------------------------------------------
// CAAPmiUserPrismaticOperationGeometryActivity : constructor
//-----------------------------------------------------------------------------
CAAPmiUserPrismaticOperationGeometryActivity::CAAPmiUserPrismaticOperationGeometryActivity():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAPmiUserPrismaticOperationGeometryActivity : destructor
//-----------------------------------------------------------------------------
CAAPmiUserPrismaticOperationGeometryActivity::~CAAPmiUserPrismaticOperationGeometryActivity()
{
}
 
//-----------------------------------------------------------------------------
// Implements CATIMfgGeometryActivity::GetMainPanelEditor
//-----------------------------------------------------------------------------
HRESULT CAAPmiUserPrismaticOperationGeometryActivity::GetMainPanelEditor (CATDialog * iFather , CATDlgFrame*&  oFrame , CATDlgStyle  iStyle)
{

   return S_OK;
}

