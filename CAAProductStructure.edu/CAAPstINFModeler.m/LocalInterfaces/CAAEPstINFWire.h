// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAEPstINFWire_H
#define CAAEPstINFWire_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFWire component, implementing
//  the CAAIPstINFWire interface defined in the CAAProductStructure.edu framework,
//  allowing the setting and retrieval of point values defining a CAAPstINFWire feature.
//
//  Illustrates programming the setting and retrieval methods necessary for the
//  definition of a CAAPstINFWire feature.
//
//===========================================================================
//  Inheritance:
//  ------------
//            
//  CATBaseUnknown (System Framework) 
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

// ObjectSpecsModeler Framework
#include "CATListPtrCATISpecObject.h"
class CATISpecObject;

class CAAEPstINFWire: public CATBaseUnknown
{
    CATDeclareClass;
    
    public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEPstINFWire ();
    virtual ~CAAEPstINFWire();    
    
    // Retrieves the list of CATISpecObject pointers to "CAAPstINFPoint" features
	// defining the wire.
    HRESULT GetPoints (CATListPtrCATISpecObject **opPointList);

	// Define or update a "CAAPstINFWire" feature by valuating its attribute containing a list of
	// CATISpecObject pointers to "CAAPstINFPoint" features.
    HRESULT SetPoints (CATListPtrCATISpecObject *ipPointList);   
       
    
    private:
    // Copy constructor and equal operator, not implemented
    // Set as private to prevent the compiler from automatically creating them as public.
    // -------------------------------------------------------------------
	CAAEPstINFWire (CAAEPstINFWire &);
    CAAEPstINFWire& operator=(CAAEPstINFWire&);
    
};

#endif
