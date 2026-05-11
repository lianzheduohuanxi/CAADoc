// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAAfrGeneralWksAdn.h"
#include "CAAAfrMRUHeader.h"

// ApplicationFrame Framework 
#include "CATCreateWorkshop.h"
#include "CATAfrCheckHeaderAccessor.h"

// Creates the CAAAfrGeneralWksHeader command header class
#include "CATCommandHeader.h"
MacDeclareHeader(CAAAfrGeneralWksAddinHeader);  


//----------------------------------------------------------------------------
// To create the TIE Object
#include <TIE_CATIAfrGeneralWksAddin.h>
TIE_CATIAfrGeneralWksAddin(CAAAfrGeneralWksAdn);

// To declare that the class 
// is a DataExtension of (late type) CAAAfrGeneralWksAddin
//
CATImplementClass(CAAAfrGeneralWksAdn, DataExtension, 
                  CATBaseUnknown, CAAAfrGeneralWksAddin);

// 
// To declare that CAAAfrGeneralWksAddin implements CATIAfrGeneralWksAddin, insert 
// the following line in the interface dictionary:
//
//   CAAAfrGeneralWksAddin  CATIAfrGeneralWksAddin libCAAAfrGeneralWksAddin
//
//---------------------------------------------------------------------------


CAAAfrGeneralWksAdn::CAAAfrGeneralWksAdn()
{
}

CAAAfrGeneralWksAdn::~CAAAfrGeneralWksAdn()
{
}


//-----------------------------------------------------------------------------
// CreateCommands
//-----------------------------------------------------------------------------
void CAAAfrGeneralWksAdn::CreateCommands()
{

  // Search Demonstrator
  // -------------------
  //
  // CAAAfrSearchHdr        : identifier of the command header
  // CAACafSearch           : name of the module exporting the Search demonstrator command 
  // CAACafSearchCmd        : name of the command class 
  // NULL                   : no argument for the CAACafSearchCmd command class
  //
  new CAAAfrGeneralWksAddinHeader("CAAAfrSearchHdr", 
                             "CAACafSearch", 
                             "CAACafSearchCmd", (void *)NULL);

  // Viewer Feedback Demonstrator
  // ----------------------------
  //
  // CAAAfrViewerFeedbackHdr : identifier of the check command header created by 
  //                           CATAfrCheckHeaderAccessor
  // CAACafViewerFeedback    : name of the module exporting the command to 
  //                           activate / desactivate the viewer feedback
  // CAACafViewerFeedbackCmd : name of the command class 
  // NULL                    : no argument for the CAACafViewerFeedbackCmd command class
  //

  CATAfrCheckHeaderAccessor ViewerFeedbackHdrAccessor ("CAAAfrViewerFeedbackHdr");

  // In the CAAAfrGeneralWksAddinHeader.CATNls/Rsc there are the
  // help, short help ... and the icon for the CAAAfrViewerFeedbackHdr check header
  //
  ViewerFeedbackHdrAccessor.SetResourceFile("CAAAfrGeneralWksAddinHeader");


  // Two CAAAfrGeneralWksAddinHeader class instances are created 
  // to associate the check/uncheck behaviors. 
  // When the end user checks the button, the CAAAfrViewerFeedbackHdr check 
  // header starts the CAACafViewerFeedbackCheckHdr command header, otherwise
  // it starts the CAACafViewerFeedbackUncheckHdr. 
  //
  // CAACafViewerFeedbackCheckHdr and CAACafViewerFeedbackUncheckHdr are 
  // without NLS resources because there are any visual representation,and they are
  // hidden in the Command tab page of the Tools/Customize command
  // 
  // The CAACafViewerFeedbackCmd, thanks to the argument, activates or
  // deactivates the viewer feedback. see CAACATIAApplicationFrm.edu
  // 
  CATCommandHeader * pHdr = (CATCommandHeader*) new CAAAfrGeneralWksAddinHeader("CAACafViewerFeedbackCheckHdr", 
                             "CAACafViewerFeedback", 
                             "CAACafViewerFeedbackCmd", (void *)1);
  if (NULL != pHdr) pHdr->SetVisibility(0);

  pHdr = (CATCommandHeader*) new CAAAfrGeneralWksAddinHeader("CAACafViewerFeedbackUncheckHdr", 
                             "CAACafViewerFeedback", 
                             "CAACafViewerFeedbackCmd", (void *)2);
  if (NULL != pHdr) pHdr->SetVisibility(0);

 
  ViewerFeedbackHdrAccessor.SetCheckCommand("CAACafViewerFeedbackCheckHdr");
  ViewerFeedbackHdrAccessor.SetUncheckCommand("CAACafViewerFeedbackUncheckHdr");


  // Cutsomized command header 
  // 
  CATCommandHeader * pHdrMRU = (CATCommandHeader*) new CAAAfrMRUHeader("CAAAfrMRUHdr");
  if (NULL != pHdrMRU) pHdrMRU->SetVisibility(0);

  pHdrMRU = (CATCommandHeader*) new CAAAfrGeneralWksAddinHeader("CAAAfrMRUSelElementHdr", 
                             "CAAAfrGeoCommands", 
                             "CAAAfrMRUSelElementCmd",
                             (void *) NULL);
  if (NULL != pHdrMRU) pHdrMRU->SetVisibility(0);

  // This hdr is launched thanks to a starter 
  new CAAAfrGeneralWksAddinHeader("CAAAfrMRUAddElementHdr", 
                             "CAAAfrGeoCommands", 
                             "CAAAfrMRUAddElementCmd",
                             (void *) NULL);

  // This hdr is launched when the end user sel an element in the 
  // MRU item list - See CAAEAfrCommandHeaderRepForMRU
  //
  
  // Center Graph Demonstrator
  // -------------------------
  //
  // CAAAfrCenterGraphHdr   : identifier of the command header
  // CAACafCenterGraph      : name of the module exporting the Center Graph demonstrator command 
  // CAACafCenterGraphCmd   : name of the command class 
  // NULL                   : no argument for the CAACafCenterGraphCmd command class
  //
  new CAAAfrGeneralWksAddinHeader("CAAAfrCenterGraphHdr", 
    "CAACafCenterGraph", 
    "CAACafCenterGraphCmd", (void *)NULL);
}


