// COPYRIGHT Dassault Systemes 2003
//===================================================================
// CATIA ShapeDesign And Styling  
// ------------------------------------------------------------------//
// CAAEGSMSewSkinBasicMf3DBehavior.cpp
// Provide implementation to interface
//    CATIMf3DBehavior
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//June 2006 : Creation CAA Sample 
//===================================================================

#include "CAAEGSMSewSkinBasicMf3DBehavior.h"

#include "CATISpecObject.h"
#include "CAAIGSMSewSkinBasic.h"
#include "CATGSMContextDef.h"

#include "CATBody.h"

#include "CAAGsiServicesBody.h"

// #include "iostream.h"
 
CATImplementClass( CAAEGSMSewSkinBasicMf3DBehavior,
                    CodeExtension,
                    CATBaseUnknown,
                    CAASewSkinBasic );
//-----------------------------------------------------------------------------
// CAAEGSMSewSkinBasicMf3DBehavior : constructor
//-----------------------------------------------------------------------------
CAAEGSMSewSkinBasicMf3DBehavior::CAAEGSMSewSkinBasicMf3DBehavior():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAEGSMSewSkinBasicMf3DBehavior : destructor
//-----------------------------------------------------------------------------
CAAEGSMSewSkinBasicMf3DBehavior::~CAAEGSMSewSkinBasicMf3DBehavior()
{
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIMf3DBehavior.h"
TIE_CATIMf3DBehavior( CAAEGSMSewSkinBasicMf3DBehavior);
//-----------------------------------------------------------------------------
// Implements CATIMf3DBehavior::IsASolid
//-----------------------------------------------------------------------------
HRESULT CAAEGSMSewSkinBasicMf3DBehavior::IsASolid () const
{
    HRESULT rc = E_FAIL;
    return rc = E_FAIL;
}

//-----------------------------------------------------------------------------
// Implements CATIMf3DBehavior::IsAShape
//-----------------------------------------------------------------------------
HRESULT CAAEGSMSewSkinBasicMf3DBehavior::IsAShape () const
{
    
    HRESULT rc = S_OK ; 
    /*
    int iType = 0; 
    CATISpecObject_var hSpec = GetImpl();
    CAAIGSMSewSkinBasic_var spGSMSewSkinBasic = hSpec  ;
    if(!!spGSMSewSkinBasic)    {
        CATGSMFeatureContextType Ctx=CATGSMSurfaceCtxt;
        spGSMSewSkinBasic->GetContext(Ctx);
        spGSMSewSkinBasic->GetResultType(iType);
        if(Ctx==CATGSMSurfaceCtxt || iType == 0 ){
            cout << "(CAAGSMSewSkinBasicDlg::IsAShape) IsAShape  ? YES"  << endl; 
            rc =  S_OK;
        }
        else {
            cout << "(CAAGSMSewSkinBasicDlg::IsAShape) IsAShape  ? NO"  << endl; 
            rc =  E_FAIL;
        }
    }
    */ 
    return rc;
}

//-----------------------------------------------------------------------------
// Implements CATIMf3DBehavior::IsADatum
//-----------------------------------------------------------------------------
HRESULT CAAEGSMSewSkinBasicMf3DBehavior::IsADatum () const
{
    HRESULT rc = E_FAIL;
    return rc;
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIMf3DBehavior2.h"
TIE_CATIMf3DBehavior2(CAAEGSMSewSkinBasicMf3DBehavior);
//-----------------------------------------------------------------------------
// Implements CATIMf3DBehavior::IsASolid
//-----------------------------------------------------------------------------
HRESULT CAAEGSMSewSkinBasicMf3DBehavior::IsAVolume () const
{
    
    HRESULT rc = E_FAIL;
/*
    CATISpecObject_var hSpec = GetImpl();
    CATBody_var BodyRes = CAAGsiGetFirstBody(hSpec); 
    // Check on Geometrical result 
    if (!! BodyRes) { 
        
        if(CAAGsiGetHigherDimFromBody(BodyRes)==3)        {
            //cout << "(CAAEGSMSewSkinBasicMf3DBehavior::IsAVolume ) IsAVolume  ? YES"  << endl; 
            rc = S_OK;
            
        }
    }
    // Check on feature attributes 
    else {
        CAAIGSMSewSkinBasic_var spGSMSewSkinBasic = hSpec  ;
        if(!!spGSMSewSkinBasic)    {
            int iType = 0; 
            CATGSMFeatureContextType Ctx=CATGSMSurfaceCtxt;
            spGSMSewSkinBasic->GetContext(Ctx);
            spGSMSewSkinBasic->GetResultType(iType);
            
            if(Ctx==CATGSMVolumeCtxt && iType == 1 ){
                //cout << "(CAAEGSMSewSkinBasicMf3DBehavior::IsAVolume ) IsAVolume  ? YES"  << endl; 
                rc =  S_OK;
            }
            else {
                //cout << "(CAAEGSMSewSkinBasicMf3DBehavior::IsAVolume ) IsAVolume  ? NO"  << endl; 
                rc =  E_FAIL;
            }
        }
    }
  */  
    return rc ;
}

