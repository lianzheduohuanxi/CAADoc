// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAADegEditor1DeselectedNotification.h"

// To declare that the class is a component main class
CATImplementClass(CAADegEditor1DeselectedNotification,Implementation,CATNotification,CATNull);

// The CATNotification base class constructor is called with the
// CATNotificationDeleteOn parameter to state that we want this
// notification to be automatically deleted at the end of the next transaction,
// that is, as soon as the dialog between sending and receiving commands
// is completed.

CAADegEditor1DeselectedNotification::CAADegEditor1DeselectedNotification()
                        : CATNotification(CATNotificationDeleteOn)
{
}

CAADegEditor1DeselectedNotification::~CAADegEditor1DeselectedNotification()
{
}

