#ifndef CAAEMmrCombCrvMf3DBehavior_H
#define CAAEMmrCombCrvMf3DBehavior_H
// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATBaseUnknown.h" // needed to derive from

class CAAEMmrCombCrvMf3DBehavior: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
     
    CAAEMmrCombCrvMf3DBehavior ();
    virtual ~CAAEMmrCombCrvMf3DBehavior ();
    
    virtual HRESULT IsASolid() const ;
    virtual HRESULT IsAShape() const ;
    virtual HRESULT IsADatum() const ;

private:

    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrCombCrvMf3DBehavior (CAAEMmrCombCrvMf3DBehavior &iObjectToCopy);
    CAAEMmrCombCrvMf3DBehavior& operator=(CAAEMmrCombCrvMf3DBehavior &iObjectToCopy);
    
};

#endif
