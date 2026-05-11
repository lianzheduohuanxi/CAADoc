#ifndef CAAEGSMCircleSweepTgEdit_H
#define CAAEGSMCircleSweepTgEdit_H
//---------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2005
//---------------------------------------------------------------------
// CATIA Shape Design And Styling 
//---------------------------------------------------------------------
// Responsable: BIW
//---------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd
//---------------------------------------------------------------------
// 
//  Circle Sweep tangent command / Implement CATIEdit 
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 05/xx/xx > PEY 
//---------------------------------------------------------------------
// System Framework
#include "CATExtIEdit.h"  // To derive from 

/**
* Class extending the object "CAASewSkin".
* It implements the interfaces :
*      ApplicationFrame.CATIEdit
*         This interface is called when editing a Sew Skin.
*         It associates a dialog panel and fill in the contextual menu of the Sew Skin.
*/

class CAAEGSMCircleSweepTgEdit: public CATExtIEdit
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEGSMCircleSweepTgEdit ();
    virtual ~CAAEGSMCircleSweepTgEdit ();
    
    /**
    * Implements the method Activate of the interface CATIEdit
    * see ApplicationFrame.CATIEdit.Activate
    */
    CATCommand* Activate (CATPathElement *ipPath) ;
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEGSMCircleSweepTgEdit (CAAEGSMCircleSweepTgEdit & iObjectToCopy);
    CAAEGSMCircleSweepTgEdit& operator=(CAAEGSMCircleSweepTgEdit & iObjectToCopy);
    
};


#endif
