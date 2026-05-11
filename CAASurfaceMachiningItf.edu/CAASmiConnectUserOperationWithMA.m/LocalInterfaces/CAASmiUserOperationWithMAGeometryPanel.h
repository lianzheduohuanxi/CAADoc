// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAASmiUserOperationWithMAGeometryPanel.h
//
//===================================================================
#ifndef CAASmiUserOperationWithMAGeometryPanel_H
#define CAASmiUserOperationWithMAGeometryPanel_H

#include "CATDlgFrame.h"
#include "CATIContainer.h"
class CATDlgCombo;
class CATDlgDialog;

class CAASmiUserOperationWithMAGeometryPanel: public CATDlgFrame
{
  // Allows customization/internationalization of command's messages
  DeclareResource( CAASmiUserOperationWithMAGeometryPanel, CATDlgFrame )
  
  public:

	 // Standard constructors and destructors for an implementation class
     CAASmiUserOperationWithMAGeometryPanel(CATDialog *iFather, const CATBaseUnknown_var &iObject);
     virtual ~CAASmiUserOperationWithMAGeometryPanel();

  private:
     
	 // Callback on combo box (selection)
	 void SelectMachArea ( CATCommand *iPublisher, CATNotification *iNotification,
						   CATCommandClientData iUsefulData );
     
	 // Current user operation
	 CATBaseUnknown_var _spBaseActivity;

	 // Combo box
	 CATDlgCombo * _pDlgCombo;

	 // List of Machining Areas inside the model
     CATListPtrCATBaseUnknown _pListOfMAs;

};

#endif
