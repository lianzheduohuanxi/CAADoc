#ifndef CAAVisBaseRenderBENotification_h
#define CAAVisBaseRenderBENotification_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Notification corresponding to the "Render Bounding Elements"
//  event.
//
//===========================================================================
//  Inheritance:
//  ------------
//           CAAVisBaseRenderBENotification
//             CATNotification (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//  GetState : gets the check item state.
//===========================================================================

//System Framework
#include "CATNotification.h"


class CAAVisBaseRenderBENotification : public CATNotification
{
  CATDeclareClass;
  
public :

  // Constructs a "Render Bounding Elements"
  // notification from the state of the corresponding
  // check item
  // Parameters
  //   iState
  //     0 (unchecked) or 1 (checked)
  CAAVisBaseRenderBENotification(int iState);

  //Destructor
  virtual ~CAAVisBaseRenderBENotification();

  // Gets the check item state
  // returns 0 or 1
  int GetState();

private:

  //Default constructor
  CAAVisBaseRenderBENotification();

  //Copy constructor
  CAAVisBaseRenderBENotification(const CAAVisBaseRenderBENotification &iBrother);

  //Assignment operator
  CAAVisBaseRenderBENotification & operator = (const CAAVisBaseRenderBENotification &iBrother);

private:

  int _State;
};

#endif
