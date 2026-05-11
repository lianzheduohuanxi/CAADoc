#ifndef CAAEMmrCCDataExtensionBuild_H
#define CAAEMmrCCDataExtensionBuild_H
// COPYRIGHT DASSAULT SYSTEMES 2007

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

class CATISpecObject;
class CATUnicodeString;

/**
 * Class extending the object "MmrCCDataExtension".
 *  
 * It implements the interfaces :
 *       ObjectSpecsModeler.CATIBuild
 */

class CAAEMmrCCDataExtensionBuild: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEMmrCCDataExtensionBuild ();
    virtual ~CAAEMmrCCDataExtensionBuild ();
    
    /**
    * Implements the method build of the interface CATIBuild.
    * see ObjectSpecsModeler.CATIBuild.Build
    */
    HRESULT Build () ;
    
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrCCDataExtensionBuild (CAAEMmrCCDataExtensionBuild &);
    CAAEMmrCCDataExtensionBuild& operator=(CAAEMmrCCDataExtensionBuild&);

    void RaiseAnError(CATUnicodeString& ErrorLabel, CATISpecObject *iAssociatedFeature);
};

#endif
