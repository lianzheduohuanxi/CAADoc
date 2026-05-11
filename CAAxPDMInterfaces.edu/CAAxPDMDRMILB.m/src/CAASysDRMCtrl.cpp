// COPYRIGHT DASSAULT SYSTEMES 2006

// System Framework
#include "CATUnicodeString.h"
#include "CATLib.h"
#include "AES.h"
#include "CAASysDRMCtrl.h"
#include "CATTime.h"
#include "CATSysDRMHR.h"
#include "CATSysSHA256.h"
#include "CATSysDRMRights.h"

#include "CATApplicationFrame.h"
#include "CATBasicAuthenticationPanel.h"
#include "CATDlgEditor.h"
#include "CATDlgNotify.h"
//#include "CATSysGetBatchMode.h"

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



// Memcpy to copy integer in BigEndian format
static void * Memcpy( char *Buff, int *Obj)
{
  // Copy in plateform format
  memcpy( Buff, (char *)Obj, sizeof(int));
#ifdef _ENDIAN_LITTLE
  Buff[0]^=Buff[3];
  Buff[3]^=Buff[0];
  Buff[0]^=Buff[3];
  Buff[1]^=Buff[2];
  Buff[2]^=Buff[1];
  Buff[1]^=Buff[2];
#endif
  return Buff;
}


#define DRMmin(a,b)	((a<b) ? a: b)
CAASysDRMCtrl *CAASysDRMCtrl::_DRMCtrl=NULL;

//default key size 256 bits
int CAASysDRMCtrl::_KeySize=32;


static void DRMWarning ( int iBatchMode, const char *iMessage, const char *iTitle)
{
  if ( iBatchMode == CATSysInteractive) 
  {
    CATDlgNotify *P=NULL;
    CATApplicationFrame *frm = CATApplicationFrame::GetFrame();
    if (frm == NULL)
      return;
    P = new CATDlgNotify (frm->GetMainWindow(), "Notif", CATDlgNfyWarning | CATDlgWndNoButton);
    P->DisplayBlocked (iMessage, iTitle);
  }
}

//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
CAASysDRMCtrl::~CAASysDRMCtrl() 
{
  delete []_User;
  _User = NULL;
  delete []_Pwd;
  _Pwd = NULL;
  delete []_DRMUsers;
  _DRMUsers=NULL;
  delete []_Rights;
  _Rights =NULL;
  _Activated=0;
}



//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
CAASysDRMCtrl::CAASysDRMCtrl() :
_User (NULL), _Pwd (NULL), _NbUsers (0),  _Activated (0), _Logged (0),
_DRMUsers (NULL), _Rights (NULL), _BatchMode(0),_DRMProfile(0)
{
  // Default user/password
  _BatchMode = CATSysGetBatchMode();
  if ( _BatchMode != CATSysInteractive)
  {
    // We need to have here a default user for batchs
    UpdateCtrl ( "batchuser", "batchpassword");
    _NbUsers = 1;
    _DRMUsers = new CATUnicodeString [_NbUsers];
    _Rights = new DWORD [_NbUsers];
    _DRMUsers[0] = "batchuser";
    _Rights[0] = CATDRM_READ | CATDRM_EDITRIGHT | CATDRM_SAVE;
    _Activated = 1;
    _Logged = 1;
  }

}


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::UpdateCtrl(const char *iUser, const char *iPwd) 
{
  char * User = (char*)iUser;
  char * Pwd = (char*) iPwd;

  // explicit login in dRM
  _Logged  = 1;

  if ((( iUser==NULL) && (iPwd==NULL)) ||
    ((iUser) && (iPwd) && (strlen(iUser)==0)))
  {
    // No more user 
    delete []_User;
    delete []_Pwd;
    _Pwd  =  NULL;
    _User = NULL;
    _Logged = 0;
    return S_OK;
  }

  if (_User ) 
    delete []_User;
  _User  = new char [strlen (User)+1];
  memset ( _User, '\0', strlen (User)+1);
  memcpy ( _User, User, strlen (User));
  if (_Pwd ) 
    delete []_Pwd;
  _Pwd   = new char [65];
  memset ( _Pwd, '\0', 65);


  // Password generation 
  off_t off =0;
  if ( strlen(Pwd) >0)
  {
    while ( off < 64)
    {
      size_t len =DRMmin(strlen(Pwd), 64-off);
      memcpy ( _Pwd+off, Pwd, len);
      off += len;
    }
  }
  else
    memset(_Pwd, 'a', 64);

  off = 61;
  //memcpy ( _Pwd + off, _User, 3);
  return S_OK;
}



