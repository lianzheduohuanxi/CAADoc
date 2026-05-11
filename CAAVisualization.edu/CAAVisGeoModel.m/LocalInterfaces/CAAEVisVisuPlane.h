#ifndef CAAEVisVisuPlane_H
#define CAAEVisVisuPlane_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document (CAAGeometry) with its own workshop and 
//  commands.
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAASysPlane component, implementing the CATI3DGeoVisu 
//  interface to enable the visualization of the planes.
//  This class derives from the CATExtIVisu adapter.
//
//===========================================================================
//  Inheritance:
//  ------------
//            CATExtIVisu ( Visualization Framework) 
//                CATBaseUnknown (System Framework).
//
//===========================================================================
//  Main Method:
//  ------------
//
//  BuildRep
//
//===========================================================================
// Visualization Framework
#include "CATExtIVisu.h"   // Need to derive from

class CAAEVisVisuPlane : public CATExtIVisu 
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEVisVisuPlane();
    virtual ~CAAEVisVisuPlane();

    // Constructs the CAT3DRep for the Plane. 
    // This rep is kept in the CATExtIVisu code
    //
    virtual  CATRep * BuildRep();

  private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisVisuPlane(const CAAEVisVisuPlane &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisVisuPlane & operator = (const CAAEVisVisuPlane &iObjectToCopy);
};
#endif
