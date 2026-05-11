// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAEPstINFPoint.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"     // needed to manage/query features
#include "CATISpecAttrAccess.h" // needed to manage/query feature attributes
#include "CATISpecAttrKey.h"    // needed to retrieve the attribute key  

// Others
#include "iostream.h"
 
//-----------------------------------------------------------------------------
// Tie the implementation to its interface.
#include "TIE_CAAIPstINFPoint.h"
TIE_CAAIPstINFPoint(CAAEPstINFPoint);

// To declare that the class is a data extension of CAAPstINFPoint
//
CATImplementClass (CAAEPstINFPoint,
                   DataExtension,    
                   CATBaseUnknown,
                   CAAPstINFPoint);

// 
// To declare that CAAEPstINFPoint implements CAAIPstINFPoint for the CAAPstINFPoint
// component, insert the following line in the interface dictionary:
//
//    CAAPstINFPoint CAAIPstINFPoint  libCAAINFModeler
//

//-------------------------------------------------------------------------------------
// CAAEPstINFPoint : constructor
//-------------------------------------------------------------------------------------
CAAEPstINFPoint::CAAEPstINFPoint():
CATBaseUnknown()
{ 
	cout << "******CAAEPstINFPoint::CAAEPstINFPoint" << endl;
}

//-------------------------------------------------------------------------------------
// CAAEPstINFPoint : destructor
//-------------------------------------------------------------------------------------
CAAEPstINFPoint::~CAAEPstINFPoint()
{
	cout << "******CAAEPstINFPoint::~CAAEPstINFPoint" << endl;
}

//-------------------------------------------------------------------------------------
// Implements CAAIPstINFPoint::GetX
//-------------------------------------------------------------------------------------

HRESULT CAAEPstINFPoint::GetX(double *pX) 
{
	cout << "******CAAEPstINFPoint::GetX" << endl;
 
	CATISpecAttrAccess *piSpecAttrAccessOnPoint = NULL;
	HRESULT rc = QueryInterface (IID_CATISpecAttrAccess,
		                         (void**) &piSpecAttrAccessOnPoint);
	if (FAILED(rc))	return E_FAIL;

	CATISpecAttrKey *piXKey = piSpecAttrAccessOnPoint -> GetAttrKey ("X");
	if (NULL == piXKey) 
	{
		piSpecAttrAccessOnPoint -> Release();
        piSpecAttrAccessOnPoint = NULL;
        return E_FAIL;
	}
	
	*pX = piSpecAttrAccessOnPoint -> GetDouble(piXKey);

    piSpecAttrAccessOnPoint -> Release();
    piSpecAttrAccessOnPoint = NULL;

	piXKey -> Release();
	piXKey = NULL;
   
    return S_OK;
}

//-------------------------------------------------------------------------------------
// Implements CAAIPstINFPoint::GetY
//-------------------------------------------------------------------------------------

HRESULT CAAEPstINFPoint::GetY(double *pY ) 
{
	cout << "******CAAEPstINFPoint::GetY" << endl;

    CATISpecAttrAccess *piSpecAttrAccessOnPoint = NULL;
	HRESULT rc = QueryInterface (IID_CATISpecAttrAccess,
		                         (void**) &piSpecAttrAccessOnPoint);
	if (FAILED(rc)) return E_FAIL;

	CATISpecAttrKey *piYKey = piSpecAttrAccessOnPoint -> GetAttrKey ("Y");
	if (NULL == piYKey) 
	{
		piSpecAttrAccessOnPoint -> Release();
        piSpecAttrAccessOnPoint = NULL;
		return E_FAIL;
    }
	
	*pY = piSpecAttrAccessOnPoint -> GetDouble(piYKey); 

    piSpecAttrAccessOnPoint -> Release();
    piSpecAttrAccessOnPoint = NULL;

	piYKey -> Release();
	piYKey = NULL;
   
    return S_OK;
}

//-------------------------------------------------------------------------------------
// Implements CAAIPstINFPoint::GetZ
//-------------------------------------------------------------------------------------