//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::DeriveSymetricKey (unsigned char *&oKey, size_t &oKeySize)
{
  if ( _Logged ==0) return DRM_E_NODRM;

  // 256 bits key
  // salt generation.
  char tmp [64],salt[64];
  CATTime T;
  sprintf (tmp, "%x%x%x%x", rand(), this, CATGetProcessId(),T.Gettime_t());
  off_t off =0;
  while ( off < 64)
  {
    size_t len =DRMmin(strlen(tmp), 64 -off);
    memcpy ( salt + off, tmp , len);
    off += len;
  }

  // Password Usage 
  int i = 0;
  for (; i < 64; i++)
    salt[i] ^= _Pwd[i];
  // derivation
  DWORD H [8] = {0,0,0,0,0,0,0,0};
  for ( i=0; i < 64; i++)
    CATSysSHA_256 ( salt, 64, H);

  oKeySize = _KeySize;
  // In this sample _KeySize is either equal to 16 or 32
  // corresponding to 128 or 256 bits keys
  oKey = new unsigned char[ _KeySize];
  memcpy ( oKey, H, DRMmin(_KeySize,sizeof(DWORD)*8));

  return S_OK;
}

//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::EncryptSymetricKey (unsigned char *key, int iKeySize,
                                           void  *&oCryptedkey,
                                           size_t &oCryptedKeySize)
{
  if ( _Logged ==0) return DRM_E_NODRM;
  // dummy encryption of the key - just for test purpose
  // We XOR the password to the key and append the the SHA-256 of the Password 
  // for signature purpose, then we store all this in Big Endian format
  // for cross-platform interoperability.
  oCryptedKeySize=  (iKeySize*4 +32);
  char  *tmp = new char [oCryptedKeySize];
  if ( tmp == NULL)  
    return DRM_E_INSUFFICIENTMEMORY;
  memset ( tmp, '\0', oCryptedKeySize);

  int *tab = (int *)tmp;
  int i = 0;
  for (; i< iKeySize; i++)
  {
    tab [i] = key [i] ^ _Pwd[i];
  }

  // Signature of the password
  DWORD H [8] = {0,0,0,0,0,0,0,0};
  CATSysSHA_256 ( _Pwd, 64, H);
  memcpy( &tab[ iKeySize], H, 8*sizeof (DWORD));

  // BigLittle 
#ifdef _ENDIAN_LITTLE
  for ( i=0; i < iKeySize+8; i++)
  {
    char *Buff= (char*)&tab[i];
    Buff[0]^=Buff[3];
    Buff[3]^=Buff[0];
    Buff[0]^=Buff[3];
    Buff[1]^=Buff[2];
    Buff[2]^=Buff[1];
    Buff[1]^=Buff[2];
  }
#endif

  oCryptedkey = tmp;
  return S_OK;
}


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::DecryptSymetricKey  (const void *Cryptedkey, size_t iSize,
                                            unsigned char *&oKey, size_t &oKeySize)
{
  if ( _Logged ==0) 
  {
    DRMWarning (_BatchMode, "CAA-DRM Warning: You are not logged in DRM", "DRM warning");
    return DRM_E_NODRM;
  }

  static int recursion=0;
  oKeySize = iSize / sizeof(int);
  // We are waiting for a 256 or 128 bits keys (32/16 bytes) + 8 bytes of SHA256
  // stored on 40/24 int32
  if (( oKeySize != 40) && (oKeySize!= 24))
    return DRM_E_NOKEY;
  int *tmp = new int [ oKeySize ];
  if (tmp == NULL)
    return DRM_E_INSUFFICIENTMEMORY;
  memcpy (tmp, Cryptedkey, iSize);

  // Big Endian
#ifdef _ENDIAN_LITTLE
  int i = 0;
  for ( ; i < oKeySize ; i++)
  {
    char *Buff= (char*)&tmp[i];
    Buff[0]^=Buff[3];
    Buff[3]^=Buff[0];
    Buff[0]^=Buff[3];
    Buff[1]^=Buff[2];
    Buff[2]^=Buff[1];
    Buff[1]^=Buff[2];
  }
#endif

  oKeySize -=8;
  // Signature of the password
  DWORD H [8] = {0,0,0,0,0,0,0,0};
  CATSysSHA_256 ( _Pwd, 64, H);

  // the last 8 DWORD are the SHA256 of _Pwd
  // We can check the signature of the user
  int ret = memcmp ( &tmp[oKeySize], H, 8*sizeof(DWORD));
  if ( ret != 0)
  {
    HRESULT hres = DRM_E_NOKEY;
    // for display and test purpose
    if ( FAILED(hres))
      DRMWarning (_BatchMode,"CAA-DRM Error: The password is not correct to decrypt the current document","DRM Error");
    return hres;
  }


  oKey = new unsigned char [oKeySize];
  memset ( oKey, '\0', oKeySize);
  for (int i=0; i< oKeySize; i++)
    oKey[i] = tmp [i] ^ _Pwd[i] ;

  delete []tmp;
  return S_OK;
}

