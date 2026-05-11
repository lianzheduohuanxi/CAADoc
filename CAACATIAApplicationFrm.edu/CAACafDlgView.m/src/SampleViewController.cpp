// COPYRIGHT Dassault Systemes 2007

#include "SampleViewController.h"

#include "CATCommand.h"
#include "CATFrmEditor.h"
#include "CATCSO.h"
#include "CATPathElement.h"
#include "CATCallbackManager.h"
// SCA : CATSysMacros.h etait inclus pour CATSysReleasePtr mais est ProtectedInterfaces.
//       De plus, le CATSysReleasePtr etait utilise a la place d'un Release, pourquoi ?
//#include "CATSysMacros.h"
#include "CATMsgCatalog.h"
#include "SampleViewModel.h"
#include "SampleListEditor.h"

#ifdef TEST1
#include "SamplePushItem.h"
#endif
#ifdef TEST2
#include "CATDlgPushItem.h"
#endif

#include "CATDeviceEvent.h"
#include "CATIDlgTableViewController.h"
#include "CATIDlgTableViewModel.h"

CATImplementClass(SampleViewController,
  Implementation,
  CATExtIDlgTableViewController,
  CATNull);

#include  <TIE_CATIDlgTableViewController.h>  
TIE_CATIDlgTableViewController(SampleViewController);  

//CATImplementCBEvent(SampleViewController, ItemSelected, "ItemSelected");

#define NO_TRACES_CONTROL
#define NO_TRACES_SYNCHRO
#define TRACES_CONTEXT

#if defined(TRACES_CONTROL) || defined(TRACES_SYNCHRO) || defined(TRACES_CONTEXT)
#include <iostream.h>
#endif

//-----------------------------------------------------------------------------
// SampleViewController : constructor
//-----------------------------------------------------------------------------
SampleViewController::SampleViewController(SampleListEditor* iView):
  CATExtIDlgTableViewController(), 
  _view(iView),
  _model(NULL_var),
  _ContextualLine(0),
  _ContextualColumn(0),
  _TypeOfModel(-1),
  _another(NULL),
  _anotherController(NULL)
{
#ifdef TRACES_CONTROL
  cout << this << ", A new SampleViewController" << endl;
#endif
  _LastHighlightedColumnID = "";
  _PreSelectedRow = NULL;
  _PreSelectedCol2 = "";
}

//-----------------------------------------------------------------------------
// SampleViewController : destructor
//-----------------------------------------------------------------------------
SampleViewController::~SampleViewController()
{
#ifdef TRACES_CONTROL
  cout << this << ", A deleted SampleViewController" << endl;
#endif
  // clean out callbacks placed on this controller
//   CATCallbackManager* mgr = GetCallbackManager();
//   if(mgr) mgr->RemoveAllCallbacks();

  //Clean the selection list
  ClearSelection(0);

  _view = NULL;
  _model = NULL;
  _another = NULL;
  _anotherController = NULL;
}

void SampleViewController::SetModel(CATIDlgTableViewModel_var iModel)
{
  _model = iModel;
}

CATIDlgTableViewModel_var SampleViewController::GetModel()
{
  return _model;
}

