/**
 * @quickReview ZGG 02:06:05
 * @quickReview ZGG 02:03:05
 */
// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// CAATpiAccessGeometryWnd
//   Works with the state command CATTpiAccessGeometryCmd.
//   Panel to display the geometry analysis of the selected 3D Annotation.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Fev. 2002  Creation
//=============================================================================

//-------------------------------------------------- Include File of this class
#include "CAATpiAccessGeometryWnd.h"

//---------------------------------------------------------------------- System
#include "CATBoolean.h"
#include "CATString.h"
#include "CATUnicodeString.h"
#include "CATMsgCatalog.h"
#include "CATListOfCATUnicodeString.h"

//------------------------------------------------------------ ApplicationFrame
#include "CATApplicationFrame.h"

//---------------------------------------------------------------------- Dialog
#include "CATDlgMultiList.h"
#include "CATDlgCheckButton.h"
#include "CATDlgGridConstraints.h"

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAATpiAccessGeometryWnd::CAATpiAccessGeometryWnd() 
: CATDlgDialog (
             (CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
             "CAATpiAccessGeometryWnd", 
             CATDlgWndNoResize | CATDlgWndBtnClose | CATDlgWndTitleBarHelp |
             CATDlgGridLayout)
, _pComposList (NULL)
, _pDisplay3DGridCkB (NULL)
, _pDisplayTTRSRepCkB (NULL)
{
  _pComposList = new CATDlgMultiList (this,"AnalysisList",CATDlgLstAutoSort);
 
  CATString MsgCatalogName ("CAATpiAccessGeometryWnd");
  CATString MsgKey ("CompositionList.ColumnTitle");
  CATUnicodeString Title = CATMsgCatalog::BuildMessage(MsgCatalogName, MsgKey);

  _pComposList -> SetVisibleColumnCount (1);
  _pComposList -> SetVisibleLineCount (6);
  _pComposList -> SetColumnTextWidth (0, 15);
  _pComposList -> SetColumnTitles (1, &Title);
  _pComposList -> SetGridConstraints (0, 0, 1, 1, CATGRID_4SIDES);

  _pDisplay3DGridCkB = new CATDlgCheckButton (this, "Display3DGridCkB");
  _pDisplay3DGridCkB -> SetState (CATDlgCheck, 0);
  _pDisplay3DGridCkB -> SetGridConstraints (1, 0, 1, 1, CATGRID_4SIDES);

  _pDisplayTTRSRepCkB = new CATDlgCheckButton (this, "DisplayTTRSRepCkB"); 
  _pDisplayTTRSRepCkB -> SetState (CATDlgCheck, 0);
  _pDisplayTTRSRepCkB -> SetGridConstraints (2, 0, 1, 1, CATGRID_4SIDES);
}


//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAATpiAccessGeometryWnd::~CAATpiAccessGeometryWnd ()
{
  _pComposList = NULL;
  _pDisplay3DGridCkB = NULL;
  _pDisplayTTRSRepCkB = NULL;
}


//-----------------------------------------------------------------------------
// SetCompositionList
//-----------------------------------------------------------------------------
HRESULT CAATpiAccessGeometryWnd::SetCompositionList (
                                  CATListValCATUnicodeString &iCompositionList)
{
  if ( !_pComposList ) return (E_FAIL);

  HRESULT oRc = S_OK;

  // Erase all existing lines
  _pComposList -> ClearLine();

  int Count = iCompositionList.Size ();

  // Fill multi list with the list of alias
  for (int Idx = 0 ; Idx < Count ; Idx ++)
  {
    _pComposList -> SetColumnItem (0, iCompositionList[Idx+1]);
  }
  return (oRc);
}


//-----------------------------------------------------------------------------
// GetRequiredDisplay
//-----------------------------------------------------------------------------
HRESULT CAATpiAccessGeometryWnd::GetRequiredDisplay (
                                                 CATBoolean * oDisplay3DGrid,
                                                 CATBoolean * oDisplayTTRSRep)
{
  if ( !oDisplay3DGrid || !oDisplayTTRSRep || 
       !_pDisplay3DGridCkB  || !_pDisplayTTRSRepCkB ) return (E_FAIL);

  HRESULT oRc = S_OK;

  (*oDisplay3DGrid) = FALSE;
  if ( _pDisplay3DGridCkB -> GetState() == CATDlgCheck )
  {
    (*oDisplay3DGrid) = TRUE;
  }

  (*oDisplayTTRSRep) = FALSE;
  if ( _pDisplayTTRSRepCkB -> GetState() == CATDlgCheck )
  {
    (*oDisplayTTRSRep) = TRUE;
  }

  return (oRc);
}
