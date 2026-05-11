#ifndef CAAFrmSelectorMultiUINotifications_H
#define CAAFrmSelectorMultiUINotifications_H
//---------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2005
//---------------------------------------------------------------------
// Shape Design And Styling 
//---------------------------------------------------------------------
// Responsable: BIW
//---------------------------------------------------------------------
// CAAGSMFrmSelectorCtx
//---------------------------------------------------------------------
// 
//  Notification for contextual menu activation 
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 05/xx/xx > PEY 
//---------------------------------------------------------------------
#include "CAAGsiFeaturesSplUI.h"
#include "CATNotification.h"


class ExportedByCAAGsiFeaturesSplUI CAAGSMFrmSelectorCtxNotifClear : public CATNotification
{
public:
	CATDeclareClass;
    CAAGSMFrmSelectorCtxNotifClear();
    virtual ~CAAGSMFrmSelectorCtxNotifClear();
private:

};

#endif
