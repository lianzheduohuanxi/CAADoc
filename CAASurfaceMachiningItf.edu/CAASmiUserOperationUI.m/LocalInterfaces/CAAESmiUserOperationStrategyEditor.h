// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiUserOperationStrategyEditor.h
//
//===================================================================
#ifndef CAAESmiUserOperationStrategyEditor_H
#define CAAESmiUserOperationStrategyEditor_H

#include "CATIMfgStrategyActivity.h"
#include "CATDialog.h"
#include "CATDlgFrame.h"

class CAAESmiUserOperationStrategyEditor: public CATIMfgStrategyActivity
{
  CATDeclareClass;

  public:

	 // Standard constructors and destructors for an implementation class
     CAAESmiUserOperationStrategyEditor ();
     virtual ~CAAESmiUserOperationStrategyEditor ();

     // Writes the strategy tabpage frame. 
	 HRESULT GetMainPanelEditor (CATDialog * iFather , CATDlgFrame*&  oFrame , CATDlgStyle  iStyle=NULL) ;

  private:

     // The copy constructor and the equal operator must not be implemented
    CAAESmiUserOperationStrategyEditor (CAAESmiUserOperationStrategyEditor &);
    CAAESmiUserOperationStrategyEditor& operator=(CAAESmiUserOperationStrategyEditor&);

};
#endif
