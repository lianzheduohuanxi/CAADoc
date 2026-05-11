#ifndef CAAPriEditSketchNotification_h
#define CAAPriEditSketchNotification_h

// COPYRIGHT DASSAULT SYSTEMES 2000
//   
//==============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Notification sends by the CAAPriEditSketchDlg class when the end user
//  clicks on the Sketch button to edit the profile of the Pad.
//
//==============================================================================

// System Framework
#include "CATNotification.h"    // Needed to derive from CATNotification

class CAAPriEditSketchNotification : public CATNotification
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
  public:

    // Constructor/destructor

    CAAPriEditSketchNotification();
    virtual ~CAAPriEditSketchNotification();

  private:
    
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAPriEditSketchNotification(const CAAPriEditSketchNotification &iObjectToCopy);
};

#endif
