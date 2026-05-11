// COPYRIGHT Dassault Systemes 2005
//===================================================================
// CATIA ShapeDesign And Styling  
// ------------------------------------------------------------------
//
// CAAEGSMCircleSweepTgMf3DBehavior.cpp
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

#include "CAAEGSMCircleSweepTgMf3DBehavior.h"

#include "CATISpecObject.h"
#include "CAAIGSMCircleSweepTg.h"
#include "CATBody.h"

#include "CAAGsiServicesBody.h"


CATImplementClass( CAAEGSMCircleSweepTgMf3DBehavior,
                    CodeExtension,
                    CATBaseUnknown,
                    CAACircleSweepTg );
//-----------------------------------------------------------------------------
// CAAEGSMCircleSweepTgMf3DBehavior : constructor
//-----------------------------------------------------------------------------
CAAEGSMCircleSweepTgMf3DBehavior::CAAEGSMCircleSweepTgMf3DBehavior():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAEGSMCircleSweepTgMf3DBehavior : destructor
//-----------------------------------------------------------------------------
CAAEGSMCircleSweepTgMf3DBehavior::~CAAEGSMCircleSweepTgMf3DBehavior()
{
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIMf3DBehavior.h"
TIE_CATIMf3DBehavior( CAAEGSMCircleSweepTgMf3DBehavior);
//-----------------------------------------------------------------------------
// Implements CATIMf3DBehavior::IsASolid
//-----------------------------------------------------------------------------
HRESULT CAAEGSMCircleSweepTgMf3DBehavior::IsASolid () const
{
    HRESULT rc = E_FAIL;
    return rc = E_FAIL;
}

//-----------------------------------------------------------------------------
// Implements CATIMf3DBehavior::IsAShape
//-----------------------------------------------------------------------------
HRESULT CAAEGSMCircleSweepTgMf3DBehavior::IsAShape () const
{
    
    HRESULT rc = S_OK ; 
    return rc;
}

//-----------------------------------------------------------------------------
// Implements CATIMf3DBehavior::IsADatum
//-----------------------------------------------------------------------------
HRESULT CAAEGSMCircleSweepTgMf3DBehavior::IsADatum () const
{
    HRESULT rc = E_FAIL;
    return rc;
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIMf3DBehavior2.h"
TIE_CATIMf3DBehavior2(CAAEGSMCircleSweepTgMf3DBehavior);
//-----------------------------------------------------------------------------
// Implements CATIMf3DBehavior::IsASolid
//-----------------------------------------------------------------------------
HRESULT CAAEGSMCircleSweepTgMf3DBehavior::IsAVolume () const
{
    HRESULT rc = E_FAIL;
    
    /*
    CATISpecObject_var hSpec = GetImpl();
    CATBody_var BodyRes = CAAGsiGetFirstBody(hSpec); 
    // Check on Geometrical result 
    if (!! BodyRes) { 
        
        if(CAAGsiGetHigherDimFromBody(BodyRes)==3)        {
            //cout << "(CAAEGSMCircleSweepTgMf3DBehavior::IsAVolume ) IsAVolume  ? YES"  << endl; 
            rc = S_OK;
            
        }
    }
    // Check on feature attributes 
    else {
        CAAIGSMCircleSweepTg_var spGSMCircleSweepTg = hSpec  ;
        if(!!spGSMCircleSweepTg)    {
            int iType = 0; 
            CATGSMFeatureContextType Ctx=CATGSMSurfaceCtxt;
            spGSMCircleSweepTg->GetContext(Ctx);
            spGSMCircleSweepTg->GetResultType(iType);
            
            if(Ctx==CATGSMVolumeCtxt && iType == 1 ){
                //cout << "(CAAEGSMCircleSweepTgMf3DBehavior::IsAVolume ) IsAVolume  ? YES"  << endl; 
                rc =  S_OK;
            }
            else {
                //cout << "(CAAEGSMCircleSweepTgMf3DBehavior::IsAVolume ) IsAVolume  ? NO"  << endl; 
                rc =  E_FAIL;
            }
        }
    }
    */

    
    return rc ;
}

