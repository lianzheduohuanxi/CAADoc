// COPYRIGHT DASSAULT SYSTEMES 2007						                
#ifndef _CAA2DLPrintToDraftingWatcher_H
#define _CAA2DLPrintToDraftingWatcher_H


#include "CATBaseUnknown.h"
#include "CATEventSubscriber.h"
#include "CATBatchPublicDefinitions.h"

class  CAA2DLPrintToDraftingWatcher : public CATBaseUnknown
{

  CATDeclareClass;

public :

  CAA2DLPrintToDraftingWatcher ();
  ~CAA2DLPrintToDraftingWatcher () ;

  void SetUUID(char* uuid);

  int GetRC() {return _rc;}


  void  OnBatchEnd(CATCallbackEvent iEvt, 
    void *iAlarme,
    CATNotification  *iNotif, 
    CATSubscriberData iData,
    CATCallback       iIdCbk);

private :

  int _rc;
  CATCallback _CB;
  char _uuid[SIZE_T_ID];
};

#endif

