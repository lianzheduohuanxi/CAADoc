// COPYRIGHT Dassault Systemes 2003
//==============================================================================

#ifndef CAAPuiPrsConfigAddinHeader_H
#define CAAPuiPrsConfigAddinHeader_H

// System Framework
#include "CATCommandHeader.h"

class CATFrmEditor;

//------------------------------------------------------------------------------
// Command header
// With ENOVIA LCA integration handing
//------------------------------------------------------------------------------
class CAAPuiPrsConfigAddinHeader : public CATCommandHeader
{
CATDeclareKindOf;
CATDeclareHeaderResources;

public:
  
	CAAPuiPrsConfigAddinHeader(const CATString & HeaderID,
				   const CATString & loadName,
				   const CATString & classname,
				   void * argument,
				   int state = CATFrmAvailable);  
	CATCommandHeader *Clone();
	virtual ~CAAPuiPrsConfigAddinHeader();

protected:

	CAAPuiPrsConfigAddinHeader(CATCommandHeader *header);

	void UpdateAvailability();
	void AddUIActivatedCallback();
	void RemoveUIActivatedCallback();
	void UIActivated(CATCallbackEvent,
			 void *,
			 CATNotification *,
			 CATSubscriberData,
			 CATCallback);

	CATFrmEditor *_FrmEditor;
	CATCallback   _UIActivatedCallback;
};

#endif
