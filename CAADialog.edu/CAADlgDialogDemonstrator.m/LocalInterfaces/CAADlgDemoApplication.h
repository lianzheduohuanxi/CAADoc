#ifndef CAADlgDemoApplication_H
#define CAADlgDemoApplication_H

// COPYRIGHT DASSAULT SYSTEMES 2000

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
//    CAADlgBBInteractiveApp
//
//=============================================================================

// Dialog Framework
#include "CATInteractiveApplication.h"

// Local Framework

class CAADlgDemoApplication: public CATInteractiveApplication {

  public:

    // Constructs the application given an identifier
    // Parameters:
    //    iIdentifier: 
    //        The identifier 
    CAADlgDemoApplication(const CATString &iIdentifier);

    virtual ~CAADlgDemoApplication();

    //Contains the application code  
    void BeginApplication();

    //Returns the application return code.
    int EndApplication();

  private:
 
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgDemoApplication ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgDemoApplication(const CAADlgDemoApplication &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgDemoApplication & operator = (const CAADlgDemoApplication &iObjectToCopy);

};

#endif
