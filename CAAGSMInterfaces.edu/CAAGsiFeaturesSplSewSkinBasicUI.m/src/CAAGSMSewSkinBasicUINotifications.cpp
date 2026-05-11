// =========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2006
// =========================================================================
// CATIA Shape Design And Styling 
//---------------------------------------------------------------------
// 
// CAAGSMSewSkinBasicUINotifications
//---------------------------------------------------------------------
// 
//  Sew Skin Basic command notifications  
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 05/xx/xx > PEY 
//---------------------------------------------------------------------
#include "CAAGSMSewSkinBasicUINotifications.h"


 // needed to Clear Selection
//--------------------------------------------------------------

CATImplementClass(CAAGSMSewSkinBasicUIRemoveElement,Implementation,CATNotification,CATNull);
CAAGSMSewSkinBasicUIRemoveElement::CAAGSMSewSkinBasicUIRemoveElement()
{
}
CAAGSMSewSkinBasicUIRemoveElement::~CAAGSMSewSkinBasicUIRemoveElement()
{}


//------------------------------------------------------------
CATImplementClass(CAASurfaceToSewFieldActivate,Implementation,CATNotification,CATNull);
CAASurfaceToSewFieldActivate::CAASurfaceToSewFieldActivate()
{}
CAASurfaceToSewFieldActivate::~CAASurfaceToSewFieldActivate()
{}

//------------------------------------------------------------
CATImplementClass(CAASupportFieldActivate,Implementation,CATNotification,CATNull);
CAASupportFieldActivate::CAASupportFieldActivate()
{}
CAASupportFieldActivate::~CAASupportFieldActivate()
{}

//------------------------------------------------------------
CATImplementClass(CAAInvertOrientation,Implementation,CATNotification,CATNull);
CAAInvertOrientation::CAAInvertOrientation() 
{}
CAAInvertOrientation::~CAAInvertOrientation()
{}

