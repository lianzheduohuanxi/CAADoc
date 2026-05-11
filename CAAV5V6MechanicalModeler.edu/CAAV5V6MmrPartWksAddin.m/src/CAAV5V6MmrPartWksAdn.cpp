// COPYRIGHT DASSAULT SYSTEMES 2012

#include "CATIAV5Level.h"

// Local Framework
#include "CAAV5V6MmrPartWksAdn.h"

// ApplicationFrame Framework in V5
// AfrFoundation Framework in V6 
#include "CATCreateWorkshop.h"

// CATMecModUIUseItf Framework in V6
// MechanicalModelerUI Framework in V5
#include "TIE_CATIPrtWksAddin.h"
TIE_CATIPrtWksAddin(CAAV5V6MmrPartWksAdn);

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

// AfrFoundaton Framework
#include "CATAfrCommandHeader.h"  

#else
//============================================== 
// V5 only
//============================================== 

// ApplicationFrame Framework
#include "CATCommandHeader.h"
MacDeclareHeader(CAAV5V6MmrPartWksAddinHeader); 
#endif

//----------------------------------------------------------------------------


// To declare that the class 
// is a DataExtension of (late type) CAAV5V6MmrPartWksAddin
//
CATImplementClass(CAAV5V6MmrPartWksAdn, DataExtension, 
                  CATBaseUnknown, CAAV5V6MmrPartWksAddin);

// 
// To declare that CAAV5V6MmrPartWksAddin implements CATIPrtWksAddin, insert 
// the following line in the interface dictionary:
//
//   CAAV5V6MmrPartWksAddin  CATIPrtWksAddin libCAAV5V6MmrPartWksAddin
//
//---------------------------------------------------------------------------


CAAV5V6MmrPartWksAdn::CAAV5V6MmrPartWksAdn()
{
}

CAAV5V6MmrPartWksAdn::~CAAV5V6MmrPartWksAdn()
{
}

//-----------------------------------------------------------------------------
// CreateCommands
//-----------------------------------------------------------------------------
void CAAV5V6MmrPartWksAdn::CreateCommands()
{

  // CAAV5V6MmrPartWksCollapseExpandHdr : identifier of the command header
  // CAAOmbSpecTree                     : name of the module exporting the command 
  // CAAOmbCollapseExpandCmd            : name of command class 
  // NULL                               : no argument for the command class
  //
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
  CATAfrCommandHeader::CATCreateCommandHeader("CAAV5V6MmrPartWksCollapseExpandHdr",   
                               "CAAOmbSpecTree",                        
                               "CAAOmbCollapseExpandCmd",                    
   							   (void *)NULL,                                  
							   "CAAV5V6MmrPartWksAddinHeader",		          
							   CATFrmAvailable);


  // CAAV5V6MmrPartWksFreezeUnfreezeHdr : identifier of the command header
  // CAAV5V6MmrFreezeInternalCopy       : name of the module exporting the command 
  // CAAV5V6MmrPartWksFreezeUnfreezeCmd : name of command class 
  // NULL                           : no argument for the command class
  //
  CATAfrCommandHeader::CATCreateCommandHeader("CAAV5V6MmrPartWksFreezeUnfreezeHdr",   
                               "CAAV5V6MmrFreezeInternalCopy",                        
                               "CAAV5V6MmrPartWksFreezeUnfreezeCmd",                    
   							   (void *)NULL,                                  
							   "CAAV5V6MmrPartWksAddinHeader",		          
							   CATFrmAvailable);

  // CAAV5V6MmrSetShowModeHdr : identifier of the command header
  // CAAV5V6MmrSetShowMode    : name of the module exporting the command 
  // CAAV5V6MmrSetShowModeCmd : name of command class 
  // NULL                 : no argument for the command class
  //
  CATAfrCommandHeader::CATCreateCommandHeader("CAAV5V6MmrSetShowModeHdr",   
                               "CAAV5V6MmrCommands",                        
                               "CAAV5V6MmrSetShowModeCmd",                    
   							   (void *)NULL,                                  
							   "CAAV5V6MmrPartWksAddinHeader",		          
							   CATFrmAvailable); 
#else
//============================================== 
// V5 only
//============================================== 

  // CAAV5V6MmrPartWksCollapseExpandHdr : identifier of the command header
  // CAACafSpecTree                 : name of the module exporting the command 
  // CAACafCollapseExpandCmd        : name of command class 
  // NULL                           : no argument for the command class
  //
  new CAAV5V6MmrPartWksAddinHeader("CAAV5V6MmrPartWksCollapseExpandHdr", 
                                   "CAACafSpecTree", 
                                   "CAACafCollapseExpandCmd", (void *)NULL);


  // CAAV5V6MmrPartWksFreezeUnfreezeHdr : identifier of the command header
  // CAAV5V6MmrFreezeInternalCopy       : name of the module exporting the command 
  // CAAV5V6MmrPartWksFreezeUnfreezeCmd : name of command class 
  // NULL                               : no argument for the command class
  //
  new CAAV5V6MmrPartWksAddinHeader("CAAV5V6MmrPartWksFreezeUnfreezeHdr", 
                                   "CAAV5V6MmrFreezeInternalCopy", 
                                   "CAAV5V6MmrPartWksFreezeUnfreezeCmd", (void *)NULL);

  // CAAV5V6MmrSetShowModeHdr : identifier of the command header
  // CAAV5V6MmrCommands       : name of the module exporting the command 
  // CAAV5V6MmrSetShowModeCmd : name of command class 
  // NULL                     : no argument for the command class
  //
  new CAAV5V6MmrPartWksAddinHeader("CAAV5V6MmrSetShowModeHdr",   
                                   "CAAV5V6MmrCommands",                        
                                   "CAAV5V6MmrSetShowModeCmd", (void *)NULL);       
#endif
}


