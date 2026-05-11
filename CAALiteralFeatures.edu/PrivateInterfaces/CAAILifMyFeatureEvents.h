// COPYRIGHT DASSAULT SYSTEMES  1999

#ifndef CAAILifMyFeatureEvents_H
#define CAAILifMyFeatureEvents_H

#include "CATBaseUnknown.h"

class CATICkeParm_var;

// OLE
#ifndef LOCAL_DEFINITION_FOR_IID
extern IID IID_CAAILifMyFeatureEvents;
#else
extern "C" const IID IID_CAAILifMyFeatureEvents;
#endif

// ========================================================================
//
// ABSTRACT
// --------
//
// Declares the methods to be implemented in CAALifMyEventsExt
//
// ========================================================================

class  CAAILifMyFeatureEvents : public CATBaseUnknown
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
    virtual void OnDeleteEvent (CATCallbackEvent iEvent,
      void* iFrom,
      CATNotification* iNotification,
      CATSubscriberData iInfo,
      CATCallback iCallback)=0;


  /** Called when parameter value is changed
    */
    virtual void OnChangeValueEvent (CATCallbackEvent iEvent,
      void* iFrom,
      CATNotification* iNotification,
      CATSubscriberData iInfo,
      CATCallback iCallback)=0;

 
   /** Called when parameter visualisation is changed
    */
    virtual void OnChangeVisuEvent (CATCallbackEvent iEvent,
      void* iFrom,
      CATNotification* iNotification,
      CATSubscriberData iInfo,
      CATCallback iCallback)=0;

	/** Initialize the events data.
	*/
   virtual void Init () = 0;

	/** Retreives the internal event data.
	*/
   virtual void GetData( int& oChangeValue, int& oChangeVisu, int& oNbDelete) = 0;


};

CATDeclareHandler(CAAILifMyFeatureEvents,CATBaseUnknown);

#endif