HRESULT SampleViewController::OnSelect(CATBaseUnknown_var iItem, const CATString& iColumnID)
{
  if (!_view) return S_OK;

#ifdef TRACES_CONTROL
  cout << this << ", SampleViewController::OnSelect(" << GetItemRowIndex(iItem) << ", " << iColumnID << ")" << endl;
#endif

  // SCA : Because the same code for 2 different controllers.
  if (_TypeOfModel == -1)
  {
    if (!!_model)
    {
      CATBaseUnknown* BUModel = NULL;
      HRESULT RC = _model->QueryInterface(IID_CATBaseUnknown, (void**) &BUModel);
      if (SUCCEEDED(RC))
      {
        if (BUModel->IsAKindOf("SampleViewModel"))
          _TypeOfModel = 1;
        if (BUModel->IsAKindOf("SampleVariantModel"))
          _TypeOfModel = 2;
        // SCA : CATSysMacros.h etait inclus pour CATSysReleasePtr mais est ProtectedInterfaces.
        //       De plus, le CATSysReleasePtr etait utilise a la place d'un Release, pourquoi ?
        //CATSysReleasePtr(BUModel); 
        BUModel->Release(); 
      }
    }
  }
  if (_TypeOfModel == -1) return E_FAIL;

  SampleCell pCell(iItem, iColumnID);

  if ((_view->GetDeviceEvent()->GeneralModifier == ShiftModifierOn) && (SelectionCount() > 0))
  {
#ifdef TRACES_CONTROL
    cout << this << ", SampleViewController::OnSelect with SHIFT key" << endl;
#endif
    // Remarks for cells selection
    // 1. If no item previously selected: behaves as single selection
    // 2. Else: if current selection in the same column as previous: grep the items in between
    // 3. Else: if current selection in the same column as previous: grep the items within the squarre (not implemented)

    // 3.
    //Row range
    int index1 = GetItemRowIndex(_LastSelectedItem);
    int index2 = GetItemRowIndex(iItem);
    int lowR = 0;
    int highR = 0;

    if (index1 > index2)
    {
      lowR = index2;
      highR = index1;
    }
    else
    {
      lowR = index1;
      highR = index2;
    }

    int delta = highR - lowR + 1;

    //Grep the corresponding cells
    if( _TypeOfModel == 1 && !!_model )
    {
      //Highlight the line
      //Remove previous selection. It will be re-included here after. The goal is to ease the algorithm.
      CATBoolean AddLine = CATFalse;
      LineSelection(_LastSelectedItem, AddLine);

      CATListOfCATBaseUnknown_var fullList;
      _model->GetLines(lowR, delta, fullList); 
      AddLine = CATTrue;
      for (int i=1; i<=fullList.Size(); i++)
        LineSelection(fullList[i], AddLine);
    }
    if( _TypeOfModel == 2 && !!_model )
    {
      //Column range
      // 2.
      if (_LastSelectedColumnID != iColumnID)
        return S_OK;

      //Highlight the column
      //Remove previous selection. It will be re-included here after. The goal is to ease the algorithm.
      RemoveFromSelection(_LastCell);

      CATListOfCATBaseUnknown_var fullList;
      _model->GetLines(lowR, delta, fullList);     
      for (int i=1; i<=fullList.Size(); i++)
      {
        SampleCell Cell(fullList[i], iColumnID);
        AddToSelection(Cell);
      }
    }
  }
  else if (_view->GetDeviceEvent()->GeneralModifier == ControlModifierOn)
  {
#ifdef TRACES_CONTROL
    cout << this << ", SampleViewController::OnSelect with CONTROL key" << endl;
#endif

    //If the view is "SampleViewModel", then highlight the line
    if( _TypeOfModel == 1 )
    {
      CATBoolean AddLine;
      if (IsInSelection(pCell) >= 1)
        AddLine = CATFalse;
      else
        AddLine = CATTrue;  
      LineSelection(iItem, AddLine);
    }
    if( _TypeOfModel == 2 )
    {
      //Take into account only the cell
      if (IsInSelection(pCell) >= 1)
        RemoveFromSelection(pCell);
      else
        AddToSelection(pCell);
    }
  }
  else
  {
#ifdef TRACES_CONTROL
    cout << "SampleViewController::OnSelect without key" << endl;
#endif
    ClearSelection(0);

    //If the view is "SampleViewModel", then highlight the line
    if( _TypeOfModel == 1 )
    {
      //Line Selection
      CATBoolean AddLine = CATTrue;
      LineSelection(iItem, AddLine);
    }
    if( _TypeOfModel == 2 )
    {
      //Cell Selection
      AddToSelection(pCell);
    }
  }

  // SCA : Used in OnRowHeaderContext method
  _LastSelectedColumnID = iColumnID;
  _LastHighlightedColumnID = "";

  //MBH : used for SHIFT / CTRL keys 
  _LastCell = pCell;
  _LastSelectedItem = iItem;

  if (_view) _view->Draw();

  // SCA : Used for OnActivate and OnEdit methods.
  _PreSelectedCol = iColumnID;

  //Send notification to the application
  _view->SendNotification(_view, _view->GetSelectionNotification());

  return S_OK;
}

