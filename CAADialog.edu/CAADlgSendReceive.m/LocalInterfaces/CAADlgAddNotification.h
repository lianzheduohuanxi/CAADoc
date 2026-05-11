#ifndef CAADlgAddNotification_h
#define CAADlgAddNotification_h

// COPYRIGHT DASSAULT SYSTEMES 2000
//   
//==============================================================================
//  Abstract of the class:
//  ---------------------
//
//  Element addition notification class.
//
//==============================================================================

// System Framework
#include "CATNotification.h"    // Needed to derive from CATNotification

class CAADlgAddNotification : public CATNotification
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
  public:

    CAADlgAddNotification();
    virtual ~CAADlgAddNotification();

  private:
    
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgAddNotification(const CAADlgAddNotification &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgAddNotification & operator = (const CAADlgAddNotification &iObjectToCopy);
};

#endif
