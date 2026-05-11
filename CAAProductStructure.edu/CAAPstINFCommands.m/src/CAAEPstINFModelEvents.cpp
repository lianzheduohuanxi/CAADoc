// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAEPstINFModelEvents.h"

// Visualization Framework
#include "CATIModelEvents.h"

// Others
#include "iostream.h"

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIModelEvents.h"
TIE_CATIModelEvents(CAAEPstINFModelEvents);

// To declare that the class is a data extension of CAAPstINFRoot, CAAPstINFLine and
// CAAPstINFPoint.
//
CATBeginImplementClass(CAAEPstINFModelEvents,
   			           DataExtension, 
				       CATBaseUnknown, 
				       CAAPstINFPoint);
CATAddClassExtension(CAAPstINFLine);
CATAddClassExtension(CAAPstINFWire);
CATAddClassExtension(CAAPstINFRoot);
CATEndImplementClass(CAAEPstINFModelEvents); 
 
// To declare that CAAEPstINFModelEvents implements CATIModelEvents for the CAAPstINFRoot,
// CAAPstINFPoint, CAAPstINFLine and CAAPstINFWire components, insert the following lines
// in the interface dictionary:
//
//    CAAPstINFPoint    CATIModelEvents  libCAAPstINFCommands
//    CAAPstINFLine     CATIModelEvents  libCAAPstINFCommands
//    CAAPstINFWire     CATIModelEvents  libCAAPstINFCommands
//    CAAPstINFRoot     CATIModelEvents  libCAAPstINFCommands
//
//-----------------------------------------------------------------------------------

CAAEPstINFModelEvents::CAAEPstINFModelEvents()
{
  cout << "******CAAEPstINFModelEvents::CAAEPstINFModelEvents" << endl;
}

CAAEPstINFModelEvents::~CAAEPstINFModelEvents()
{
  cout << "******CAAEPstINFModelEvents::~CAAEPstINFModelEvents" << endl;
}
