// COPYRIGHT DASSAULT SYSTEMES 2006

//Local Framework
#include "CAASysDRMILB.h"
#include "CAASysDRMCtrl.h"
#include "CAASysDRMDocument.h"


// System Framework
#include "CATUnicodeString.h"
#include "CATLib.h"
#include "CATIUExitDRMILockBytes.h"
#include "CATIUExitDRMDocument.h"
#include "CATIUExitDRMAuthorization.h"
#include "CATSysDRMRights.h"


//-----------------------------------------------------------------------------
// To create the TIE object on the CATIUExitDRMILockBytes
#include "TIE_CATIUExitDRMILockBytes.h"
TIEchain_CATIUExitDRMILockBytes(CAASysDRMILB);
CATImplementClass(CAASysDRMILB, CacheExtension,
		  CATBaseUnknown, CATSysDRMDocument);

// Contrary to the CATIUExitDRMDocument and CATIUExitDRMAuthorization
// the CATIUExitDRMILockBytes has to be implemented in a separate class and
// declared as a cache extension. This enables to get a new instance of the 
// interface with each QueryInterface. Thus it is possible to have more than
// one instance of CATIUExitDRMILockBytes associated to a given instance of
// the couple of interfaces CATIUExitDRMDocument and CATIUExitDRMAuthorization.
// This behavior is used to manipulate a temporary file during the save.
// For a given CATIUExitDRMDocument/CATIUExitDRMAuthorization object the 
// V5 code will instanciate two instance of CATIUExitDRMILockBytes.


//----------------------------------------------------------------------------
//  insert the following line in the interface dictionary:
//  CAASysDRMILB CATIUExitDRMILockBytes		libCAASysDRMILB
//  CAASysDRMILB CATIUExitDRMDocument		libCAASysDRMILB
//  CAASysDRMILB CATIUExitDRMAuthorization	libCAASysDRMILB
//----------------------------------------------------------------------------
 
#define DRMmin(a,b)	((a<b) ? a: b)

// Buffer Size
size_t  CAASysDRMILB::_Size = 0;

// Cipher block size for symetric algorithm
#define CBS		16

// General Remark
// The proposed implementation of the CATIUExitDRMILockbytes is intended to be 
// used with a symetric encryption algorithm. The key point is that we have
// a bijective function between the offset in the encrypted document and the 
// offset in the original document.
// We strongly advise to used only algorithms with such a property, because
// if no bijective function between encrypted offset an original ones is available
// the only solution will be to crypt/encrypt the document as a whole entity.
// All partial loading properties will be lost.


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
CAASysDRMILB::~CAASysDRMILB() 
{
  Close();
  delete [] _Buff;
  _Buff =NULL;
  delete []_key;
  _key = NULL;
}



//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMILB::Close() 
{
  // Remark.
  // Releasing and destroying a CATIUExitDRMILockBytes only means that the 
  // physical repository of the DRM document is no more accessible ie mostly
  // for a file the file is physicaliy closed. However it does not mean that the 
  // DRM Document is no more in session. The logical closing corresponding to 
  // exit of the DRM document from the session is bound to the 
  // CATIUExitDRMAuthorization interface.
  // One needs to flush everything before releasing the ILockBytes.
  Flush();


  // Cleaning of member data correcponding to the ILockBytes
  // Important !
  memset ( _Buff, '\0', _Size);
  _State = 0;
  _Offset.QuadPart=0;
  _CurPos=0;
  _Used = 0;
  _FileOffset.QuadPart =0;
  _FileSize.QuadPart =0;

  // One needs to release the underlying provided ILockBytes.
  if (_ILB) _ILB->Release();
  _ILB =NULL;
  STATSTGDEL(_Stat.pwcsName);
  memset (&_Stat, '\0', sizeof (STATSTG));
  return S_OK;
}



