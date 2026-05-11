// COPYRIGHT DASSAULT SYSTEMES  2002
//-------------------------------------------------------------------------
//
// This class is used to suscribe to the algorithm end iteration event
// in a BATCH MODE (in interactiv mode, a stop dialog is created and
// it is this stop dialog which suscribe to the algorithm end iteration event).
// => As soon as the end iteration notification is received, the 
//	  OnReceiveNotification() method is called.
//-------------------------------------------------------------------------

#ifndef _CAAPeoUserCmd_
#define _CAAPeoUserCmd_

#include "CAAPeoCreateUserAlgorithm.h"
#include "CATCommand.h"

class ExportedByCAAPeoCreateUserAlgorithm CAAPeoUserCmd : public CATCommand
{

public:

	CAAPeoUserCmd();
	virtual ~CAAPeoUserCmd();

	void OnReceiveNotification(CATCallbackEvent iCBEvent, void* iClientData, CATNotification *iData, CATSubscriberData iSubData, CATCallback iCB);

private:


};
#endif

