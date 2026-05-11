// COPYRIGHT DASSAULT SYSTEMES  1999

#ifndef CAAIMyFeatureEvents_H
#define CAAIMyFeatureEvents_H

#include "CAALFBasis.h"

#include "CATBaseUnknown.h"

class CATICkeParm_var;

// OLE
extern IID  ExportedByCAALFBasis IID_CAAIMyFeatureEvents;


class  ExportedByCAALFBasis CAAIMyFeatureEvents : public CATBaseUnknown
{
   CATDeclareInterface;

public:
   
   /** Sets all callbacks
	*/
   virtual void Observe   (const CATICkeParm_var &iParameterToObserve) = 0;
   
   /** Resets all callbacks
	*/
   virtual void Suppress  (const CATICkeParm_var &iParameterToObserve) = 0;


   /** Called when parameter is deleted
    */
    virtual void IfDelete (CATCallbackEvent iEvent,
      void* iFrom,
      CATNotification* iNotification,
      CATSubscriberData iInfo,
      CATCallback iCallback)=0;


  /** Called when parameter value is changed
    */
    virtual void IfChangeValue (CATCallbackEvent iEvent,
      void* iFrom,
      CATNotification* iNotification,
      CATSubscriberData iInfo,
      CATCallback iCallback)=0;

 
   /** Called when parameter visualisation is changed
    */
    virtual void IfChangeVisu (CATCallbackEvent iEvent,
      void* iFrom,
      CATNotification* iNotification,
      CATSubscriberData iInfo,
      CATCallback iCallback)=0;

	/** Initialize the events data.
	*/
   virtual void Init () = 0;


};

CATDeclareHandler(CAAIMyFeatureEvents,CATInterfaceEvents);

#endif
