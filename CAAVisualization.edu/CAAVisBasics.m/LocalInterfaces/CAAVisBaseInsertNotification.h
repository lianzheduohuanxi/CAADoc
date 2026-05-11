#ifndef CAAVisBaseInsertNotification_h
#define CAAVisBaseInsertNotification_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Notification corresponding to the "Insert"
//  event.
//
//===========================================================================
//  Inheritance:
//  ------------
//           CAAVisBaseInsertNotification
//             CATNotification (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//  GetFileName : gets the CGR file name to open.
//===========================================================================

//System Framework
#include "CATNotification.h"

class CAAVisBaseInsertNotification : public CATNotification
{
  CATDeclareClass;
  
public :

  // Constructs an insert notification from
  // the name of the CGR file containing
  // the model to insert.
  // Parameters
  //   iFileName
  //     The CGR file name.
  CAAVisBaseInsertNotification(const char *iFileName);

  //Destructor
  virtual ~CAAVisBaseInsertNotification();

  // Gets the name of the CGR file containing
  // the model to read.
  const char * GetFileName();

private:

  //Default constructor
  CAAVisBaseInsertNotification();

  //Copy constructor
  CAAVisBaseInsertNotification(const CAAVisBaseInsertNotification &iBrother);

  //Assignment operator
  CAAVisBaseInsertNotification & operator = (const CAAVisBaseInsertNotification &iBrother);

private:
  char *_pFileName;
};

#endif
