// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAPstINFEditCmdPoint_h
#define CAAPstINFEditCmdPoint_h

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Command which edits a point (an CAAPstINFPoint component).
//  This command is returned by the CAAPstINFPoint implementation of the CATIEdit
//  interface.
//
//  Illustrates programming a command which edits an object.
//
//  This command must manage its destruction itself. 
//  It must be deleted:
//     -  when the end user closes the dialog box (Ok orCancel buttons):
//        the command must subscribe to the corresponding notifications and 
//        request the command destruction in the callbacks.
//     -  when another command is launched: the current command must take 
//        the focus in order to be called on the Cancel when it loses the 
//        focus. Cancel must request the command destruction as well.
//
//  This command launches a dialog box to edit this object.
//  
//===========================================================================
//  Inheritance:
//  ------------
// 
//  CATDlgDialog ( Dialog Framework) 
//     CATDlgWindow ( Dialog Framework) 
//        CATDialog   (Dialog Framework)
//           CATCommand  (System Framework)
//              CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//  
//  Constructor  -> Requests the focus.
//
//  Cancel       -> End of the command.
//  Desactivate  -> Dialog box is hidden.
//  Activate     -> Creates and builds the dialog box if it does not already exist 
//                  and displays it.
//
//  CloseBox     -> End of the command 
//
//===========================================================================

// System Framework
#include "CATCommand.h"  //Needed to derive from  CATCommand

// Local Framework
class CAAIPstINFPoint;         //The point to modify
class CAAPstINFEditDlgPoint;   //Point Dialog Box


class CAAPstINFEditCmdPoint : public CATCommand
{ 
  public :

	// Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAPstINFEditCmdPoint(CAAIPstINFPoint *ipiEdit);
    virtual ~CAAPstINFEditCmdPoint();  

    // Methods called by the command selector to manage the focus
    virtual CATStatusChangeRC Cancel     (CATCommand *ipPublisher,CATNotification *ipNotification);
    virtual CATStatusChangeRC Desactivate(CATCommand *ipPublisher,CATNotification *ipNotification);
    virtual CATStatusChangeRC Activate   (CATCommand *ipPublisher,CATNotification *ipNotification);
  
  private :

    // CloseBox
    // --------
    // Requests the destrution of the current instance 
    void CloseBox (CATCommand *ipPublisher, 
                   CATNotification *ipNotification,
                   CATCommandClientData iUsefulData);

    // Asignment operator, copy constructor and default constructor, not implemented
    // Set as private to prevent the compiler from automatically creating them as public.
	//-----------------------------------------------------------------------------------
    CAAPstINFEditCmdPoint & operator = (const CAAPstINFEditCmdPoint &iObjectToCopy);
    CAAPstINFEditCmdPoint(const CAAPstINFEditCmdPoint &iObjectToCopy);
    CAAPstINFEditCmdPoint ();

  private:

    // The point dialog box
    CAAPstINFEditDlgPoint *_pDialogPoint;
	
    // The object to modify 
    CAAIPstINFPoint *_piPstINFPointEdit ;

};
#endif
