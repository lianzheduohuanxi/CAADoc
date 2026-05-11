#ifndef CAAEV5V6ExtMmrMultiMeasureFactory_H
#define CAAEV5V6ExtMmrMultiMeasureFactory_H

// COPYRIGHT DASSAULT SYSTEMES 2012

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown


/**
 * Class extending the CATPrtCont object: The container of specifications
 * in the Part document.
 *
 * It implements the interfaces :
 *      CAAMechanicalModeler.edu.CAAIMmrMultiMeasureAndMeasureSetFactory
 */

class CAAEV5V6ExtMmrMultiMeasureFactory: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEV5V6ExtMmrMultiMeasureFactory ();
    virtual ~CAAEV5V6ExtMmrMultiMeasureFactory ();

    /**
    * Implements the method CreateMmrMultiMeasureAndMeasureSet of the interface CAAIMmrMultiMeasureAndMeasureSetFactory
    * see CAAMechanicalModeler.edu.CAAIMmrMultiMeasureAndMeasureSetFactory.CreateMmrMultiMeasure
    */
    HRESULT CreateMmrMultiMeasure(CATBaseUnknown *ipGeometricalElementToMesure ,
                                  CATBaseUnknown *&opMultiMeasureInstance);
   
    /**
    * Implements the method CreateMmrMultiMeasureAndMeasureSet of the interface CAAIMmrMultiMeasureAndMeasureSetFactory
    * see CAAMechanicalModeler.edu.CAAIMmrMultiMeasureAndMeasureSetFactory.CreateMmrMultiMeasure
    */
    HRESULT CreateMmrMeasureSet(CATBaseUnknown *&opMeasureSetInstance);

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEV5V6ExtMmrMultiMeasureFactory (CAAEV5V6ExtMmrMultiMeasureFactory &);
    CAAEV5V6ExtMmrMultiMeasureFactory& operator=(CAAEV5V6ExtMmrMultiMeasureFactory&);
    
};


#endif
