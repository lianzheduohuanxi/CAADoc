/* COPYRIGHT DASSAULT SYSTEMES 2006 */
#ifndef CAASysDRMSession_H
#define CAASysDRMSession_H

#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"
class CATDlgFrame;
/**
 * Interface to enable user specific DRM (digital rights management) mechanism in
 * a session 
 * <b>Role</b>: This interface is a user exit, that allows an user to create its 
 * security environment session.
 * Implementing this user exit is not mandatory. It is provided as a
 * facility to be called at the beggining and at the end of the security session to
 * do initialisation and cleanup treatments.
 *
 **/
class  CAASysDRMSession : public CATBaseUnknown
{
  CATDeclareClass;
public:
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
  virtual HRESULT DRMInitSession();

/**
 * Allow or Refuse save of documents without DRM Protection.
 * <br><b>Role</b>:Allow or Refuse save of documents without DRM Protection.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>Save allowed.
 *   <br><tt> DRM_E_FAIL:</tt> Save forbidden
 *   <br><tt> DRM_E_UNKNOWN :</tt> unexpected error.
*/
  virtual HRESULT DRMGetPolicy(DWORD iPolicy);

/**
 * Closes the DR: Session ization container for a given document.
 * <br><b>Role</b>:Closes the DRM environment session created in 
 * @href #DRMInitSession
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> DRM_E_FAIL :</tt> error
*/
  virtual HRESULT DRMCloseSession( );

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
  virtual HRESULT DRMGetProviderName(CATUnicodeString &oName);

  /**
  *	Create a frame with about information on DRM User exit.
  * @param iParentFrame [in]
  *    the parent frame to use to build your dialog objects
  * @return
  *   <b>Legal values</b>:
  *   <br><tt> S_OK :</tt>on Success.
  *   <br><tt> E_FAIL:</tt>on Fail
  */
  virtual HRESULT BuildAboutFrame(CATDlgFrame *iParentFrame);

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
  virtual HRESULT BuildEditRightFrame(CATDlgFrame *iParentFrame,
     const void *iDRMAuthorization,
     size_t iDRMAuthorizationSize,
     CATDlgFrame **oCreatedFrame);


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
   HRESULT FillAdditionalInformationFrame(CATDlgFrame *iParentFrame,
                                          CATBaseUnknown *iCurrentDoc );

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
   HRESULT IsAbletoShow(int iFrameDescriptor,
                        CATBoolean& iIsAble);
};

#endif



