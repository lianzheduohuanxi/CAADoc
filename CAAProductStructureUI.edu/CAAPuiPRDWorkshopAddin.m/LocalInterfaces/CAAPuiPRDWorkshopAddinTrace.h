// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// CAAPuiPRDWorkshopAddinTrace.h
// Trace macro
//
//===================================================================
#ifndef CAAPuiPRDWorkshopAddinTrace_H
#define CAAPuiPRDWorkshopAddinTrace_H

#include <iostream.h>

#ifdef  CAAPuiPRDWorkshopAddinTRACE
#error "CAAPuiPRDWorkshopAddinTRACE is already defined"
#else
#define CAAPuiPRDWorkshopAddinTRACE(msg)	cout << msg << endl
#endif

#endif
