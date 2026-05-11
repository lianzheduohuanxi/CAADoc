#ifndef CAAMcaUdfLoftDlg_H
#define CAAMcaUdfLoftDlg_H

// COPYRIGHT Dassault Systemes 2002
//===================================================================
//
//  Abstract of the class:
//  ----------------------
//  Dialog box to edit or create a user feature which contains two
//  inputs: two points.
//  This dialog box is used by the CAAMcaUdfLoftEditCreateCmd and contains
//  for each input to valuate:
//    - a CATDlgSelectorList with one element
//        It contains the alias name of the input.
//    - a CATDlgLabel    
//        The title of the label is the role of the input   
//  
//  To indicate to the end user the current input to valuate, the 
//  linked CATDlgSelectorList is highlighted (selected)
//  
//===========================================================================

#include "CATDlgDialog.h"   // To derive from
class  CATDlgSelectorList;  // a dialog object used in the dialog box
class  CATDlgLabel;         // a dialog object used in the dialog box

class CAAMcaUdfLoftDlg: public CATDlgDialog
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAAMcaUdfLoftDlg.CATNls 
  //    
  DeclareResource(CAAMcaUdfLoftDlg,CATDlgDialog) ;

  public :

    // Constructor
    // ------------
    // Constructs a dialog box whose the style is:
    // The style of the dialog box is 
    //    CATDlgGridLayout            
    //        For the arrangment
    //    CATDlgWndBtnOKCancelPreview 
    //        The dialog box has 3 buttons: OK CANCEL and PREVIEW. It
    //        is a recommanded style (with CATDlgWndBtnOKCancel). On NT,the 
    //        help is included in the bannere of the dialog box (question mark)
    //        and on Unix, select the question mark command and click the
    //        current dialog box.
    // 
    CAAMcaUdfLoftDlg(CATDialog *iParent);
    virtual ~CAAMcaUdfLoftDlg(); 
	
    // Build
    // ------
    // Constructs the dialog objects inside the dialog box
    //
    void Build();

    // InitPointName
    // -------------
    // Method to initialize the CATDlgSelectorList with the name
    // of the inputs. This method is used in edit mode,  
    // to call when the dialog box is not yet built
    // 
    void InitPointName(CATUnicodeString iName1 , CATUnicodeString iName2 );

    // SetPointName
    // ------------
    // Method to modify the CATDlgSelectorList when a point
    // is selected to valuate the iPointNumber input. 
    // To call when the Dialog box is built
    void SetPointName(int iPointNumber , CATUnicodeString iName );

    // SetRole
    // -------
    // Method to set the role of the input as title of its label.
    //
    void SetRole(int iPointNumber , CATUnicodeString iName );

    // GetActiveEditorNumber
    // ----------------------
    // Method which returns the current CATDlgSelectorList. 
    //
    int  GetActiveEditorNumber();

  private : 

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAMcaUdfLoftDlg ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAMcaUdfLoftDlg(const CAAMcaUdfLoftDlg &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAMcaUdfLoftDlg & operator = (const CAAMcaUdfLoftDlg &iObjectToCopy);
	
    virtual void EditorSelect (CATCommand *, CATNotification* , CATCommandClientData data);

  private : 

      // The current CATDlgSelectorList
      int _ActiveEditor ;

      // Two CATDlgSelectorList, one for each input
      // We have used a CATDlgSelectorList in place of a CATDlgEditor
      // to have the highlight in the current CATDlgSelectorList
      // It allows to the end user to know the current input to valuate.
      //
      CATDlgSelectorList * _pEditorOfThePoint1 ;
      CATDlgSelectorList * _pEditorOfThePoint2;

      // Two CATDlgLabel, one for each input
      // Caution: To set the role of the input
      // as title of the label, use the SetTitle method
      // but do not set a title in the CAAMcaUdfLoftDlg Nls file.
      //
      CATDlgLabel        * _pLabelOfThePoint1 ;
      CATDlgLabel        * _pLabelOfThePoint2 ;

};
#endif

