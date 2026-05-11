// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAASysAlarm.h"
#include "CAASysRingNotification.h"

//System Framework : to send a notification
#include "CATCallbackManager.h"

//----------------------------------------------------------------------------

CATImplementClass(CAASysAlarm, Implementation, CATBaseUnknown, CATNull);

//----------------------------------------------------------------------------

CAASysAlarm::CAASysAlarm(char * iAlarmPlaceName) 
{
  // Keep the name of the alarm place  
  if ( NULL != iAlarmPlaceName )
  {
     _pAlarmPlaceName = new char [strlen(iAlarmPlaceName)+1];
     strcpy(_pAlarmPlaceName,iAlarmPlaceName);
  }else
  {
      _pAlarmPlaceName = new char [13];
      strcpy(_pAlarmPlaceName,"DefaultPlace");
  }

  printf("Alarm %s is created.\n", _pAlarmPlaceName);
}

//----------------------------------------------------------------------------

CAASysAlarm::~CAASysAlarm()
{

  printf("Alarm %s is deleted.\n", _pAlarmPlaceName);

  if ( NULL != _pAlarmPlaceName )
  {
     delete [] _pAlarmPlaceName ;
     _pAlarmPlaceName = NULL ;
  }
}

//---------------------------------------------------------------------------

void CAASysAlarm::StartRinging() 
{
  printf("Alarm %s starts ringing.\n", _pAlarmPlaceName);
 
  CATCallbackManager * pCBManager = ::GetDefaultCallbackManager(this) ;
  if ( NULL != pCBManager )
  {
     CAASysRingNotification * pNotification = new CAASysRingNotification();
     pCBManager->DispatchCallbacks(pNotification, this);
     pNotification->Release();
  }
}

//---------------------------------------------------------------------------

char *CAASysAlarm::GetPlace() 
{
  return(_pAlarmPlaceName);
}
