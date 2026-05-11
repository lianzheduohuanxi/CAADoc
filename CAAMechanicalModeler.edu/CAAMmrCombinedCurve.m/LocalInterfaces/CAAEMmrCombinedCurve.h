#ifndef CAAEMmrCombinedCurve_H
#define CAAEMmrCombinedCurve_H
// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

class CATISpecObject;

/**
 * Class extending the object "CombinedCurve".
 *  
 * It implements the interface :
 *      CAAMechanicalModeler.edu.CAAIMmrCombinedCurve
 */

class CAAEMmrCombinedCurve: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEMmrCombinedCurve ();
    virtual ~CAAEMmrCombinedCurve ();
    
    /**
    * Implements the method SetCurve of the interface CAAMmrCombinedCurve.
    * see CAAMechanicalModeler.edu.CAAIMmrCombinedCurve.SetCurve
    */
    HRESULT SetCurve ( int iNum , CATISpecObject *ipiSpecOnCurve ) ;
    
    /**
    * Implements the method GetCurve of the interface CAAMmrCombinedCurve.
    * see CAAMechanicalModeler.edu.CAAIMmrCombinedCurve.GetCurve
    */
    HRESULT GetCurve ( int iNum , CATISpecObject **opiSpecOnCurve )  ;
    
    /**
    * Implements the method SetDirection of the interface CAAMmrCombinedCurve.
    * see CAAMechanicalModeler.edu.CAAIMmrCombinedCurve.SetDirection
    */
    HRESULT SetDirection ( int iNum , CATISpecObject *ipiSpecOnDirection )  ;
    
    /**
    * Implements the method GetDirection of the interface CAAMmrCombinedCurve.
    * see CAAMechanicalModeler.edu.CAAIMmrCombinedCurve.GetDirection
    */
    HRESULT GetDirection ( int iNum , CATISpecObject **opiSpecOnDirection ) ;
    

    
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrCombinedCurve (CAAEMmrCombinedCurve &);
    CAAEMmrCombinedCurve& operator=(CAAEMmrCombinedCurve&);
    
};

#endif
