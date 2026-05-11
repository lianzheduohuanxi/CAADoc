// COPYRIGHT DASSAULT SYSTEMES 2012

#ifndef CAAEV5V6ExtMmrCombinedCurve_H
#define CAAEV5V6ExtMmrCombinedCurve_H


// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

// FeatureModelerExt Framework
#include "CATFmCredentials.h"


/**
 * Class extending the object "V5V6ExtCombinedCurve".
 *  
 * It implements the interface :
 *      CAAV5V6MechanicalModeler.edu.CAAIV5V6ExtMmrCombinedCurve
 */

class CAAEV5V6ExtMmrCombinedCurve: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEV5V6ExtMmrCombinedCurve ();
    virtual ~CAAEV5V6ExtMmrCombinedCurve ();
    
    /**
    * Implements the method SetCurve of the interface CAAIV5V6ExtMmrCombinedCurve.
    * see CAAV5V6MechanicalModeler.edu.CAAIV5V6ExtMmrCombinedCurve.SetCurve
    */
    HRESULT SetCurve(int iNum, CATBaseUnknown *ipCurve);
    
    /**
    * Implements the method GetCurve of the interface CAAIV5V6ExtMmrCombinedCurve.
    * see CAAV5V6MechanicalModeler.edu.CAAIV5V6ExtMmrCombinedCurve.GetCurve
    */
    HRESULT GetCurve(int iNum, CATBaseUnknown *&opCurve);
    
    /**
    * Implements the method SetDirection of the interface CAAIV5V6ExtMmrCombinedCurve.
    * see CAAV5V6MechanicalModeler.edu.CAAIV5V6ExtMmrCombinedCurve.SetDirection
    */
    HRESULT SetDirection(int iNum, CATBaseUnknown *ipDirection);
    
    /**
    * Implements the method GetDirection of the interface CAAIV5V6ExtMmrCombinedCurve.
    * see CAAV5V6MechanicalModeler.edu.CAAIV5V6ExtMmrCombinedCurve.GetDirection
    */
    HRESULT GetDirection(int iNum, CATBaseUnknown *&opDirection);
    

    
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEV5V6ExtMmrCombinedCurve (CAAEV5V6ExtMmrCombinedCurve &);
    CAAEV5V6ExtMmrCombinedCurve& operator=(CAAEV5V6ExtMmrCombinedCurve&);
    
     CATFmCredentials _CredentialForCC;

};

#endif
