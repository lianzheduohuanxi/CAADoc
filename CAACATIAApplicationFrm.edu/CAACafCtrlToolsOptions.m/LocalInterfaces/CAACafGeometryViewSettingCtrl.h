#ifndef CAACafGeometryViewSettingCtrl_H
#define CAACafGeometryViewSettingCtrl_H
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//  
//  Implementation class of the CAACafGeometryViewSettingCtrl component.
// 
//  This component is instantiated once in using the global function
//  GetCAACafGeometryViewSettingCtrl. 
//
//===========================================================================
#include "CATBaseUnknown.h"  // To derive from

#include "CATIniCleanerSettingCtrl.h" 

class  CAACafGeometryViewSettingCtrl : public CATBaseUnknown
{
   // Used in conjunction with CATImplementClass in the .cpp file
   CATDeclareClass;

   public:
 
   CAACafGeometryViewSettingCtrl();
   virtual ~CAACafGeometryViewSettingCtrl(); 

   // Retrieves or creates the unic instance class
   // This method must only be called by the global function 
   // GetCAACafGeometryViewSettingCtrl defined in ProtectedInterfaces
   // of this Framework
   static HRESULT GetSettingController(CAACafGeometryViewSettingCtrl ** oCtrl);

 private:
   
   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAACafGeometryViewSettingCtrl(const CAACafGeometryViewSettingCtrl &iObjectToCopy);

   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAACafGeometryViewSettingCtrl & operator = (const CAACafGeometryViewSettingCtrl &iObjectToCopy);

 private:

   // This class contains the unic instance of CAACafGeometryViewSettingCtrl
   // We use a cleaner class to avoid MLK at the end of the session
   //
   static CATIniCleanerSettingCtrl _CleanerCtrl ;


};


#endif
