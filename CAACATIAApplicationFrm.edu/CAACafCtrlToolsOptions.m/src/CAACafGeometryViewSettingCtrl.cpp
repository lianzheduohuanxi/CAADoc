//
// COPYRIGHT DASSAULT SYSTEMES 2001
//

// Local Framework
#include "CAACafGeometryViewSettingCtrl.h"
#include "CAAICafGeometryViewSettingAtt.h"

// InteractiveInterfaces Framework
#include <CATIIniSettingManagment.h>

// System Framework
#include <CATErrorDef.h> 
#include <CATBoolean.h> 

// Other
#include <iostream.h> 

CATIniCleanerSettingCtrl CAACafGeometryViewSettingCtrl::_CleanerCtrl ;

// --------------------------------------------------------------------------
// To declare that the class is a component main class 
CATImplementClass(CAACafGeometryViewSettingCtrl, Implementation, CATBaseUnknown , CATNull);


// --------------------------------------------------------------------------

CAACafGeometryViewSettingCtrl::CAACafGeometryViewSettingCtrl()
{
   cout << " Construction de CAACafGeometryViewSettingCtrl"<< endl ;
}

// --------------------------------------------------------------------------

CAACafGeometryViewSettingCtrl::~CAACafGeometryViewSettingCtrl()
{
   cout << " destruction de CAACafGeometryViewSettingCtrl"<< endl ;
}

// --------------------------------------------------------------------------

HRESULT CAACafGeometryViewSettingCtrl::GetSettingController(CAACafGeometryViewSettingCtrl ** oCtrl)
{
	HRESULT rc = S_OK ;

	if ( NULL != oCtrl )
	{
           *oCtrl = NULL ;

           CATBaseUnknown * pCtrl = _CleanerCtrl.GetController();
           if ( NULL == pCtrl )
           {
               CAACafGeometryViewSettingCtrl * SettingController = NULL;
               SettingController = new CAACafGeometryViewSettingCtrl();
               if ( NULL == SettingController )
               {
                  rc = E_OUTOFMEMORY ;
               }else
               {
                  CATBoolean Init = FALSE ;

                  // The Initialization is mandatory
                  CAAICafGeometryViewSettingAtt * pISettingAtForCtrl = NULL ;
                  rc = SettingController->QueryInterface(IID_CAAICafGeometryViewSettingAtt,
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
                           
                             // The cleaner keeps the unic instance
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
              *oCtrl = (CAACafGeometryViewSettingCtrl *) pCtrl ;
           }
                
	}else rc = E_FAIL ;
	
	return rc ;

}
// --------------------------------------------------------------------------

