#ifndef CAAEMmrMultiMeasureEdit_H
#define CAAEMmrMultiMeasureEdit_H

// COPYRIGHT DASSAULT SYSTEMES 2007

// System Framework
#include "CATExtIEdit.h"  // To derive from 

/**
* Class extending the object "CAAMultiMeasure".
* It implements the interfaces :
*      ApplicationFrame.CATIEdit
*         This interface is called when editing a CAAMmrMultiMeasure.
*/

class CAAEMmrMultiMeasureEdit: public CATExtIEdit
{
    CATDeclareClass;
    
public:
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEMmrMultiMeasureEdit();
    virtual ~CAAEMmrMultiMeasureEdit();
    
    /**
    * Implements the method Activate of the interface CATIEdit
    * see ApplicationFrame.CATIEdit.Activate
    */
    CATCommand* Activate (CATPathElement *ipPath) ;
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrMultiMeasureEdit (CAAEMmrMultiMeasureEdit & iObjectToCopy);
    CAAEMmrMultiMeasureEdit& operator = ( CAAEMmrMultiMeasureEdit & iObjectToCopy);   
};
#endif
