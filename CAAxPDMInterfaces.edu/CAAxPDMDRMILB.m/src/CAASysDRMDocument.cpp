// COPYRIGHT DASSAULT SYSTEMES 2006

//Local Framework
#include "CAASysDRMILB.h"
#include "CAASysDRMDocument.h"
#include "CAASysDRMCtrl.h"


// System Framework
#include "CATUnicodeString.h"
#include "CATLib.h"
#include "CATIUExitDRMILockBytes.h"
#include "CATIUExitDRMDocument.h"
#include "CATIUExitDRMAuthorization.h"
#include "CATSysDRMRights.h"


//-----------------------------------------------------------------------------
// To create the TIE object on the CATIUExitDRMDocument
#include "TIE_CATIUExitDRMDocument.h"
TIEchain_CATIUExitDRMDocument(CAASysDRMDocument);
// To create the TIE object on the CATIUExitDRMAuthorization
#include "TIE_CATIUExitDRMAuthorization.h"
TIE_CATIUExitDRMAuthorization(CAASysDRMDocument);

CATImplementClass(CAASysDRMDocument, DataExtension, CATBaseUnknown, CATSysDRMDocument);

//----------------------------------------------------------------------------
//  insert the following line in the interface dictionary:
//  CAASysDRMILB CATIUExitDRMILockBytes		libCAASysDRMILB
//  CAASysDRMILB CATIUExitDRMDocument		libCAASysDRMILB
//  CAASysDRMILB CATIUExitDRMAuthorization	libCAASysDRMILB
//----------------------------------------------------------------------------

//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
CAASysDRMDocument::~CAASysDRMDocument() 
{
  delete []_key;
  _key = NULL;
  delete []_Right;
  _Right = NULL;
}





//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
CAASysDRMDocument::CAASysDRMDocument() :
  _key (NULL), _KeySize(0), _Right (NULL), _RightSize (0)
{
}





//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMDocument::DRMCreateContext( const CATUC2Bytes * iDocumentID)
{
  HRESULT hres =S_OK;
  CAASysDRMCtrl *ctrl = CAASysDRMCtrl::GetCtrl();
  if (ctrl == NULL) return  DRM_E_NOKEY;
  int Activation =1;
  ctrl->GetDRMActivation (Activation);

  // if not activated we return S_FALSE
  if (  Activation ==0)
    return S_FALSE;
  else
    return hres;
}


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMDocument::DRMCloseContext()
{
  HRESULT hres =S_OK;
  return hres;
}


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMDocument::DRMExportEnveloppe ( void  *&oDRMEnveloppe,
						size_t &oDRMEnveloppeSize)

{
  HRESULT hres =S_OK;
  // for bufferization purpose, it is important to store the encryption key 
  // Thus we will avoid prompting the user for his password so long the document 
  // is in session, even if the  document has been physically closed.
  // We expose nothing through interfaces and only use C++ because the 
  // information we need to pass between the implementation is critical.
  CAASysDRMCtrl *ctrl = CAASysDRMCtrl::GetCtrl();
  if (ctrl == NULL) return  DRM_E_NOKEY;
  if (_key==NULL)
    {
      // 256 bits key
      _KeySize=0;
      ctrl-> DeriveSymetricKey(_key , _KeySize);
    }
 
  oDRMEnveloppeSize =0;
  ctrl->EncryptSymetricKey( _key, _KeySize, oDRMEnveloppe, oDRMEnveloppeSize );

  return hres;
}



//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMDocument::DRMFreeEnveloppe (void *oDRMEnvelope)
{
  HRESULT hres =S_OK;
  char *p= (char*)oDRMEnvelope;
  delete [] p;
  return hres;
}


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMDocument::DRMImportEnveloppe( const void *iDRMEnveloppe,
					       size_t iDRMEnveloppeSize)
{
  HRESULT hres =S_OK;
  if ( _key) delete []_key;
  _key = NULL;

  CAASysDRMCtrl *ctrl = CAASysDRMCtrl::GetCtrl();
  if (ctrl == NULL) return  DRM_E_NOKEY;
  size_t size=0;
  hres = ctrl->DecryptSymetricKey(iDRMEnveloppe, iDRMEnveloppeSize, _key, size);
  _KeySize = size;
  return hres;
}


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMDocument::DRMGetLibUID( GUID &oUID)
{
  // To redefine for your specific implementation with  uuid_gen
  // To update for each non compatible modification of the implementation.
  GUID Lib={ 0xbfa2aa67, 
	     0x9b9b, 
	     0x0000,
	     {0x02,0x80,0x03,0x10,0x74,0x00,0x00,0x00}};
  memcpy (&oUID, &Lib, sizeof (GUID));
  return S_OK;
}


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMDocument::DRMInitAuthorization( const CATUC2Bytes * iDocumentID)
{
  HRESULT hres =S_OK;
  return hres;
}


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMDocument::DRMReleaseAuthorization(const CATUC2Bytes *iDocID)
{
  HRESULT hres =S_OK;
  return hres;
}


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMDocument::DRMExportAuthorization(void  *&oDRMAuthorization,
						  size_t&oDRMAuthorizationSize)
{
  HRESULT hres =S_OK;
  if ( _Right == NULL)
    {
      CAASysDRMCtrl *ctrl = CAASysDRMCtrl::GetCtrl();
      if (ctrl == NULL) return  DRM_E_NOKEY;
      hres = ctrl-> EncryptAuthorization (_Right, _RightSize);
    }

  oDRMAuthorizationSize = _RightSize;
  oDRMAuthorization  = new char [ oDRMAuthorizationSize ];
  memset ( oDRMAuthorization, '\0',  oDRMAuthorizationSize);
  memcpy ( oDRMAuthorization, _Right, oDRMAuthorizationSize);
  return hres;
}



//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMDocument::DRMFreeAuthorization (void *oDRMAuthorization)
{
  HRESULT hres =S_OK;
  char *p= (char*)oDRMAuthorization;
  delete [] p;
  return hres;
}


//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMDocument::DRMImportAuthorization( const void *iDRMAuth,
						   size_t iDRMAuthSize)
{
  HRESULT hres =S_OK;
  _RightSize = iDRMAuthSize;
  if (_Right) delete [] _Right;
  _Right = new char [iDRMAuthSize];
  memcpy ( _Right, iDRMAuth, iDRMAuthSize);
  return hres;
}



//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
HRESULT CAASysDRMDocument::IsGranted( DWORD iRightToCheck)
{
  HRESULT hres =S_OK;
  CAASysDRMCtrl *ctrl = CAASysDRMCtrl::GetCtrl();
  if (ctrl == NULL) return  DRM_E_NOKEY;
  DWORD Authorization=0;
  hres = ctrl-> DecryptAuthorization (_Right, _RightSize, Authorization);


  //printf( "\nCurrent rights %x\n", Authorization);
  if (( Authorization & iRightToCheck) ==iRightToCheck)
    return S_OK;
  else
    {
      //printf( "Not granted for %x right\n", iRightToCheck);
      return DRM_E_ACCESSDENIED;
    }
  return hres;
}


