// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAEPstINFWire.h"


// ObjectSpecsModeler Framework
#include "CATISpecObject.h"     // needed to manage/query features
#include "CATISpecAttrAccess.h" // needed to manage/query feature attributes
#include "CATISpecAttrKey.h"    // needed to retrieve the attribute key    

// Others
#include "iostream.h"

// Tie the implementation to its interface.
#include "TIE_CAAIPstINFWire.h"
TIE_CAAIPstINFWire(CAAEPstINFWire);

// To declare that the class is a data extension of CAAPstINFWire
//
CATImplementClass (CAAEPstINFWire,
                   DataExtension,    
                   CATBaseUnknown,
                   CAAPstINFWire);

// 
// To declare that CAAEPstINFWire implements CAAIPstINFWire for the CAAPstINFWire
// component, insert the following Wire in the interface dictionary:
//
//    CAAPstINFWire CAAIPstINFWire  libCAAPstINFModeler
//

//-------------------------------------------------------------------------------------
// CAAEPstINFWire : constructor
//-------------------------------------------------------------------------------------
CAAEPstINFWire::CAAEPstINFWire():
CATBaseUnknown()
{
    
}

//-------------------------------------------------------------------------------------
// CAAEPstINFPoint : destructor
//-------------------------------------------------------------------------------------
CAAEPstINFWire::~CAAEPstINFWire()
{
    
}

//-------------------------------------------------------------------------------------
// Implements CAAIPstINFWire::GetPoints
//-------------------------------------------------------------------------------------

HRESULT CAAEPstINFWire::GetPoints(CATListPtrCATISpecObject **pPointList) 
{
    cout << "******CAAEPstINFWire::GetPoints" << endl;

    if (NULL == pPointList) return E_FAIL;

    CATISpecAttrAccess *piSpecAttrAccessOnWire = NULL;
    HRESULT rc = QueryInterface (IID_CATISpecAttrAccess,
		                         (void**) &piSpecAttrAccessOnWire);
    
    if (FAILED(rc)) return E_FAIL;

    // Retrieve the key to the feature's "Points" attribute
    CATUnicodeString keyName = "Points";
    CATISpecAttrKey *piPointKey = piSpecAttrAccessOnWire -> GetAttrKey (keyName);
    if (NULL == piPointKey)
    {
	piSpecAttrAccessOnWire -> Release();
        piSpecAttrAccessOnWire = NULL;
	return E_FAIL;
    }
	
    // Scan through the list of features referenced by the attribute,
    // retrieve each feature and append it to the list to be returned to the caller.
    *pPointList = new CATListPtrCATISpecObject();

    CATISpecObject *piPoint = NULL;
    int n = piSpecAttrAccessOnWire -> GetListSize(piPointKey);

    for (int i = 1; i <= n; i++)
    {
        piPoint = piSpecAttrAccessOnWire -> GetSpecObject(piPointKey, i);	
	    (*pPointList) -> Append(piPoint);
	    piPoint = NULL;
    }

    piSpecAttrAccessOnWire -> Release();
    piSpecAttrAccessOnWire = NULL;

    piPointKey -> Release();
    piPointKey = NULL;
   
   
    return S_OK;
}


//-------------------------------------------------------------------------------------
// Implements CAAIPstINFWire::SetPoint
//-------------------------------------------------------------------------------------

HRESULT CAAEPstINFWire::SetPoints(CATListPtrCATISpecObject *pPointList)
{
    cout << "******CAAEPstINFWire::SetPoints" << endl;

    if (NULL == pPointList) return E_FAIL;
   
    CATISpecAttrAccess *piSpecAttrAccessOnWire = NULL;
    HRESULT rc = QueryInterface (IID_CATISpecAttrAccess,
		                         (void**) &piSpecAttrAccessOnWire);
    if (FAILED(rc))	return E_FAIL;

    // Retrieve the key to the feature's "Points" attribute
    CATUnicodeString keyName = "Points";
    CATISpecAttrKey *piPointKey = piSpecAttrAccessOnWire -> GetAttrKey (keyName);
    if (NULL == piPointKey) 
    {
	    piSpecAttrAccessOnWire -> Release();
        piSpecAttrAccessOnWire = NULL;	
    	return E_FAIL;
    }

	// If the list of attributes is already valuated, initialize it to NULL in order
	// to entirely re-create it.
    int nb = piSpecAttrAccessOnWire->GetListSize(piPointKey);
    if ( 0 != nb )
    {
       piSpecAttrAccessOnWire -> UnsetAttributeValue(piPointKey);
    }   

    // Scan through the list of features passed in the argument,
    // retrieve each feature from the list and save it in the list of feature
    // referenced by the "Points" attribute.
    CATISpecObject *piPoint = NULL;
    for(int i=1;i<=pPointList->Size();i++)
    {
	    piPoint = (*pPointList)[i] ;
	    piSpecAttrAccessOnWire -> SetSpecObject(piPointKey, piPoint, 0);
	    piPoint = NULL;
    }
	piSpecAttrAccessOnWire -> Release();
    piSpecAttrAccessOnWire = NULL;

    piPointKey -> Release();
    piPointKey = NULL;
   

    return S_OK;
}

