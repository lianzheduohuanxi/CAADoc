// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAEPstINFLine_H
#define CAAEPstINFLine_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFLine component, implementing
//  the CAAIPstINFLine interface defined in the CAAProductStructure.edu framework,
//  allowing the setting and retrieval of point values defining a CAAPstINFLine feature.
//
//  Illustrates programming the setting and retrieval methods necessary for the
//  definition of a CAAPstINFLine feature.
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
class CATISpecObject;

class CAAEPstINFLine: public CATBaseUnknown
{
    CATDeclareClass;
    
    public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEPstINFLine ();
    virtual ~CAAEPstINFLine();    
    
    // Retrieves the value of one of the two point features defining the line.
    HRESULT GetPoint (int iNum, CATISpecObject **opiPoint);

	// Valuates one of the line feature's attribute with a point feature. 
    HRESULT SetPoint (int iNum, CATISpecObject *ipiPoint);   
       
    
    private:
    // Copy constructor and equal operator, not implemented
    // Set as private to prevent the compiler from automatically creating them as public.
    // -------------------------------------------------------------------
	CAAEPstINFLine (CAAEPstINFLine &);
    CAAEPstINFLine& operator=(CAAEPstINFLine&);
    
};

#endif
