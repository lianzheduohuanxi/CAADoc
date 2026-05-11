// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAMmrDebugAdn.h"

// ApplicationFrame Framework 
#include "CATCreateWorkshop.h"

// Creates the CAAMmrDebugHeader command header class
#include "CATCommandHeader.h"
MacDeclareHeader(CAAMmrDebugAddinHeader);  


//----------------------------------------------------------------------------
// To create the TIE Object
#include <TIE_CATIPrtWksAddin.h>
TIE_CATIPrtWksAddin(CAAMmrDebugAdn);

// To declare that the class 
// is a DataExtension of (late type) CAAMmrDebugAddin
//
CATImplementClass(CAAMmrDebugAdn, DataExtension, 
                  CATBaseUnknown, CAAMmrDebugAddin);

// 
// To declare that CAAMmrDebugAddin implements CATIPrtWksAddin, insert 
// the following line in the interface dictionary:
//
//   CAAMmrDebugAddin  CATIPrtWksAddin libCAAMmrDebugPrtWksAddin
//
//---------------------------------------------------------------------------


CAAMmrDebugAdn::CAAMmrDebugAdn()
{
}

CAAMmrDebugAdn::~CAAMmrDebugAdn()
{
}


//-----------------------------------------------------------------------------
// CreateCommands
//-----------------------------------------------------------------------------
void CAAMmrDebugAdn::CreateCommands()
{

  // CAAMmrDebugJournalHdr : identifier of the command header
  // CATMmuDebugCAA        : name of the mechanical modeler command class 
  // CATMmuDebugCAA        : name of the module exporting the mechanical modeler command 
  // NULL                  : no argument for the CATMmuDebugCAA command class
  new CAAMmrDebugAddinHeader("CAAMmrDebugJournalHdr", 
                             "CATMmuDebugCAA", 
                             "CATMmuDebugCAA", (void *)NULL);
}


//-----------------------------------------------------------------------------
// CreateToolbars
//-----------------------------------------------------------------------------
CATCmdContainer *CAAMmrDebugAdn::CreateToolbars()
{
  
  // Toolbar Debug 
  NewAccess(CATCmdContainer, pCAAMmrDebugTlb, CAAMmrDebugTlb);
  
  NewAccess(CATCmdStarter, pCAAMmrDebugJournalStr, CAAMmrDebugJournalStr);
  SetAccessCommand(pCAAMmrDebugJournalStr, "CAAMmrDebugJournalHdr");
  SetAccessChild(pCAAMmrDebugTlb, pCAAMmrDebugJournalStr);
  
  AddToolbarView(pCAAMmrDebugTlb, -1, Right); // "-1" --> Unvisible Toolbar
  
  return pCAAMmrDebugTlb;
}

