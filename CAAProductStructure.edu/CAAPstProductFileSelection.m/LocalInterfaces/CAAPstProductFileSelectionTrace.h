// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// CATCAAPstProductFileSelectionTrace.h
// Trace macro
//
//===================================================================
#ifndef CAAPstProductFileSelectionTrace_H
#define CAAPstProductFileSelectionTrace_H

#include <iostream.h>

#ifdef  CAAPstPFSTRACE
#error "CAAPstPFSTRACE is already defined"
#else
#define CAAPstPFSTRACE(msg)	cout << msg << endl
#endif

#endif