//-----------------------------------------------------------------------------
// CreateToolbars
//-----------------------------------------------------------------------------
CATCmdContainer *CAAAfrGeneralWksAdn::CreateToolbars()
{
  //----------------------
  // Toolbar 
  //----------------------
  NewAccess(CATCmdContainer, pCAAAfrGeneralWksTlb, CAAAfrGeneralWksTlb);
  
  NewAccess(CATCmdStarter, pCAAAfrSearchStr, CAAMmrGeneralSearchStr);
  SetAccessCommand(pCAAAfrSearchStr, "CAAAfrSearchHdr");
  SetAccessChild(pCAAAfrGeneralWksTlb, pCAAAfrSearchStr);

  NewAccess(CATCmdStarter, pCAAAfrViewerFeedbackStr, CAAAfrViewerFeedbackStr);
  SetAccessCommand(pCAAAfrViewerFeedbackStr, "CAAAfrViewerFeedbackHdr");
  SetAccessNext(pCAAAfrSearchStr, pCAAAfrViewerFeedbackStr);

  NewAccess(CATCmdStarter, pCAAAfrMRUAddElementStr, CAAAfrMRUAddElementStr);
  SetAccessCommand(pCAAAfrMRUAddElementStr, "CAAAfrMRUAddElementHdr");
  SetAccessNext(pCAAAfrViewerFeedbackStr, pCAAAfrMRUAddElementStr);

  AddToolbarView(pCAAAfrGeneralWksTlb, 1, Right); 

  //----------------------
  //  Menubar 
  //----------------------

  NewAccess(CATCmdContainer,pCAAAfrGeneralWksMbr,CAAAfrGeneralWksMbr);

  //  File menu
  //------------------------------------------------------
  NewAccess(CATCmdContainer,pCAAAfrGeneralFileMnu,CATAfrFileMnu);
       SetAccessChild(pCAAAfrGeneralWksMbr,pCAAAfrGeneralFileMnu);

       NewAccess(CATCmdStarter,pCAAAfrGeneralFileMRUStr,CAAAfrGeneralFileMRUStr);
       SetAccessChild(pCAAAfrGeneralFileMnu,pCAAAfrGeneralFileMRUStr);
       SetAccessCommand(pCAAAfrGeneralFileMRUStr,"CAAAfrMRUHdr");
       SetAccessAnchorName(pCAAAfrGeneralFileMRUStr,"CATAfrFileExitStr"); // Before Exit 

  //  Edit menu
  //------------------------------------------------------
  NewAccess(CATCmdContainer,pCAAAfrGeneralEditMnu,CATAfrEditMnu);
       SetAccessNext(pCAAAfrGeneralFileMnu,pCAAAfrGeneralEditMnu);

       NewAccess(CATCmdStarter,pCAAAfrGeneralEditSearchStr,CAAAfrGeneralEditSearchStr);
       SetAccessChild(pCAAAfrGeneralEditMnu,pCAAAfrGeneralEditSearchStr);
       SetAccessCommand(pCAAAfrGeneralEditSearchStr,"CAAAfrSearchHdr");
       SetAccessAnchorName(pCAAAfrGeneralEditSearchStr,"CATAfrEditSearchStr"); // Before Search

  //  View menu
  //------------------------------------------------------
  NewAccess(CATCmdContainer,pCAAAfrGeneralView,CATAfrView);
     SetAccessNext(pCAAAfrGeneralEditMnu,pCAAAfrGeneralView);

       NewAccess(CATCmdStarter,pCAAAfrGeneralViewFBStr,CAAAfrGeneralViewFBStr);
       SetAccessChild(pCAAAfrGeneralView,pCAAAfrGeneralViewFBStr);
       SetAccessCommand(pCAAAfrGeneralViewFBStr,"CAAAfrViewerFeedbackHdr");

  // Set the menu 
  // -------------
  SetAddinMenu(pCAAAfrGeneralWksTlb,pCAAAfrGeneralWksMbr);


  return pCAAAfrGeneralWksTlb;
}

