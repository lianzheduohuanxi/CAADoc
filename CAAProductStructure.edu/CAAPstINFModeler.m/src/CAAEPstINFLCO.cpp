// COPYRIGHT Dassault Systemes 2002

// Local Framework
#include "CAAEPstINFLCO.h"

// ObjectModelerBase Framework
#include "CATIRedrawEvent.h"
#include "LifeCycleObject.h"

// Visualization Framework
#include "CATDelete.h"
#include "CATIModelEvents.h"

// Others
#include "iostream.h"

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_LifeCycleObject.h"
TIE_LifeCycleObject( CAAEPstINFLCO);

// To declare that the class is a data extension of "CAAPstINFLine" and "CAAPstINFWire" 
//
CATBeginImplementClass(CAAEPstINFLCO,
   		      	       DataExtension, 
		               CATBaseUnknown, 
			           CAAPstINFLine);
CATAddClassExtension(CAAPstINFWire);
CATEndImplementClass(CAAEPstINFLCO);

// To declare that CAAEPstINFLCO implements LifeCycleObject for the
// CAAPstINFLine and CAAPstINFWire components, insert the following line in the interface dictionary:
//
//    CAAPstINFLine    LifeCycleObject   libCAAINFModeler
//    CAAPstINFWire    LifeCycleObject   libCAAINFModeler
//
//-----------------------------------------------------------------------------
// CAAEPstINFLCO : constructor
//-----------------------------------------------------------------------------
CAAEPstINFLCO::CAAEPstINFLCO():
    CATSpecLifeCycleObjectExt()
{
}

//-----------------------------------------------------------------------------
// CAAEPstINFLCO : destructor
//-----------------------------------------------------------------------------
CAAEPstINFLCO::~CAAEPstINFLCO()
{
}
 
//-----------------------------------------------------------------------------
// Implements LifeCycleObject::remove
//-----------------------------------------------------------------------------
void CAAEPstINFLCO::remove (int forCloseContext )
{
	cout << "******CAAEPstINFLCO::remove" << endl;

	HRESULT rc;

    if (!forCloseContext)
	{
       // Update the navigation tree
       CATIRedrawEvent *piRedrawEventOnFeature = NULL;
       rc = this -> QueryInterface(IID_CATIRedrawEvent,
		                           (void**) &piRedrawEventOnFeature);
       if (SUCCEEDED(rc))
	   {
          piRedrawEventOnFeature -> RedrawParent();
          piRedrawEventOnFeature -> Release();
          piRedrawEventOnFeature = NULL;
	   }

	   // Force an update of the visualization process
       CATIModelEvents *piModelEventsOnFeature = NULL;
       rc = this -> QueryInterface(IID_CATIModelEvents,
	   	                           (void**) &piModelEventsOnFeature);

       if (SUCCEEDED(rc))
	   {
          CATDelete delNotif (this);
          piModelEventsOnFeature -> Dispatch(delNotif);
          piModelEventsOnFeature -> Release();
          piModelEventsOnFeature = NULL;
	   }
	}

    CATSpecLifeCycleObjectExt::remove(forCloseContext);

    return;
}

