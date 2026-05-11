#ifndef CAAEDlgCreateInstanceForEditorMessage_H
#define CAAEDlgCreateInstanceForEditorMessage_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAADlgBBEditorMessage component and implementing the 
//  CATICreateInstance interface.
//
//  This interface allows you to create a component : CAADlgBBEditorMessage
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAEDlgCreateInstanceForEditorMessage : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEDlgCreateInstanceForEditorMessage();
    virtual ~CAAEDlgCreateInstanceForEditorMessage();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEDlgCreateInstanceForEditorMessage(const CAAEDlgCreateInstanceForEditorMessage &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEDlgCreateInstanceForEditorMessage & operator = (const CAAEDlgCreateInstanceForEditorMessage &iObjectToCopy);

};
#endif
