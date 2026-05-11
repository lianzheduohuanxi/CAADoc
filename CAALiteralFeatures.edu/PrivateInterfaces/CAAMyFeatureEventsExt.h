// COPYRIGHT DASSAULT SYSTEMES  1999

#ifndef CAAMyFeatureEventsExt_H
#define CAAMyFeatureEventsExt_H

// module definition
#include "CAALFBasis.h"

// inherit from
#include "CATBaseUnknown.h"

// interface for events
#include "CATInterfaceEvents.h"

// forward
class CATICkeParm_var;

// This class is an extension of an example of feature that wishes to subscribe to parameters events.
// It implements CAAIMyFeatureEvents that is an example of interface 

class ExportedByCAALFBasis CAAMyFeatureEventsExt : public CATBaseUnknown
{
public:

   CATDeclareClass;

   CAAMyFeatureEventsExt () {}

   // this method is called to put all the callbacks on parameters modification
   virtual void Observe  (const CATICkeParm_var &iParameterToObserve);

    // this method is called back when parameter is deleted
   virtual void IfDelete (CATCallbackEvent iEvent,
      void* iFrom,
      CATNotification* iNotification,
      CATSubscriberData iInfo,
      CATCallback iCallback);

   // this method is called back when parameter value has changed
   virtual void IfChangeValue (CATCallbackEvent iEvent,
      void* iFrom,
      CATNotification* iNotification,
      CATSubscriberData iInfo,
      CATCallback iCallback);

   // this method is called back when visualisation of the parameter has changed
   virtual void IfChangeVisu (CATCallbackEvent iEvent,
      void* iFrom,
      CATNotification* iNotification,
      CATSubscriberData iInfo,
      CATCallback iCallback);
 
   // To suppress events
   virtual void Suppress (const CATICkeParm_var &iParameterToObserve);

  // this counts the number of change value events received
   static int nbchangevalue;

   // this counts the number of change visu events received
   static int nbchangevisu;

   // this counts the number of delete events received
   static int nbdelete;

 
};
#endif
