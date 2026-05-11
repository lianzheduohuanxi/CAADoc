#ifndef CAACafGeometryEltSettingCtrl_H
#define CAACafGeometryEltSettingCtrl_H
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//  
//  Implementation class of the CAACafGeometryEltSettingCtrl component.
// 
//  This component is instantiated once in using the global function
//  GetCAACafGeometryEltSettingCtrl. 
//
//===========================================================================
#include "CATBaseUnknown.h"  // To derive from

#include "CATIniCleanerSettingCtrl.h" 

class  CAACafGeometryEltSettingCtrl : public CATBaseUnknown
{
   // Used in conjunction with CATImplementClass in the .cpp file
   CATDeclareClass;

   public:
 
   CAACafGeometryEltSettingCtrl();
   virtual ~CAACafGeometryEltSettingCtrl(); 

   // Retrieves or creates the unic instance class
   // This method must only be called by the global function 
   // GetCAACafGeometryEltSettingCtrl defined in ProtectedInterfaces
   // of this Framework
   static HRESULT GetSettingController(CAACafGeometryEltSettingCtrl ** oCtrl);

 private:
   
   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAACafGeometryEltSettingCtrl(const CAACafGeometryEltSettingCtrl &iObjectToCopy);

   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAACafGeometryEltSettingCtrl & operator = (const CAACafGeometryEltSettingCtrl &iObjectToCopy);

 private:

   // This class contains the unic instance of CAACafGeometryEltSettingCtrl
   // We use a cleaner class to avoid MLK at the end of the session
   //
   static CATIniCleanerSettingCtrl _CleanerCtrl ;


};


#endif
