// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAVisBaseRenderBENotification.h"

CATImplementClass(CAAVisBaseRenderBENotification, Implementation, CATNotification, CATNull);

//-------------------------------------------------------------------------------

CAAVisBaseRenderBENotification::CAAVisBaseRenderBENotification(int iState)
:CATNotification(CATNotificationDeleteOn)
{
   // We use the CATNotificationDeleteOn parameter to say that we want this 
   // notification to be automatically
   // delete at the end of the next transaction (as defines by the System FrameWork).
   //
  _State = iState;
}

//-------------------------------------------------------------------------------

CAAVisBaseRenderBENotification::~CAAVisBaseRenderBENotification()
{
}

//-------------------------------------------------------------------------------

int CAAVisBaseRenderBENotification::GetState()
{
  return _State;
}
