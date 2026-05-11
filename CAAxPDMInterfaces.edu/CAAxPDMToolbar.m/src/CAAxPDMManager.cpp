// COPYRIGHT DASSAULT SYSTEMES 2006
#include "CAAxPDMManager.h"


CAAxPDMManager*   CAAxPDMManager::_MyThis = NULL;


CATImplementCBEvent(CAAxPDMManager,ConnectionChange,"ConnectedModified");

//---------------------------------------------------------------------
CAAxPDMManager* CAAxPDMManager::GetCAAxPDMManager()
{
   if (!_MyThis) _MyThis = new CAAxPDMManager();
   return _MyThis;
}

//---------------------------------------------------------------------
CAAxPDMManager::CAAxPDMManager()
{
   _IsConnected=0;
}
CAAxPDMManager::~CAAxPDMManager()
{}

//---------------------------------------------------------------------
int CAAxPDMManager::IsConnected()
{
   return _IsConnected;
}

HRESULT CAAxPDMManager::Connect()
{
   if (!_IsConnected)
   {
      _IsConnected=1;
      EnvironmentModify();
      return S_OK;
   }
   return E_FAIL;
}

HRESULT CAAxPDMManager::Disconnect()
{
   if (_IsConnected)
   {
      _IsConnected=0;
      EnvironmentModify();
      return S_OK;
   }
   return E_FAIL;
}

void CAAxPDMManager::EnvironmentModify()
{
   DispatchCallbacks(ConnectionChange(),NULL,this);
   return;
}

