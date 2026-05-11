// COPYRIGHT DASSAULT SYSTEMES 2006
//===================================================================
// CATIA ShapeDesign And Styling  
// ------------------------------------------------------------------
//
// CAAEGSMSewSkinBasicIcon.cpp
// Provide implementation to interface
//    CATIIcon 
//
//===================================================================
//June 2006 : Creation CAA Sample 
//===================================================================

// Local FrameWork
// MINC 
#include "CATBoolean.h"

#include "CAAEGSMSewSkinBasicIcon.h"
#include "CATIMf3DBehavior2.h"

#include "CAAIGSMSewSkinBasic.h"

#include "CATUnicodeString.h"

CATImplementClass ( CAAEGSMSewSkinBasicIcon ,
                    CodeExtension           ,
                    CATBaseUnknown          ,
                    CAASewSkinBasic            );

//-----------------------------------------------------------------------------
// CAAEGSMSewSkinBasicIcon : constructor
//-----------------------------------------------------------------------------
CAAEGSMSewSkinBasicIcon::CAAEGSMSewSkinBasicIcon()
{
}

//-----------------------------------------------------------------------------
// CAAEGSMSewSkinBasicIcon : destructor
//-----------------------------------------------------------------------------
CAAEGSMSewSkinBasicIcon::~CAAEGSMSewSkinBasicIcon()
{
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIIcon.h" // needed to tie the implementation to its interface
TIE_CATIIcon( CAAEGSMSewSkinBasicIcon);

// 
// To declare that SewSkin implements CATIIcon, insert 
// the following line in the interface dictionary :
//
// SewSkin      CATIIcon    libCAASewSkinUI

//-----------------------------------------------------------------------------
// Implements CATIIcon::GetIconName
//-----------------------------------------------------------------------------

HRESULT CAAEGSMSewSkinBasicIcon::GetIconName(CATUnicodeString& oName)
{
    
    // returns the name of the icon representing Combined Curves in the graph
    // oName = CATUnicodeString("CAAGsi_I_SewSkin");
    CAAIGSMSewSkinBasic_var spSewSkin (this);
    if(!!spSewSkin)
    {
        CATBoolean IsAVolume = FALSE;
        CATIMf3DBehavior2_var spBehavior2 = spSewSkin ;                                       
        if(!!spBehavior2)                                                               
        {                                                                          
            HRESULT rc =spBehavior2->IsAVolume();                                       
            if(FAILED(rc))                                                          
                IsAVolume=FALSE;                                                    
            else                                                                    
                IsAVolume=TRUE;                                                     
        }                      
        
        if (IsAVolume)
            oName =  CATUnicodeString("CAAGsi_I_SewSkinVolume");
        else
            oName =  CATUnicodeString("CAAGsi_I_SewSkin"); 
    }
    else
        oName = CATUnicodeString("CAAGsi_I_SewSkin"); 
    
    return S_OK;
}
    
    

//-----------------------------------------------------------------------------
// Implements CATIIcon::SetIconName
//-----------------------------------------------------------------------------

HRESULT CAAEGSMSewSkinBasicIcon::SetIconName(const CATUnicodeString& iName)
{
    return E_FAIL;
}

