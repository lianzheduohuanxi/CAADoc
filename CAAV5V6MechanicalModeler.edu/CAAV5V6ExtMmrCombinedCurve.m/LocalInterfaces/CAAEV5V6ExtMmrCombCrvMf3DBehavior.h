#ifndef CAAEV5V6ExtMmrCombCrvMf3DBehavior_H
#define CAAEV5V6ExtMmrCombCrvMf3DBehavior_H

// COPYRIGHT DASSAULT SYSTEMES 2012

// System Framework
#include "CATBaseUnknown.h" 

// CATMecModExtendItf
#include "CATMf3DBehaviorAdapter.h"

class CAAEV5V6ExtMmrCombCrvMf3DBehavior: public CATMf3DBehaviorAdapter
{
    CATDeclareClass;
    
public:
     
    CAAEV5V6ExtMmrCombCrvMf3DBehavior ();
    virtual ~CAAEV5V6ExtMmrCombCrvMf3DBehavior ();
    
    virtual HRESULT IsAShape() const ;

private:

    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEV5V6ExtMmrCombCrvMf3DBehavior (CAAEV5V6ExtMmrCombCrvMf3DBehavior &iObjectToCopy);
    CAAEV5V6ExtMmrCombCrvMf3DBehavior& operator=(CAAEV5V6ExtMmrCombCrvMf3DBehavior &iObjectToCopy);
    
};

#endif