#ifdef TEST1
void SampleViewController::OnSelectContextualMenu( CATCallbackEvent, void *, CATNotification * evt, CATSubscriberData data, CATCallback)
{
   if (!_view) return;

#ifdef TRACES_CONTEXT
  cout << "SampleViewController::OnSelectContextualMenu()" << endl;
#endif
}
#endif
#ifdef TEST2
void SampleViewController::OnSelectContextualMenu( CATCommand *iCmd, CATNotification *iNotif, CATCommandClientData iData)
{
   if (!_view) return;

#ifdef TRACES_CONTEXT
  cout << "SampleViewController::OnSelectContextualMenu()" << endl;
#endif
}
#endif

HRESULT SampleViewController::OnColumnHeaderContext(const CATString& iColumnID)
{
  //Display contextual menu specific to column header
  if (!_view) return S_OK;
  CATDlgContextualMenu* pMenu = _view->GetMenu();

#ifdef TRACES_CONTEXT
  cout << "SampleViewController::OnColumnHeaderContext(" << iColumnID << ")" << endl;
  if(pMenu)
      cout << "  CATDlgContextualMenu is " << pMenu->GetName() << endl;
  else
      cout << "  CATDlgContextualMenu is NULL !" << endl;
#endif
  
  if(pMenu)
  {
#ifdef TEST1
    // Pb SampleViewController n'herite plus d'une CATCommand.
    SamplePushItem* pRevertRowItem = new SamplePushItem(pMenu, "LVMenuRevertRow");
    pRevertRowItem->SetTitle(CATUnicodeString("Contextual menu for header of COLUMN "+iColumnID));
    pRevertRowItem->RegisterItemActivatedEvent(pMenu, (CATSubscriberMethod)&SampleViewController::OnSelectContextualMenu, NULL);
    pMenu->SetVisibility(CATDlgShow);
#endif
#ifdef TEST2
    // Pb SampleViewController n'herite plus d'une CATCommand.
    CATDlgPushItem* pRevertRowItem = new CATDlgPushItem(pMenu, "LVMenuRevertRow");
    pRevertRowItem->SetTitle(CATUnicodeString("Contextual menu for header of COLUMN "+iColumnID));
    //AddAnalyseNotificationCB(pRevertRowItem, pRevertRowItem->GetMenuIActivateNotification(),
                           //(CATCommandMethod)&SampleViewController::OnSelectContextualMenu, (CATCommandClientData)this);
    pMenu->SetVisibility(CATDlgShow);
#endif
  }

  return S_OK;
}

/**
 * Request for contextual menu on one of the view's row headers
 */
HRESULT SampleViewController::OnRowHeaderContext(CATBaseUnknown_var iItem)
{
  //Display contextual menu specific to row header
  if (!_view) return S_OK;
  CATDlgContextualMenu* pMenu = _view->GetMenu();

#ifdef TRACES_CONTEXT
  cout << "SampleViewController::OnColumnHeaderContext(" << iItem << ")" << endl;
  if(pMenu)
      cout << "  CATDlgContextualMenu is " << pMenu->GetName() << endl;
  else
      cout << "  CATDlgContextualMenu is NULL !" << endl;
#endif

  if(pMenu)
  {
#ifdef TEST1
    // Pb SampleViewController n'herite plus d'une CATCommand.
    SamplePushItem* pRevertRowItem = new SamplePushItem(pMenu, "LVMenuRevertRow");
    pRevertRowItem->SetTitle("Contextual menu for header of ROW");
    pRevertRowItem->RegisterItemActivatedEvent(pMenu, (CATSubscriberMethod)&SampleViewController::OnSelectContextualMenu, NULL);
    pMenu->SetVisibility(CATDlgShow);
#endif
#ifdef TEST2
    // Pb SampleViewController n'herite plus d'une CATCommand.
    CATDlgPushItem* pRevertRowItem = new CATDlgPushItem(pMenu, "LVMenuRevertRow");
    pRevertRowItem->SetTitle("Contextual menu for header of ROW");
    //AddAnalyseNotificationCB(pRevertRowItem, pRevertRowItem->GetMenuIActivateNotification(),
                           //(CATCommandMethod)&SampleViewController::OnSelectContextualMenu, (CATCommandClientData)this);
    pMenu->SetVisibility(CATDlgShow);
#endif
  }

  return S_OK;
}

