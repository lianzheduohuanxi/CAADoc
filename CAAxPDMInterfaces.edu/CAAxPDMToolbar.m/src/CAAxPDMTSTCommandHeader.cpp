// COPYRIGHT DASSAULT SYSTEMES 2006
#include "CAAxPDMTSTCommandHeader.h"

#include "CAAxPDMManager.h"

CATImplementHeaderResources(CAAxPDMTSTCommandHeader, CATCommandHeader,CAAxPDMTSTCommandHeader)
CATImplementClass(CAAxPDMTSTCommandHeader, Implementation,CATCommandHeader, CATNull);


CAAxPDMTSTCommandHeader::CAAxPDMTSTCommandHeader (const CATString & HeaderID,const CATString & loadName,const CATString & classname,
                                                  void * argument,int state,int type):
CATCommandHeader(HeaderID, loadName, classname, argument, state),_classname(classname),_loadname(loadName),_type(type),_argument(argument)
{
   UpdateHeader();
   //Callback on Connect and Disconnect
   CAAxPDMManager* xPDMManager = CAAxPDMManager::GetCAAxPDMManager();
   if(xPDMManager)
   {
      _callback = AddCallback(xPDMManager,xPDMManager->ConnectionChange(),
         (CATSubscriberMethod)&CAAxPDMTSTCommandHeader::OnSettingsChange,NULL);
   }
}
CAAxPDMTSTCommandHeader::~CAAxPDMTSTCommandHeader ()
{
   if (_callback)
      RemoveCallback(CAAxPDMManager::GetCAAxPDMManager(),_callback);
   _callback=0;
   _argument=NULL;
}
void CAAxPDMTSTCommandHeader::OnSettingsChange(CATCallbackEvent iEvt,void * iSrv,CATNotification * iNotif,CATSubscriberData iData,CATCallback iCB)
{
   UpdateHeader();
}
void CAAxPDMTSTCommandHeader::UpdateHeader()
{
   if (_type==0)
   {
      CAAxPDMManager* xPDMManager = CAAxPDMManager::GetCAAxPDMManager();
      if(xPDMManager)
      {
         if (xPDMManager->IsConnected())
            BecomeAvailable();
         else
            BecomeUnavailable();
      }
   }
   return;
}
CATCommandHeader * CAAxPDMTSTCommandHeader::Clone()
{
   CAAxPDMTSTCommandHeader* header = new CAAxPDMTSTCommandHeader(GetID(),_loadname,_classname,_argument,CATFrmAvailable,_type);
   return header;
}

