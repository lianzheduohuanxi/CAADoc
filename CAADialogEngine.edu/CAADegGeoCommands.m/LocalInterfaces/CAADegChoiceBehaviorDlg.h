#ifndef CAADegChoiceBehaviorDlg_h
#define CAADegChoiceBehaviorDlg_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//  This class is a dialog box. It allows the end user 
//  to choice the behavior of the selection's agent used in 
//  the CAADegAnalysisNumericCmd command
//
//
//===========================================================================
// Dialog Framework
#include "CATDlgDialog.h" //Needed to derive from CATDlgDialog

class CATDlgRadioButton;

class CAADegChoiceBehaviorDlg : public CATDlgDialog
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegChoiceBehaviorDlg.CATNLS 
  //    
  DeclareResource(CAADegChoiceBehaviorDlg,CATDlgDialog) ;

  public :

    CAADegChoiceBehaviorDlg(CATDialog * iParent);

    virtual ~CAADegChoiceBehaviorDlg(); 
	
    // Constructs Dialog object 
    void Build();

    // Returns the current choice of the radio button
    void GetChoice(int & oChoice);

  private : 

    //
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegChoiceBehaviorDlg ();
    
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegChoiceBehaviorDlg(const CAADegChoiceBehaviorDlg &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegChoiceBehaviorDlg & operator = (const CAADegChoiceBehaviorDlg &iObjectToCopy);

  private :

    CATDlgRadioButton * _pMultiAcquisitionSelModesChoice ;
    CATDlgRadioButton * _pMultiAcquisitionCtrlChoice ;
    CATDlgRadioButton * _pMultiAcquisitionUserCtrlChoice ;

};
#endif
