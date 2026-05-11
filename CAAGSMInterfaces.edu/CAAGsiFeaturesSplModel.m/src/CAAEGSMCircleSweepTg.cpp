// COPYRIGHT Dassault Systemes 2005
//===================================================================
// CATIA ShapeDesign And Styling  
// ------------------------------------------------------------------
//
// CAAEGSMCircleSweepTg.cpp
// Provide implementation to interface
//    CAAIGSMCircleSweepTg
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//June 2006 : Creation CAA Sample 
//===================================================================

#include "CAAEGSMCircleSweepTg.h"

#include "CATISpecObject.h"
#include "CATISpecAttribute.h"
#include "CATISpecAttrKey.h"
#include "CATISpecAttrAccess.h"
#include "CATLISTV_CATBaseUnknown.h"

// V5R17 
#include "CATIGSMAttributes.h"

// #define DEBUG_GSD_CAASAMPLE
#ifdef DEBUG_GSD_CAASAMPLE
#include "iostream.h"
#endif 



CATImplementClass( CAAEGSMCircleSweepTg,CodeExtension, CATBaseUnknown, CAACircleSweepTg );

//-----------------------------------------------------------------------------
// CAAEGSMCircleSweepTg : constructor
//-----------------------------------------------------------------------------
CAAEGSMCircleSweepTg::CAAEGSMCircleSweepTg():
CATBaseUnknown()
{
#ifdef DEBUG_GSD_CAASAMPLE
	cout << "CAAEGSMCircleSweepTg - Constructor" <<endl;
#endif 
}

