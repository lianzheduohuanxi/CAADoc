#ifndef CAAEVisCreateInstanceForWireBox_H
#define CAAEVisCreateInstanceForWireBox_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysWireBox component and implementing the 
//  CATICreateInstance interface.
//
//  This interface eanbles you to create a component: CAAVisWireBox
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAEVisCreateInstanceForWireBox : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEVisCreateInstanceForWireBox();
    virtual ~CAAEVisCreateInstanceForWireBox();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEVisCreateInstanceForWireBox(const CAAEVisCreateInstanceForWireBox &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEVisCreateInstanceForWireBox & operator = (const CAAEVisCreateInstanceForWireBox &iObjectToCopy);

};
#endif
