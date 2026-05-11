#ifndef CAADegRadiusEllipseEditor_h
#define CAADegRadiusEllipseEditor_h

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
//  Build  : creation of the editors and subscribes to the Ok button.
//  ClickOK: callback subscribed to the Ok button. Stores the radius values.
//
//===========================================================================
// Dialog Framework
#include "CATDlgDialog.h" //Needed to derive from CATDlgDialog

class CATDlgSpinner;

class CAADegRadiusEllipseEditor : public CATDlgDialog
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegRadiusEllipseEditor.CATNLS 
  //    
  DeclareResource(CAADegRadiusEllipseEditor,CATDlgDialog) ;

  public :

    CAADegRadiusEllipseEditor(CATDialog * iParent);

    virtual ~CAADegRadiusEllipseEditor(); 
	
    void GetValues(float *oU, float *oV) ;

    // Constructs Dialog object 
    void Build();

  private : 

    // Sends a notification OK to its father
    void ClickOK    (CATCommand          * iPublisher, 
                     CATNotification     * iNotification,
                     CATCommandClientData  iUsefulData);

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegRadiusEllipseEditor ();
    
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegRadiusEllipseEditor(const CAADegRadiusEllipseEditor &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegRadiusEllipseEditor & operator = (const CAADegRadiusEllipseEditor &iObjectToCopy);

  private :

    CATDlgSpinner * _USpinner ;
    CATDlgSpinner * _VSpinner;

    float  _Uvalues, _Vvalues;
};
#endif
