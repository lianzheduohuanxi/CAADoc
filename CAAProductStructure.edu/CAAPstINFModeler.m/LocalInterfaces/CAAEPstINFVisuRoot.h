// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAEPstINFVisuRoot_H
#define CAAEPstINFVisuRoot_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFRoot component, implementing the CATI3DGeoVisu 
//  interface to enable the visualization of a Root.
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

class CAAEPstINFVisuRoot : public CATExtIVisu
{
    CATDeclareClass;

	public:

	// Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEPstINFVisuRoot();
    virtual ~CAAEPstINFVisuRoot();

    // Constructs the CAT3DRep for the Root. 
    CATRep * BuildRep();

    private:

    // Copy constructor and assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEPstINFVisuRoot(const CAAEPstINFVisuRoot &iObjectToCopy);
    CAAEPstINFVisuRoot & operator = (const CAAEPstINFVisuRoot &iObjectToCopy);

};
#endif
