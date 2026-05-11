#ifndef CAADegEditor1SelectedNotification_h
#define CAADegEditor1SelectedNotification_h

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

class CAADegEditor1SelectedNotification : public CATNotification
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
  public:

    // Constructor/destructor

    CAADegEditor1SelectedNotification();
    virtual ~CAADegEditor1SelectedNotification();

  private:
    
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegEditor1SelectedNotification(const CAADegEditor1SelectedNotification &iObjectToCopy);
};

#endif
