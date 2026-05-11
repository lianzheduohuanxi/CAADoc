// COPYRIGHT DASSAULT SYSTEMES 2000
//
// CATIFmFeatureBehaviorCustomization::OnBuild implementation on the "CAAOsmSquare" feature  
//
//		1- Build Client Identity as an owner of the "CAAOsmCatalogSU" Catalog 
//      2- Retrieve Keys to Attributes associated with CAAOsmSquare
//			2-1- Retrieve the key to the "Num" attribute
//			2-2- Retrieve the key to the "Square" attribute
//		3- Retrieve the value of the "Num" attribute
//			3-1- Create a facade bound to the "CAAOsmSquare" feature (this)
//			3-2- Retrieve the value of the "Num" attribute
//		4- Compute and Valuate the "Square" attribute
//			4-1- Valuate the "Square" attribute. It is the square of "Num"
//			4-2- Retrieve the value of the attribute "Square". Confirm if it is set to the new value
//
// --------------------------------------------------------------------------------------------------
#include "CAAEV5V6OsmBehaviorCustomizationSquare.h" 

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

CATImplementClass(CAAEV5V6OsmBehaviorCustomizationSquare,
				  DataExtension,
                  CATIFmFeatureBehaviorCustomization,
				  CAAOsmSquare);
CATImplementBOA(CATIFmFeatureBehaviorCustomization,CAAEV5V6OsmBehaviorCustomizationSquare); 

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAAEV5V6OsmBehaviorCustomizationSquare::CAAEV5V6OsmBehaviorCustomizationSquare()
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAAEV5V6OsmBehaviorCustomizationSquare::~CAAEV5V6OsmBehaviorCustomizationSquare()
{
}


HRESULT CAAEV5V6OsmBehaviorCustomizationSquare::Build()
{
	cout << "   Starting CAAOsmSquare::OnBuild" << endl;

	// -------------------------------------------------------------------------------------
	// 1- Create Credentials
	// -------------------------------------------------------------------------------------
	CATFmCredentials MyCredential;
	MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
    MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");

	// -------------------------------------------------------------------------------------
	// 2- Retrieve Keys to Attributes associated with "CAAOsmSquare"
	// -------------------------------------------------------------------------------------
	// 2-1- Retrieve the key to the "Num" attribute
	CATFmAttributeName SqrNumAttrKey("Num");
	// 2-2- Retrieve the key to the "Square" attribute
	CATFmAttributeName SqrSqrAttrKey("Square");

	//------------------------------------------------------------------------------
	// 3- Retrieve the "Num" attribute value of the "CAAOsmSquare" feature
	//------------------------------------------------------------------------------
	// 3-1- Create a facade bound to the "CAAOsmSquare" feature
	CATFmFeatureFacade FmFeatFacadeOnCAAEV5V6OsmBehaviorCustomizationSquare(MyCredential,this);
	// 3-2- Retrieve the value of the "Num" attribute
	CATFmAttributeValue FmAttrValue;
	int iNum = 0;
	HRESULT rc =  FmFeatFacadeOnCAAEV5V6OsmBehaviorCustomizationSquare.GetValue(SqrNumAttrKey,FmAttrValue);
	if (SUCCEEDED(rc))
		rc = FmAttrValue.GetInteger(iNum);

	//------------------------------------------------------------------------------
	// 4- Compute and Valuate the "Square" attribute
	//------------------------------------------------------------------------------
	if (SUCCEEDED(rc))
	{
		// 4-1- Valuate the "Square" attribute. It works out to "Num*Num"
		int iSqr = iNum*iNum;
		FmAttrValue.SetInteger(iSqr);
		rc =  FmFeatFacadeOnCAAEV5V6OsmBehaviorCustomizationSquare.SetValue(SqrSqrAttrKey,FmAttrValue);
		
		// 4-2- Retrieve the value of the attribute "Square". Confirm if it is set to the new value
		if (SUCCEEDED(rc))
		{
			rc =  FmFeatFacadeOnCAAEV5V6OsmBehaviorCustomizationSquare.GetValue(SqrSqrAttrKey,FmAttrValue);
			if (SUCCEEDED(rc))
			{
				int iSqrValue = 0;
				rc = FmAttrValue.GetInteger(iSqrValue);
				if (SUCCEEDED(rc))
					cout << "   The value of Square is " << iSqrValue << endl << flush;
			}
		}
	}

	return rc;
 }





