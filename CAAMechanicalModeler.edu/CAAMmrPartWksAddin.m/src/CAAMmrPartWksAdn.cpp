// COPYRIGHT DASSAULT SYSTEMES 2002


// Local Framework
#include "CAAMmrPartWksAdn.h"

// ApplicationFrame Framework 
#include "CATCreateWorkshop.h"

// Creates the CAAMmrPartWksHeader command header class
#include "CATCommandHeader.h"
MacDeclareHeader(CAAMmrPartWksAddinHeader);  


//----------------------------------------------------------------------------
// To create the TIE Object
#include <TIE_CATIPrtWksAddin.h>
TIE_CATIPrtWksAddin(CAAMmrPartWksAdn);

// To declare that the class 
// is a DataExtension of (late type) CAAMmrPartWksAddin
//
CATImplementClass(CAAMmrPartWksAdn, DataExtension, 
                  CATBaseUnknown, CAAMmrPartWksAddin);

// 
// To declare that CAAMmrPartWksAddin implements CATIPrtWksAddin, insert 
// the following line in the interface dictionary:
//
//   CAAMmrPartWksAddin  CATIPrtWksAddin libCAAMmrPartWksAddin
//
//---------------------------------------------------------------------------


CAAMmrPartWksAdn::CAAMmrPartWksAdn()
{
}

CAAMmrPartWksAdn::~CAAMmrPartWksAdn()
{
}

//-----------------------------------------------------------------------------
// CreateCommands
//-----------------------------------------------------------------------------
void CAAMmrPartWksAdn::CreateCommands()
{

  // CAAMmrPartWksCollapseExpandHdr : identifier of the command header
  // CAACafSpecTree                 : name of the module exporting the command 
  // CAACafCollapseExpandCmd        : name of command class 
  // NULL                           : no argument for the command class
  //
  new CAAMmrPartWksAddinHeader("CAAMmrPartWksCollapseExpandHdr", 
                             "CAACafSpecTree", 
                             "CAACafCollapseExpandCmd", (void *)NULL);
   // CAAMmrPartWksFreezeUnfreezeHdr : identifier of the command header
  // CAAMmrFreezeInternalCopy       : name of the module exporting the command 
  // CAAMmrPartWksFreezeUnfreezeCmd : name of command class 
  // NULL                           : no argument for the command class
  //
  new CAAMmrPartWksAddinHeader("CAAMmrPartWksFreezeUnfreezeHdr", 
                                "CAAMmrFreezeInternalCopy", 
                               "CAAMmrPartWksFreezeUnfreezeCmd", (void *)NULL);

	// CAAMmrSetShowModeHdr : identifier of the command header
  // CAAMmrCommands       : name of the module exporting the command 
  // CAAMmrSetShowModeCmd : name of command class 
  // NULL                 : no argument for the command class
  //
  new CAAMmrPartWksAddinHeader("CAAMmrSetShowModeHdr",   
                               "CAAMmrCommands",                        
                               "CAAMmrSetShowModeCmd", (void *)NULL);        
}


//-----------------------------------------------------------------------------
// CreateToolbars
//-----------------------------------------------------------------------------
CATCmdContainer *CAAMmrPartWksAdn::CreateToolbars()
{
  // Spec Tree Toolbar 
  NewAccess(CATCmdContainer, pCAAMmrPartWksSpecTreeTlb, CAAMmrPartWksSpecTreeTlb);
  
  NewAccess(CATCmdStarter, pCAAMmrPartWksCollExpTStr, CAAMmrPartWksCollExpTStr);
  SetAccessCommand(pCAAMmrPartWksCollExpTStr, "CAAMmrPartWksCollapseExpandHdr");
  SetAccessChild(pCAAMmrPartWksSpecTreeTlb, pCAAMmrPartWksCollExpTStr);


  NewAccess(CATCmdStarter, pCAAMmrPartWksFreezeUnfreezeStr, CAAMmrPartWksFreezeUnfreezeStr);
  SetAccessCommand(pCAAMmrPartWksFreezeUnfreezeStr,"CAAMmrPartWksFreezeUnfreezeHdr");
  SetAccessNext(pCAAMmrPartWksCollExpTStr,pCAAMmrPartWksFreezeUnfreezeStr);
  
  NewAccess(CATCmdStarter, pCAAMmrSetShowModeStr, CAAMmrSetShowModeStr);
  SetAccessCommand(pCAAMmrSetShowModeStr,"CAAMmrSetShowModeHdr");
  SetAccessNext(pCAAMmrPartWksFreezeUnfreezeStr,pCAAMmrSetShowModeStr);

  AddToolbarView(pCAAMmrPartWksSpecTreeTlb, -1, Right); // "-1" --> Unvisible Toolbar

   //----------------------
  //  Menubar 
  //----------------------

  NewAccess(CATCmdContainer,pCAAMmrPartWksSpecTreeMbr,CAAMmrPartWksSpecTreeMbr);

  //  Tools menu
  //-----------------------
  NewAccess(CATCmdContainer,pCATAfrToolsMnu,CATAfrToolsMnu);
       SetAccessChild(pCAAMmrPartWksSpecTreeMbr,pCATAfrToolsMnu);

       NewAccess(CATCmdStarter,pCAAMmrPartWksCollExpMStr,CAAMmrPartWksCollExpMStr);
       SetAccessChild(pCATAfrToolsMnu,pCAAMmrPartWksCollExpMStr);
       SetAccessCommand(pCAAMmrPartWksCollExpMStr,"CAAMmrPartWksCollapseExpandHdr");

  // Set the menu 
  // -------------
  SetAddinMenu(pCAAMmrPartWksSpecTreeTlb,pCAAMmrPartWksSpecTreeMbr);

  return pCAAMmrPartWksSpecTreeTlb;
 
  
}

