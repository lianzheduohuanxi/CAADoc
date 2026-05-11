// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAVisBaseManipulatorNotification.h"

CATImplementClass(CAAVisBaseManipulatorNotification, Implementation, CATNotification, CATNull);

//-------------------------------------------------------------------------------

CAAVisBaseManipulatorNotification::CAAVisBaseManipulatorNotification(int iState)
:CATNotification(CATNotificationDeleteOn)
{
   // We use the CATNotificationDeleteOn parameter to say that we want this 
   // notification to be automatically
   // delete at the end of the next transaction (as defines by the System FrameWork).
   //
  _State = iState;
}

//-------------------------------------------------------------------------------

CAAVisBaseManipulatorNotification::~CAAVisBaseManipulatorNotification()
{
}

//-------------------------------------------------------------------------------

int CAAVisBaseManipulatorNotification::GetState()
{
  return _State;
}
