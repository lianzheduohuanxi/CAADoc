#ifndef CAACafLaunchNextQueryNotification_h
#define CAACafLaunchNextQueryNotification_h

// COPYRIGHT DASSAULT SYSTEMES 2003
//   
//==============================================================================
//  Abstract of the class:
//  ----------------------
//
// Launch button selection notification class.
//
//==============================================================================

// System Framework
#include "CATNotification.h"    // Needed to derive from CATNotification

class CAACafLaunchNextQueryNotification : public CATNotification
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
  public:

    // Constructor/destructor

    CAACafLaunchNextQueryNotification();
    virtual ~CAACafLaunchNextQueryNotification();

  private:
    
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafLaunchNextQueryNotification(const CAACafLaunchNextQueryNotification &iObjectToCopy);
};

#endif
