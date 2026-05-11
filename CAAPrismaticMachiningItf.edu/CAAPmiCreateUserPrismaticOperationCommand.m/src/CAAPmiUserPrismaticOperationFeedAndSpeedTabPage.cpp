//===================================================================
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
//===================================================================
#include "CAAPmiUserPrismaticOperationFeedAndSpeedTabPage.h"
 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIMfgFeedAndSpeedTabPage.h"
TIE_CATIMfgFeedAndSpeedTabPage( CAAPmiUserPrismaticOperationFeedAndSpeedTabPage);

CATBeginImplementClass (CAAPmiUserPrismaticOperationFeedAndSpeedTabPage,CodeExtension,CATBaseUnknown,UserDrilling );
CATAddClassExtension   (UserPocketing);
CATAddClassExtension   (UserProfileContouring);
CATAddClassExtension   (UserCircularMilling);
CATEndImplementClass   (CAAPmiUserPrismaticOperationFeedAndSpeedTabPage);

//-----------------------------------------------------------------------------
// CAAPmiUserPrismaticOperationFeedAndSpeedTabPage : constructor
//-----------------------------------------------------------------------------
CAAPmiUserPrismaticOperationFeedAndSpeedTabPage::CAAPmiUserPrismaticOperationFeedAndSpeedTabPage():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAPmiUserPrismaticOperationFeedAndSpeedTabPage : destructor
//-----------------------------------------------------------------------------
CAAPmiUserPrismaticOperationFeedAndSpeedTabPage::~CAAPmiUserPrismaticOperationFeedAndSpeedTabPage()
{
}
 
//-----------------------------------------------------------------------------
// Implements CATIMfgFeedAndSpeedTabPage::IsFeedAndSpeedTabPageAvailable
//-----------------------------------------------------------------------------
HRESULT CAAPmiUserPrismaticOperationFeedAndSpeedTabPage::IsFeedRateTabPageAvailable (int & oIsAvailable)
{
    oIsAvailable = 0;
   return S_OK;
}

