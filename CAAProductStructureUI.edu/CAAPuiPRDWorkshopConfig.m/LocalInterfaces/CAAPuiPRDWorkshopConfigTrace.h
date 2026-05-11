// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// CAAPuiPRDWorkshopConfigTrace.h
// Trace macro
//
//===================================================================
#ifndef CAAPuiPRDWorkshopConfigTrace_H
#define CAAPuiPRDWorkshopConfigTrace_H

#include <iostream.h>

#ifdef  CAAPuiPRDWorkshopConfigTRACE
#error "CAAPuiPRDWorkshopConfigTRACE is already defined"
#else
#define CAAPuiPRDWorkshopConfigTRACE(msg)		cout << msg << endl
#endif

#endif
