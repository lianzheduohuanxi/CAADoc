// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAEMaiUserDataFeature:
//
// Sample code for : Prismatic Machining Programmer
// Mission         : Provide an editor to a User Data Feature
//
//
// Type            : Interactive functionality
//
// Illustrates     : 1- sample of coding an editor of a User Data Feature
//                   2- provide an implementation of CATIMfgUserDataFeature interface
//                 
// The late type of the User Data Feature is MyUserDataFeature
// It has one attribute, MyAttribute, that is modelized as a Literal Feature 
//
//=============================================================================

#include "CAAEMaiUserDataFeature.h"

// Object Specs Modeler
#include "CATISpecObject.h"
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"

// Literal Features
#include "CATICkeParamFrame.h"
 
CATImplementClass(CAAEMaiUserDataFeature, DataExtension, CATBaseUnknown, MyUserDataFeature);

#include "TIE_CATIMfgUserDataFeature.h"
TIEchain_CATIMfgUserDataFeature(CAAEMaiUserDataFeature);

//========================================================================
// Constructor
//========================================================================

CAAEMaiUserDataFeature::CAAEMaiUserDataFeature ()
{
}

//========================================================================
// Destructor
//========================================================================

CAAEMaiUserDataFeature::~CAAEMaiUserDataFeature ()
{
}

//========================================================================
// GetEditor
//========================================================================

HRESULT CAAEMaiUserDataFeature::GetEditor (CATDialog *iFather,CATDlgFrame* &oEditor)
{
	HRESULT RC = S_OK;

	// Creates a Frame
	oEditor = new CATDlgFrame (iFather,CATString("Parameter 1"));

	// Retrieves the attribute 'MyAttribute'
	CATISpecAttrAccess_var SpecAccess(this);
	if (NULL_var != SpecAccess)
	{
		CATISpecAttrKey * pAttribute = SpecAccess->GetAttrKey("MyAttribute");
		if (NULL != pAttribute)
		{
			CATISpecObject * pSpecObject = SpecAccess->GetSpecObject(pAttribute);
			if(pSpecObject != NULL)
			{
				// Retrieves the Literal Feature
				CATICkeParamFrame_var ParmFrame(pSpecObject);
				if (NULL_var != ParmFrame)
				{
					// Builds its editor
					CATDlgFrame * pTheFrame = ParmFrame->GetInPanelEdition (NULL_var, oEditor, CATCkeWithSpinner|CATCkeNoLabel);
				}

				pSpecObject->Release();
				pSpecObject = NULL;
			}

			pAttribute->Release();
			pAttribute = NULL;    
		}
	}

	return (RC);
}

//========================================================================
// GetNLSDescription
//========================================================================

HRESULT CAAEMaiUserDataFeature::GetNLSDescription (CATUnicodeString &oNLSDescription)
{
  HRESULT RC = S_OK;

// Builds the string that will appear in the menu item

  oNLSDescription = CATUnicodeString("Standards..."); 

  return (RC);
}

