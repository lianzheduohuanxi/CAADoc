// COPYRIGHT DASSAULT SYSTEMES 2007

#include "SamplePushItem.h"
#include "CATCallbackManager.h"

CATImplementClass( SamplePushItem,
                   Implementation,
                   CATDlgPushItem,
                   CATNull );

CATImplementCBEvent( SamplePushItem, MenuItemActivated, "MenuItemActivated" );

SamplePushItem::SamplePushItem(CATDialog *iFather, const CATString &iName, int iStyle)
               :CATDlgPushItem( iFather, iName, iStyle  )
{
    AddAnalyseNotificationCB(this,
                             GetMenuIActivateNotification(),
                             (CATCommandMethod)&SamplePushItem::OnPushed,
                             NULL);

}

SamplePushItem::~SamplePushItem()
{
    // clean out callbacks placed on this PushItem
    CATCallbackManager* mgr = GetCallbackManager();
    if(mgr) mgr->RemoveAllCallbacks();

}

void SamplePushItem::OnPushed( CATCommand *, CATNotification *, CATCommandClientData )
{
    if(GetCallbackManager())
       GetCallbackManager()->DispatchCallbacks( MenuItemActivated() );
}

CATCallback SamplePushItem::RegisterItemActivatedEvent( CATEventSubscriber *iSubscriber,
                                                      CATSubscriberMethod iMethod,
                                                      CATSubscriberData iData )
{
    if( iSubscriber )
    {
        return iSubscriber->AddCallback( this, MenuItemActivated(), iMethod, iData );
    }
    else
    {
        return NULL;
    }
}

void SamplePushItem::UnregisterItemActivatedEvent( CATEventSubscriber *iSubscriber, CATCallback iUpdateCallback )
{
    if( iSubscriber )
    {
        iSubscriber->RemoveCallback( this, iUpdateCallback );
    }
}
