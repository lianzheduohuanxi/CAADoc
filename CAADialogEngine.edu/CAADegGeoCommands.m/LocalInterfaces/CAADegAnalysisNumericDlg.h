#ifndef CAADegAnalysisNumericDlg_h
#define CAADegAnalysisNumericDlg_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Dialog window which enables the user to enter the two radius of an ellipse.
//  This window is used by the CAADegCreateEllipseCmd.
//
//===========================================================================
//  Main Method:
//  ------------
//
//  Build       : creation of the dialog object 
//  UpdateValues: Set values on label from the current selection
// 
//===========================================================================
// Dialog Framework
#include "CATDlgDialog.h" //Needed to derive from CATDlgDialog

class CATDlgLabel ;

class CAADegAnalysisNumericDlg : public CATDlgDialog
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegAnalysisNumericDlg.CATNLS 
  //    
  DeclareResource(CAADegAnalysisNumericDlg,CATDlgDialog) ;

  public :

    CAADegAnalysisNumericDlg(CATDialog * iParent);

    virtual ~CAADegAnalysisNumericDlg(); 
	
    // Constructs Dialog object 
    void Build();

	// Updates labels 
    void UpdateValues(int iNbplane, int iNbpoint,
					  int iNbline,  int iNbcircle, int iNbellipse) ;

  private : 

    //
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegAnalysisNumericDlg ();
    
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegAnalysisNumericDlg(const CAADegAnalysisNumericDlg &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegAnalysisNumericDlg & operator = (const CAADegAnalysisNumericDlg &iObjectToCopy);

  private :

    CATDlgLabel * _pPlaneVal ;
    CATDlgLabel * _pPointVal ;
    CATDlgLabel * _pLineVal ;
    CATDlgLabel * _pCircleVal ;
    CATDlgLabel * _pEllipseVal ;
};
#endif
