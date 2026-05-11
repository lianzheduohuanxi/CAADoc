// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2008
//===================================================================
//
// Usage notes: Sample Command
//
//===================================================================
#include "CAAMaiAddinCmd.h"

#include "CAAMaiStandardMPCom.h"
#include "CAAMaiStandardMPCom2.h"

#include "CATCommandHeader.h"

#include <CATCreateWorkshop.h>

CATImplementClass(CAAMaiAddinCmd,
				  Implementation,
				  CATBaseUnknown,
				  CATnull);

//TIE or TIEchain definitions
#include "TIE_CATIManufacturingProgramAddin.h"
TIE_CATIManufacturingProgramAddin(CAAMaiAddinCmd);

MacDeclareHeader(SampleCmdHdr);

//-----------------------------------------------------------------------------
// CAAMaiAddinCmd : constructor
//-----------------------------------------------------------------------------
CAAMaiAddinCmd::CAAMaiAddinCmd():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAMaiAddinCmd : destructor
//-----------------------------------------------------------------------------
CAAMaiAddinCmd::~CAAMaiAddinCmd()
{
}

//-----------------------------------------------------------------------------
// CAAMaiAddinCmd : CreateCommands
//-----------------------------------------------------------------------------
void CAAMaiAddinCmd::CreateCommands()
{
	static CATString DummyArg("");

  // The following command headers have a dedicated resource file for icons 
  // named SampleCmdHdr.CATRsc
	// sample command
	new SampleCmdHdr(	"CAAMaiStandardMPCom",
								"CAAMaiToolBarFromCatalog",
								"CAAMaiStandardMPCom",
								(void *) &DummyArg);
	// sample command
	new SampleCmdHdr(	"CAAMaiStandardMPCom2",
								"CAAMaiToolBarFromCatalog",
								"CAAMaiStandardMPCom2",
								(void *) &DummyArg);
}

//-----------------------------------------------------------------------------
// CAAMaiAddinCmd : CreateToolbars
//-----------------------------------------------------------------------------
CATCmdContainer* CAAMaiAddinCmd::CreateToolbars()
{
	// Creation of the Toolbar
	NewAccess(CATCmdContainer, pNCToolBar, NULSampleToolBar);
	SetAccessTitle(pNCToolBar,"NCToolBar");
	AddToolbarView(pNCToolBar, 1, Left);

  // Sub-Container Child of Tool bar
  NewAccess(CATCmdContainer,CATCmdContainer_StandardDrillingMP,StandardDrillingMPContainer);
  {
    NewAccess(CATCmdStarter,MfgStandardDrilling,StandardDrilling);
    SetAccessCommand(MfgStandardDrilling,"StandardDrilling");
    SetAccessChild (CATCmdContainer_StandardDrillingMP,MfgStandardDrilling);

    NewAccess(CATCmdStarter,MfgMPForCAAMaiStandardMPCom,CAAMaiStandardMPCom);
    SetAccessCommand(MfgMPForCAAMaiStandardMPCom,"CAAMaiStandardMPCom");
    SetAccessNext (MfgStandardDrilling,MfgMPForCAAMaiStandardMPCom);
  }
	SetAccessChild	(pNCToolBar, CATCmdContainer_StandardDrillingMP);

  // Other Sub-Containers after the previous ones

  NewAccess (CATCmdContainer,CATCmdContainer_StandardOtherMP,StandardOtherMPContainer);
  {
    NewAccess(CATCmdStarter,MfgMPForCAAMaiStandardMPCom2,CAAMaiStandardMPCom2);
    SetAccessCommand(MfgMPForCAAMaiStandardMPCom2,"CAAMaiStandardMPCom2");
    SetAccessChild (CATCmdContainer_StandardOtherMP,MfgMPForCAAMaiStandardMPCom2);

    NewAccess(CATCmdStarter,MfgMPForCAAMaiStandardMPCom,CAAMaiStandardMPCom);
    SetAccessCommand(MfgMPForCAAMaiStandardMPCom,"CAAMaiStandardMPCom");
    SetAccessNext (MfgMPForCAAMaiStandardMPCom2,MfgMPForCAAMaiStandardMPCom);
  }
	SetAccessNext	(CATCmdContainer_StandardDrillingMP, CATCmdContainer_StandardOtherMP);

	return pNCToolBar;
}
