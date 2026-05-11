#ifndef CAAGSMSewSkinBasicUINotifications_H
#define CAAGSMSewSkinBasicUINotifications_H
//---------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2005
//---------------------------------------------------------------------
// CATIA Shape Design And Styling 
//---------------------------------------------------------------------
//
// CAAGSMSewSkinBasicUINotifications
//---------------------------------------------------------------------
// 
//  Sew Skin Basic notifications 
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


class CAAGSMSewSkinBasicUIRemoveElement : public CATNotification
{
public:
	CATDeclareClass;
    CAAGSMSewSkinBasicUIRemoveElement();
    virtual ~CAAGSMSewSkinBasicUIRemoveElement();
};


class CAASurfaceToSewFieldActivate : public CATNotification
{
public:
	CATDeclareClass;
    CAASurfaceToSewFieldActivate();
    virtual ~CAASurfaceToSewFieldActivate();
};

class CAASupportFieldActivate : public CATNotification
{
public:
	CATDeclareClass;
    CAASupportFieldActivate();
    virtual ~CAASupportFieldActivate();
};


class CAAInvertOrientation : public CATNotification
{
 public:
    CATDeclareClass;
    CAAInvertOrientation ();
    virtual ~ CAAInvertOrientation ();
};


#endif
