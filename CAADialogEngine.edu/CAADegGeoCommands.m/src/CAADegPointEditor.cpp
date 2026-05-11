// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAADegPointEditor.h"

// Dialog Framework
#include "CATDlgFrame.h"
#include "CATDlgLabel.h"
#include "CATDlgSpinner.h"
#include "CATDlgGridConstraints.h"

// C++ Standard Library
#include "iostream.h"

//------------------------------------------------------------------------------------------

CAADegPointEditor::CAADegPointEditor(CATDialog * iParent): 
      CATDlgDialog (iParent,
                    "PointEditorId",
                    CATDlgWndOK|CATDlgWndAPPLY|CATDlgWndCANCEL|CATDlgGridLayout),
                    _XSpinner(NULL),
                    _YSpinner(NULL),
                    _ZSpinner(NULL)
                             
{
  cout << "CAADegPointEditor::CAADegPointEditor" << endl; 
}

CAADegPointEditor::~CAADegPointEditor()
{
  cout << "CAADegPointEditor::~CAADegPointEditor" << endl;
  _XSpinner = NULL ;
  _YSpinner = NULL ;
  _ZSpinner = NULL ;
}

//--------------------------------------------------------------------------------------

void CAADegPointEditor::Build()
{
   cout << "CAADegPointEditor::Build" << endl;

  //Creation of Frames, Labels and Spinners.
  CATDlgLabel   * XLabel = NULL  ;
  CATDlgLabel   * YLabel = NULL  ;
  CATDlgLabel   * ZLabel = NULL  ;
  CATDlgFrame   * XFrame = NULL  ;
  CATDlgFrame   * YFrame = NULL  ;
  CATDlgFrame   * ZFrame = NULL  ;

  XFrame = new CATDlgFrame(this, "XFrame",
                            CATDlgFraNoTitle|CATDlgFraNoFrame|CATDlgGridLayout);
  YFrame = new CATDlgFrame(this, "YFrame",
                            CATDlgFraNoTitle|CATDlgFraNoFrame|CATDlgGridLayout);
  ZFrame = new CATDlgFrame(this, "ZFrame",
                            CATDlgFraNoTitle|CATDlgFraNoFrame|CATDlgGridLayout);

  XLabel = new CATDlgLabel(XFrame, "XLabel");

  YLabel = new CATDlgLabel(YFrame, "YLabel");
  ZLabel = new CATDlgLabel(ZFrame, "ZLabel");

  _XSpinner = new CATDlgSpinner(XFrame, "XSpinner", CATDlgSpnEntry);
  _XSpinner->SetRange(-10000., 10000., 20000);
  float x = (float) _Point.GetX() ;
  _XSpinner->SetCurrentValue(x); 
  _YSpinner = new CATDlgSpinner(YFrame, "YSpinner", CATDlgSpnEntry);
  _YSpinner->SetRange(-10000., 10000., 20000);
  float y = (float) _Point.GetY() ;
  _YSpinner->SetCurrentValue(y); 
  _ZSpinner = new CATDlgSpinner(ZFrame, "ZSpinner", CATDlgSpnEntry);
  _ZSpinner->SetRange(-10000., 10000., 20000);
  float z = (float) _Point.GetZ() ;
  _ZSpinner->SetCurrentValue(z); 

  //Arrangement
  XFrame->SetGridConstraints(0,0,1,1,CATGRID_CENTER);
  YFrame->SetGridConstraints(1,0,1,1,CATGRID_CENTER);
  ZFrame->SetGridConstraints(2,0,1,1,CATGRID_CENTER);

  XLabel->SetGridConstraints(0,0,1,1,CATGRID_CENTER);
  YLabel->SetGridConstraints(0,0,1,1,CATGRID_CENTER);
  ZLabel->SetGridConstraints(0,0,1,1,CATGRID_CENTER);

  _XSpinner->SetGridConstraints(0,1,1,1,CATGRID_CENTER);
  _YSpinner->SetGridConstraints(0,1,1,1,CATGRID_CENTER);
  _ZSpinner->SetGridConstraints(0,1,1,1,CATGRID_CENTER);

  //Callbacks
  AddAnalyseNotificationCB(this, this->GetDiaOKNotification(),
                (CATCommandMethod)&CAADegPointEditor::EnterCB,
                            NULL);
  AddAnalyseNotificationCB(this, this->GetDiaAPPLYNotification(),
                (CATCommandMethod)&CAADegPointEditor::EnterCB,
                            NULL);
}


CATMathPoint & CAADegPointEditor::GetValue()
{
	return _Point ;
}


void CAADegPointEditor::EnterCB    (CATCommand           * iPublisher ,
                                    CATNotification      * iNotification,
                                    CATCommandClientData   iUsefulData)
{
   cout << "CAADegPointEditor::EnterCB" << endl;
  
   _Point.SetCoord(_XSpinner->GetCurrentValue(),
	               _YSpinner->GetCurrentValue(),
	               _ZSpinner->GetCurrentValue() );

   // This notification enables the state command to receive it and 
   // to value its dialog agent. 
   SendNotification(GetFather(),iNotification);
}



