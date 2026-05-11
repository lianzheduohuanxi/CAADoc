// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiUserOperationMacroEditor.h
//
//===================================================================
#ifndef CAAESmiUserOperationMacroEditor_H
#define CAAESmiUserOperationMacroEditor_H

#include "CATIMfgMacroEditorActivity.h"
#include "CATDlgFrame.h"
#include "CATDialog.h"

class CAAESmiUserOperationMacroEditor: public CATIMfgMacroEditorActivity
{
  CATDeclareClass;

  public:

     // Standard constructors and destructors for an implementation class
     CAAESmiUserOperationMacroEditor ();
     virtual ~CAAESmiUserOperationMacroEditor ();

     // Writes the macro tabpage frame. 
     HRESULT GetMainPanelEditor (CATDialog * iFather, CATDlgFrame*&  oFrame, CATDlgStyle iStyle=NULL) ;


  private:

     // The copy constructor and the equal operator must not be implemented
     CAAESmiUserOperationMacroEditor (CAAESmiUserOperationMacroEditor &);
     CAAESmiUserOperationMacroEditor& operator=(CAAESmiUserOperationMacroEditor&);

};

#endif
