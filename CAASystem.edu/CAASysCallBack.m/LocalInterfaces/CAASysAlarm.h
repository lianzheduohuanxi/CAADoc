#ifndef CAASysAlarm_H
#define CAASysAlarm_H

// COPYRIGHT DASSAULT SYSTEMES 2000

// ==================================================================================
// Abstract class
// -------------
// Class which publishes an event
//
// ==================================================================================


// System Framework
#include "CATBaseUnknown.h"

class CAASysAlarm: public CATBaseUnknown 
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;
  
  public:
  
    // Create an alarm with the name of the place.
    CAASysAlarm(char * iAlarmPlaceName);

    // to delete notifications.
    virtual ~CAASysAlarm();

    // StartRinging
    // -------------
    // Send a notification to state that the alarm starts ringing
    //
    void StartRinging();


    // GetPlace
    // ---------
    // Returns the place name of the alarm.
    //
    char *GetPlace();

  private:

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysAlarm ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysAlarm(const CAASysAlarm &iObjectToCopy);
  
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysAlarm & operator = (const CAASysAlarm &iObjectToCopy);
  
  private:

    // The name of the place of the alarm
    char                        * _pAlarmPlaceName;


};

#endif