//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
CAASysDRMILB::CAASysDRMILB() :
  _ILB (NULL),  _key (0), _KeySize(0)
{
  //Init STATSTG structure
  memset ( (void*)&_Stat, '\0', sizeof(STATSTG));

  if ( _Size ==0)
    {
      // We work in CBC on a _Size bytes long window 
      // The size of this window is customizable through the following variable
      const char *tmp=CATGetEnv( "CAASysCryptedILBBufferSize");
      if ( tmp!=0)
	_Size = atoi (tmp);
      if (( _Size ==0) || ( _Size ==-1))
	_Size=256;
    }

  _Buff = new char [ _Size + CBS];
  // State of the block ( dirty or not )
  _State = 0;
  // Begin offset of the buffer block in the file 
  _Offset.QuadPart=0;
  // Current offset in the block
  // ie the offset in the file is _Offset+_CurPos
  _CurPos=0;
  _Used = 0;
  // Offset in the real file need to avaid to many seeks
  _FileOffset.QuadPart =0;
  _FileSize.QuadPart =0;
}




  


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMILB::OpenOnILockBytes( CATILockBytes  * iILB)
{
  // iILB is provided by DS code. The implementer of the user exit does not
  // need to know where the document physically resides.
  HRESULT hres = S_OK;
  // It is fundamental to store the adress here and to make and AddRef.
  // All physical ReadAt and WriteAt must be redirect onto this object
  if ( iILB == NULL) 
    return STG_E_INVALIDHANDLE;
  _ILB = iILB;
  _ILB->AddRef();

  // Retrieving of the encryption key.
  // The key has been provided by the interface CATIUExitDRMDocument that
  // has been already called before the OpenOnILockBytes (DRMImportEnveloppe)
  CATIUExitDRMDocument *Doc =NULL;
  hres = QueryInterface( IID_CATIUExitDRMDocument,(void**)&Doc);
  if (FAILED(hres))	return hres;
  void *tmp =NULL;
  size_t size =0;
  hres = Doc->DRMExportEnveloppe ( tmp, size);
  Doc->Release();
  if (FAILED(hres))	return hres;
  
  CAASysDRMCtrl *ctrl = CAASysDRMCtrl::GetCtrl();
  if (ctrl == NULL) return  DRM_E_NOKEY;
  hres = ctrl->DecryptSymetricKey( tmp, size, _key, _KeySize);
  if (FAILED(hres))	return hres;
  if (_key ==NULL)      return E_FAIL;


  // Physical size of document ;
  _ILB->Stat (&_Stat,STATFLAG_NONAME);
  _FileSize = _Stat.cbSize;

  
  // For test purpose
  CATIUExitDRMAuthorization *DRMAuth=NULL;
  hres=QueryInterface(IID_CATIUExitDRMAuthorization,(void**)&DRMAuth);
  if ( SUCCEEDED(hres))
    {
      hres = DRMAuth->IsGranted (CATDRM_READ);
      DRMAuth->Release();
    }
  return hres ;
}
  

//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMILB::ReadAt( ULARGE_INTEGER iOffset, void FAR *iBuff,
			      ULONG iLengthToRead, ULONG FAR *oLengthRead)
{
  HRESULT hres = S_OK;
  // Setting the file pointer
  // where is the iOffset for the current block
  ULARGE_INTEGER OffBck;
  OffBck.QuadPart= (iOffset.QuadPart / _Size)* _Size;
  // Still in the current block or no block read
  if ((OffBck.QuadPart != _Offset.QuadPart) || (_Used == 0))
    {
      // Flush the block if necessary
      if ((_State & 0xF)==1 )
	FlushCurBck ();
      // Read and decrypt a new one at the given position
      _Offset =  OffBck;
      size_t Read=0;
      hres = ReadCurBck( Read);
      if (FAILED(hres) || (Read<0))
 	return STG_E_READFAULT;
 
      // important for the last block of the file 
      _Used = Read;
      _FileOffset.QuadPart = _Offset.QuadPart + _Used;
    }

  // where are we exactly in the current block in memory.
  _CurPos = (size_t)(iOffset.QuadPart - _Offset.QuadPart);
  

  *oLengthRead=0;
  ULONG rest=iLengthToRead;
  size_t  offset=0, len =rest;
  // _Used =0 implies that we are at the end of the file
  while (( *oLengthRead!=iLengthToRead) && (hres == S_OK) && 
	 (_Used !=0) && (len !=0))
    {
      len =DRMmin( rest, _Used-_CurPos);
      memcpy ( (char*)iBuff+offset, _Buff+_CurPos, len);
      rest -= len;
      *oLengthRead +=len;
      _CurPos += len;
      offset +=len;
      // reading of the subsequent block if necessary
      if ( _CurPos == _Size)
	{
	  // flush the current block if it is dirty
	  if ((_State & 0xF)==1 )
	    FlushCurBck ();
	  else
	    {
	      _CurPos =0;
	      _Offset.QuadPart += _Size;
	    }
	  size_t Read=0;
	  // Read + decrypt the new block
	  hres = ReadCurBck( Read);
	  if (FAILED(hres) || (Read<0))
	    return STG_E_READFAULT;
	  _Used = Read;
	  _FileOffset.QuadPart = _Offset.QuadPart + _Used;
	}
    } 
  
  return hres;
}
    

