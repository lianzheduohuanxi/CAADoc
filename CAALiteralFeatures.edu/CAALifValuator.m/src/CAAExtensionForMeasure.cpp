//COPYRIGHT DASSAULT SYSTEMES  1994 2000
// =============================================================================
//
// ABSTRACT
// --------
// Implements the necessary interfaces for building a feature that 
// valuates a parameter as output.
//
// =============================================================================
//  Usage:
//  ------
//		In Show() implement the way the output parameter is seen through the 
//	knowledgeware editors.
//		In Build() implement the valuation of the otput parameter in function
// of the input one.
//   
// 	
//===========================================================================
//  Inheritance:
//  ------------
//         CATParmValuatorAdapter
//
//===========================================================================
//  Main Method:
//  ------------
//				None
//
//===========================================================================


#include "CAAExtensionForMeasure.h"

//ObjectModeler

#include "CATISpecObject.h"

#include "CATIBuild.h"
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"

#include "CATIContainer.h"

//LiteralFeatures
#include "CATICkeType.h"
#include "CATParmValuatorAdapter.h"
#include "CATICkeParm.h"


#include "iostream.h"

CATImplementClass(CAAExtensionForMeasure,DataExtension,CATBaseUnknown,CAALifFeature);

#include <TIE_CATIParmValuator.h>
TIE_CATIParmValuator(CAAExtensionForMeasure);


#include <TIE_CATIBuild.h>
TIE_CATIBuild(CAAExtensionForMeasure);


CAAExtensionForMeasure::CAAExtensionForMeasure():CATParmValuatorAdapter()
{
}

CAAExtensionForMeasure::CAAExtensionForMeasure(const CAAExtensionForMeasure &e)
{
}

CAAExtensionForMeasure::~CAAExtensionForMeasure()
{	
}


// Method used to show in Knowledge Explorer what is valuating a given parameter
CATUnicodeString  CAAExtensionForMeasure::Show () const      
{
	CATUnicodeString us ("CAA feature valuated by ");
	CATISpecObject_var name((CAAExtensionForMeasure*) this);
	us.Append(name->GetDisplayName());
	return us;
}


HRESULT CAAExtensionForMeasure::Build()
{
	// Get the parameters and compute the output parameter in function of the
	// input.
	cout << " In Build ... " << endl;

	//First I get my input parameter.
	CATICkeParm* piInParam = NULL;	
	CATICkeParm* piOutParam = NULL;


	// Gets the InAttribute
	CATISpecAttrAccess * piSpecAttrAccessOnIn = NULL; 
	HRESULT rc = QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnIn);
	if ( SUCCEEDED(rc) ) 
	{ 
		if (NULL != piSpecAttrAccessOnIn)
		{
			// Gets a pointer on the in attribute
			CATISpecAttrKey * piSpecAttrKeyOnIn = NULL;    
			piSpecAttrKeyOnIn = piSpecAttrAccessOnIn->GetAttrKey("InAttribute");

			if ( NULL != piSpecAttrKeyOnIn )
			{
				CATISpecObject* piInSpec = piSpecAttrAccessOnIn->GetSpecObject(piSpecAttrKeyOnIn);
				piSpecAttrKeyOnIn->Release();
				piSpecAttrKeyOnIn = NULL;

				if( piInSpec != NULL) 
				{ 
					HRESULT rc = piInSpec-> QueryInterface(IID_CATICkeParm,(void**) &piInParam);	 
					piInSpec->Release();
					piInSpec = NULL;
				}

			}
			piSpecAttrAccessOnIn->Release();
			piSpecAttrAccessOnIn = NULL;
		}
	}

	// Gets the OutAttribute
	CATISpecAttrAccess * piSpecAttrAccessOnOut = NULL; 
	rc = QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnOut);
	if ( SUCCEEDED(rc) ) 
	{ 
		if (NULL != piSpecAttrAccessOnOut)
		{
			// Gets a pointer on the in attribute
			CATISpecAttrKey * piSpecAttrKeyOnOut = NULL;    
			piSpecAttrKeyOnOut = piSpecAttrAccessOnOut->GetAttrKey("OutAttribute");

			if ( NULL != piSpecAttrKeyOnOut )
			{
				CATISpecObject* piOutSpec = piSpecAttrAccessOnOut->GetSpecObject(piSpecAttrKeyOnOut);
				piSpecAttrKeyOnOut->Release();
				piSpecAttrKeyOnOut = NULL;

				if( piOutSpec != NULL) 
				{ 
					HRESULT rc = piOutSpec-> QueryInterface(IID_CATICkeParm,(void**) &piOutParam);	 
					piOutSpec->Release();
					piOutSpec = NULL;
				}

			}
			piSpecAttrAccessOnOut->Release();
			piSpecAttrAccessOnOut = NULL;
		}
	}

	if( NULL != piInParam && NULL != piOutParam )
	{
		int in = piOutParam->Value()->AsInteger();

		if( in%2 )
		{
			cout << "Value if the input parameter: " << in <<  " = odd parameter " << in%2 << endl;
			piOutParam->Valuate(99);
		}
		else
		{
			cout << "Value if the input parameter: " << in <<  " = even paramater " << in%2 << endl;		
			piOutParam->Valuate(100);
		}
		piInParam->Release();
		piInParam = NULL;
		piOutParam->Release();
		piOutParam = NULL;
	}
	else
	{
		cout << " Unable to access in or out parameters " << endl;
	}

	return S_OK;
}
