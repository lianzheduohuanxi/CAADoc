#ifndef CAASysComponentBOA_H
#define CAASysComponentBOA_H

// COPYRIGHT DASSAULT SYSTEMES 2003

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAASysComponentBOA : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAASysComponentBOA();
    virtual ~CAASysComponentBOA();

  private:
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysComponentBOA(const CAASysComponentBOA &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysComponentBOA & operator = (const CAASysComponentBOA &iObjectToCopy);

};
#endif
