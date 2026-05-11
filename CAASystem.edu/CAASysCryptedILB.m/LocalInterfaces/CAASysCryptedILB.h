// COPYRIGHT DASSAULT SYSTEMES 2004
#ifndef __CAAESysCryptedILB__
#define __CAAESysCryptedILB__
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CATUExitCryptedILockBytes component and implementing 
//  the CATIUExitCryptedILockBytes interface.
//
//  The component CATUExitCryptedILockBytes is defined in the System FW. 
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown
#include "CATIUExitCryptedILockBytes.h"


class CAASysCryptedILB : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAASysCryptedILB();
    virtual ~CAASysCryptedILB();

/**
 * Reads and decrypts a block of datas.
 * <b>Role</b>: Reads a block of datas in a crypted ILockBytes and returns the 
 * decrypted datas. This method is used for the manipulation of V5 documents.
 * The given offset and length are refering to the decrypted version of the 
 * file.
 * @param iOffset [in]
 *   Offset of the block in the decrypted file 
 * @param  iBuff [in]
 *  Buffer where the decrypted datas where will be writen.
 * @param iLengthToRead [i]
 *   the size of of the requested decrypted datas.
 * @param oLengthRead [out]
 *   the length of read datas.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATSysCLB_E_SEEKERROR :</tt> problem in setting the read offset.
 *   <br><tt> CATSysCLB_E_READFAULT :</tt> problem while reading.
 *   <br><tt> CATSysCLB_E_INVALIDPARAMETER :</tt> arguments incorrects.
 *   <br><tt> CATSysCLB_E_DOCFILECORRUPT  :</tt> document can not be decrypted.
 *   <br><tt> CATSysCLB_E_UNKNOWN :</tt> unexpected error.
 */    
    HRESULT ReadAt( ULARGE_INTEGER iOffset,
		    void  *iBuff,
		    ULONG iLengthToRead,
		    ULONG  *oLengthRead) ; 


/**
 * Writes and crypts  a block of datas.
 * <b>Role</b>: Writes a block of datas. This method is used for the manipulation
 * of V5 documents.
 * The given offset and length are refering to the decrypted version of the file. 
 * @param iOffset [in]
 *   Offset of the block in the decrypted file 
 * @param  iDataSource [in]
 *  Buffer of uncrypted datas to write.
 * @param iLengthToWrite [i]
 *   the size of of the datas to write.
 * @param oLengthWriten [out]
 *   the length of read writen. Should be equal to iLengthToWrite if no 
 *   problem has occurred.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATSysCLB_E_SEEKERROR :</tt> problem in setting the read offset.
 *   <br><tt> CATSysCLB_E_WRITEFAULT :</tt> problem while writing.
 *   <br><tt> CATSysCLB_E_MEDIUMFULL :</tt> disk full error.
 *   <br><tt> CATSysCLB_E_INVALIDPARAMETER :</tt> arguments incorrects.
 *   <br><tt> CATSysCLB_E_DISKISWRITEPROTECTED :</tt> disk write protected.
 *   <br><tt> CATSysCLB_E_UNKNOWN :</tt> unexpected error.
*/          
  HRESULT WriteAt( ULARGE_INTEGER iOffset,
		   const void *iDataSource,
		   ULONG iLengthToWrite,
		   ULONG  *LengthWritten) ;
        
/**
 * Flush all the buffers.
 * <b>Role</b>: Insures that the disk view of the file is coherent, and that all
 * the  buffers have been writen on disk.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATSysCLB_E_WRITEFAULT :</tt> problem while writing.
 *   <br><tt> CATSysCLB_E_MEDIUMFULL :</tt> disk full error.
 *   <br><tt> CATSysCLB_E_DISKISWRITEPROTECTED :</tt> disk write protected.
 *   <br><tt> CATSysCLB_E_UNKNOWN :</tt> unexpected error.
*/          
  HRESULT  Flush( void) ;



