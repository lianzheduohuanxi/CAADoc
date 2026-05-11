#ifndef CAAVisBaseOpenNotification_h
#define CAAVisBaseOpenNotification_h

// COPYRIGHT DASSAULT SYSTEMES 2000

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
//           CAAVisBaseOpenNotification
//             CATNotification (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//  GetFileName : gets the CGR file name to open.
//===========================================================================

//System Framework
#include "CATNotification.h"

class CAAVisBaseOpenNotification : public CATNotification
{
  CATDeclareClass;
  
public :

  // Constructs an Open notification from
  // the name of the CGR file containing
  // the model to Open.
  // Parameters
  //   iFileName
  //     The CGR file name.
  CAAVisBaseOpenNotification(const char *iFileName);

  //Destructor
  virtual ~CAAVisBaseOpenNotification();

  // Gets the name of the CGR file containing
  // the model to read.
  const char * GetFileName();

private:

  //Default constructor
  CAAVisBaseOpenNotification();

  //Copy constructor
  CAAVisBaseOpenNotification(const CAAVisBaseOpenNotification &iBrother);

  //Assignment operator
  CAAVisBaseOpenNotification & operator = (const CAAVisBaseOpenNotification &iBrother);

private:

  char *_pFileName;
};

#endif
