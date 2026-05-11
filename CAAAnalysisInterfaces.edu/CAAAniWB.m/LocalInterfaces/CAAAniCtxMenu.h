#ifndef CAAAniCtxMenu_H
#define CAAAniCtxMenu_H
// COPYRIGHT Dassault Systemes 2000
//===================================================================
//
// CAAAniCtxMenu.h
// Provide implementation to interface CATISamCtxMenuProvider
// 
//===================================================================

#include "CATBaseUnknown.h"
#include "CATBoolean.h"
class CATCmdContainer;

//-----------------------------------------------------------------------

class CAAAniCtxMenu: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
    CAAAniCtxMenu ();
    virtual ~CAAAniCtxMenu ();

	  HRESULT GetContextualMenu(CATBaseUnknown * iObj, CATCmdContainer* &ioCtxMenu) ;
    CATBoolean IsPermanent() ;

  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAAniCtxMenu (CAAAniCtxMenu &);
  CAAAniCtxMenu& operator=(CAAAniCtxMenu&);

};

//-----------------------------------------------------------------------

#endif


