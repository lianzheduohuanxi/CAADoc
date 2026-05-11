#ifndef CAADlgModifNotification_h
#define CAADlgModifNotification_h

// COPYRIGHT DASSAULT SYSTEMES 1999
//   
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Modification Notification class.
//
//===========================================================================
//  Inheritance:
//  ------------
//            CATNotification  ( System Framework)
//               CATBaseUnknown ( System Framework).
//
//===========================================================================

// System Framework
#include "CATNotification.h"    // Needed to derive from CATNotification

class CAADlgModifNotification : public CATNotification
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
  public:

    CAADlgModifNotification();
    virtual ~CAADlgModifNotification();

  private:
    
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgModifNotification(const CAADlgModifNotification &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgModifNotification & operator = (const CAADlgModifNotification &iObjectToCopy);

};

#endif
