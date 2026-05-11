// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// CAALifInstanceScrewExt.cpp
// Provide implementation to interface CATIInstance
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//===================================================================

#include <iostream.h>
#include "CAALifInstanceScrewExt.h"
#include "CATCkeGlobalFunctions.h"
#include "CATITypeDictionary.h"
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"
#include "CATISpecObject.h"
#include "CATICkeParm.h"
#include "CATICkeParmFactory.h"

CATImplementClass(CAALifInstanceScrewExt,DataExtension,CATBaseUnknown,CAALifFeatureScrew);

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIInstance.h"
TIEchain_CATIInstance( CAALifInstanceScrewExt);

//-----------------------------------------------------------------------------
// CAALifInstanceScrewExt : constructor
//-----------------------------------------------------------------------------
CAALifInstanceScrewExt::CAALifInstanceScrewExt():
CATKweInstanceAdapter()
{
}

//-----------------------------------------------------------------------------
// CAALifInstanceScrewExt : destructor
//-----------------------------------------------------------------------------
CAALifInstanceScrewExt::~CAALifInstanceScrewExt()
{
}

//-----------------------------------------------------------------------------
// Implements CAALifInstanceScrewExt::TypeInternal
//-----------------------------------------------------------------------------
CATIType* CAALifInstanceScrewExt::TypeInternal() const
{
	CATITypeDictionary_var dico = CATGlobalFunctions::GetTypeDictionary();
	CATIType * pTypeInDico = NULL;
	if (!!dico)
	{
		CATIType_var spTypeInDico;
		if (SUCCEEDED(dico->FindTypeSafe("Screw","DoItYourself",spTypeInDico)) && !!spTypeInDico)
			spTypeInDico->QueryInterface(IID_CATIType, (void**) &pTypeInDico);
	}  
	return pTypeInDico;
}

//-----------------------------------------------------------------------------
// Implements CAALifInstanceScrewExt::SetValueInternal
//-----------------------------------------------------------------------------
HRESULT CAALifInstanceScrewExt::SetValueInternal( const CATUnicodeString& iKey, const CATIValue_var& iValue )
{
	CATUnicodeString Str1 = "ScrewLength";
	CATUnicodeString Str2 = "ScrewHeadDiameter";
	CATUnicodeString Str3 = "ScrewStemDiameter";
	CATUnicodeString Str4 =  "CenterPoint";

	if (iKey != Str1 && iKey != Str1 && iKey != Str3 && iKey != Str4)
		return E_FAIL;

	if (!iValue)
		return E_FAIL;

	HRESULT hr = E_FAIL;

	CATISpecAttrAccess_var piSpecAttrAccess = this;
	if (!!piSpecAttrAccess)
	{
		CATISpecAttrKey * attrkey = piSpecAttrAccess->GetAttrKey(iKey);
		if (attrkey)
		{
			//In this case, the attributes are parameters
			if (iKey == Str1 || iKey == Str2 || iKey == Str3)
			{
				//we get the parameter in attribute
				CATISpecObject_var SpecParm = piSpecAttrAccess->GetSpecObject(attrkey);
				if (SpecParm != NULL_var)
				{
					SpecParm->Release();

					CATICkeParm_var Parm = SpecParm;
					if (Parm != NULL_var)
					{
						//we valuate the parameter with the value in argument
						double toto = 0.0;
						if (SUCCEEDED(iValue->AsReal(toto)))
						{
							Parm->Valuate(toto);
							hr = S_OK;
						}
					}
				}
			}
			//In this the attribute is a feature
			else if (iKey == Str4)
			{
				//we get the feature to put in the attribute
				CATBaseUnknown_var object = NULL_var;
				if (SUCCEEDED(iValue->AsObject(object)))
				{
					CATISpecObject_var newSpecObj = object;
					piSpecAttrAccess->SetSpecObject(attrkey, newSpecObj);
					hr = S_OK;
					//if attr of kind tk_component, the old value is removed and the new one is aggregated.
					//if attr of kind tk_specobject, the reference is changed, the old value stays somewhere.
				}
			}

			attrkey->Release();
			attrkey = NULL;
		}
	}
	return hr;
}

//-----------------------------------------------------------------------------
// Implements CAALifInstanceScrewExt::GetValueInternal
//-----------------------------------------------------------------------------
CATIValue* CAALifInstanceScrewExt::GetValueInternal( const CATUnicodeString& iKey )
{
	CATUnicodeString Str1 = "ScrewLength";
	CATUnicodeString Str2 = "ScrewHeadDiameter";
	CATUnicodeString Str3 = "ScrewStemDiameter";
	CATUnicodeString Str4 =  "CenterPoint";

	if (iKey != Str1 && iKey != Str1 && iKey != Str3 && iKey != Str4)
		return NULL;

	HRESULT hr = E_FAIL;
	CATIValue* returnedValue = NULL;
	CATISpecAttrAccess_var piSpecAttrAccess = this;
	if (piSpecAttrAccess != NULL_var)
	{
		CATISpecAttrKey *attrkey = piSpecAttrAccess->GetAttrKey(iKey);
		CATISpecObject_var obj = NULL_var;
		if (attrkey)
		{
			// The wanted value is a parameter
			if (iKey == Str1 || iKey == Str2 || iKey == Str3)
			{
				obj = piSpecAttrAccess->GetSpecObject(attrkey);
				if (obj != NULL_var)
				{
					obj->Release();
					obj->QueryInterface(IID_CATIValue, (void**) &returnedValue);
				}
			}
			// The wanted value is a feature point
			else if (iKey == Str4)
			{
				obj = piSpecAttrAccess->GetSpecObject(attrkey);
				if (obj != NULL_var)
				{
					obj->Release();

					CATICkeParmFactory_var VolFactory = CATCkeGlobalFunctions::GetVolatileFactory();
					if(VolFactory != NULL_var)
					{
						// Transformation of the point in a parameter and then in a CATIValue
						CATICkeParm_var parm = VolFactory->CreateObjectReference(obj);
						if(parm != NULL_var)  
							parm->QueryInterface(IID_CATIValue, (void  **)&returnedValue);
					}
				}
			}

			attrkey->Release();
			attrkey = NULL;
		}
	}

	return  returnedValue;  
}
