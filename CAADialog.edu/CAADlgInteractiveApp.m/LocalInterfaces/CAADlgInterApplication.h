#ifndef CAADlgInterApplication_H
#define CAADlgInterApplication_H

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

class CAADlgInterApplication: public CATInteractiveApplication {

  public:

    // Constructs the application given an identifier
    // Parameters:
    //    iIdentifier: 
    //        The identifier 
    CAADlgInterApplication(const CATString &iIdentifier);

    virtual ~CAADlgInterApplication();

    //Contains the application code  
    void BeginApplication();

    //Returns the application return code.
    int EndApplication();

  private:
 
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgInterApplication ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgInterApplication(const CAADlgInterApplication &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgInterApplication & operator = (const CAADlgInterApplication &iObjectToCopy);

};

#endif
