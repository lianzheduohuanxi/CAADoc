// COPYRIGHT DASSAULT SYSTEMES 2007

#ifndef CAAEMmrCCDataExtensionModelEvent_H
#define CAAEMmrCCDataExtensionModelEvent_H

#include "CATExtIModelEvents.h"

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  CATIModelEvents implementation for MmrDataExtensionCont
//  - Standard Links between Model and Visu.
//===========================================================================
//===========================================================================

class CAAEMmrCCDataExtensionModelEvent: public CATExtIModelEvents
{
CATDeclareClass;

public:
  CAAEMmrCCDataExtensionModelEvent();
  ~CAAEMmrCCDataExtensionModelEvent();
};
#endif
