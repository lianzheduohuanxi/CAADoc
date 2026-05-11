// COPYRIGHT Dassault Systemes 2003
//===================================================================
// CATIA ShapeDesign And Styling  
// ------------------------------------------------------------------//
// CAAEGSMSewSkinBasic.cpp
// Provide implementation to interface
//    CAAIGSMSewSkinBasic
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//June 2006 : Creation CAA Sample 
//===================================================================

#include "CATISpecObject.h"
#include "CATISpecAttribute.h"
#include "CATISpecAttrKey.h"
#include "CATISpecAttrAccess.h"
#include "CATLISTV_CATBaseUnknown.h"

#include "CAAEGSMSewSkinBasic.h"
#include "CATIGSMAttributes.h"


CATImplementClass(CAAEGSMSewSkinBasic, CodeExtension, CATBaseUnknown, CAASewSkinBasic );



//-----------------------------------------------------------------------------
// CAAEGSMSewSkinBasic : constructor
//-----------------------------------------------------------------------------
CAAEGSMSewSkinBasic::CAAEGSMSewSkinBasic():
CATBaseUnknown()
{
	// cout << "(CAAEGSMSewSkinBasic::CAAEGSMSewSkinBasic)CAAEGSMSewSkinBasic - Constructor" <<endl;
}

