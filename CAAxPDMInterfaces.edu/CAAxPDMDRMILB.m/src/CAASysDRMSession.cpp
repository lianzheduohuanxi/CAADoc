/* COPYRIGHT DASSAULT SYSTEMES 2006 */
#include "CAASysDRMSession.h"

#include "CATMsgCatalog.h"
//include Dialog
#include "CATBasicAuthenticationPanel.h"
#include "CATDlgFrame.h"
#include "CATDlgPushButton.h"
#include "CATDlgLabel.h"
//include ApplicationFrame
#include "CATApplicationFrame.h"
//include CAAxPDMInterfaces
#include "CAASysDRMCtrl.h"
#include "CAAxPDMDRMRightEditionFrame.h"

// To declare that the class is a data extension of CATSysDRMDocument
CATImplementClass(CAASysDRMSession, DataExtension,CATBaseUnknown, CATUExitDRMSession);


#include "TIE_CATIUExitDRMSession.h"
TIE_CATIUExitDRMSession(CAASysDRMSession);
#include "TIE_CATIUExitDRMEditorFactory.h"
TIE_CATIUExitDRMEditorFactory(CAASysDRMSession);


//------------------------------------------------------------------------------------------
#ifdef _WINDOWS_SOURCE
#ifdef __JS0ERROR
#define ExportedByJS0ERROR __declspec (dllexport)
#else
#define ExportedByJS0ERROR __declspec (dllimport)
#endif
#else
#define ExportedByJS0ERROR
#endif
enum CATSysBatchMode 
{
  CATSysInteractive =0,       /* application is interactive                          */
  CATSysInteractiveAsBatch=1, /* application designed as interactive is run as batch */
  CATSysBatch=2               /* application is fully designed as  a batch           */
};
extern ExportedByJS0ERROR CATSysBatchMode  CATSysGetBatchMode();
//------------------------------------------------------------------------------------------


/**
* Initialize the DRM environment session
* <br><b>Role</b>:Initializes the DRM environment globally.
* This must be called before the first document is opened.
* @return
*   <b>Legal values</b>:
*   <br><tt> S_OK :</tt>on Success.
*   <br><tt> DRM_E_FAIL:</tt> environment not correctly  initialised
*   <br><tt> DRM_E_UNKNOWN :</tt> unexpected error.
*/
HRESULT CAASysDRMSession::DRMInitSession()
{
   HRESULT hr=S_OK;

   // Only if in interactive mode 
   int BatchMode = CATSysGetBatchMode();
   if (( BatchMode == CATSysInteractive))
   {
      CAASysDRMCtrl *ctrl = CAASysDRMCtrl::GetCtrl();
      if (ctrl)
      {
         CATUnicodeString user;
         if (FAILED(ctrl->GetCurrentUser(user)) || user.GetLengthInChar()==0)
         {
            //We should request a user/pwd
            CATBasicAuthenticationPanel *P=NULL;
            CATApplicationFrame *frm = CATApplicationFrame::GetFrame();
            if (frm)
            {
               P = new CATBasicAuthenticationPanel ();
               P->SetTitle("DRM Login as new user"); 
               P->AddLogo("I_CAAxPDMLogo");
               P->AddLabelAndEditor("User","",10);
               P->AddLabelAndEditor("Password","",10, TRUE);
               CATUnicodeString Name, Password;
               P->WaitAuthentication(Name, Password);
               ctrl->UpdateCtrl( Name.ConvertToChar(), Password.ConvertToChar());
            }
         }
      }
   }
   return hr;
}

#include "iostream.h"
/**
* Allow or Refuse save of documents without DRM Protection.
* <br><b>Role</b>:Allow or Refuse save of documents without DRM Protection.
* @return
*   <b>Legal values</b>:
*   <br><tt> S_OK :</tt>Save allowed.
*   <br><tt> DRM_E_FAIL:</tt> Save forbidden
*   <br><tt> DRM_E_UNKNOWN :</tt> unexpected error.
*/
HRESULT CAASysDRMSession::DRMGetPolicy(DWORD iPolicy)
{
   CAASysDRMCtrl *ctrl = CAASysDRMCtrl::GetCtrl();
   if (ctrl)
   {
      if (( iPolicy & 0x00000001) == 0x00000001)
      {
         cout << "DRMGetPolicy " << endl;
         int oProfile=0;
         if (SUCCEEDED(ctrl->DRMGetProfile(oProfile)) && oProfile==1)
         {
            cout << "PROTECTED " << endl;
            //On a supplier site, this code should be activated to forbid save of new files
            //without DRM rights
            return DRM_E_FAIL;
         }
      }
   }
   return S_OK;
}

/**
* Closes the DR: Session ization container for a given document.
* <br><b>Role</b>:Closes the DRM environment session created in 
* @href #DRMInitSession
* @return
*   <b>Legal values</b>:
*   <br><tt> S_OK :</tt>on Success.
*   <br><tt> DRM_E_FAIL :</tt> error
*/
HRESULT CAASysDRMSession::DRMCloseSession( )
{
   HRESULT hr=S_OK;
   return hr;
}

