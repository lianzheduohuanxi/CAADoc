#ifndef CAAVisBaseExitNotification_h
#define CAAVisBaseExitNotification_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Notification corresponding to the "Exit"
//  event.
//
//===========================================================================
//  Inheritance:
//  ------------
//           CAAVisBaseExitNotification
//             CATNotification (System Framework)
//
//===========================================================================

//System Framework
#include "CATNotification.h"

class CAAVisBaseExitNotification : public CATNotification
{
  CATDeclareClass;
  
public :

  // Constructs a "Exit" notification
  CAAVisBaseExitNotification();

  //Destructor
  virtual ~CAAVisBaseExitNotification();

private:
  //Copy constructor
  CAAVisBaseExitNotification(const CAAVisBaseExitNotification &iBrother);

  //Assignment operator
  CAAVisBaseExitNotification & operator = (const CAAVisBaseExitNotification &iBrother);

};

#endif
