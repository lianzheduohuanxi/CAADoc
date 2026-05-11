// COPYRIGHT Dassault Systemes 2007

#ifndef SampleListEditor_H
#define SampleListEditor_H

#include "CATDlgTableView.h"
#include "CATString.h"

class SampleListEditor: public CATDlgTableView
{
  CATDeclareClass;

  public:
  SampleListEditor( CATDlgFrame *iViewer, const CATString &iName, int iStyle=CATRightScroll|CATListSortable );
  virtual ~SampleListEditor ();

  // Copy constructor and equal operator
  // -----------------------------------
  SampleListEditor (SampleListEditor &);
  SampleListEditor& operator=(SampleListEditor&);

  CATNotification *GetSelectionNotification();
};

//-----------------------------------------------------------------------

#endif
