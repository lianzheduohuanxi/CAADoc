#ifndef CAAGemBrowserApplication_h
#define CAAGemBrowserApplication_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the sample:
//  ----------------------
//
//  This use case illustrates how to visualize a NCGM document.
// 
//=============================================================================
//  How to launch :
//  --------------
//
//  Type : CAAGemBrowser
//
//=============================================================================

// Dialog Framework
#include "CATInteractiveApplication.h"  // To derive from

class CAAGemBrowserApplication : public CATInteractiveApplication
{
  public:
	/*
	 * Constructor. No initialization is actually done in it.
	 * The real initialization is done in the BeginApplication method.
	 */
    CAAGemBrowserApplication(const CATString & iApplicationId);
    virtual     ~CAAGemBrowserApplication();

    /*
    * Application initialization. 
    * This method instantiates a CAAVisBasicWindow, calls its Build
    * method to initialize it and gives control of it to the
    * main event loop 
    */
    virtual void BeginApplication();

    //Returns the application return code.
    virtual int  EndApplication();

private:

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAGemBrowserApplication();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAGemBrowserApplication(const CAAGemBrowserApplication &iObjectToCopy); 
    
};
#endif


