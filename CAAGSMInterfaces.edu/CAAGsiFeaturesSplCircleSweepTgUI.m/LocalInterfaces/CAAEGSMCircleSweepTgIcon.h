#ifndef CAAEGSMCircleSweepTgIcon_H
#define CAAEGSMCircleSweepTgIcon_H
//---------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2005
//---------------------------------------------------------------------
// Shape Design And Styling 
//---------------------------------------------------------------------
// Responsable: BIW
//---------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd
//---------------------------------------------------------------------
// 
//  Circle Sweep tangent command / Implement CATIIcon 
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

class CAAEGSMCircleSweepTgIcon: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEGSMCircleSweepTgIcon ();
    virtual ~CAAEGSMCircleSweepTgIcon ();
    
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
    CAAEGSMCircleSweepTgIcon (CAAEGSMCircleSweepTgIcon &);
    CAAEGSMCircleSweepTgIcon& operator=(CAAEGSMCircleSweepTgIcon&);
    
};


#endif