/**
 * Sets the size of the CATILockBytes.
 * <b>Role</b>: Sets the size of the CATILockBytes.
 * @ param iLength.
 *      The new size of the CATILockBytes.
 * @return
 *   S_OK on Success.
 *   E_FAIL on error. ( We can discuss further for more precise errors codes)
*/                  
  HRESULT SetSize( ULARGE_INTEGER iLength);
        
 /**
 * Locks a region of the CATILockBytes.
 * <b>Role</b>: Locks a region of the CATILockBytes. Not used.
 * The implementation can return CATSysCLB_E_UNIMPLEMENTEDFUNCTION
 * @param iOffset [in]
 *   Offset of the block in the decrypted file  
 * @param iLength [i] 
 *   the size of the region. 
 * @param dwLockType [in] 
 *        type of lock. 
 * @return 
 *   <b>Legal values</b>: 
 *   <br><tt> S_OK :</tt>on Success. 
 *   <br><tt> CATSysCLB_E_UNIMPLEMENTEDFUNCTION :</tt> unimplemented       
*/               
  HRESULT LockRegion( ULARGE_INTEGER iOffset, 
		      ULARGE_INTEGER iLegnth,
		      DWORD dwLockType); 
 /**
 * Unocks a region of the CATILockBytes.
 * <b>Role</b>: Unlocks a region of the CATILockBytes. Not used.
 * The implementation can return CATSysCLB_E_UNIMPLEMENTEDFUNCTION
 * @param iOffset [in]
 *   Offset of the block in the decrypted file 
 * @param iLength [i]
 *   the size of the region.
 * @param dwLockType [in]
 *        type of lock.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATSysCLB_E_UNIMPLEMENTEDFUNCTION :</tt> unimplemented
*/                
 HRESULT  UnlockRegion( ULARGE_INTEGER iOffset,
			ULARGE_INTEGER iLength,
			DWORD dwLockType) ;
/**
 * Returns informations for the given file.
 * <b>Role</b>:  Returns informations for the given file. For the size, 
 * the uncrypted size must be returned.
 * @return
 *   S_OK on Success.
 *   E_FAIL on error. ( We can discuss further for more precise errors codes)
*/          
  HRESULT  Stat( STATSTG FAR *oStat, DWORD iStatFlag);


/**
 * Defines the way to open the CATILockbytes
 * <b>Role</b>:Defines the way to open the CATILockBytes.
 * @param iMode
 *      The global opening mode used by the V5 document. This mode is not to
 *      be analysed, but should be stored in the STATSTG structure. 
 *      For non V5-document it will be 0 and never used.
 * @param iOpenMode 
 *      Opening mode 
 * @param iSharingMode
 *      Sharing mode
  * @param  iOpenFlag 
 *       flag for specifying the open processing 
 * @param  iSpecialFlag
 *       flag for specifying special behavior.
 *	<b>Legal values</b>:
 *	<br><tt>1 :</tt> the file is deleted on close.
 *	 <br><tt>0 :</tt> Nothing
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATSysCLB_E_INVALIDNAME :</tt> invalid name for the document.
 *   <br><tt> CATSysCLB_E_ACCESSDENIED:</tt> access to the document not granted.
 *   <br><tt> CATSysCLB_E_LOCKVIOLATION :</tt> document locked by another process.
 *   <br><tt> CATSysCLB_E_NOMOREFILES :</tt> too many opened files
 *   <br><tt> CATSysCLB_E_INVALIDPARAMETER :</tt> arguments incorrect.
 *   <br><tt> CATSysCLB_E_DOCFILECORRUPT :</tt> document can not be read.
 *   <br><tt> CATSysCLB_E_FILENOTFOUND :</tt> document can not be found.
 *   <br><tt> CATSysCLB_E_PATHNOTFOUND :</tt> The path of the document could 
 *                                            not be found.
 *   <br><tt> CATSysCLB_E_UNKNOWN :</tt> unexpected error.
*/
  HRESULT  Open( const CATUnicodeString * iPath, 
		 DWORD iMode,
		 CATSysOpenMode iOpenMode, 
		 CATSysSharing iSharingMode, 
		 CATSysCreateMode iOpenFlag, 
		 CATSysCloseMode iCloseFlag);

