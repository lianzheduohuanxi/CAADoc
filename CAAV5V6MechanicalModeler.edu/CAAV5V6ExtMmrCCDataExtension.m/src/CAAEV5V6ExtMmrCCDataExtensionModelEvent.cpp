// COPYRIGHT DASSAULT SYSTEMES 2012
//======================================================================================
//
// CAAEV5V6ExtMmrCCDataExtensionModelEvent :
// Provide implementation to interface CATIModelEvents 
//   - Standard Links between Model and Visu.
//
// Note : CAAEV5V6ExtMmrCCDataExtensionModelEvent is the same use case as CAAECCDataExtensionModelEvent. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//======================================================================================

// CAAV5V6MechanicalModeler.edu Framework
#include "CAAEV5V6ExtMmrCCDataExtensionModelEvent.h"

// Visualization Framework in V5
// VisualizationController Framework in V6
#include "TIE_CATIModelEvents.h"

CATImplementClass(CAAEV5V6ExtMmrCCDataExtensionModelEvent, DataExtension, CATExtIModelEvents, CAAV5V6ExtMmrCCDataExtension);

TIE_CATIModelEvents(CAAEV5V6ExtMmrCCDataExtensionModelEvent);

//-----------------------------------------------------------------------------
// CAAEV5V6ExtMmrCCDataExtensionModelEvent : constructor
//-----------------------------------------------------------------------------
CAAEV5V6ExtMmrCCDataExtensionModelEvent::CAAEV5V6ExtMmrCCDataExtensionModelEvent():CATExtIModelEvents()
{}

//-----------------------------------------------------------------------------
// CAAEV5V6ExtMmrCCDataExtensionModelEvent : destructor
//-----------------------------------------------------------------------------
CAAEV5V6ExtMmrCCDataExtensionModelEvent::~CAAEV5V6ExtMmrCCDataExtensionModelEvent()
{}
