#ifndef CAADegPointEditor_h
#define CAADegPointEditor_h

// COPYRIGHT DASSAULT SYSTEMES 1999
  
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Dialog window which enables the user to enter the x y z coordinates of a point.
//  This window is used by the CAADegCreatePointCmd.
//
//===========================================================================
//  Main Method:
//  ------------
//
//  Build  : Creation of the editors and subscribes to the Ok  and Apply buttons.
//  EnterCB: Callback subscribed to the Ok and Apply buttons. Stores the point
//           coordinates.
//
//===========================================================================
// Dialog Framework
#include "CATDlgDialog.h"  //Needed to derive from CATDlgDialog

// Mathematics Framework
#include "CATMathPoint.h"  

// Dialog Framework
class CATDlgSpinner;

class CAADegPointEditor : public CATDlgDialog
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegPointEditor.CATNLS 
  //    
  DeclareResource(CAADegPointEditor,CATDlgDialog) ;

  public :

    CAADegPointEditor(CATDialog * iParent);
    virtual ~CAADegPointEditor(); 
	
    // Returns the 3D Coordinnates
    CATMathPoint & GetValue() ;

    // Constructs the Dialog objects
    void Build();

  private : 

    //
    // EnterCB 
    // -------
    // The dialog box is closed and values are assigned from the 
    // dialog box to the current object.
    //
    void EnterCB    (CATCommand          * iPublisher, 
                     CATNotification     * iNotification,
                     CATCommandClientData  iUsefulData);
    // 
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegPointEditor ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegPointEditor(const CAADegPointEditor &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegPointEditor & operator = (const CAADegPointEditor &iObjectToCopy);

  private : 

    // Dialog object to get 3D coordinates
    CATDlgSpinner * _XSpinner ;
    CATDlgSpinner * _YSpinner ;
    CATDlgSpinner * _ZSpinner ;

    // Point valuated in the EnterCB method and returned by the GetValue
    // method
    CATMathPoint  _Point;
};
#endif
