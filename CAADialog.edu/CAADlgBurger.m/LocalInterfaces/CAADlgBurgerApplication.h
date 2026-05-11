#ifndef CAADlgBurgerApplication_h
#define CAADlgBurgerApplication_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract of the sample:
//  ----------------------
//
//  This  example is intended to cover the scope of programming tasks to 
//  create a dialog box. These tasks are: 
//
//    Creating an interactive application to display the dialog box 
//    Creating dialog objects and setting their behaviors and styles 
//    Arranging the dialog objects in the dialog box 
//    Setting callbacks onto controls 
//    Internationalizing the texts and messages. 
//    
//=============================================================================
//  How to launch :
//  --------------
//
//  Type : CAADlgBurger 
//
//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Application class.
//  This is the main object in the process. It avoids writing a main function.
//  Event loop is managed automatically by deriving from 
//  CATInteractiveApplication. 
//
//  CAADlgBurgerApplication only creates the main window and subscribes to the 
//  window closing to terminate the application.  
//
//=============================================================================
//  Inheritance:
//  ------------
//           CATInteractiveApplication (Dialog Framework)
//              CATApplication (System Framework)
//
//=============================================================================
//  Main Method:
//  ------------
//
//  BeginApplication: Contains the whole application code.
//
//
//=============================================================================
// Dialog Framework
#include "CATInteractiveApplication.h"  // To derive from

class CAADlgBurgerApplication : public CATInteractiveApplication
{
  public:
    /*
    * Constructor. No initialization is actually done in it.
    * The real initialization is done in the BeginApplication method.
    */
    CAADlgBurgerApplication(const CATString & iApplicationId);
    virtual     ~CAADlgBurgerApplication();

    /*
    * Application initialization. 
    * This method instantiates a CAADlgBurgerWindow, calls its build
    * method to initialize it and gives control of it to the
    * main event loop 
    */
    virtual void BeginApplication();

    //Returns the application return code.
    virtual int  EndApplication();

private:

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBurgerApplication ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBurgerApplication(const CAADlgBurgerApplication &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBurgerApplication & operator = (const CAADlgBurgerApplication &iObjectToCopy);
};
#endif
