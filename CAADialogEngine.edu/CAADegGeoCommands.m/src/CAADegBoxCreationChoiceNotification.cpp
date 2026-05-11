// COPYRIGHT DASSAULT SYSTEMES 2003

// Local Framework
#include "CAADegBoxCreationChoiceNotification.h"

// To declare that the class is a component main class
CATImplementClass(CAADegBoxCreationChoiceNotification,Implementation,CATNotification,CATNull);

// The CATNotification base class constructor is called with the
// CATNotificationDeleteOn parameter to state that we want this
// notification to be automatically deleted at the end of the next transaction,
// that is, as soon as the dialog between sending and receiving commands
// is completed.

CAADegBoxCreationChoiceNotification::CAADegBoxCreationChoiceNotification()
                        : CATNotification(CATNotificationDeleteOn)
{
    _ChoiceValue = 0 ;
}

CAADegBoxCreationChoiceNotification::~CAADegBoxCreationChoiceNotification()
{
}

HRESULT CAADegBoxCreationChoiceNotification::SetChoice(int iChoiceValue )
{
    _ChoiceValue = iChoiceValue;
       
    return S_OK ;
}

HRESULT CAADegBoxCreationChoiceNotification::GetChoice(int & oChoiceValue )
{
    HRESULT rc = E_FAIL ;
    oChoiceValue =  _ChoiceValue ;
    if ( 0 != _ChoiceValue )
    {
       rc = S_OK ;
    }
    return rc ;
}

