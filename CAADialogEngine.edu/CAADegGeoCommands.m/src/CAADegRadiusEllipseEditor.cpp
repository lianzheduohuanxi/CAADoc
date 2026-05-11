// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegRadiusEllipseEditor.h"

// Dialog Framework
#include "CATDlgFrame.h"
#include "CATDlgLabel.h"
#include "CATDlgSpinner.h"
#include "CATDlgGridConstraints.h"

// C++ Standard Library
#include "iostream.h"


//-------------------------------------------------------------------
CAADegRadiusEllipseEditor::CAADegRadiusEllipseEditor(CATDialog * iParent): 
             CATDlgDialog (iParent, 
                           "RadiusEllipseEditorId", 
						   CATDlgWndOK|CATDlgGridLayout),
                           _Uvalues(1.),_Vvalues(1.),
                           _USpinner(NULL),_VSpinner(NULL)
                             
{
  cout << "CAADegRadiusEllipseEditor::CAADegRadiusEllipseEditor" << endl; 
}

//------------------------------------------------------------------------------

CAADegRadiusEllipseEditor::~CAADegRadiusEllipseEditor()
{
  cout << "CAADegRadiusEllipseEditor::~CAADegRadiusEllipseEditor" << endl;
  _USpinner = NULL ;
  _VSpinner = NULL ;
}

//---------------------------------------------------------------------

void CAADegRadiusEllipseEditor::Build()
{
   cout << "CAADegRadiusEllipseEditor::Build" << endl;
  
   // Creation of Frames, Labels and Spinners.
   CATDlgFrame * UFrame = NULL ;
   CATDlgFrame * VFrame = NULL ;

   UFrame = new CATDlgFrame(this, "UFrame",
                            CATDlgFraNoTitle|CATDlgFraNoFrame|CATDlgGridLayout);
   VFrame = new CATDlgFrame(this, "VFrame",
                            CATDlgFraNoTitle|CATDlgFraNoFrame|CATDlgGridLayout);

   CATDlgLabel *ULabel = NULL ;
   CATDlgLabel *VLabel = NULL ;
   ULabel = new CATDlgLabel(UFrame, "ULabel");
   VLabel = new CATDlgLabel(VFrame, "VLabel");

   _USpinner = new CATDlgSpinner(UFrame, "USpinner", CATDlgSpnEntry);
   _USpinner->SetRange(1., 10000., 10000);
   _USpinner->SetCurrentValue(_Uvalues); 

   _VSpinner = new CATDlgSpinner(VFrame, "VSpinner", CATDlgSpnEntry);
   _VSpinner->SetRange(1., 10000., 10000);
   _VSpinner->SetCurrentValue(_Vvalues); 

   // Arrangement
   UFrame->SetGridConstraints(0,0,1,1,CATGRID_CENTER);
   VFrame->SetGridConstraints(1,0,1,1,CATGRID_CENTER);
 
   ULabel->SetGridConstraints(0,0,1,1,CATGRID_CENTER);
   VLabel->SetGridConstraints(0,0,1,1,CATGRID_CENTER);
   _USpinner->SetGridConstraints(0,1,1,1,CATGRID_CENTER);
   _VSpinner->SetGridConstraints(0,1,1,1,CATGRID_CENTER);
 
   // Callback
   AddAnalyseNotificationCB(this, this->GetDiaOKNotification(),
                (CATCommandMethod)&CAADegRadiusEllipseEditor::ClickOK,
                            NULL);
}

//-------------------------------------------------------------------------------

void CAADegRadiusEllipseEditor::GetValues( float * oU ,  float * oV )
{
   *oU = _Uvalues	;
   *oV = _Vvalues	;
}

//--------------------------------------------------------------------------------

void CAADegRadiusEllipseEditor::ClickOK (CATCommand               * iPublisher,
                                              CATNotification     * iNotification,
                                              CATCommandClientData  iUsefulData)
{
   cout << "CAADegRadiusEllipseEditor::ClickOK" << endl;
  
   _Uvalues = _USpinner->GetCurrentValue() ;
   _Vvalues = _VSpinner->GetCurrentValue() ;

   //Useful for the command state
   SendNotification(GetFather(),CATDlgDialog::GetDiaOKNotification());

}


