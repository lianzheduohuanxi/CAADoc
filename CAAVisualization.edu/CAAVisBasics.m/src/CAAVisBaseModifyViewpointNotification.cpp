// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAVisBaseModifyViewpointNotification.h"

CATImplementClass(CAAVisBaseModifyViewpointNotification, Implementation, CATNotification, CATNull);

//-------------------------------------------------------------------------------

CAAVisBaseModifyViewpointNotification::CAAVisBaseModifyViewpointNotification()
:CATNotification(CATNotificationDeleteOn)
{
   // We use the CATNotificationDeleteOn parameter to say that we want this 
   // notification to be automatically
   // delete at the end of the next transaction (as defines by the System FrameWork).
   //
}

//-------------------------------------------------------------------------------

CAAVisBaseModifyViewpointNotification::~CAAVisBaseModifyViewpointNotification()
{
}

