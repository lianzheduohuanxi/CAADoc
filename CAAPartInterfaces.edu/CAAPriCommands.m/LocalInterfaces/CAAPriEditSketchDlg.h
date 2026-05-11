#ifndef CAAPriEditSketchDlg_H
#define CAAPriEditSketchDlg_H

// COPYRIGHT Dassault Systemes 2002
//===================================================================
//
//  Abstract of the class:
//  ----------------------
//  Dialog box associated with the CAAPriEditSketchCmd. 
//  
//===========================================================================

// Dialog framework
#include "CATDlgDialog.h"   // To derive from
class  CATDlgLabel;         // a dialog object used in the dialog box

// ObjectSpecsModeler framework
class CATISpecObject ;

class CAAPriEditSketchDlg: public CATDlgDialog
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAAPriEditSketchDlg.CATNls 
  //    
  DeclareResource(CAAPriEditSketchDlg,CATDlgDialog) ;

  public :

    // Constructor
    // ------------
    // Constructs a dialog box whose the style is:
    // The style of the dialog box is 
    //    CATDlgGridLayout            
    //        For the arrangment
    //    CATDlgWndBtnOKCancelPreview 
    //        The dialog box has 2 buttons: OK CANCEL . It
    //        is a recommanded style (with CATDlgWndBtnOKCancel). On NT,the 
    //        help is included in the bannere of the dialog box (question mark)
    //        and on Unix, select the question mark command and click the
    //        current dialog box.
    // 
    CAAPriEditSketchDlg(CATDialog *iParent);
    virtual ~CAAPriEditSketchDlg(); 
	
    // Build
    // ------
    // Constructs the dialog objects inside the dialog box
    //
    void Build();

    // SetElement
    // ----------
    // The CAAPriEditSketchCmd command gives the name of the 
    // profile .
    //
    void SetElement(CATISpecObject * pISpecObjectOnPad);

  private : 

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAPriEditSketchDlg ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAPriEditSketchDlg(const CAAPriEditSketchDlg &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAPriEditSketchDlg & operator = (const CAAPriEditSketchDlg &iObjectToCopy);
	
    // Callback method to send an event 
    void EditSketch(CATCommand* cmd, 
                                  CATNotification* evt, 
                                  CATCommandClientData data) ;
  private : 

      // A CATDlgLabel for the sketch name
      // Caution: To set the name of the input
      // as title of the label, use the SetTitle method
      // but do not set a title in the CAAPriEditSketchDlg Nls file.
      //
      CATDlgLabel        * _pLabelOfTheProfile ;
};
#endif

