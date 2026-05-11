// =========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2006
// =========================================================================
// CATIA Shape Design And Styling 
//---------------------------------------------------------------------
// Responsable: BIW
//---------------------------------------------------------------------
// CAAGSMCircleSweepTgUINotifications
//---------------------------------------------------------------------
// 
//  Circle Sweep tangent command notifications  
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 05/xx/xx > PEY 
//---------------------------------------------------------------------

#include "CAAGSMCircleSweepTgUINotifications.h"


 // needed to Clear Selection
//--------------------------------------------------------------

CATImplementClass(CAACircleSweepTgUIRemoveElement,Implementation,CATNotification,CATNull);
CAACircleSweepTgUIRemoveElement::CAACircleSweepTgUIRemoveElement()
{
}
CAACircleSweepTgUIRemoveElement::~CAACircleSweepTgUIRemoveElement()
{}


//------------------------------------------------------------
CATImplementClass(CAACircleSweepTgUICurveRefFieldActivate,Implementation,CATNotification,CATNull);
CAACircleSweepTgUICurveRefFieldActivate::CAACircleSweepTgUICurveRefFieldActivate()
{}
CAACircleSweepTgUICurveRefFieldActivate::~CAACircleSweepTgUICurveRefFieldActivate()
{}

//------------------------------------------------------------
CATImplementClass(CAACircleSweepTgUISupportFieldActivate,Implementation,CATNotification,CATNull);
CAACircleSweepTgUISupportFieldActivate::CAACircleSweepTgUISupportFieldActivate()
{}
CAACircleSweepTgUISupportFieldActivate::~CAACircleSweepTgUISupportFieldActivate()
{}

//------------------------------------------------------------
CATImplementClass(CAACircleSweepTgUIInvertOrientation,Implementation,CATNotification,CATNull);
CAACircleSweepTgUIInvertOrientation::CAACircleSweepTgUIInvertOrientation() 
{}
CAACircleSweepTgUIInvertOrientation::~CAACircleSweepTgUIInvertOrientation()
{}

//------------------------------------------------------------
CATImplementClass(CAACircleSweepTgUIValueChanged,Implementation,CATNotification,CATNull);
CAACircleSweepTgUIValueChanged::CAACircleSweepTgUIValueChanged()
{}
CAACircleSweepTgUIValueChanged::~CAACircleSweepTgUIValueChanged()
{}

//------------------------------------------------------------
CATImplementClass(CAACircleSweepTgUITrimChanged,Implementation,CATNotification,CATNull);
CAACircleSweepTgUITrimChanged::CAACircleSweepTgUITrimChanged()
{}
CAACircleSweepTgUITrimChanged::~CAACircleSweepTgUITrimChanged()
{}
