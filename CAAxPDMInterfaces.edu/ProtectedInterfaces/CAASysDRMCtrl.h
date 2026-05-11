/* COPYRIGHT DASSAULT SYSTEMES 2006 */

#ifndef __CAASysDRMCtrlH
#define __CAASysDRMCtrlH

#ifdef _WINDOWS_SOURCE
#ifdef __CAAxPDMDRMILB
#define ExportedByCAASysDRMCtrl __declspec(dllexport)
#else
#define ExportedByCAASysDRMCtrl __declspec(dllimport)
#endif
#else
#define ExportedByCAASysDRMCtrl
#endif
#include "CATWTypes.h"

class ExportedByCAASysDRMCtrl CAASysSymetricProvider
{
 public:
  enum Mode { ECB , CBC };
  enum Direction { crypt , decrypt };
  CAASysSymetricProvider();
  virtual ~CAASysSymetricProvider ();

/**
 * Inits the symetric provider.
 * <br><b>Role</b>: Inits the symetric provider.
 * @param  mode [i]
 *  the mode ECB or CBC.
 * @param  dir [i]
 *  Usage mode- encryption or decryption.
 * @param key [i]
 *  the symetric key.
 * @param KeyLen [i]
 *  the symetric key length.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
*/   
  HRESULT InitProvider ( Mode mode, Direction dir,
			 unsigned char * key, size_t KeyLen);

/**
 * Encrypts data.
 * <br><b>Role</b>: Encrypts a data buffer which size is a multiple of the cipher
 * block size.
 * @param  iPT [i]
 *  the plain text.
 * @param  iPTLen [i]
 *   plain text length in bytes which must be a multiple of the cipher
 *   block size.
 * @param oCT [io]
 *  the cipher text previously allocated.
 * @param oCTLen [o]
 *  the cipher text length - should be equal to iPTLen.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
*/   
  HRESULT Encrypt ( void *iPT, size_t iPTLen, void *ioCT,size_t &oCTLen);
/**
 * Decrypts data.
 * <br><b>Role</b>: Decrypts a data buffer which size is a multiple of the cipher
 * block size.
 * @param  iCT [i]
 *  the cipher text.
 * @param  iCTLen [i]
 *   cipher text length in bytes which must be a multiple of the cipher
 *   block size.
 * @param oPT [io]
 *  the plain text previously allocated.
 * @param oPTLen [o]
 *  the plain text length - should be equal to iCTLen.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
*/   
  HRESULT Decrypt ( void *iCT, size_t iCTLen, void *ioPT,size_t &oPTLen);
 private:
  void * _Provider;
};


  


class CATUnicodeString;

class ExportedByCAASysDRMCtrl CAASysDRMCtrl
{
 public :
  CAASysDRMCtrl();
  virtual ~CAASysDRMCtrl();

/**
 * Creates or return the controller for DRM.
 * <br><b>Role</b>:Creates or gets the unique DRM controller.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> not NULL :</tt>on Success the pointer on the unique controller.
 *   <br><tt> NULL :</tt> on error.
*/   
 static CAASysDRMCtrl *GetCtrl ();

/**
 * Sets the rights for the session.
 * <br><b>Role</b>: Defines the rights associated to a list of users, that will
 * used for all documents in the current session.
 * @param  iUsers [i]
 *  an array of users
 * @param  iRights [i]
 *  array of associated rights.
 * @param  iNb [i]
 *  the numbers of elements of the previously defined arrays
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
*/   
  HRESULT SetAuthorization(CATUnicodeString *iUsers, DWORD *iRights, int iNb);

/**
 * Gets the rights for the session.
 * <br><b>Role</b>: Reads the rights associated to a list of users, that will
 * used for all documents in the current session.
 * @param  iUsers [i]
 *  an array of users
 * @param  iRights [i]
 *  array of associated rights.
 * @param  iNb [i]
 *  the numbers of elements of the previously defined arrays
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
*/   
  HRESULT GetAuthorization(CATUnicodeString *&oUsers, DWORD *&oRights, int& oNb);
  
  HRESULT GetDecryptAuthorization( char *iRight, size_t iSize,
     CATUnicodeString *&oUsers, DWORD *&oRights, int& oNb);