//-----------------------------------------------------------------------------
// CAAEGSMCircleSweepTg : destructor
//-----------------------------------------------------------------------------
CAAEGSMCircleSweepTg::~CAAEGSMCircleSweepTg()
{
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "CAAEGSMCircleSweepTg - Destructor" <<endl;
#endif 
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CAAIGSMCircleSweepTg.h"
TIE_CAAIGSMCircleSweepTg( CAAEGSMCircleSweepTg);
//-----------------------------------------------------------------------------
// Implements CAAIGSMCircleSweepTg::SetCurveRef
//-----------------------------------------------------------------------------
HRESULT CAAEGSMCircleSweepTg::SetCurveRef (const CATISpecObject_var  ispCurveRef )
{
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAEspCircleSweepTg::SetCurveRef)" <<endl;
#endif     
    

	HRESULT rc = S_OK; 
    CATISpecObject_var spCircleSweepTg (this);
    CATISpecObject_var ToSet= ispCurveRef;
    
    CATISpecAttrAccess_var spCircleSweepTgAttrAccess = spCircleSweepTg;

	// Set up attribute on GSMGeom derivated  Object 
	CATIGSMAttributes_var spGsdSpecAttr (this) ; 
	CATISpecAttrKey_var pInputSurfaceSpecAttrKey = NULL_var ;

	if (!!spGsdSpecAttr){ 
		if (!!spCircleSweepTgAttrAccess) {
			pInputSurfaceSpecAttrKey = spCircleSweepTgAttrAccess ->GetAttrKey("CurveRef");
			if (!!ToSet ) { 
				rc = spGsdSpecAttr -> SetAttrSpecObject(pInputSurfaceSpecAttrKey,ispCurveRef);
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
// Implements CAAIGSMCircleSweepTg::GetCurveRef
//-----------------------------------------------------------------------------
HRESULT CAAEGSMCircleSweepTg::GetCurveRef (CATISpecObject_var & ospCurveRef )
{
    
	HRESULT rc = E_FAIL;
    // Gets a pointer on CATISpecObject
    CATISpecObject_var spCircleSweepTg(this) ;
    
    
    // Gets a pointer on the curve attribute to get
    CATISpecAttrAccess_var spCircleSweepTgAttrAccess = spCircleSweepTg;

	// Set up attribute on GSMGeom derivated  Object 
	CATIGSMAttributes_var spGsdSpecAttr (this) ; 
	CATISpecAttrKey_var pInputSurfaceSpecAttrKey = NULL_var ;

	if (!!spGsdSpecAttr){ 
		if (!!spCircleSweepTgAttrAccess) {
			pInputSurfaceSpecAttrKey = spCircleSweepTgAttrAccess ->GetAttrKey("CurveRef");
			if (!!pInputSurfaceSpecAttrKey) { 
				rc  = spGsdSpecAttr -> GetAttrSpecObject(pInputSurfaceSpecAttrKey, ospCurveRef);
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
// Implements CAAIGSMCircleSweepTg::SetSurfaceSupport
//-----------------------------------------------------------------------------
HRESULT CAAEGSMCircleSweepTg::SetSurfaceSupport (const CATISpecObject_var  ipSupport )
{
    HRESULT rc = E_FAIL ; 
    CATISpecObject_var spCircleSweepTg (this);
    CATISpecObject_var ToSet= ipSupport;
    
    CATISpecAttrAccess_var spCircleSweepTgAttrAccess = spCircleSweepTg;

	// Set up attribute on GSMGeom derivated  Object 
	CATIGSMAttributes_var spGsdSpecAttr (this) ; 
	CATISpecAttrKey_var pInputSurfaceSpecAttrKey = NULL_var ;

	if (!!spGsdSpecAttr){ 
		if (!!spCircleSweepTgAttrAccess) {
			pInputSurfaceSpecAttrKey = spCircleSweepTgAttrAccess ->GetAttrKey("SurfaceSupport");
			if (!!ToSet ) { 
				rc = spGsdSpecAttr -> SetAttrSpecObject(pInputSurfaceSpecAttrKey,ipSupport);
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
// Implements CAAIGSMCircleSweepTg::GetSurfaceSupport
//-----------------------------------------------------------------------------
HRESULT CAAEGSMCircleSweepTg::GetSurfaceSupport (CATISpecObject_var & ospSupport )
{
	HRESULT rc = E_FAIL ;     
    // Gets a pointer on CATISpecObject
    CATISpecObject_var spCircleSweepTg(this) ;
    
    
    // Gets a pointer on the curve attribute to get
    CATISpecAttrAccess_var spCircleSweepTgAttrAccess = spCircleSweepTg;

	// Get up attribute on GSMGeom derivated  Object 
	CATIGSMAttributes_var spGsdSpecAttr (this) ; 
	CATISpecAttrKey_var pInputSurfaceSpecAttrKey = NULL_var ;

	if (!!spGsdSpecAttr){ 
		if (!!spCircleSweepTgAttrAccess) {
			pInputSurfaceSpecAttrKey = spCircleSweepTgAttrAccess ->GetAttrKey("SurfaceSupport");
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
// Implements CAAIGSMCircleSweepTg::SetRadius
//-----------------------------------------------------------------------------
HRESULT CAAEGSMCircleSweepTg::SetRadius (const double  iRadius)
{
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAEspCircleSweepTg::SetRadius) " <<endl;
#endif     
	CATISpecObject_var spCircleSweepTg(this) ;
    
    // Gets a pointer on the curve attribute to get
    CATISpecAttrAccess_var spCircleSweepTgAttrAccess = spCircleSweepTg;

	CATISpecAttrKey * Radius = NULL ;
    
    if(!!spCircleSweepTgAttrAccess) {
        Radius = spCircleSweepTgAttrAccess ->GetAttrKey("Radius");
        if (NULL == Radius) return E_FAIL; 
    }
    else
    {
        return E_FAIL;
    }
    
   // spCircleSweepTgAttrAccess->UnsetAttributeValue(Radius);
    spCircleSweepTgAttrAccess->SetDouble(Radius,iRadius);
    if (!!Radius) {Radius->Release();Radius = NULL;}
    return S_OK;
}

//-----------------------------------------------------------------------------
// Implements CAAIGSMCircleSweepTg::GetRadius
//-----------------------------------------------------------------------------
HRESULT CAAEGSMCircleSweepTg::GetRadius (double &  oRadius)
{

#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAEGSMCircleSweepTg::GetRadius ) " <<endl;
#endif 
	CATISpecObject_var spCircleSweepTg(this) ;
    
    // Gets a pointer on the curve attribute to get
    CATISpecAttrAccess_var spCircleSweepTgAttrAccess = spCircleSweepTg;
    CATISpecAttrKey * Radius = NULL ;
    
    if(!!spCircleSweepTgAttrAccess) {
        Radius = spCircleSweepTgAttrAccess ->GetAttrKey("Radius");
        if (NULL == Radius) return E_FAIL; 
    }
    else
    {
        return E_FAIL;
    }
    
    oRadius  = spCircleSweepTgAttrAccess->GetDouble(Radius);
    
    if (!!Radius) {Radius->Release();Radius = NULL;}
    
    return S_OK;
}

//-----------------------------------------------------------------------------
// Implements CAAIGSMCircleSweepTg::SetSolution
//-----------------------------------------------------------------------------
HRESULT CAAEGSMCircleSweepTg::SetSolution (const int  iSolution)
{
#ifdef DEBUG_GSD_CAASAMPLE
     cout << "(CAAEspCircleSweepTg::SetSolution) " <<endl;
#endif 
	 CATISpecObject_var spCircleSweepTg(this) ;
    
    // Gets a pointer on the curve attribute to get
    CATISpecAttrAccess_var spCircleSweepTgAttrAccess = spCircleSweepTg;
    CATISpecAttrKey * Solution = NULL ;
    
    if(!!spCircleSweepTgAttrAccess) {
        Solution = spCircleSweepTgAttrAccess ->GetAttrKey("Solution");
        if (NULL == Solution) return E_FAIL; 
    }
    else
    {
        return E_FAIL;
    }
    
    spCircleSweepTgAttrAccess->UnsetAttributeValue(Solution);
    
    
    spCircleSweepTgAttrAccess->SetInteger(Solution,iSolution);
    if (!!Solution) {Solution->Release();Solution = NULL;}
    return S_OK;
}

//-----------------------------------------------------------------------------
// Implements CAAIGSMCircleSweepTg::GetSolution
//-----------------------------------------------------------------------------
HRESULT CAAEGSMCircleSweepTg::GetSolution (int &  oSolution)
{
    CATISpecObject_var spCircleSweepTg(this) ;
    
    // Gets a pointer on the curve attribute to get
    CATISpecAttrAccess_var spCircleSweepTgAttrAccess = spCircleSweepTg;
    CATISpecAttrKey * Solution = NULL ;
    
    if(!!spCircleSweepTgAttrAccess) {
        Solution = spCircleSweepTgAttrAccess ->GetAttrKey("Solution");
        if (NULL == Solution) return E_FAIL; 
    }
    else
    {
        return E_FAIL;
    }
    
    oSolution  = spCircleSweepTgAttrAccess->GetInteger(Solution);
    
    if (!!Solution) {Solution->Release();Solution = NULL;}
    return S_OK;
}

//-----------------------------------------------------------------------------
// Implements CAAIGSMCircleSweepTg::SetTrimMode
//-----------------------------------------------------------------------------
HRESULT CAAEGSMCircleSweepTg::SetTrimMode (const int  iTrimMode)
{
#ifdef DEBUG_GSD_CAASAMPLE
    cout << "(CAAEspCircleSweepTg::SetTrimMode) " <<endl;
#endif 
	CATISpecObject_var spCircleSweepTg(this) ;
    
    // Gets a pointer on the curve attribute to get
    CATISpecAttrAccess_var spCircleSweepTgAttrAccess = spCircleSweepTg;
    CATISpecAttrKey * TrimMode = NULL ;
    
    if(!!spCircleSweepTgAttrAccess) {
        TrimMode = spCircleSweepTgAttrAccess ->GetAttrKey("TrimMode");
        if (NULL == TrimMode) return E_FAIL; 
    }
    else
    {
        return E_FAIL;
    }
    
    spCircleSweepTgAttrAccess->UnsetAttributeValue(TrimMode);
    
    
    spCircleSweepTgAttrAccess->SetInteger(TrimMode,iTrimMode);
    if (!!TrimMode) {TrimMode->Release();TrimMode = NULL;}
    return S_OK;
}

//-----------------------------------------------------------------------------
// Implements CAAIGSMCircleSweepTg::GetTrimMode
//-----------------------------------------------------------------------------
HRESULT CAAEGSMCircleSweepTg::GetTrimMode (int &  oTrimMode)
{
    CATISpecObject_var spCircleSweepTg(this) ;
    
    // Gets a pointer on the curve attribute to get
    CATISpecAttrAccess_var spCircleSweepTgAttrAccess = spCircleSweepTg;
    CATISpecAttrKey * TrimMode = NULL ;
    
    if(!!spCircleSweepTgAttrAccess) {
        TrimMode = spCircleSweepTgAttrAccess ->GetAttrKey("TrimMode");
        if (NULL == TrimMode) return E_FAIL; 
    }
    else
    {
        return E_FAIL;
    }
    
    oTrimMode  = spCircleSweepTgAttrAccess->GetInteger(TrimMode);
    
    if (!!TrimMode) {TrimMode->Release();TrimMode = NULL;}
    return S_OK;
}
