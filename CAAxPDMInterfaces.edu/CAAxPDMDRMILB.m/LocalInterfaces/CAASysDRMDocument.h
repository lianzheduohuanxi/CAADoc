// COPYRIGHT DASSAULT SYSTEMES 2006
#ifndef __CAAESysDRMDOCUMENT
#define __CAAESysDRMDOCUMENT
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CATSysDRMDocument component and implementing 
// CATIUExitDRMDocument and CATIUExitDRMAuthorization
//
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown
#include "CATILockBytes.h"


class CAASysDRMDocument : public CATBaseUnknown
{
  friend class CAASysDRMILB;

  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAASysDRMDocument();
    virtual ~CAASysDRMDocument();


/**
 * Creates the DRM context for a given document.
 * <br><b>Role</b>:Creates the DRM context necessary to work on the document
 * pointed by iDocumentID. This method will be called at the opening of the 
 * document. It must be thread safe.
 * @param iDocumentID
 *      Pointer to the wide char string null terminated defining the document ID
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> DRM_E_INVALIDNAME :</tt> invalid name for the document.
 *   <br><tt> DRM_E_ACCESSDENIED:</tt> access to the document not granted.
 *   <br><tt> DRM_E_INVALIDPARAMETER :</tt> DRM environment not set.
 *   <br><tt> DRM_E_DOCUMENTNOTFOUND :</tt> document can not be found.
 *   <br><tt> DRM_E_INSUFFICIENTMEMORY :</tt> no more memory to make the open.
 *   <br><tt> DRM_E_UNKNOWN :</tt> unexpected error.
*/
  HRESULT DRMCreateContext( const CATUC2Bytes * iDocumentID);



/**
 * Closes the DRM context.
 * <br><b>Role</b>: Closes the DRM context associated to a given document that
 * has been previously created by @href #DRMCreateContext.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt>S_OK :</tt>	on Success.
 *   <br><tt> E_FAIL :</tt>	on Error.
*/
  HRESULT DRMCloseContext();



/**
 * Creates the digital envelope for a protected document.
 * <br><b>Role</b>: Creates the digital envelope for a protected document on an
 * exportable format. This information will be packed with the encrypted document
 * during its saving phase. This data blob can be retrieved at opening by @href 
 * #DRMImportEnvelope .
 * @param  oDRMEnvelope [out]
 *  Buffer where the protected exportable Envelope data will be stored.
 * @param iDRMEnvelopeSize [out]
 *   the size of of the DRM Envelope.
 * @return
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> DRM_E_FAIL :</tt> problem during envelope generation.
 *   <br><tt> DRM_E_ACCESSDENIED:</tt> access to the document not granted.
 *   <br><tt> DRM_E_INVALIDPARAMETER :</tt> arguments incorrects.
 *   <br><tt> DRM_E_INSUFFICIENTMEMORY :</tt>no more memory to make the envelope.
 *   <br><tt> DRM_E_UNKNOWN :</tt> unexpected error.
*/    
  HRESULT DRMExportEnveloppe ( void  *&oDRMEnvelope,
			       size_t &oDRMEnvelopeSize);
  
/**
 * Frees the exportable envelope data.
 * <br><b>Role</b>: Frees  the envelope data associated to a given document that 
 * has been allocated during the @href #DRMExportEnveloppe
 * @param iDRMEnvelope [in]
 *     DRMEnvelope Buffer.
 * @return
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> DRM_E_FAIL :</tt> problem during license generation.
*/    
  HRESULT DRMFreeEnveloppe (void *oDRMEnvelope);



/**
 * Returns to DRM code the envelope data associated with a document.
 * <br><b>Role</b>: Returns to the DRM code the envelope data associated with 
 * the document that has been opened with @href DRMCreateContext. The DRM code 
 * should be able to retrieve here all the necessary information for decrypting 
 * the document, verify its integrety.
 * It is possible to revoque directly here all subsequent operation by returning
 * DRM_E_ACCESSDENIED.
 * @param  iDRMLicence [in]
 *  Buffer containing the DRM Envelope data.
 * @param iDRMLicenseSize [in]
 *   the size of the DRM license.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> DRM_E_FAIL :</tt> problem during license retrieval.
 *   <br><tt> DRM_E_NODRM :</tt> Not DRM protected document.
 *   <br><tt> DRM_E_ACCESSDENIED:</tt> access to the document not granted.
 *   <br><tt> DRM_E_INVALIDPARAMETER :</tt> arguments incorrects.
 *   <br><tt> DRM_E_UNKNOWN :</tt> unexpected error.
*/          
  HRESULT DRMImportEnveloppe( const void *iDRMEnvelope,
			     size_t iDRMEnvelopeSize) ;





/**
 * Returns the GUID of the library implementing the user exits.
 * <br><b>Role</b>: Returns the GUID of the library implementing the user exits.
 * Thus it will be possible to detect documents that have been crypted by other
 * code or level of code. This GUID will be marshalled into the document.
 * @param  oUID [o]
 *  GUID structure.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> DRM_E_FAIL :</tt> problem during license retrieval.
 *   <br><tt> DRM_E_INVALIDPARAMETER :</tt> arguments incorrects.
 *   <br><tt> DRM_E_UNKNOWN :</tt> unexpected error.
*/          
  HRESULT DRMGetLibUID( GUID &oUID);



