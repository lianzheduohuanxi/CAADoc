// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAASmiUserOperationGeometryPanel.h
//
//===================================================================
#ifndef CAASmiUserOperationGeometryPanel_H
#define CAASmiUserOperationGeometryPanel_H

#include "CAASmiUserOperationGeomUIEnv.h"

#include "CATDlgFrame.h"
class CATDlgPushButton;

class ExportedByCAASmiUserOperationGeomUIEnv CAASmiUserOperationGeometryPanel: public CATDlgFrame
{
  // Allows customization/internationalization of command's messages
  DeclareResource(CAASmiUserOperationGeometryPanel, CATDlgFrame )

  public:

	 // Standard constructors and destructors for an implementation class
     CAASmiUserOperationGeometryPanel(CATDialog *iFather, const CATBaseUnknown_var &ispMachFeature);
     virtual ~CAASmiUserOperationGeometryPanel();

     // Callbacks on push buttons
	 void SelectCurve(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData iUsefulData);
	 void SelectZone(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData iUsefulData);
	 void RemoveAll(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData iUsefulData);
	 void NewZone(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData iUsefulData);
	 void Export(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData iUsefulData);
						
     // Callbacks on guide
	 void UpdateButtons(CATCallbackEvent iEvent,void *iFrom, CATNotification *iNotification, CATSubscriberData iClientData,CATCallback iCallBack);

  private:

	 // Machinable feature
	 CATBaseUnknown_var _spGuide;

	 // Push Buttons
	 CATDlgPushButton * _pSelCurveButton;
	 CATDlgPushButton * _pSelZoneButton;
	 CATDlgPushButton * _pNewZoneButton;
	 CATDlgPushButton * _pExportButton;
};

#endif
