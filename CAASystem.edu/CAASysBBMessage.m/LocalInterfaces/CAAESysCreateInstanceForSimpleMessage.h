#ifndef CAAESysCreateInstanceForSimpleMessage_H
#define CAAESysCreateInstanceForSimpleMessage_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysSimpleMessage component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows to create a component : CAASysSimpleMessage
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForSimpleMessage : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

  CAAESysCreateInstanceForSimpleMessage();
  virtual ~CAAESysCreateInstanceForSimpleMessage();

  // CATICreateInstance 
  // -------------------

  virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAESysCreateInstanceForSimpleMessage(const CAAESysCreateInstanceForSimpleMessage &iObjectToCopy);

  // Assignment operator , not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAESysCreateInstanceForSimpleMessage & operator = (const CAAESysCreateInstanceForSimpleMessage &iObjectToCopy);

};
#endif