/**
 * Defines the way to open the CATILockbytes
 * <b>Role</b>:Defines the way to open the CATILockBytes.
 * @param iMode
 *      The global opening mode used by the V5 document. This mode is not to
 *      be analysed, but should be stored in the STATSTG structure. 
 *      For non V5-document it will be 0 and never used.
 * @param iOpenMode 
 *      Opening mode 
 * @param iSharingMode
 *      Sharing mode
  * @param  iOpenFlag 
 *       flag for specifying the open processing 
 * @param  iSpecialFlag
 *       flag for specifying special behavior.
 *	<b>Legal values</b>:
 *	<br><tt>1 :</tt> the file is deleted on close.
 *	 <br><tt>0 :</tt> Nothing
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATSysCLB_E_INVALIDNAME :</tt> invalid name for the document.
 *   <br><tt> CATSysCLB_E_ACCESSDENIED:</tt> access to the document not granted.
 *   <br><tt> CATSysCLB_E_LOCKVIOLATION :</tt> document locked by another process.
 *   <br><tt> CATSysCLB_E_NOMOREFILES :</tt> too many opened files
 *   <br><tt> CATSysCLB_E_INVALIDPARAMETER :</tt> arguments incorrect.
 *   <br><tt> CATSysCLB_E_DOCFILECORRUPT :</tt> document can not be read.
 *   <br><tt> CATSysCLB_E_FILENOTFOUND :</tt> document can not be found.
 *   <br><tt> CATSysCLB_E_PATHNOTFOUND :</tt> The path of the document could 
 *                                            not be found.
 *   <br><tt> CATSysCLB_E_UNKNOWN :</tt> unexpected error.
*/
  HRESULT  OpenW( const CATUC2Bytes * iPath,  
		 DWORD iMode, 
		 CATSysOpenMode iOpenMode,  
		 CATSysSharing iSharingMode,  
		 CATSysCreateMode iOpenFlag,  
		 CATSysCloseMode iCloseFlag); 
/**
 * Closes the CATILockBytes.
 * <b>Role</b>: Closes the CATILockBytes.
 * @return
 *	<b>Legal values</b>:
 *	<br><tt>S_OK :</tt>   on Success
*/
  HRESULT Close();




/**
 * Reads and decrypts a block of datas.
 * <b>Role</b>: Reads a block of datas in a crypted ILockBytes from the current 
 * offset in the file and returns the decrypted datas. This method will be only 
 * used for non V5 documents.
 * @param  iBuff [in]
 *  Buffer where the decrypted datas where will be writen.
 * @param iLengthToRead [i]
 *   the size of of the requested decrypted datas.
 * @param oLengthRead [out]
 *   the length of read datas.
 * @return
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATSysCLB_E_READFAULT :</tt> problem while reading.
 *   <br><tt> CATSysCLB_E_INVALIDPARAMETER :</tt> arguments incorrects.
 *   <br><tt> CATSysCLB_E_DOCFILECORRUPT  :</tt> document can not be decrypted.
 *   <br><tt> CATSysCLB_E_UNKNOWN :</tt> unexpected error.
*/    
  HRESULT Read(   void  *iBuff,
		  ULONG iLengthToRead,
		  ULONG *oLengthRead);


/**
 * Writes and crypts  a block of datas.
 * <b>Role</b>: Writes a block of datas at the current offset. This method will 
 * be only used for non V5 documents.
 * @param  iDataSource [in]
 *  Buffer of uncrypted datas to write.
 * @param iLengthToWrite [i]
 *   the size of of the datas to write.
 * @param oLengthWriten [out]
 *   the length of read writen. Should be equal to iLengthToWrite if no 
 *   problem has occurred.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATSysCLB_E_WRITEFAULT :</tt> problem while writing.
 *   <br><tt> CATSysCLB_E_MEDIUMFULL :</tt> disk full error.
 *   <br><tt> CATSysCLB_E_INVALIDPARAMETER :</tt> arguments incorrects.
 *   <br><tt> CATSysCLB_E_DISKISWRITEPROTECTED :</tt> disk write protected.
 *   <br><tt> CATSysCLB_E_UNKNOWN :</tt> unexpected error.
*/          
  HRESULT Write( const void *iDataSource,
		 ULONG iLengthToWrite,
		 ULONG  *LengthWritten);



