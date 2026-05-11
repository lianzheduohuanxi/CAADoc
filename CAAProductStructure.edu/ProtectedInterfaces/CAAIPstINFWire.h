// COPYRIGHT Dassault Systemes 2002
//===================================================================
//
// CAAIPstINFWire.h
// Define the CAAIPstINFWire interface
//
//===================================================================

#ifndef CAAIPstINFWire_H
#define CAAIPstINFWire_H

// Local Framework
#include "CAAPstINFInterfaces.h"

// System Framework
#include "CATBaseUnknown.h"

// ObjectSpecsModeler Framework
#include "CATListPtrCATISpecObject.h"

extern ExportedByCAAPstINFInterfaces IID IID_CAAIPstINFWire;

//------------------------------------------------------------------

// This interface is used by the CAAPstIntegrateNewFeatures use case to set
// and retrieve data defining a "CAAPstINFWire" feature.

class ExportedByCAAPstINFInterfaces CAAIPstINFWire: public CATBaseUnknown
{
  CATDeclareInterface;

  public:

     // Retrieve the list of points defining the wire.
	 virtual HRESULT GetPoints(CATListPtrCATISpecObject **pointList)=0;

	 // Valuate the list of points defining the wire.
	 virtual HRESULT SetPoints(CATListPtrCATISpecObject *pointList)=0;

  // No constructors or destructors on this pure virtual base class
  // --------------------------------------------------------------
};

//------------------------------------------------------------------

#endif
