// COPYRIGHT DASSAULT SYSTEMES 1999
#include "CAAVisManagerWindowActivateNotif.h"

CATImplementClass(CAAVisManagerWindowActivateNotif,Implementation,CATNotification,NULL);

//-------------------------------------------------------------------------------

CAAVisManagerWindowActivateNotif::CAAVisManagerWindowActivateNotif() 
: CATNotification(CATNotificationDeleteOn)
{
   // We use the CATNotificationDeleteOn parameter to say that we want this 
   // notification to be automatically
   // delete at the end of the next transaction
   //
}

//-------------------------------------------------------------------------------

CAAVisManagerWindowActivateNotif::~CAAVisManagerWindowActivateNotif()
{
}

//-------------------------------------------------------------------------------
