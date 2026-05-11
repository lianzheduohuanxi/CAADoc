//===================================================================
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
//===================================================================
#include "CAAPmiUserPrismaticOperationMacrosTabPage.h"
 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIMfgMacrosTabPage.h"
TIE_CATIMfgMacrosTabPage( CAAPmiUserPrismaticOperationMacrosTabPage);

CATBeginImplementClass (CAAPmiUserPrismaticOperationMacrosTabPage,CodeExtension,CATBaseUnknown,UserDrilling );
CATAddClassExtension   (UserPocketing);
CATAddClassExtension   (UserProfileContouring);
CATAddClassExtension   (UserCircularMilling);
CATEndImplementClass   (CAAPmiUserPrismaticOperationMacrosTabPage);
 
//-----------------------------------------------------------------------------
// CAAPmiUserPrismaticOperationMacrosTabPage : constructor
//-----------------------------------------------------------------------------
CAAPmiUserPrismaticOperationMacrosTabPage::CAAPmiUserPrismaticOperationMacrosTabPage():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAPmiUserPrismaticOperationMacrosTabPage : destructor
//-----------------------------------------------------------------------------
CAAPmiUserPrismaticOperationMacrosTabPage::~CAAPmiUserPrismaticOperationMacrosTabPage()
{
}
 
//-----------------------------------------------------------------------------
// Implements CATIMfgMacrosTabPage::IsMacrosTabPageAvailable
//-----------------------------------------------------------------------------
HRESULT CAAPmiUserPrismaticOperationMacrosTabPage::IsMacrosTabPageAvailable (int & oIsAvailable)
{
   oIsAvailable = 0;
   return S_OK;
}

