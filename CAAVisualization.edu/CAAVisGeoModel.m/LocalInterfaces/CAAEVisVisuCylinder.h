#ifndef CAAEVisVisuCylinder_H
#define CAAEVisVisuCylinder_H

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
//  Data extension of the Cylinder component, implementing the CATI3DGeoVisu 
//  interface to enable the visualization of the Cylinders.
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
#include "CATExtIVisu.h"  // Need to derive from

class CAAEVisVisuCylinder : public CATExtIVisu
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEVisVisuCylinder();
    virtual ~CAAEVisVisuCylinder();

    // Constructs the CAT3DRep for the Cylinder. 
    // This rep is kept in the CATExtIVisu code
    //
    virtual  CATRep * BuildRep();

  private :

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisVisuCylinder(const CAAEVisVisuCylinder &iObjectToCopy);

  // Assignment operator , not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisVisuCylinder & operator = (const CAAEVisVisuCylinder &iObjectToCopy);

};
#endif
