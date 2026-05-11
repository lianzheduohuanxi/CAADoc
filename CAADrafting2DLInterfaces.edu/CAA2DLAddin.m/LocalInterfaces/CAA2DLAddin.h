// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// CAA2DLAddin
//   Addin to add CAA sample commands to 2DL workbenchs.
//   Provide implementation for CATI2DLMainWkbAddin interface.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Dec. 2007  Creation
//=============================================================================

#ifndef CAA2DLAddin_H
#define CAA2DLAddin_H

#include "CATBaseUnknown.h"

class CATCmdContainer;

//-----------------------------------------------------------------------------
class CAA2DLAddin : public CATBaseUnknown
{
  CATDeclareClass;

  public:

    CAA2DLAddin ();
    virtual ~CAA2DLAddin ();

    // CATIWorkbenchAddin
    // CATI2DLMainWkbAddin
    virtual void CreateCommands();
    virtual CATCmdContainer * CreateToolbars();

  private:
    // must not be implemented
    CAA2DLAddin (CAA2DLAddin &);
    CAA2DLAddin& operator=(CAA2DLAddin&);

};
#endif
