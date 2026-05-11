// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAPriEditSketchNotification.h"

// To declare that the class is a component main class
CATImplementClass(CAAPriEditSketchNotification,Implementation,CATNotification,CATNull);

// The CATNotification base class constructor is called with the
// CATNotificationDeleteOn parameter to state that we want this
// notification to be automatically deleted at the end of the next transaction,
// that is, as soon as the dialog between sending and receiving commands
// is completed.

CAAPriEditSketchNotification::CAAPriEditSketchNotification()
                        : CATNotification(CATNotificationDeleteOn)
{
}

CAAPriEditSketchNotification::~CAAPriEditSketchNotification()
{
}

