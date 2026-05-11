#ifndef CAADegHstChartWndDlg_h
#define CAADegHstChartWndDlg_h

// COPYRIGHT DASSAULT SYSTEMES 1999
 
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//
//===========================================================================

// Dialog Framework
#include "CATDlgDialog.h"  //Needed to derive from CATDlgDialog

class CAADegHstChartWndDlg : public CATDlgDialog
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegHstChartWndDlg.CATNls 
  //    
  DeclareResource(CAADegHstChartWndDlg,CATDlgDialog) ;

  public :

    CAADegHstChartWndDlg(CATDialog *iParent);
    virtual ~CAADegHstChartWndDlg(); 
	
    // Constructs the Dialog objects
    void Build();

  private : 

    void PositionHistogramChange (CATCommand        * iPublisher, 
		          CATNotification      * iNotification, 
		          CATCommandClientData   iUsefulData);

    void ClickClose (CATCommand        * iPublisher, 
		          CATNotification      * iNotification, 
		          CATCommandClientData   iUsefulData);

    void Editor1Selected (CATCommand        * iPublisher, 
		          CATNotification      * iNotification, 
		          CATCommandClientData   iUsefulData);

    void Editor1Deselected (CATCommand        * iPublisher, 
		          CATNotification      * iNotification, 
		          CATCommandClientData   iUsefulData);

	// 
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegHstChartWndDlg ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegHstChartWndDlg(const CAADegHstChartWndDlg &iObjectToCopy);


};
#endif
