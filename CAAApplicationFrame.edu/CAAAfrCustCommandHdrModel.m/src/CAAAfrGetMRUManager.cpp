//
// COPYRIGHT DASSAULT SYSTEMES 2001
//

// Local Framework
#include "CAAAfrGetMRUManager.h" // The header of the global function
#include "CAAAfrMRUManager.h"    // The class to contruct 

// System Framework 
#include "CATErrorDef.h" // for SUCCEEDED macro

HRESULT CAAAfrGetMRUManager(const IID & iInterfaceIdentifier,
                            void     ** oInterfacePointer)
{
    HRESULT rc = S_OK ;

    if ( NULL != oInterfacePointer )
    {
       CAAAfrMRUManager * pManager = NULL ;
       rc = ::CAAAfrMRUManager::GetMRUManager(&pManager);
       if ( SUCCEEDED(rc) && ( NULL != pManager) )
       {
          rc = pManager->QueryInterface(iInterfaceIdentifier,oInterfacePointer);
  
          pManager->Release();
          pManager= NULL ;

       }else 
       {
           rc = E_FAIL ;
       }
    }else rc = E_FAIL ;

    return rc ;
}