/**
 * Returns the display name of the DRM provider.
 * <br><b>Role</b>:Returns the display name of the DRM provider currently used. This
 * method is only intended for user interface purpose. The relevant information 
 * concerning the implementation identification is the 
 * @href CATIUExitDRMDocument::DRMGetLibUID .
 * @param oName [out]
 *	The name of the current implementation
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> DRM_E_FAIL :</tt> error
*/
HRESULT CAASysDRMSession::DRMGetProviderName(CATUnicodeString &oName)
{
   oName = "CAA PX1 DRM Sample";
   return S_OK;
}

/**
*	Create a frame with about information on DRM User exit.
* @param iParentFrame [in]
*    the parent frame to use to build your dialog objects
* @return
*   <b>Legal values</b>:
*   <br><tt> S_OK :</tt>on Success.
*   <br><tt> E_FAIL:</tt>on Fail
*/
HRESULT CAASysDRMSession::BuildAboutFrame(CATDlgFrame *iParentFrame)
{
   if (iParentFrame)
   {
      iParentFrame->SetDefaultOrientation(Vertical);
      CATDlgPushButton * but = new CATDlgPushButton(iParentFrame,"but");
      but->SetIconName("I_CAAxPDMLogo");
      CATDlgLabel* label01 = new CATDlgLabel(iParentFrame,"label01");
      CATDlgLabel* label02 = new CATDlgLabel(iParentFrame,"label02");
      CATDlgLabel* label03 = new CATDlgLabel(iParentFrame,"label03");
      CATDlgLabel* label04 = new CATDlgLabel(iParentFrame,"label04");
      CATDlgLabel* label05 = new CATDlgLabel(iParentFrame,"label05");
      label01->SetTitle(CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","About1"));
      label02->SetTitle(CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","About2"));
      label03->SetTitle(CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","About3"));
      label04->SetTitle(CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","About4"));
      label05->SetTitle(CATMsgCatalog::BuildMessage("CAAxPDMDRMTemplatePanel","About5"));
   }
   return S_OK;
}
/**
*	Create a frame to change rights on one document.
* @param iParentFrame [in]
*    the parent frame to use to build your dialog objects
* @param  iDRMAuthorization [in]
*  Buffer containing the DRM Authorization data to edit.
* @param iDRMAuthorizationSize [in]
*   the size of the DRM Authorization data to edit.
* @param oCreatedFrame [out]
*    the created frame, it should implement @href CATIUExitDRMEditorFrame to be able to validate modifications.
* @return
*   <b>Legal values</b>:
*   <br><tt> S_OK :</tt>on Success.
*   <br><tt> E_FAIL:</tt>on Fail
*/
HRESULT CAASysDRMSession::BuildEditRightFrame(CATDlgFrame *iParentFrame,
                                              const void *iDRMAuthorization,
                                              size_t iDRMAuthorizationSize,
                                              CATDlgFrame **oCreatedFrame)
{
   CAAxPDMDRMRightEditionFrame* frame = new CAAxPDMDRMRightEditionFrame(iParentFrame);
   if (frame)
   {
      frame->Init(iDRMAuthorization,iDRMAuthorizationSize);
      *oCreatedFrame = frame;
      return S_OK;
   }
   return E_FAIL;
}

/**
*	Allow the implementation to show more specific details about the document. 
* @param iParentFrame [in]
*    the parent frame to be used to build your dialog objects
* @param iCurrentDoc  [in]
*    a CATBaseUnkwown object that will allow to retrieve the object extending CATIUExitDRMDocument and CATIUExitDRMAuthorization
* @return
*   <b>Legal values</b>:
*   <br><tt> S_OK :</tt>on Success.
*   <br><tt> E_FAIL:</tt>on Fail
*/
HRESULT CAASysDRMSession::FillAdditionalInformationFrame(CATDlgFrame *iParentFrame, CATBaseUnknown *iCurrentDoc )
{
   return E_FAIL;
}

/**
*	Ask what the current implementation is able to show. If the answer is no then the button is hidden. 
* @param iFrameDescriptor [in]
*    a frame descriptor, possible values are FRAME_DESCRIPTOR_ABOUT,FRAME_DESCRIPTOR_EDITRIGHTS or FRAME_DESCRIPTOR_ADDITIONAL
* @param iIsAble [in]
*    must be set to TRUE if your implementation is able to show the frame asked with iFrameDescriptor, FALSE if not.
* @return
*   <b>Legal values</b>:
*   <br><tt> S_OK :</tt>on Success.
*   <br><tt> E_FAIL:</tt>on Fail
*/
HRESULT CAASysDRMSession::IsAbletoShow(int iFrameDescriptor, CATBoolean& iIsAble)
{
   if( iFrameDescriptor == FRAME_DESCRIPTOR_ABOUT ) iIsAble = TRUE;
   else if( iFrameDescriptor == FRAME_DESCRIPTOR_ADDITIONAL ) iIsAble = FALSE;
   else if( iFrameDescriptor == FRAME_DESCRIPTOR_EDITRIGHTS ) iIsAble = TRUE;
   else iIsAble = FALSE;

   return S_OK;
}

