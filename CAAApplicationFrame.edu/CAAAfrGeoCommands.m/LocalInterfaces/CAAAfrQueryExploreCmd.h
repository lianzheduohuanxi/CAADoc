#ifndef CAAAfrQueryExploreCmd_h
#define CAAAfrQueryExploreCmd_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document (CAAGeometry) with its own workshop and 
//  commands.
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Shared command which inserts a progress bar in the status bar and 
//  simulates its use.
//
//  Illustrates:
//     - creating a simple shared command derived from CATCommand
//     - Using a progress bar
//
//===========================================================================
//  Inheritance:
//  ------------
//                  CATCommand  (System Framework)
//                      CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  Activates 
//     Contains nearly all the code.
//     Creates the progress bar and simulates a long task to show a 
//     progression.
//
//===========================================================================

// System framework
#include "CATCommand.h"   //Needed to derive from CATCommand

class CAAAfrQueryExploreCmd : public CATCommand
{
  public :

    CAAAfrQueryExploreCmd();

    virtual ~CAAAfrQueryExploreCmd();  
	
    // Activate:
    // --------
    // Contains the command code. 
    // The method is called when the command gets the focus.
    //
    virtual CATStatusChangeRC Activate(CATCommand      * iFromClient,
                                       CATNotification * iEvtData);

    // Cancel:
    // --------
    // This method is called when the command loses the focus definitively
    // because an excluse command requires it. 
    // This method must request explicitely the deallocation of the 
    // current command.
    //
    virtual CATStatusChangeRC Cancel(CATCommand        * iFromClient,
                                     CATNotification   * iEvtData);

    // Simulates a long task. 
    virtual void Compute() ;

  private :

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrQueryExploreCmd(const CAAAfrQueryExploreCmd &iObjectToCopy);

    // Assigment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrQueryExploreCmd & operator = (const CAAAfrQueryExploreCmd &iObjectToCopy);

};
#endif



