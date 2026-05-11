/**
 * @quickReview ZGG 02:03:05
 */
// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// CAATpiRetrieveAnnotationWnd
//   Works with the state command CATTpiRetrieveAnnotationCmd.
//   Panel to display the list of Alias of the 3D annotations which are
//   linked to the geometry selected.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Fev. 2002  Creation
//=============================================================================

//-------------------------------------------------- Include File of this class
#include "CAATpiRetrieveAnnotationWnd.h"

//---------------------------------------------------------------------- System
#include "CATString.h"
#include "CATUnicodeString.h"
#include "CATMsgCatalog.h"
#include "CATListOfCATUnicodeString.h"

//------------------------------------------------------------ ApplicationFrame
#include "CATApplicationFrame.h"

//---------------------------------------------------------------------- Dialog
#include "CATDlgMultiList.h"

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAATpiRetrieveAnnotationWnd::CAATpiRetrieveAnnotationWnd() 
: CATDlgDialog (
             (CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
             "CAATpiRetrieveAnnotationWnd", 
             CATDlgWndNoResize | CATDlgWndBtnClose | CATDlgWndTitleBarHelp)
, _pAliasList (NULL)
{
  _pAliasList = new CATDlgMultiList (this, "AliasList",CATDlgLstAutoSort);
 
  CATString MsgCatalogName ("CAATpiRetrieveAnnotationWnd");
  CATString MsgKey ("AliasList.ColumnTitle");
  CATUnicodeString Title = CATMsgCatalog::BuildMessage(MsgCatalogName, MsgKey);

  _pAliasList -> SetVisibleColumnCount (1);
  _pAliasList -> SetVisibleLineCount (6);
  _pAliasList -> SetColumnTextWidth (0, 15);
  _pAliasList -> SetColumnTitles (1, &Title);
}


//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAATpiRetrieveAnnotationWnd::~CAATpiRetrieveAnnotationWnd ()
{
  _pAliasList = NULL;
}


//-----------------------------------------------------------------------------
// SetAliasList
//-----------------------------------------------------------------------------
HRESULT CAATpiRetrieveAnnotationWnd::SetAliasList (
                                        CATListValCATUnicodeString &iAliasList)
{
  if ( !_pAliasList ) return (E_FAIL);

  HRESULT oRc = S_OK;

  // Erase all existing lines
  _pAliasList -> ClearLine();

  int Count = iAliasList.Size ();

  // Fill multi list with the list of alias
  for (int Idx = 0 ; Idx < Count ; Idx ++)
  {
    _pAliasList -> SetColumnItem (0, iAliasList[Idx+1]);
  }
  return (oRc);
}
