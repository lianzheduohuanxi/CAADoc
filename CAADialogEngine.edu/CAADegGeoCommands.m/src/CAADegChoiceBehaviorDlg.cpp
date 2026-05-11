// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegChoiceBehaviorDlg.h"

// Dialog Framework
#include "CATDlgRadioButton.h"
#include "CATDlgGridConstraints.h"

// C++ Standard Library
#include "iostream.h"


//-------------------------------------------------------------------
CAADegChoiceBehaviorDlg::CAADegChoiceBehaviorDlg(CATDialog * iParent): 
             CATDlgDialog (iParent, 
                           "ChoiceBehaviorDlgId", 
			   CATDlgWndBtnOKCancel|CATDlgGridLayout),
                           _pMultiAcquisitionSelModesChoice(NULL),
                           _pMultiAcquisitionCtrlChoice(NULL),
                           _pMultiAcquisitionUserCtrlChoice(NULL)
{
  cout << "CAADegChoiceBehaviorDlg::CAADegChoiceBehaviorDlg" << endl; 
}

//------------------------------------------------------------------------------

CAADegChoiceBehaviorDlg::~CAADegChoiceBehaviorDlg()
{
  cout << "CAADegChoiceBehaviorDlg::~CAADegChoiceBehaviorDlg" << endl;

  _pMultiAcquisitionSelModesChoice          = NULL ;
  _pMultiAcquisitionCtrlChoice      = NULL ;
  _pMultiAcquisitionUserCtrlChoice = NULL ;
}

//---------------------------------------------------------------------

void CAADegChoiceBehaviorDlg::Build()
{
    cout << "CAADegChoiceBehaviorDlg::Build" << endl;
  
    _pMultiAcquisitionSelModesChoice = new CATDlgRadioButton(this,"ChoiceMASelModesId");
    _pMultiAcquisitionSelModesChoice->SetGridConstraints(0,0,1,1,CATGRID_LEFT);
    _pMultiAcquisitionSelModesChoice->SetState(CATDlgCheck);

    _pMultiAcquisitionCtrlChoice = new CATDlgRadioButton(this,"ChoiceMACtrlId");
    _pMultiAcquisitionCtrlChoice->SetGridConstraints(1,0,1,1,CATGRID_LEFT);
    _pMultiAcquisitionCtrlChoice->SetState(CATDlgUncheck);

    _pMultiAcquisitionUserCtrlChoice = new CATDlgRadioButton(this,"ChoiceMAUserCtrlId");
    _pMultiAcquisitionUserCtrlChoice->SetGridConstraints(2,0,1,1,CATGRID_LEFT);
    _pMultiAcquisitionUserCtrlChoice->SetState(CATDlgUncheck);
}


//--------------------------------------------------------------------------------
void CAADegChoiceBehaviorDlg::GetChoice(int & oChoice)
{
    cout << "CAADegChoiceBehaviorDlg::GetChoice" << endl;
    oChoice = 0 ;

    if ( (NULL != _pMultiAcquisitionSelModesChoice) &&
          (CATDlgCheck == _pMultiAcquisitionSelModesChoice->GetState() ) ) 
    {
        oChoice = 1;
    } else if ( (NULL != _pMultiAcquisitionSelModesChoice) &&
          (CATDlgCheck == _pMultiAcquisitionCtrlChoice->GetState() ) ) 
    {
        oChoice = 2;
    } else if ( (NULL != _pMultiAcquisitionSelModesChoice) &&
          (CATDlgCheck == _pMultiAcquisitionUserCtrlChoice->GetState() ) ) 
    {
        oChoice = 3;
    }

}
