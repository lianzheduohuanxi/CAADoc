#ifndef CAASysLine_H
#define CAASysLine_H

// COPYRIGHT DASSAULT SYSTEMES 1999
 
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAASysLine component.
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"  //Needed to derive from CATBaseUnknown

class  CAASysLine : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAASysLine();
    virtual ~CAASysLine();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysLine(const CAASysLine &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysLine & operator = (const CAASysLine &iObjectToCopy);

};
#endif
