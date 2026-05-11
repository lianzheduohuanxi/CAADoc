#ifndef CAAVisBaseModifyViewpointNotification_h
#define CAAVisBaseModifyViewpointNotification_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Notification corresponding to the "Modify Viewpoint"
//  event.
//
//===========================================================================
//  Inheritance:
//  ------------
//           CAAVisBaseModifyViewpointNotification
//             CATNotification (System Framework)
//
//===========================================================================

//System Framework
#include "CATNotification.h"

class CAAVisBaseModifyViewpointNotification : public CATNotification
{
  CATDeclareClass;
  
public :

  // Constructs a "ModifyViewpoint" notification
  CAAVisBaseModifyViewpointNotification();

  //Destructor
  virtual ~CAAVisBaseModifyViewpointNotification();

private:

  //Copy constructor
  CAAVisBaseModifyViewpointNotification(const CAAVisBaseModifyViewpointNotification &iBrother);

  //Assignment operator
  CAAVisBaseModifyViewpointNotification & operator = (const CAAVisBaseModifyViewpointNotification &iBrother);

};

#endif
