#ifndef CAAEV5V6ExtMmrCombinedCurveEdit_H
#define CAAEV5V6ExtMmrCombinedCurveEdit_H

// COPYRIGHT DASSAULT SYSTEMES 2012

#include "CATExtIEdit.h"  // To derive from 

/**
* Class extending the object "CombinedCurve".
* It implements the interfaces :
*      ApplicationFrame.CATIEdit
*         This interface is called when editing a Combined Curve.
*         It associates a dialog panel and fill in the contextual menu of the Combined Curve.
*
*/
// Note : CAAEV5V6ExtMmrCombinedCurveEdit is the same use case as CAAMmrCombinedCurveEdit. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.


class CAAEV5V6ExtMmrCombinedCurveEdit: public CATExtIEdit
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEV5V6ExtMmrCombinedCurveEdit ();
    virtual ~CAAEV5V6ExtMmrCombinedCurveEdit ();
    
    /**
    * Implements the method Activate of the interface CATIEdit
    * see ApplicationFrame.CATIEdit.Activate
    */
    CATCommand* Activate (CATPathElement *ipPath) ;
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEV5V6ExtMmrCombinedCurveEdit (CAAEV5V6ExtMmrCombinedCurveEdit & iObjectToCopy);
    CAAEV5V6ExtMmrCombinedCurveEdit& operator=(CAAEV5V6ExtMmrCombinedCurveEdit & iObjectToCopy);
    
};


#endif
