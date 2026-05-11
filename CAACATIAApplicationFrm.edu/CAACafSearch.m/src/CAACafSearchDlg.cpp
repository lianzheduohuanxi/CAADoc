// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAACafSearchDlg.h"
#include "CAACafLaunchNextQueryNotification.h"
#include "CAACafSearchCmd.h"

//Application Frame Framework
#include "CATApplicationFrame.h"
#include "CATFrmEditor.h"

// Dialog Framework
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgCombo.h"
#include "CATDlgPushButton.h"
#include "CATDlgGridConstraints.h"

// Visualization Framework
#include "CATPSO.h"

// System Framework
#include "CATMsgCatalog.h"

// C++ Standard Library
#include "iostream.h"

//------------------------------------------------------------------------------------------

CAACafSearchDlg::CAACafSearchDlg(CATDialog * iParent, CAACafSearchCmd * iCmd): 
      CATDlgDialog (iParent,
                    "CAACafSearchDlgId",
                    CATDlgWndBtnClose |CATDlgGridLayout),
                    _pResultQueryEditor(NULL),
                    _pLaunchBtn(NULL),
                    _pContextCombo(NULL),
                    _pCriteriaCombo(NULL),
                    _pCriteriaList(NULL),
                    _pPso(NULL)
                             
{
  cout << "CAACafSearchDlg::CAACafSearchDlg" << endl; 

  // Retrieves the text of the queries created by the CAACafSearchCmd command
  //
  if ( NULL != iCmd )
  {   
     iCmd->GetCriteriaText(&_pCriteriaList);
  }

  // Retrieves the PSO from the current editor 
  //
  CATFrmEditor * pEditor = CATFrmEditor::GetCurrentEditor();
  if ( NULL !=  pEditor )
  {
      _pPso = pEditor->GetPSO();
  }
}

//------------------------------------------------------------------------------------------
CAACafSearchDlg::~CAACafSearchDlg()
{
  cout << "CAACafSearchDlg::~CAACafSearchDlg" << endl;

  _pResultQueryEditor = NULL ;
  _pLaunchBtn = NULL ;
  _pContextCombo = NULL ;
  _pCriteriaCombo = NULL ;
  _pPso = NULL ;

  if ( NULL != _pCriteriaList )
  {
      delete _pCriteriaList ;
      _pCriteriaList = NULL ;
  }
}

//--------------------------------------------------------------------------------------

void CAACafSearchDlg::Build()
{
   cout << "CAACafSearchDlg::Build" << endl;
 
  // Dialog Object creation
 
  CATDlgLabel * pCriterionTxt        = new CATDlgLabel(this,"QueryTxtId");
  _pCriteriaCombo = new CATDlgCombo(this,"QueriesComboId",CATDlgCmbDropDown);

  CATDlgLabel * pContextComboTxt    = new CATDlgLabel(this,"ContextComboTxtId");
  _pContextCombo = new CATDlgCombo(this,"ContextComboId",CATDlgCmbDropDown);

  CATDlgLabel * pResultQueryTxt    = new CATDlgLabel(this,"ResultQueryTxtId");
  _pResultQueryEditor = new CATDlgEditor(this,"ResultQueryEditorId",CATDlgEdtReadOnly);
  
  _pLaunchBtn = new CATDlgPushButton(this,"LaunchBtnId");
  if ( NULL == _pPso )
  {
      // there is certainely no open document 
     _pLaunchBtn->SetSensitivity(CATDlgDisable);
  }

  // Dialog Object arrangement
  pCriterionTxt->SetGridConstraints(0,0,1,1,CATGRID_CENTER);
  _pCriteriaCombo->SetGridConstraints(0,1,1,1,CATGRID_CENTER);
  pContextComboTxt->SetGridConstraints(0,2,1,1,CATGRID_CENTER);
  _pContextCombo->SetGridConstraints(0,3,1,1,CATGRID_CENTER);

  pResultQueryTxt->SetGridConstraints(1,0,1,1,CATGRID_CENTER);
  _pResultQueryEditor->SetGridConstraints(1,1,1,1,CATGRID_CENTER);

  _pLaunchBtn->SetGridConstraints(2,0,1,1,CATGRID_CENTER);

  // Retrieves the NLS text for each context combo's line
  CATUnicodeString ContextValues[4];
  CATUnicodeString ContextText ;
  CATString Text ;
  char Key[30]; 

  int nbmaxchar = 0 ;
  int i = 0;
  for ( ; i < 4 ; i++)
  {
    // Transformation of an int in a char *
    sprintf(Key, "Context%d", i);

    // Set this char * in a CATSTring
    Text = Key ;
    ContextText = Text ;

    // retrieves the NLS text
    ContextText = CATMsgCatalog::BuildMessage("CAACafSearchDlg",Text,NULL,0,ContextText);
    ContextValues[i] = ContextText ;

    if ( ContextText.GetLengthInChar() > nbmaxchar ) nbmaxchar = ContextText.GetLengthInChar() ;
  }

  _pContextCombo->SetLine(ContextValues,4);
  _pContextCombo->SetDropDownTextWidth(nbmaxchar);
  
  // Sets the criteria combo's lines
  nbmaxchar = 0 ;
  if ( NULL != _pCriteriaList )
  {
     for ( i= 1 ; i <= _pCriteriaList->Size() ; i++)
     {
        CATUnicodeString CriterionValue = (*_pCriteriaList)[i] ;
        if ( CriterionValue.GetLengthInChar() > nbmaxchar ) 
        {
            nbmaxchar = CriterionValue.GetLengthInChar() ;
        }
        _pCriteriaCombo->SetLine(CriterionValue);
     }
  }
  _pCriteriaCombo->SetDropDownTextWidth(nbmaxchar);

  // Callbacks
  AddAnalyseNotificationCB(_pLaunchBtn, _pLaunchBtn->GetPushBActivateNotification(),
                (CATCommandMethod)&CAACafSearchDlg::LaunchBtn,
                            NULL);

  AddAnalyseNotificationCB(_pCriteriaCombo, _pCriteriaCombo->GetComboSelectNotification(),
                (CATCommandMethod)&CAACafSearchDlg::ComboSelected,
                            NULL);

  AddAnalyseNotificationCB(_pContextCombo, _pContextCombo->GetComboSelectNotification(),
                (CATCommandMethod)&CAACafSearchDlg::ComboSelected,
                            NULL);


}

