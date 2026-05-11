#ifndef CAAAfrComboColorNotification_h
#define CAAAfrComboColorNotification_h

// COPYRIGHT DASSAULT SYSTEMES 1999
//   
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//===========================================================================

// System Framework
#include "CATNotification.h"    // Needed to derive from CATNotification


class CAAAfrComboColorNotification : public CATNotification
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
  public:

    CAAAfrComboColorNotification();
    virtual ~CAAAfrComboColorNotification();

  private:
    
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrComboColorNotification(const CAAAfrComboColorNotification &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrComboColorNotification & operator = (const CAAAfrComboColorNotification &iObjectToCopy);
     
};

#endif
