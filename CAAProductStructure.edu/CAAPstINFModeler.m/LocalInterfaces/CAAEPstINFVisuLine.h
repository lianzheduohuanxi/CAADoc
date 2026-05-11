// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAEPstINFVisuLine_H
#define CAAEPstINFVisuLine_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFLine component, implementing the CATI3DGeoVisu 
//  interface to enable the visualization of a line.
//
//  This class derives from the CATExtIVisu adapter.
//
//  Illustrates programming the visualization of an object by implementing the
//  CATI3DGeoVisu interface of the Visualization framework.
//
//  Inheritance:
//  ------------
//            
//  CATExtIVisu (Visualization)
//     CATBaseUnknown (System Framework)  
//
//===========================================================================

// Visualization Framework
#include "CATExtIVisu.h"    // Need to derive from

class CAAEPstINFVisuLine : public CATExtIVisu
{
    CATDeclareClass;

	public:

	// Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEPstINFVisuLine();
    virtual ~CAAEPstINFVisuLine();

    // Constructs the CAT3DRep for the Line. 
    CATRep * BuildRep();

    private:

    // Copy constructor and assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEPstINFVisuLine(const CAAEPstINFVisuLine &iObjectToCopy);
    CAAEPstINFVisuLine & operator = (const CAAEPstINFVisuLine &iObjectToCopy);

};
#endif
