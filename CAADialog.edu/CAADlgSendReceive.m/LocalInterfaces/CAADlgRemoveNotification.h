#ifndef CAADlgRemoveNotification_h
#define CAADlgRemoveNotification_h

// COPYRIGHT DASSAULT SYSTEMES 2000
//   
//==============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Element removal notification class.
//
//==============================================================================

// System Framework
#include "CATNotification.h"    // Needed to derive from CATNotification

class CAADlgRemoveNotification : public CATNotification
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
  public:

    CAADlgRemoveNotification();
    virtual ~CAADlgRemoveNotification();

  private:
    
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgRemoveNotification(const CAADlgRemoveNotification &iObjectToCopy);
    
    // Assignment operator , not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgRemoveNotification & operator = (const CAADlgRemoveNotification &iObjectToCopy);
};

#endif
