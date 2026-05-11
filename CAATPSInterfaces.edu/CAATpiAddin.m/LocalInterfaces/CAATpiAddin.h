// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// CAATpiAddin
//   Addin to add CAA sample commands to Tolerancing & Annotations workbenchs.
//   Provide implementation for CATITPSCfgAddin interface.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Fev. 2002  Creation
//=============================================================================

#ifndef CAATpiAddin_H
#define CAATpiAddin_H

#include "CATBaseUnknown.h"

class CATCmdContainer;

//-----------------------------------------------------------------------------
class CAATpiAddin : public CATBaseUnknown
{
  CATDeclareClass;

  public:

    CAATpiAddin ();
    virtual ~CAATpiAddin ();

    // CATIWorkbenchAddin
    // CATITPSCfgAddin
    virtual void CreateCommands();
    virtual CATCmdContainer * CreateToolbars();

  private:
    // must not be implemented
    CAATpiAddin (CAATpiAddin &);
    CAATpiAddin& operator=(CAATpiAddin&);

};
#endif
