/*=======================================================================*/
/* COPYRIGHT DASSAULT SYSTEMES 2000						                */
/*=======================================================================*/
/*                                                                       */
/*  CATBatchEventWatcher                                                        */
/*                                                                        */
/*  Usage Notes: 
/*    
/*=======================================================================*/
/*  Creation Oct	2000                                 jnm             */
/*=======================================================================*/
#ifndef _CATBatchEventWatcher_H
#define _CATBatchEventWatcher_H


#include "CATBaseUnknown.h"
#include "CATEventSubscriber.h"
#include "CATBatchPublicDefinitions.h"


	


class  CATBatchEventWatcher : public CATBaseUnknown
{

    CATDeclareClass;

   public :

   CATBatchEventWatcher (int* cond=NULL);
   ~CATBatchEventWatcher () ;
   
   void SetUUID(char* uuid);
   
   int GetRC() {return _rc;}
      

   void  OnBatchEnd(CATCallbackEvent iEvt, void             *iAlarme,
                             CATNotification  *iNotif, CATSubscriberData iData,
                             CATCallback       iIdCbk);

	 
   private :
   
   int* _cond;
   int _rc;
   char _uuid[SIZE_T_ID];

};


#endif

