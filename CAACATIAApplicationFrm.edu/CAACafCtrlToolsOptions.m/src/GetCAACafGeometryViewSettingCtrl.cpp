//
// COPYRIGHT DASSAULT SYSTEMES 2001
//

// Local Framework
#include "GetCAACafGeometryViewSettingCtrl.h" // The header of the global function
#include "CAACafGeometryViewSettingCtrl.h"    // The class to contruct 

// System Framework 
#include "CATErrorDef.h" // for SUCCEEDED macro

HRESULT GetCAACafGeometryViewSettingCtrl(const IID & iInterfaceIdentifier,
                                       void     ** oInterfacePointer)
{
    HRESULT rc = S_OK ;

    if ( NULL != oInterfacePointer )
    {
       CAACafGeometryViewSettingCtrl * pCtrl = NULL ;
       rc = ::CAACafGeometryViewSettingCtrl::GetSettingController(&pCtrl);
       if ( SUCCEEDED(rc) && ( NULL != pCtrl) )
       {
          rc = pCtrl->QueryInterface(iInterfaceIdentifier,oInterfacePointer);
  
          pCtrl->Release();
          pCtrl= NULL ;

       }else 
       {
           rc = E_FAIL ;
       }
    }else rc = E_FAIL ;

    return rc ;
}
