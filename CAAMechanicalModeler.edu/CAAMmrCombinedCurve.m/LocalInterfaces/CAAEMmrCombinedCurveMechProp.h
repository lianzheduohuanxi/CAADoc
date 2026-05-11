#ifndef CAAEMmrCombinedCurveMechProp_H
#define CAAEMmrCombinedCurveMechProp_H
// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATBaseUnknown.h" // needed to derive from

class CAAEMmrCombinedCurveMechProp: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
     
    CAAEMmrCombinedCurveMechProp ();
    virtual ~CAAEMmrCombinedCurveMechProp ();
    
    virtual int IsInactive() const ;
    virtual void Activate() ;
    virtual void InActivate() ;

private:

    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrCombinedCurveMechProp (CAAEMmrCombinedCurveMechProp &iObjectToCopy);
    CAAEMmrCombinedCurveMechProp& operator=(CAAEMmrCombinedCurveMechProp &iObjectToCopy);
    
private:
    int _status ;
};

#endif
