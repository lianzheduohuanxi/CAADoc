//
// COPYRIGHT DASSAULT SYSTEMES 2001
//

// Local Framework
#include "CAACafGeometryEltSettingCtrl.h"
#include "CAAICafGeometryEltSettingAtt.h"

// InteractiveInterfaces Framework
#include <CATIIniSettingManagment.h>

// System Framework
#include <CATErrorDef.h> 
#include <CATBoolean.h> 

// Others
#include <iostream.h>

CATIniCleanerSettingCtrl CAACafGeometryEltSettingCtrl::_CleanerCtrl ;

// --------------------------------------------------------------------------
// To declare that the class is a component main class 
CATImplementClass(CAACafGeometryEltSettingCtrl, Implementation, CATBaseUnknown , CATNull);


// --------------------------------------------------------------------------

CAACafGeometryEltSettingCtrl::CAACafGeometryEltSettingCtrl()
{
   cout << " Construction de CAACafGeometryEltSettingCtrl"<< endl ;
}

// --------------------------------------------------------------------------

CAACafGeometryEltSettingCtrl::~CAACafGeometryEltSettingCtrl()
{
   cout << " destruction de CAACafGeometryEltSettingCtrl"<< endl ;
}

// --------------------------------------------------------------------------

HRESULT CAACafGeometryEltSettingCtrl::GetSettingController(CAACafGeometryEltSettingCtrl ** oCtrl)
{
        HRESULT rc = S_OK ;

        if ( NULL != oCtrl )
        {
           *oCtrl = NULL ;

           CATBaseUnknown * pCtrl = _CleanerCtrl.GetController();
           if ( NULL == pCtrl )
           {
               CAACafGeometryEltSettingCtrl * SettingController = NULL;
               SettingController = new CAACafGeometryEltSettingCtrl();
               if ( NULL == SettingController )
               {
                  rc = E_OUTOFMEMORY ;
               }else
               {
                  CATBoolean Init = FALSE ;

                  // The Initialization is mandatory
                  CAAICafGeometryEltSettingAtt * pISettingAtForCtrl = NULL ;
                  rc = SettingController->QueryInterface(IID_CAAICafGeometryEltSettingAtt,
                                                        (void**) &pISettingAtForCtrl );
                  if ( SUCCEEDED(rc) )
                  {
                     rc = pISettingAtForCtrl->Initialize();
                     if ( SUCCEEDED(rc) )
                     {
                        CATIIniSettingManagment * pIMgtAtForCtrl = NULL ;
                        rc = SettingController->QueryInterface(IID_CATIIniSettingManagment,
                                                               (void**) &pIMgtAtForCtrl );
                        if ( SUCCEEDED(rc) )
                        {
                           // For the first Roolback 
                           pIMgtAtForCtrl->Commit() ;                      

                           pIMgtAtForCtrl->Release();
                           pIMgtAtForCtrl = NULL; 

                           // The cleaner keeps the unique instance
                           _CleanerCtrl.SetController(SettingController);

                           *oCtrl = SettingController ;
                           Init = TRUE ;
                        }

                     }
                     pISettingAtForCtrl->Release();
                     pISettingAtForCtrl = NULL ;
                  }

                  if ( FALSE == Init ) 
                  {
                     SettingController->Release() ;
                     SettingController = NULL ; 
                  }
               }
           }else  
           {
              *oCtrl = (CAACafGeometryEltSettingCtrl *) pCtrl ;
           }
                
        }else rc = E_FAIL ;

        return rc ;

}
// --------------------------------------------------------------------------