//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMILB::WriteAt( ULARGE_INTEGER iOffset, 
			       const void FAR *iBuff,
			       ULONG iLengthToWrite, 
			       ULONG FAR *oLengthWritten)
{
  HRESULT hres = S_OK;
  // Setting the file pointer
  // where is the iOffset 
  ULARGE_INTEGER OffBck;
  OffBck.QuadPart= (iOffset.QuadPart / _Size) *_Size;
  // Still in the current block? if not the block must be flushed to disk
  // if it has been written.
  if (OffBck.QuadPart != _Offset.QuadPart)
    {
      if ( (_State & 0xF)==1)
	FlushCurBck ();
      // Set the current position at OffBck
      // No reading yet because it is perhaps useless => _Used=0
      _Used = 0;
      _Offset =  OffBck;
      _CurPos = 0;
      _FileOffset = _Offset;
    }

  // where are we exactly in the current block in memory.
  _CurPos = (size_t)(iOffset.QuadPart - _Offset.QuadPart);


  // Writing
  *oLengthWritten=0;
  ULONG rest=iLengthToWrite;
  size_t  offset=0;
  while (( *oLengthWritten!=iLengthToWrite) && (hres == S_OK))
    {
      // if _Buff is empty (_Used=0) and if the block will not be 
      // completly overwritten  we must read it 
      if ((_Used == 0) && (( rest < _Size) || (_CurPos!=0)))
	{
	  size_t Read =0;
	  // reading at _FileOffset => _Offset = _FileOffset
	  hres = ReadCurBck( Read);
	  if (FAILED(hres) || (Read<0))
	    return STG_E_READFAULT;

	  _Used = Read;
	 // _Offset = _FileOffset;
	  _FileOffset.QuadPart = _Offset.QuadPart + _Used;
	  // decrypt _Buff
	}
      
      // how much can we write in the current buffer ?
      size_t len =DRMmin( rest, _Size-_CurPos);
      memcpy ( _Buff+_CurPos, (char*)iBuff+offset, len);
      rest -= len;
      offset+=len;
      *oLengthWritten +=len;
      _CurPos += len;
      // Block Dirty
      _State |= 1;
      // for the last block we can increase _Used
      if ( _Used < _CurPos)
	_Used = _CurPos;
      // Flush the current block ( and crypt of course)
      if ( _CurPos == _Size)
	{
	  hres =FlushCurBck();
	}
    } 
  
  return S_OK;
}

 

//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMILB::SetSize( ULARGE_INTEGER iLength)
{
  // No size modification on RO files
  HRESULT hres =S_OK;
  if ((_Stat.grfMode & 0xF) == STGM_READ)
    return STG_E_INVALIDFLAG;
  else  if (_ILB )
    {
      // We flush everything before doing the job
      if ((_State & 0xF)==1 )
	FlushCurBck();
      // We take into memory the block where the trucation will occur
      // Setting the file pointer
      ULARGE_INTEGER OffBck;
      OffBck.QuadPart= (iLength.QuadPart / _Size)* _Size;
      // Read and decrypt a new one at the given position
      _Offset =  OffBck;
      size_t Read=0;
      hres = ReadCurBck( Read);
      if (FAILED(hres) || (Read<0))
 	return STG_E_READFAULT;
      // important for the last block of the file 
      _Used = Read;
      _FileOffset.QuadPart = _Offset.QuadPart + _Used;
      _CurPos = Read;
    
      // we truncate right inside the block in memory
      _Used = iLength.QuadPart - _Offset.QuadPart;
      memset ( _Buff + _Used, '\0', _Size -_Used);
      _State |=1;
      _FileOffset.QuadPart = _Offset.QuadPart;
      // The Size will be truncate at _Offset
      _FileSize.QuadPart =  _Offset.QuadPart;
      _CurPos = _Used;
      // to avoid to keep garbage at the end, we set the size at the 
      // beginning of the current memory block
      hres =_ILB->SetSize( _Offset);
    }
  return hres ;
}



