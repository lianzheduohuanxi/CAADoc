// COPYRIGHT DASSAULT SYSTEMES 1999
#include "CAAVisManagerWindowDeleteNotif.h"

//-------------------------------------------------------------------------------
CATImplementClass(CAAVisManagerWindowDeleteNotif,Implementation,CATNotification,NULL);

//-------------------------------------------------------------------------------

CAAVisManagerWindowDeleteNotif::CAAVisManagerWindowDeleteNotif() 
:CATNotification(CATNotificationDeleteOn)
{
   // We use the CATNotificationDeleteOn parameter to say that we want this 
   // notification to be automatically
   // delete at the end of the next transaction 
}

//-------------------------------------------------------------------------------

CAAVisManagerWindowDeleteNotif::~CAAVisManagerWindowDeleteNotif()
{
}

//-------------------------------------------------------------------------------
