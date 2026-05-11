// Copyright © 1994-2000 Dassault Systèmes.
// All right reserved
/**
 * @quickReview BAG 04:02:25
 * @quickReview sqa 04:01:09
 */

// Local Framework
#include "CAAPriEShapeFeatProp.h"


// ObjectSpecsModeler Framework	
#include "CATLISTV_CATISpecObject.h"
#include "CATISpecAttrAccess.h"					 // needed to access Userpad attributes
#include "CATISpecAttrKey.h"						 // needed to access Userpad attribute keys


// PartInterfaces Framework
#include "CATIPrtProfile.h"                   // needed to manage the profile of the 
                                              // the PatternPad

// To declare that the class 
// is a DataExtension of (late type) CAAPriPatternPad
CATImplementClass(CAAPriEShapeFeatProp, 
                  DataExtension, 
                  CATBaseUnknown, 
                  CAAPriPatternPad);

#include "TIE_CATIShapeFeatureProperties.h" // needed to tie the implementation to its interface
TIE_CATIShapeFeatureProperties(CAAPriEShapeFeatProp);

// To declare that PatternPad implements CATIShapeFeatureProperties, insert 
// the following line in the interface dictionary:
//
// CAAPriPatternPad  CATIShapeFeatureProperties  libCAAPriPattern


//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
CAAPriEShapeFeatProp::CAAPriEShapeFeatProp()
{
}


//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
CAAPriEShapeFeatProp::~CAAPriEShapeFeatProp()
{
}


//-------------------------------------------------------------------------
// IsAFreeFormFeature
// This method returns 1 if the feature is a free form feature.
// The PatternPad is a free form feature.
//-------------------------------------------------------------------------
int CAAPriEShapeFeatProp::IsAFreeFormFeature()
{
	return 1;
}

//-------------------------------------------------------------------------
// IsAContextualFeature
// This method returns 0 if the feature is not a contextual feature.
// The UserPad is not a contextual feature.
//-------------------------------------------------------------------------
int CAAPriEShapeFeatProp::IsAContextualFeature ( )
{
	return 0;
}

//-------------------------------------------------------------------------
// GetPolarity
// This method returns the polarity (Add/Remove) of the feature
// The UserPad is of Add polarity
//-------------------------------------------------------------------------
CATUnicodeString CAAPriEShapeFeatProp::GetPolarity ( )
{
	CATUnicodeString str;
	return str;
}

//-------------------------------------------------------------------------
// GiveMeYourFavoriteSketches
// This method returns the sketches used to build the PatternPad.
// This method in used in Cut/Copy/Paste operations
//-------------------------------------------------------------------------	
CATLISTV(CATISpecObject_var) CAAPriEShapeFeatProp::GiveMeYourFavoriteSketches()
{
  // Retrieves the profile
  //
  CATISpecObject_var spiProfile = NULL_var;
  CATISpecObject_var spiUserPad((CATBaseUnknown*)this);
  CATLISTV(CATISpecObject_var) listSpec;

  CATISpecAttrAccess * piSpecAttrAccessOnUserPad = NULL;

	HRESULT hr = E_FAIL;
	if(NULL_var != spiUserPad)
		hr = spiUserPad->QueryInterface(IID_CATISpecAttrAccess, 
																		(void**) & piSpecAttrAccessOnUserPad);
		
	if ( SUCCEEDED(hr) ) 
	{ 
		// Gets a pointer on the Profile attribute key
		CATISpecAttrKey * piSpecAttrKeyOnProfile = NULL;    
		piSpecAttrKeyOnProfile = piSpecAttrAccessOnUserPad->GetAttrKey("Profile");
		
		if ( NULL != piSpecAttrKeyOnProfile )
		{
			spiProfile = piSpecAttrAccessOnUserPad->GetSpecObject(piSpecAttrKeyOnProfile);
			
			piSpecAttrKeyOnProfile->Release();
			piSpecAttrKeyOnProfile = NULL ;
				
			if( NULL_var != spiProfile )
				spiProfile->Release();

			// Build the list of the sketches, to return
			//
			// The UserPad is made with only one sketch
			CATIPrtProfile_var spiPrtProfileOnProfile(spiProfile);
			if (NULL_var != spiPrtProfileOnProfile)
			{
				CATISpecObject_var spiElt = NULL_var;
				spiPrtProfileOnProfile->GetElement(1, spiElt);
				if (NULL_var != spiElt)
				{
					listSpec.Append(spiElt);
				}
			}
		}

		piSpecAttrAccessOnUserPad->Release();
		piSpecAttrAccessOnUserPad = NULL;
  }

  return listSpec;
}

//-------------------------------------------------------------------------
// GiveMeYourBRepSpecifications
// This method returns an empty list, as there is no BRep specification
// for the PatternPad.
//-------------------------------------------------------------------------
CATLISTV(CATISpecObject_var) CAAPriEShapeFeatProp::GiveMeYourBRepSpecifications()
{
	CATLISTV(CATISpecObject_var) listBRep;
	return listBRep;
}

//-------------------------------------------------------------------------
// HasAnAxis
// This method returns 1 if the feature has an axis (like shaft...)
// The PatternPad has no axis
//-------------------------------------------------------------------------
int CAAPriEShapeFeatProp::HasAnAxis()
{
	return 0;
}

//-------------------------------------------------------------------------
// HasAnAxis
// This method returns 1 if the feature has an axis
// The PatternPad has no axis.
//-------------------------------------------------------------------------
int CAAPriEShapeFeatProp::HasAnAxis(CATBaseUnknown_var Elt)
{
	return 0;
}

//-------------------------------------------------------------------------
// GetBoundingPlane
// This method returns the bounding plane of the feature
// The PatternPad do not use any plane
//-------------------------------------------------------------------------
CATMathPlane CAAPriEShapeFeatProp::GetBoundingPlane(CATUnicodeString& Side)
{
	CATMathPlane plan;
	return plan;
}

//-------------------------------------------------------------------------
// CanBePatterned
// This method returns 1 if the feature can be patterned.
// The PatternPad can be patterned.
//-------------------------------------------------------------------------
int CAAPriEShapeFeatProp::CanBePatterned()
{
	return 1;
}
