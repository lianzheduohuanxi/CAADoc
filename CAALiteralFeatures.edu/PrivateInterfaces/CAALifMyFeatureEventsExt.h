//  COPYRIGHT DASSAULT SYSTEMES  1994 2000

#ifndef CAALifMyFeatureEventsExt_H
#define CAALifMyFeatureEventsExt_H

// Local Framework
//#include "CAALifBasis.h"

#include "CATBaseUnknown.h"

// System
#include "CATInterfaceEvents.h"

class CATICkeParm_var;

// Implements CAAIMyFeatureEvents  

class CAALifMyFeatureEventsExt : public CATBaseUnknown
{
public:

   CATDeclareClass;

   CAALifMyFeatureEventsExt ();
   
   virtual ~CAALifMyFeatureEventsExt ();

   // Method called to detect all parameter modifications
   virtual void Observe  (const CATICkeParm_var &iParameterToObserve);

   // Method called each time a parameter is deleted 
   virtual void OnDeleteEvent (CATCallbackEvent iEvent,
      void* iFrom,
      CATNotification* iNotification,
      CATSubscriberData iInfo,
      CATCallback iCallback);

   // Method called each time a parameter value has changed
   virtual void OnChangeValueEvent (CATCallbackEvent iEvent,
      void* iFrom,
      CATNotification* iNotification,
      CATSubscriberData iInfo,
      CATCallback iCallback);

   // Method called each time a visualisation aspect changed
   virtual void OnChangeVisuEvent (CATCallbackEvent iEvent,
      void* iFrom,
      CATNotification* iNotification,
      CATSubscriberData iInfo,
      CATCallback iCallback);
 
   // Delete events
   virtual void Suppress (const CATICkeParm_var &iParameterToObserve);

   // Initialize the events data.
   virtual void Init ();

   virtual void GetData( int& oChangeValue, int& oChangeVisu, int& oNbDelete);

   // Example of personal data
   // Counts the number of "change value" events received
   int nbchangevalue;

   // Counts the number of "change visu" events received
   int nbchangevisu;

   // Counts the number of "delete" events received
   int nbdelete;
 
};
#endif
