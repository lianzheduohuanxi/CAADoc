#ifndef CAADegEditor1DeselectedNotification_h
#define CAADegEditor1DeselectedNotification_h

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

class CAADegEditor1DeselectedNotification : public CATNotification
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
  public:

    // Constructor/destructor

    CAADegEditor1DeselectedNotification();
    virtual ~CAADegEditor1DeselectedNotification();

  private:
    
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegEditor1DeselectedNotification(const CAADegEditor1DeselectedNotification &iObjectToCopy);
};

#endif