  HRESULT GetEncryptAuthorization(CATUnicodeString* iUsers, DWORD* iRights, int iNb,
     char* &oRight, size_t& oSize);

/**
 * Sets the DRM activation.
 * <br><b>Role</b>: Turns ON or Off the DRM. 
 * @param  iActivation [i]
 *  the DRM activation.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
*/   
  HRESULT SetDRMActivation( int iActivation);

/**
 * Gets the DRM activation.
 * <br><b>Role</b>: Get the DRM activation status. 
 * @param  oActivation [o]
 *  the DRM activation.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
*/   
  HRESULT GetDRMActivation( int &oActivation);


/**
 * Sets the current logged DRM user.
 * <br><b>Role</b>: Sets the current logged DRM user.
 * @param  iUser [i]
 *   user name
 * @param  iPwd [i]
 *  associated password.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
*/   
  HRESULT UpdateCtrl(const char *iUser, const char *iPwd) ;

/**
 * Retrieves the current logged DRM users name.
 * <br><b>Role</b>: Retrieves the current logged DRM users name.
 * @param  oUser [o]
 *   user name
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
*/   
  HRESULT GetCurrentUser (CATUnicodeString &oUser) ;


/**
 * Retrieves if one has explicitly logged into DRM.
 * <br><b>Role</b>: Retrieves if one has explicitly logged into DRM.
 * @param  oLogged [o]
 *   login status 
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
*/
  HRESULT IsLogged ( int &oLogged);

/**
 * Read DRM Profile
 * <br><b>Role</b>:Read DRM profile to define which operation are allowed
 * @param  oProfile [out]
 *   <b>Legal values</b>:
 *   <br><tt> 0 :</tt>Author.
 *   <br><tt> 1 :</tt>Design supplier.
 *   <br><tt> 2 :</tt>Downstream supplier.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
 */
  HRESULT DRMGetProfile(int& oProfile);

/**
 * Initialize DRM Profile
 * <br><b>Role</b>:Choose DRM profile to define which operation are allowed
 * @param  iProfile [in]
 *   <b>Legal values</b>:
 *   <br><tt> 0 :</tt>Author.
 *   <br><tt> 1 :</tt>Design supplier.
 *   <br><tt> 2 :</tt>Downstream supplier.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
 */
  HRESULT DRMSetProfile(int iProfile);

/**
 * Sets the symetric key size.
 * <br><b>Role</b>: Sets the symetric key size in byte.
 * @param  iSize [i]
 *   the key size 
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
*/
  HRESULT SetSymetricKeySize( int iSize);

/**
 * Gets the symetric key size.
 * <br><b>Role</b>: Gets the symetric key size in byte.
 * @param  oSize [o]
 *   the key size 
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
*/
  HRESULT GetSymetricKeySize( int& oSize);
 

/** The following methods control the encryption :
 *  Creation of a one shot symetric key for the encryption of the data.
 *  Encryption-Decryption with a symetric algorithm of data.
 *  Export-Import of these symetric keys in a data blobs.
 *  Export-Import of the DRM authorization in a data blobs.
*/

/**
 * Generates a one-shot symetric key.
 * <br><b>Role</b>: Generates a one-shot symetric key to encrypt a given document.
 * @param  oKey [o]
 *  the symetric key.
 * @param  oKeySize [o]
 *  the symetric key Size.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
*/   
  HRESULT DeriveSymetricKey (unsigned char *&oKey, size_t &oKeySize);

/**
 * Generates an encrypted marshalled blob of the symetric key.
 * <br><b>Role</b>: Generates an encrypted marshalled blob of the symetric key 
 * used for a given document that can be send to @href DRMExportEnveloppe .
 * @param  iKey [i]
 *  the symetric key.
 * @param  iKeySize [i]
 *  the symetric key Size.
 * @param  oCryptedKey [o]
 *  the resulting encrypted marshalled buffer.
 * @param  oCryptedKeySize [o]
 *  the size of the encrypted marshalled buffer.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
*/   
  HRESULT EncryptSymetricKey (unsigned char *iKey, int iKeySize,
			      void  *&oCryptedkey, size_t &oCryptedKeySize);

/**
 * Retrieves a symetric key from an encrypted marshalled blob.
 * <br><b>Role</b>:Retrieves a symetric key from an encrypted marshalled blob that
 * has been previously created with @href EncryptSymetricKey.
 * @param  iCrypedKey [i]
 *  the symetric key.
 * @param  iKeySize [i]
 *  the symetric key Size.
 * @param  oKey [o]
 *  the resulting decrypted symetric key.
 * @param  oKeySize [o]
 *  the size of the decrypted key.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> DRM_E_NOKEY :</tt> No key in the buffer.
 *   <br><tt>  DRM_E_INSUFFICIENTMEMORY:</tt> no more memory.
*/   
  HRESULT DecryptSymetricKey (const void *iCyptedKey, size_t iKeySize,
			      unsigned char *&oKey, size_t &oKeySize);



/**
 * Generates an encrypted marshalled blob of the rights.
 * <br><b>Role</b>: Generates an encrypted marshalled blob of the rights 
 * associated to a given document.
 * @param  oRight [o]
 *  the right blob.
 * @param  oSize [i]
 *  Size of the buffer.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
*/   
  HRESULT EncryptAuthorization( char *&oRight, size_t &oSize);

/**
 * Retrieves the rights associated to a given document.
 * <br><b>Role</b>: Retrieves the rights associated to a given document from an 
 * encrypted marshalled blob.
 * @param  iRight [o]
 *  the right blob.
 * @param  iSize [i]
 *  Size of the buffer.
 *  @param  oRight [o]
 *  the set of authorization associated to the document.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> DRM_E_CRYPTCORRUPTION:</tt> the blob can not be decrypted.
 *   <br><tt> E_FAIL :</tt> on error.
*/   
  HRESULT DecryptAuthorization( char *iRight, size_t iSize, DWORD &oRight);


/**
 * Retrieves the provider for the symetric encryption algorithm.
 * <br><b>Role</b>: Retrieves the provider for the symetric encryption algorithm.
 * @param oProvider
 *   pointer to the provider.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on error.
*/   
  HRESULT GetSymetricProvider ( CAASysSymetricProvider *&oProvider);


 private:
/**
 * pointer on the DRM controller.
*/
 static CAASysDRMCtrl *_DRMCtrl;

/**
 * Key size in byte
*/
  static int _KeySize;

/**
 * Currently logged DRM user.
*/
  char * _User;
/**
 * Current password of the logged DRM user.
*/
  char * _Pwd;

/**
 * Referenced users in the DRM context.
*/
  CATUnicodeString *_DRMUsers;
/**
 * Associated Rights of the users in the DRM context.
*/
  DWORD *_Rights;
/**
 * Number of referenced users in the DRM context.
*/
  int _NbUsers;
/**
 * Activation status of the DRM.
*/
  int _Activated;

/**
  * Login status.
*/
  int _Logged;
/**
  * Interactive status.
*/
  int _BatchMode;
/**
  * DRM Profile
*/
  int _DRMProfile;


};
#endif

  
