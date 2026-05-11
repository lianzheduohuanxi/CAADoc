// COPYRIGHT DASSAULT SYSTEMES 2000
//
// Implementation of CAAIBiogNovel for the "CAAOsmBiographicalNovel"
// extension late type.  

// ObjectSpecsModeler Framework
#include "CATISpecAttrAccess.h"     // GetAttrKey, GetInteger, SetInteger
#include "CATISpecAttrKey.h"        // Result of GetAttrKey

// Other
#include "CAAEOsmBiogNovel.h"               
#include "iostream.h"

#include "TIE_CAAIBiogNovel.h"
TIE_CAAIBiogNovel(CAAEOsmBiogNovel);

CATImplementClass(CAAEOsmBiogNovel, 
				  DataExtension,
                  CATBaseUnknown,
				  CAAOsmBiographicalNovel);

HRESULT CAAEOsmBiogNovel::GetEpoch (CATUnicodeString *pEpoch) 
{
    cout << "Starting GetEpoch" << endl << flush;

// Retrieve the attribute keys

	CATISpecAttrAccess *piSpecAttrAccessOnEpoch = NULL;
	HRESULT rc = this -> QueryInterface(IID_CATISpecAttrAccess,
		                                (void**) &piSpecAttrAccessOnEpoch);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for CAAOsmBiographicalNovel" << endl << flush;
		return E_FAIL;
	}
 
	CATISpecAttrKey *piKeyEpoch = NULL;
	piKeyEpoch = piSpecAttrAccessOnEpoch ->	GetAttrKey("Epoch");
	if (NULL == piKeyEpoch)
	{
		cout << "ERROR in retrieving Epoch key" << endl << flush;
		return E_FAIL;
	}
	
// Retrieve the value of the "Epoch" attribute

	*pEpoch = piSpecAttrAccessOnEpoch -> GetString(piKeyEpoch);

    piSpecAttrAccessOnEpoch -> Release();
	piKeyEpoch -> Release();
	
  return S_OK;
}

HRESULT CAAEOsmBiogNovel::SetEpoch (const CATUnicodeString epoch) 
{
    cout << "Starting SetEpoch" << endl << flush;

// Retrieve the attribute keys

	CATISpecAttrAccess *piSpecAttrAccessOnEpoch = NULL;
	HRESULT rc = this -> QueryInterface(IID_CATISpecAttrAccess,
		                                (void**) &piSpecAttrAccessOnEpoch);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for CAAOsmBiographicalNovel" << endl << flush;
		return E_FAIL;
	}
 
	CATISpecAttrKey *piKeyEpoch = piSpecAttrAccessOnEpoch -> 
		GetAttrKey("Epoch");
	if (NULL == piKeyEpoch)
	{
		cout << "ERROR in retrieving Epoch key" << endl << flush;
		return E_FAIL;
	}
	
// Valuate the "Epoch" attribute with the value passed as input

	piSpecAttrAccessOnEpoch -> SetString(piKeyEpoch, epoch);
	
	piSpecAttrAccessOnEpoch -> Release();
	piKeyEpoch -> Release();
		
  return S_OK;
}

HRESULT CAAEOsmBiogNovel::GetDomain (CATUnicodeString *pDomain)
{
    cout << "Starting GetDomain" << endl << flush;

// Retrieve the attribute keys

	CATISpecAttrAccess *piSpecAttrAccessOnDomain = NULL;
	HRESULT rc = this -> QueryInterface(IID_CATISpecAttrAccess,
		                                (void**) &piSpecAttrAccessOnDomain);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for CAAOsmBiographicalNovel" << endl << flush;
		return E_FAIL;
	}
 
	CATISpecAttrKey *piKeyDomain = piSpecAttrAccessOnDomain -> 
		GetAttrKey("Domain");
	if (NULL == piKeyDomain)
	{
		cout << "ERROR in retrieving Domain key" << endl << flush;
		return E_FAIL;
	}
	
// Retrieve the value of the "Domain" attribute

	*pDomain = piSpecAttrAccessOnDomain -> GetString(piKeyDomain);

	piSpecAttrAccessOnDomain -> Release();
	piKeyDomain -> Release();
		
  return S_OK;
}

HRESULT CAAEOsmBiogNovel::SetDomain (const CATUnicodeString domain)
{
    cout << "Starting SetDomain" << endl << flush;

// Retrieve the attribute keys

	CATISpecAttrAccess *piSpecAttrAccessOnDomain = NULL;
	HRESULT rc = this -> QueryInterface(IID_CATISpecAttrAccess,
		                                (void**) &piSpecAttrAccessOnDomain);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for CAAOsmBiographicalNovel" << endl << flush;
		return E_FAIL;
	}
 
	CATISpecAttrKey *piKeyDomain = piSpecAttrAccessOnDomain -> 
		GetAttrKey("Domain");
	if (NULL == piKeyDomain)
	{
		cout << "ERROR in retrieving Domain key" << endl << flush;
		return E_FAIL;
	}
	
// Valuate the "Domain" attribute with the value passed as input

	piSpecAttrAccessOnDomain -> SetString(piKeyDomain, domain);
	
	piSpecAttrAccessOnDomain -> Release();
	piKeyDomain -> Release();
		
  return S_OK;
}
