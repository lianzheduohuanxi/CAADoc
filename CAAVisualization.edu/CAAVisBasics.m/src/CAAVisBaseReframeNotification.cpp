// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAVisBaseReframeNotification.h"

CATImplementClass(CAAVisBaseReframeNotification, Implementation, CATNotification, CATNull);

//-------------------------------------------------------------------------------

CAAVisBaseReframeNotification::CAAVisBaseReframeNotification()
:CATNotification(CATNotificationDeleteOn)
{
   // We use the CATNotificationDeleteOn parameter to say that we want this 
   // notification to be automatically
   // delete at the end of the next transaction (as defines by the System FrameWork).
   //
}

//-------------------------------------------------------------------------------

CAAVisBaseReframeNotification::~CAAVisBaseReframeNotification()
{
}

