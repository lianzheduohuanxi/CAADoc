#ifndef CAAAfrMRUManagerNotification_h
#define CAAAfrMRUManagerNotification_h

// COPYRIGHT DASSAULT SYSTEMES 1999
//   
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//===========================================================================

// System Framework
#include "CATNotification.h"    // Needed to derive from CATNotification


class CAAAfrMRUManagerNotification : public CATNotification
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
  public:

    CAAAfrMRUManagerNotification();
    virtual ~CAAAfrMRUManagerNotification();

  private:
    
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrMRUManagerNotification(const CAAAfrMRUManagerNotification &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrMRUManagerNotification & operator = (const CAAAfrMRUManagerNotification &iObjectToCopy);
     
};

#endif
