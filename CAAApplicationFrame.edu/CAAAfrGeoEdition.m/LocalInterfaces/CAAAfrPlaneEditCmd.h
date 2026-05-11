#ifndef CAAAfrPlaneEditCmd_h
#define CAAAfrPlaneEditCmd_h

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
//  Command which edits a plane (an CAASysPlane component).
//  This command is returned by the CAASysPlane implementation of the CATIEdit
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
//  Build        -> Builds the dialog box and subscribes to its notifications.
//
//  Cancel       -> Suicide
//  Desactivate  -> Dialog box is hidden
//  Activate     -> Dialog box is shown
// 
//  ClickPreview -> Modifies the object and sends a notification 
//                  to update the display
//  ClickOk      -> Modifies the object, sends a notification 
//                  to update the display and closes the dialog box
//  ClickCancel  -> Restores the initial values, sends a notification 
//                  to update the display and closes the dialog box
//  ClickClose   -> Closes the dialog box
//
//  CloseBox     -> Suicide 
//
//===========================================================================
// Dialog Framework
#include "CATDlgDialog.h"     // Needed to derive from CATDlgDialog

// CAASystem.edu Framework
class CAAISysPlane ;     // plane interface

// Dialog Framework
class CATDlgSpinner;

class CAAAfrPlaneEditCmd : public CATDlgDialog
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAAAfrPlaneEditCmd.CATNls 
  //    
  DeclareResource(CAAAfrPlaneEditCmd, CATDlgDialog);
  
  public :
    
    CAAAfrPlaneEditCmd(CATDialog       * iParent,
                       const CATString & iName,
                       CATDlgStyle       iStyle,
                       CAAISysPlane    * ipEdit);

    virtual ~CAAAfrPlaneEditCmd();  

    // Methods called by the Command Selector to manage the focus
    virtual CATStatusChangeRC Cancel     (CATCommand *iPublisher,CATNotification *iNotification);
    virtual CATStatusChangeRC Desactivate(CATCommand *iPublisher,CATNotification *iNotification);
    virtual CATStatusChangeRC Activate   (CATCommand *iPublisher,CATNotification *iNotification);
	
    // Construction of the dialog objects 
    void Build();

  private : 

    // ClickOK 
    // -------
    // Called when the end user clicks Ok.
    // Assignes values from the Dialog box to the current object 
    //
    void ClickOK    (CATCommand         * iPublisher, 
                     CATNotification    * iNotification ,
                     CATCommandClientData iUsefulData);

    // ClickPreview 
    // ------------
    // Called when the end user clicks Preview.
    // Assignes values from the the Dialog box to the current object 
    //
    void ClickPreview (CATCommand         * iPublisher, 
                     CATNotification    * iNotification ,
                     CATCommandClientData iUsefulData);

    // ClickCancel
    // -----------
    // The end user clicks Cancel. 
    // Assignes the saved values
    //
    void ClickCancel(CATCommand         * iPublisher, 
                     CATNotification    * iNotification ,
                     CATCommandClientData iUsefulData);

    // ClickClose
    // ----------
    // Called when the end user clicks Close. 
    // 
    void ClickClose (CATCommand         * iPublisher, 
                     CATNotification    * iNotification ,
                     CATCommandClientData iUsefulData);


    // CloseBox
    // --------
    // Hiddes the Dialog Box and Asks the destruction of the command.
    // Methods called when the Dialog box must be closed: ( ClickOK and 
    // ClickCancel methods ) or when the command must be deleted ( Cancel method)
    //
    void CloseBox() ;

    // ModifyModelAndVisu
    // ------------------
    // Modifies the position of the plane and sends a notification to 
    // redraw it.
    //
    void ModifyModelAndVisu(const float iX, const float iY, const float iZ);

    // Assigment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrPlaneEditCmd & operator = (const CAAAfrPlaneEditCmd &iObjectToCopy);

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrPlaneEditCmd(const CAAAfrPlaneEditCmd &iObjectToCopy);

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrPlaneEditCmd ();

  private : 

    // X,Y,Z Position of the plane 
    CATDlgSpinner * _XSpinner ;
    CATDlgSpinner * _YSpinner ;
    CATDlgSpinner * _ZSpinner ;


    // Object to modify
    CAAISysPlane  * _piSysPlaneEdit;

    // Values to restore if the end user clicks Cancel 
    float  _Xfirst ;
    float  _Yfirst ;
    float  _Zfirst ;

};
#endif
