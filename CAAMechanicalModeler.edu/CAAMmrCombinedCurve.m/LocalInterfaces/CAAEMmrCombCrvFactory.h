#ifndef CAAEMmrCombCrvFactory_H
#define CAAEMmrCombCrvFactory_H
// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

class CATISpecObject;

/**
 * Class extending the CATPrtCont object: The container of specifications
 * in the Part document.
 *
 * It implements the interfaces :
 *      CAAMechanicalModeler.edu.CAAIMmrCombCrvFactory
 */

class CAAEMmrCombCrvFactory: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEMmrCombCrvFactory ();
    virtual ~CAAEMmrCombCrvFactory ();

    /**
    * Implements the method CreateCombinedCurve of the interface CAAIMmrCombCrvFactory
    * see CAAMechanicalModeler.edu.CAAIMmrCombCrvFactory.CreateCombinedCurve
    */
    HRESULT CreateCombinedCurve ( CATISpecObject *ipiSpecOnCurve1,
                                 CATISpecObject *ipiSpecOnDirection1,
                                 CATISpecObject *ipiSpecOnCurve2,
                                 CATISpecObject *ipiSpecOnDirection2,
                                 CATISpecObject **opiSpecOnCombinedCurve );
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrCombCrvFactory (CAAEMmrCombCrvFactory &);
    CAAEMmrCombCrvFactory& operator=(CAAEMmrCombCrvFactory&);
    
};


#endif
