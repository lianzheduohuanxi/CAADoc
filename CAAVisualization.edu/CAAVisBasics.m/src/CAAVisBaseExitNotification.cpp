// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAVisBaseExitNotification.h"

CATImplementClass(CAAVisBaseExitNotification, Implementation, CATNotification, CATNull);

//-------------------------------------------------------------------------------

CAAVisBaseExitNotification::CAAVisBaseExitNotification()
:CATNotification(CATNotificationDeleteOn)
{
   // We use the CATNotificationDeleteOn parameter to say that we want this 
   // notification to be automatically
   // delete at the end of the next transaction (as defines by the System FrameWork).
   //
}

//-------------------------------------------------------------------------------

CAAVisBaseExitNotification::~CAAVisBaseExitNotification()
{
}

