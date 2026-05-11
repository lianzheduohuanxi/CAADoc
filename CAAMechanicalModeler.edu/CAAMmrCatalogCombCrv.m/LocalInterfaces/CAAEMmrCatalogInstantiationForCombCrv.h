#ifndef CAAEMmrCatalogInstantiationForCombCrv_H
#define CAAEMmrCatalogInstantiationForCombCrv_H

// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATBaseUnknown.h"  // To derive from 
class CATICatalogLink;
class CATICatalogBrowser ;

/**
* Class extending the object "CombinedCurve".
* It implements the interface :
*      ComponentsCatalogsInterfaces.CATICatalogInstantiation
*/

class CAAEMmrCatalogInstantiationForCombCrv: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEMmrCatalogInstantiationForCombCrv ();
    virtual ~CAAEMmrCatalogInstantiationForCombCrv ();
    
    virtual HRESULT RunInstantiationCmd (const CATICatalogLink    * ipCatalogLink,
                                       const CATICatalogBrowser * ipBrowser,
                                       int iInstantiateMode,
                                       int iRepeatMode,
                                       int & oNotDone) ;
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrCatalogInstantiationForCombCrv (CAAEMmrCatalogInstantiationForCombCrv & iObjectToCopy);
    CAAEMmrCatalogInstantiationForCombCrv& operator=(CAAEMmrCatalogInstantiationForCombCrv & iObjectToCopy);
    
};


#endif
