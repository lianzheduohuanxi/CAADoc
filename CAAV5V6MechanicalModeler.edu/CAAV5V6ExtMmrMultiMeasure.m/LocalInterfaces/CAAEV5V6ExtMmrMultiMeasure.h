#ifndef CAAEV5V6ExtMmrMultiMeasure_H
#define CAAEV5V6ExtMmrMultiMeasure_H

// COPYRIGHT DASSAULT SYSTEMES 2012

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

// FeatureModelerExt
#include "CATFmCredentials.h"

class CATISpecObject;
class CATICkeParm_var ;

/**
 * Class extending the object "V5V6ExtMmrMultiMeasure".
 *  
 * It implements the interface :
 *      CAAIV5V6ExtMmrMultiMeasure
 */

class CAAEV5V6ExtMmrMultiMeasure: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEV5V6ExtMmrMultiMeasure ();
    virtual ~CAAEV5V6ExtMmrMultiMeasure ();
    
    /**
    * Implements the method SetInputGeomFeature of the interface CAAIMmrMultiMeasure.
    */
    HRESULT SetInputGeomFeature (CATBaseUnknown * ipGeomFeature );
    
    /**
    * Implements the method GetGeomFeature of the interface CAAIMmrMultiMeasure.
    */
    HRESULT GetGeomFeature (CATBaseUnknown *&oGeomFeature );

    /**
    * Implements the method GetLengthParameter of the interface CAAIMmrMultiMeasure.
    */
	  HRESULT GetLengthParameter (CATICkeParm_var &oLengthParm) ;

    /**
    * Implements the method GetWetAreaParameter of the interface CAAIMmrMultiMeasure.
    */
    HRESULT GetWetAreaParameter (CATICkeParm_var &oWetAreaParm) ;

    /**
    * Implements the method GetVolumeParameter of the interface CAAIMmrMultiMeasure.
    */
    HRESULT GetVolumeParameter (CATICkeParm_var &oVolumeParm) ;
            
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEV5V6ExtMmrMultiMeasure (CAAEV5V6ExtMmrMultiMeasure &);
    CAAEV5V6ExtMmrMultiMeasure& operator=(CAAEV5V6ExtMmrMultiMeasure&);
    
    CATFmCredentials _CredentialForMultiMeasure;
};

#endif
