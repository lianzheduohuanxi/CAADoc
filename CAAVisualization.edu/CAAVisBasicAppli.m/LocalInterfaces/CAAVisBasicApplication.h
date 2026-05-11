#ifndef CAAVisBasicApplication_h
#define CAAVisBasicApplication_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract of the sample:
//  ----------------------
//
//  This sample illustrates how to use Graphic Representation in a Viewer.
// 
//=============================================================================
//  How to launch :
//  --------------
//
//  Type : CAAVisBasicAppli
//
//
//=============================================================================
//  Inheritance:
//  ------------
//           CATInteractiveApplication (Dialog Framework)
//              CATApplication (System Framework)
//
//=============================================================================

// Dialog Framework
#include "CATInteractiveApplication.h"  // To derive from

class CAAVisBasicApplication : public CATInteractiveApplication
{
  public:
   /*
    * Constructor. No initialization is actually done in it.
    * The real initialization is done in the BeginApplication method.
    */
    CAAVisBasicApplication(const CATString & iApplicationId);
    virtual     ~CAAVisBasicApplication();

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
    CAAVisBasicApplication();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisBasicApplication(const CAAVisBasicApplication &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisBasicApplication & operator = (const CAAVisBasicApplication &iObjectToCopy);

};
#endif
