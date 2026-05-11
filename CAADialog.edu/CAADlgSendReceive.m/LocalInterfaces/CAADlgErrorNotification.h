#ifndef CAADlgErrorNotification_h
#define CAADlgErrorNotification_h

// COPYRIGHT DASSAULT SYSTEMES 2000
//   
//==============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Error notification class.
//
//==============================================================================

// System Framework
#include "CATNotification.h"    // Needed to derive from CATNotification

class CAADlgErrorNotification : public CATNotification
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
  public:

    CAADlgErrorNotification();
    virtual ~CAADlgErrorNotification();

  private:
    
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgErrorNotification(const CAADlgErrorNotification &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgErrorNotification & operator = (const CAADlgErrorNotification &iObjectToCopy);
};

#endif
