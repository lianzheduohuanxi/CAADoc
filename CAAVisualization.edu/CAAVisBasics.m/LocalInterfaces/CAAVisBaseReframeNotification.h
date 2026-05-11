#ifndef CAAVisBaseReframeNotification_h
#define CAAVisBaseReframeNotification_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Notification corresponding to the "Reframe"
//  event.
//
//===========================================================================
//  Inheritance:
//  ------------
//           CAAVisBaseReframeNotification
//             CATNotification (System Framework)
//
//===========================================================================

//System Framework
#include "CATNotification.h"

class CAAVisBaseReframeNotification : public CATNotification
{
  CATDeclareClass;
  
public :

  // Constructs a "Reframe" notification
  CAAVisBaseReframeNotification();

  //Destructor
  virtual ~CAAVisBaseReframeNotification();

private:

  //Copy constructor
  CAAVisBaseReframeNotification(const CAAVisBaseReframeNotification &iBrother);

  //Assignment operator
  CAAVisBaseReframeNotification & operator = (const CAAVisBaseReframeNotification &iBrother);

};
#endif
