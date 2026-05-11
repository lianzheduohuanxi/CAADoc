#ifndef CAAEMmrCombinedCurveEdit_H
#define CAAEMmrCombinedCurveEdit_H

// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATExtIEdit.h"  // To derive from 

/**
* Class extending the object "CombinedCurve".
* It implements the interfaces :
*      ApplicationFrame.CATIEdit
*         This interface is called when editing a Combined Curve.
*         It associates a dialog panel and fill in the contextual menu of the Combined Curve.
*/

class CAAEMmrCombinedCurveEdit: public CATExtIEdit
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEMmrCombinedCurveEdit ();
    virtual ~CAAEMmrCombinedCurveEdit ();
    
    /**
    * Implements the method Activate of the interface CATIEdit
    * see ApplicationFrame.CATIEdit.Activate
    */
    CATCommand* Activate (CATPathElement *ipPath) ;
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrCombinedCurveEdit (CAAEMmrCombinedCurveEdit & iObjectToCopy);
    CAAEMmrCombinedCurveEdit& operator=(CAAEMmrCombinedCurveEdit & iObjectToCopy);
    
};


#endif