//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMILB::LockRegion( ULARGE_INTEGER iOffset, 
				  ULARGE_INTEGER iLegnth,
				  DWORD dwLockType) 
{
  // No Need To implement
  return STG_E_UNIMPLEMENTEDFUNCTION;
}

//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************  
HRESULT CAASysDRMILB::UnlockRegion( ULARGE_INTEGER iOffset,  
				    ULARGE_INTEGER iLength,
				    DWORD dwLockType) 
{
  // No Need To implement
  return STG_E_UNIMPLEMENTEDFUNCTION;
}
   
//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMILB::Stat( STATSTG FAR *oStat,  DWORD iStatFlag)
{
  if (_ILB==NULL) return STG_E_INVALIDHANDLE;
  HRESULT hres=S_OK;
  hres = _ILB->Stat( &_Stat, iStatFlag);
  
  // Size Update
  // Caution with the padding
  // this point is not important for the V5 document because we never bother 
  // really on the exact size of the CATILockbytes ( the compound file structure
  // manage all the size information directly.
  // However there is here a potential difference between the physical size and 
  // the size of the user data because of the padding at the end.
  // thus we need to read the last block and decrypt it ...
  if ((_Offset.QuadPart == (_Stat.cbSize.QuadPart /_Size) *_Size) &&
      (( _Used >0) && (_Used <_Size)))
    {
      // the last block is still in memory
      _Stat.cbSize.QuadPart = _Offset.QuadPart +_Used;
    }
  else
    {
      if ((_State & 0xF)==1)
	FlushCurBck();
      // Reading of the last block to determine the amount of padding
      // Setting the offset 
      _Offset.QuadPart = (_Stat.cbSize.QuadPart /_Size) *_Size;
      size_t Read =0;
      ReadCurBck(Read);
      _Stat.cbSize.QuadPart = _Offset.QuadPart+ Read;
      // the Stat must not modify the offset
      // Invalidation of the memory block
      _CurPos=0;
      _Used =0;
      _Offset.QuadPart =0;
    }
  *oStat = _Stat;
  return hres;
}




//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMILB::FlushCurBck()
{
  if (_ILB==NULL) return STG_E_INVALIDHANDLE;
  if ( _key ==NULL) return E_FAIL;

  // padding if we are (over)writing the last block of the document
  // RFC 2630 - we have add CBS at the allocation to be able to add a whole
  // CBS long extra block for padding if _Used %CBS =0
  // In this sample we use a symetric algorithm in CBC mode  on _Size long window.
  // We need to padd a whole window only if it the last one. In  this case we will
  // add a whole block of CBS at the end file.
  // If we flush a partial window, as the window size _Size is a multiple of CBS
  // we know that we will never add a whole block of CBS padding.
  if ((( _Used ==_Size) && ( _FileSize.QuadPart < _Offset.QuadPart + _Used)) ||
      (( _Used !=_Size) && 
       ( _FileSize.QuadPart <= (((_Offset.QuadPart + _Used)/CBS)+1)*CBS ))) 
    {
      // Currently no symmetric algorithm use CBS > 255
      // AES works currently with CBS = 16
      char padding = CBS - (_Used % CBS);
      memset ( _Buff + _Used , padding, padding);
      _Used += padding;
    }
  
  // Symetric provider retrieving
  CAASysDRMCtrl *ctrl = CAASysDRMCtrl::GetCtrl();
  if (ctrl == NULL) return  DRM_E_NOKEY;
  CAASysSymetricProvider *Prov = NULL;
  ctrl->GetSymetricProvider ( Prov);
  if ( Prov == NULL) return  DRM_E_NOKEY;
  Prov->InitProvider( CAASysSymetricProvider::CBC, 
		      CAASysSymetricProvider::crypt, _key, _KeySize);
 
  char *Crypt=new char [_Size+ CBS];
  memset (Crypt, '\0', (_Size + CBS));
  size_t used = DRMmin (_Size, _Used), cryptedlen;
  
  Prov->Encrypt( _Buff, used, Crypt, cryptedlen);
  // Extra block for padding is gone beyond _Size 
  // as we work in CBC on  _Size length block we need to add a new block
  if ( _Used > _Size)
    Prov->Encrypt((_Buff+_Size), CBS, Crypt+_Size, cryptedlen);
  delete Prov;


  // First verification of the physical offset
  // FileOffset contains the offset of the last octect read or writen
  if ( _FileOffset.QuadPart != _Offset.QuadPart)
    _FileOffset = _Offset;
    
  
  ULONG len =0;
  HRESULT  hres = _ILB->WriteAt ( _Offset, Crypt, _Used, &len);
  delete [] Crypt;
  
  if ( (FAILED(hres)) || ( len != _Used ))
    return STG_E_WRITEFAULT;
  memset ( _Buff, '\0', _Size + CBS);
  _CurPos =0;
  
  _FileOffset.QuadPart = _Offset.QuadPart + len;
  _Offset.QuadPart = ((_Offset.QuadPart + len)/ _Size)* _Size;
  _Used = 0;
  _State = (_State & 0xFFFFFFF0);
  // New physical Size
  if ( _FileSize.QuadPart < _FileOffset.QuadPart)
    {
      _FileSize.QuadPart = _FileOffset.QuadPart;
      // For control purpose to be sure that everything is OK
      // No need to do it for performance issues
      STATSTG st;
      _ILB->Stat ( &st,  STATFLAG_NONAME);
      if ( _FileSize.QuadPart != st.cbSize.QuadPart)
	exit (-100);
    }
	
  return S_OK;
}