//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
CAASysDRMCtrl* CAASysDRMCtrl::GetCtrl()
{
  if (_DRMCtrl ==NULL)
    _DRMCtrl = new CAASysDRMCtrl();

  return _DRMCtrl;
}


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::SetAuthorization(CATUnicodeString *iUsers, DWORD *iRights, 
                                        int nb)
{
  delete []_DRMUsers;
  delete []_Rights;
  _Rights =NULL;
  _DRMUsers =NULL;
  _NbUsers = 0;

  if ( nb)
  {
    _DRMUsers = new CATUnicodeString[nb];
    _Rights = new DWORD [nb];
    _NbUsers= nb;
    for ( int i=0; i < nb; i++)
      _DRMUsers[i] = iUsers[i];
    memcpy ( _Rights, iRights, nb*sizeof(DWORD));
  }
  return S_OK;
}

//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::GetAuthorization(CATUnicodeString *&iUsers, DWORD *&iRights, int& nb)
{
  nb = _NbUsers;
  if (nb)
  {
    iUsers = new CATUnicodeString[nb];
    iRights = new DWORD [nb];
    for ( int i=0; i < nb; i++)
    {
      iUsers[i] = _DRMUsers[i];
      iRights[i] = _Rights[i];
    }
  }
  return S_OK;
}


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::EncryptAuthorization( char *&oRight, size_t &oSize)
{
  if ( _Logged ==0) return DRM_E_NODRM;
  if ( _NbUsers == 0)
  {
    // without any user you will create a file with no right !
    DRMWarning (_BatchMode, "CAA-DRM Warning: You should add some users before !","DRM Warning");
    return DRM_E_NODRM;
  }

  // Generation of the Authorization blob
  // Caution the blob must be platform independant -thus we must take care
  // of the endianess of the architecture.
  size_t len=0;
  int i = 0;
  for (; i< _NbUsers; i++)
    //  round to the upper 4
    len += ((_DRMUsers[i].GetLengthInByte())/4 +1)*4 + 4;
  len += _NbUsers*sizeof(DWORD);
  // for _NbUsers and  signature
  len += 4 + 32 ;
  char * blob = new char [len +1 ];
  memset ( blob, '\0', len+1);
  off_t off=0;
  // Big Endian memcpy
  Memcpy ( blob+off, &_NbUsers);
  off += sizeof(int);
  printf ("NB users %d", _NbUsers);
  for ( i =0; i< _NbUsers; i++)
  {
    printf ( "Crypt %s - %x", _DRMUsers[i].ConvertToChar(), _Rights[i]);
    int ll = _DRMUsers[i].GetLengthInByte();
    int llpadded = (ll/4 +1)*4;
    Memcpy ( blob+off, &llpadded);
    off += sizeof(int);
    memcpy ( blob+off, _DRMUsers[i].ConvertToChar(), ll);
    ll = (ll/4 +1)*4;
    //padding
    off += ll;
    Memcpy ( blob+off, (int*)&_Rights[i]);
    off+=  sizeof(DWORD);
  }

  // Signature of the password.
  // It is intended to assert the validity of the Rights block. Other solution are
  // of course possible, like storing a crc of the bloc etc.
  // The current solution insure that only a user with the right password can decrypt
  // the rights block
  DWORD H [8] = {0,0,0,0,0,0,0,0};
  CATSysSHA_256 ( _Pwd, 64, H);
  for ( i=0 ; i<8; i++)
  {
    Memcpy ( blob+off, (int*)&H[i]);
    off+=sizeof(DWORD);
  }

  // dummy encryption XOR with _Pwd
  int lenkey = strlen (_Pwd);
  int *tmp = (int *)blob;
  // len % 4 = 0
  for ( i=0; i < len ; i++)
  {
    blob [i] ^= _Pwd[i% lenkey];
    blob [i] = ~blob [i];
  }


  oRight = blob;
  oSize = len;
  return S_OK;
}


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::DecryptAuthorization( char *iRight, size_t iSize, 
                                            DWORD &oRight) 
{
  if ( _Logged ==0) return DRM_E_NODRM;
  // Nothing to decrypt => corruption 
  if (( iSize ==0) || ( iRight ==NULL))
    return DRM_E_CRYPTCORRUPTION;

  // copy because we will modify the buffer
  char *Right = new char [iSize];
  memcpy ( Right, iRight, iSize);
  // dummy decryption XOR with _Pwd
  int lenkey = strlen (_Pwd);
  int *tmp = (int *)Right;
  // iSize % 4 = 0 
  if (( iSize % 4) !=0)
    return DRM_E_CRYPTCORRUPTION;

  int i = 0;
  for ( ; i < iSize; i++)
  {
    Right[i] ^= _Pwd [ i % lenkey];
    Right[i] = ~Right[i];
  }


  // Signature of the password
  DWORD H [8] = {0,0,0,0,0,0,0,0};
  CATSysSHA_256 ( _Pwd, 64, H);

  // the last 8 DWORD are the SHA256 of _Pwd
  // We can check the signature of the user
  HRESULT hres = S_OK;
  for ( i =8; i>0; i--)
  {
    DWORD h=0;
    Memcpy ( (char*)&h, (int*)(Right+iSize- i*4));
    if ( h != H[8-i])
    {
      hres = DRM_E_CRYPTCORRUPTION;
      break;
    }
  }
  if (FAILED(hres)) return hres;

  // Interpretation of the Authorization blob
  oRight = 0;
  int NbUsers =0;
  off_t off = 0;
  Memcpy ( (char*)&NbUsers, (int*)Right);
  printf ("Decrypt NB users %d", NbUsers);
  off +=  sizeof(int);
  DWORD Authorization = 0;
  CATUnicodeString User;
  if (NbUsers)
  {
    int len=0;
    for ( i =0; i< NbUsers; i++)
    {
      //  size of the user name
      Memcpy ((char*)&len, (int*)(Right+off));
      off +=  sizeof(int);
      User = (Right+off);
      off+= len;
      Memcpy( (char*)&Authorization, (int*)(Right+off));
      off +=  sizeof(int);
      // Test with the current logged User
      printf ( "\nuser %d %s - %x",i, User.ConvertToChar(), Authorization);
      if ( User ==_User)
      {
        oRight = Authorization;
        break;
      }
    }
  }
  delete []Right;
  return S_OK;
}


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::GetDecryptAuthorization(char *iRight, size_t iSize,
                                               CATUnicodeString *&oUsers, 
                                               DWORD *&oRights, int& oNb)
{
  // Nothing to decrypt => corruption 
  if (( iSize ==0) || ( iRight ==NULL))
    return DRM_E_CRYPTCORRUPTION;
  // copy because we will modify the buffer
  char *Right = new char [iSize];
  memcpy ( Right, iRight, iSize);
  // dummy decryption XOR with _Pwd
  int lenkey = strlen (_Pwd);
  int *tmp = (int *)Right;
  // iSize % 4 = 0 
  if (( iSize % 4) !=0)
    return DRM_E_CRYPTCORRUPTION;
  int i = 0;
  for ( ; i < iSize; i++)
  {
    Right[i] ^= _Pwd [ i % lenkey];
    Right[i] = ~Right[i];
  }

  // Signature of the password 
  DWORD H [8] = {0,0,0,0,0,0,0,0};
  CATSysSHA_256 ( _Pwd, 64, H);

  // the last 8 DWORD are the SHA256 of _Pwd
  // We can check the signature of the user
  HRESULT hres = S_OK;
  for ( i =8; i>0; i--)
  {
    DWORD h=0;
    Memcpy ( (char*)&h, (int*)(Right+iSize- i*4));
    if ( h != H[8-i])
    {
      hres = DRM_E_CRYPTCORRUPTION;
      break;
    }
  }
  if (FAILED(hres)) return hres;


  // Interpretation of the Authorization blob
  int NbUsers =0;
  off_t off = 0;
  Memcpy ( (char*)&NbUsers, (int*)Right);
  printf ("Decrypt NB users %d", NbUsers);
  off +=  sizeof(int);
  DWORD Authorization = 0;
  if (NbUsers)
  {
    oNb = NbUsers;
    oUsers = new CATUnicodeString[NbUsers];
    oRights = new DWORD [NbUsers];
    int len=0;
    for ( i =0; i< NbUsers; i++)
    {
      //  size of the user name
      Memcpy ((char*)&len, (int*)(Right+off));
      off +=  sizeof(int);
      oUsers[i] = (Right+off);
      off+= len;
      Memcpy( (char*)&Authorization, (int*)(Right+off));
      off +=  sizeof(int);
      // Test with the current logged User
      printf ( "\nuser %d %s - %x",i, oUsers[i].ConvertToChar(), Authorization);
      oRights[i] = Authorization;
    }
  }
  delete [] Right;
  return S_OK;
}

