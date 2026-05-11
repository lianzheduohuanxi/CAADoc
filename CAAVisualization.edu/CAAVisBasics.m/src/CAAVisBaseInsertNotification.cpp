// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAVisBaseInsertNotification.h"

#include <stdlib.h>
#include <malloc.h>

CATImplementClass(CAAVisBaseInsertNotification, Implementation, CATNotification, CATNull);

//-------------------------------------------------------------------------------

CAAVisBaseInsertNotification::CAAVisBaseInsertNotification(const char *iFileName)
:CATNotification(CATNotificationDeleteOn)
{
   // We use the CATNotificationDeleteOn parameter to say that we want this 
   // notification to be automatically
   // delete at the end of the next transaction (as defines by the System FrameWork).
   //

  _pFileName = (char *)malloc((strlen(iFileName)+1) * sizeof(char));
  memset(_pFileName, 0, strlen(iFileName)+1);
  strcpy(_pFileName, iFileName);
}

//-------------------------------------------------------------------------------

CAAVisBaseInsertNotification::~CAAVisBaseInsertNotification()
{
  free(_pFileName);
  _pFileName = NULL;
}

//-------------------------------------------------------------------------------

const char * CAAVisBaseInsertNotification::GetFileName()
{
  return _pFileName;
}
