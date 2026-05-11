#ifndef CAAGSMCircleSweepTgUINotifications_H
#define CAAGSMCircleSweepTgUINotifications_H
//---------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2005
//---------------------------------------------------------------------
// Shape Design And Styling 
//---------------------------------------------------------------------
// Responsable: BIW
//---------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd
//---------------------------------------------------------------------
// 
//  Circle Sweep tangent command / Notification definitions 
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 05/xx/xx > PEY 
//---------------------------------------------------------------------
#include "CATNotification.h"
#include "CATLISTV_CATISpecObject.h"

/**
* Class defining all the notifications used by the command and the dialog panel of Sew Skin .
*	
* refer to programming resources of Dialog framework.
* (consult base class description).
*/


class CAACircleSweepTgUIRemoveElement : public CATNotification
{
public:
	CATDeclareClass;
    CAACircleSweepTgUIRemoveElement();
    virtual ~CAACircleSweepTgUIRemoveElement();
};


class CAACircleSweepTgUICurveRefFieldActivate : public CATNotification
{
public:
	CATDeclareClass;
    CAACircleSweepTgUICurveRefFieldActivate();
    virtual ~CAACircleSweepTgUICurveRefFieldActivate();
};

class CAACircleSweepTgUISupportFieldActivate : public CATNotification
{
public:
	CATDeclareClass;
    CAACircleSweepTgUISupportFieldActivate();
    virtual ~CAACircleSweepTgUISupportFieldActivate();
};


class CAACircleSweepTgUIInvertOrientation : public CATNotification
{
 public:
    CATDeclareClass;
    CAACircleSweepTgUIInvertOrientation ();
    virtual ~ CAACircleSweepTgUIInvertOrientation ();
};


class CAACircleSweepTgUIValueChanged : public CATNotification
{
 public:
    CATDeclareClass;
    CAACircleSweepTgUIValueChanged ();
    virtual ~ CAACircleSweepTgUIValueChanged ();
};


class CAACircleSweepTgUITrimChanged : public CATNotification
{
 public:
    CATDeclareClass;
    CAACircleSweepTgUITrimChanged ();
    virtual ~ CAACircleSweepTgUITrimChanged ();
};

#endif
