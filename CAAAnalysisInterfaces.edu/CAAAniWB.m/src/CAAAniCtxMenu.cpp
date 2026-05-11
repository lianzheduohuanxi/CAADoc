// COPYRIGHT Dassault Systemes 2000
//===================================================================
// CAAAniCtxMenu.h
// Provide implementation to interface CATISamCtxMenuProvider.
// Provide some contextual menus associated to the CAA Analysis Workbench.
//===================================================================
#include "CAAAniCtxMenu.h"      // this include

#include "CATCreateWorkshop.h"  // New access
#include "CATAfrCommandHeaderServices.h"
#include "CATCommandHeader.h"   //
#include "CATCmdContainer.h"    //

#include "CATISpecObject.h"     // To Test the Object
#include "CATString.h"


CATImplementClass(CAAAniCtxMenu,Implementation,CATBaseUnknown,CATnull);

//-----------------------------------------------------------------------------
// CAAAniCtxMenu : constructor
//-----------------------------------------------------------------------------
CAAAniCtxMenu::CAAAniCtxMenu():
CATBaseUnknown()
{}
//-----------------------------------------------------------------------------
// CAAAniCtxMenu : destructor
//-----------------------------------------------------------------------------
CAAAniCtxMenu::~CAAAniCtxMenu()
{}
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATISamCtxMenuProvider.h"
TIE_CATISamCtxMenuProvider( CAAAniCtxMenu);
//-----------------------------------------------------------------------------
// Implements CAAAniCtxMenu::GetContextualMenu
//-----------------------------------------------------------------------------
HRESULT CAAAniCtxMenu::GetContextualMenu(CATBaseUnknown * iObj, CATCmdContainer* &ioCtxMenu)
{
  CATISpecObject_var spSpecObj (iObj);
  if (NULL_var == spSpecObj) return S_OK;

  CATString FeatureType = ((spSpecObj -> GetType()).ConvertToChar());

  CATCommandHeader* pHeader = NULL;
  if (FeatureType == "AeroDynamicSet")              
  {
    CATString HeaderId = "CreateOneImage" ;    // header defined in the CAAAniCfg.cpp
    NewAccess (CATCmdStarter ,CmdStarterCreateOneImage ,CAAAniCreateOneImage);
    SetAccessCommand	(CmdStarterCreateOneImage,HeaderId);
    if (ioCtxMenu) ioCtxMenu -> AddChild (CmdStarterCreateOneImage);

    CATAfrGetCommandHeader(HeaderId,pHeader);
    if (pHeader)
    {
      pHeader -> BecomeUnavailable();
      if (spSpecObj -> IsUpToDate()) pHeader -> BecomeAvailable();
    }
  }
  else if (FeatureType == "MSHPartOctree2D")              
  {
    CATString HeaderId = "CreateOneMeshOperator" ;
    NewAccess (CATCmdStarter ,CmdStarterCreateOneMeshOperator ,CAAAniOperHoleCmd);
    SetAccessCommand	(CmdStarterCreateOneMeshOperator,HeaderId);
    if (ioCtxMenu) ioCtxMenu -> AddChild (CmdStarterCreateOneMeshOperator);
    CATAfrGetCommandHeader(HeaderId,pHeader);

  }


  return S_OK;
}
//===========================================================================================
CATBoolean CAAAniCtxMenu::IsPermanent()
{
  return FALSE;
}
//===========================================================================================





