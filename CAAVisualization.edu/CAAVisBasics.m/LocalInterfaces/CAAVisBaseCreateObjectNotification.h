#ifndef CAAVisBaseCreateObjectNotification_h
#define CAAVisBaseCreateObjectNotification_h

// COPYRIGHT DASSAULT SYSTEMES 2005

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Notification corresponding to the "Open"
//  event.
//
//===========================================================================
//  Inheritance:
//  ------------
//           CAAVisBaseCreateObjectNotification
//             CATNotification (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//  GetFileName : gets the CGR file name to open.
//===========================================================================

//System Framework
#include "CATNotification.h"

#include "CAAVisObjectType.h"

class CAAVisBaseCreateObjectNotification : public CATNotification
{
  CATDeclareClass;
  
public :

  // Constructs an Open notification from
  // the name of the CGR file containing
  // the model to Open.
  // Parameters
  //   iFileName
  //     The CGR file name.
  CAAVisBaseCreateObjectNotification(CAAVisObjectType iObjectType);

  //Destructor
  virtual ~CAAVisBaseCreateObjectNotification();

  // Gets the type of the object to be created.
  CAAVisObjectType GetObjectType();

private:

  //Default constructor
  CAAVisBaseCreateObjectNotification();

  //Copy constructor
  CAAVisBaseCreateObjectNotification(const CAAVisBaseCreateObjectNotification &iBrother);

  //Assignment operator
  CAAVisBaseCreateObjectNotification & operator = (const CAAVisBaseCreateObjectNotification &iBrother);

private:

  CAAVisObjectType _objectType;
};

#endif