/**
 * Reads in the encrypted file and returns a line.
 * <b>Role</b>: Reads in the encrypted file and return decrypted data up to
 * the number of bytes specified by iNb parameter minus 1, or until a new-line
 * character and transfers that character to the ioLine parameter, or until it
 * encounters an end-of-file condition. The method then terminates the data 
 * string with a null character.
 * This method will never be called for V5 documents. 
 * @param  ioLine [inout]
 *  line Buffer of at least iNb size.
 * @param iNb [i]
 *   max number of character to read.
 * @param oEof[o]
 *   to indicate if the end of the file as been reached.
 *   <br><tt> 1 :</tt> End of file has been reached. In this case the return
 *   is S_OK.
 *   <br><tt> 0 :</tt> End of file has not been reached
 * @return
 *   <br><tt> S_OK :</tt>on Success .
 *   <br><tt> STG_E_READFAULT :</tt> problem while reading.
 *   <br><tt> STG_E_INVALIDPARAMETER :</tt> arguments incorrects.
 *   <br><tt> STG_E_DOCFILECORRUPT  :</tt> document can not be decrypted.
 *   <br><tt> STG_E_UNKNOWN :</tt> unexpected error.
 */
  HRESULT ReadLine ( char * ioLine, ULONG iNb, int &oEof);



/**
 * Crypts and write a line for crypted text files.
 * <b>Role</b>: Crypts Writes the null-terminated string pointed to by the 
 * iBuff parameter. The method does not crypt and write the terminating null 
 * character.
 * This method  will be only used for non V5 documents.
 * @param  iBuff [in]
 *  uncrypted Line  to write.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> STG_E_WRITEFAULT :</tt> problem while writing.
 *   <br><tt> STG_E_MEDIUMFULL :</tt> disk full error.
 *   <br><tt> STG_E_INVALIDPARAMETER :</tt> arguments incorrects.
 *   <br><tt> STG_E_DISKISWRITEPROTECTED :</tt> disk write protected.
 *   <br><tt> STG_E_UNKNOWN :</tt> unexpected error.
*/          
  HRESULT WriteLine ( const char * iBuff);

/**
 * Reads in the encrypted file and returns a line of unicode characters
 * <b>Role</b>: Reads in the encrypted file and return decrypted data up to
 * the number of bytes specified by iNb parameter minus 1, or until a new-line
 * character and transfers that character to the ioLine parameter, or until it
 * encounters an end-of-file condition. The method then terminates the data 
 * string with a null character.
 * This method will never be called for V5 documents. 
 * @param  ioLine [inout]
 *  line Buffer.
 * @param iNb [i]
 *   max number of character to read.
 * @param oEof[o]
 *   to indicate if the end of the file as been reached.
 *   <br><tt> 1 :</tt> End of file has been reached. In this case the return
 *   is S_OK.
 *   <br><tt> 0 :</tt> End of file has not been reached
 * @return
 *   <br><tt> S_OK :</tt>on Success .
 *   <br><tt> STG_E_READFAULT :</tt> problem while reading.
 *   <br><tt> STG_E_INVALIDPARAMETER :</tt> arguments incorrects.
 *   <br><tt> STG_E_DOCFILECORRUPT  :</tt> document can not be decrypted.
 *   <br><tt> STG_E_UNKNOWN :</tt> unexpected error.  
 */
  HRESULT ReadLineW ( CATUnicodeString *ioLine, ULONG iNb, int &oEof);

