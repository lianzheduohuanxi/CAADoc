// COPYRIGHT Dassault Systemes 2007

#include "SampleListEditor.h"

#include "CATDlgTableView.h"

CATImplementClass( SampleListEditor,
                   Implementation,
                   CATDlgTableView,
                   CATNull );

#define NO_TRACES_SELECTION
#define NO_TRACES_MOUSE
#define NO_TRACES_KEYBOARD
#if defined(TRACES_MOUSE) || defined(TRACES_KEYBOARD) || defined(TRACES_SELECTION)
#include <iostream.h>
#endif

class CATSelectionNotification: public CATNotification
{
  CATDeclareClass;
};
CATImplementClass( CATSelectionNotification,Implementation,CATNotification,CATNull );

//-----------------------------------------------------------------------------
// SampleListEditor : constructor
//-----------------------------------------------------------------------------
SampleListEditor::SampleListEditor( CATDlgFrame* iVizViewer, const CATString &iName, int iStyle )
                 :CATDlgTableView(iVizViewer, iName, iStyle)
{
}

//-----------------------------------------------------------------------------
// SampleListEditor : destructor
//-----------------------------------------------------------------------------
SampleListEditor::~SampleListEditor()
{
}

CATNotification * SampleListEditor::GetSelectionNotification()
{
  static CATSelectionNotification notif;
  return &notif;
}
