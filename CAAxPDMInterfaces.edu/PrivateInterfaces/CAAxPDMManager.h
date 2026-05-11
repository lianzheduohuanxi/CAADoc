// COPYRIGHT DASSAULT SYSTEMES 2006
#ifndef CAAxPDMManager_H_
#define CAAxPDMManager_H_

#include "CATCallbackManager.h"
#include "ExportedByCAAxPDMToolbar.h"

class ExportedByCAAxPDMToolbar CAAxPDMManager : public CATCallbackManager
{
public:
   //----------------------------------------------------------------
   //   Retrieve Manager
   //----------------------------------------------------------------
   static CAAxPDMManager* GetCAAxPDMManager();
   
   //----------------------------------------------------------
   //  Connection Support
   //----------------------------------------------------------
   int IsConnected();
   HRESULT Connect();
   HRESULT Disconnect();

   //CallBack Declaration
   CATDeclareCBEvent(ConnectionChange);
   void EnvironmentModify();

private:
   CAAxPDMManager();
   CAAxPDMManager(const CAAxPDMManager&);
   CAAxPDMManager& operator = (const CAAxPDMManager&);
   ~CAAxPDMManager();

   void RefreshVisu();
   
   //Stockage des settings crees
   static CAAxPDMManager*        _MyThis;
   int                           _IsConnected;
};

#endif

