// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAEPstINFPoint_H
#define CAAEPstINFPoint_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFPoint component, implementing
//  the CAAIPstINFPoint interface defined in the CAAProductStructure.edu framework,
//  allowing the setting and retrieval of point coordinate values defining a
//  CAAPstINFPoint feature.
//
//  Illustrates programming the setting and retrieval methods necessary for the
//  definition of a CAAPstINFPoint feature.
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

class CAAEPstINFPoint: public CATBaseUnknown
{
    CATDeclareClass;
    
    public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEPstINFPoint ();
    virtual ~CAAEPstINFPoint();    
    
    // Retrieves the value of the X coordinate of the point.
    HRESULT GetX ( double *opX );

	// Retrieves the value of the Y coordinate of the point.
    HRESULT GetY ( double *opY );

	// Retrieves the value of the Z coordinate of the point.
    HRESULT GetZ ( double *opZ );

	// Valuates the X coordinate of the point.
    HRESULT SetX ( double iX );

	// Valuates the Y coordinate of the point.
    HRESULT SetY ( double iY );

	// Valuates the Z coordinate of the point.
    HRESULT SetZ ( double iZ );
    
       
    
    private:
	// Copy constructor and equal operator, not implemented
    // Set as private to prevent the compiler from automatically creating them as public.
    // -------------------------------------------------------------------
    CAAEPstINFPoint (CAAEPstINFPoint &);
    CAAEPstINFPoint& operator=(CAAEPstINFPoint&);
    
};

#endif
