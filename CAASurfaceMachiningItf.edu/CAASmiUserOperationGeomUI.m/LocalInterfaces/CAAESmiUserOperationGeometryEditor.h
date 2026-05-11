// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiUserOperationGeometryEditor.h
//
//===================================================================
#ifndef CAAESmiUserOperationGeometryEditor_H
#define CAAESmiUserOperationGeometryEditor_H

#include "CATIMfgGeometryActivity.h"
#include "CATDlgFrame.h"
#include "CATDialog.h"

class CAAESmiUserOperationGeometryEditor: public CATIMfgGeometryActivity
{
  CATDeclareClass;

  public:

	 // Standard constructors and destructors for an implementation class
     CAAESmiUserOperationGeometryEditor ();
     virtual ~CAAESmiUserOperationGeometryEditor ();

     // Writes the geometry tabpage frame.
     HRESULT GetMainPanelEditor (CATDialog * iFather , CATDlgFrame*&  oFrame , CATDlgStyle  iStyle=NULL) ;


  private:
  
	// The copy constructor and the equal operator must not be implemented
    CAAESmiUserOperationGeometryEditor (CAAESmiUserOperationGeometryEditor &);
    CAAESmiUserOperationGeometryEditor& operator=(CAAESmiUserOperationGeometryEditor&);

    // Instanciates a nul machining feature
	HRESULT CreateCAAMachiningFeature(CATBaseUnknown_var & oFeature);

};

#endif
