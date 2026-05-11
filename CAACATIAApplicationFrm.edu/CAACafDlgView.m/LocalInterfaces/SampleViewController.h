// COPYRIGHT Dassault Systemes 2007

#ifndef SampleViewController_H
#define SampleViewController_H

#include "CATExtIDlgTableViewController.h"
#include "CATString.h"
#include "CATBaseUnknown.h"
#include "CATListOfSampleCell.h"
#include "CATLISTV_CATBaseUnknown.h"

#include "CATIDlgTableViewModel.h"
#include "CATBoolean.h"

class CATDlgTableView;
class SampleListEditor;

class SampleViewController: public CATExtIDlgTableViewController
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors
  // -------------------------------------
  SampleViewController (SampleListEditor * iView);
  virtual ~SampleViewController ();

  // Copy constructor and equal operator
  // -----------------------------------
  SampleViewController (SampleViewController &);
  SampleViewController& operator=(SampleViewController&);

  void SetModel(CATIDlgTableViewModel_var iModel);
  CATIDlgTableViewModel_var GetModel();

  // CATIDlgTableViewController implementation

  void ClearSelection( int iNotify= 1 );
  void RemoveFromSelection( const SampleCell &pCell );
  void AddToSelection( const SampleCell &pCell, int iNotify= 1 );
  int IsInSelection( const SampleCell &pCell );
  int SelectionCount();

  virtual HRESULT IsSelected( CATBaseUnknown_var iNode, CATBoolean & oResult );
  virtual HRESULT IsSelected( CATBaseUnknown_var iNode, const CATString& iColID, CATBoolean & oResult );
  virtual HRESULT IsPreSelected( CATBaseUnknown_var iNode, const CATString& iColID, CATBoolean & oResult );
  virtual HRESULT HasSelection( const CATString& iColumn, CATBoolean & oHasSelection );
  virtual HRESULT OnSelect( CATBaseUnknown_var iNode, const CATString& iColID );
  virtual HRESULT OnMoveOver( CATBaseUnknown_var iNode, const CATString& iColID );  
  virtual HRESULT OnActivate(CATBaseUnknown_var iItem );
  virtual HRESULT OnContext( CATBaseUnknown_var iNode );
  virtual HRESULT OnCellContext( CATBaseUnknown_var iNode, const CATString& iColID );
  virtual HRESULT OnRowHeaderContext( CATBaseUnknown_var iItem);
  virtual HRESULT OnColumnHeaderContext( const CATString& iColID );

  virtual void OnSampleContextualDependant( CATCallbackEvent, void *, CATNotification * evt, CATSubscriberData data, CATCallback );

  CATCallback RegisterItemSelectedEvent( CATEventSubscriber *iSubscriber, CATSubscriberMethod iMethod, CATSubscriberData iData );
  void UnregisterItemSelectedEvent( CATEventSubscriber *iSubscriber, CATCallback iUpdateCallback );

  void HighlightColumn(const CATString& iColID);
  virtual int ACellIsSelectedInTheColumn(const CATString& iColID);
  virtual int ACellIsSelectedInTheLine(CATBaseUnknown_var iItem);
  virtual int ACellIsSelectedInTheLine(const int iRow);
  CATListOfSampleCell GetSelectedCells();
  void LineSelection(CATBaseUnknown_var iItem, const CATBoolean &AddLine);

#define TEST2
  // ContextualMenu
#ifdef TEST1
  virtual void OnSelectContextualMenu( CATCallbackEvent, void *, CATNotification *, CATSubscriberData data, CATCallback );
#endif
#ifdef TEST2
  virtual void OnSelectContextualMenu( CATCommand *, CATNotification *, CATCommandClientData );
#endif

  // Two list synchronisation
  void OnScrollStart();
  void OnScroll();
  void OnScrollStop();
  void Synchronize(SampleListEditor *another, SampleViewController * anotherController, CATBoolean iHide=FALSE);
  void UpdateHighlight(CATBaseUnknown_var iItem);
  void UpdateHighlight(int iLine);

  protected:
  
  SampleListEditor *_another;
  SampleViewController * _anotherController;

  private:

  int GetItemRowIndex(CATBaseUnknown_var iNode);

  SampleListEditor * _view;
  CATIDlgTableViewModel_var _model;

  //  CATDefineCBEvent( ItemSelected );

  CATString _LastSelectedColumnID;
  CATString _LastHighlightedColumnID;

  CATBaseUnknown_var _PreSelectedRow;
  CATString _PreSelectedCol2;

  CATBaseUnknown_var _LastSelectedItem;
  SampleCell _LastCell;
    
  CATListOfSampleCell _SampleCells;

  int _ContextualLine;
  int _ContextualColumn;
  int _TypeOfModel;

  CATString _PreSelectedCol;
  CATListOfCATString _ColumnsWithSelectedCells;
};
#endif