void SampleViewController::OnSampleContextualDependant(CATCallbackEvent, void *, CATNotification * evt, CATSubscriberData data, CATCallback)
{
#ifdef TRACES_CONTEXT
  cout << this << ", SampleViewController::OnSampleContextualDependant(" << _ContextualLine << ", " << _ContextualColumn << ")" << endl;
#endif
}

// int SampleViewController::GetItemRowIndex(CATBaseUnknown_var iItem)
// {
//   //Here we should distinguish between "SampleViewModel::GetRowId" and "SampleVariantModel::GetRowId"
//   //...we are lucky because the have the same data structure for this sample.
//   return SampleViewModel::GetRowId(iItem);
// }

// TODO : revoirle mecanisme d'update
// CATCallback SampleViewController::RegisterItemSelectedEvent(CATEventSubscriber *iSubscriber,
//   CATSubscriberMethod iMethod,
//   CATSubscriberData iData)
// {
//   if( iSubscriber)
//   {
//     return iSubscriber->AddCallback(this, ItemSelected(), iMethod, iData);
//   }
//   else
//   {
//     return NULL;
//   }
// }

// void SampleViewController::UnregisterItemSelectedEvent(CATEventSubscriber *iSubscriber, CATCallback iUpdateCallback)
// {
//   if( iSubscriber)
//   {
//     iSubscriber->RemoveCallback(this, iUpdateCallback);
//   }
// }

HRESULT SampleViewController::HasSelection( const CATString& iColumnID, CATBoolean & oHasSelection )
{
    oHasSelection = ACellIsSelectedInTheColumn(iColumnID);

    return S_OK;
}

int SampleViewController::ACellIsSelectedInTheColumn(const CATString& iColumnID)
{
  // SCA : Pour le model SampleViewModel, ne rien faire
  if (_TypeOfModel == 1 || _TypeOfModel == -1) return 0;

  // SCA : Pour le model SampleVariantModel, compare to the selection list
  return _ColumnsWithSelectedCells.Locate(iColumnID);
}

int SampleViewController::ACellIsSelectedInTheLine(CATBaseUnknown_var iItem)
{
  int result = 0;

  for (int i=1; i<=_ColumnsWithSelectedCells.Size() && !result; i++)
  {
    CATBoolean oSelected = FALSE;
    HRESULT hr = IsSelected(iItem, _ColumnsWithSelectedCells[i], oSelected);
    result = (oSelected ? 1 : 0);
  }

  // TODO : S'il existe une liste synchronisee ?
  if (_anotherController && result == 0)
  {
      int index = GetItemRowIndex(iItem);
      result = _anotherController->ACellIsSelectedInTheLine(index);
  }

  return result;
}

int SampleViewController::ACellIsSelectedInTheLine(const int iRow)
{
  int result = 0;

  return result;
}

void SampleViewController::HighlightColumn(const CATString& iColumnID)
{
#ifdef TRACES_CONTROL
  cout << this << ", SampleViewController::HighlightColumn(" << iColumnID << ")" << endl;
#endif

  if (strcmp(_LastHighlightedColumnID, iColumnID) == 0)
  {
    //Do not highlight twice
#ifdef TRACES_CONTROL
    cout << "  " << iColumnID << " already highlighted" << endl;
#endif
    return;
  }

  if (!!_model)
  {
    int count = 0;
    _model->GetLineCount(count);
    CATListOfCATBaseUnknown_var fullList;
    _model->GetLines(0, count, fullList);

    //Empty le selection list
    ClearSelection(0);

    _LastHighlightedColumnID = iColumnID;

    //Fill the selection list
    for (int i=1; i<=count; i++)  
    {
#ifdef TRACES_CONTROL
      cout << "  ObjList[" << i << "] = " << fullList[i] << endl;
#endif
      SampleCell pCell(fullList[i], iColumnID);
      AddToSelection(pCell, 0);
    }

    //Update the view
    if (_view) _view->Draw();

    //Send notification to the application
    if (_view)
      _view->SendNotification(_view, _view->GetSelectionNotification());
  }
}

