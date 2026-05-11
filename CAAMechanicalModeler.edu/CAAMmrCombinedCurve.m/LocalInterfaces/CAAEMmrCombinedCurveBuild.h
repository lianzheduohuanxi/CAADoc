#ifndef CAAEMmrCombinedCurveBuild_H
#define CAAEMmrCombinedCurveBuild_H
// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

class CATISpecObject;

/**
 * Class extending the object "CombinedCurve".
 *  
 * It implements the interfaces :
 *       ObjectSpecsModeler.CATIBuild
 */

class CAAEMmrCombinedCurveBuild: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEMmrCombinedCurveBuild ();
    virtual ~CAAEMmrCombinedCurveBuild ();
    
    /**
    * Implements the method build of the interface CATIBuild.
    * see ObjectSpecsModeler.CATIBuild.Build
    */
    HRESULT Build () ;
    
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrCombinedCurveBuild (CAAEMmrCombinedCurveBuild &);
    CAAEMmrCombinedCurveBuild& operator=(CAAEMmrCombinedCurveBuild&);
    
};

#endif