/**
 * Reads in the encrypted file and returns a line of unicode characters
 * <b>Role</b>: Reads in the encrypted file and return decrypted data up to
 * the number of bytes specified by iNb parameter minus 1, or until a new-line
 * character and transfers that character to the ioLine parameter, or until it
 * encounters an end-of-file condition. The method then terminates the data 
 * string with a null character.
 * This method will never be called for V5 documents. 
 * @param  ioLine [inout]
 *  line Buffer.
 * @param iNb [i]
 *   max number of character to read.
 * @param oEof[o]
 *   to indicate if the end of the file as been reached.
 *   <br><tt> 1 :</tt> End of file has been reached. In this case the return
 *   is S_OK.
 *   <br><tt> 0 :</tt> End of file has not been reached
 * @return
 *   <br><tt> S_OK :</tt>on Success .
 *   <br><tt> STG_E_READFAULT :</tt> problem while reading.
 *   <br><tt> STG_E_INVALIDPARAMETER :</tt> arguments incorrects.
 *   <br><tt> STG_E_DOCFILECORRUPT  :</tt> document can not be decrypted.
 *   <br><tt> STG_E_UNKNOWN :</tt> unexpected error.  
 */
  HRESULT ReadLineWchar ( CATUC2Bytes *ioLine, ULONG iNb, int &oEof);



/**
 * Crypts and write a line for crypted text files.
 * <b>Role</b>: Crypts Writes the null-terminated unicode  string pointed to
 * by the iBuff parameter. The method does not crypt and write the terminating
 * null character.
 * This method  will be only used for non V5 documents.
 * @param  iBuff [in]
 *  uncrypted Line  to write.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> STG_E_WRITEFAULT :</tt> problem while writing.
 *   <br><tt> STG_E_MEDIUMFULL :</tt> disk full error.
 *   <br><tt> STG_E_INVALIDPARAMETER :</tt> arguments incorrects.
 *   <br><tt> STG_E_DISKISWRITEPROTECTED :</tt> disk write protected.
 *   <br><tt> STG_E_UNKNOWN :</tt> unexpected error.
*/          
  HRESULT WriteLineW ( const CATUnicodeString * iBuff);


/**
 * Crypts and write a line for crypted text files.
 * <b>Role</b>: Crypts Writes the null-terminated unicode  string pointed to
 * by the iBuff parameter. The method does not crypt and write the terminating
 * null character.
 * This method  will be only used for non V5 documents.
 * @param  iBuff [in]
 *  uncrypted Line  to write.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> STG_E_WRITEFAULT :</tt> problem while writing.
 *   <br><tt> STG_E_MEDIUMFULL :</tt> disk full error.
 *   <br><tt> STG_E_INVALIDPARAMETER :</tt> arguments incorrects.
 *   <br><tt> STG_E_DISKISWRITEPROTECTED :</tt> disk write protected.
 *   <br><tt> STG_E_UNKNOWN :</tt> unexpected error.
*/
  HRESULT WriteLineWchar ( const  CATUC2Bytes* iBuff);


  private:
  
  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAASysCryptedILB(const CAASysCryptedILB &iObjectToCopy);
  
  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAASysCryptedILB & operator = (const CAASysCryptedILB &iObjectToCopy);

  // To flush the current memory block
  HRESULT FlushCurBck();
  // To load into memory a disk block
  HRESULT ReadCurBck(size_t &oRead);

#ifdef _WINDOWS_SOURCE
  HANDLE _fd;
#else
  int _fd;
#endif
  
  // Block Size for the encryption algorithm
  static size_t _Size;
  // Statistics of the file
  STATSTG _Stat;
  // memory buffer
  char * _Buff;
  // Space really used in the buffer ( usefull for the last block of the file)
  size_t _Used;
  // Current position in the memory buffer
  size_t  _CurPos;
  // Offset of the begining of the Buffer in the file 
  ULARGE_INTEGER _Offset;
  // Physical file offset needed for avoiding too many seeks
  ULARGE_INTEGER _FileOffset;
  //File Size
  ULARGE_INTEGER _FileSize;
  // flags
  int _State;
  // Encrypted or not
  int _Encrypted;
  
};
#endif