HRESULT SampleViewController::IsSelected(CATBaseUnknown_var iItem, CATBoolean & oSelected)
{
#if defined(TRACES_CONTROL)
  cout << this << ", SampleViewController::IsSelected(" << GetItemRowIndex(iItem) << "), model = " << _TypeOfModel << endl;
#endif

  if (_TypeOfModel == -1)
  {
#if defined(TRACES_CONTROL)
  cout << "  Model undefined" << endl;
#endif
    oSelected = FALSE;
  }
  //If the view is "SampleViewModel"
  // Dans ce cas, il suffit que la premiere cellule soit selectionnee
  else if( _TypeOfModel == 1 )
  {
#if defined(TRACES_CONTROL)
  cout << "  Model View, selection par ligne" << endl;
#endif
    oSelected = FALSE;
  }
  //If the view is "SampleVariantModel"
  // Dans ce cas, il suffit qu'une cellule soit selectionnee
  else if( _TypeOfModel == 2 )
  {
#if defined(TRACES_CONTROL)
  cout << "  Model Variant, selection par cellule" << endl;
#endif
    oSelected = ACellIsSelectedInTheLine(iItem);
  }

  return S_OK;
}

HRESULT SampleViewController::IsSelected(CATBaseUnknown_var iItem, const CATString& iColumnID, CATBoolean & oSelected)
{
#ifdef TRACES_CONTROL
  cout << this << ", SampleViewController::IsSelected(" << GetItemRowIndex(iItem) << ", " << iColumnID << ")" << endl;
#endif
  SampleCell pCell(iItem, iColumnID);

  oSelected = IsInSelection(pCell);

  return S_OK;
}

HRESULT SampleViewController::IsPreSelected(CATBaseUnknown_var iItem, const CATString& iColumnID, CATBoolean & result)
{
  result = FALSE;
#ifdef TRACES_CONTROL
  //cout << this << ", SampleViewController::IsPreSelected(" << GetItemRowIndex(iItem) << ", " << iColumnID << endl;
#endif
  if (_TypeOfModel == -1)
  {
    result = FALSE;
  }
  //If the view is "SampleViewModel"
  else if( _TypeOfModel == 1 )
  {
    if (_PreSelectedRow == iItem)
      result = TRUE;
    else
      result = FALSE;
  }
  //If the view is "SampleVariantModel"
  else if( _TypeOfModel == 2 )
  {
    if (_PreSelectedRow == iItem && _PreSelectedCol2 == iColumnID)
      result = TRUE;
    else
      result = FALSE;
  }

  return S_OK;
}

HRESULT SampleViewController::OnMoveOver(CATBaseUnknown_var iItem, const CATString& iColumnID)
{
#ifdef TRACES_CONTROL
  //cout << this << ", SampleViewController::OnMoveOver(" << GetItemRowIndex(iItem) << ", " << iColumnID << ")" << endl;
#endif
  // If cursor still in same row & column, do nothing
  if( _PreSelectedRow == iItem && !_PreSelectedCol2.Compare(iColumnID))
    return S_OK;

  _PreSelectedCol = iColumnID;
  _PreSelectedCol2 = iColumnID;

  //Change pre-highlighting
  CATBaseUnknown_var last(_PreSelectedRow);
  _PreSelectedRow= iItem;
  if (_view)
  {
    if( !!last)
    {
      _view->UpdateHighlight(last);
    }
    if( !!_PreSelectedRow)
    {
      _view->UpdateHighlight(_PreSelectedRow);
    }
  }
  return S_OK;
}

HRESULT SampleViewController::OnContext(CATBaseUnknown_var iItem)
{
#ifdef TRACES_CONTEXT
  cout << "SampleViewController::OnContext(" << GetItemRowIndex(iItem) << ")" << endl;
#endif
  return S_OK;
}

