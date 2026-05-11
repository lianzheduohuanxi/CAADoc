#ifndef CAADlgInterApplication_H
#define CAADlgInterApplication_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the sample
//  -----------------------
//
//  This sample illustrates usage of OnIdle callback and timeout callback.
//
//  Four classes are defined to show the usage of callback :
//    1) the Burglar     class,
//    2) the Alarm       class,
//    3) the Application class,
//    4) the Command     class.
//
//  The burglar and the alarm class to show callback.
//
//  The Application is necessary to show OnIdle and timeOut callbacks.
//
//  The command is necessary to show timeOut callback.
//
//=============================================================================
//  How to Launch the sample:
//  -------------------------
//
//  Type:
//    CAADlgInterApplication
//
//=============================================================================

// Dialog Framework
#include "CATInteractiveApplication.h"

// Local Framework
class CAADlgObject;
class CAADlgTessellation;
class CAADlgTimeOutCommand;


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

    //Calls when the application does nothing
    // 
    void OnIdle();

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

  private:
    //  The Count 
    int                        _CAADlgCount;

    // Argument for the scenario
    CAADlgObject              *_pObject;
    CAADlgTessellation        *_pTessellation;

    // Command which manages the timeout
    CAADlgTimeOutCommand      *_pTimeOutCommand;
};

#endif
