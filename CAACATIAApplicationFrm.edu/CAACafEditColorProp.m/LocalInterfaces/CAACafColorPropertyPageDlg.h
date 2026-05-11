#ifndef CAACafColorPropertyPageDlg_H
#define CAACafColorPropertyPageDlg_H
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  This class is a page of the Edit/Properties Dialog Box. This page is 
//  managing by the CAACafColorPropertyPageEdt editor .
//
//  See CATCafTexturePropertyPageDlg in CAACafEditTextureProp.m to have more
//  detail about this class.
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
//    6 methods called by the CAACafColorPropertyPageEdt class
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
//===========================================================================

// Dialog Framework
#include "CATDlgFrame.h"  // Needed to derive from  CATDlgFrame  

// Dialog Framework
class CATDlgSlider;

// CATIAApplicationFrame Framework
#include <CATEditor.h>    

class CAACafColorPropertyPageDlg : public CATDlgFrame
{

  // NLS Macro, so in CNext/resources/msgcatalog you have :
  // CAACafColorPropertyPageDlg.CATNls 
  // 
  DeclareResource(CAACafColorPropertyPageDlg , CATDlgFrame);

  public :


    CAACafColorPropertyPageDlg (CATDialog * iParent);
    virtual ~CAACafColorPropertyPageDlg ();

    void Build();

    void SetPropertyValue(CATLISTV(CATBaseUnknown_var) & iExtract,ModeReadWrite iMode);

    void CommitModification(CATLISTV(CATBaseUnknown_var) & iExtract);

    void CancelModification(CATLISTV(CATBaseUnknown_var) & iExtract);

    void CloseWindowFromEditor();

  private :

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafColorPropertyPageDlg ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafColorPropertyPageDlg(const CAACafColorPropertyPageDlg &iObjectToCopy);

    // Assignment opeartor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafColorPropertyPageDlg & operator = (const CAACafColorPropertyPageDlg &iObjectToCopy);

  private :

    // Dialog Objects to modify the 3 components of the color
    CATDlgSlider         * _pRedSlider ;
    CATDlgSlider         * _pGreenSlider ;
    CATDlgSlider         * _pBlueSlider ;

};

#endif