//-----------------------------------------------------------------------------
// CAAEGSMSewSkinBasic : destructor
//-----------------------------------------------------------------------------
CAAEGSMSewSkinBasic::~CAAEGSMSewSkinBasic()
{
	//cout << "(CAAEGSMSewSkinBasic::~CAAEGSMSewSkinBasic)CAAEGSMSewSkinBasic - Destructor" <<endl;
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CAAIGSMSewSkinBasic.h"
TIE_CAAIGSMSewSkinBasic( CAAEGSMSewSkinBasic);



//-----------------------------------------------------------------------------
// Implements CAAIGSMSewSkinBasic::SetSurfaceToSew
//-----------------------------------------------------------------------------
HRESULT CAAEGSMSewSkinBasic::SetSurfaceToSew (CATISpecObject_var  ipSurfaceToSew )
{

	//cout << "(CAAEGSMSewSkinBasic::SetSurfaceToSew)" <<endl;


	HRESULT rc = E_FAIL ; 
	CATISpecObject_var GSMSewSkinBasic (this);
	CATISpecObject_var ToSet= ipSurfaceToSew;


	// Gets a pointer on the curve attribute to get
	CATISpecAttrAccess_var spGSMSewSkinBasicAttrAccess = GSMSewSkinBasic;

	// Sets Attribute for GSMGeom dervited late type 
	CATIGSMAttributes_var spGsdSpecAttr (this) ; 
	CATISpecAttrKey_var pInputSurfaceSpecAttrKey = NULL_var ;

	if (!!spGsdSpecAttr){ 
		if (!!spGSMSewSkinBasicAttrAccess) {
			pInputSurfaceSpecAttrKey = spGSMSewSkinBasicAttrAccess ->GetAttrKey("SurfaceToSew");
			if (!!ToSet ) { 
				rc = spGsdSpecAttr -> SetAttrSpecObject(pInputSurfaceSpecAttrKey,ipSurfaceToSew);
			}
			else {
				rc = spGsdSpecAttr -> UnsetAttrValue(pInputSurfaceSpecAttrKey);
			}
			if (!!pInputSurfaceSpecAttrKey) {
				pInputSurfaceSpecAttrKey->Release();pInputSurfaceSpecAttrKey = NULL_var;
			}
		}
	}
	return rc ; 

}

//-----------------------------------------------------------------------------
// Implements CAAIGSMSewSkinBasic::GetSurfaceToSew
//-----------------------------------------------------------------------------
HRESULT  CAAEGSMSewSkinBasic::GetSurfaceToSew (CATISpecObject_var & ospSurfaceToSew  )
{
	//cout << "(CAAEGSMSewSkinBasic::GetSurfaceToSew)" <<endl;

	HRESULT rc = E_FAIL ; 
	// Gets a pointer on CATISpecObject
	CATISpecObject_var GSMSewSkinBasic(this) ;

	// Gets a pointer on the curve attribute to get
	CATISpecAttrAccess_var spGSMSewSkinBasicAttrAccess = GSMSewSkinBasic;

	// Gets Attribute for GSMGeom dervited late type 

	CATIGSMAttributes_var spGsdSpecAttr (this) ; 
	CATISpecAttrKey_var pInputSurfaceSpecAttrKey = NULL_var ;

	if (!!spGsdSpecAttr){ 
		if (!!spGSMSewSkinBasicAttrAccess) {
			pInputSurfaceSpecAttrKey = spGSMSewSkinBasicAttrAccess ->GetAttrKey("SurfaceToSew");
			if (!!pInputSurfaceSpecAttrKey) { 
				rc   = spGsdSpecAttr -> GetAttrSpecObject(pInputSurfaceSpecAttrKey,ospSurfaceToSew);
				pInputSurfaceSpecAttrKey->Release();pInputSurfaceSpecAttrKey = NULL_var;
			}
			else {
				rc = E_FAIL; 
			}
		}
	}
	return rc ; 

}

//-----------------------------------------------------------------------------
// Implements CAAIGSMSewSkinBasic::SetSurfaceSupport
//-----------------------------------------------------------------------------
HRESULT CAAEGSMSewSkinBasic::SetSurfaceSupport (CATISpecObject_var ipSupport )
{
	// cout << "( CAAEGSMSewSkinBasic::SetSurfaceSupport )" <<endl;

	HRESULT rc = E_FAIL ; 
	CATISpecObject_var GSMSewSkinBasic (this);
	CATISpecObject_var ToSet= ipSupport;

	// Gets a pointer on the curve attribute to get
	CATISpecAttrAccess_var spGSMSewSkinBasicAttrAccess = GSMSewSkinBasic;

	// Sets Attribute for GSMGeom dervited late type 
	CATIGSMAttributes_var spGsdSpecAttr (this) ; 
	CATISpecAttrKey_var pInputSurfaceSpecAttrKey = NULL_var ;

	if (!!spGsdSpecAttr){ 
		if (!!spGSMSewSkinBasicAttrAccess) {
			pInputSurfaceSpecAttrKey = spGSMSewSkinBasicAttrAccess ->GetAttrKey("SurfaceSupport");
			if (!!ToSet ) { 
				rc = spGsdSpecAttr -> SetAttrSpecObject(pInputSurfaceSpecAttrKey, ipSupport);
			}
			else {
				rc = spGsdSpecAttr -> UnsetAttrValue(pInputSurfaceSpecAttrKey);
			}
			if (!!pInputSurfaceSpecAttrKey) {
				pInputSurfaceSpecAttrKey->Release();pInputSurfaceSpecAttrKey = NULL_var;
			}
		}
	}
	return rc ; 
}

//-----------------------------------------------------------------------------
// Implements CAAIGSMSewSkinBasic::GetSurfaceSupport
//-----------------------------------------------------------------------------
HRESULT CAAEGSMSewSkinBasic::GetSurfaceSupport (CATISpecObject_var & ospSupport)
{
	//   cout << "(CAAEGSMSewSkinBasic::GetSurfaceSupport )" <<endl;

	HRESULT rc = E_FAIL ; 
	// Gets a pointer on CATISpecObject
	CATISpecObject_var GSMSewSkinBasic(this) ;

	// Gets a pointer on the curve attribute to get
	CATISpecAttrAccess_var spGSMSewSkinBasicAttrAccess = GSMSewSkinBasic;

	// Gets Attribute for GSMGeom dervited late type 
	CATIGSMAttributes_var spGsdSpecAttr (this) ; 
	CATISpecAttrKey_var pInputSurfaceSpecAttrKey = NULL_var ;

	if (!!spGsdSpecAttr){ 
		if (!!spGSMSewSkinBasicAttrAccess) {
			pInputSurfaceSpecAttrKey = spGSMSewSkinBasicAttrAccess ->GetAttrKey("SurfaceSupport");
			if (!!pInputSurfaceSpecAttrKey) { 
				rc  = spGsdSpecAttr -> GetAttrSpecObject(pInputSurfaceSpecAttrKey,ospSupport);
				pInputSurfaceSpecAttrKey->Release();pInputSurfaceSpecAttrKey = NULL_var;
			}
			else {
				rc = E_FAIL; 
			}
		}
	}
	return rc ; 
}


//-----------------------------------------------------------------------------
// Implements CAAIGSMSewSkinBasic::SetOrientation
//-----------------------------------------------------------------------------

HRESULT CAAEGSMSewSkinBasic::SetOrientation(CATGSMOrientation iOrientation)
{
	//  cout << "(CAAEGSMSewSkinBasic::SetOrientation) " <<endl;
	CATISpecObject_var GSMSewSkinBasic(this) ;

	// Gets a pointer on the curve attribute to get
	CATISpecAttrAccess_var GSMSewSkinBasicAttrAccess = GSMSewSkinBasic;
	CATISpecAttrKey * Orientation = NULL ;

	if(!!GSMSewSkinBasicAttrAccess) {
		Orientation = GSMSewSkinBasicAttrAccess ->GetAttrKey("Orientation");
		if (NULL == Orientation) return E_FAIL; 
	}
	else
	{
		return E_FAIL;
	}

	GSMSewSkinBasicAttrAccess->UnsetAttributeValue(Orientation);

	if (iOrientation == CATGSMSameOrientation){
		GSMSewSkinBasicAttrAccess->SetInteger(Orientation,1);
	}else {
		GSMSewSkinBasicAttrAccess->SetInteger(Orientation,0);
	}
	if (!!Orientation) {Orientation->Release();Orientation = NULL;}

	return S_OK;
}

//-----------------------------------------------------------------------------
// Implements CAAIGSMSewSkinBasic::GetOrientation
//-----------------------------------------------------------------------------

HRESULT CAAEGSMSewSkinBasic::GetOrientation(CATGSMOrientation &iOrientation)
{
	//cout << "(CAAEGSMSewSkinBasic::GetOrientation) " <<endl;
	CATISpecObject_var GSMSewSkinBasic(this) ;

	// Gets a pointer on the curve attribute to get
	CATISpecAttrAccess_var GSMSewSkinBasicAttrAccess = GSMSewSkinBasic;
	CATISpecAttrKey * Orientation = NULL ;

	if(!!GSMSewSkinBasicAttrAccess) {
		Orientation = GSMSewSkinBasicAttrAccess ->GetAttrKey("Orientation");
		if (NULL == Orientation) return E_FAIL; 
	}
	else
	{
		return E_FAIL;
	}

	int ori = GSMSewSkinBasicAttrAccess->GetInteger(Orientation);
	if (ori == 0){
		iOrientation = CATGSMInvertOrientation;
	}else {
		iOrientation = CATGSMSameOrientation;
	}

	if (!!Orientation) {Orientation->Release();Orientation = NULL;}

	return S_OK;
}



//-----------------------------------------------------------------------------
// Implements CAAIGSMSewSkinBasic::InvertOrientation
//-----------------------------------------------------------------------------

HRESULT CAAEGSMSewSkinBasic::InvertOrientation()
{
	// cout << "(CAAEGSMSewSkinBasic::InvertOrientation) " <<endl;

	CATISpecObject_var GSMSewSkinBasic(this) ;

	// Gets a pointer on the curve attribute to get
	CATISpecAttrAccess_var GSMSewSkinBasicAttrAccess = GSMSewSkinBasic;
	CATISpecAttrKey * Orientation = NULL ;

	if(!!GSMSewSkinBasicAttrAccess) {
		Orientation = GSMSewSkinBasicAttrAccess ->GetAttrKey("Orientation");
		if (NULL == Orientation) return E_FAIL; 
	}
	else    {
		return E_FAIL;
	}

	int ori = GSMSewSkinBasicAttrAccess->GetInteger(Orientation);
	if (ori == 0){
		SetOrientation(CATGSMSameOrientation);
	}else {
		SetOrientation(CATGSMInvertOrientation);
	}
	if (!!Orientation) {Orientation->Release();Orientation = NULL;}

	return S_OK;
}
