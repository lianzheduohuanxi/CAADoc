// COPYRIGHT DASSAULT SYSTEMES 2000

//======================================================================================
//  Abstract of the sample
//  -----------------------
//  
//  This sample illustrates:
//
//     - Creating an event 
//          -> See the CAASysRingNotification class
//     - Creating an event publisher
//          -> See the CAASysAlarm class
//     - Creating an event subscriber
//          -> See the CAASysBurglar class
//
//  This sample shows how to implement the publish/subscribe design pattern using
//  the example of an event publisher played by an Alarm that can ring  and an 
//  event subscriber played by a burglar that approaches a place where there is 
//  something to steal,but fortunaly protected by an alarm. 
//
//===================================================================================
// How to launch the sample :
// -------------------------
//
//  Type:
//    CAASysCallBack
//
//  Return Code:
//     0 : OK  
//====================================================================================

// Local Framework
#include "CAASysBurglar.h"
#include "CAASysAlarm.h"

//C++ standard library
#include <iostream.h>

int main() 
{

  cout << endl << "The CAASysCallback program begins ...."<< endl<<endl;

  // Creation on an alarm
  CAASysAlarm Alarm("House");
  
  // Creation of a burglar
  CAASysBurglar Burglar("Peter");
  
  // The Burglar approachs the house, but carefully 
  // subscribes at the Ring event 
  Burglar.Approach(&Alarm);
  
  // The alarm starts ringing, so publishes an Ring event. The burglar prevents by
  // its subcribtion run away.
  //
  Alarm.StartRinging();

  cout << endl << "The CAASysCallback program is finished" << endl << endl;
  
  return(0);
}