//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMILB::ReadCurBck(size_t &oRead)
{
  if (_ILB==NULL) return STG_E_INVALIDHANDLE;
  if ( _key ==NULL) return E_FAIL;

  // Read and decrypt the block at _Offset.
  // It is assume that this offset is aligned on BlockCipher size
  char * Decrypt= new char [_Size];
  memset ( (char*)Decrypt, '\0', _Size);
  oRead=0;
  HRESULT hres =S_OK;
  ULONG read = 0;
  hres = _ILB->ReadAt (_Offset, Decrypt, _Size, &read);
  oRead = read;
  if (FAILED(hres ))
    return hres;
  // no more data to read 
  if ( oRead == 0)
    {
      delete []Decrypt;
      return S_OK;
    }
  
  //Crypt _Buff
  CAASysDRMCtrl *ctrl = CAASysDRMCtrl::GetCtrl();
  if (ctrl == NULL) return  DRM_E_NOKEY;
  CAASysSymetricProvider *Prov = NULL;
  ctrl->GetSymetricProvider ( Prov);
  if ( Prov == NULL) return  DRM_E_NOKEY;
  memset (_Buff, '\0', _Size+ CBS);

  Prov->InitProvider( CAASysSymetricProvider::CBC, 
		      CAASysSymetricProvider::decrypt, _key,_KeySize);
  size_t r =0;
  Prov->Decrypt ( Decrypt, oRead, _Buff, r);
  delete Prov;

  delete []Decrypt;
  if ( r !=oRead)    return DRM_E_CRYPTCORRUPTION;
  
  // is it the last block of the file ie the one that could have
  // been padded
  size_t realSize= oRead;
  if ( _FileSize.QuadPart == _Offset.QuadPart + oRead)
    {
      char padding = _Buff[ oRead-1];
      // Control as we have always do a padding
      if ( padding > CBS) return DRM_E_CRYPTCORRUPTION;
      // Now we can remove exactly the number of characters pointed by padding
      // We check that they all have the padding value for control purpose
      for ( int i =0; i < padding; i++)
	{
	  if (_Buff[ oRead-1-i] == padding)
	    {
	      _Buff[ oRead-1-i] =0;
	      realSize --;
	    }
	  else
	    return DRM_E_CRYPTCORRUPTION;
	}
    }
  oRead=  realSize;
  return S_OK;
}


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMILB::Flush( void)
{
  HRESULT hres =S_OK;
  if ((_State & 0xF)==1)
    hres = FlushCurBck();
  return (hres );
}
 







