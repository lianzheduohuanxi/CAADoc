#ifndef CAADlgHelloApplication_H
#define CAADlgHelloApplication_H

// COPYRIGHT DASSAULT SYSTEMES 2003

//=============================================================================
//  Abstract of the sample
//  -----------------------
//
//  This sample shows how implement a CATInteractiveApplication. 
//
//=============================================================================
//  How to Launch the sample:
//  -------------------------
//
//  Type:
//    mkrun -c CAADlgHelloApplication
//
//=============================================================================

// Dialog Framework
#include "CATInteractiveApplication.h"

// Local Framework

class CAADlgHelloApplication: public CATInteractiveApplication {

  public:

    // Constructs the application given an identifier
    // Parameters:
    //    iIdentifier: 
    //        The identifier 
    CAADlgHelloApplication(const CATString &iIdentifier);

    virtual ~CAADlgHelloApplication();

    //Contains the application code  
    void BeginApplication();

    //Returns the application return code.
    int EndApplication();

  private:
 
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgHelloApplication ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgHelloApplication(const CAADlgHelloApplication &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgHelloApplication & operator = (const CAADlgHelloApplication &iObjectToCopy);

};

#endif