//--------------------------------------------------------------------------------------

void CAACafSearchDlg::LaunchBtn    (CATCommand           * iPublisher ,
                                    CATNotification      * iNotification,
                                    CATCommandClientData   iUsefulData)
{
   cout << "CAACafSearchDlg::SearchNextBtn" << endl;
  
   // This notification enables the state command to receive it and 
   // to value its dialog agent to launch the query
   //
   CAACafLaunchNextQueryNotification * pNotification = NULL ;
   pNotification = new CAACafLaunchNextQueryNotification();     

   SendNotification(GetFather(),pNotification);
}

//--------------------------------------------------------------------------------------

void CAACafSearchDlg::ComboSelected    (CATCommand           * iPublisher ,
                                    CATNotification      * iNotification,
                                    CATCommandClientData   iUsefulData)
{
   cout << "CAACafSearchDlg::ComboSelected" << endl;

   _pResultQueryEditor->SetText("");

   if ( NULL != _pPso ) 
   {
      _pPso->Empty();
   }

}
//--------------------------------------------------------------------------------------

void CAACafSearchDlg::SetResultQueryEditorText(CATUnicodeString iText)
{
   cout << "CAACafSearchDlg::SetResultQueryEditorText" << endl;

   _pResultQueryEditor->SetText(iText);
}

//--------------------------------------------------------------------------------------
void CAACafSearchDlg::GetCurrentContext(CATIIniSearchContext::Scope & oCurrentContext)
{
   cout << "CAACafSearchDlg::GetCurrentContext" << endl;
   int value = _pContextCombo->GetSelect() ;

   switch ( value )
   {
       case 0 : oCurrentContext = CATIIniSearchContext::Everywhere ; break ;
       case 1 : oCurrentContext = CATIIniSearchContext::InUIActiveObject ; break ;
       case 2 : oCurrentContext = CATIIniSearchContext::FromUIActiveObjectToBottom ; break ;
       case 3 : oCurrentContext = CATIIniSearchContext::FromSelection ; break ;
       case 4 : oCurrentContext = CATIIniSearchContext::OnSameLevel ; break ;
   }

}

//--------------------------------------------------------------------------------------
void CAACafSearchDlg::GetCurrentCriterion(int & oCurrentCriterion)
{
   cout << "CAACafSearchDlg::GetCurrentCriterion" << endl;

   oCurrentCriterion = _pCriteriaCombo->GetSelect() ;
   oCurrentCriterion ++ ;
}

