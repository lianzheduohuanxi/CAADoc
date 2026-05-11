#ifndef CAAEV5V6ExtMmrCCDataExtension_H
#define CAAEV5V6ExtMmrCCDataExtension_H
// COPYRIGHT DASSAULT SYSTEMES 2012

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

// FeatureModelerExt Framework
#include "CATFmCredentials.h"

class CATICkeParm_var;

/**
 * Class extending the object "V5V6ExtMmrCCDataExtension".
 *  
 * It implements the interface :
 *      CAAV5V6MechanicalModeler.edu.CAAIV5V6ExtMmrCCDataExtension
 */

class CAAEV5V6ExtMmrCCDataExtension: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEV5V6ExtMmrCCDataExtension ();
    virtual ~CAAEV5V6ExtMmrCCDataExtension ();
    
    /**
    * Implements the method SetGeomFeature of the interface CAAIV5V6ExtMmrCCDataExtension.
    * see CAAV5V6MechanicalModeler.edu.CAAIMmrCCDataExtension.SetGeomFeature
    */
    HRESULT SetGeomFeature (CATBaseUnknown * ipGeomFeature );
    
    /**
    * Implements the method GetGeomFeature of the interface CAAIV5V6ExtMmrCCDataExtension.
    * see CAAV5V6MechanicalModeler.edu.CAAIMmrCCDataExtension.GetGeomFeature
    */
    HRESULT GetGeomFeature (CATBaseUnknown *&opGeomFeature );
    
    /**
    * Implements the method AggregateParam of the interface CAAIV5V6ExtMmrCCDataExtension.
    * see CAAV5V6MechanicalModeler.edu.CAAIMmrCCDataExtension.AggregateParam
    */
    HRESULT AggregateParam (CATICkeParm_var ispParmToAggregate);
    
    /**
    * Implements the method GetValuatedParam of the interface CAAIV5V6ExtMmrCCDataExtension.
    * see CAAV5V6MechanicalModeler.edu.CAAIMmrCCDataExtension.GetValuatedParam
    */
    HRESULT GetValuatedParam (CATICkeParm_var& iospValuatedParm);
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEV5V6ExtMmrCCDataExtension (CAAEV5V6ExtMmrCCDataExtension &);
    CAAEV5V6ExtMmrCCDataExtension& operator=(CAAEV5V6ExtMmrCCDataExtension&);

    CATFmCredentials _CredentialForDataExt;
};

#endif