//-----------------------------------------------------------------------------
// CreateToolbars
//-----------------------------------------------------------------------------
CATCmdContainer *CAAV5V6MmrPartWksAdn::CreateToolbars()
{
   
  // Spec Tree Toolbar 
  NewAccess(CATCmdContainer, pCAAV5V6MmrPartWksSpecTreeTlb, CAAV5V6MmrPartWksSpecTreeTlb);
  
  NewAccess(CATCmdStarter, pCAAV5V6MmrPartWksCollExpTStr, CAAV5V6MmrPartWksCollExpTStr);
  SetAccessCommand(pCAAV5V6MmrPartWksCollExpTStr, "CAAV5V6MmrPartWksCollapseExpandHdr");
  SetAccessChild(pCAAV5V6MmrPartWksSpecTreeTlb, pCAAV5V6MmrPartWksCollExpTStr);
    
  NewAccess(CATCmdStarter, pCAAV5V6MmrPartWksFreezeUnfreezeStr, CAAV5V6MmrPartWksFreezeUnfreezeStr);
  SetAccessCommand(pCAAV5V6MmrPartWksFreezeUnfreezeStr,"CAAV5V6MmrPartWksFreezeUnfreezeHdr");
  SetAccessNext(pCAAV5V6MmrPartWksCollExpTStr,pCAAV5V6MmrPartWksFreezeUnfreezeStr);
  
  NewAccess(CATCmdStarter, pCAAV5V6MmrSetShowModeStr, CAAV5V6MmrSetShowModeStr);
  SetAccessCommand(pCAAV5V6MmrSetShowModeStr,"CAAV5V6MmrSetShowModeHdr");
  SetAccessNext(pCAAV5V6MmrPartWksFreezeUnfreezeStr,pCAAV5V6MmrSetShowModeStr);

  AddToolbarView(pCAAV5V6MmrPartWksSpecTreeTlb, -1, Right); // "-1" --> Unvisible Toolbar
    
  //----------------------
  //  Menubar 
  //----------------------

  NewAccess(CATCmdContainer,pCAAV5V6MmrPartWksSpecTreeMbr,CAAV5V6MmrPartWksSpecTreeMbr);

  //  Tools menu
  //-----------------------
  NewAccess(CATCmdContainer,pCATAfrToolsMnu,CATAfrToolsMnu);
  SetAccessChild(pCAAV5V6MmrPartWksSpecTreeMbr,pCATAfrToolsMnu);

  NewAccess(CATCmdStarter,pCAAV5V6MmrPartWksCollExpMStr,CAAV5V6MmrPartWksCollExpMStr);
  SetAccessChild(pCATAfrToolsMnu,pCAAV5V6MmrPartWksCollExpMStr);
  SetAccessCommand(pCAAV5V6MmrPartWksCollExpMStr,"CAAV5V6MmrPartWksCollapseExpandHdr");

  // Set the menu 
  // -------------
  SetAddinMenu(pCAAV5V6MmrPartWksSpecTreeTlb,pCAAV5V6MmrPartWksSpecTreeMbr);

  return pCAAV5V6MmrPartWksSpecTreeTlb;
}

