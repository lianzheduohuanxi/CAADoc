#ifndef CAAEV5V6ExtMmrCombCrvFactory_H
#define CAAEV5V6ExtMmrCombCrvFactory_H

// COPYRIGHT DASSAULT SYSTEMES 2012

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

class CAAIV5V6ExtMmrCombinedCurve;

/**
 * Class extending the CATPrtCont object: The container of specifications
 * in the Part document.
 *
 * It implements the interfaces :
 *      CAAV5V6MechanicalModeler.edu.CAAIV5V6ExtMmrCombCrvFactory
 */

class CAAEV5V6ExtMmrCombCrvFactory: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEV5V6ExtMmrCombCrvFactory ();
    virtual ~CAAEV5V6ExtMmrCombCrvFactory ();

    /**
    * Implements the method CreateCombinedCurve of the interface CAAIMmrCombCrvFactory
    * see CAAMechanicalModeler.edu.CAAIMmrCombCrvFactory.CreateCombinedCurve
    */
    HRESULT CreateCombinedCurve ( CATBaseUnknown *ipCurve1,
                                  CATBaseUnknown *ipDirection1,
                                  CATBaseUnknown *ipCurve2,
                                  CATBaseUnknown *ipDirection2,
                                  CAAIV5V6ExtMmrCombinedCurve *& opCombinedCurve );
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEV5V6ExtMmrCombCrvFactory (CAAEV5V6ExtMmrCombCrvFactory &);
    CAAEV5V6ExtMmrCombCrvFactory& operator=(CAAEV5V6ExtMmrCombCrvFactory&);
    
};


#endif
