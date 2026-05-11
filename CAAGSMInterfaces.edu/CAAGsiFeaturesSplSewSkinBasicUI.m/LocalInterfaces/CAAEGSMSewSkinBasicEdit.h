#ifndef CAAEGSMSewSkinBasicEdit_H
#define CAAEGSMSewSkinBasicEdit_H
//---------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2005
//---------------------------------------------------------------------
// CATIA Shape Design And Styling 
//---------------------------------------------------------------------
//
// CAAEGSMSewSkinBasicEdit 
//---------------------------------------------------------------------
// 
//  Sew Skin Basic  command / Implement CATIEdit 
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 05/xx/xx > PEY 
//---------------------------------------------------------------------

// System Framework
#include "CATExtIEdit.h"  // To derive from 

/**
* Class extending the object "SewSkin".
* It implements the interfaces :
*      ApplicationFrame.CATIEdit
*         This interface is called when editing a Sew Skin.
*         It associates a dialog panel and fill in the contextual menu of the Sew Skin.
*/

class CAAEGSMSewSkinBasicEdit: public CATExtIEdit
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEGSMSewSkinBasicEdit ();
    virtual ~CAAEGSMSewSkinBasicEdit ();
    
    /**
    * Implements the method Activate of the interface CATIEdit
    * see ApplicationFrame.CATIEdit.Activate
    */
    CATCommand* Activate (CATPathElement *ipPath) ;
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEGSMSewSkinBasicEdit (CAAEGSMSewSkinBasicEdit & iObjectToCopy);
    CAAEGSMSewSkinBasicEdit& operator=(CAAEGSMSewSkinBasicEdit & iObjectToCopy);
    
};


#endif
