#ifndef CAASysBurglar_H
#define CAASysBurglar_H

// COPYRIGHT DASSAULT SYSTEMES 2000

// ==================================================================================
// Abstract class
// -------------
//
// Class which subscribes to an event 
//
// ==================================================================================


// System Framework
#include "CATBaseUnknown.h"
#include "CATEventSubscriber.h"

class CAASysAlarm;

class CAASysBurglar: public CATBaseUnknown
{
  public:

    // Constructor to create a new burglar with his name.
    CAASysBurglar(char * iBurglarName);

    // Destructor to delete a burglar.
    virtual ~CAASysBurglar();

    // Approch
    // -------
    // To make a burglar act and subscribe to ring alarm event.
    //
    void Approach          (CAASysAlarm *iAlarm);


    // RunAway
    // -------
    // It'a callback to react at a ringing alarm.
    //
    void RunAway          (CATCallbackEvent  iEventAlarm,
                           void             *iAlarm,
                           CATNotification  *iNotifAlarm,
                           CATSubscriberData iBurglarData,
                           CATCallback       iCallBack );


  private:

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysBurglar ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysBurglar(const CAASysBurglar &iObjectToCopy);
  
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysBurglar & operator = (const CAASysBurglar &iObjectToCopy);
  
  private:

    //The alarm associate to the current action of the burglar.
    CAASysAlarm * _pAlarm;

    // The name of the burglar.
    char        * _pBurglarName;
};

#endif
