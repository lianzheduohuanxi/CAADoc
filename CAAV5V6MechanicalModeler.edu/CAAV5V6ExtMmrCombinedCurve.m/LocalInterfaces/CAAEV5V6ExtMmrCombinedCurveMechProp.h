#ifndef CAAEV5V6ExtMmrCombinedCurveMechProp_H
#define CAAEV5V6ExtMmrCombinedCurveMechProp_H

// COPYRIGHT DASSAULT SYSTEMES 2012

// System Framework
#include "CATBaseUnknown.h" 

class CAAEV5V6ExtMmrCombinedCurveMechProp: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
     
    CAAEV5V6ExtMmrCombinedCurveMechProp ();
    virtual ~CAAEV5V6ExtMmrCombinedCurveMechProp ();
    
    virtual int IsInactive() const ;
    virtual void Activate() ;
    virtual void InActivate() ;

private:

    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEV5V6ExtMmrCombinedCurveMechProp (CAAEV5V6ExtMmrCombinedCurveMechProp &iObjectToCopy);
    CAAEV5V6ExtMmrCombinedCurveMechProp& operator=(CAAEV5V6ExtMmrCombinedCurveMechProp &iObjectToCopy);
    
    /**
    * Refresh CombinedCurve for activation/desactivation
    */
    HRESULT RefreshCombinedCurve();
    HRESULT ReadStatus();

    int _status;
};

#endif
