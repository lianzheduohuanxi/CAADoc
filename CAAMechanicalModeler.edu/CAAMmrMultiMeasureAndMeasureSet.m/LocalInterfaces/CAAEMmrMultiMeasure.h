#ifndef CAAEMmrMultiMeasure_H
#define CAAEMmrMultiMeasure_H
// COPYRIGHT DASSAULT SYSTEMES 2007

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

class CATISpecObject;
class CATICkeParm_var ;

/**
 * Class extending the object "MmrMultiMeasure".
 *  
 * It implements the interface :
 *      CAAMechanicalModeler.edu.CAAIMmrMultiMeasure
 */

class CAAEMmrMultiMeasure: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEMmrMultiMeasure ();
    virtual ~CAAEMmrMultiMeasure ();
    
    /**
    * Implements the method SetGeomFeature of the interface CAAMmrMultiMeasure.
    * see CAAMechanicalModeler.edu.CAAIMmrMultiMeasure.SetInputGeomFeature
    */
    HRESULT SetInputGeomFeature (CATBaseUnknown * ipGeomFeature );
    
    /**
    * Implements the method GetGeomFeature of the interface CAAMmrMultiMeasure.
    * see CAAMechanicalModeler.edu.CAAIMmrMultiMeasure.GetGeomFeature
    */
    HRESULT GetGeomFeature (CATISpecObject **ioGeomFeature );
            
	 HRESULT GetLengthParameter (CATICkeParm_var &oLengthParm) ;
    HRESULT GetWetAreaParameter (CATICkeParm_var &oWetAreaParm) ;
    HRESULT GetVolumeParameter (CATICkeParm_var &oVolumeParm) ;
            
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrMultiMeasure (CAAEMmrMultiMeasure &);
    CAAEMmrMultiMeasure& operator=(CAAEMmrMultiMeasure&);
    
};

#endif
