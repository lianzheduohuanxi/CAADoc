// COPYRIGHT DASSAULT SYSTEMES 2006

// System Framework
#include "CATLib.h"
#include "AES.h"
#include "CAASysDRMCtrl.h"
#include "CATSysDRMRights.h"



HRESULT CAASysSymetricProvider::InitProvider( Mode iMode, Direction iDir,
					      unsigned char * key, 
					      size_t KeyLen)
{
  Rijndael *prov = (Rijndael*)_Provider;
  if ( prov==NULL)	return E_FAIL;

  Rijndael::Mode  mode;
  if ( iMode == CAASysSymetricProvider::ECB)
    mode =Rijndael::ECB;
  else 
    mode = Rijndael::CBC;
  
  Rijndael::Direction dir;
  if ( iDir == CAASysSymetricProvider::crypt)
    dir = Rijndael::Encrypt;
  else
    dir = Rijndael::Decrypt;

  Rijndael::KeyLength keylen = Rijndael::Key32Bytes;
  if (KeyLen ==16)
    keylen = Rijndael::Key16Bytes;

  prov->init( mode, dir, key, keylen);
  return S_OK;
}


CAASysSymetricProvider:: CAASysSymetricProvider ()
{
  _Provider  = new Rijndael;
}

CAASysSymetricProvider:: ~CAASysSymetricProvider ()
{
  Rijndael *prov = (Rijndael*)_Provider;
  if ( prov) delete prov;
  _Provider = NULL;
}


HRESULT CAASysSymetricProvider:: Encrypt ( void *iPT, size_t iPTLen, 
					   void *oCT, size_t& oCTLen)
{
  HRESULT hres =S_OK;
  Rijndael *prov = (Rijndael*)_Provider;
  if (prov==NULL) return E_FAIL;
  int len = prov->blockEncrypt( (const UINT8 *) iPT, iPTLen*8,
				(UINT8 *)oCT);
  if (len >0)
    oCTLen = len/8;
  else
    hres = E_FAIL;
  return hres;
}



HRESULT CAASysSymetricProvider:: Decrypt ( void *iCT, size_t iCTLen, 
					   void *oPT, size_t& oPTLen)
{
  HRESULT hres =S_OK;
  Rijndael *prov = (Rijndael*)_Provider;
  if (prov==NULL) return E_FAIL;
  int len = prov->blockDecrypt( (const UINT8 *) iCT, iCTLen*8,
				(UINT8 *)oPT);
  if (len >0)
    oPTLen = len/8;
  else
    hres = E_FAIL;
  return hres;
}