HRESULT CAAEPstINFPoint::GetZ(double *pZ ) 
{
	cout << "******CAAEPstINFPoint::GetZ" << endl;
    
	CATISpecAttrAccess *piSpecAttrAccessOnPoint = NULL;
	HRESULT rc = QueryInterface (IID_CATISpecAttrAccess,
		                         (void**) &piSpecAttrAccessOnPoint);
	if (FAILED(rc)) return E_FAIL;

	CATISpecAttrKey *piZKey = piSpecAttrAccessOnPoint -> GetAttrKey ("Z");
	if (NULL == piZKey)
	{
		piSpecAttrAccessOnPoint -> Release();
        piSpecAttrAccessOnPoint = NULL;
		return E_FAIL;
    }
	
	*pZ = piSpecAttrAccessOnPoint -> GetDouble(piZKey); 

    piSpecAttrAccessOnPoint -> Release();
    piSpecAttrAccessOnPoint = NULL;

	piZKey -> Release();
	piZKey = NULL;
   
    return S_OK;
}

//-------------------------------------------------------------------------------------
// Implements CAAIPstINFPoint::SetX
//-------------------------------------------------------------------------------------

HRESULT CAAEPstINFPoint::SetX(double iX)
{
	cout << "******CAAEPstINFPoint::SetX" << endl;
	
	CATISpecAttrAccess *piSpecAttrAccessOnPoint = NULL;
	HRESULT rc = QueryInterface (IID_CATISpecAttrAccess,
		                         (void**) &piSpecAttrAccessOnPoint);
	if (FAILED(rc)) return E_FAIL;

	CATISpecAttrKey *piXKey = piSpecAttrAccessOnPoint -> GetAttrKey ("X");
	if (NULL == piXKey)
	{
		piSpecAttrAccessOnPoint -> Release();
        piSpecAttrAccessOnPoint = NULL;
		return E_FAIL;
    }
	
	piSpecAttrAccessOnPoint -> SetDouble( piXKey, iX );

    piSpecAttrAccessOnPoint -> Release();
	piSpecAttrAccessOnPoint = NULL;

	piXKey -> Release();
	piXKey = NULL;

	return S_OK;
}

//-------------------------------------------------------------------------------------
// Implements CAAIPstINFPoint::SetY
//-------------------------------------------------------------------------------------

HRESULT CAAEPstINFPoint::SetY(double iY)
{
	cout << "******CAAEPstINFPoint::SetY" << endl;
	
	CATISpecAttrAccess *piSpecAttrAccessOnPoint = NULL;
	HRESULT rc = QueryInterface (IID_CATISpecAttrAccess,
		                         (void**) &piSpecAttrAccessOnPoint);
	if (FAILED(rc)) return E_FAIL;

	CATISpecAttrKey *piYKey = piSpecAttrAccessOnPoint -> GetAttrKey ("Y");
	if (NULL == piYKey)
	{
		piSpecAttrAccessOnPoint -> Release();
        piSpecAttrAccessOnPoint = NULL;
		return E_FAIL;
    }
	
	piSpecAttrAccessOnPoint -> SetDouble( piYKey, iY );

    piSpecAttrAccessOnPoint -> Release();
	piSpecAttrAccessOnPoint = NULL;

	piYKey -> Release();
	piYKey = NULL;

	return S_OK;
}

//-------------------------------------------------------------------------------------
// Implements CAAIPstINFPoint::SetZ
//-------------------------------------------------------------------------------------

HRESULT CAAEPstINFPoint::SetZ(double iZ)
{
	cout << "******CAAEPstINFPoint::SetZ" << endl;

	CATISpecAttrAccess *piSpecAttrAccessOnPoint = NULL;
	HRESULT rc = QueryInterface (IID_CATISpecAttrAccess,
		                         (void**) &piSpecAttrAccessOnPoint);
	if (FAILED(rc)) return E_FAIL;

	CATISpecAttrKey *piZKey = piSpecAttrAccessOnPoint -> GetAttrKey ("Z");
	if (NULL == piZKey)
	{
		piSpecAttrAccessOnPoint -> Release();
        piSpecAttrAccessOnPoint = NULL;
		return E_FAIL;
    }
	
	piSpecAttrAccessOnPoint -> SetDouble( piZKey, iZ );

    piSpecAttrAccessOnPoint -> Release();
	piSpecAttrAccessOnPoint = NULL;

	piZKey -> Release();
	piZKey = NULL;

	return S_OK;
}