HRESULT SampleViewController::OnCellContext(CATBaseUnknown_var iItem, const CATString& iColumnID)
{
  //If cell is not already selected, treat "right click" as left "click" + "right click"
  SampleCell pCell(iItem, iColumnID);
  if(!IsInSelection(pCell))
  {
    OnMoveOver(iItem, iColumnID);
    OnSelect(iItem, iColumnID);
  }

  //Display contextual menu specific to cell
  if (!_view) return S_OK;

  CATDlgContextualMenu* pMenu = _view->GetMenu();

#ifdef TRACES_CONTEXT
  cout << "SampleViewController::OnCellContext(" << iColumnID << ")" << endl;
  if(pMenu)
      cout << "  CATDlgContextualMenu is " << pMenu->GetName() << endl;
  else
      cout << "  CATDlgContextualMenu is NULL !" << endl;
#endif

  if(pMenu)
  {
#ifdef TEST1
    // Pb SampleViewController n'herite plus d'une CATCommand.
    SamplePushItem* pRevertRowItem = new SamplePushItem(pMenu, "LVMenuRevertRow");
    if (SelectionCount() <= 1)
      pRevertRowItem->SetTitle("This is a test for mono-sel");
    else
      pRevertRowItem->SetTitle("This is a test for multi-cell");
    pRevertRowItem->RegisterItemActivatedEvent(pMenu, (CATSubscriberMethod)&SampleViewController::OnSelectContextualMenu, NULL);
    pMenu->SetVisibility(CATDlgShow);
#endif
#ifdef TEST2
    // Pb SampleViewController n'herite plus d'une CATCommand.
    CATDlgPushItem* pRevertRowItem = new CATDlgPushItem(pMenu, "LVMenuRevertRow");
    if (SelectionCount() <= 1)
      pRevertRowItem->SetTitle("This is a test for mono-sel");
    else
      pRevertRowItem->SetTitle("This is a test for multi-cell");
    //AddAnalyseNotificationCB(pRevertRowItem, pRevertRowItem->GetMenuIActivateNotification(),
                           //(CATCommandMethod)&SampleViewController::OnSelectContextualMenu, (CATCommandClientData)this);
    pMenu->SetVisibility(CATDlgShow);
#endif
  }

  return S_OK;
}

CATListOfSampleCell SampleViewController::GetSelectedCells()
{
#ifdef TRACES_CONTROL
  cout << this << ", SampleViewController::GetSelectedCells()" << endl;
#endif

  CATListOfSampleCell oSelection(_SampleCells);
  return oSelection;
}

void SampleViewController::ClearSelection(int iNotify)
{
#ifdef TRACES_CONTROL
  cout << this << ", SampleViewController::ClearSelection()" << endl;
#endif

  // SCA : Mise a jour du CATCellEditController
  _ColumnsWithSelectedCells.RemoveAll();

  // TODO : boucler sur la liste pour updater le highlight

  //Empty the list
  _SampleCells.RemoveAll();

  // CATCellEditController::ClearSelection(iNotify);

  //Update the view
  if (_view) _view->Draw();

  _LastHighlightedColumnID = "";
  _PreSelectedRow = NULL;
  _PreSelectedCol2 = "";
}

void SampleViewController::RemoveFromSelection (const SampleCell &pCell)
{
  // SCA : Mise a jour du CATCellEditController
  CATBaseUnknown_var item = pCell._iRow;
  //CATCellEditController::RemoveFromSelection(item);
  // TODO : gerer une liste des objets de la selection
  if (_view) _view->UpdateHighlight(item);

  CATString colID = pCell._iCol;
  _ColumnsWithSelectedCells.RemoveValue(colID);

#ifdef TRACES_CONTROL
  cout << "SampleViewController::RemoveFromSelection(" << colID << ")" << endl;
#endif

  //Remove the selected item from the list
  _SampleCells.RemoveValue(pCell);
}

int SampleViewController::IsInSelection(const SampleCell &pCell)
{   
#ifdef TRACES_CONTROL
  CATString colID = pCell._iCol;
  cout << this << ", SampleViewController::IsInSelection(" << colID << ") = " << _SampleCells.Locate(pCell) << endl;
#endif

  //Compare to the selection list
  return _SampleCells.Locate(pCell);
}

