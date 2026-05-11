// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAADlgRemoveNotification.h"

// To declare that the class is a component main class which OM derives from
// CATNotification
CATImplementClass(CAADlgRemoveNotification,Implementation,CATNotification,CATNull);

// The CATNotification base class constructor is called with the
// CATNotificationDeleteOn parameter to state that we want this
// notification to be automatically deleted at the end of the next transaction,
// that is, as soon as the dialog between sending and receiving commands
// is completed.

CAADlgRemoveNotification::CAADlgRemoveNotification()
                        : CATNotification(CATNotificationDeleteOn)
{
}

CAADlgRemoveNotification::~CAADlgRemoveNotification()
{
}

