// COPYRIGHT DASSAULT SYSTEMES 2000
//
// Implementation of CATIBuild for "CAAOsmSquare"  

// ObjectSpecsModeler Framework
#include "CATISpecAttrAccess.h"     // GetAttrKey, GetInteger, SetInteger
#include "CATISpecAttrKey.h"        // Result of GetAttrKey

// Other
#include "CAAOsmSquareOp.h" 
#include "iostream.h"

#include "TIE_CATIBuild.h"
TIE_CATIBuild(CAAOsmSquareOp);

CATImplementClass(CAAOsmSquareOp,
				  DataExtension,
                  CATBaseUnknown,
				  CAAOsmSquare);

HRESULT CAAOsmSquareOp::Build()
{
  cout << "Starting CAAOsmSquare Build" << endl;

  // Retrieve the attribute keys

	CATISpecAttrAccess *piSpecAttrAccessOnSquare = NULL;
	HRESULT rc = this -> QueryInterface(IID_CATISpecAttrAccess,
		                                (void**) &piSpecAttrAccessOnSquare);
	if (FAILED(rc))
	{
		cout << "ERROR in QueryInterface on CATISpecAttrAccess for CAAOsmSquare" << endl << flush;
		return 1;
	}
 
	CATISpecAttrKey *piKeyNum = piSpecAttrAccessOnSquare ->
		GetAttrKey("Num");
	if (NULL == piKeyNum)
	{
		cout << "ERROR in retrieving Num key" << endl << flush;
		return 2;
	}

	CATISpecAttrKey *piKeySquare = piSpecAttrAccessOnSquare -> 
		GetAttrKey("Square");
	if (NULL == piKeySquare)
	{
		cout << "ERROR in retrieving Square key" << endl << flush;
		return 2;
	}

// Retrieve the values of the attribute "Num", calculate its square and
// store in "Square"

	int val = 0;
	val = piSpecAttrAccessOnSquare -> GetInteger(piKeyNum);
	piSpecAttrAccessOnSquare -> SetInteger(piKeySquare, val*val);

	int printVal = 0;
	printVal = piSpecAttrAccessOnSquare -> GetInteger(piKeySquare);
	cout << "The value of Square is " << printVal << endl << flush;
	
	piSpecAttrAccessOnSquare -> Release();
	piKeyNum -> Release();
	piKeySquare -> Release();

  return 0;
 }
