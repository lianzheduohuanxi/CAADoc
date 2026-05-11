//  COPYRIGHT DASSAULT SYSTEMES  1994 2000

//============================================================================
//
//  ABSTRACT:
//  ---------
//
//  Extension of CAALifSimpleFeature, the feature which subscribes to parameter events                                       
//  Provides an implementation of CAAILifMyfeatureEvents (PrivateInterfaces)  
//
//============================================================================

//C++ Headers
#include "iostream.h"

// CAA LiteralFeatures header 
#include "CAALifMyFeatureEventsExt.h"

// LiteralFeatures 
#include "CATICkeParm.h"
#include "CATIParmEvents.h"

// ObjectModelerBase
#include "CATInterfaceEvents.h"

// Declare the implementation as an extension of CAAMyfeature 
CATImplementClass(CAALifMyFeatureEventsExt, DataExtension, CATBaseUnknown, CAALifSimpleFeature);

#include "TIE_CAAILifMyFeatureEvents.h"
TIE_CAAILifMyFeatureEvents(CAALifMyFeatureEventsExt);

CAALifMyFeatureEventsExt::CAALifMyFeatureEventsExt()  
{
	nbchangevalue = 0;  
	nbchangevisu = 0;  
	nbdelete = 0;    
}

CAALifMyFeatureEventsExt::~CAALifMyFeatureEventsExt()  
{
	nbchangevalue = 0;  
	nbchangevisu = 0;  
	nbdelete = 0;    
}

   // Initialize the events data.
void CAALifMyFeatureEventsExt::Init ()
{
	nbchangevalue = 0;  
	nbchangevisu = 0;  
	nbdelete = 0;    
}


void CAALifMyFeatureEventsExt::GetData( int& oChangeValue, int& oChangeVisu, int& oNbDelete)
{
	oChangeValue = nbchangevalue;
	oChangeVisu = nbchangevisu;
	oNbDelete = nbdelete;
}

// Subscribe to all events on parameter iParameterToObserve
void CAALifMyFeatureEventsExt::Observe (const CATICkeParm_var &iParameterToObserve)
{
  // Retrieve the CATIParmEvents interface from your parameter
  CATIParmEvents_var spParameterEvents = iParameterToObserve;
 
  // Retrieve the CATInterfaceEvents to manage the callbacks
  CATInterfaceEvents_var spSpev(this);

  cout << " Subscribing to events" << endl;
  
 
  // Add subscription to the "change value" event 
  spSpev->AddSubscription(spParameterEvents,
		      spParameterEvents->GetChangeValueNotification(),
		      (CATSubscriberMethod)&CAAILifMyFeatureEvents::OnChangeValueEvent,
		      "CAAILifMyFeatureEvents",
		      (CATSubscriberData) this);
 
  // Add subscription to the "change visu" event 
  spSpev->AddSubscription(spParameterEvents,
		      spParameterEvents->GetChangeVisuNotification(),
		      (CATSubscriberMethod)&CAAILifMyFeatureEvents::OnChangeVisuEvent,
		      "CAAILifMyFeatureEvents",
		      (CATSubscriberData) this);

  // Add subscription to the "delete" event 
  spSpev->AddSubscription(spParameterEvents,
		      spParameterEvents->GetDeleteNotification(),
		      (CATSubscriberMethod)&CAAILifMyFeatureEvents::OnDeleteEvent,
		      "CAAILifMyFeatureEvents",
		      (CATSubscriberData) this);
}

 
// Delete events 
void CAALifMyFeatureEventsExt::Suppress (const CATICkeParm_var &iParameterToObserve)
{
  // Retrieve the CATIParmEvents interface from  iParameterToObserve
  CATIParmEvents_var spParameterEvents = iParameterToObserve;
  
  // Retrieve the CATInterfaceEvents interface to reset the callbacks
  CATInterfaceEvents_var spSpev (this);
 
  spSpev->RemoveSubscriptionsOn(spParameterEvents, 
				     spParameterEvents->GetDeleteNotification(),
				     "CAAILifMyFeatureEvents", NULL);

  spSpev->RemoveSubscriptionsOn(spParameterEvents, 
				     spParameterEvents->GetChangeVisuNotification(),
				     "CAAILifMyFeatureEvents", NULL);

  spSpev->RemoveSubscriptionsOn(spParameterEvents, 
				     spParameterEvents->GetChangeValueNotification(),
				     "CAAILifMyFeatureEvents", NULL);

}

// Service called when the parameter is deleted
void CAALifMyFeatureEventsExt::OnDeleteEvent
                         ( CATCallbackEvent iEvent,
                                       void* iFrom,
                    CATNotification* iNotification,
                           CATSubscriberData iInfo,
                              CATCallback iCallback)
{
	nbdelete++;
  //((CAALifMyFeatureEventsExt*)iInfo)->nbdelete++;
  cout << "Receiving Delete number " << nbdelete << endl;
}

// Service called when parameter value is changed
void CAALifMyFeatureEventsExt::OnChangeValueEvent
                           (CATCallbackEvent iEvent,
                                        void* iFrom,
                     CATNotification* iNotification,
                            CATSubscriberData iInfo,
                              CATCallback iCallback)
{
    //Retrieve the parameter that sent the event.
    CATBaseUnknown* cbup = (CATBaseUnknown*)iFrom;
    CATICkeParm_var p = cbup;
    if(p!=NULL_var)
        cerr << " Parm: " << p->Name().ConvertToChar() << endl;
    

	nbchangevalue++;
  //((CAALifMyFeatureEventsExt*)iInfo)->nbchangevalue++;
  cout << "Receiving ChangeValue number "<< nbchangevalue << endl;
}

// Service called when some visualisation aspects of the parameter have changed
void CAALifMyFeatureEventsExt::OnChangeVisuEvent
                           (CATCallbackEvent iEvent,
                                        void* iFrom,
                     CATNotification* iNotification,
                            CATSubscriberData iInfo,
                              CATCallback iCallback)
{
	nbchangevisu++;
  //((CAALifMyFeatureEventsExt*)iInfo)->nbchangevisu++;
  cout << "Receiving ChangeVisu number " << nbchangevisu << endl;
}


// Define the CAAILifMyFeatureEvent interface
#ifndef LOCAL_DEFINITION_FOR_IID
IID IID_CAAILifMyFeatureEvents = { 0x7f5e0d25,
    0x47d2,
    0x0000,
    {0x02,0x80, 0x02, 0x0a, 0x5c, 0x00, 0x00, 0x00} };
#endif


CATImplementInterface(CAAILifMyFeatureEvents,CATBaseUnknown);

// Declare smart pointers or handlers
CATImplementHandler(CAAILifMyFeatureEvents,CATBaseUnknown);

