#ifndef CAAESysCreateInstanceForDataMessage_H
#define CAAESysCreateInstanceForDataMessage_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysDataMessage component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows to create a component : CAASysDataMessage
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForDataMessage : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

  CAAESysCreateInstanceForDataMessage();
  virtual ~CAAESysCreateInstanceForDataMessage();

  // CATICreateInstance 
  // -------------------

  virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAESysCreateInstanceForDataMessage(const CAAESysCreateInstanceForDataMessage &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAESysCreateInstanceForDataMessage & operator = (const CAAESysCreateInstanceForDataMessage &iObjectToCopy);

};
#endif
