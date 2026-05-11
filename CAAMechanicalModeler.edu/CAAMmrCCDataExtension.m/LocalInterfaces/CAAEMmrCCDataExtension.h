#ifndef CAAEMmrCCDataExtension_H
#define CAAEMmrCCDataExtension_H
// COPYRIGHT DASSAULT SYSTEMES 2007

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

class CATISpecObject;
class CATICkeParm_var;

/**
 * Class extending the object "MmrCCDataExtension".
 *  
 * It implements the interface :
 *      CAAMechanicalModeler.edu.CAAIMmrCCDataExtension
 */

class CAAEMmrCCDataExtension: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEMmrCCDataExtension ();
    virtual ~CAAEMmrCCDataExtension ();
    
    /**
    * Implements the method SetGeomFeature of the interface CAAMmrCCDataExtension.
    * see CAAMechanicalModeler.edu.CAAIMmrCCDataExtension.SetGeomFeature
    */
    HRESULT SetGeomFeature (const CATBaseUnknown * ipGeomFeature );
    
    /**
    * Implements the method GetGeomFeature of the interface CAAMmrCCDataExtension.
    * see CAAMechanicalModeler.edu.CAAIMmrCCDataExtension.GetGeomFeature
    */
    HRESULT GetGeomFeature (CATISpecObject **ioGeomFeature );
    
    /**
    * Implements the method AggregateParam of the interface CAAMmrCCDataExtension.
    * see CAAMechanicalModeler.edu.CAAIMmrCCDataExtension.AggregateParam
    */
    HRESULT AggregateParam (CATICkeParm_var ispParmToAggregate);
    
    /**
    * Implements the method GetValuatedParam of the interface CAAMmrCCDataExtension.
    * see CAAMechanicalModeler.edu.CAAIMmrCCDataExtension.GetValuatedParam
    */
    HRESULT GetValuatedParam (CATICkeParm_var& iospValuatedParm);
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrCCDataExtension (CAAEMmrCCDataExtension &);
    CAAEMmrCCDataExtension& operator=(CAAEMmrCCDataExtension&);
    
};

#endif
