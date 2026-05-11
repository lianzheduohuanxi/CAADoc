// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAEPstINFNavigateObjectRoot.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"

// ObjectModelerBase Framework
#include "CATLISTV_CATBaseUnknown.h"
#include "CATINavigateObject.h"

// System Framework
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h" // contains the CATListValCATUnicodeString class definition

// Others
#include "iostream.h"

// Tie the implementation to its interface
#include "TIE_CATINavigateObject.h"
TIE_CATINavigateObject(CAAEPstINFNavigateObjectRoot);

// Declares that the class is a data extension of CAAPstINFRoot. 
//
CATImplementClass(CAAEPstINFNavigateObjectRoot,
				  DataExtension,
				  CATBaseUnknown,
				  CAAPstINFRoot);
// 
// To declare that CAAEPstNavigateObject implements the CATINavigateObject 
// interface for the CAAPstINFRoot component, insert these following line
// in the interface dictionary:
//
//    CAAPstINFRoot   CATINavigateObject  libCAAPstIntegrateNewFeaturesModel
//
//
//---------------------------------------------------------------------------------------------

CAAEPstINFNavigateObjectRoot::CAAEPstINFNavigateObjectRoot()
{
  cout << "CAAEPstINFNavigateObjectRoot::CAAEPstINFNavigateObjectRoot" << endl;
}

//---------------------------------------------------------------------------------------------

CAAEPstINFNavigateObjectRoot::~CAAEPstINFNavigateObjectRoot()
{
  cout <<"CAAEPstINFNavigateObjectRoot::~CAAEPstINFNavigateObjectRoot" << endl;
}

//---------------------------------------------------------------------------------------------

CATListValCATUnicodeString * CAAEPstINFNavigateObjectRoot::GetIdentificators()
{
  cout << "***** CAAEPstINFNavigateObjectRoot: CAAEPstINFNavigateObjectRoot::GetIdentificators" << endl;

  CATListOfCATUnicodeString *pIdent = new CATListOfCATUnicodeString;

  CATISpecObject *piSpecObjectOnRoot = NULL;
  HRESULT rc = this -> QueryInterface(IID_CATISpecObject,
        			                  (void**)&piSpecObjectOnRoot);
  if (SUCCEEDED(rc))
  {
	  // Retrieve the root's name
      CATUnicodeString rootId = piSpecObjectOnRoot -> GetDisplayName();
      piSpecObjectOnRoot -> Release();
	  piSpecObjectOnRoot = NULL;

      // String added to the list 
      pIdent -> Append(rootId);
  }

  return pIdent;
}

//---------------------------------------------------------------------------------------------

CATListValCATBaseUnknown_var * CAAEPstINFNavigateObjectRoot::GetChildren()
{
	cout << "***** CAAEPstINFNavigateObjectRoot::GetChildren" << endl;

	CATListValCATBaseUnknown_var *pList = NULL ;
    
	CATISpecAttrAccess *piAttrAccessOnRoot = NULL;
	HRESULT rc = this -> QueryInterface(IID_CATISpecAttrAccess,
					    (void**) &piAttrAccessOnRoot);
	if (FAILED(rc)) return pList;
  
	CATISpecAttrKey *piListComponentKey = NULL;
	piListComponentKey = piAttrAccessOnRoot -> GetAttrKey ("ListOfComponents");
	if (!piListComponentKey) return pList;
  
	pList = new CATListValCATBaseUnknown_var();

	CATISpecObject *piComponent = NULL;
	int n = piAttrAccessOnRoot -> GetListSize(piListComponentKey);
	for (int i = 1; i <= n; i++) {
		piComponent = piAttrAccessOnRoot -> GetSpecObject(piListComponentKey, i);
		if (NULL == piComponent) {
			cout << "Error in in retrieving component" << endl;
			piAttrAccessOnRoot -> Release();
			piAttrAccessOnRoot = NULL;
			piListComponentKey -> Release();
			piListComponentKey = NULL;
			return pList;  
		}
		cout << "Component retrieved OK" << endl; 
		pList -> Append(piComponent);
		piComponent->Release();
		piComponent = NULL;
	}

	piAttrAccessOnRoot -> Release();
	piAttrAccessOnRoot = NULL;
	piListComponentKey -> Release();
	piListComponentKey = NULL;

	return pList;
}
		
