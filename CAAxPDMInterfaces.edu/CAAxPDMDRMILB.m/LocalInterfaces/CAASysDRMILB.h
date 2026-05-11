// COPYRIGHT DASSAULT SYSTEMES 2006
#ifndef __CAAESysDRMILB
#define __CAAESysDRMILB
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CATSysDRMDocument component and implementing 
//  the CATIUExitDRMILockBytes, CATIUExitDRMDocument and CATIUExitDRMAuthorization
//
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown
#include "CATIUExitDRMILockBytes.h"
#include "CATILockBytes.h"


class CAASysDRMILB : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAASysDRMILB();
    virtual ~CAASysDRMILB();

  // ILockBytes   
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


  // CATIUExitDRMILockBytes
  HRESULT  OpenOnILockBytes ( CATILockBytes *iILB);

  HRESULT Close();



 private:
  
  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAASysDRMILB(const CAASysDRMILB &iObjectToCopy);
  
  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAASysDRMILB & operator = (const CAASysDRMILB &iObjectToCopy);

  HRESULT FlushCurBck();
  HRESULT ReadCurBck(size_t &oRead);

  
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
  // Physical size of the document for padding purpose
  ULARGE_INTEGER _FileSize;
  // flags
  int _State;
  // ILockBytes
  CATILockBytes *_ILB;

  // current symetric key
  unsigned char *_key;
  // size of the key
  size_t _KeySize;

};
#endif
