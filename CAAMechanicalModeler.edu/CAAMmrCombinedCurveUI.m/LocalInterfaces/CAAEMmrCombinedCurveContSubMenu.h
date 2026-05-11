#ifndef CAAEMmrCombinedCurveContSubMenu_h
#define CAAEMmrCombinedCurveContSubMenu_h

// Copyright Dassault Systemes 2001

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
#include "CATBaseUnknown.h"

class CATCmdAccess;
class CATCmdStarter;

class CAAEMmrCombinedCurveContSubMenu : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEMmrCombinedCurveContSubMenu();
    virtual ~CAAEMmrCombinedCurveContSubMenu();

    virtual CATCmdAccess * GetContextualSubMenu() ;
 
  private :

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMmrCombinedCurveContSubMenu(const CAAEMmrCombinedCurveContSubMenu &iObjectToCopy);

    // Assigment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMmrCombinedCurveContSubMenu & operator = (const CAAEMmrCombinedCurveContSubMenu &iObjectToCopy);


  private :

    CATCmdAccess *  _pMenu ;
    CATCmdStarter *  _pCAAMmrSwapActiveStr ;
};
#endif
