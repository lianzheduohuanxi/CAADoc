// COPYRIGHT Dassault Systemes 2002
//===================================================================
//
// CAAIPstINFPoint.h
// Define the CAAIPstINFPoint interface
//
///===================================================================
#ifndef CAAIPstINFPoint_H
#define CAAIPstINFPoint_H

// Local Framework
#include "CAAPstINFInterfaces.h"

// System Framework
#include "CATBaseUnknown.h"

extern ExportedByCAAPstINFInterfaces IID IID_CAAIPstINFPoint;

//------------------------------------------------------------------

// This interface is used by the CAAPstIntegrateNewFeatures use case to set
// and retrieve data defining a "CAAPstINFPoint" feature.

class ExportedByCAAPstINFInterfaces CAAIPstINFPoint: public CATBaseUnknown
{
  CATDeclareInterface;

  public:

     // Retrieve the point's X coordinate value.
	 virtual HRESULT GetX(double *opX)=0;

	 // Retrieve the point's Y coordinate value.      
     virtual HRESULT GetY(double *opY)=0;

	 // Retrieve the point's Z coordinate value.
     virtual HRESULT GetZ(double *opZ)=0;

     // Valuate the point's X coordinate.
	 virtual HRESULT SetX(double iX)=0;

     // Valuate the point's Y coordinate.
     virtual HRESULT SetY(double iY)=0;

	 // Valuate the point's Z coordinate.
	 virtual HRESULT SetZ(double iZ)=0;
	
     
     // No constructors or destructors on this pure virtual base class
     // --------------------------------------------------------------
};

//------------------------------------------------------------------

#endif
