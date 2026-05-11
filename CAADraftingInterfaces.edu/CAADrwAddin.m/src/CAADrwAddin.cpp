// ================================
// COPYRIGHT DASSAULT SYSTEMES 2007
// ================================

#include "CAADrwAddin.h"

#include "CATCommandHeader.h"
#include "CATCreateWorkshop.h"

#include "CATCmdContainer.h"
#include "CATCmdStarter.h"

MacDeclareHeader(CAADrwHeader);

CATImplementClass( CAADrwAddin,
                   DataExtension,
                   CATBaseUnknown,
                   CAADrwAddn);

//-----------------------------------------------------------------------------
// CAADrwAddin : constructor and destructor
//-----------------------------------------------------------------------------
CAADrwAddin::CAADrwAddin():
    CATBaseUnknown()
{
}

CAADrwAddin::~CAADrwAddin()
{
}

//----------------------------------------------------------------------------- 
// Tie the implementation to its interface
// ----------------------------------------------------------------------------
#include "TIE_CATIDRWFRAMEAddin.h"
TIE_CATIDRWFRAMEAddin(CAADrwAddin);

//----------------------------------------------------
// Implements CATIDRWFRAMEAddin::CreateCommands
//----------------------------------------------------
void CAADrwAddin::CreateCommands()
{
	new CAADrwHeader("DimDressup","CAADrwDimDressup",
					 "CAADrwDimDressupCmd",(void *)NULL);
	new CAADrwHeader("CenterLine","CAADrwCenterLine",
					 "CAADrwCenterLineCmd",(void *)NULL);
	new CAADrwHeader("MultiSheet","CAADrwMultiSheetCmd",
					 "CAADrwMultiSheetCmd",(void *)NULL);
	new CAADrwHeader("CreateDimSystem","CAADrwCreateDimSyst",
					 "CAADrwCreateDimSystCmd",(void *)NULL);
}

//-----------------------------------------------------
// Implements CATIDRWFRAMEAddin::CreateToolbars
//-----------------------------------------------------
CATCmdContainer *CAADrwAddin::CreateToolbars()
{
    NewAccess        (CATCmdContainer, pCAADrwTlb,      CAAUseCaseCommands );
        
    NewAccess        (CATCmdStarter,   pDimDressupStr , DimDressupStr );
    SetAccessCommand (pDimDressupStr,  "DimDressup" );
    SetAccessChild   (pCAADrwTlb,      pDimDressupStr  );

    NewAccess        (CATCmdStarter    , pCenterLineStr , CenterLineStr );
    SetAccessCommand (pCenterLineStr    , "CenterLine" );
    SetAccessNext    (pDimDressupStr , pCenterLineStr  );

    NewAccess        (CATCmdStarter    , pMultiSheetStr , MultiSheetStr );
    SetAccessCommand (pMultiSheetStr   , "MultiSheet" );
    SetAccessNext    (pCenterLineStr , pMultiSheetStr  );

    NewAccess        (CATCmdStarter    , pDimSystStr , DimSystStr );
    SetAccessCommand (pDimSystStr   , "CreateDimSystem" );
    SetAccessNext    (pMultiSheetStr , pDimSystStr  );

    AddToolbarView   (pCAADrwTlb , -1 , UnDock); 

    return pCAADrwTlb;
}
