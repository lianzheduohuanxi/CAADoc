#ifndef CAAVisRepApplication_h
#define CAAVisRepApplication_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract of the sample:
//  ----------------------
//
//  This sample illustrates:
// 
//   I- Management of Graphic Representation (Rep)
//
//      - Creation of CAT3DBagRep (Bag)
//      - Creation of CAT3DCustomRep which can contain:
//          - CAT3DLineGP
//          - CAT3DMarkerGP
//          - CAT3DPlanarFaceGP
//      - Adding a Rep in a Bag to create a tree
//
//  II- Management of Graphic Attributes 
//
//      - Color , Thickness, Line Type 
//      - show,no show
//      - Inheritance
//      - type : Volum, Skin or Edge
//      - 
//    
//=============================================================================
//  How to launch :
//  --------------
//
//  Type : CAAVisRep
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

class CAAVisRepApplication : public CATInteractiveApplication
{
  public:
   /*
    * Constructor. No initialization is actually done in it.
    * The real initialization is done in the BeginApplication method.
    */
    CAAVisRepApplication(const CATString & iApplicationId);
    virtual     ~CAAVisRepApplication();

    /*
    * Application initialization. 
    * This method instantiates a CAAVisRepWindow, calls its Build
    * method to initialize it and gives control of it to the
    * main event loop 
    */
    virtual void BeginApplication();

    //Returns the application return code.
    virtual int  EndApplication();

private:

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisRepApplication ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisRepApplication(const CAAVisRepApplication &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisRepApplication & operator = (const CAAVisRepApplication &iObjectToCopy);
};
#endif
