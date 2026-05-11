// COPYRIGHT DASSAULT SYSTEMES 2000
//
// Implementation of CATIBuild for "CAAOsmAdd" feature  

// ObjectSpecsModeler Framework
#include "CATISpecAttrAccess.h"     // GetAttrKey, GetInteger, SetInteger
#include "CATISpecAttrKey.h"        // Result of GetAttrKey

// Other
#include "CAAOsmAddOp.h"               
#include "iostream.h"

#include "TIE_CATIBuild.h"
TIE_CATIBuild(CAAOsmAddOp);

CATImplementClass(CAAOsmAddOp, 
				  DataExtension,
                  CATBaseUnknown,
				  CAAOsmAdd);

HRESULT CAAOsmAddOp::Build()
{
    cout << "Starting CAAOsmAdd Build" << endl << flush;

// Retrieve the attribute keys

	CATISpecAttrAccess *piSpecAttrAccessOnAdd = NULL;
	HRESULT rc = this -> QueryInterface(IID_CATISpecAttrAccess,
		                                (void**) &piSpecAttrAccessOnAdd);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for CAAOsmAdd" << endl << flush;
		return 1;
	}
 
	CATISpecAttrKey *piKeyFirst = piSpecAttrAccessOnAdd -> 
		GetAttrKey("First");
	if (NULL == piKeyFirst)
	{
		cout << "ERROR in retrieving First key" << endl << flush;
		return 2;
	}

	CATISpecAttrKey *piKeySecond = piSpecAttrAccessOnAdd ->
		GetAttrKey("Second");
	if (NULL == piKeySecond)
	{
		cout << "ERROR in retrieving Second key" << endl << flush;
		return 2;
	}

	CATISpecAttrKey *piKeySum = piSpecAttrAccessOnAdd -> 
		GetAttrKey("Sum");
	if (NULL == piKeySum)
	{
		cout << "ERROR in retrieving Sum key" << endl << flush;
		return 2;
	}
	
// Retrieve the values of the attributes "First" and "Second" and calculate and
// store "Sum"

	int f = 0;
	int s = 0;
	f = piSpecAttrAccessOnAdd -> GetInteger(piKeyFirst);
	s = piSpecAttrAccessOnAdd -> GetInteger(piKeySecond);
	piSpecAttrAccessOnAdd -> SetInteger(piKeySum, f+s);
	int printVal = 0;
	printVal = piSpecAttrAccessOnAdd -> GetInteger(piKeySum);
	cout << "The value of sum is " << printVal << endl << flush;

	piSpecAttrAccessOnAdd -> Release();
	piKeyFirst -> Release();
	piKeySecond -> Release();
	piKeySum -> Release();
	
  return 0;
 }