 /**
 * Creates the DRM authorization container for a given document.
 * <br><b>Role</b>:Creates the DRM authorization context necessary to work on 
 * the document pointed by iDocumentID. This method will be called at the logical 
 * opening of the document. It must be thread safe.
 * @param iDocumentID
 *      Pointer to the wide char string null terminated defining the document ID
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> DRM_E_INVALIDNAME :</tt> invalid name for the document.
 *   <br><tt> DRM_E_INVALIDPARAMETER :</tt> DRM environment not set.
 *   <br><tt> DRM_E_DOCUMENTNOTFOUND :</tt> document can not be found.
 *   <br><tt> DRM_E_INSUFFICIENTMEMORY :</tt> no more memory to make the open.
 *   <br><tt> DRM_E_UNKNOWN :</tt> unexpected error.
*/
  HRESULT DRMInitAuthorization( const CATUC2Bytes * iDocumentID);

/**
 * Releases the DRM authorization container for a given document.
 * <br><b>Role</b>:Releases the DRM authorization context that has been created by
 * @href #DRMInitAuthorization
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> error
 *   <br><tt> DRM_E_REVERTED :</tt> DRMReleaseAuthorization already called
 *   <br><tt> DRM_E_UNKNOWN :</tt> unexpected error.
*/
  HRESULT DRMReleaseAuthorization( const CATUC2Bytes * iDocumentID);


/**
 * Returns if the given right is granted or not.
 * <br><b>Role</b>:Returns if the given right is granted or not for the
 * authenticated user.
 * @param iRight
 *    The right to be checked. TBD
 *	READ, SAVE, PRINT, SAVEAS,  EXPORT, MODIFY_RIGHTS
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt> if granted .
 *   <br><tt> DRM_E_ACCESSDENIED:</tt> right not granted.
 *   <br><tt> DRM_E_UNKNOWNRIGHT :</tt> unknown right
 *   <br><tt> DRM_E_UNKNOWN :</tt> unexpected error.
*/
  HRESULT  IsGranted( DWORD iRightToCheck);


/**
 * Creates the exportable authorization blob for a protected document.
 * <br><b>Role</b>: Creates the digital rights blobs for a protected document on an
 * exportable format. This information will be packed inside the encrypted document
 * during its saving phase. This data blob can be retrieved at opening by @href 
 * #DRMImportAuthorization .
 * @param  oDRMAuthorization [out]
 *  Buffer where the protected exportable authorization data will be stored.
 * @param iDRMAuthorizationSize [out]
 *   the size of of the DRM authorization buffer.
 * @return
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> DRM_E_FAIL :</tt> problem during envelope generation.
 *   <br><tt> DRM_E_ACCESSDENIED:</tt> access to the document not granted.
 *   <br><tt> DRM_E_INVALIDPARAMETER :</tt> arguments incorrect.
 *   <br><tt> DRM_E_INSUFFICIENTMEMORY :</tt> no more memory to make the  envelope.
 *   <br><tt> DRM_E_UNKNOWN :</tt> unexpected error.
*/    
  HRESULT DRMExportAuthorization ( void  *&oDRMAuthorization,
				   size_t &oDRMAuthorizationSize);
  
/**
 * Frees the exportable authorizationdata.
 * <br><b>Role</b>: Frees the authorization data associated to a given document 
 * that has been allocated during the @href #DRMExportAuthorization
 * @param iDRMAuthorizationEnvelope [in]
 *     DRMAuthorization Buffer.
 * @return
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> DRM_E_FAIL :</tt> problem during license generation.
*/    
  HRESULT DRMFreeAuthorization (void *iDRMAuthorization);



/**
 * Returns to DRM code the Authorization data associated with a document.
 * <br><b>Role</b>: Returns to the DRM code the Authorization data associated with 
 * the document that has been opened with @href DRMCreateContext. The DRM code 
 * should be able to retrieve here all the necessary information for decrypting 
 * the buffer ( since the call to @href CATIUExitDRMDocument::DRMImportEnvelope).
 * Thanks to this buffer the DRM code is now able to build the authorizations
 * that the document's publisher has set.
 * @param  iDRMAuthorization [in]
 *  Buffer containing the DRM Authorization data.
 * @param iDRMAuthorizationSize [in]
 *   the size of the DRM Authorization data.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> DRM_E_FAIL :</tt> problem during license retrieval.
 *   <br><tt> DRM_E_NODRM :</tt> Not DRM protected document.
 *   <br><tt> DRM_E_ACCESSDENIED:</tt> access to the document not granted.
 *   <br><tt> DRM_E_INVALIDPARAMETER :</tt> arguments incorrects.
 *   <br><tt> DRM_E_UNKNOWN :</tt> unexpected error.
*/          
  HRESULT DRMImportAuthorization( const void *iDRMAuthorization,
				  size_t iDRMAuthorizationSize);



 private:
  
  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAASysDRMDocument(const CAASysDRMDocument &iObjectToCopy);
  
  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAASysDRMDocument & operator = (const CAASysDRMDocument &iObjectToCopy);

  
  // current symetric key
  unsigned char *_key;
  // size of the key
  size_t _KeySize;

  // DRM
  char *_Right;
  size_t _RightSize;

};
#endif
