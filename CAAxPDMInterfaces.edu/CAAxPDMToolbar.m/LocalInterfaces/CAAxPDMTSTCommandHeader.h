/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
#ifndef CAAxPDMTSTCommandHeader_H 
#define CAAxPDMTSTCommandHeader_H 

#include "CATCommandHeader.h"


class CAAxPDMTSTCommandHeader : public CATCommandHeader

{
   CATDeclareClass;
   CATDeclareHeaderResources;
public:
   CAAxPDMTSTCommandHeader (const CATString & HeaderID,
      const CATString & loadName,const CATString & classname,void * argument,int state=CATFrmAvailable, int type=0);
   virtual ~CAAxPDMTSTCommandHeader ();
   void OnSettingsChange(CATCallbackEvent iEvt,void * iSrv,CATNotification * iNotif,CATSubscriberData iData,CATCallback iCB);
   void UpdateHeader();
   CATCommandHeader* Clone();
private:
   int _type;
   CATCallback _callback;
   CATString _loadname, _classname;
   void* _argument;
};
#endif
