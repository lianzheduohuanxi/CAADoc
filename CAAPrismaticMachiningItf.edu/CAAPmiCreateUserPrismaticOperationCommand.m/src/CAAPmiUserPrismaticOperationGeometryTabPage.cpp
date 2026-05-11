//===================================================================
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
//===================================================================
#include "CAAPmiUserPrismaticOperationGeometryTabPage.h"
 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIMfgGeometryTabPage.h"
TIE_CATIMfgGeometryTabPage( CAAPmiUserPrismaticOperationGeometryTabPage);

CATBeginImplementClass (CAAPmiUserPrismaticOperationGeometryTabPage,CodeExtension,CATBaseUnknown,UserDrilling );
CATAddClassExtension   (UserPocketing);
CATAddClassExtension   (UserProfileContouring);
CATAddClassExtension   (UserCircularMilling);
CATEndImplementClass   (CAAPmiUserPrismaticOperationGeometryTabPage);
 
//-----------------------------------------------------------------------------
// CAAPmiUserPrismaticOperationGeometryTabPage : constructor
//-----------------------------------------------------------------------------
CAAPmiUserPrismaticOperationGeometryTabPage::CAAPmiUserPrismaticOperationGeometryTabPage():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAPmiUserPrismaticOperationGeometryTabPage : destructor
//-----------------------------------------------------------------------------
CAAPmiUserPrismaticOperationGeometryTabPage::~CAAPmiUserPrismaticOperationGeometryTabPage()
{
}
 
//-----------------------------------------------------------------------------
// Implements CATIMfgGeometryTabPage::IsGeometryTabPageAvailable
//-----------------------------------------------------------------------------
HRESULT CAAPmiUserPrismaticOperationGeometryTabPage::IsGeometryTabPageAvailable (int & oIsAvailable)
{
    oIsAvailable = 1;
   return S_OK;
}

