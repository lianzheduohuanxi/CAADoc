// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAPstINFEditDlgPoint_h
#define CAAPstINFEditDlgPoint_h

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Dialog box which edits a point (an CAAPstINFPoint component).
//  This dialog box is called by the CAAPstINFEditCmdPoint command which is the
//  Edit command of the CAAPstINFPoint component, that is to say the command 
//  returned by the CAAPstINFPoint implementation of the CATIEdit interface.
//
//  Illustrates programming a dialog which edits an object.
//
//  The dialog box does not manage its life cycle. The calling command 
//  must request its destruction.
//
//===========================================================================
//  Inheritance:
//  ------------
//   
//  CATDlgDialog ( Dialog Framework) 
//      CATDlgWindow ( Dialog Framework) 
//          CATDialog   (Dialog Framework)
//              CATCommand  (System Framework)
//                 CATBaseUnknown (System Framework).
//
//===========================================================================
//  Main Method:
//  ------------
//
//  Build        -> Construction of the dialog objects.
//
//  ClickPreview -> Modifies the object and sends a notification 
//                  to update the display.
//  ClickOk      -> Modifies the object, sends a notification 
//                  to update the display and closes the dialog box.
//  ClickCancel  -> Restores the initial values, sends a notification 
//                  to update the display and closes the dialog box.
//  CloseBox     -> Hides the dialog box and sends a close notification.
//                  
//******************************************************************************

// Dialog Framework
#include "CATDlgDialog.h"   //Needed to derive from CATDlgDialog

// Local Framework
class CAAIPstINFPoint;    //Needed by Object to modify

// Dialog Framework
class CATDlgSpinner;        // 3D coordinates 


class CAAPstINFEditDlgPoint : public CATDlgDialog
{ 
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAAPstINFEditDlgPoint.CATNLS 
  //    
  DeclareResource(CAAPstINFEditDlgPoint,CATDlgDialog) ;

  public :

    CAAPstINFEditDlgPoint (CATDialog *ipParent,
                           const CATString &iName,
                           CATDlgStyle iStyle,
                           CAAIPstINFPoint *ipiEdit);

    virtual ~CAAPstINFEditDlgPoint();  
	
    // Construction of the dialog objects
    void Build();

  private : 

    // ClickOK 
    // -------
    // Called when the end user clicks OK.
    // Assigns values from the Dialog box to the current object 
    //
    void ClickOK (CATCommand *ipPublisher, 
                  CATNotification *ipNotification ,
                  CATCommandClientData iUsefulData);

    // ClickPreview 
    // ------------
    // Called when the end user clicks Preview.
    // Assigns values from the the Dialog box to the current object 
    //
    void ClickPreview (CATCommand *ipPublisher, 
                       CATNotification *ipNotification ,
                       CATCommandClientData iUsefulData);

    // ClickCancel
    // -----------
    // Called when the end user clicks Cancel. 
    // Assigns the saved values
    //
    void ClickCancel (CATCommand *ipPublisher, 
                      CATNotification *ipNotification ,
                      CATCommandClientData iUsefulData);

    // CloseBox
    // --------
    // Hides the Dialog Box.
    // Methods called when the Dialog box must be closed: ClickOK and 
    // ClickCancel methods or when the command must be deleted (Cancel method)
    //
    void CloseBox();

    // ModifyModelAndVisu
    // ------------------
    // Modifies the position of the point and sends a notification to redraw it.
    //
    void ModifyModelAndVisu(const double iX,
		                    const double iY,
							const double iZ);

    // Assignment operator, copy constructor and default constructor, not implemented
    // Set as private to prevent the compiler from automatically creating them as public.
	//-----------------------------------------------------------------------------------
    CAAPstINFEditDlgPoint & operator = (const CAAPstINFEditDlgPoint &iObjectToCopy);
    CAAPstINFEditDlgPoint(const CAAPstINFEditDlgPoint &iObjectToCopy);
    CAAPstINFEditDlgPoint ();

  private : 

    // X,Y,Z Coordinates of the point
    CATDlgSpinner *_XSpinner ;
    CATDlgSpinner *_YSpinner ;
    CATDlgSpinner *_ZSpinner ;

    // Object to modify
    CAAIPstINFPoint  *_piPstINFPointEdit;

    // Values to restore if the end user clicks Cancel 
    double  _X ;
    double  _Y ;
    double  _Z ;

};
#endif
