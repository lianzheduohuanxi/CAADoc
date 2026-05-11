// COPYRIGHT DASSAULT SYSTEMES 2002
//===================================================================
//
// CAAIPstINFLine.h
// Define the CAAIPstINFLine interface
//
//===================================================================
#ifndef CAAIPstINFLine_H
#define CAAIPstINFLine_H

// Local Framework
#include "CAAPstINFInterfaces.h"

// System Framework
#include "CATBaseUnknown.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

extern ExportedByCAAPstINFInterfaces IID IID_CAAIPstINFLine;

//----------------------------------------------------------------------------------

// This interface is used by the CAAPstIntegrateNewFeatures use case to set
// and retrieve data defining a "CAAPstINFLine" feature.

class ExportedByCAAPstINFInterfaces CAAIPstINFLine: public CATBaseUnknown
{
  CATDeclareInterface;

  public:

     // Retrieves one of the point features pointed to by the line's attribute definitions.
     virtual HRESULT GetPoint(int iNum, CATISpecObject **opiPoint)=0;

     // Valuates one of the line's attribute definitions with a point feature.
     virtual HRESULT SetPoint(int iNum, CATISpecObject *ipiPoint)=0;
          
    // No constructors or destructors on this pure virtual base class
    // --------------------------------------------------------------
};

//------------------------------------------------------------------

#endif
