#ifndef CAAVisWireBox_H
#define CAAVisWireBox_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAAVisWireBox component.
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"

class  CAAVisWireBox : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public :

    CAAVisWireBox();
    virtual ~CAAVisWireBox();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisWireBox(const CAAVisWireBox &iObjectToCopy);
 
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisWireBox & operator = (const CAAVisWireBox &iObjectToCopy);
 
};

#endif
