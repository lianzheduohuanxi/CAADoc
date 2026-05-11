#ifndef CAADlgBBSenderApplication_H
#define CAADlgBBSenderApplication_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the sample
//  -----------------------
//  This Sample illustrates how to use the backbone bus to communicate beetween 
//  interactives applications. 
//  
//  2 interactives applications :
//    - CAADlgBBReceiver --> receives CAADlgBBEditorMessage. 
//    - CAADlgBBSender   --> sends such message towards the 
//                           CAADlgBBReceiver application. 
//
//  The main difference between this sample and these described in the 
//  CAASystem.edu/CAASysBackboneBasic.m module is that the event loop 
//  is these of the interactive application. The receiver don't have need to
//  have a wait protocole. 
//
//=============================================================================
//  Abstract of the class
//  -----------------------
//
//    - Creates the frame of the application. This frame contains all the
//      code. 
//
//
//=============================================================================
//  How to Launch the sample:
//  -------------------------
//
//  Type:
//    CAADlgBBReceiver in the first  process
//    CAADlgBBSender   in the second process
//
//=============================================================================

// Dialog Framework
#include "CATInteractiveApplication.h"

// Local Framework

class CAADlgBBSenderApplication: public CATInteractiveApplication {

  public:

    // Constructs the application given an identifier
    // Parameters:
    //    iIdentifier: 
    //        The identifier 
    CAADlgBBSenderApplication(const CATString &iIdentifier);

    virtual ~CAADlgBBSenderApplication();

    //Contains the application code  
    void BeginApplication();

    //Returns the application return code.
    int EndApplication();

    //Calls when the application does nothing
    // 
    void OnIdle();

  private:
 
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBBSenderApplication ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBBSenderApplication(const CAADlgBBSenderApplication &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgBBSenderApplication & operator = (const CAADlgBBSenderApplication &iObjectToCopy);


};

#endif
