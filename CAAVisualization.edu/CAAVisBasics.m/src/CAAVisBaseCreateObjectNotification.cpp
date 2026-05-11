// COPYRIGHT DASSAULT SYSTEMES 2005

//Local Framework
#include "CAAVisBaseCreateObjectNotification.h"

CATImplementClass(CAAVisBaseCreateObjectNotification, Implementation, CATNotification, CATNull);

//-------------------------------------------------------------------------------

CAAVisBaseCreateObjectNotification::CAAVisBaseCreateObjectNotification(CAAVisObjectType iObjectType)
: CATNotification(CATNotificationDeleteOn)
, _objectType(iObjectType)
{
   // We use the CATNotificationDeleteOn parameter to say that we want this 
   // notification to be automatically
   // delete at the end of the next transaction (as defines by the System FrameWork).
}

//-------------------------------------------------------------------------------

CAAVisBaseCreateObjectNotification::~CAAVisBaseCreateObjectNotification()
{
}

//-------------------------------------------------------------------------------

CAAVisObjectType CAAVisBaseCreateObjectNotification::GetObjectType()
{
  return _objectType;
}
