// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CAASysBurglar.h"
#include "CAASysAlarm.h"

//-----------------------------------------------------------------------

CAASysBurglar::CAASysBurglar(char * iBurglarName) 
{
  _pAlarm=NULL;

  // Keep the name of the alarm place  
  if ( NULL != iBurglarName )
  {
     _pBurglarName = new char [strlen(iBurglarName)+1];
     strcpy(_pBurglarName,iBurglarName);
  }else
  {
      _pBurglarName = new char [15];
      strcpy(_pBurglarName,"DefaultBurglar");
  }

  printf("Burglar %s is alive.\n", _pBurglarName);
}

//-----------------------------------------------------------------------

CAASysBurglar::~CAASysBurglar() 
{
  if ( NULL != _pAlarm) 
  {
    ::RemoveSubscriberCallbacks(this, _pAlarm);
    _pAlarm=NULL;
  };
  
  printf("Burglar %s is dead.\n", _pBurglarName);

  delete [] _pBurglarName ;
  _pBurglarName= NULL  ;
}

//-----------------------------------------------------------------------

void CAASysBurglar::Approach(CAASysAlarm *iAlarm) 
{
  if ( iAlarm !=  _pAlarm )
  {
     if ( NULL != _pAlarm) 
     {
       
        ::RemoveSubscriberCallbacks(this, _pAlarm);
     }

     _pAlarm=iAlarm;
  
     if ( NULL !=  iAlarm )
     {
        // I want to be prevent when the alarm will start to ring.
        CATCallback idCB ;
        idCB = ::AddCallback(this,
                   iAlarm,
                   "CAASysRingNotification",
                   (CATSubscriberMethod)&CAASysBurglar::RunAway,
                   NULL);
        
        // In this sample idCB is not used, but you can keep this value
        // as data member and reused it to make the destruction of this callback:
        // RemoveSubscriberCallbacks(_pAlarm,idCB)

        printf("Burglar %s approachs slowly %s and opens his ears.\n", 
                  _pBurglarName, iAlarm->GetPlace());
     }  
  }

}

//-----------------------------------------------------------------------

void CAASysBurglar::RunAway(CATCallbackEvent  iEventAlarm,
                            void             *iAlarm,
                            CATNotification  *iNotifAlarm,
                            CATSubscriberData iBurglarData,
                            CATCallback       iCallBack ) 
{
  CAASysAlarm * AlarmIsRinging= (CAASysAlarm *)iAlarm;
  
  if ( NULL != AlarmIsRinging )
  { 
      printf("Burglar %s run away %s and very quickly.\n", 
                _pBurglarName, AlarmIsRinging->GetPlace());
  }
}

