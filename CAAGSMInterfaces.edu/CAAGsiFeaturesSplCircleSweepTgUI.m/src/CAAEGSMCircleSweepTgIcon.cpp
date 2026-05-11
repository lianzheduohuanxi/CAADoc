// COPYRIGHT DASSAULT SYSTEMES 2006
//===================================================================
// CATIA ShapeDesign And Styling  
// ------------------------------------------------------------------
//
// CAAEGSMCircleSweepTgIcon.cpp
// Provide implementation to interface
//    CATIIcon 
//
//===================================================================
//June 2006 : Creation CAA Sample 
//===================================================================

// Local FrameWork
#include "CAAEGSMCircleSweepTgIcon.h"
#include "CATIMf3DBehavior2.h"

#include "CAAIGSMCircleSweepTg.h"

#include "CATUnicodeString.h"

CATImplementClass ( CAAEGSMCircleSweepTgIcon ,
                    CodeExtension           ,
                    CATBaseUnknown          ,
                    CAACircleSweepTg          );

//-----------------------------------------------------------------------------
// CAAEGSMCircleSweepTgIcon : constructor
//-----------------------------------------------------------------------------
CAAEGSMCircleSweepTgIcon::CAAEGSMCircleSweepTgIcon()
{
}

//-----------------------------------------------------------------------------
// CAAEGSMCircleSweepTgIcon : destructor
//-----------------------------------------------------------------------------
CAAEGSMCircleSweepTgIcon::~CAAEGSMCircleSweepTgIcon()
{
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIIcon.h" // needed to tie the implementation to its interface
TIE_CATIIcon( CAAEGSMCircleSweepTgIcon);

// 
// To declare that CircleSweepTg implements CATIEdit , insert 
// the following line in the interface dictionary :
//
// CAACircleSweepTg      CATIIcon    libCAAGsiFeaturesSplCircleSweepTgUI

//-----------------------------------------------------------------------------
// Implements CATIIcon::GetIconName
//-----------------------------------------------------------------------------

HRESULT CAAEGSMCircleSweepTgIcon::GetIconName(CATUnicodeString& oName)
{
    
    // returns the name of the icon representing Combined Curves in the graph
    // oName = CATUnicodeString("CAAGsi_I_SewSkin");
    // CAAIGSMCircleSweepTg_var spCircleSweepTg (this);
    //if(!!spCircleSweepTg)
    //{
    //    CATBoolean IsAVolume = FALSE;
    //    CATIMf3DBehavior2_var spBehavior2 =spCircleSweepTg ;                                       
    //    if(!!spBehavior2)                                                               
    //    {                                                                          
    //        HRESULT rc =spBehavior2->IsAVolume();                                       
    //        if(FAILED(rc))                                                          
    //            IsAVolume=FALSE;                                                    
    //        else                                                                    
    //            IsAVolume=TRUE;                                                     
    //    }                      
    //    
    //    if (IsAVolume)
    //        oName =  CATUnicodeString("CAAGsi_I_SewSkinVolume");
    //    else
    //
    //    oName =  CATUnicodeString("CAAGsi_I_SewSkin"); 
    //}
    oName = CATUnicodeString("CAAGsi_I_CircleSweepTg"); 
    
    return S_OK;
}
    
    

//-----------------------------------------------------------------------------
// Implements CATIIcon::SetIconName
//-----------------------------------------------------------------------------

HRESULT CAAEGSMCircleSweepTgIcon::SetIconName(const CATUnicodeString& iName)
{
    return E_FAIL;
}