void SampleViewController::AddToSelection(const SampleCell &pCell, int iNotify)
{
  // SCA : Mise a jour du CATCellEditController
  CATBaseUnknown_var item = pCell._iRow;
  //CATCellEditController::AddToSelection(item, iNotify);
  // TODO : gerer une liste des objets de la selection
  if (_view) _view->UpdateHighlight(item);

  CATString colID = pCell._iCol;
  if (!_ColumnsWithSelectedCells.Locate(colID))
    _ColumnsWithSelectedCells.Append(colID);

#ifdef TRACES_CONTROL
  cout << this << ", SampleViewController::AddToSelection(" << colID << ")" << endl;
#endif

  //Append to the selection list
  if (!IsInSelection(pCell))
    _SampleCells.Append(pCell);
}

int SampleViewController::SelectionCount()
{
  return (_SampleCells.Size());
}

void SampleViewController::LineSelection(CATBaseUnknown_var iItem, const CATBoolean &AddLine)
{
  CATString ColID;
  char pColID[100] = "";
  for (int i=1; i<=10; i++)
  {
    sprintf(pColID, "Col0%d", i);
    
    if (i==10)
      ColID = "Col10";
    else
      ColID = pColID;

    SampleCell Cell(iItem, ColID);
    if (AddLine)
      AddToSelection(Cell);
    else
      RemoveFromSelection(Cell);
  }
}

void SampleViewController::Synchronize(SampleListEditor *another, SampleViewController *anotherController, CATBoolean iHide)
{
#ifdef TRACES_SYNCHRO
  cout << this << ", SampleListEditor::Synchronize(" << another << ")" << endl;
#endif
  if (!_view) return;

  if (_another == another || !another) return;

  // SCA : Si Hide est FALSE, thisController pilote anotherController
  if (!iHide)
  {
    _another = another;
    _anotherController = anotherController;
    // SCA : et donc on cache l'ascenseur de anotherListEditor
    another->SetScrollXVisibility(1);
    another->SetScrollYVisibility(0);
  }

  // SCA : Si Hide est TRUE, anotherController pilote thisController
  if (iHide && anotherController)
  {
    anotherController->Synchronize(_view, this, !iHide);
  }
}

void SampleViewController::UpdateHighlight(CATBaseUnknown_var iItem)
{
#ifdef TRACES_SYNCHRO
  cout << this << ", SampleListEditor::UpdateHightlight(" << iItem << ")" << endl;
#endif
  if (_anotherController)
  {
    // SCA : Avoids the loop between synchronized lists.
    _anotherController->_anotherController = NULL;
    _anotherController->_another = NULL;
    _anotherController->UpdateHighlight(GetItemRowIndex(iItem));
    _anotherController->_another = _view;
    _anotherController->_anotherController = this;
  }
}

void SampleViewController::OnScrollStart( void )
{
#ifdef TRACES_SYNCHRO
  cout << this << ", SampleViewController::OnScrollStart()" << endl;
#endif
}

void SampleViewController::OnScroll( void )
{
#ifdef TRACES_SYNCHRO
  cout << this << ", SampleViewController::OnScroll()" << endl;
#endif

  if (_view && _another)
  {
    float yscroll = _view->GetScrollY();
    int iForce = 0;
    if (_another->GetScrollYVisibility() == 0)
      iForce = 1;
    _another->SetScrollY(yscroll, iForce);
  }
}

void SampleViewController::OnScrollStop( void )
{
#ifdef TRACES_SYNCHRO
  cout << this << ", SampleViewController::OnScrollStop()" << endl;
#endif
}

void SampleViewController::UpdateHighlight(int iLine)
{
#ifdef TRACES_SYNCHRO
  cout << this << ", SampleListEditor::UpdateHightlight(" << iLine << ")" << endl;
#endif
}

HRESULT SampleViewController::OnActivate(CATBaseUnknown_var iItem)
{
  if (_view)
    _view->Edit(iItem,_PreSelectedCol);
  return S_OK;
}

int SampleViewController::GetItemRowIndex(CATBaseUnknown_var iItem)
{
  int result = -1;
  if( _view )
    result = _view->GetRow( iItem )-1;

  return result;
}

