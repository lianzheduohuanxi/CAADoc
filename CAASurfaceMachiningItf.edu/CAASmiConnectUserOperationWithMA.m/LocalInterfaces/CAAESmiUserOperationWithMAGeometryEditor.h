// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiUserOperationWithMAGeometryEditor.h
//
//===================================================================
#ifndef CAAESmiUserOperationWithMAGeometryEditor_H
#define CAAESmiUserOperationWithMAGeometryEditor_H

#include "CATIMfgGeometryActivity.h"
#include "CATDlgFrame.h"
#include "CATDialog.h"

class CAAESmiUserOperationWithMAGeometryEditor: public CATIMfgGeometryActivity
{
  CATDeclareClass;

  public:

	 // Standard constructors and destructors for an implementation class
     CAAESmiUserOperationWithMAGeometryEditor ();
     virtual ~CAAESmiUserOperationWithMAGeometryEditor ();

     // Writes the geometry tabpage frame.
     HRESULT GetMainPanelEditor (CATDialog * iFather, CATDlgFrame*& oFrame, CATDlgStyle iStyle=NULL) ;


  private:
  
	// The copy constructor and the equal operator must not be implemented
    CAAESmiUserOperationWithMAGeometryEditor (CAAESmiUserOperationWithMAGeometryEditor &);
    CAAESmiUserOperationWithMAGeometryEditor& operator=(CAAESmiUserOperationWithMAGeometryEditor&);

};

#endif
