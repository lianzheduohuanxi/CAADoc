// COPYRIGHT DASSAULT SYSTEMES 2006
#include "CAAxPDMCheckInOutCmd.h"


#ifdef _WINDOWS_SOURCE
#include <io.h>
#endif
//include System
#include "CATStdIO.h"
#include "CATGetEnvValue.h"
//include ApplicationFrame
#include "CATApplicationFrame.h"
#include "CATDlgNotify.h"
//include CATxPDMInterfaces
#include "CATxPDMSessionServices.h"
#include "CATIxPDMSession.h"
#include "CATIxPDMItem.h"
//include ApplicationFrame
#include "CATApplicationFrame.h"

#include "CATCreateExternalObject.h"
CATCreateClassArg(CAAxPDMCheckInOutCmd,CATString);


CATImplementClass(CAAxPDMCheckInOutCmd, Implementation, CATStateCommand,CATNull);

CATUnicodeString RetrieveNameFromPath(CATUnicodeString& iPath);

//========================================================================
// Command
//========================================================================

//------------------------------------------------------------------------
//	Constructeur/Destructeur
//------------------------------------------------------------------------
CAAxPDMCheckInOutCmd::CAAxPDMCheckInOutCmd(CATString* str):CATStateCommand("CheckInOutPX1")
{
   _mode=0;
   if (str && *str=="CheckIn")
      _mode=1;
   else if (str && *str=="CheckOut")
      _mode=0;
}
//------------------------------------------------------------------------
CAAxPDMCheckInOutCmd::~CAAxPDMCheckInOutCmd()
{
}
//------------------------------------------------------------------------
void CAAxPDMCheckInOutCmd::BuildGraph()
{
}

//------------------------------------------------------------------------
CATStatusChangeRC CAAxPDMCheckInOutCmd::Activate(CATCommand*, CATNotification*)
{
   CATApplicationFrame *pApplication = CATApplicationFrame::GetFrame();
   if (!pApplication) return CATStatusChangeRCAborted;
   CATIxPDMItem_var xPDMItem;
   CATUnicodeString oErrorMessage;
   CATUnicodeString oItemName;
   CATIxPDMSession_var xPDMSession(pApplication);
   if ( NULL_var != xPDMSession )
   {
      //Retrieve current item for CheckIn/CheckOut operation
      if (SUCCEEDED(xPDMSession->GetCurrentItem(xPDMItem)) && !!xPDMItem)
      {
         CATUnicodeString oFileName;
         if (SUCCEEDED(xPDMItem->GetDocFileName(oFileName)))
            oItemName =  RetrieveNameFromPath(oFileName);
         //Check current status
         CATBoolean oIsReadOnly=FALSE;
         if (SUCCEEDED(xPDMItem->GetReadOnlyStatus(oIsReadOnly)))
         {
            //------------------------------------------------------------------
            //CHECK HERE THAT SELECTED FILE IS NOT LAREADY CHECK-IN OR CHECK-OUT
            //------------------------------------------------------------------
            if (oIsReadOnly && _mode)
            {
               //This file is already read-only, nothing to change
               oErrorMessage = CATMsgCatalog::BuildMessage("CAAxPDMCheckInOutCmd","AlreadyCheckIn",&oItemName,1,"AlreadyCheckIn");
            }
            if (!oIsReadOnly && !_mode)
            {
               //This file is already read-write, nothing to change
               oErrorMessage = CATMsgCatalog::BuildMessage("CAAxPDMCheckInOutCmd","AlreadyCheckOut",&oItemName,1,"AlreadyCheckOut");
            }
         }

         //CheckIn is forbidden if item is modified
         CATBoolean oNeedToBeSaved;
	      if (_mode && SUCCEEDED(xPDMItem->NeedToBeSaved(oNeedToBeSaved)) && oNeedToBeSaved)
         {
            oErrorMessage = CATMsgCatalog::BuildMessage("CAAxPDMCheckInOutCmd","ModifiedInSession",&oItemName,1,"Modified");
         }


         //Now we can proceed.
         if (!oErrorMessage.GetLengthInChar())
         {
            //------------------------------------------------------------------
            //PERFORM HERE CHECK-IN OR CHECK-OUT IN YOUR PDM
            //------------------------------------------------------------------

            //Update File Rights
#ifdef _WINDOWS_SOURCE
            int mask = _S_IREAD;
            if (!_mode)
               mask = _S_IREAD|_S_IWRITE;
            if ( _chmod( oFileName.ConvertToChar(), mask )== -1 )
               oErrorMessage = CATMsgCatalog::BuildMessage("CAAxPDMCheckInOutCmd","ChgRight",NULL,0,"ChgRight failed");
#endif

            //Update Session Content and Display
            CATxPDMSessionServices::ItemRefresh refresh = CATxPDMSessionServices::ReadWrite;
            HRESULT rc = CATxPDMSessionServices::RefreshItemInformation(xPDMItem,refresh);
            if (FAILED(rc))
               oErrorMessage = CATMsgCatalog::BuildMessage("CAAxPDMCheckInOutCmd","Error",NULL,0,"Error");
         }
      }
      else
         oErrorMessage = CATMsgCatalog::BuildMessage("CAAxPDMCheckInOutCmd","NoItem",NULL,0,"Nothing");
   }
   else
      oErrorMessage = CATMsgCatalog::BuildMessage("CAAxPDMCheckInOutCmd","NoItem",NULL,0,"Nothing");


   //Display report
   if (oErrorMessage.GetLengthInChar())
   {
      CATDlgNotify* notif = new CATDlgNotify(pApplication->GetApplicationDocument(),"Notif",CATDlgNfyError);
      notif->DisplayBlocked(oErrorMessage,"Warning");
      notif->RequestDelayedDestruction();
   }
   else
   {
      CATDlgNotify* notif = new CATDlgNotify(pApplication->GetApplicationDocument(),"Notif",CATDlgNfyInformation|CATDlgWndNoButton);
      CATUnicodeString texte;
      if (_mode)
         texte=CATMsgCatalog::BuildMessage("CAAxPDMCheckInOutCmd","CheckInOK",&oItemName,1,"CheckIN OK");
      else
         texte=CATMsgCatalog::BuildMessage("CAAxPDMCheckInOutCmd","CheckOutOK",&oItemName,1,"CheckOut OK");
      notif->DisplayBlocked(texte,"Info");
      notif->RequestDelayedDestruction();
   }

   RequestDelayedDestruction();
   return CATStatusChangeRCCompleted;
}
//------------------------------------------------------------------------
CATStatusChangeRC CAAxPDMCheckInOutCmd::Cancel(CATCommand* cmd, CATNotification* notif)
{
   return CATStateCommand::Cancel(cmd, notif);
}

