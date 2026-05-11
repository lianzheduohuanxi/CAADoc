/**
 * @quickReview BAG 04:02:25
 * @quickReview sqa 04:01:09
 * @quickReview JDE 03:02:20
 */
// Copyright © 1994-2000 Dassault Systèmes.
// All right reserved


// ObjectSpecsModeler Framework	

// Local Framework
#include "CAAPriECCPProp.h"                    

#include "CATLISTV_CATISpecObject.h"          // needed to manage the sketch associated
                                              // to the profile

// ObjectSpecsModeler Framework
#include "CATISpecAttrAccess.h"								// needed to access Userpad attributes
#include "CATISpecAttrKey.h"									// needed to access Userpad attribute keys

// PartInterfaces Framework
#include "CATIPrtProfile.h"                   // needed to manage the profile of the 
                                              // the User Pad


// To declare that the class 
// is a DataExtension of (late type) CAAPriUserPad
CATImplementClass(CAAPriECCPProp, 
                  DataExtension, 
                  CATIShapeFeatureProperties, 
                  CAAPriUserPad);

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIShapeFeatureProperties, CAAPriECCPProp);

// To declare that UserPad implements CATIShapeFeatureProperties, insert 
// the following line in the interface dictionary:
//
// CAAPriUserPad CATIShapeFeatureProperties  libCAAPriCutCopyPaste

//-----------------------------------------------------------------------------
// CAAPriECCPProp : constructor
//-----------------------------------------------------------------------------
CAAPriECCPProp::CAAPriECCPProp():CATMmrShapeFeaturePropertiesAdapter()
{
}

//-----------------------------------------------------------------------------
// CAAPriECCPProp : destructor
//-----------------------------------------------------------------------------
CAAPriECCPProp::~CAAPriECCPProp()
{
}

//-------------------------------------------------------------------------
CATUnicodeString CAAPriECCPProp::GetPolarity ( )
{
  CATUnicodeString PrtAdd("Add");
  return PrtAdd;
}

//-------------------------------------------------------------------------

CATLISTV(CATISpecObject_var) CAAPriECCPProp::GiveMeYourFavoriteSketches()
{
	
  // Retrieves the Profile attribute of the UserPad feature.
  //
 
  CATLISTV(CATISpecObject_var) listSpec;

  CATISpecObject * piUserPad = NULL;
  HRESULT rc = QueryInterface( IID_CATISpecObject , ( void** ) &piUserPad );
  if( FAILED(rc) )
    return listSpec;

  CATISpecAttrAccess * piSpecAttrAccessOnUserPad = NULL; 
	rc = piUserPad->QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnUserPad);
		
	if ( SUCCEEDED(rc) ) 
	{ 
		// Gets a pointer on the Profile attribute key
		CATISpecAttrKey * piSpecAttrKeyOnProfile = NULL;    
		piSpecAttrKeyOnProfile = piSpecAttrAccessOnUserPad->GetAttrKey("Profile");
		
		if ( NULL != piSpecAttrKeyOnProfile )
		{
			
			CATISpecObject_var spProfile = piSpecAttrAccessOnUserPad->GetSpecObject(piSpecAttrKeyOnProfile);
			piSpecAttrKeyOnProfile->Release();
			piSpecAttrKeyOnProfile = NULL ;
			if(NULL_var != spProfile)
			{
				spProfile->Release();
				
				// Retrieves the sketch associated with the profile
				// The sketch is added in the returned list
				//
				CATIPrtProfile_var spPrtProfileOnProfile(spProfile);
				if (NULL_var != spPrtProfileOnProfile)
				{
					CATISpecObject_var spElt = NULL_var;
					spPrtProfileOnProfile->GetElement(1, spElt);
					if (NULL_var != spElt)
					{
						listSpec.Append(spElt);
					}
				}
			}
		}

		piSpecAttrAccessOnUserPad->Release();
		piSpecAttrAccessOnUserPad = NULL;

	}

	piUserPad->Release();
	piUserPad = NULL;
  return listSpec;
}
