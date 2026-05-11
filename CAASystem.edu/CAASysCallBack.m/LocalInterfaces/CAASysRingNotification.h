#ifndef CAASysRingNotification_h
#define CAASysRingNotification_h

// COPYRIGHT DASSAULT SYSTEMES 1999
//   
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Ring Notification class.
//
//===========================================================================
//  Inheritance:
//  ------------
//            CATNotification  ( System Framework)
//               CATBaseUnknown (System Framework).
//
//===========================================================================

// System Framework
#include "CATNotification.h"    // Needed to derive from CATNotification

class CAASysRingNotification : public CATNotification
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
  public:

    CAASysRingNotification();
    virtual ~CAASysRingNotification();

  private:
    
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysRingNotification(const CAASysRingNotification &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysRingNotification & operator = (const CAASysRingNotification &iObjectToCopy);
     
};

#endif
