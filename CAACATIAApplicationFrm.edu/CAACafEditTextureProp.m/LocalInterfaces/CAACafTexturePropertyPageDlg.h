#ifndef CAACafTexturePropertyPageDlg_H
#define CAACafTexturePropertyPageDlg_H
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  This class is a page of the Edit/Properties Dialog Box. This page is 
//  managing by the CAACafTexturePropertyPageEdt editor .
//
//===========================================================================
//  Inheritance
//  ------------
//       CATDlgFrame (Dialog Framework)
//          CATDlgBox      (Dialog Framework)
//               CATDialog     (Dialog Framework)
//                  CATCommand  ( System Framework)
//                      CATBaseUnknown (System Framework)
//                   
//
//===========================================================================
//  Main Methods:
//  -------------
//    6 methods called by the CAACafTexturePropertyPageEdt class
//
//    constructor           -> Initialization 
//    Build                 -> Construction of the Dialog object 
//    SetPropertyValue      -> Valuation of the Dialog object
//    CommitModification    -> Set the current value to the extract object 
//    CancelModification    -> Empty for the sample
//    CloseWindowFromEditor -> Empty for the sample
//
//    1 method  called by its Dialog's father 
//    destructor            -> delete object which are not dialog object 
//
///===========================================================================
// CATDialog Framework
#include "CATDlgFrame.h"  // Needed to derive from  CATDlgFrame  

// CATDialog Framework
class CATDlgCheckButton;
// CATIAApplicationFrame Framework
#include <CATEditor.h>    

class CAACafTexturePropertyPageDlg : public CATDlgFrame
{
    // NLS Macro, so in CNext/resources/msgcatalog you have :
    // CAACafTexturePropertyPageDlg.CATNls 
    // 
    DeclareResource(CAACafTexturePropertyPageDlg , CATDlgFrame);

  public :


    CAACafTexturePropertyPageDlg (CATDialog * iParent);
    virtual ~CAACafTexturePropertyPageDlg ();

    // Builds the Dialog objects
    void Build();


    // SetPropertyValue 
    // -----------------
    // Sets the values and options in the Dialog object from objects 
    // of the extracted list.  
    //
    // This method is called by the CAACafTexturePropertyPageEdt::SetPropertyValue 
    // method after the Build method. 
    //
    void SetPropertyValue(CATLISTV(CATBaseUnknown_var) & iExtract,ModeReadWrite iMode);

    // CommitModification 
    // -------------------
    // Modifies objects of the extracted list with the current values 
    // of the page.
    //
    // This method is called by the CAACafTexturePropertyPageEdt::CommitModification 
    //  
	void CommitModification(CATLISTV(CATBaseUnknown_var) & iExtract);

    // CancelModification 
    // -------------------
    // The Cancel Button becomes Close Button after the first Apply. 
    //
    // This method is called by the CAACafTexturePropertyPageEdt::CancelModification 
    //
    // In these two cases, you don't modify the model: for a cancel, the model keeps
    // the initial values, and for a close, the model keeps the last applied values.
    // 
	void CancelModification(CATLISTV(CATBaseUnknown_var) & iExtract);

    // CloseWindowFromEditor()
    // -----------------------
    // This method is called, by the editor, when the end user swaps between pages,
    // but not when the Edit Properties Dialog box is closed. 
    // 
	void CloseWindowFromEditor();

  private :
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafTexturePropertyPageDlg ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafTexturePropertyPageDlg(const CAACafTexturePropertyPageDlg &iObjectToCopy);

    // Assigment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafTexturePropertyPageDlg & operator = (const CAACafTexturePropertyPageDlg &iObjectToCopy);

  private :

    // Dialog Objects
    CATDlgCheckButton    * _pMetal;
    CATDlgCheckButton    * _pRough;

};

#endif
