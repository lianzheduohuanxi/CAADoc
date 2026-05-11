#ifndef CAAEV5V6ExtMmrMultiMeasureEdit_H
#define CAAEV5V6ExtMmrMultiMeasureEdit_H

// COPYRIGHT DASSAULT SYSTEMES 2012

// System Framework
#include "CATExtIEdit.h"  // To derive from 

/**
* Class extending the object "CAAV5V6ExtMmrMultiMeasure".
* It implements the interfaces :
*      ApplicationFrame.CATIEdit
*         This interface is called when editing a CAAV5V6ExtMmrMultiMeasure.
*/

class CAAEV5V6ExtMmrMultiMeasureEdit: public CATExtIEdit
{
    CATDeclareClass;
    
public:
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEV5V6ExtMmrMultiMeasureEdit();
    virtual ~CAAEV5V6ExtMmrMultiMeasureEdit();
    
    /**
    * Implements the method Activate of the interface CATIEdit
    * see ApplicationFrame.CATIEdit.Activate
    */
    CATCommand* Activate (CATPathElement *ipPath) ;
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEV5V6ExtMmrMultiMeasureEdit (CAAEV5V6ExtMmrMultiMeasureEdit & iObjectToCopy);
    CAAEV5V6ExtMmrMultiMeasureEdit& operator = ( CAAEV5V6ExtMmrMultiMeasureEdit & iObjectToCopy);   
};
#endif
