#ifndef CAAAfrPointEditDlg_h
#define CAAAfrPointEditDlg_h

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
//  Dialog box which edits a point (an CAASysPoint component).
//  This dialog box is called by the CAAAfrPointEditCmd command which is the
//  Edit command of the CAASysPoint component, that is to say the command 
//  returned by the CAASysPoint implementation of the CATIEdit interface.
//
//  Illustrates:
//    programming a dialog which edits an object.
//
//  The dialog box does not manage its life cycle. The calling command 
//  must request its destruction.
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
//  Build        -> Construction of the dialog objects
//
//  ClickPreview -> Modifies the object and sends a notification 
//                  to update the display
//  ClickOk      -> Modifies the object, sends a notification 
//                  to update the display and closes the dialog box
//  ClickCancel  -> Restores the initial values, sends a notification 
//                  to update the display and closes the dialog box
//  ClickClose   -> Closes the dialog box
//
//  CloseBox     -> Hides the dialog box and sends a close notification.
//                  
//******************************************************************************
// Dialog Framework
#include "CATDlgDialog.h"   //Needed to derive from CATDlgDialog

// CAASystem.edu Framework
class CAAISysPoint;    //Needed by Object to modify

// Dialog Framework
class CATDlgSpinner;        // 3D coordinates 


class CAAAfrPointEditDlg : public CATDlgDialog
{ 
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAAAfrPointEditDlg.CATNLS 
  //    
  DeclareResource(CAAAfrPointEditDlg,CATDlgDialog) ;

  public :

    CAAAfrPointEditDlg( CATDialog       * iParent,
                        const CATString & iName,
                        CATDlgStyle       iStyle,
                        CAAISysPoint    * ipEdit);

    virtual ~CAAAfrPointEditDlg();  
	
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
    void ClickPreview(CATCommand         * iPublisher, 
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

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrPointEditDlg & operator = (const CAAAfrPointEditDlg &iObjectToCopy);

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrPointEditDlg(const CAAAfrPointEditDlg &iObjectToCopy);

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrPointEditDlg ();

  private : 

    // X,Y,Z Coordinates of the point
    CATDlgSpinner * _XSpinner ;
    CATDlgSpinner * _YSpinner ;
    CATDlgSpinner * _ZSpinner ;

    // Object to modify
    CAAISysPoint  * _piSysPointEdit;

    // Values to restore if the end user clicks Cancel 
    float  _Xfirst ;
    float  _Yfirst ;
    float  _Zfirst ;

};
#endif
