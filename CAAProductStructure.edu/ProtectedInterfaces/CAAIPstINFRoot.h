// COPYRIGHT Dassault Systemes 2002
//===================================================================
//
// CAAIPstINFRoot.h
// Define the CAAIPstINFRoot interface
//
//===================================================================
#ifndef CAAIPstINFRoot_H
#define CAAIPstINFRoot_H

// Local Framework
#include "CAAPstINFInterfaces.h"

// System Framework
#include "CATLISTV_CATBaseUnknown.h"
#include "CATBaseUnknown.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

extern ExportedByCAAPstINFInterfaces IID IID_CAAIPstINFRoot;

//------------------------------------------------------------------
// This interface is used to aggregate a new feature to the root feature.

class ExportedByCAAPstINFInterfaces CAAIPstINFRoot: public CATBaseUnknown
{
  CATDeclareInterface;

  public:

   	// Aggregates a new feature under the root.
    virtual HRESULT AddChild (CATISpecObject *ipiFeature)=0;

    
	// Returns a list of the direct children of the root node.
    virtual HRESULT GetChildren(CATListValCATBaseUnknown_var **opList)=0;
 
    // No constructors or destructors on this pure virtual base class
    // --------------------------------------------------------------
};

//------------------------------------------------------------------

#endif
