#ifndef CAAECafContextualMenuEllipse_h
#define CAAECafContextualMenuEllipse_h

//******************************************************************************
// CATIA Version 5 Release 2 
// Copyright Dassault Systemes 1999
//******************************************************************************
//  Abstract:
//  ---------
//  Implementation of the CATIContextualMenu interface for 
//  the CAASysEllipse object. 
//
//******************************************************************************
//  Usage:
//  ------
//    Launch a CATIA V5. 
//    Create a new CAAGeometry document. 
//    Create an ellipse
//    Click the right button: the contextual menu appears.
// 
//******************************************************************************
//  Explanation for contextual menu
//  -------------------------------
//  In general the contextual menu dedicated to your object completes the
//  default contextual menu. This default menu is the same that the  
//  default menu of the UI active object. 
//
//  If you call CATExtIContextualMenu::GetContextualMenu, you get the 
//  default contextual menu and you can complete it.
// 
//  So to do that, in the constructor of the data extension of your object, you 
//  retrieve the contextual menu of CATExtIContextualMenu and you create 
//  several items, that you chain to it. 
//  
//  The life cycle of the menu is managed by the  CATExtIContextualMenu class.
//
//  The contextual menu dedicaded to the UI active object is defined in the 
//  CAAApplicationFrame.edu/CAAAfrGeoDocument/src/CAAEAfrUIActiveRootObj.cpp
// 
//******************************************************************************
#include "CATExtIContextualMenu.h"

class CAAECafContextualMenuEllipse : public CATExtIContextualMenu
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    // We get the menu of the CATExtIContextualMenu's instance and we
	// complete it.
	//  
    CAAECafContextualMenuEllipse();
    virtual ~CAAECafContextualMenuEllipse();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAECafContextualMenuEllipse(const CAAECafContextualMenuEllipse &iObjectToCopy);

};
#endif
