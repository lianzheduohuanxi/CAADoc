// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAEPstINFLine.h"


// ObjectSpecsModeler Framework
#include "CATISpecObject.h"     // needed to manage/query features
#include "CATISpecAttrAccess.h" // needed to manage/query feature attributes
#include "CATISpecAttrKey.h"    // needed to retrieve the attribute key    

// Others
#include "iostream.h"

// Tie the implementation to its interface.
#include "TIE_CAAIPstINFLine.h"
TIE_CAAIPstINFLine(CAAEPstINFLine);

// To declare that the class is a data extension of CAAPstINFLine
//
CATImplementClass (CAAEPstINFLine,
                   DataExtension,    
                   CATBaseUnknown,
                   CAAPstINFLine);

// 
// To declare that CAAEPstINFLine implements CAAIPstINFLine for the CAAPstINFLine
// component, insert the following line in the interface dictionary:
//
//    CAAPstINFLine CAAIPstINFLine  libCAAINFModeler
//

//-------------------------------------------------------------------------------------
// CAAEPstINFLine : constructor
//-------------------------------------------------------------------------------------
CAAEPstINFLine::CAAEPstINFLine():
CATBaseUnknown()
{
    
}

//-------------------------------------------------------------------------------------
// CAAEPstINFPoint : destructor
//-------------------------------------------------------------------------------------
CAAEPstINFLine::~CAAEPstINFLine()
{
    
}

//-------------------------------------------------------------------------------------
// Implements CAAIPstINFLine::GetPoint
//-------------------------------------------------------------------------------------

HRESULT CAAEPstINFLine::GetPoint(int iNum, CATISpecObject **piPoint) 
{
	cout << "******CAAEPstINFLine::GetPoint" << endl;

    CATISpecAttrAccess *piSpecAttrAccessOnLine = NULL;
	HRESULT rc = QueryInterface (IID_CATISpecAttrAccess,
		                         (void**) &piSpecAttrAccessOnLine);
	if (FAILED(rc)) return E_FAIL;

	CATUnicodeString keyName;
	if (1 == iNum) keyName = "Point1";
	else keyName = "Point2";

	CATISpecAttrKey *piPointKey = piSpecAttrAccessOnLine -> GetAttrKey (keyName);
	if (NULL == piPointKey)
	{
		piSpecAttrAccessOnLine -> Release();
        piSpecAttrAccessOnLine = NULL;
		return E_FAIL;
	}
	
	*piPoint = piSpecAttrAccessOnLine -> GetSpecObject(piPointKey);
	
	piSpecAttrAccessOnLine -> Release();
    piSpecAttrAccessOnLine = NULL;

	piPointKey -> Release();
	piPointKey = NULL;
   
	if (NULL != piPoint) return S_OK;
	else return E_FAIL;
}


//-------------------------------------------------------------------------------------
// Implements CAAIPstINFLine::SetPoint
//-------------------------------------------------------------------------------------

HRESULT CAAEPstINFLine::SetPoint(int iNum, CATISpecObject *piPoint)
{
	cout << "******CAAEPstINFLine::SetPoint" << endl;

	CATISpecAttrAccess *piSpecAttrAccessOnLine = NULL;
	HRESULT rc = QueryInterface (IID_CATISpecAttrAccess,
		                         (void**) &piSpecAttrAccessOnLine);
	if (FAILED(rc)) return E_FAIL;

	CATUnicodeString keyName;
	if (1 == iNum) keyName = "Point1";
	else keyName = "Point2";

	CATISpecAttrKey *piPointKey = piSpecAttrAccessOnLine -> GetAttrKey (keyName);
	if (NULL == piPointKey) 
	{
	    piSpecAttrAccessOnLine -> Release();
        piSpecAttrAccessOnLine = NULL;	
		return E_FAIL;
    }
		
	piSpecAttrAccessOnLine -> SetSpecObject(piPointKey, piPoint);
	
	piSpecAttrAccessOnLine -> Release();
    piSpecAttrAccessOnLine = NULL;

	piPointKey -> Release();
	piPointKey = NULL;
   
    return S_OK;
}

