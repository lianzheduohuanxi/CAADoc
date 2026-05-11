#ifndef CAAEMmrCCDataExtensionFactory_H
#define CAAEMmrCCDataExtensionFactory_H

// COPYRIGHT DASSAULT SYSTEMES 2007

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

class CAAIMmrCCDataExtension;

/**
 * Class extending the CATPrtCont object: The container of specifications
 * in the Part document.
 *
 * It implements the interfaces :
 *      CAAMechanicalModeler.edu.CAAIMmrCCDataExtensionFactory
 */

class CAAEMmrCCDataExtensionFactory: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEMmrCCDataExtensionFactory ();
    virtual ~CAAEMmrCCDataExtensionFactory ();

    /**
    * Implements the method CreateMmrCCDataExtension of the interface CAAIMmrCCDataExtensionFactory
    * see CAAMechanicalModeler.edu.CAAIMmrCCDataExtensionFactory.CreateMmrCCDataExtension
    */
    HRESULT CreateMmrCCDataExtension(const CATBaseUnknown *iBaseFeature,
                                     CAAIMmrCCDataExtension **ioMmrCCDataExtension);
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrCCDataExtensionFactory (CAAEMmrCCDataExtensionFactory &);
    CAAEMmrCCDataExtensionFactory& operator=(CAAEMmrCCDataExtensionFactory&);
    
};


#endif
