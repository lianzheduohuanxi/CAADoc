// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// CAAPuiPrsConfigAddinTrace.h
// Trace macro
//
//===================================================================
#ifndef CAAPuiPrsConfigAddinTrace_H
#define CAAPuiPrsConfigAddinTrace_H

#include <iostream.h>

#ifdef  CAAPuiPrsConfigAddinTRACE
#error "CAAPuiPrsConfigAddinTRACE is already defined"
#else
#define CAAPuiPrsConfigAddinTRACE(msg)	cout << msg << endl
#endif

#endif
