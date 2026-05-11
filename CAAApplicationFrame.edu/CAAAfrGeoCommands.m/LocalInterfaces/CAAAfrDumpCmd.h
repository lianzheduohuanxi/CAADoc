#ifndef CAAAfrDumpCmd_h
#define CAAAfrDumpCmd_h

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
//  Command which launches a dialog box which displays the composition
//  of the current document, that is to say the number of objects of
//  each types (points, lines, circles...)
//
//  This command takes the focus in shared mode.
//
//  Illustrates:
//     - creating a simple command derived from CATCommand
//     - creating a dialog box
//     - Subscribing to send/receive events
//
//===========================================================================
//  Inheritance:
//  ------------
//         CATCommand  (System Framework)
//           CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  Activate 
//     Creates the dialog box
//     Subscribes to the dialog box events
//     Calls a method to display the model contents
//
//  DumpContainer
//     Scans the container 
//     Displays its contents.
//
//===========================================================================

// System framework
#include "CATCommand.h"  //Needed to derive from  CATCommand

// Dialog framework
class CATDlgNotify;      //Dialog Box for the dump


class CAAAfrDumpCmd : public CATCommand
{ 

  public :

    CAAAfrDumpCmd();
    virtual ~CAAAfrDumpCmd();  

    // Activate
    // ---------
    // Creates a CATDlgNotify to display the model's contain. This dialog box
    // is created modal , so the end user cannot do anything before to close it. 
    // When it is done, the dump command is killed and the dialog box too.
    //
    // If the dialog box were not modal, you should override :
    //   - the Cancel method: to do the same thing that the CloseBox Method
    //   - the Desactivate method to hide the dialog box
    // 
    virtual CATStatusChangeRC Activate( CATCommand      *iFromClient,
                                        CATNotification *iNotification);
  
  private :

    // CloseBox
    // --------
    // Requests a delete of the current object. 
    // This is a callback method set in the Activate method 
    //
    void CloseBox(CATCommand              *iPublishingCommand, 
                  CATNotification         *iNotification, 
                  CATCommandClientData     iUsefulData);

    // DisplayModelContain
    // -------------------
    // Displays the count of element contained in the model 
    //
    void DisplayModelContain();
    void DumpContainer(CATBaseUnknown *iContainer);

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrDumpCmd(const CAAAfrDumpCmd &iObjectToCopy );

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrDumpCmd & operator = (const CAAAfrDumpCmd &iObjectToCopy );

  private :

    // The point dialog box
    CATDlgNotify   * _DumpDialogBox;
	

};
#endif
