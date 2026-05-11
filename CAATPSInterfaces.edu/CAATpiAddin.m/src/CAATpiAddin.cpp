/**
 * @quickReview CNA 09:05:18
 * @quickReview ZGG 02:03:05
 * @quickReview CGK 02:02:21
 */
// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// CAATpiAddin
//   Addin to add CAA sample commands to Tolerancing & Annotations workbench.
//   Provide implementation for CATITPSCfgAddin interface.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Fev. 2002  Creation
//=============================================================================

//---------------------------------------------- Include File of this extension
#include "CAATpiAddin.h"

//---------------------------------------------------------------------- System
#include "CATLib.h"
#include "CATGetEnvValue.h"

//------------------------------------------------------------ ApplicationFrame
#include "CATCreateWorkshop.h"

//-------------------------------------------------------- CATTPSInterfaces.edu
#include "CAATpiHeader.h"

//--------------------------------------------------------- Supported Interface
#include "TIE_CATITPSCfgAddin.h"
TIE_CATITPSCfgAddin(CAATpiAddin);

CATImplementClass (CAATpiAddin, DataExtension, CATBaseUnknown, CAATpiAddinObj);

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAATpiAddin::CAATpiAddin()
{}


//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAATpiAddin::~CAATpiAddin()
{}


//-----------------------------------------------------------------------------
// CreateCommands                                               CATITPSCfgAddin
//-----------------------------------------------------------------------------
void CAATpiAddin::CreateCommands()
{
  new CAATpiHeader("CAATpiCreateTextHdr", // Header name
                   "CAATPSInterfaces",    // Module containing the command
                   "CAATpiCreateTextCmd", // Command class name
                   (void*)NULL);

  new CAATpiHeader("CAATpiRetrieveAnnotationHdr",
                   "CAATPSInterfaces",
                   "CAATpiRetrieveAnnotationCmd",
                   (void*)NULL);

  new CAATpiHeader("CAATpiAccessGeometryHdr",
                   "CAATPSInterfaces",
                   "CAATpiAccessGeometryCmd",
                   (void*)NULL);

  new CAATpiHeader("CAATpiDumpTextContentHdr",
                   "CAATPSInterfaces",
                   "CAATpiDumpTextContentCmd",
                   (void*)NULL);

  if(CATGetEnv("CAT_FTA_R193_GLOBAL_COPY"))
  {
    new CAATpiHeader("CAATpiAnnotationSetGlobalCopyHdr", "CAATPSInterfaces", "CAATpiAnnotSetGlobalCopyCmd", (void*)NULL);
    new CAATpiHeader("CAATpiAnnotationSetGlobalCopyTransfoHdr", "CAATPSInterfaces", "CAATpiAnnotSetGlobalCopyTransfoCmd", (void*)NULL);
  }
}


//-----------------------------------------------------------------------------
// CreateToolbars                                               CATITPSCfgAddin
//-----------------------------------------------------------------------------
CATCmdContainer * CAATpiAddin::CreateToolbars()
{
  // Create container and starter
  NewAccess (CATCmdContainer, opCAATpiContainer, CAATpiSampleTlb);

    NewAccess (CATCmdStarter, pStarterCAATpi1, ButtonCAATpi1);
    SetAccessCommand (pStarterCAATpi1, "CAATpiCreateTextHdr");
    SetAccessChild (opCAATpiContainer, pStarterCAATpi1);

    NewAccess (CATCmdStarter, pStarterCAATpi2, ButtonCAATpi2);
    SetAccessCommand(pStarterCAATpi2,"CAATpiRetrieveAnnotationHdr");
    SetAccessNext (pStarterCAATpi1, pStarterCAATpi2);

    NewAccess(CATCmdStarter, pStarterCAATpi3, ButtonCAATpi3);
    SetAccessCommand(pStarterCAATpi3, "CAATpiAccessGeometryHdr");
    SetAccessNext(pStarterCAATpi2, pStarterCAATpi3);

    NewAccess(CATCmdStarter, pStarterCAATpi4, ButtonCAATpi4);
    SetAccessCommand(pStarterCAATpi4,"CAATpiDumpTextContentHdr");
    SetAccessNext(pStarterCAATpi3, pStarterCAATpi4);

    if(CATGetEnv("CAT_FTA_R193_GLOBAL_COPY"))
    {
      NewAccess(CATCmdStarter, pStarterCAATpi5, ButtonCAATpi5);
      SetAccessCommand(pStarterCAATpi5, "CAATpiAnnotationSetGlobalCopyHdr");
      SetAccessNext(pStarterCAATpi4, pStarterCAATpi5);

      NewAccess(CATCmdStarter, pStarterCAATpi6, ButtonCAATpi6);
      SetAccessCommand(pStarterCAATpi6, "CAATpiAnnotationSetGlobalCopyTransfoHdr");
      SetAccessNext(pStarterCAATpi5, pStarterCAATpi6);
    }

  // Invisible Toolbar (-1) that appear Undocked
  AddToolbarView (opCAATpiContainer, -1, UnDock);

  return (opCAATpiContainer);
}
