#ifndef CAAIDDBasicCalcApplication_h
#define CAAIDDBasicCalcApplication_h

// COPYRIGHT DASSAULT SYSTEMES 2008

//=============================================================================
//  Abstract of the sample:
//  ----------------------
//
//    
//=============================================================================
//  How to launch :
//  --------------
//
//  Type : CAAIDDBasicCalc
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

class CAAIDDBasicCalcApplication : public CATInteractiveApplication
{
  public:
    /*
    * Constructor. No initialization is actually done in it.
    * The real initialization is done in the BeginApplication method.
    */
    CAAIDDBasicCalcApplication(const CATString & iApplicationId);
    virtual     ~CAAIDDBasicCalcApplication();

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

	// callback triggered when the root document window is closed
	void onExit(CATCommand* iSendingCommand, CATNotification* iSentNotification, CATCommandClientData iUsefulData);

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAIDDBasicCalcApplication();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAIDDBasicCalcApplication(const CAAIDDBasicCalcApplication &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAIDDBasicCalcApplication & operator = (const CAAIDDBasicCalcApplication &iObjectToCopy);
};
#endif
