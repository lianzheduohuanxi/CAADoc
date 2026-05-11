#ifndef CAAEMmrMultiMeasureAndMeasureSetFactory_H
#define CAAEMmrMultiMeasureAndMeasureSetFactory_H

// COPYRIGHT DASSAULT SYSTEMES 2007

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

class CAAIMmrMultiMeasureAndMeasureSet;
class CATISpecObject;
/**
 * Class extending the CATPrtCont object: The container of specifications
 * in the Part document.
 *
 * It implements the interfaces :
 *      CAAMechanicalModeler.edu.CAAIMmrMultiMeasureAndMeasureSetFactory
 */

class CAAEMmrMultiMeasureAndMeasureSetFactory: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEMmrMultiMeasureAndMeasureSetFactory ();
    virtual ~CAAEMmrMultiMeasureAndMeasureSetFactory ();

    /**
    * Implements the method CreateMmrMultiMeasureAndMeasureSet of the interface CAAIMmrMultiMeasureAndMeasureSetFactory
    * see CAAMechanicalModeler.edu.CAAIMmrMultiMeasureAndMeasureSetFactory.CreateMmrMultiMeasure
    */
    HRESULT CreateMmrMultiMeasure(CATBaseUnknown *ipGeometricalElementToMesure ,
                                  CATISpecObject **opMultiMeasureInstance );
   
    /**
    * Implements the method CreateMmrMultiMeasureAndMeasureSet of the interface CAAIMmrMultiMeasureAndMeasureSetFactory
    * see CAAMechanicalModeler.edu.CAAIMmrMultiMeasureAndMeasureSetFactory.CreateMmrMultiMeasure
    */
    HRESULT CreateMmrMeasureSet(CATISpecObject **opMeasureSetInstance);

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrMultiMeasureAndMeasureSetFactory (CAAEMmrMultiMeasureAndMeasureSetFactory &);
    CAAEMmrMultiMeasureAndMeasureSetFactory& operator=(CAAEMmrMultiMeasureAndMeasureSetFactory&);
    
};


#endif
