// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAMcaUdfLoftDlg.h"

// Dialog Framework
#include "CATDlgGridConstraints.h"
#include "CATDlgLabel.h"
#include "CATDlgSelectorList.h"
#include "CATMsgCatalog.h"          // To retrieve NLS message

// C++ Standard Library
#include "iostream.h"

//------------------------------------------------------------------------------------------

CAAMcaUdfLoftDlg::CAAMcaUdfLoftDlg(CATDialog * iParent): 
      CATDlgDialog (iParent,"CAAMcaUdfLoftDlg",
                    CATDlgWndBtnOKCancelPreview | CATDlgGridLayout),
_pLabelOfThePoint1(NULL),_pLabelOfThePoint2(NULL),
_pEditorOfThePoint1(NULL),_pEditorOfThePoint2(NULL)      
{
  cout << "CAAMcaUdfLoftDlg::CAAMcaUdfLoftDlg" << endl; 
}

//--------------------------------------------------------------------------------------

CAAMcaUdfLoftDlg::~CAAMcaUdfLoftDlg()
{
  cout << "CAAMcaUdfLoftDlg::~CAAMcaUdfLoftDlg" << endl;
  _pLabelOfThePoint1 = NULL ;
  _pLabelOfThePoint2 = NULL ;
  _pEditorOfThePoint1 = NULL ;
  _pEditorOfThePoint2 = NULL ;
}

//--------------------------------------------------------------------------------------

void CAAMcaUdfLoftDlg::Build()
{
   // Labels
   _pLabelOfThePoint1 = new CATDlgLabel(this, "LabelOfThePoint1");
   _pLabelOfThePoint1 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
   
   _pLabelOfThePoint2 = new CATDlgLabel(this, "LabelOfThePoint2");
   _pLabelOfThePoint2 -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);

   // Editor
   _pEditorOfThePoint1 = new CATDlgSelectorList(this, "EditorOfThePoint1");
   _pEditorOfThePoint1 -> SetVisibleTextHeight(1);
   _pEditorOfThePoint1 -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);

   _pEditorOfThePoint2 = new CATDlgSelectorList(this, "EditorOfThePoint2");
   _pEditorOfThePoint2 -> SetVisibleTextHeight(1);
   _pEditorOfThePoint2 -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);

   // One the inputs are not valuated
   CATUnicodeString NoSelectionMsg ;
   NoSelectionMsg = CATMsgCatalog::BuildMessage("CAAMcaUdfLoftDlg",
                                        "NoSelectionMsg",NULL,0,
                                        "no selection");

   _pEditorOfThePoint1 -> SetLine(NoSelectionMsg);
   _pEditorOfThePoint2 -> SetLine(NoSelectionMsg);

   // The first point to choose if the point represented
   // by the the first selector
   // 
   int RowNb = 0 ;
   _pEditorOfThePoint1->SetSelect(&RowNb, 1);
   _ActiveEditor = 1 ;

   // Callbacks which enables the end user to change the current input to
   // valuate
   AddAnalyseNotificationCB (_pEditorOfThePoint1, 
                              _pEditorOfThePoint1->GetListSelectNotification(),
                              (CATCommandMethod)&CAAMcaUdfLoftDlg::EditorSelect,
                              (void*)1);

   AddAnalyseNotificationCB (_pEditorOfThePoint2, 
                              _pEditorOfThePoint2->GetListSelectNotification(),
                              (CATCommandMethod)&CAAMcaUdfLoftDlg::EditorSelect,
                              (void*)2);
                              
}

//--------------------------------------------------------------------------------------

void CAAMcaUdfLoftDlg::EditorSelect(CATCommand* cmd, 
                                    CATNotification* evt, 
                                    CATCommandClientData data)
{
    
    int number = CATPtrToINT32(data); 

    if (_ActiveEditor != number) 
    {
        if ( _pEditorOfThePoint1 == cmd )
        {
           _pEditorOfThePoint2->ClearSelect();
        }
        else if ( _pEditorOfThePoint2 == cmd )
        {
          _pEditorOfThePoint1->ClearSelect();
        }
    }

    _ActiveEditor = number;
}

//--------------------------------------------------------------------------------------

int CAAMcaUdfLoftDlg::GetActiveEditorNumber()
{
    if (_pEditorOfThePoint1->IsSelect(0)) _ActiveEditor= 1;
    if (_pEditorOfThePoint2->IsSelect(0)) _ActiveEditor= 2;

    return _ActiveEditor; 
}

//--------------------------------------------------------------------------------------

void CAAMcaUdfLoftDlg::SetPointName(int iPointNumber , CATUnicodeString iName )
{
    int RowNb = 0;
    if ( 1 == iPointNumber )
    {
       _pEditorOfThePoint1->ClearLine();
       _pEditorOfThePoint1->SetLine ( iName ); 
       _pEditorOfThePoint2->SetSelect(&RowNb, 1);
    }else
    {
       _pEditorOfThePoint2->ClearLine();
       _pEditorOfThePoint2->SetLine (iName); 
       _pEditorOfThePoint1->SetSelect(&RowNb, 1);
    }
}

//--------------------------------------------------------------------------------------

void CAAMcaUdfLoftDlg::SetRole(int iPointNumber , CATUnicodeString iName )
{
    int RowNb = 0;
    if ( 1 == iPointNumber )
    {
       _pLabelOfThePoint1-> SetTitle(iName+"  "); 
    }else
    {
       _pLabelOfThePoint2-> SetTitle(iName+"  "); 
    }
}

//--------------------------------------------------------------------------------------

void CAAMcaUdfLoftDlg::InitPointName(CATUnicodeString iName1 , CATUnicodeString iName2 )
{
    _pEditorOfThePoint1->ClearLine();
    _pEditorOfThePoint1->SetLine (iName1); 
 
    _pEditorOfThePoint2->ClearLine();
    _pEditorOfThePoint2->SetLine (iName2); 
    
    // SetLine removes the line of the selection. So the first SetSelect, done
    // in the Build Method is invalided by the first ClearLine/SetLine of this
    // method.
    //
    int RowNb = 0 ;
    _pEditorOfThePoint1->SetSelect(&RowNb, 1);
    _ActiveEditor = 1  ;
}

//--------------------------------------------------------------------------------------

