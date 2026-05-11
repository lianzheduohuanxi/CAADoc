#ifndef CAACafComboApplication_H
#define CAACafComboApplication_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the sample
//  -----------------------
//
//  This sample shows how to use CATComboColor,CATComboWeight,CATComboSymbol,
//  and CATComboDashed of CATIAApplicationFrame framework
//
//=============================================================================
//  How to Launch the sample:
//  -------------------------
//
//  Type:
//    mkrun -c CAACafGrapPropCombo
//
//=============================================================================

// Dialog Framework
#include "CATInteractiveApplication.h"

// Local Framework

class CAACafComboApplication: public CATInteractiveApplication {

  public:

    // Constructs the application given an identifier
    // Parameters:
    //    iIdentifier: 
    //        The identifier 
    CAACafComboApplication(const CATString &iIdentifier);

    virtual ~CAACafComboApplication();

    //Contains the application code  
    void BeginApplication();

    //Returns the application return code.
    int EndApplication();

  private:
 
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafComboApplication ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafComboApplication(const CAACafComboApplication &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafComboApplication & operator = (const CAACafComboApplication &iObjectToCopy);

};

#endif