//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::GetEncryptAuthorization(CATUnicodeString* iUsers, 
                                               DWORD* iRights, int iNb,
                                               char* &oRight, size_t& oSize)
{
  // Generation of the Authorization blob
  // Caution the blob must be platform independant -thus we must take care
  // of the endianess of the architecture.
  size_t len=0;
  int i = 0;
  for (; i< iNb; i++)
    //  round to the upper 4
    len += ((iUsers[i].GetLengthInByte())/4 +1)*4 + 4;
  len += iNb*sizeof(DWORD);
  // for _NbUsers and signature
  len += 4 +32;
  char * blob = new char [len +1];
  memset ( blob, '\0', len+1);
  off_t off=0;
  // Big Endian memcpy
  Memcpy ( blob+off, &iNb);
  off += sizeof(int);
  //printf ("NB users %d", iNb);
  for ( i =0; i< iNb; i++)
  {
    //printf ( "Crypt %s - %x", iUsers[i].ConvertToChar(), iRights[i]);
    int ll = iUsers[i].GetLengthInByte();
    int llpadded = (ll/4 +1)*4;
    Memcpy ( blob+off, &llpadded);
    off += sizeof(int);
    memcpy ( blob+off, iUsers[i].ConvertToChar(), ll);
    ll = (ll/4 +1)*4;
    //padding
    off += ll;
    Memcpy ( blob+off, (int*)&iRights[i]);
    off+=  sizeof(DWORD);
  }

  // Signature of the password
  DWORD H [8] = {0,0,0,0,0,0,0,0};
  CATSysSHA_256 ( _Pwd, 64, H);
  for ( i=0 ; i<8; i++)
  {
    Memcpy ( blob+off, (int*)&H[i]);
    off+=sizeof(DWORD);
  }


  // dummy encryption XOR with _Pwd
  int lenkey = strlen (_Pwd);   //Used for logon so this is same password
  int *tmp = (int *)blob;
  // len % 4 = 0
  for ( i=0; i < len ; i++)
  {
    blob [i] ^= _Pwd[i% lenkey];
    blob [i] = ~blob [i];
  }
  oRight = blob;
  oSize = len;
  return S_OK;
}

//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::GetDRMActivation( int &oActivation)
{
  oActivation = _Activated;
  return S_OK;
}



//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::SetDRMActivation( int iActivation)
{
  _Activated = iActivation;
  return S_OK;
}

//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::GetCurrentUser ( CATUnicodeString &oUser)
{
  oUser = _User;
  return S_OK;
}


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::IsLogged ( int &oLogged)
{
  oLogged = _Logged;
  return S_OK;
}

//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::DRMGetProfile(int& oProfile)
{
  oProfile = _DRMProfile;
  return S_OK;
}
HRESULT CAASysDRMCtrl::DRMSetProfile(int iProfile)
{
  _DRMProfile = iProfile;
  return S_OK;
}

//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::SetSymetricKeySize( int iSize)
{
  _KeySize = iSize;
  return S_OK;
}

//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::GetSymetricKeySize( int& oSize)
{
  oSize = _KeySize;
  return S_OK;
}


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMCtrl::GetSymetricProvider ( CAASysSymetricProvider *&oProvider)
{
  oProvider = new CAASysSymetricProvider;
  return S_OK;
}
