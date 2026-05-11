#ifndef CAADlgBBMessageNotification_h
#define CAADlgBBMessageNotification_h

// COPYRIGHT DASSAULT SYSTEMES 1999
//   
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Received Message Notification class. 
//
//
//===========================================================================

// System Framework
#include "CATNotification.h"    // Needed to derive from CATNotification

class CAADlgBBMessageNotification : public CATNotification
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
  public:

    CAADlgBBMessageNotification(char * iText);
    virtual ~CAADlgBBMessageNotification();

    HRESULT GetText(char  ** oText ) ;


  private:
    
    // Constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBBMessageNotification();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBBMessageNotification(const CAADlgBBMessageNotification &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBBMessageNotification & operator = (const CAADlgBBMessageNotification &iObjectToCopy);

  private:

  // The text sent by the sender application
  char * _Text ;
     
};

#endif
