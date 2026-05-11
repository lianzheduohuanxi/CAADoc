//
// COPYRIGHT DASSAULT SYSTEMES 2001
//

// Local Framework
#include "CAAAfrMRUManager.h"
#include "CAAAfrMRUManagerNotification.h"

// System Framework
#include <CATErrorDef.h> 
#include <CATBoolean.h> 
#include <CATUnicodeString.h> 

// Others
#include <iostream.h>

// --------------------------------------------------------------------------

CATIniCleanerSettingCtrl CAAAfrMRUManager::_Cleaner ;

// --------------------------------------------------------------------------
// To declare that the class is a component main class 
CATImplementClass(CAAAfrMRUManager, Implementation, CATBaseUnknown , CATNull);

#include <TIE_CAAIAfrMRUManagement.h>
TIE_CAAIAfrMRUManagement(CAAAfrMRUManager);

// --------------------------------------------------------------------------

CAAAfrMRUManager::CAAAfrMRUManager()
{
   cout << " Construction de CAAAfrMRUManager"<< endl ;
   // Reads the settings to initialize the list
}

// --------------------------------------------------------------------------

CAAAfrMRUManager::~CAAAfrMRUManager()
{
   cout << " destruction de CAAAfrMRUManager"<< endl ;
   // Writes the settings to keep the value for a next session
}

// --------------------------------------------------------------------------

HRESULT CAAAfrMRUManager::GetMRUManager(CAAAfrMRUManager ** oManager)
{
   HRESULT rc = S_OK ;

   if ( NULL != oManager )
   {
      *oManager = NULL ;

      CATBaseUnknown * pManager = _Cleaner.GetController();
      if ( NULL == pManager )
      {
          // First creation 
          CAAAfrMRUManager * Obj = NULL;
          Obj = new CAAAfrMRUManager();
          if ( NULL == Obj )
          {
             rc = E_OUTOFMEMORY ;
          }else
          {
            *oManager = Obj ; 
            _Cleaner.SetController(Obj);
          }
       }else  
       {
          *oManager = (CAAAfrMRUManager *) pManager ;
       }
                
   }else rc = E_FAIL ;

   return rc ;

}
// --------------------------------------------------------------------------
HRESULT CAAAfrMRUManager::AddElement(CATUnicodeString &iNewElement) 
{
    cout <<" CAAAfrMRUManager::AddElement" << endl;

    if ( MRU_MAX_SIZE == _NameList.Size() )
    {
        // The list is full, the last element is removed
       _NameList.RemovePosition(MRU_MAX_SIZE);
    }

    // At the first position
    _NameList.InsertBefore(1,iNewElement);
    
    for ( int i=1 ; i <= _NameList.Size() ; i++ )
    {
        cout <<"elt " << _NameList[i].ConvertToChar() << endl;
    }

    //Update the 
    CATCallbackManager * pCBManager = ::GetDefaultCallbackManager(this) ;
    if ( NULL != pCBManager )
    {
         CAAAfrMRUManagerNotification * pNotification = new CAAAfrMRUManagerNotification();
         pCBManager->DispatchCallbacks(pNotification,this);
         pNotification->Release(); pNotification = NULL ;
    }

    return S_OK ;
}
// --------------------------------------------------------------------------
HRESULT CAAAfrMRUManager::GetElementList(CATListOfCATUnicodeString & oElementList) const  
{
    cout <<" CAAAfrMRUManager::GetElementList" << endl;

    for ( int i = 1 ; i <= _NameList.Size() ; i++)
    {
       oElementList.Append(_NameList[i]);
    }

    return S_OK ;
}
// --------------------------------------------------------------------------

HRESULT CAAAfrMRUManager::SelectElement(int iPosition) 
{
    HRESULT rc = E_FAIL ;

    cout <<" CAAAfrMRUManager::SelectElement" << endl;

    if ( (iPosition >= 1) && (iPosition <= MRU_MAX_SIZE) )
    {
       // Modifies the order into the list of element
        CATUnicodeString Sel = _NameList[iPosition] ;

       _NameList.RemovePosition(iPosition);

       _NameList.InsertBefore(1,Sel);

       // Event to prevent the MRU header instances to update
       // their dialog objets.
       CATCallbackManager * pCBManager = ::GetDefaultCallbackManager(this) ;
       if ( NULL != pCBManager )
       {
          CAAAfrMRUManagerNotification * pNotification = new CAAAfrMRUManagerNotification();
          
          pCBManager->DispatchCallbacks(pNotification,this);
          
          pNotification->Release();
          pNotification = NULL ;

          rc = S_OK ;
       }
    }

    return rc ;
}
// --------------------------------------------------------------------------

