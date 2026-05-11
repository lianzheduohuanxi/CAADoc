#ifndef CAAEGSMSewSkinBasicIcon_H
#define CAAEGSMSewSkinBasicIcon_H
//---------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2005
//---------------------------------------------------------------------
// CATIA Shape Design And Styling 
//---------------------------------------------------------------------
//
// CAAEGSMSewSkinBasicIcon
//---------------------------------------------------------------------
// 
//  Sew Skin Basic  command / Implement CATIIcon 
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 05/xx/xx > PEY 
//---------------------------------------------------------------------

// System Framework
#include "CATBaseUnknown.h"  // Needed to derive from CATBaseUnknown

class CATUnicodeString;
/**
* Class extending the object "SewSkin".
* It implements the interfaces :
*      MechanicalCommands.CATIIcon
*         This interface associates an icon with a tree node.
*/

class CAAEGSMSewSkinBasicIcon: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEGSMSewSkinBasicIcon ();
    virtual ~CAAEGSMSewSkinBasicIcon ();
    
    /**
    * Implements the method GetIconName of the interface CATIICon.
    * see MechanicalCommands.CATIIcon.GetIconName
    */
    HRESULT GetIconName( CATUnicodeString& oName );

    /**
    * Implements the method GetIconName of the interface CATIICon.
    * see MechanicalCommands.CATIIcon.GetIconName
    */
    HRESULT SetIconName( const CATUnicodeString& iName );

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEGSMSewSkinBasicIcon (CAAEGSMSewSkinBasicIcon &);
    CAAEGSMSewSkinBasicIcon& operator=(CAAEGSMSewSkinBasicIcon&);
    
};


#endif
