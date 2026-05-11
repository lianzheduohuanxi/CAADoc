#ifndef CAAAfrMRUManager_H
#define CAAAfrMRUManager_H
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//  
//  Implementation class of the CAAAfrMRUManager component.
// 
//  This component is instantiated once in using the global function
//  GetCAAAfrMRUManager. 
//
//===========================================================================
// System framework
#include "CATBaseUnknown.h"  // To derive from
class CATUnicodeString ;
#include "CATListOfCATUnicodeString.h"
#include "CATCallbackManager.h"

// InteractiveInterfaces framework   
#include "CATIniCleanerSettingCtrl.h" 

#define MRU_MAX_SIZE 5 

class  CAAAfrMRUManager : public CATBaseUnknown
{
   // Used in conjunction with CATImplementClass in the .cpp file
   CATDeclareClass;

   public:
 
   CAAAfrMRUManager();
   virtual ~CAAAfrMRUManager(); 

   // Retrieves or creates the unic instance class
   // This method must only be called by the global function 
   // GetCAAAfrMRUManager defined in PublicInterfaces
   // of this Framework
   static HRESULT GetMRUManager(CAAAfrMRUManager ** oManager);


   // CAAIAfrMRUManagement
   virtual HRESULT AddElement(CATUnicodeString &iNewElement) ;

   virtual HRESULT GetElementList(CATListOfCATUnicodeString &ElementList) const  ;

   virtual HRESULT SelectElement(int iPosition) ;

 private:
   
   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAAfrMRUManager(const CAAAfrMRUManager &iObjectToCopy);

   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAAfrMRUManager & operator = (const CAAAfrMRUManager &iObjectToCopy);

 private:

   // This class contains the unic instance of CAAAfrMRUManager
   // We use a cleaner class to avoid MLK at the end of the session
   //
   static CATIniCleanerSettingCtrl _Cleaner ;

   CATListOfCATUnicodeString       _NameList;

};


#endif
