// COPYRIGHT DASSAULT SYSTEMES 2000
//
// CATIFmFeatureBehaviorCustomization::OnBuild implementation on the "CAAOsmAdd" feature  
//
//		1- Build Client Identity as an owner of the "CAAOsmCatalogSU" Catalog 
//      2- Retrieve Keys to Attributes associated with CAAOsmAdd 
//			2-1- Retrieve the key to the "First" attribute
//			2-2- Retrieve the key to the "Second" attribute
//			2-3- Retrieve the key to the "Sum" attribute
//		3- Retrieve the value of the "First" attribute
//			3-1- Create a facade bound to the "CAAOsmAdd" feature (this)
//			3-2- Retrieve the value of the "First" attribute
//		4- Retrieve the value of the "Second" attribute
//		5- Compute and Valuate the "Sum" attribute
//			5-1- Valuate the "Sum" attribute. It is the sum of "First" and "Second"
//			5-2- Retrieve the value of the attribute "Sum". Confirm if it is set to the new value
// --------------------------------------------------------------------------------------------------
#include "CAAEV5V6FmExtBehaviorCustomizationAdd.h"               

// FeatureModelerExt 
#include "CATFmFeatureFacade.h"
#include "CATFmCredentials.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATFmFeatureModelerID.h"

// System
#include "CATUnicodeString.h"

// Other
#include "iostream.h"

CATImplementClass(CAAEV5V6FmExtBehaviorCustomizationAdd, 
				  DataExtension,
                  CATIFmFeatureBehaviorCustomization,
				  CAAOsmAdd);
CATImplementBOA(CATIFmFeatureBehaviorCustomization,CAAEV5V6FmExtBehaviorCustomizationAdd); 

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAAEV5V6FmExtBehaviorCustomizationAdd::CAAEV5V6FmExtBehaviorCustomizationAdd()
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAAEV5V6FmExtBehaviorCustomizationAdd::~CAAEV5V6FmExtBehaviorCustomizationAdd()
{
}

HRESULT CAAEV5V6FmExtBehaviorCustomizationAdd::Build()
{
	cout << "   Starting CAAEV5V6FmExtBehaviorCustomizationAdd::Build" << endl << flush;

	// -------------------------------------------------------------------------------------
	// 1- Create Credentials
	// -------------------------------------------------------------------------------------
	CATFmCredentials MyCredential;
	MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
    MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");

	// -------------------------------------------------------------------------------------
	// 2- Retrieve Keys to Attributes associated with "CAAOsmAdd" feature 
	// -------------------------------------------------------------------------------------
	// 2-1- Retrieve the key to the "First" attribute
	CATFmAttributeName AddFirstAttrKey("First");
	// 2-2- Retrieve the key to the "Second" attribute
	CATFmAttributeName AddSecndAttrKey("Second");
	// 2-3- Retrieve the key to the "Sum" attribute
	CATFmAttributeName AddSumAttrKey("Sum");

	//--------------------------------------------------
	// 3- Retrieve the value of the "First" attribute
	//--------------------------------------------------
	// 3-1- Create a facade bound to the "CAAOsmAdd" feature (this)
	CATFmFeatureFacade FmFeatFacadeOnCAAEV5V6FmExtBehaviorCustomizationAdd(MyCredential,this);

	// 3-2- Retrieve the value of the "First" attribute
	int iFirstAttr = 0;
	CATFmAttributeValue FmAttrValue;
	HRESULT rc =  FmFeatFacadeOnCAAEV5V6FmExtBehaviorCustomizationAdd.GetValue(AddFirstAttrKey,FmAttrValue);
	if (SUCCEEDED(rc))
		rc = FmAttrValue.GetInteger(iFirstAttr);
	
	//--------------------------------------------------
	// 4- Retrieve the value of the "Second" attribute
	//--------------------------------------------------
	int iSecondAttr = 0;
	if (SUCCEEDED(rc))
	{
		rc =  FmFeatFacadeOnCAAEV5V6FmExtBehaviorCustomizationAdd.GetValue(AddSecndAttrKey,FmAttrValue);
		if (SUCCEEDED(rc))
			rc = FmAttrValue.GetInteger(iSecondAttr);
	}
	
	//------------------------------------------------------------------------------
	// 5- Compute and Valuate the "Sum" attribute
	//------------------------------------------------------------------------------
	if (SUCCEEDED(rc))
	{
		// 5-1- Valuate the "Sum" attribute. It is the sum of "First" and "Second"
		int iSumAttr = iFirstAttr + iSecondAttr;
		FmAttrValue.SetInteger(iSumAttr);
		rc =  FmFeatFacadeOnCAAEV5V6FmExtBehaviorCustomizationAdd.SetValue(AddSumAttrKey,FmAttrValue);
		// 5-2- Retrieve the value of the attribute "Sum". Confirm if it is set to the new value
		if (SUCCEEDED(rc))
		{
			rc =  FmFeatFacadeOnCAAEV5V6FmExtBehaviorCustomizationAdd.GetValue(AddSumAttrKey,FmAttrValue);
			if (SUCCEEDED(rc))
			{
				int iSumValue = 0;
				rc = FmAttrValue.GetInteger(iSumValue);
				if (SUCCEEDED(rc))
					cout << "   The value of Sum is " << iSumValue << endl << flush;
			}
		}
	}

	return rc;
 }




