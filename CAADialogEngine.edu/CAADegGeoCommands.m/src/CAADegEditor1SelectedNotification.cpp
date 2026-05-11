// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAADegEditor1SelectedNotification.h"

// To declare that the class is a component main class
CATImplementClass(CAADegEditor1SelectedNotification,Implementation,CATNotification,CATNull);

// The CATNotification base class constructor is called with the
// CATNotificationDeleteOn parameter to state that we want this
// notification to be automatically deleted at the end of the next transaction,
// that is, as soon as the dialog between sending and receiving commands
// is completed.

CAADegEditor1SelectedNotification::CAADegEditor1SelectedNotification()
                        : CATNotification(CATNotificationDeleteOn)
{
}

CAADegEditor1SelectedNotification::~CAADegEditor1SelectedNotification()
{
}

