// COPYRIGHT DASSAULT SYSTEMES 2003

#ifndef CAAEVisCreateInstanceForTextModel_h
#define CAAEVisCreateInstanceForTextModel_h

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//  This class is implementation of the CATICreateInstance interface
//  on the CAAVisTextModel component
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"  // to derive from
      
class  CAAEVisCreateInstanceForTextModel : public CATBaseUnknown
      
{
         // Used in conjunction with CATImplementClass in the .cpp file
         CATDeclareClass;

 public:
         CAAEVisCreateInstanceForTextModel() ;
         virtual ~CAAEVisCreateInstanceForTextModel();
         virtual HRESULT __stdcall CreateInstance(void **oppv);

 private:
 
         // Copy constructor, not implemented
         // Set as private to prevent from compiler automatic creation as public.
         CAAEVisCreateInstanceForTextModel(const CAAEVisCreateInstanceForTextModel &iObjectToCopy);
 
         // Assignment operator, not implemented
         // Set as private to prevent from compiler automatic creation as public.
         CAAEVisCreateInstanceForTextModel & operator = (const CAAEVisCreateInstanceForTextModel &iObjectToCopy);
      
};
#endif


