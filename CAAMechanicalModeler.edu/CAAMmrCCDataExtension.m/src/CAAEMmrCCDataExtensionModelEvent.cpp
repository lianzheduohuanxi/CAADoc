// COPYRIGHT DASSAULT SYSTEMES 2007
//======================================================================================
//
// CAAEMmrCCDataExtensionModelEvent.cpp
// Provide implementation to interface
//      CATIModelEvents - Standard Links between Model and Visu.
//======================================================================================

#include "CAAEMmrCCDataExtensionModelEvent.h"

CATImplementClass(CAAEMmrCCDataExtensionModelEvent, DataExtension, CATExtIModelEvents, CAAMmrCCDataExtension);

//CATIModelEvents Interface
#include "TIE_CATIModelEvents.h"
TIEchain_CATIModelEvents(CAAEMmrCCDataExtensionModelEvent);
//-----------------------------------------------------------------------------
// CATFdeEventsExt : constructor
//-----------------------------------------------------------------------------
CAAEMmrCCDataExtensionModelEvent::CAAEMmrCCDataExtensionModelEvent():CATExtIModelEvents()
{
}

//-----------------------------------------------------------------------------
// CATFdeEventsExt : destructor
//-----------------------------------------------------------------------------
CAAEMmrCCDataExtensionModelEvent::~CAAEMmrCCDataExtensionModelEvent()
{
}
