#ifndef CAAEMmrCatalogEnableForCombCrv_H
#define CAAEMmrCatalogEnableForCombCrv_H

// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATBaseUnknown.h"  // To derive from 

/**
* Class extending the object "CombinedCurve".
* It implements the interface :
*      ComponentsCatalogsInterfaces.CATICatalogEnable
*/

class CAAEMmrCatalogEnableForCombCrv: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEMmrCatalogEnableForCombCrv ();
    virtual ~CAAEMmrCatalogEnableForCombCrv ();
    
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrCatalogEnableForCombCrv (CAAEMmrCatalogEnableForCombCrv & iObjectToCopy);
    CAAEMmrCatalogEnableForCombCrv& operator=(CAAEMmrCatalogEnableForCombCrv & iObjectToCopy);
    
};


#endif
