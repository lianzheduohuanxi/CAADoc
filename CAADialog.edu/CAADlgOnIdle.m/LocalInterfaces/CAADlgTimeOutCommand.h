#ifndef CAADlgCommand_H
#define CAADlgCommand_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the class
//  -----------------------
//
//  The command is necessary to show timeOut callback.
//
//=============================================================================
 
// System Framework
#include "CATCommand.h"        // To derive from

// Local Framework 
class CAADlgInterApplication ; // For the constructor

class CAADlgTimeOutCommand: public CATCommand 
{
  public:

    CAADlgTimeOutCommand(CAADlgInterApplication * iParent);
    virtual ~CAADlgTimeOutCommand();

    // Method calls when the timeout is ellapsed
    //
    static void CAADlgTimeOut(CATCommand             * iToClient, 
                              int                      iTime, 
                              void                   * iUsefulData);

  private:
    
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgTimeOutCommand ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgTimeOutCommand(const CAADlgTimeOutCommand &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgTimeOutCommand & operator = (const CAADlgTimeOutCommand &iObjectToCopy);
};

#endif
