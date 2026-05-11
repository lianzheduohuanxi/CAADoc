#ifndef CAAEV5V6ExtMmrCombinedCurveContSubMenu_h
#define CAAEV5V6ExtMmrCombinedCurveContSubMenu_h

// Copyright Dassault Systemes 2012

//******************************************************************************
//  Abstract:
//  ---------
//  Implementation of CATIContextualSubMenu for the Combined Curve 
//
//  You are adding commands which appears in the <CombinedCurve> object menu of the 
//  contextual menu.
//
//  To do this, we create and arrange command starters that we associate with 
//  commands using command headers. 
//
//  These command headers are referred to using their identifiers.  
//
//  Here each command header is defined in the Part Document workshop 
//
// Note : CAAEV5V6ExtMmrCombinedCurveContSubMenu is the same use case as CAAEMmrCombinedCurveContSubMenu. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//******************************************************************************
//  Explanation:
//  ------------
//  The sub menu must be a data member to manage its life cycle. It can be
//  identical or different from a call to another.
//  . If it is identical, it can be created in the constructor, returned in the
//    GetContextualSubMenu method, and deleted in the destructor. This is the
//    case here
//  . Otherwise, it must be created in the GetContextualSubMenu method. To
//    correctly manage its life cycle, it must be deleted:
//    . whenever calling GetContextualSubMenu
//    . in the destructor when the class itself is deleted
// 
//******************************************************************************
//  Main Methods:
//  ------------- 
//  Constructor            -> Builds the  sub menu 
//  Destructor             -> Deletes it
//  GetContextualSubMenu() -> Returns it
//
//******************************************************************************

#include "CATIAV5Level.h"

class CATCmdStarter;



#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

#include "CATExtIContextualSubMenu.h"

class CAAEV5V6ExtMmrCombinedCurveContSubMenu : public CATExtIContextualSubMenu 
#else
//============================================== 
// V5 only
//==============================================

#include "CATBaseUnknown.h"
class CATCmdAccess;

class CAAEV5V6ExtMmrCombinedCurveContSubMenu : public CATBaseUnknown
#endif
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEV5V6ExtMmrCombinedCurveContSubMenu();
    virtual ~CAAEV5V6ExtMmrCombinedCurveContSubMenu();

    virtual CATCmdAccess * GetContextualSubMenu() ;
 
  private :

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEV5V6ExtMmrCombinedCurveContSubMenu(const CAAEV5V6ExtMmrCombinedCurveContSubMenu &iObjectToCopy);

    // Assigment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEV5V6ExtMmrCombinedCurveContSubMenu & operator = (const CAAEV5V6ExtMmrCombinedCurveContSubMenu &iObjectToCopy);


  private :
#ifdef CATIAV5R23
//============================================== 
// V5 only
//==============================================
	CATCmdAccess *  _pMenu ;
#endif    
    CATCmdStarter *  _pCAAV5V6ExtMmrSwapActiveStr ;
};
#endif
