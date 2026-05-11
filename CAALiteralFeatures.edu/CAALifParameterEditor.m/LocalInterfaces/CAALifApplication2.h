#ifndef CAALifApplication2_h
#define CAALifApplication2_h

// COPYRIGHT DASSAULT SYSTEMES 1999 - 2000

//=============================================================================
//  Abstract
//  --------
//
//  This sample illustrates:
// 
//   1  - The creation of parameters and formulas 
//
//   2  - The creation of a manipulator
//
//   3  - The display of a parameter constrained by a formula in a dialog frame 
//        with a spinner  
//    
//=============================================================================
//  How to launch :
//  --------------
//
//  Type : CAALifParameterEditor
//
//
//=============================================================================
//  Inheritance:
//  ------------
//           CATInteractiveApplication (Dialog Framework)
//              CATApplication (System Framework)
//
//=============================================================================

//CAALiteralFeatures headers
#include "CAALifServices.h"

// Dialog Framework
#include "CATInteractiveApplication.h"  

class CAALifApplication2 : public CATInteractiveApplication
{
	CATDeclareClass;
	
  public:
	/*
	 * Constructor. No initialization is actually done in it.
	 * The real initialization is done in the BeginApplication method.
	 */
    CAALifApplication2(const CATString & iApplicationId);
    virtual     ~CAALifApplication2();

    /*
    * Application initialization. 
    * This method instantiates a CAALifWindow, calls its Build
    * method to initialize it and gives control of it to the
    * main event loop 
    */
    virtual void BeginApplication();

    //Returns the application return code.
    virtual int  EndApplication();

	void GetServices(CAALifServices** oServices);

private:

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAALifApplication2 ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAALifApplication2(const CAALifApplication2 &iObjectToCopy);

	CAALifServices* _services;

	};
#endif
