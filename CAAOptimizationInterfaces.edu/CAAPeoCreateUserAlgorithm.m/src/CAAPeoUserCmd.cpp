#include "CAAPeoUserCmd.h"
#include "CAAPeoUserAlgorithmNotif.h"
#include <iostream.h>

CAAPeoUserCmd::CAAPeoUserCmd()
{

}

CAAPeoUserCmd::~CAAPeoUserCmd()
{

}


void CAAPeoUserCmd::OnReceiveNotification(CATCallbackEvent iCBEvent, void* iClientData, CATNotification *iData, CATSubscriberData iSubData, CATCallback iCB)
{
	CAAPeoUserAlgorithmNotif* pNotif = NULL;
	pNotif = (CAAPeoUserAlgorithmNotif*) iData;

	if(!pNotif)
		return;

	cerr << pNotif->GetComment().ConvertToChar();
}

