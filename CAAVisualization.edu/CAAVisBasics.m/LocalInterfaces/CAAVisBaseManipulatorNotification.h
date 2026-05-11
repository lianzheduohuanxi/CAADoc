#ifndef CAAVisBaseManipulatorNotification_h
#define CAAVisBaseManipulatorNotification_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Notification corresponding to the "Manipulator"
//  event.
//
//===========================================================================
//  Inheritance:
//  ------------
//           CAAVisBaseManipulatorNotification
//             CATNotification (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//  GetState : gets the check item state.
//===========================================================================

//System Framework
#include "CATNotification.h"


class CAAVisBaseManipulatorNotification : public CATNotification
{
  CATDeclareClass;
  
public :

  // Constructs a "Render Bounding Elements"
  // notification from the state of the corresponding
  // check item
  // Parameters
  //   iState
  //     1 or 0
  CAAVisBaseManipulatorNotification(int iState);

  //Destructor
  virtual ~CAAVisBaseManipulatorNotification();

  // Gets the check item state
  // returns 1(checked) or 0(unchecked)
  int GetState();

private:

  //Default constructor
  CAAVisBaseManipulatorNotification();

  //Copy constructor
  CAAVisBaseManipulatorNotification(const CAAVisBaseManipulatorNotification &iBrother);

  //Assignment operator
  CAAVisBaseManipulatorNotification & operator = (const CAAVisBaseManipulatorNotification &iBrother);

private:

  int _State;
};

#endif
