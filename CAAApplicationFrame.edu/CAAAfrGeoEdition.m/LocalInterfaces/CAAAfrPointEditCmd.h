#ifndef CAAAfrPointEditCmd_h
#define CAAAfrPointEditCmd_h

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
//  Command which edits a point (an CAASysPoint component).
//  This command is returned by the CAASysPoint implementation of the CATIEdit
//  interface.
//
//  Illustrates:
//    programming a command which edits an object.
//
//  This command must manage its destruction itself. 
//  It must be deleted:
//     -  when the end user closes the dialog box (Ok,Cancel,Close buttons).
//        So the command must subscribe to the corresponding notifications and 
//        request the command destruction in the callbacks.
//     -  when another command is launched. So the current command must take 
//        the focus in order to be called on the Cancel when it loses the 
//        focus. Cancel must request the command destruction as well.
//
//  This command launches a dialog box to edit this object. It could have been 
//  the dialog object itself like the CAAAfrPlaneEditCmd in the same module.
//  
//===========================================================================
//  Inheritance:
//  ------------
//            CATDlgDialog ( Dialog Framework) 
//              CATDlgWindow ( Dialog Framework) 
//                CATDialog   (Dialog Framework)
//                  CATCommand  (System Framework)
//                    CATBaseUnknown (System Framework).
//
//===========================================================================
//  Main Method:
//  ------------
//  
//  constructor  -> requests the focus
//
//  Cancel       -> Suicide of the command 
//  Desactivate  -> Dialog box is hidden.
//  Activate     -> Creates and builds the dialog box if it doesn't exist 
//                    and shows it.
//
//  CloseBox     -> Suicide of the command 
//
//===========================================================================
// System Framework
#include "CATCommand.h"  //Needed to derive from  CATCommand

// CAASystem.edu Framework
class CAAISysPoint;   //The point to modify

// Local Framework
class CAAAfrPointEditDlg;   //Point Dialog Box


class CAAAfrPointEditCmd : public CATCommand
{ 
  public :

    CAAAfrPointEditCmd(CAAISysPoint * ipEdit);
    virtual ~CAAAfrPointEditCmd();  

    // Methods called by the command selector to manage the focus
    virtual CATStatusChangeRC Cancel     ( CATCommand *iPublisher,CATNotification *iNotification);
    virtual CATStatusChangeRC Desactivate( CATCommand *iPublisher,CATNotification *iNotification);
    virtual CATStatusChangeRC Activate   ( CATCommand *iPublisher,CATNotification *iNotification);
  
  private :

    // CloseBox
    // --------
    // Requests the destrution of the current instance 
    void CloseBox (CATCommand           * iPublisher, 
                   CATNotification      * iNotification,
                   CATCommandClientData   iUsefulData);

    // Asignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrPointEditCmd & operator = (const CAAAfrPointEditCmd &iObjectToCopy);

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrPointEditCmd(const CAAAfrPointEditCmd &iObjectToCopy);

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrPointEditCmd ();

  private:

    // The point dialog box
    CAAAfrPointEditDlg   * _pDialogPoint;
	
    // The object to modify 
    CAAISysPoint         * _piSysPointEdit ;

};
#endif
